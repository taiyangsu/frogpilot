# PFEIFER - VTSC

# Acknowledgements:
# This code is a rewrite of the move-fast teams vtsc implementation. (https://github.com/move-fast/openpilot) Huge thanks to them for the initial implementation.
# I also used sunnypilot as a reference. (https://github.com/sunnyhaibin/sunnypilot) Big thanks for sunny's amazing work

# Tweaked by FrogAi for FrogPilot

import numpy as np
from openpilot.common.numpy_fast import clip
from openpilot.common.realtime import DT_MDL
from time import time

Polynomial = np.polynomial.polynomial.Polynomial

MIN_DIST = 0.5  # Seconds. Min distance to evaluate for
MAX_DIST = 5    # Seconds. Max distance to evaluate for

MIN_TARGET_DIST = 1.5  # Seconds. Min distance to use as an acceleration target
MAX_TARGET_DIST = 5.0  # Seconds. Max distance to use as an acceleration target

# Maximum rate of change of acceleration this controller will request
MAX_JERK = 1.0  # m/s^3

# The maximum this controller will request to decelerate
MAX_DECEL = -2.5  # m/s^2

TARGET_LAT_A = 2.4  # m/s^2

MIN_TARGET_V = 5  # m/s


def poly_x_for_y(poly, y):
  """
  Finds the x values that solve for y with a given polynomial.
  """
  return (poly - y).roots()


def poly_points_to_curvature(poly, x_points):
  """
  This function takes a numpy Polynomial and points on the x axis and returns
  the curve K at each point.

  ref: https://math24.net/curvature-radius.html
  curve at a point is defined as the mean curvature of the arc when the
  displacement along the arc nears 0

           lim       |  delta a  |
  K = -------------- | --------- |
       delta s -> 0  |  delta s  |

  radius R is defined as inverse of the curvature K
  R = 1 / K

  Therefore:
  K = 1 / R

  R can be obtained when y is a function of x using the following equation:

       ( 1 + y'(x)^2 ) ^ (3/2)
  R = -------------------------
             | y''(x) |

  Therefore:
            | y''(x) |
  K = -------------------------
       ( 1 + y'(x)^2 ) ^ (3/2)

  """
  dy = poly.deriv()
  ddy = dy.deriv()
  def point_to_curv(x):
    k = abs(ddy(x)) / ((1 + dy(x)**2)**(3/2))
    return k

  return np.vectorize(point_to_curv)(x_points)


class VisionTurnController():
  def __init__(self):
    self.gas_pressed = False
    self.op_enabled = False
    self.a_ego = 0
    self.a_target = 0
    self.v_cruise_setpoint = 0
    self.v_ego = 0
    self.v_target = 0
    self.last_update = time()
    self.update_time_diff = DT_MDL  # Seconds, updated each update loop

    self.reset()

  @property
  def active(self):
    turn_limit_exceeded = self.v_target < self.v_cruise_setpoint
    return self.op_enabled and not self.gas_pressed and turn_limit_exceeded

  @property
  def plan(self):
    v_target = self.v_target if self.v_target < self.v_cruise_setpoint else self.v_cruise_setpoint
    return (self.a_target, v_target)

  def reset(self):
    self.x_plan = []
    self.y_plan = []

  def get_driving_path_poly(self):
    """
    Fits the points from the predicted driving path to a numpy polynomial function.
    """
    # Calculate curvature polynomial from predicted path
    if len(self.x_plan) > 3:
      return Polynomial.fit(self.x_plan, self.y_plan, 4)

    return Polynomial([0, 0, 0, 0])

  def update_current_state(self, sm):
    """
    Uses the current state of the car to calculate the curvature based off the
    angle of the wheels and store the max acceptable velocity for the curve as
    well as the current lateral acceleration.
    """
    now = time()
    self.update_time_diff = now - self.last_update
    self.last_update = now

  def apply_limits(self, turn_aggressiveness):
    # VTSC not needed or disabled, do not change targets
    if not self.active:
      self.a_target = self.a_ego
      self.v_target = self.v_cruise_setpoint
      return

    if self.max_pred_lat_acc > TARGET_LAT_A * turn_aggressiveness:
      self.a_target = max(self.a_target, MAX_DECEL)
      self.v_target = min(self.v_target, self.v_cruise_setpoint)  # Never request more velocity than the set max
    # Limit accel based on MAX_JERK
    a_ego = min(self.a_ego, 0)
    min_accel = a_ego - (MAX_JERK * self.update_time_diff)
    max_accel = a_ego + (MAX_JERK * self.update_time_diff)
    self.a_target = clip(self.a_target, min_accel, max_accel)

  def update_calculations(self, sm, curve_sensitivity, turn_aggressiveness):
    self.update_current_state(sm)

    # Fit the model's predicted path to polynomial
    path_poly = self.get_driving_path_poly()

    # Find distances on poly that match minimums/maximums
    path_poly_d = path_poly.deriv()
    eval_distances = poly_x_for_y(path_poly_d, 0)

    # Remove max/min values outside our distance bounds
    min_dist = self.v_ego * MIN_DIST
    max_dist = self.v_ego * MAX_DIST
    eval_distances = [x for x in eval_distances if x > min_dist and x < max_dist]

    # If the calculated distances are not within our bounds then we know our min or max dist will be the max curve
    if len(eval_distances) == 0:
      eval_distances = [MIN_DIST, MAX_DIST]

    # Find curvature values from the predicted driving path
    v_ego = max(self.v_ego, 0.1)  # Ensure a value greater than 0 for calculations
    predicted_curvatures = poly_points_to_curvature(path_poly, eval_distances) * curve_sensitivity
    predicted_lat_accels = np.abs(predicted_curvatures * (v_ego**2))

    # Find max lat accel
    accel_idx = np.argmax(predicted_lat_accels)
    self.max_pred_lat_acc = predicted_lat_accels[accel_idx]

    # Set an upper limit to prevent activating for stops
    if self.max_pred_lat_acc > 5.0:
      self.v_target = self.v_ego
    else:
      max_curve = predicted_curvatures[accel_idx]
      self.v_target = ((TARGET_LAT_A * turn_aggressiveness) / max_curve) ** 0.5

    # Get the target distance to hit the velocity at
    min_target_dist = MIN_TARGET_DIST * v_ego
    max_target_dist = MAX_TARGET_DIST * v_ego
    target_dist = clip(eval_distances[accel_idx], min_target_dist, max_target_dist)

    self.v_target = max(self.v_target, MIN_TARGET_V)

    # Calculate the target acceleration using the difference in velocity and the target distance
    self.a_target = ((self.v_target ** 2) - (v_ego ** 2)) / (2 * target_dist)

    # Update targets based on limits
    self.apply_limits(turn_aggressiveness)

  def update(self, enabled, v_ego, a_ego, v_cruise_setpoint, sm, curve_sensitivity, turn_aggressiveness):
    self.op_enabled = enabled
    self.gas_pressed = sm['carState'].gasPressed
    self.v_ego = v_ego
    self.a_ego = a_ego
    self.v_cruise_setpoint = v_cruise_setpoint
    self.x_plan = np.array(sm['modelV2'].position.x)[:17]
    self.y_plan = np.array(sm['modelV2'].position.y)[:17]

    self.update_calculations(sm, curve_sensitivity, turn_aggressiveness)

vtsc = VisionTurnController()
