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
void err_fun(double *nom_x, double *delta_x, double *out_5071898843746341962) {
   out_5071898843746341962[0] = delta_x[0] + nom_x[0];
   out_5071898843746341962[1] = delta_x[1] + nom_x[1];
   out_5071898843746341962[2] = delta_x[2] + nom_x[2];
   out_5071898843746341962[3] = delta_x[3] + nom_x[3];
   out_5071898843746341962[4] = delta_x[4] + nom_x[4];
   out_5071898843746341962[5] = delta_x[5] + nom_x[5];
   out_5071898843746341962[6] = delta_x[6] + nom_x[6];
   out_5071898843746341962[7] = delta_x[7] + nom_x[7];
   out_5071898843746341962[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_7429405783689188202) {
   out_7429405783689188202[0] = -nom_x[0] + true_x[0];
   out_7429405783689188202[1] = -nom_x[1] + true_x[1];
   out_7429405783689188202[2] = -nom_x[2] + true_x[2];
   out_7429405783689188202[3] = -nom_x[3] + true_x[3];
   out_7429405783689188202[4] = -nom_x[4] + true_x[4];
   out_7429405783689188202[5] = -nom_x[5] + true_x[5];
   out_7429405783689188202[6] = -nom_x[6] + true_x[6];
   out_7429405783689188202[7] = -nom_x[7] + true_x[7];
   out_7429405783689188202[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_5526837896722839594) {
   out_5526837896722839594[0] = 1.0;
   out_5526837896722839594[1] = 0;
   out_5526837896722839594[2] = 0;
   out_5526837896722839594[3] = 0;
   out_5526837896722839594[4] = 0;
   out_5526837896722839594[5] = 0;
   out_5526837896722839594[6] = 0;
   out_5526837896722839594[7] = 0;
   out_5526837896722839594[8] = 0;
   out_5526837896722839594[9] = 0;
   out_5526837896722839594[10] = 1.0;
   out_5526837896722839594[11] = 0;
   out_5526837896722839594[12] = 0;
   out_5526837896722839594[13] = 0;
   out_5526837896722839594[14] = 0;
   out_5526837896722839594[15] = 0;
   out_5526837896722839594[16] = 0;
   out_5526837896722839594[17] = 0;
   out_5526837896722839594[18] = 0;
   out_5526837896722839594[19] = 0;
   out_5526837896722839594[20] = 1.0;
   out_5526837896722839594[21] = 0;
   out_5526837896722839594[22] = 0;
   out_5526837896722839594[23] = 0;
   out_5526837896722839594[24] = 0;
   out_5526837896722839594[25] = 0;
   out_5526837896722839594[26] = 0;
   out_5526837896722839594[27] = 0;
   out_5526837896722839594[28] = 0;
   out_5526837896722839594[29] = 0;
   out_5526837896722839594[30] = 1.0;
   out_5526837896722839594[31] = 0;
   out_5526837896722839594[32] = 0;
   out_5526837896722839594[33] = 0;
   out_5526837896722839594[34] = 0;
   out_5526837896722839594[35] = 0;
   out_5526837896722839594[36] = 0;
   out_5526837896722839594[37] = 0;
   out_5526837896722839594[38] = 0;
   out_5526837896722839594[39] = 0;
   out_5526837896722839594[40] = 1.0;
   out_5526837896722839594[41] = 0;
   out_5526837896722839594[42] = 0;
   out_5526837896722839594[43] = 0;
   out_5526837896722839594[44] = 0;
   out_5526837896722839594[45] = 0;
   out_5526837896722839594[46] = 0;
   out_5526837896722839594[47] = 0;
   out_5526837896722839594[48] = 0;
   out_5526837896722839594[49] = 0;
   out_5526837896722839594[50] = 1.0;
   out_5526837896722839594[51] = 0;
   out_5526837896722839594[52] = 0;
   out_5526837896722839594[53] = 0;
   out_5526837896722839594[54] = 0;
   out_5526837896722839594[55] = 0;
   out_5526837896722839594[56] = 0;
   out_5526837896722839594[57] = 0;
   out_5526837896722839594[58] = 0;
   out_5526837896722839594[59] = 0;
   out_5526837896722839594[60] = 1.0;
   out_5526837896722839594[61] = 0;
   out_5526837896722839594[62] = 0;
   out_5526837896722839594[63] = 0;
   out_5526837896722839594[64] = 0;
   out_5526837896722839594[65] = 0;
   out_5526837896722839594[66] = 0;
   out_5526837896722839594[67] = 0;
   out_5526837896722839594[68] = 0;
   out_5526837896722839594[69] = 0;
   out_5526837896722839594[70] = 1.0;
   out_5526837896722839594[71] = 0;
   out_5526837896722839594[72] = 0;
   out_5526837896722839594[73] = 0;
   out_5526837896722839594[74] = 0;
   out_5526837896722839594[75] = 0;
   out_5526837896722839594[76] = 0;
   out_5526837896722839594[77] = 0;
   out_5526837896722839594[78] = 0;
   out_5526837896722839594[79] = 0;
   out_5526837896722839594[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_4137341935110265011) {
   out_4137341935110265011[0] = state[0];
   out_4137341935110265011[1] = state[1];
   out_4137341935110265011[2] = state[2];
   out_4137341935110265011[3] = state[3];
   out_4137341935110265011[4] = state[4];
   out_4137341935110265011[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_4137341935110265011[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_4137341935110265011[7] = state[7];
   out_4137341935110265011[8] = state[8];
}
void F_fun(double *state, double dt, double *out_4749271280852372652) {
   out_4749271280852372652[0] = 1;
   out_4749271280852372652[1] = 0;
   out_4749271280852372652[2] = 0;
   out_4749271280852372652[3] = 0;
   out_4749271280852372652[4] = 0;
   out_4749271280852372652[5] = 0;
   out_4749271280852372652[6] = 0;
   out_4749271280852372652[7] = 0;
   out_4749271280852372652[8] = 0;
   out_4749271280852372652[9] = 0;
   out_4749271280852372652[10] = 1;
   out_4749271280852372652[11] = 0;
   out_4749271280852372652[12] = 0;
   out_4749271280852372652[13] = 0;
   out_4749271280852372652[14] = 0;
   out_4749271280852372652[15] = 0;
   out_4749271280852372652[16] = 0;
   out_4749271280852372652[17] = 0;
   out_4749271280852372652[18] = 0;
   out_4749271280852372652[19] = 0;
   out_4749271280852372652[20] = 1;
   out_4749271280852372652[21] = 0;
   out_4749271280852372652[22] = 0;
   out_4749271280852372652[23] = 0;
   out_4749271280852372652[24] = 0;
   out_4749271280852372652[25] = 0;
   out_4749271280852372652[26] = 0;
   out_4749271280852372652[27] = 0;
   out_4749271280852372652[28] = 0;
   out_4749271280852372652[29] = 0;
   out_4749271280852372652[30] = 1;
   out_4749271280852372652[31] = 0;
   out_4749271280852372652[32] = 0;
   out_4749271280852372652[33] = 0;
   out_4749271280852372652[34] = 0;
   out_4749271280852372652[35] = 0;
   out_4749271280852372652[36] = 0;
   out_4749271280852372652[37] = 0;
   out_4749271280852372652[38] = 0;
   out_4749271280852372652[39] = 0;
   out_4749271280852372652[40] = 1;
   out_4749271280852372652[41] = 0;
   out_4749271280852372652[42] = 0;
   out_4749271280852372652[43] = 0;
   out_4749271280852372652[44] = 0;
   out_4749271280852372652[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_4749271280852372652[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_4749271280852372652[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_4749271280852372652[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_4749271280852372652[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_4749271280852372652[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_4749271280852372652[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_4749271280852372652[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_4749271280852372652[53] = -9.8000000000000007*dt;
   out_4749271280852372652[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_4749271280852372652[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_4749271280852372652[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4749271280852372652[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4749271280852372652[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_4749271280852372652[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_4749271280852372652[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_4749271280852372652[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4749271280852372652[62] = 0;
   out_4749271280852372652[63] = 0;
   out_4749271280852372652[64] = 0;
   out_4749271280852372652[65] = 0;
   out_4749271280852372652[66] = 0;
   out_4749271280852372652[67] = 0;
   out_4749271280852372652[68] = 0;
   out_4749271280852372652[69] = 0;
   out_4749271280852372652[70] = 1;
   out_4749271280852372652[71] = 0;
   out_4749271280852372652[72] = 0;
   out_4749271280852372652[73] = 0;
   out_4749271280852372652[74] = 0;
   out_4749271280852372652[75] = 0;
   out_4749271280852372652[76] = 0;
   out_4749271280852372652[77] = 0;
   out_4749271280852372652[78] = 0;
   out_4749271280852372652[79] = 0;
   out_4749271280852372652[80] = 1;
}
void h_25(double *state, double *unused, double *out_5245866700509374347) {
   out_5245866700509374347[0] = state[6];
}
void H_25(double *state, double *unused, double *out_211849249113722097) {
   out_211849249113722097[0] = 0;
   out_211849249113722097[1] = 0;
   out_211849249113722097[2] = 0;
   out_211849249113722097[3] = 0;
   out_211849249113722097[4] = 0;
   out_211849249113722097[5] = 0;
   out_211849249113722097[6] = 1;
   out_211849249113722097[7] = 0;
   out_211849249113722097[8] = 0;
}
void h_24(double *state, double *unused, double *out_1359151821500781896) {
   out_1359151821500781896[0] = state[4];
   out_1359151821500781896[1] = state[5];
}
void H_24(double *state, double *unused, double *out_6787421055705240198) {
   out_6787421055705240198[0] = 0;
   out_6787421055705240198[1] = 0;
   out_6787421055705240198[2] = 0;
   out_6787421055705240198[3] = 0;
   out_6787421055705240198[4] = 1;
   out_6787421055705240198[5] = 0;
   out_6787421055705240198[6] = 0;
   out_6787421055705240198[7] = 0;
   out_6787421055705240198[8] = 0;
   out_6787421055705240198[9] = 0;
   out_6787421055705240198[10] = 0;
   out_6787421055705240198[11] = 0;
   out_6787421055705240198[12] = 0;
   out_6787421055705240198[13] = 0;
   out_6787421055705240198[14] = 1;
   out_6787421055705240198[15] = 0;
   out_6787421055705240198[16] = 0;
   out_6787421055705240198[17] = 0;
}
void h_30(double *state, double *unused, double *out_1608417172255351997) {
   out_1608417172255351997[0] = state[4];
}
void H_30(double *state, double *unused, double *out_7128539590605338852) {
   out_7128539590605338852[0] = 0;
   out_7128539590605338852[1] = 0;
   out_7128539590605338852[2] = 0;
   out_7128539590605338852[3] = 0;
   out_7128539590605338852[4] = 1;
   out_7128539590605338852[5] = 0;
   out_7128539590605338852[6] = 0;
   out_7128539590605338852[7] = 0;
   out_7128539590605338852[8] = 0;
}
void h_26(double *state, double *unused, double *out_1428368879188980688) {
   out_1428368879188980688[0] = state[7];
}
void H_26(double *state, double *unused, double *out_3529654069760334127) {
   out_3529654069760334127[0] = 0;
   out_3529654069760334127[1] = 0;
   out_3529654069760334127[2] = 0;
   out_3529654069760334127[3] = 0;
   out_3529654069760334127[4] = 0;
   out_3529654069760334127[5] = 0;
   out_3529654069760334127[6] = 0;
   out_3529654069760334127[7] = 1;
   out_3529654069760334127[8] = 0;
}
void h_27(double *state, double *unused, double *out_396863170571582488) {
   out_396863170571582488[0] = state[3];
}
void H_27(double *state, double *unused, double *out_4953776278804913941) {
   out_4953776278804913941[0] = 0;
   out_4953776278804913941[1] = 0;
   out_4953776278804913941[2] = 0;
   out_4953776278804913941[3] = 1;
   out_4953776278804913941[4] = 0;
   out_4953776278804913941[5] = 0;
   out_4953776278804913941[6] = 0;
   out_4953776278804913941[7] = 0;
   out_4953776278804913941[8] = 0;
}
void h_29(double *state, double *unused, double *out_3393256095405493648) {
   out_3393256095405493648[0] = state[1];
}
void H_29(double *state, double *unused, double *out_3240413551935362908) {
   out_3240413551935362908[0] = 0;
   out_3240413551935362908[1] = 1;
   out_3240413551935362908[2] = 0;
   out_3240413551935362908[3] = 0;
   out_3240413551935362908[4] = 0;
   out_3240413551935362908[5] = 0;
   out_3240413551935362908[6] = 0;
   out_3240413551935362908[7] = 0;
   out_3240413551935362908[8] = 0;
}
void h_28(double *state, double *unused, double *out_4822224085869814021) {
   out_4822224085869814021[0] = state[0];
}
void H_28(double *state, double *unused, double *out_1841985465134167666) {
   out_1841985465134167666[0] = 1;
   out_1841985465134167666[1] = 0;
   out_1841985465134167666[2] = 0;
   out_1841985465134167666[3] = 0;
   out_1841985465134167666[4] = 0;
   out_1841985465134167666[5] = 0;
   out_1841985465134167666[6] = 0;
   out_1841985465134167666[7] = 0;
   out_1841985465134167666[8] = 0;
}
void h_31(double *state, double *unused, double *out_5521060762793880236) {
   out_5521060762793880236[0] = state[8];
}
void H_31(double *state, double *unused, double *out_242495210990682525) {
   out_242495210990682525[0] = 0;
   out_242495210990682525[1] = 0;
   out_242495210990682525[2] = 0;
   out_242495210990682525[3] = 0;
   out_242495210990682525[4] = 0;
   out_242495210990682525[5] = 0;
   out_242495210990682525[6] = 0;
   out_242495210990682525[7] = 0;
   out_242495210990682525[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_5071898843746341962) {
  err_fun(nom_x, delta_x, out_5071898843746341962);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_7429405783689188202) {
  inv_err_fun(nom_x, true_x, out_7429405783689188202);
}
void car_H_mod_fun(double *state, double *out_5526837896722839594) {
  H_mod_fun(state, out_5526837896722839594);
}
void car_f_fun(double *state, double dt, double *out_4137341935110265011) {
  f_fun(state,  dt, out_4137341935110265011);
}
void car_F_fun(double *state, double dt, double *out_4749271280852372652) {
  F_fun(state,  dt, out_4749271280852372652);
}
void car_h_25(double *state, double *unused, double *out_5245866700509374347) {
  h_25(state, unused, out_5245866700509374347);
}
void car_H_25(double *state, double *unused, double *out_211849249113722097) {
  H_25(state, unused, out_211849249113722097);
}
void car_h_24(double *state, double *unused, double *out_1359151821500781896) {
  h_24(state, unused, out_1359151821500781896);
}
void car_H_24(double *state, double *unused, double *out_6787421055705240198) {
  H_24(state, unused, out_6787421055705240198);
}
void car_h_30(double *state, double *unused, double *out_1608417172255351997) {
  h_30(state, unused, out_1608417172255351997);
}
void car_H_30(double *state, double *unused, double *out_7128539590605338852) {
  H_30(state, unused, out_7128539590605338852);
}
void car_h_26(double *state, double *unused, double *out_1428368879188980688) {
  h_26(state, unused, out_1428368879188980688);
}
void car_H_26(double *state, double *unused, double *out_3529654069760334127) {
  H_26(state, unused, out_3529654069760334127);
}
void car_h_27(double *state, double *unused, double *out_396863170571582488) {
  h_27(state, unused, out_396863170571582488);
}
void car_H_27(double *state, double *unused, double *out_4953776278804913941) {
  H_27(state, unused, out_4953776278804913941);
}
void car_h_29(double *state, double *unused, double *out_3393256095405493648) {
  h_29(state, unused, out_3393256095405493648);
}
void car_H_29(double *state, double *unused, double *out_3240413551935362908) {
  H_29(state, unused, out_3240413551935362908);
}
void car_h_28(double *state, double *unused, double *out_4822224085869814021) {
  h_28(state, unused, out_4822224085869814021);
}
void car_H_28(double *state, double *unused, double *out_1841985465134167666) {
  H_28(state, unused, out_1841985465134167666);
}
void car_h_31(double *state, double *unused, double *out_5521060762793880236) {
  h_31(state, unused, out_5521060762793880236);
}
void car_H_31(double *state, double *unused, double *out_242495210990682525) {
  H_31(state, unused, out_242495210990682525);
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
