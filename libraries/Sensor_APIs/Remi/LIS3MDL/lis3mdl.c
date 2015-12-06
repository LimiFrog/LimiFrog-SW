/****************************************************************************
 * File : c:/Lisp/Production/sensors_st/sensors_st_lis3mdl/Linux/lis3mdl.c
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

#ifndef C__LISP_PRODUCTION_SENSORS_ST_SENSORS_ST_LIS3MDL_LINUX_LIS3MDL_C
#define C__LISP_PRODUCTION_SENSORS_ST_SENSORS_ST_LIS3MDL_LINUX_LIS3MDL_C


#ifdef __cplusplus
extern "C" {
#endif
#include "lis3mdl.h"

extern unsigned char lis3mdl_read_register( unsigned short register_address);
extern void lis3mdl_write_register( unsigned short register_address, unsigned char data );


/***************************************************************************
 *
 * Function : lis3mdl_get_who_iam
 *
 * RET  : Return the value of register 0xWhoIam
 *
 * Notes : From register 0xF, bits 7:0
 *
 **************************************************************************/
unsigned char lis3mdl_get_who_iam()
  {
    unsigned char value;


    /* 
     * Who I am register, ID register 
     */ 
    value = lis3mdl_read_register(WHO_IAM_REG);
    return value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_set_self_test
 *
 * IN   : param, a value to write to the regiter ControlRegister1
 * OUT  : 
 *
 * RET  : Return the value of register 0xControlRegister1
 *
 * Notes : From register 0x20, bits 0:0
 *
 **************************************************************************/
unsigned char lis3mdl_set_self_test( enum self_test_enable param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lis3mdl_read_register(CONTROL_REGISTER_1_REG);

    /* 
     * ST Self-test enable.0: self-test disabled; 1: self-test 
     * enabled 
     */ 
    switch( param ){
        case SELF_TEST_ENABLE_E: 
           value = old_value | SELF_TEST_MASK; 
           break;
        case SELF_TEST_DISABLE_E: 
           value = old_value & ~ SELF_TEST_MASK;
           break;
    }
  

    if (value != old_value)
        lis3mdl_write_register(CONTROL_REGISTER_1_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_get_self_test
 *
 * RET  : Return the value of register 0xControlRegister1
 *
 * Notes : From register 0x20, bits 0:0
 *
 **************************************************************************/
unsigned char lis3mdl_get_self_test()
  {
    unsigned char value;


    /* 
     * ST Self-test enable.0: self-test disabled; 1: self-test 
     * enabled 
     */ 
    value = (lis3mdl_read_register(CONTROL_REGISTER_1_REG) & SELF_TEST_MASK);
    return value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_set_fast_data_rate
 *
 * IN   : param, a value to write to the regiter ControlRegister1
 * OUT  : 
 *
 * RET  : Return the value of register 0xControlRegister1
 *
 * Notes : From register 0x20, bits 1:1
 *
 **************************************************************************/
unsigned char lis3mdl_set_fast_data_rate( enum fast_mode_enable param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lis3mdl_read_register(CONTROL_REGISTER_1_REG);

    /* 
     * FAST_ODR enables data rates higher than 80 Hz 
     */ 
    switch( param ){
        case FAST_MODE_ENABLE_E: 
           value = old_value | FAST_DATA_RATE_MASK; 
           break;
        case FAST_MODE_DISABLE_E: 
           value = old_value & ~ FAST_DATA_RATE_MASK;
           break;
    }
  

    if (value != old_value)
        lis3mdl_write_register(CONTROL_REGISTER_1_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_get_fast_data_rate
 *
 * RET  : Return the value of register 0xControlRegister1
 *
 * Notes : From register 0x20, bits 1:1
 *
 **************************************************************************/
unsigned char lis3mdl_get_fast_data_rate()
  {
    unsigned char value;


    /* 
     * FAST_ODR enables data rates higher than 80 Hz 
     */ 
    value = (lis3mdl_read_register(CONTROL_REGISTER_1_REG) & FAST_DATA_RATE_MASK) >> 1;
    return value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_set_data_rate
 *
 * IN   : param, a value to write to the regiter ControlRegister1
 * OUT  : 
 *
 * RET  : Return the value of register 0xControlRegister1
 *
 * Notes : From register 0x20, bits 4:2
 *
 **************************************************************************/
unsigned char lis3mdl_set_data_rate( enum data_rate param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lis3mdl_read_register(CONTROL_REGISTER_1_REG);

    /* 
     * output data rate selection 
     */ 
  

     value =  old_value & ~DATA_RATE_MASK ;

    switch(  param ){

           case DATA_RATE_0_625_HZ_E:
                value  = value  | (DATA_RATE_0_625_HZ << 0x2);
                break;
           case DATA_RATE_1_25_HZ_E:
                value  = value  | (DATA_RATE_1_25_HZ << 0x2);
                break;
           case DATA_RATE_2_5_HZ_E:
                value  = value  | (DATA_RATE_2_5_HZ << 0x2);
                break;
           case DATA_RATE_5_HZ_E:
                value  = value  | (DATA_RATE_5_HZ << 0x2);
                break;
           case DATA_RATE_10_HZ_E:
                value  = value  | (DATA_RATE_10_HZ << 0x2);
                break;
           case DATA_RATE_20_HZ_E:
                value  = value  | (DATA_RATE_20_HZ << 0x2);
                break;
           case DATA_RATE_40_HZ_E:
                value  = value  | (DATA_RATE_40_HZ << 0x2);
                break;
           case DATA_RATE1_80_HZ_E:
                value  = value  | (DATA_RATE1_80_HZ << 0x2);
                break;
    }
  

    if (value != old_value)
        lis3mdl_write_register(CONTROL_REGISTER_1_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_get_data_rate
 *
 * RET  : Return the value of register 0xControlRegister1
 *
 * Notes : From register 0x20, bits 4:2
 *
 **************************************************************************/
unsigned char lis3mdl_get_data_rate()
  {
    unsigned char value;


    /* 
     * output data rate selection 
     */ 
    value = (lis3mdl_read_register(CONTROL_REGISTER_1_REG) & DATA_RATE_MASK) >> 2;
    return value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_set_operative_mode_selection
 *
 * IN   : param, a value to write to the regiter ControlRegister1
 * OUT  : 
 *
 * RET  : Return the value of register 0xControlRegister1
 *
 * Notes : From register 0x20, bits 6:5
 *
 **************************************************************************/
unsigned char lis3mdl_set_operative_mode_selection( enum operative_mode_selection param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lis3mdl_read_register(CONTROL_REGISTER_1_REG);

    /* 
     * X and Y axes operative mode selection 
     */ 
    switch( param ){
        case OPERATIVE_MODE_SELECT_E: 
           value = old_value | OPERATIVE_MODE_SELECTION_MASK; 
           break;
        case OPERATIVE_MODE_UN_SELECT_E: 
           value = old_value & ~ OPERATIVE_MODE_SELECTION_MASK;
           break;
    }
  

    if (value != old_value)
        lis3mdl_write_register(CONTROL_REGISTER_1_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_get_operative_mode_selection
 *
 * RET  : Return the value of register 0xControlRegister1
 *
 * Notes : From register 0x20, bits 6:5
 *
 **************************************************************************/
unsigned char lis3mdl_get_operative_mode_selection()
  {
    unsigned char value;


    /* 
     * X and Y axes operative mode selection 
     */ 
    value = (lis3mdl_read_register(CONTROL_REGISTER_1_REG) & OPERATIVE_MODE_SELECTION_MASK) >> 5;
    return value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_set_temperature_sensor
 *
 * IN   : param, a value to write to the regiter ControlRegister1
 * OUT  : 
 *
 * RET  : Return the value of register 0xControlRegister1
 *
 * Notes : From register 0x20, bits 7:7
 *
 **************************************************************************/
unsigned char lis3mdl_set_temperature_sensor( enum temperature_sensor_enable param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lis3mdl_read_register(CONTROL_REGISTER_1_REG);

    /* 
     * Temperature sensor enable 
     */ 
    switch( param ){
        case TEMPERATURE_SENSOR_ENABLE_E: 
           value = old_value | TEMPERATURE_SENSOR_MASK; 
           break;
        case TEMPERATURE_SENSOR_DISABLE_E: 
           value = old_value & ~ TEMPERATURE_SENSOR_MASK;
           break;
    }
  

    if (value != old_value)
        lis3mdl_write_register(CONTROL_REGISTER_1_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_get_temperature_sensor
 *
 * RET  : Return the value of register 0xControlRegister1
 *
 * Notes : From register 0x20, bits 7:7
 *
 **************************************************************************/
unsigned char lis3mdl_get_temperature_sensor()
  {
    unsigned char value;


    /* 
     * Temperature sensor enable 
     */ 
    value = (lis3mdl_read_register(CONTROL_REGISTER_1_REG) & TEMPERATURE_SENSOR_MASK) >> 7;
    return value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_set_software_reset
 *
 * IN   : param, a value to write to the regiter ControlRegister2
 * OUT  : 
 *
 * RET  : Return the value of register 0xControlRegister2
 *
 * Notes : From register 0x21, bits 0:0
 *
 **************************************************************************/
unsigned char lis3mdl_set_software_reset( enum software_reset_enable param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lis3mdl_read_register(CONTROL_REGISTER_2_REG);

    /* 
     * Software Reset Enable. 
     */ 
    switch( param ){
        case SOFTWARE_RESET_ENABLE_E: 
           value = old_value | SOFTWARE_RESET_MASK; 
           break;
        case SOFTWARE_RESET_DISABLE_E: 
           value = old_value & ~ SOFTWARE_RESET_MASK;
           break;
    }
  

    if (value != old_value)
        lis3mdl_write_register(CONTROL_REGISTER_2_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_get_software_reset
 *
 * RET  : Return the value of register 0xControlRegister2
 *
 * Notes : From register 0x21, bits 0:0
 *
 **************************************************************************/
unsigned char lis3mdl_get_software_reset()
  {
    unsigned char value;


    /* 
     * Software Reset Enable. 
     */ 
    value = (lis3mdl_read_register(CONTROL_REGISTER_2_REG) & SOFTWARE_RESET_MASK);
    return value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_set_reboot_memory_content
 *
 * IN   : param, a value to write to the regiter ControlRegister2
 * OUT  : 
 *
 * RET  : Return the value of register 0xControlRegister2
 *
 * Notes : From register 0x21, bits 4:4
 *
 **************************************************************************/
unsigned char lis3mdl_set_reboot_memory_content( enum reboot_memory_content_enable param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lis3mdl_read_register(CONTROL_REGISTER_2_REG);

    /* 
     * Reboot memory content. 
     */ 
    switch( param ){
        case REBOOT_MEMORY_CONTENT_ENABLE_E: 
           value = old_value | REBOOT_MEMORY_CONTENT_MASK; 
           break;
        case REBOOT_MEMORY_CONTENT_DISABLE_E: 
           value = old_value & ~ REBOOT_MEMORY_CONTENT_MASK;
           break;
    }
  

    if (value != old_value)
        lis3mdl_write_register(CONTROL_REGISTER_2_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_get_reboot_memory_content
 *
 * RET  : Return the value of register 0xControlRegister2
 *
 * Notes : From register 0x21, bits 4:4
 *
 **************************************************************************/
unsigned char lis3mdl_get_reboot_memory_content()
  {
    unsigned char value;


    /* 
     * Reboot memory content. 
     */ 
    value = (lis3mdl_read_register(CONTROL_REGISTER_2_REG) & REBOOT_MEMORY_CONTENT_MASK) >> 4;
    return value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_set_full_scale
 *
 * IN   : param, a value to write to the regiter ControlRegister2
 * OUT  : 
 *
 * RET  : Return the value of register 0xControlRegister2
 *
 * Notes : From register 0x21, bits 6:5
 *
 **************************************************************************/
unsigned char lis3mdl_set_full_scale( enum full_scale param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lis3mdl_read_register(CONTROL_REGISTER_2_REG);

    /* 
     * Full-scale selection 
     */ 
    if (value != old_value)
        lis3mdl_write_register(CONTROL_REGISTER_2_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_get_full_scale
 *
 * RET  : Return the value of register 0xControlRegister2
 *
 * Notes : From register 0x21, bits 6:5
 *
 **************************************************************************/
unsigned char lis3mdl_get_full_scale()
  {
    unsigned char value;


    /* 
     * Full-scale selection 
     */ 
    value = (lis3mdl_read_register(CONTROL_REGISTER_2_REG) & FULL_SCALE_MASK) >> 5;
    return value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_set_operating_mode
 *
 * IN   : param, a value to write to the regiter ControlRegister3
 * OUT  : 
 *
 * RET  : Return the value of register 0xControlRegister3
 *
 * Notes : From register 0x22, bits 1:0
 *
 **************************************************************************/
unsigned char lis3mdl_set_operating_mode( enum operating_mode param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lis3mdl_read_register(CONTROL_REGISTER_3_REG);

    /* 
     * Operating mode selection 
     */ 
  

     value =  old_value & ~OPERATING_MODE_MASK ;

    switch(  param ){

           case CONTINUOUS_CONVERSION_MODE_E:
                value =  value | CONTINUOUS_CONVERSION_MODE ;
                break;
           case SINGLE_CONVERSION_MODE_E:
                value =  value | SINGLE_CONVERSION_MODE ;
                break;
           case POWER_DOWN_MODE_E:
                value =  value | POWER_DOWN_MODE ;
                break;
    }
  

    if (value != old_value)
        lis3mdl_write_register(CONTROL_REGISTER_3_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_get_operating_mode
 *
 * RET  : Return the value of register 0xControlRegister3
 *
 * Notes : From register 0x22, bits 1:0
 *
 **************************************************************************/
unsigned char lis3mdl_get_operating_mode()
  {
    unsigned char value;


    /* 
     * Operating mode selection 
     */ 
    value = (lis3mdl_read_register(CONTROL_REGISTER_3_REG) & OPERATING_MODE_MASK);
    return value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_set_spi_mode
 *
 * IN   : param, a value to write to the regiter ControlRegister3
 * OUT  : 
 *
 * RET  : Return the value of register 0xControlRegister3
 *
 * Notes : From register 0x22, bits 2:2
 *
 **************************************************************************/
unsigned char lis3mdl_set_spi_mode( enum spi_mode param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lis3mdl_read_register(CONTROL_REGISTER_3_REG);

    /* 
     * SPI serial interface mode selection 
     */ 
    switch( param ){
        case SPI_3_wire_interface_E: 
           value = old_value | SPI_MODE_MASK; 
           break;
        case SPI_4_wire_interface_E: 
           value = old_value & ~ SPI_MODE_MASK;
           break;
    }
  

    if (value != old_value)
        lis3mdl_write_register(CONTROL_REGISTER_3_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_get_spi_mode
 *
 * RET  : Return the value of register 0xControlRegister3
 *
 * Notes : From register 0x22, bits 2:2
 *
 **************************************************************************/
unsigned char lis3mdl_get_spi_mode()
  {
    unsigned char value;


    /* 
     * SPI serial interface mode selection 
     */ 
    value = (lis3mdl_read_register(CONTROL_REGISTER_3_REG) & SPI_MODE_MASK) >> 2;
    return value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_set_big_endian_mode
 *
 * IN   : param, a value to write to the regiter ControlRegister4
 * OUT  : 
 *
 * RET  : Return the value of register 0xControlRegister4
 *
 * Notes : From register 0x23, bits 1:1
 *
 **************************************************************************/
unsigned char lis3mdl_set_big_endian_mode( enum big_endian_mode param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lis3mdl_read_register(CONTROL_REGISTER_4_REG);

    /* 
     * Big/Little Endian data selection 
     */ 
    switch( param ){
        case BIG_ENDIAN_DATA_E: 
           value = old_value | BIG_ENDIAN_MODE_MASK; 
           break;
        case LITTLE_ENDIAN_DATA_E: 
           value = old_value & ~ BIG_ENDIAN_MODE_MASK;
           break;
    }
  

    if (value != old_value)
        lis3mdl_write_register(CONTROL_REGISTER_4_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_get_big_endian_mode
 *
 * RET  : Return the value of register 0xControlRegister4
 *
 * Notes : From register 0x23, bits 1:1
 *
 **************************************************************************/
unsigned char lis3mdl_get_big_endian_mode()
  {
    unsigned char value;


    /* 
     * Big/Little Endian data selection 
     */ 
    value = (lis3mdl_read_register(CONTROL_REGISTER_4_REG) & BIG_ENDIAN_MODE_MASK) >> 1;
    return value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_set_axisz_mod
 *
 * IN   : param, a value to write to the regiter ControlRegister4
 * OUT  : 
 *
 * RET  : Return the value of register 0xControlRegister4
 *
 * Notes : From register 0x23, bits 3:2
 *
 **************************************************************************/
unsigned char lis3mdl_set_axisz_mod( enum axisz_mod param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lis3mdl_read_register(CONTROL_REGISTER_4_REG);

    /* 
     * Z-axis operative mode selection. 
     */ 
    switch( param ){
        case AXISZ_MOD_1_E: 
           value = old_value | AXISZ_MOD_MASK; 
           break;
        case AXISZ_MOD_0_E: 
           value = old_value & ~ AXISZ_MOD_MASK;
           break;
    }
  

    if (value != old_value)
        lis3mdl_write_register(CONTROL_REGISTER_4_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_get_axisz_mod
 *
 * RET  : Return the value of register 0xControlRegister4
 *
 * Notes : From register 0x23, bits 3:2
 *
 **************************************************************************/
unsigned char lis3mdl_get_axisz_mod()
  {
    unsigned char value;


    /* 
     * Z-axis operative mode selection. 
     */ 
    value = (lis3mdl_read_register(CONTROL_REGISTER_4_REG) & AXISZ_MOD_MASK) >> 2;
    return value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_set_update_data_mode
 *
 * IN   : param, a value to write to the regiter ControlRegister5
 * OUT  : 
 *
 * RET  : Return the value of register 0xControlRegister5
 *
 * Notes : From register 0x24, bits 6:6
 *
 **************************************************************************/
unsigned char lis3mdl_set_update_data_mode( enum update_data_mode param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lis3mdl_read_register(CONTROL_REGISTER_5_REG);

    /* 
     * Block data update for magnetic data. 
     * 0: continuous update 
     * 1: output registers not updated until MSb and LSb have 
     * been read 
     */ 
    switch( param ){
        case UPDATE_WHEN_DATA_READED_E: 
           value = old_value | UPDATE_DATA_MODE_MASK; 
           break;
        case CONTINIOUS_UPDATE_E: 
           value = old_value & ~ UPDATE_DATA_MODE_MASK;
           break;
    }
  

    if (value != old_value)
        lis3mdl_write_register(CONTROL_REGISTER_5_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_get_update_data_mode
 *
 * RET  : Return the value of register 0xControlRegister5
 *
 * Notes : From register 0x24, bits 6:6
 *
 **************************************************************************/
unsigned char lis3mdl_get_update_data_mode()
  {
    unsigned char value;


    /* 
     * Block data update for magnetic data. 
     * 0: continuous update 
     * 1: output registers not updated until MSb and LSb have 
     * been read 
     */ 
    value = (lis3mdl_read_register(CONTROL_REGISTER_5_REG) & UPDATE_DATA_MODE_MASK) >> 6;
    return value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_set_fast_read
 *
 * IN   : param, a value to write to the regiter ControlRegister5
 * OUT  : 
 *
 * RET  : Return the value of register 0xControlRegister5
 *
 * Notes : From register 0x24, bits 7:7
 *
 **************************************************************************/
unsigned char lis3mdl_set_fast_read( enum fast_read_enable param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lis3mdl_read_register(CONTROL_REGISTER_5_REG);

    /* 
     * allows reading the high part of DATA OUT only in order to 
     * increase reading efficiency 
     */ 
    switch( param ){
        case FAST_READ_ENABLE_E: 
           value = old_value | FAST_READ_MASK; 
           break;
        case FAST_READ_DISABLE_E: 
           value = old_value & ~ FAST_READ_MASK;
           break;
    }
  

    if (value != old_value)
        lis3mdl_write_register(CONTROL_REGISTER_5_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_get_fast_read
 *
 * RET  : Return the value of register 0xControlRegister5
 *
 * Notes : From register 0x24, bits 7:7
 *
 **************************************************************************/
unsigned char lis3mdl_get_fast_read()
  {
    unsigned char value;


    /* 
     * allows reading the high part of DATA OUT only in order to 
     * increase reading efficiency 
     */ 
    value = (lis3mdl_read_register(CONTROL_REGISTER_5_REG) & FAST_READ_MASK) >> 7;
    return value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_get_data_x_ready
 *
 * RET  : Return the value of register 0xStatusRegister
 *
 * Notes : From register 0x27, bits 0:0
 *
 **************************************************************************/
unsigned char lis3mdl_get_data_x_ready()
  {
    unsigned char value;


    /* 
     * X-axis new data available. 
     */ 
    value = (lis3mdl_read_register(STATUS_REGISTER_REG) & DATA_X_READY_MASK);
    return value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_get_data_y_ready
 *
 * RET  : Return the value of register 0xStatusRegister
 *
 * Notes : From register 0x27, bits 1:1
 *
 **************************************************************************/
unsigned char lis3mdl_get_data_y_ready()
  {
    unsigned char value;


    /* 
     * Y-axis new data available. 
     */ 
    value = (lis3mdl_read_register(STATUS_REGISTER_REG) & DATA_Y_READY_MASK) >> 1;
    return value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_get_data_z_ready
 *
 * RET  : Return the value of register 0xStatusRegister
 *
 * Notes : From register 0x27, bits 2:2
 *
 **************************************************************************/
unsigned char lis3mdl_get_data_z_ready()
  {
    unsigned char value;


    /* 
     * Y-axis new data available. 
     */ 
    value = (lis3mdl_read_register(STATUS_REGISTER_REG) & DATA_Z_READY_MASK) >> 2;
    return value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_get_data_ready
 *
 * RET  : Return the value of register 0xStatusRegister
 *
 * Notes : From register 0x27, bits 3:3
 *
 **************************************************************************/
unsigned char lis3mdl_get_data_ready()
  {
    unsigned char value;


    /* 
     * X-, Y- and Z-axis new data available 
     */ 
    value = (lis3mdl_read_register(STATUS_REGISTER_REG) & DATA_READY_MASK) >> 3;
    return value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_get_data_x_overrun
 *
 * RET  : Return the value of register 0xStatusRegister
 *
 * Notes : From register 0x27, bits 4:4
 *
 **************************************************************************/
unsigned char lis3mdl_get_data_x_overrun()
  {
    unsigned char value;


    /* 
     * X-axis data overrun 
     */ 
    value = (lis3mdl_read_register(STATUS_REGISTER_REG) & DATA_X_OVERRUN_MASK) >> 4;
    return value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_get_data_y_overrun
 *
 * RET  : Return the value of register 0xStatusRegister
 *
 * Notes : From register 0x27, bits 5:5
 *
 **************************************************************************/
unsigned char lis3mdl_get_data_y_overrun()
  {
    unsigned char value;


    /* 
     * Y-axis data overrun 
     */ 
    value = (lis3mdl_read_register(STATUS_REGISTER_REG) & DATA_Y_OVERRUN_MASK) >> 5;
    return value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_get_data_z_overrun
 *
 * RET  : Return the value of register 0xStatusRegister
 *
 * Notes : From register 0x27, bits 6:6
 *
 **************************************************************************/
unsigned char lis3mdl_get_data_z_overrun()
  {
    unsigned char value;


    /* 
     * Z-axis data overrun 
     */ 
    value = (lis3mdl_read_register(STATUS_REGISTER_REG) & DATA_Z_OVERRUN_MASK) >> 6;
    return value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_get_data_overrun
 *
 * RET  : Return the value of register 0xStatusRegister
 *
 * Notes : From register 0x27, bits 7:7
 *
 **************************************************************************/
unsigned char lis3mdl_get_data_overrun()
  {
    unsigned char value;


    /* 
     * X-, Y- and Z-axis data overrun 
     */ 
    value = (lis3mdl_read_register(STATUS_REGISTER_REG) & DATA_OVERRUN_MASK) >> 7;
    return value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_get_magneto_x_low
 *
 * RET  : Return the value of register 0xMagnetoXLow
 *
 * Notes : From register 0x28, bits 7:0
 *
 **************************************************************************/
unsigned char lis3mdl_get_magneto_x_low()
  {
    unsigned char value;


    /* 
     * Status register 
     */ 
    value = lis3mdl_read_register(MAGNETO_X_LOW_REG);
    return value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_get_magneto_x_high
 *
 * RET  : Return the value of register 0xMagnetoXHigh
 *
 * Notes : From register 0x29, bits 7:0
 *
 **************************************************************************/
unsigned char lis3mdl_get_magneto_x_high()
  {
    unsigned char value;


    /* 
     * Status register 
     */ 
    value = lis3mdl_read_register(MAGNETO_X_HIGH_REG);
    return value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_get_magneto_y_low
 *
 * RET  : Return the value of register 0xMagnetoYLow
 *
 * Notes : From register 0x2A, bits 7:0
 *
 **************************************************************************/
unsigned char lis3mdl_get_magneto_y_low()
  {
    unsigned char value;


    /* 
     * Status register 
     */ 
    value = lis3mdl_read_register(MAGNETO_Y_LOW_REG);
    return value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_get_magneto_y_high
 *
 * RET  : Return the value of register 0xMagnetoYHigh
 *
 * Notes : From register 0x2B, bits 7:0
 *
 **************************************************************************/
unsigned char lis3mdl_get_magneto_y_high()
  {
    unsigned char value;


    /* 
     * Status register 
     */ 
    value = lis3mdl_read_register(MAGNETO_Y_HIGH_REG);
    return value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_get_magneto_z_low
 *
 * RET  : Return the value of register 0xMagnetoZLow
 *
 * Notes : From register 0x2C, bits 7:0
 *
 **************************************************************************/
unsigned char lis3mdl_get_magneto_z_low()
  {
    unsigned char value;


    /* 
     * Status register 
     */ 
    value = lis3mdl_read_register(MAGNETO_Z_LOW_REG);
    return value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_get_magneto_z_high
 *
 * RET  : Return the value of register 0xMagnetoZHigh
 *
 * Notes : From register 0x2D, bits 7:0
 *
 **************************************************************************/
unsigned char lis3mdl_get_magneto_z_high()
  {
    unsigned char value;


    /* 
     * Status register 
     */ 
    value = lis3mdl_read_register(MAGNETO_Z_HIGH_REG);
    return value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_get_temperature_data_lsb
 *
 * RET  : Return the value of register 0xTemperatureDataLsb
 *
 * Notes : From register 0x2E, bits 7:0
 *
 **************************************************************************/
unsigned char lis3mdl_get_temperature_data_lsb()
  {
    unsigned char value;


    /* 
     * Temperature data LSB 
     */ 
    value = lis3mdl_read_register(TEMPERATURE_DATA_LSB_REG);
    return value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_get_temperature_data_msb
 *
 * RET  : Return the value of register 0xTemperatureDataMsb
 *
 * Notes : From register 0x2F, bits 7:0
 *
 **************************************************************************/
unsigned char lis3mdl_get_temperature_data_msb()
  {
    unsigned char value;


    /* 
     * Temperature data MSB 
     */ 
    value = lis3mdl_read_register(TEMPERATURE_DATA_MSB_REG);
    return value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_set_interrupt_pin
 *
 * IN   : param, a value to write to the regiter InterruptConfig
 * OUT  : 
 *
 * RET  : Return the value of register 0xInterruptConfig
 *
 * Notes : From register 0x30, bits 0:0
 *
 **************************************************************************/
unsigned char lis3mdl_set_interrupt_pin( enum interrupt_pin_enable param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lis3mdl_read_register(INTERRUPT_CONFIG_REG);

    /* 
     * Interrupt enable on INT pin 
     */ 
    switch( param ){
        case INTERRUPT_PIN_ENABLE_E: 
           value = old_value | INTERRUPT_PIN_MASK; 
           break;
        case INTERRUPT_PIN_DISABLE_E: 
           value = old_value & ~ INTERRUPT_PIN_MASK;
           break;
    }
  

    if (value != old_value)
        lis3mdl_write_register(INTERRUPT_CONFIG_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_get_interrupt_pin
 *
 * RET  : Return the value of register 0xInterruptConfig
 *
 * Notes : From register 0x30, bits 0:0
 *
 **************************************************************************/
unsigned char lis3mdl_get_interrupt_pin()
  {
    unsigned char value;


    /* 
     * Interrupt enable on INT pin 
     */ 
    value = (lis3mdl_read_register(INTERRUPT_CONFIG_REG) & INTERRUPT_PIN_MASK);
    return value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_set_latch_interrupt_request
 *
 * IN   : param, a value to write to the regiter InterruptConfig
 * OUT  : 
 *
 * RET  : Return the value of register 0xInterruptConfig
 *
 * Notes : From register 0x30, bits 1:1
 *
 **************************************************************************/
unsigned char lis3mdl_set_latch_interrupt_request( enum latch_interrupt_request param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lis3mdl_read_register(INTERRUPT_CONFIG_REG);

    /* 
     * Latch interrupt request 
     */ 
    switch( param ){
        case EDGE_DETECTED_E: 
           value = old_value | LATCH_INTERRUPT_REQUEST_MASK; 
           break;
        case INACTIVE_E: 
           value = old_value & ~ LATCH_INTERRUPT_REQUEST_MASK;
           break;
    }
  

    if (value != old_value)
        lis3mdl_write_register(INTERRUPT_CONFIG_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_get_latch_interrupt_request
 *
 * RET  : Return the value of register 0xInterruptConfig
 *
 * Notes : From register 0x30, bits 1:1
 *
 **************************************************************************/
unsigned char lis3mdl_get_latch_interrupt_request()
  {
    unsigned char value;


    /* 
     * Latch interrupt request 
     */ 
    value = (lis3mdl_read_register(INTERRUPT_CONFIG_REG) & LATCH_INTERRUPT_REQUEST_MASK) >> 1;
    return value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_set_interrupt
 *
 * IN   : param, a value to write to the regiter InterruptConfig
 * OUT  : 
 *
 * RET  : Return the value of register 0xInterruptConfig
 *
 * Notes : From register 0x30, bits 2:2
 *
 **************************************************************************/
unsigned char lis3mdl_set_interrupt( enum interrupt_enable param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lis3mdl_read_register(INTERRUPT_CONFIG_REG);

    /* 
     * Interrupt active configuration on INT 
     */ 
    switch( param ){
        case INTERRUPT_ENABLE_E: 
           value = old_value | INTERRUPT_MASK; 
           break;
        case INTERRUPT_DISABLE_E: 
           value = old_value & ~ INTERRUPT_MASK;
           break;
    }
  

    if (value != old_value)
        lis3mdl_write_register(INTERRUPT_CONFIG_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_get_interrupt
 *
 * RET  : Return the value of register 0xInterruptConfig
 *
 * Notes : From register 0x30, bits 2:2
 *
 **************************************************************************/
unsigned char lis3mdl_get_interrupt()
  {
    unsigned char value;


    /* 
     * Interrupt active configuration on INT 
     */ 
    value = (lis3mdl_read_register(INTERRUPT_CONFIG_REG) & INTERRUPT_MASK) >> 2;
    return value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_set_interrupt_z_axise
 *
 * IN   : param, a value to write to the regiter InterruptConfig
 * OUT  : 
 *
 * RET  : Return the value of register 0xInterruptConfig
 *
 * Notes : From register 0x30, bits 5:5
 *
 **************************************************************************/
unsigned char lis3mdl_set_interrupt_z_axise( enum interrupt_z_axise_enable param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lis3mdl_read_register(INTERRUPT_CONFIG_REG);

    /* 
     * Enable interrupt generation on Z-axise 
     */ 
    switch( param ){
        case INTERRUPT_Z_AXISE_ENABLE_E: 
           value = old_value | INTERRUPT_Z_AXISE_MASK; 
           break;
        case INTERRUPT_Z_AXISE_DISABLE_E: 
           value = old_value & ~ INTERRUPT_Z_AXISE_MASK;
           break;
    }
  

    if (value != old_value)
        lis3mdl_write_register(INTERRUPT_CONFIG_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_get_interrupt_z_axise
 *
 * RET  : Return the value of register 0xInterruptConfig
 *
 * Notes : From register 0x30, bits 5:5
 *
 **************************************************************************/
unsigned char lis3mdl_get_interrupt_z_axise()
  {
    unsigned char value;


    /* 
     * Enable interrupt generation on Z-axise 
     */ 
    value = (lis3mdl_read_register(INTERRUPT_CONFIG_REG) & INTERRUPT_Z_AXISE_MASK) >> 5;
    return value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_set_interrupt_y_axise
 *
 * IN   : param, a value to write to the regiter InterruptConfig
 * OUT  : 
 *
 * RET  : Return the value of register 0xInterruptConfig
 *
 * Notes : From register 0x30, bits 6:6
 *
 **************************************************************************/
unsigned char lis3mdl_set_interrupt_y_axise( enum interrupt_y_axise_enable param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lis3mdl_read_register(INTERRUPT_CONFIG_REG);

    /* 
     * Enable interrupt generation on Y-axise 
     */ 
    switch( param ){
        case INTERRUPT_Y_AXISE_ENABLE_E: 
           value = old_value | INTERRUPT_Y_AXISE_MASK; 
           break;
        case INTERRUPT_Y_AXISE_DISABLE_E: 
           value = old_value & ~ INTERRUPT_Y_AXISE_MASK;
           break;
    }
  

    if (value != old_value)
        lis3mdl_write_register(INTERRUPT_CONFIG_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_get_interrupt_y_axise
 *
 * RET  : Return the value of register 0xInterruptConfig
 *
 * Notes : From register 0x30, bits 6:6
 *
 **************************************************************************/
unsigned char lis3mdl_get_interrupt_y_axise()
  {
    unsigned char value;


    /* 
     * Enable interrupt generation on Y-axise 
     */ 
    value = (lis3mdl_read_register(INTERRUPT_CONFIG_REG) & INTERRUPT_Y_AXISE_MASK) >> 6;
    return value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_set_interrupt_x_axise
 *
 * IN   : param, a value to write to the regiter InterruptConfig
 * OUT  : 
 *
 * RET  : Return the value of register 0xInterruptConfig
 *
 * Notes : From register 0x30, bits 7:7
 *
 **************************************************************************/
unsigned char lis3mdl_set_interrupt_x_axise( enum interrupt_x_axise_enable param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lis3mdl_read_register(INTERRUPT_CONFIG_REG);

    /* 
     * Enable interrupt generation on X-axise 
     */ 
    switch( param ){
        case INTERRUPT_X_AXISE_ENABLE_E: 
           value = old_value | INTERRUPT_X_AXISE_MASK; 
           break;
        case INTERRUPT_X_AXISE_DISABLE_E: 
           value = old_value & ~ INTERRUPT_X_AXISE_MASK;
           break;
    }
  

    if (value != old_value)
        lis3mdl_write_register(INTERRUPT_CONFIG_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_get_interrupt_x_axise
 *
 * RET  : Return the value of register 0xInterruptConfig
 *
 * Notes : From register 0x30, bits 7:7
 *
 **************************************************************************/
unsigned char lis3mdl_get_interrupt_x_axise()
  {
    unsigned char value;


    /* 
     * Enable interrupt generation on X-axise 
     */ 
    value = (lis3mdl_read_register(INTERRUPT_CONFIG_REG) & INTERRUPT_X_AXISE_MASK) >> 7;
    return value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_set_interrupt_event
 *
 * IN   : param, a value to write to the regiter InterruptSource
 * OUT  : 
 *
 * RET  : Return the value of register 0xInterruptSource
 *
 * Notes : From register 0x31, bits 0:0
 *
 **************************************************************************/
unsigned char lis3mdl_set_interrupt_event( enum interrupt_event param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lis3mdl_read_register(INTERRUPT_SOURCE_REG);

    /* 
     * This bit signals when an interrupt event occurs 
     */ 
    switch( param ){
        case INTERRUPT_EVENT_E: 
           value = old_value | INTERRUPT_EVENT_MASK; 
           break;
        case NO_EVENT_E: 
           value = old_value & ~ INTERRUPT_EVENT_MASK;
           break;
    }
  

    if (value != old_value)
        lis3mdl_write_register(INTERRUPT_SOURCE_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_get_interrupt_event
 *
 * RET  : Return the value of register 0xInterruptSource
 *
 * Notes : From register 0x31, bits 0:0
 *
 **************************************************************************/
unsigned char lis3mdl_get_interrupt_event()
  {
    unsigned char value;


    /* 
     * This bit signals when an interrupt event occurs 
     */ 
    value = (lis3mdl_read_register(INTERRUPT_SOURCE_REG) & INTERRUPT_EVENT_MASK);
    return value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_set_internal_overflow_value
 *
 * IN   : param, a value to write to the regiter InterruptSource
 * OUT  : 
 *
 * RET  : Return the value of register 0xInterruptSource
 *
 * Notes : From register 0x31, bits 1:1
 *
 **************************************************************************/
unsigned char lis3mdl_set_internal_overflow_value( enum internal_overflow_value param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lis3mdl_read_register(INTERRUPT_SOURCE_REG);

    /* 
     * Internal measurement range overflow on magnetic value 
     */ 
    switch( param ){
        case INTERNAL_OVERFLOW_E: 
           value = old_value | INTERNAL_OVERFLOW_VALUE_MASK; 
           break;
        case NO_OVERFLOW_E: 
           value = old_value & ~ INTERNAL_OVERFLOW_VALUE_MASK;
           break;
    }
  

    if (value != old_value)
        lis3mdl_write_register(INTERRUPT_SOURCE_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_get_internal_overflow_value
 *
 * RET  : Return the value of register 0xInterruptSource
 *
 * Notes : From register 0x31, bits 1:1
 *
 **************************************************************************/
unsigned char lis3mdl_get_internal_overflow_value()
  {
    unsigned char value;


    /* 
     * Internal measurement range overflow on magnetic value 
     */ 
    value = (lis3mdl_read_register(INTERRUPT_SOURCE_REG) & INTERNAL_OVERFLOW_VALUE_MASK) >> 1;
    return value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_get_threshold_negative_z
 *
 * RET  : Return the value of register 0xInterruptSource
 *
 * Notes : From register 0x31, bits 2:2
 *
 **************************************************************************/
unsigned char lis3mdl_get_threshold_negative_z()
  {
    unsigned char value;


    /* 
     * Value on Z-axis exceeds the threshold on the negative 
     * side 
     */ 
    value = (lis3mdl_read_register(INTERRUPT_SOURCE_REG) & THRESHOLD_NEGATIVE_Z_MASK) >> 2;
    return value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_get_threshold_negative_y
 *
 * RET  : Return the value of register 0xInterruptSource
 *
 * Notes : From register 0x31, bits 3:3
 *
 **************************************************************************/
unsigned char lis3mdl_get_threshold_negative_y()
  {
    unsigned char value;


    /* 
     * Value on Y-axis exceeds the threshold on the negative 
     * side 
     */ 
    value = (lis3mdl_read_register(INTERRUPT_SOURCE_REG) & THRESHOLD_NEGATIVE_Y_MASK) >> 3;
    return value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_get_threshold_negative_x
 *
 * RET  : Return the value of register 0xInterruptSource
 *
 * Notes : From register 0x31, bits 4:4
 *
 **************************************************************************/
unsigned char lis3mdl_get_threshold_negative_x()
  {
    unsigned char value;


    /* 
     * Value on X-axis exceeds the threshold on the negative 
     * side 
     */ 
    value = (lis3mdl_read_register(INTERRUPT_SOURCE_REG) & THRESHOLD_NEGATIVE_X_MASK) >> 4;
    return value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_get_threshold_positive_z
 *
 * RET  : Return the value of register 0xInterruptSource
 *
 * Notes : From register 0x31, bits 5:5
 *
 **************************************************************************/
unsigned char lis3mdl_get_threshold_positive_z()
  {
    unsigned char value;


    /* 
     * Value on Z-axis exceeds the threshold on the positive 
     * side 
     */ 
    value = (lis3mdl_read_register(INTERRUPT_SOURCE_REG) & THRESHOLD_POSITIVE_Z_MASK) >> 5;
    return value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_get_threshold_positive_y
 *
 * RET  : Return the value of register 0xInterruptSource
 *
 * Notes : From register 0x31, bits 6:6
 *
 **************************************************************************/
unsigned char lis3mdl_get_threshold_positive_y()
  {
    unsigned char value;


    /* 
     * Value on Y-axis exceeds the threshold on the positive 
     * side 
     */ 
    value = (lis3mdl_read_register(INTERRUPT_SOURCE_REG) & THRESHOLD_POSITIVE_Y_MASK) >> 6;
    return value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_get_threshold_positive_x
 *
 * RET  : Return the value of register 0xInterruptSource
 *
 * Notes : From register 0x31, bits 7:7
 *
 **************************************************************************/
unsigned char lis3mdl_get_threshold_positive_x()
  {
    unsigned char value;


    /* 
     * Value on X-axis exceeds the threshold on the positive 
     * side 
     */ 
    value = (lis3mdl_read_register(INTERRUPT_SOURCE_REG) & THRESHOLD_POSITIVE_X_MASK) >> 7;
    return value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_get_interrupt_threshold_lsb
 *
 * RET  : Return the value of register 0xInterruptThresholdLsb
 *
 * Notes : From register 0x32, bits 7:0
 *
 **************************************************************************/
unsigned char lis3mdl_get_interrupt_threshold_lsb()
  {
    unsigned char value;


    /* 
     * Interrupt Threshold Msb 
     */ 
    value = lis3mdl_read_register(INTERRUPT_THRESHOLD_LSB_REG);
    return value;
  }


/***************************************************************************
 *
 * Function : lis3mdl_get_interrupt_threshol_m_lsb
 *
 * RET  : Return the value of register 0xInterruptThresholMLsb
 *
 * Notes : From register 0x33, bits 7:0
 *
 **************************************************************************/
unsigned char lis3mdl_get_interrupt_threshol_m_lsb()
  {
    unsigned char value;


    /* 
     * Interrupt Threshold Msb 
     */ 
    value = lis3mdl_read_register(INTERRUPT_THRESHOL_M_LSB_REG);
    return value;
  }




#ifdef __cplusplus
}
#endif

#endif
