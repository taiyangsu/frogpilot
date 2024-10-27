#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                       Code generated with SymPy 1.12                       *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_8856740152215769533) {
   out_8856740152215769533[0] = delta_x[0] + nom_x[0];
   out_8856740152215769533[1] = delta_x[1] + nom_x[1];
   out_8856740152215769533[2] = delta_x[2] + nom_x[2];
   out_8856740152215769533[3] = delta_x[3] + nom_x[3];
   out_8856740152215769533[4] = delta_x[4] + nom_x[4];
   out_8856740152215769533[5] = delta_x[5] + nom_x[5];
   out_8856740152215769533[6] = delta_x[6] + nom_x[6];
   out_8856740152215769533[7] = delta_x[7] + nom_x[7];
   out_8856740152215769533[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_8849079539949943851) {
   out_8849079539949943851[0] = -nom_x[0] + true_x[0];
   out_8849079539949943851[1] = -nom_x[1] + true_x[1];
   out_8849079539949943851[2] = -nom_x[2] + true_x[2];
   out_8849079539949943851[3] = -nom_x[3] + true_x[3];
   out_8849079539949943851[4] = -nom_x[4] + true_x[4];
   out_8849079539949943851[5] = -nom_x[5] + true_x[5];
   out_8849079539949943851[6] = -nom_x[6] + true_x[6];
   out_8849079539949943851[7] = -nom_x[7] + true_x[7];
   out_8849079539949943851[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_4271361262171071118) {
   out_4271361262171071118[0] = 1.0;
   out_4271361262171071118[1] = 0;
   out_4271361262171071118[2] = 0;
   out_4271361262171071118[3] = 0;
   out_4271361262171071118[4] = 0;
   out_4271361262171071118[5] = 0;
   out_4271361262171071118[6] = 0;
   out_4271361262171071118[7] = 0;
   out_4271361262171071118[8] = 0;
   out_4271361262171071118[9] = 0;
   out_4271361262171071118[10] = 1.0;
   out_4271361262171071118[11] = 0;
   out_4271361262171071118[12] = 0;
   out_4271361262171071118[13] = 0;
   out_4271361262171071118[14] = 0;
   out_4271361262171071118[15] = 0;
   out_4271361262171071118[16] = 0;
   out_4271361262171071118[17] = 0;
   out_4271361262171071118[18] = 0;
   out_4271361262171071118[19] = 0;
   out_4271361262171071118[20] = 1.0;
   out_4271361262171071118[21] = 0;
   out_4271361262171071118[22] = 0;
   out_4271361262171071118[23] = 0;
   out_4271361262171071118[24] = 0;
   out_4271361262171071118[25] = 0;
   out_4271361262171071118[26] = 0;
   out_4271361262171071118[27] = 0;
   out_4271361262171071118[28] = 0;
   out_4271361262171071118[29] = 0;
   out_4271361262171071118[30] = 1.0;
   out_4271361262171071118[31] = 0;
   out_4271361262171071118[32] = 0;
   out_4271361262171071118[33] = 0;
   out_4271361262171071118[34] = 0;
   out_4271361262171071118[35] = 0;
   out_4271361262171071118[36] = 0;
   out_4271361262171071118[37] = 0;
   out_4271361262171071118[38] = 0;
   out_4271361262171071118[39] = 0;
   out_4271361262171071118[40] = 1.0;
   out_4271361262171071118[41] = 0;
   out_4271361262171071118[42] = 0;
   out_4271361262171071118[43] = 0;
   out_4271361262171071118[44] = 0;
   out_4271361262171071118[45] = 0;
   out_4271361262171071118[46] = 0;
   out_4271361262171071118[47] = 0;
   out_4271361262171071118[48] = 0;
   out_4271361262171071118[49] = 0;
   out_4271361262171071118[50] = 1.0;
   out_4271361262171071118[51] = 0;
   out_4271361262171071118[52] = 0;
   out_4271361262171071118[53] = 0;
   out_4271361262171071118[54] = 0;
   out_4271361262171071118[55] = 0;
   out_4271361262171071118[56] = 0;
   out_4271361262171071118[57] = 0;
   out_4271361262171071118[58] = 0;
   out_4271361262171071118[59] = 0;
   out_4271361262171071118[60] = 1.0;
   out_4271361262171071118[61] = 0;
   out_4271361262171071118[62] = 0;
   out_4271361262171071118[63] = 0;
   out_4271361262171071118[64] = 0;
   out_4271361262171071118[65] = 0;
   out_4271361262171071118[66] = 0;
   out_4271361262171071118[67] = 0;
   out_4271361262171071118[68] = 0;
   out_4271361262171071118[69] = 0;
   out_4271361262171071118[70] = 1.0;
   out_4271361262171071118[71] = 0;
   out_4271361262171071118[72] = 0;
   out_4271361262171071118[73] = 0;
   out_4271361262171071118[74] = 0;
   out_4271361262171071118[75] = 0;
   out_4271361262171071118[76] = 0;
   out_4271361262171071118[77] = 0;
   out_4271361262171071118[78] = 0;
   out_4271361262171071118[79] = 0;
   out_4271361262171071118[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_2312887418267850382) {
   out_2312887418267850382[0] = state[0];
   out_2312887418267850382[1] = state[1];
   out_2312887418267850382[2] = state[2];
   out_2312887418267850382[3] = state[3];
   out_2312887418267850382[4] = state[4];
   out_2312887418267850382[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_2312887418267850382[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_2312887418267850382[7] = state[7];
   out_2312887418267850382[8] = state[8];
}
void F_fun(double *state, double dt, double *out_3078199957203093130) {
   out_3078199957203093130[0] = 1;
   out_3078199957203093130[1] = 0;
   out_3078199957203093130[2] = 0;
   out_3078199957203093130[3] = 0;
   out_3078199957203093130[4] = 0;
   out_3078199957203093130[5] = 0;
   out_3078199957203093130[6] = 0;
   out_3078199957203093130[7] = 0;
   out_3078199957203093130[8] = 0;
   out_3078199957203093130[9] = 0;
   out_3078199957203093130[10] = 1;
   out_3078199957203093130[11] = 0;
   out_3078199957203093130[12] = 0;
   out_3078199957203093130[13] = 0;
   out_3078199957203093130[14] = 0;
   out_3078199957203093130[15] = 0;
   out_3078199957203093130[16] = 0;
   out_3078199957203093130[17] = 0;
   out_3078199957203093130[18] = 0;
   out_3078199957203093130[19] = 0;
   out_3078199957203093130[20] = 1;
   out_3078199957203093130[21] = 0;
   out_3078199957203093130[22] = 0;
   out_3078199957203093130[23] = 0;
   out_3078199957203093130[24] = 0;
   out_3078199957203093130[25] = 0;
   out_3078199957203093130[26] = 0;
   out_3078199957203093130[27] = 0;
   out_3078199957203093130[28] = 0;
   out_3078199957203093130[29] = 0;
   out_3078199957203093130[30] = 1;
   out_3078199957203093130[31] = 0;
   out_3078199957203093130[32] = 0;
   out_3078199957203093130[33] = 0;
   out_3078199957203093130[34] = 0;
   out_3078199957203093130[35] = 0;
   out_3078199957203093130[36] = 0;
   out_3078199957203093130[37] = 0;
   out_3078199957203093130[38] = 0;
   out_3078199957203093130[39] = 0;
   out_3078199957203093130[40] = 1;
   out_3078199957203093130[41] = 0;
   out_3078199957203093130[42] = 0;
   out_3078199957203093130[43] = 0;
   out_3078199957203093130[44] = 0;
   out_3078199957203093130[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_3078199957203093130[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_3078199957203093130[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_3078199957203093130[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_3078199957203093130[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_3078199957203093130[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_3078199957203093130[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_3078199957203093130[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_3078199957203093130[53] = -9.8000000000000007*dt;
   out_3078199957203093130[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_3078199957203093130[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_3078199957203093130[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3078199957203093130[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3078199957203093130[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_3078199957203093130[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_3078199957203093130[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_3078199957203093130[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3078199957203093130[62] = 0;
   out_3078199957203093130[63] = 0;
   out_3078199957203093130[64] = 0;
   out_3078199957203093130[65] = 0;
   out_3078199957203093130[66] = 0;
   out_3078199957203093130[67] = 0;
   out_3078199957203093130[68] = 0;
   out_3078199957203093130[69] = 0;
   out_3078199957203093130[70] = 1;
   out_3078199957203093130[71] = 0;
   out_3078199957203093130[72] = 0;
   out_3078199957203093130[73] = 0;
   out_3078199957203093130[74] = 0;
   out_3078199957203093130[75] = 0;
   out_3078199957203093130[76] = 0;
   out_3078199957203093130[77] = 0;
   out_3078199957203093130[78] = 0;
   out_3078199957203093130[79] = 0;
   out_3078199957203093130[80] = 1;
}
void h_25(double *state, double *unused, double *out_3020095161009376912) {
   out_3020095161009376912[0] = state[6];
}
void H_25(double *state, double *unused, double *out_8605363412927943953) {
   out_8605363412927943953[0] = 0;
   out_8605363412927943953[1] = 0;
   out_8605363412927943953[2] = 0;
   out_8605363412927943953[3] = 0;
   out_8605363412927943953[4] = 0;
   out_8605363412927943953[5] = 0;
   out_8605363412927943953[6] = 1;
   out_8605363412927943953[7] = 0;
   out_8605363412927943953[8] = 0;
}
void h_24(double *state, double *unused, double *out_1692855024534164423) {
   out_1692855024534164423[0] = state[4];
   out_1692855024534164423[1] = state[5];
}
void H_24(double *state, double *unused, double *out_6283455061979284527) {
   out_6283455061979284527[0] = 0;
   out_6283455061979284527[1] = 0;
   out_6283455061979284527[2] = 0;
   out_6283455061979284527[3] = 0;
   out_6283455061979284527[4] = 1;
   out_6283455061979284527[5] = 0;
   out_6283455061979284527[6] = 0;
   out_6283455061979284527[7] = 0;
   out_6283455061979284527[8] = 0;
   out_6283455061979284527[9] = 0;
   out_6283455061979284527[10] = 0;
   out_6283455061979284527[11] = 0;
   out_6283455061979284527[12] = 0;
   out_6283455061979284527[13] = 0;
   out_6283455061979284527[14] = 1;
   out_6283455061979284527[15] = 0;
   out_6283455061979284527[16] = 0;
   out_6283455061979284527[17] = 0;
}
void h_30(double *state, double *unused, double *out_2744901098724871023) {
   out_2744901098724871023[0] = state[4];
}
void H_30(double *state, double *unused, double *out_8476024465784703883) {
   out_8476024465784703883[0] = 0;
   out_8476024465784703883[1] = 0;
   out_8476024465784703883[2] = 0;
   out_8476024465784703883[3] = 0;
   out_8476024465784703883[4] = 1;
   out_8476024465784703883[5] = 0;
   out_8476024465784703883[6] = 0;
   out_8476024465784703883[7] = 0;
   out_8476024465784703883[8] = 0;
}
void h_26(double *state, double *unused, double *out_2217478898956422209) {
   out_2217478898956422209[0] = state[7];
}
void H_26(double *state, double *unused, double *out_4863860094053887729) {
   out_4863860094053887729[0] = 0;
   out_4863860094053887729[1] = 0;
   out_4863860094053887729[2] = 0;
   out_4863860094053887729[3] = 0;
   out_4863860094053887729[4] = 0;
   out_4863860094053887729[5] = 0;
   out_4863860094053887729[6] = 0;
   out_4863860094053887729[7] = 1;
   out_4863860094053887729[8] = 0;
}
void h_27(double *state, double *unused, double *out_6000448251431099530) {
   out_6000448251431099530[0] = state[3];
}
void H_27(double *state, double *unused, double *out_6301261153984278972) {
   out_6301261153984278972[0] = 0;
   out_6301261153984278972[1] = 0;
   out_6301261153984278972[2] = 0;
   out_6301261153984278972[3] = 1;
   out_6301261153984278972[4] = 0;
   out_6301261153984278972[5] = 0;
   out_6301261153984278972[6] = 0;
   out_6301261153984278972[7] = 0;
   out_6301261153984278972[8] = 0;
}
void h_29(double *state, double *unused, double *out_1762817005389572911) {
   out_1762817005389572911[0] = state[1];
}
void H_29(double *state, double *unused, double *out_8986255810099096067) {
   out_8986255810099096067[0] = 0;
   out_8986255810099096067[1] = 1;
   out_8986255810099096067[2] = 0;
   out_8986255810099096067[3] = 0;
   out_8986255810099096067[4] = 0;
   out_8986255810099096067[5] = 0;
   out_8986255810099096067[6] = 0;
   out_8986255810099096067[7] = 0;
   out_8986255810099096067[8] = 0;
}
void h_28(double *state, double *unused, double *out_398593265982749616) {
   out_398593265982749616[0] = state[0];
}
void H_28(double *state, double *unused, double *out_6551528698680054190) {
   out_6551528698680054190[0] = 1;
   out_6551528698680054190[1] = 0;
   out_6551528698680054190[2] = 0;
   out_6551528698680054190[3] = 0;
   out_6551528698680054190[4] = 0;
   out_6551528698680054190[5] = 0;
   out_6551528698680054190[6] = 0;
   out_6551528698680054190[7] = 0;
   out_6551528698680054190[8] = 0;
}
void h_31(double *state, double *unused, double *out_2862908492658247767) {
   out_2862908492658247767[0] = state[8];
}
void H_31(double *state, double *unused, double *out_8636009374804904381) {
   out_8636009374804904381[0] = 0;
   out_8636009374804904381[1] = 0;
   out_8636009374804904381[2] = 0;
   out_8636009374804904381[3] = 0;
   out_8636009374804904381[4] = 0;
   out_8636009374804904381[5] = 0;
   out_8636009374804904381[6] = 0;
   out_8636009374804904381[7] = 0;
   out_8636009374804904381[8] = 1;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_8856740152215769533) {
  err_fun(nom_x, delta_x, out_8856740152215769533);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8849079539949943851) {
  inv_err_fun(nom_x, true_x, out_8849079539949943851);
}
void car_H_mod_fun(double *state, double *out_4271361262171071118) {
  H_mod_fun(state, out_4271361262171071118);
}
void car_f_fun(double *state, double dt, double *out_2312887418267850382) {
  f_fun(state,  dt, out_2312887418267850382);
}
void car_F_fun(double *state, double dt, double *out_3078199957203093130) {
  F_fun(state,  dt, out_3078199957203093130);
}
void car_h_25(double *state, double *unused, double *out_3020095161009376912) {
  h_25(state, unused, out_3020095161009376912);
}
void car_H_25(double *state, double *unused, double *out_8605363412927943953) {
  H_25(state, unused, out_8605363412927943953);
}
void car_h_24(double *state, double *unused, double *out_1692855024534164423) {
  h_24(state, unused, out_1692855024534164423);
}
void car_H_24(double *state, double *unused, double *out_6283455061979284527) {
  H_24(state, unused, out_6283455061979284527);
}
void car_h_30(double *state, double *unused, double *out_2744901098724871023) {
  h_30(state, unused, out_2744901098724871023);
}
void car_H_30(double *state, double *unused, double *out_8476024465784703883) {
  H_30(state, unused, out_8476024465784703883);
}
void car_h_26(double *state, double *unused, double *out_2217478898956422209) {
  h_26(state, unused, out_2217478898956422209);
}
void car_H_26(double *state, double *unused, double *out_4863860094053887729) {
  H_26(state, unused, out_4863860094053887729);
}
void car_h_27(double *state, double *unused, double *out_6000448251431099530) {
  h_27(state, unused, out_6000448251431099530);
}
void car_H_27(double *state, double *unused, double *out_6301261153984278972) {
  H_27(state, unused, out_6301261153984278972);
}
void car_h_29(double *state, double *unused, double *out_1762817005389572911) {
  h_29(state, unused, out_1762817005389572911);
}
void car_H_29(double *state, double *unused, double *out_8986255810099096067) {
  H_29(state, unused, out_8986255810099096067);
}
void car_h_28(double *state, double *unused, double *out_398593265982749616) {
  h_28(state, unused, out_398593265982749616);
}
void car_H_28(double *state, double *unused, double *out_6551528698680054190) {
  H_28(state, unused, out_6551528698680054190);
}
void car_h_31(double *state, double *unused, double *out_2862908492658247767) {
  h_31(state, unused, out_2862908492658247767);
}
void car_H_31(double *state, double *unused, double *out_8636009374804904381) {
  H_31(state, unused, out_8636009374804904381);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_lib_init(car)
