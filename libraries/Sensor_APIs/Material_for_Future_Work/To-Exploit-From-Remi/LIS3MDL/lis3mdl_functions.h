#pragma once // means : will be included one time

#include "lis3mdl.h"

struct matrice {
  float x;
  float y;
  float z;
};

struct matrice * lis3mdl_get_mangneto(void);
float lis3mdl_get_temperature(void);

