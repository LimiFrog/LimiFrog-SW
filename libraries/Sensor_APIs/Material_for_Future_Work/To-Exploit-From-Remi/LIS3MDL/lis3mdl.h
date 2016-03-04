/****************************************************************************
 * File : c:/Lisp/Production/sensors_st/sensors_st_lis3mdl/Linux/lis3mdl.h
 * 
 *
 * Generated on the 03/11/2015 19:31 by the 'super-cool' code generator 
 *
 * Generator written in Common Lisp, created by  Rémi PRUD'HOMME 
 * with the help of : 
 *
 ***************************************************************************
 *  Copyright STMicroelectronics  2015
 *
 *
 ***************************************************************************/

// This file is generated. Don't modify it 

#ifndef C__LISP_PRODUCTION_SENSORS_ST_SENSORS_ST_LIS3MDL_LINUX_LIS3MDL_H
#define C__LISP_PRODUCTION_SENSORS_ST_SENSORS_ST_LIS3MDL_LINUX_LIS3MDL_H


#ifdef __cplusplus
extern "C" {
#endif
#include "lis3mdl_types.h"

unsigned char lis3mdl_get_who_iam();
unsigned char lis3mdl_set_self_test( enum self_test_enable param );
unsigned char lis3mdl_get_self_test();
unsigned char lis3mdl_set_fast_data_rate( enum fast_mode_enable param );
unsigned char lis3mdl_get_fast_data_rate();
unsigned char lis3mdl_set_data_rate( enum data_rate param );
unsigned char lis3mdl_get_data_rate();
unsigned char lis3mdl_set_operative_mode_selection( enum operative_mode_selection param );
unsigned char lis3mdl_get_operative_mode_selection();
unsigned char lis3mdl_set_temperature_sensor( enum temperature_sensor_enable param );
unsigned char lis3mdl_get_temperature_sensor();
unsigned char lis3mdl_set_software_reset( enum software_reset_enable param );
unsigned char lis3mdl_get_software_reset();
unsigned char lis3mdl_set_reboot_memory_content( enum reboot_memory_content_enable param );
unsigned char lis3mdl_get_reboot_memory_content();
unsigned char lis3mdl_set_full_scale( enum full_scale param );
unsigned char lis3mdl_get_full_scale();
unsigned char lis3mdl_set_operating_mode( enum operating_mode param );
unsigned char lis3mdl_get_operating_mode();
unsigned char lis3mdl_set_spi_mode( enum spi_mode param );
unsigned char lis3mdl_get_spi_mode();
unsigned char lis3mdl_set_big_endian_mode( enum big_endian_mode param );
unsigned char lis3mdl_get_big_endian_mode();
unsigned char lis3mdl_set_axisz_mod( enum axisz_mod param );
unsigned char lis3mdl_get_axisz_mod();
unsigned char lis3mdl_set_update_data_mode( enum update_data_mode param );
unsigned char lis3mdl_get_update_data_mode();
unsigned char lis3mdl_set_fast_read( enum fast_read_enable param );
unsigned char lis3mdl_get_fast_read();
unsigned char lis3mdl_get_data_x_ready();
unsigned char lis3mdl_get_data_y_ready();
unsigned char lis3mdl_get_data_z_ready();
unsigned char lis3mdl_get_data_ready();
unsigned char lis3mdl_get_data_x_overrun();
unsigned char lis3mdl_get_data_y_overrun();
unsigned char lis3mdl_get_data_z_overrun();
unsigned char lis3mdl_get_data_overrun();
unsigned char lis3mdl_get_magneto_x_low();
unsigned char lis3mdl_get_magneto_x_high();
unsigned char lis3mdl_get_magneto_y_low();
unsigned char lis3mdl_get_magneto_y_high();
unsigned char lis3mdl_get_magneto_z_low();
unsigned char lis3mdl_get_magneto_z_high();
unsigned char lis3mdl_get_temperature_data_lsb();
unsigned char lis3mdl_get_temperature_data_msb();
unsigned char lis3mdl_set_interrupt_pin( enum interrupt_pin_enable param );
unsigned char lis3mdl_get_interrupt_pin();
unsigned char lis3mdl_set_latch_interrupt_request( enum latch_interrupt_request param );
unsigned char lis3mdl_get_latch_interrupt_request();
unsigned char lis3mdl_set_interrupt( enum interrupt_enable param );
unsigned char lis3mdl_get_interrupt();
unsigned char lis3mdl_set_interrupt_z_axise( enum interrupt_z_axise_enable param );
unsigned char lis3mdl_get_interrupt_z_axise();
unsigned char lis3mdl_set_interrupt_y_axise( enum interrupt_y_axise_enable param );
unsigned char lis3mdl_get_interrupt_y_axise();
unsigned char lis3mdl_set_interrupt_x_axise( enum interrupt_x_axise_enable param );
unsigned char lis3mdl_get_interrupt_x_axise();
unsigned char lis3mdl_set_interrupt_event( enum interrupt_event param );
unsigned char lis3mdl_get_interrupt_event();
unsigned char lis3mdl_set_internal_overflow_value( enum internal_overflow_value param );
unsigned char lis3mdl_get_internal_overflow_value();
unsigned char lis3mdl_get_threshold_negative_z();
unsigned char lis3mdl_get_threshold_negative_y();
unsigned char lis3mdl_get_threshold_negative_x();
unsigned char lis3mdl_get_threshold_positive_z();
unsigned char lis3mdl_get_threshold_positive_y();
unsigned char lis3mdl_get_threshold_positive_x();
unsigned char lis3mdl_get_interrupt_threshold_lsb();
unsigned char lis3mdl_get_interrupt_threshol_m_lsb();


#ifdef __cplusplus
}
#endif

#endif
