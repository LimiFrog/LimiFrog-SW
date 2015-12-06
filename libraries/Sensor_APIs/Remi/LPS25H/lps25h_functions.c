#include "lps25h.h"
#include "../Console.h"
#include <stdio.h>

void lps25h_initialization();

//(defun compl(n)
// (if (logbitp 7 n)
//   (* -1 (- 256 n))
//     n))


float reference_pressure;

static long complement_2_16( unsigned short n)
{
  if ( n & 0x8000)
    return -1 * (65536 - n);
  else
    return n;
}

static long complement_2_24( unsigned long n)
{
  if ( n & 0x800000)
    return -1 * (16777216 - n);
  else
    return n;
}

void lps25h_i2c_init()
{
  lps25h_initialization();
}

void lps25h_initialization()
{
  lps25h_set_active_mode(ACTIVE_MODE_ENABLE_E);
  lps25h_set_one_shot(ONE_SHOT_ENABLE_E);

//  lps25h_set_data_rate(DATA_RATE_7HZ_E);

  lps25h_set_averaged_temperature_samples(TEMPERATURE_AVERAGE_64_E);
  lps25h_set_averaged_pressure_samples(PRESSURE_AVERAGE_32_E);
 
  unsigned long code = lps25h_get_reference_register_x_lsb() +  (lps25h_get_reference_register_lsb() << 8)
    + (lps25h_get_reference_register_msb() << 16);

  reference_pressure = code / 4096.0;
}

float lps25h_get_temperature()
{
  lps25h_set_data_rate(ONE_SHOT_E);

  while( !lps25h_get_pressure_data_available())
    ;

  unsigned short code = (lps25h_get_temperature_data_lsb() << 8)  + lps25h_get_temperature_data_msb();
  short temperature  = complement_2_16(code);
  float tt =  42.5 + (temperature/ 480.0);

//  sprintf(TxBuffer,"Mesure temperature code = %d, code2 %d, %f", temperature, code, tt);
//  Sendlog(TxBuffer); 
  return tt;
}


float lps25h_get_pressure()
{
  lps25h_set_data_rate(ONE_SHOT_E);
  
  while( !lps25h_get_pressure_data_available())
    ;
  
  unsigned long code = lps25h_get_pressure_data_x_lsb() +  (lps25h_get_pressure_data_lsb() << 8)
    + (lps25h_get_pressure_data_msb() << 16);

  float pp = complement_2_24(code) / 4096.0;
  
  return pp;
}


