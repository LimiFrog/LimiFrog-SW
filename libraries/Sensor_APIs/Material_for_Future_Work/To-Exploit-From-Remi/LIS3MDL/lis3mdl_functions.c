#include "lis3mdl_functions.h"
#include "lis3mdl.h"

void lis3mdl_temperature_init(void);
void lis3mdl_mangneto_init(void);

static char Message_Buffer[100];


static long complement_2_16( unsigned short n)
{
  if ( n & 0x8000)
    return -1 * (65536 - n);
  else
    return n;
}

float convert_temp( short t)
{
    float dec = t / 255.0;
    float temp = t >> 8;
    
    return  25.0 + temp + dec/10;
}

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
float lis3mdl_get_temperature(void)
{
  lis3mdl_set_operating_mode(SINGLE_CONVERSION_MODE_E);
  
  // 120 milliseoncde
  osDelay(120);
    
  return convert_temp(complement_2_16((lis3mdl_get_temperature_data_lsb() + 256 * lis3mdl_get_temperature_data_msb()))); 
}

void lis3mdl_temperature_init(void)
{
  char Message_Buffer[100];
  
  sprintf(Message_Buffer,"lis3mdl_temperature_init");
  Sendlog(Message_Buffer);    
  
  lis3mdl_set_temperature_sensor(TEMPERATURE_SENSOR_ENABLE_E);
}

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
struct matrice last_magneto_measure;

struct matrice * lis3mdl_get_mangneto(void)
{
  if (lis3mdl_get_data_ready())
    {
      last_magneto_measure.x = complement_2_16(lis3mdl_get_magneto_x_low() + 256 * lis3mdl_get_magneto_x_high());
      last_magneto_measure.y = complement_2_16(lis3mdl_get_magneto_y_low() + 256 * lis3mdl_get_magneto_y_high());
      last_magneto_measure.z = complement_2_16(lis3mdl_get_magneto_z_low() + 256 * lis3mdl_get_magneto_z_high());
      return &last_magneto_measure;
    }
  else
    {
      return 0; 
    }
}

void lis3mdl_mangneto_init(void)
{
}

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
void lis3mdl_mode()
{
  lis3mdl_set_fast_data_rate(FAST_MODE_DISABLE_E);
  lis3mdl_set_data_rate(DATA_RATE_10_HZ_E);
  lis3mdl_set_operating_mode(SINGLE_CONVERSION_MODE_E);

  lis3mdl_temperature_init();
  lis3mdl_mangneto_init();
}


