/****************************************************************************
 * File : c:/Lisp/Production/sensors_st/sensors_st_lps25h/Linux/lps25h.h
 * 
 *
 * Generated on the 08/10/2015 14:31 by the 'super-cool' code generator 
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

#ifndef C__LISP_PRODUCTION_SENSORS_ST_SENSORS_ST_LPS25H_LINUX_LPS25H_H
#define C__LISP_PRODUCTION_SENSORS_ST_SENSORS_ST_LPS25H_LINUX_LPS25H_H


#ifdef __cplusplus
extern "C" {
#endif
#include "lps25h_types.h"

unsigned char lps25h_set_reference_register_x_lsb( unsigned char param );
unsigned char lps25h_get_reference_register_x_lsb();
unsigned char lps25h_set_reference_register_lsb( unsigned char param );
unsigned char lps25h_get_reference_register_lsb();
unsigned char lps25h_set_reference_register_msb( unsigned char param );
unsigned char lps25h_get_reference_register_msb();
unsigned char lps25h_get_who_iam();
unsigned char lps25h_set_averaged_temperature_samples( enum temperature_average param );
unsigned char lps25h_get_averaged_temperature_samples();
unsigned char lps25h_set_averaged_pressure_samples( enum pressure_average param );
unsigned char lps25h_get_averaged_pressure_samples();
unsigned char lps25h_set_spi_wire( enum spi_wire param );
unsigned char lps25h_get_spi_wire();
unsigned char lps25h_set_reset_auto_zerofunction( enum reset_auto_zero param );
unsigned char lps25h_get_reset_auto_zerofunction();
unsigned char lps25h_set_continuous_update( enum continuous_update_enable param );
unsigned char lps25h_get_continuous_update();
unsigned char lps25h_set_interrupt_circuit( enum interrupt_circuit_enable param );
unsigned char lps25h_get_interrupt_circuit();
unsigned char lps25h_set_data_rate( enum data_rate param );
unsigned char lps25h_get_data_rate();
unsigned char lps25h_set_active_mode( enum active_mode_enable param );
unsigned char lps25h_get_active_mode();
unsigned char lps25h_set_one_shot( enum one_shot_enable param );
unsigned char lps25h_get_one_shot();
unsigned char lps25h_set_autozero( enum autozero_enable param );
unsigned char lps25h_get_autozero();
unsigned char lps25h_set_software_reset( enum software_reset_enable param );
unsigned char lps25h_get_software_reset();
unsigned char lps25h_set_comm( enum comm_mode param );
unsigned char lps25h_get_comm();
unsigned char lps25h_set_ord_decimatione( enum ord_decimation_enable param );
unsigned char lps25h_get_ord_decimatione();
unsigned char lps25h_set_fifo_water_mark( enum fifo_water_mark_enable param );
unsigned char lps25h_get_fifo_water_mark();
unsigned char lps25h_set_fifo( enum fifo_enable param );
unsigned char lps25h_get_fifo();
unsigned char lps25h_set_reboot_memory_content( enum reboot_memory_content_enable param );
unsigned char lps25h_get_reboot_memory_content();
unsigned char lps25h_set_data_signal_on_int_pad( enum data_signal_on_int param );
unsigned char lps25h_get_data_signal_on_int_pad();
unsigned char lps25h_set_open_drain_selection( enum open_drain_enable param );
unsigned char lps25h_get_open_drain_selection();
unsigned char lps25h_set_interrupt_level( enum level param );
unsigned char lps25h_get_interrupt_level();
unsigned char lps25h_set_data_ready_signal( enum data_ready_enable param );
unsigned char lps25h_get_data_ready_signal();
unsigned char lps25h_set_overrun_signal( enum overrunl_enable param );
unsigned char lps25h_get_overrun_signal();
unsigned char lps25h_set_watermark_signal( enum watermark_enable param );
unsigned char lps25h_get_watermark_signal();
unsigned char lps25h_set_empty_signal( enum empty_signal_enable param );
unsigned char lps25h_get_empty_signal();
unsigned char lps25h_set_pressure_high_event( enum pressure_high_event_enable param );
unsigned char lps25h_get_pressure_high_event();
unsigned char lps25h_set_pressure_low_event( enum pressure_low_event_enable param );
unsigned char lps25h_get_pressure_low_event();
unsigned char lps25h_set_interrupt_request_event( enum latch_interrupt param );
unsigned char lps25h_get_interrupt_request_event();
unsigned char lps25h_get_differential_pressure_high();
unsigned char lps25h_get_differential_pressure_low();
unsigned char lps25h_get_interrupt_active();
unsigned char lps25h_get_temperature_data_available();
unsigned char lps25h_get_pressure_data_available();
unsigned char lps25h_get_temperature_data_overrun();
unsigned char lps25h_get_pressure_data_overrun();
unsigned char lps25h_get_pressure_data_x_lsb();
unsigned char lps25h_get_pressure_data_lsb();
unsigned char lps25h_get_pressure_data_msb();
unsigned char lps25h_get_temperature_data_msb();
unsigned char lps25h_get_temperature_data_lsb();
unsigned char lps25h_set_fifo_threshold_level( enum fifo_threshold param );
unsigned char lps25h_get_fifo_threshold_level();
unsigned char lps25h_set_fifo_mode_selection( enum fifo_mode_selection param );
unsigned char lps25h_get_fifo_mode_selection();
unsigned char lps25h_get_fifo_status();
unsigned char lps25h_get_threshold_pressure_lsb();
unsigned char lps25h_get_threshold_pressure_msb();
unsigned char lps25h_get_final_threshold_pressure_lsb();
unsigned char lps25h_get_final_threshold_pressure_msb();


#ifdef __cplusplus
}
#endif

#endif
