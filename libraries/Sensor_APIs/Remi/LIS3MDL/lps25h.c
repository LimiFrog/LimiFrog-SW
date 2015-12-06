/****************************************************************************
 * File : c:/Lisp/Production/sensors_st/sensors_st_lps25h/Linux/lps25h.c
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

#ifndef C__LISP_PRODUCTION_SENSORS_ST_SENSORS_ST_LPS25H_LINUX_LPS25H_C
#define C__LISP_PRODUCTION_SENSORS_ST_SENSORS_ST_LPS25H_LINUX_LPS25H_C


#ifdef __cplusplus
extern "C" {
#endif
#include "lps25h.h"

extern unsigned char lps25h_read_register( unsigned short register_address);
extern void lps25h_write_register( unsigned short register_address, unsigned char data );


/***************************************************************************
 *
 * Function : lps25h_set_reference_register_x_lsb
 *
 * IN   : param, a value to write to the regiter ReferenceRegisterXLsb
 * OUT  : 
 *
 * RET  : Return the value of register 0xReferenceRegisterXLsb
 *
 * Notes : From register 0xB808, bits 7:0
 *
 **************************************************************************/
unsigned char lps25h_set_reference_register_x_lsb( unsigned char param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lps25h_read_register(REFERENCE_REGISTER_X_LSB_REG);

    /* 
     * Reference pressure (LSB data) 
     */ 
  
    value =  old_value ;


    value |=  param ;  

    if (value != old_value)
        lps25h_write_register(REFERENCE_REGISTER_X_LSB_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lps25h_get_reference_register_x_lsb
 *
 * RET  : Return the value of register 0xReferenceRegisterXLsb
 *
 * Notes : From register 0xB808, bits 7:0
 *
 **************************************************************************/
unsigned char lps25h_get_reference_register_x_lsb()
  {
    unsigned char value;


    /* 
     * Reference pressure (LSB data) 
     */ 
    value = lps25h_read_register(REFERENCE_REGISTER_X_LSB_REG);
    return value;
  }


/***************************************************************************
 *
 * Function : lps25h_set_reference_register_lsb
 *
 * IN   : param, a value to write to the regiter ReferenceRegisterLsb
 * OUT  : 
 *
 * RET  : Return the value of register 0xReferenceRegisterLsb
 *
 * Notes : From register 0xB809, bits 7:0
 *
 **************************************************************************/
unsigned char lps25h_set_reference_register_lsb( unsigned char param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lps25h_read_register(REFERENCE_REGISTER_LSB_REG);

    /* 
     * Reference pressure (LSB data) 
     */ 
  
    value =  old_value ;


    value |=  param ;  

    if (value != old_value)
        lps25h_write_register(REFERENCE_REGISTER_LSB_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lps25h_get_reference_register_lsb
 *
 * RET  : Return the value of register 0xReferenceRegisterLsb
 *
 * Notes : From register 0xB809, bits 7:0
 *
 **************************************************************************/
unsigned char lps25h_get_reference_register_lsb()
  {
    unsigned char value;


    /* 
     * Reference pressure (LSB data) 
     */ 
    value = lps25h_read_register(REFERENCE_REGISTER_LSB_REG);
    return value;
  }


/***************************************************************************
 *
 * Function : lps25h_set_reference_register_msb
 *
 * IN   : param, a value to write to the regiter ReferenceRegisterMsb
 * OUT  : 
 *
 * RET  : Return the value of register 0xReferenceRegisterMsb
 *
 * Notes : From register 0xB80A, bits 7:0
 *
 **************************************************************************/
unsigned char lps25h_set_reference_register_msb( unsigned char param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lps25h_read_register(REFERENCE_REGISTER_MSB_REG);

    /* 
     * Reference pressure (MSB data) 
     */ 
  
    value =  old_value ;


    value |=  param ;  

    if (value != old_value)
        lps25h_write_register(REFERENCE_REGISTER_MSB_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lps25h_get_reference_register_msb
 *
 * RET  : Return the value of register 0xReferenceRegisterMsb
 *
 * Notes : From register 0xB80A, bits 7:0
 *
 **************************************************************************/
unsigned char lps25h_get_reference_register_msb()
  {
    unsigned char value;


    /* 
     * Reference pressure (MSB data) 
     */ 
    value = lps25h_read_register(REFERENCE_REGISTER_MSB_REG);
    return value;
  }


/***************************************************************************
 *
 * Function : lps25h_get_who_iam
 *
 * RET  : Return the value of register 0xWhoIam
 *
 * Notes : From register 0xB80F, bits 7:0
 *
 **************************************************************************/
unsigned char lps25h_get_who_iam()
  {
    unsigned char value;


    /* 
     * Who I am register, ID register 
     */ 
    value = lps25h_read_register(WHO_IAM_REG);
    return value;
  }


/***************************************************************************
 *
 * Function : lps25h_set_averaged_temperature_samples
 *
 * IN   : param, a value to write to the regiter ResolutionMode
 * OUT  : 
 *
 * RET  : Return the value of register 0xResolutionMode
 *
 * Notes : From register 0xB810, bits 1:0
 *
 **************************************************************************/
unsigned char lps25h_set_averaged_temperature_samples( enum temperature_average param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lps25h_read_register(RESOLUTION_MODE_REG);

    /* 
     * To select the numbers of averaged temperature samples 
     */ 
  

     value =  old_value & ~AVERAGED_TEMPERATURE_SAMPLES_MASK ;

    switch(  param ){

           case TEMPERATURE_AVERAGE_8_E:
                value =  value | TEMPERATURE_AVERAGE_8 ;
                break;
           case TEMPERATURE_AVERAGE_16_E:
                value =  value | TEMPERATURE_AVERAGE_16 ;
                break;
           case TEMPERATURE_AVERAGE_32_E:
                value =  value | TEMPERATURE_AVERAGE_32 ;
                break;
           case TEMPERATURE_AVERAGE_64_E:
                value =  value | TEMPERATURE_AVERAGE_64 ;
                break;
    }
  

    if (value != old_value)
        lps25h_write_register(RESOLUTION_MODE_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lps25h_get_averaged_temperature_samples
 *
 * RET  : Return the value of register 0xResolutionMode
 *
 * Notes : From register 0xB810, bits 1:0
 *
 **************************************************************************/
unsigned char lps25h_get_averaged_temperature_samples()
  {
    unsigned char value;


    /* 
     * To select the numbers of averaged temperature samples 
     */ 
    value = (lps25h_read_register(RESOLUTION_MODE_REG) & AVERAGED_TEMPERATURE_SAMPLES_MASK);
    return value;
  }


/***************************************************************************
 *
 * Function : lps25h_set_averaged_pressure_samples
 *
 * IN   : param, a value to write to the regiter ResolutionMode
 * OUT  : 
 *
 * RET  : Return the value of register 0xResolutionMode
 *
 * Notes : From register 0xB810, bits 3:2
 *
 **************************************************************************/
unsigned char lps25h_set_averaged_pressure_samples( enum pressure_average param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lps25h_read_register(RESOLUTION_MODE_REG);

    /* 
     * To select the numbers of averaged pressure samples 
     */ 
  

     value =  old_value & ~AVERAGED_PRESSURE_SAMPLES_MASK ;

    switch(  param ){

           case PRESSURE_AVERAGE_8_E:
                value  = value  | (PRESSURE_AVERAGE_8 << 0x2);
                break;
           case PRESSURE_AVERAGE_32_E:
                value  = value  | (PRESSURE_AVERAGE_32 << 0x2);
                break;
           case PRESSURE_AVERAGE_128_E:
                value  = value  | (PRESSURE_AVERAGE_128 << 0x2);
                break;
           case PRESSURE_AVERAGE_512_E:
                value  = value  | (PRESSURE_AVERAGE_512 << 0x2);
                break;
    }
  

    if (value != old_value)
        lps25h_write_register(RESOLUTION_MODE_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lps25h_get_averaged_pressure_samples
 *
 * RET  : Return the value of register 0xResolutionMode
 *
 * Notes : From register 0xB810, bits 3:2
 *
 **************************************************************************/
unsigned char lps25h_get_averaged_pressure_samples()
  {
    unsigned char value;


    /* 
     * To select the numbers of averaged pressure samples 
     */ 
    value = (lps25h_read_register(RESOLUTION_MODE_REG) & AVERAGED_PRESSURE_SAMPLES_MASK) >> 2;
    return value;
  }


/***************************************************************************
 *
 * Function : lps25h_set_spi_wire
 *
 * IN   : param, a value to write to the regiter ControlRegister1
 * OUT  : 
 *
 * RET  : Return the value of register 0xControlRegister1
 *
 * Notes : From register 0xB820, bits 0:0
 *
 **************************************************************************/
unsigned char lps25h_set_spi_wire( enum spi_wire param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lps25h_read_register(CONTROL_REGISTER_1_REG);

    /* 
     * SPI Serial Interface Mode selection. 0: 4-wire interface; 
     * 1: 3-wire interface 
     */ 
    switch( param ){
        case SPI_3_WIRE_E: 
           value = old_value | SPI_WIRE_MASK; 
           break;
        case SPI_4_WIRE_E: 
           value = old_value & ~ SPI_WIRE_MASK;
           break;
    }
  

    if (value != old_value)
        lps25h_write_register(CONTROL_REGISTER_1_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lps25h_get_spi_wire
 *
 * RET  : Return the value of register 0xControlRegister1
 *
 * Notes : From register 0xB820, bits 0:0
 *
 **************************************************************************/
unsigned char lps25h_get_spi_wire()
  {
    unsigned char value;


    /* 
     * SPI Serial Interface Mode selection. 0: 4-wire interface; 
     * 1: 3-wire interface 
     */ 
    value = (lps25h_read_register(CONTROL_REGISTER_1_REG) & SPI_WIRE_MASK);
    return value;
  }


/***************************************************************************
 *
 * Function : lps25h_set_reset_auto_zerofunction
 *
 * IN   : param, a value to write to the regiter ControlRegister1
 * OUT  : 
 *
 * RET  : Return the value of register 0xControlRegister1
 *
 * Notes : From register 0xB820, bits 1:1
 *
 **************************************************************************/
unsigned char lps25h_set_reset_auto_zerofunction( enum reset_auto_zero param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lps25h_read_register(CONTROL_REGISTER_1_REG);

    /* 
     * Reset AutoZero function. Reset REF_P reg, set pressure to 
     * default value in RPDS 
     */ 
    switch( param ){
        case DISABLE_RESET_AUTOZERO_E: 
           value = old_value | RESET_AUTO_ZEROFUNCTION_MASK; 
           break;
        case RESET_AUTOZERO_E: 
           value = old_value & ~ RESET_AUTO_ZEROFUNCTION_MASK;
           break;
    }
  

    if (value != old_value)
        lps25h_write_register(CONTROL_REGISTER_1_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lps25h_get_reset_auto_zerofunction
 *
 * RET  : Return the value of register 0xControlRegister1
 *
 * Notes : From register 0xB820, bits 1:1
 *
 **************************************************************************/
unsigned char lps25h_get_reset_auto_zerofunction()
  {
    unsigned char value;


    /* 
     * Reset AutoZero function. Reset REF_P reg, set pressure to 
     * default value in RPDS 
     */ 
    value = (lps25h_read_register(CONTROL_REGISTER_1_REG) & RESET_AUTO_ZEROFUNCTION_MASK) >> 1;
    return value;
  }


/***************************************************************************
 *
 * Function : lps25h_set_continuous_update
 *
 * IN   : param, a value to write to the regiter ControlRegister1
 * OUT  : 
 *
 * RET  : Return the value of register 0xControlRegister1
 *
 * Notes : From register 0xB820, bits 2:2
 *
 **************************************************************************/
unsigned char lps25h_set_continuous_update( enum continuous_update_enable param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lps25h_read_register(CONTROL_REGISTER_1_REG);

    /* 
     * block data update 0: continuous update; 1: output 
     * registers not updated until MSB and LSB reading 
     */ 
    switch( param ){
        case CONTINUOUS_UPDATE_ENABLE_E: 
           value = old_value | CONTINUOUS_UPDATE_MASK; 
           break;
        case CONTINUOUS_UPDATE_DISABLE_E: 
           value = old_value & ~ CONTINUOUS_UPDATE_MASK;
           break;
    }
  

    if (value != old_value)
        lps25h_write_register(CONTROL_REGISTER_1_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lps25h_get_continuous_update
 *
 * RET  : Return the value of register 0xControlRegister1
 *
 * Notes : From register 0xB820, bits 2:2
 *
 **************************************************************************/
unsigned char lps25h_get_continuous_update()
  {
    unsigned char value;


    /* 
     * block data update 0: continuous update; 1: output 
     * registers not updated until MSB and LSB reading 
     */ 
    value = (lps25h_read_register(CONTROL_REGISTER_1_REG) & CONTINUOUS_UPDATE_MASK) >> 2;
    return value;
  }


/***************************************************************************
 *
 * Function : lps25h_set_interrupt_circuit
 *
 * IN   : param, a value to write to the regiter ControlRegister1
 * OUT  : 
 *
 * RET  : Return the value of register 0xControlRegister1
 *
 * Notes : From register 0xB820, bits 3:3
 *
 **************************************************************************/
unsigned char lps25h_set_interrupt_circuit( enum interrupt_circuit_enable param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lps25h_read_register(CONTROL_REGISTER_1_REG);

    /* 
     * Interrupt circuit enable. 
     */ 
    switch( param ){
        case INTERRUPT_CIRCUIT_ENABLE_E: 
           value = old_value | INTERRUPT_CIRCUIT_MASK; 
           break;
        case INTERRUPT_CIRCUIT_DISABLE_E: 
           value = old_value & ~ INTERRUPT_CIRCUIT_MASK;
           break;
    }
  

    if (value != old_value)
        lps25h_write_register(CONTROL_REGISTER_1_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lps25h_get_interrupt_circuit
 *
 * RET  : Return the value of register 0xControlRegister1
 *
 * Notes : From register 0xB820, bits 3:3
 *
 **************************************************************************/
unsigned char lps25h_get_interrupt_circuit()
  {
    unsigned char value;


    /* 
     * Interrupt circuit enable. 
     */ 
    value = (lps25h_read_register(CONTROL_REGISTER_1_REG) & INTERRUPT_CIRCUIT_MASK) >> 3;
    return value;
  }


/***************************************************************************
 *
 * Function : lps25h_set_data_rate
 *
 * IN   : param, a value to write to the regiter ControlRegister1
 * OUT  : 
 *
 * RET  : Return the value of register 0xControlRegister1
 *
 * Notes : From register 0xB820, bits 6:4
 *
 **************************************************************************/
unsigned char lps25h_set_data_rate( enum data_rate param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lps25h_read_register(CONTROL_REGISTER_1_REG);

    /* 
     * output data rate selection 
     */ 
  

     value =  old_value & ~DATA_RATE_MASK ;

    switch(  param ){

           case ONE_SHOT_E:
                value  = value  | (ONE_SHOT << 0x4);
                break;
           case DATA_RATE_1HZ_E:
                value  = value  | (DATA_RATE_1HZ << 0x4);
                break;
           case DATA_RATE_7HZ_E:
                value  = value  | (DATA_RATE_7HZ << 0x4);
                break;
           case DATA_RATE_12_5HZ_E:
                value  = value  | (DATA_RATE_12_5HZ << 0x4);
                break;
           case DATA_RATE_15_5HZ_E:
                value  = value  | (DATA_RATE_15_5HZ << 0x4);
                break;
    }
  

    if (value != old_value)
        lps25h_write_register(CONTROL_REGISTER_1_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lps25h_get_data_rate
 *
 * RET  : Return the value of register 0xControlRegister1
 *
 * Notes : From register 0xB820, bits 6:4
 *
 **************************************************************************/
unsigned char lps25h_get_data_rate()
  {
    unsigned char value;


    /* 
     * output data rate selection 
     */ 
    value = (lps25h_read_register(CONTROL_REGISTER_1_REG) & DATA_RATE_MASK) >> 4;
    return value;
  }


/***************************************************************************
 *
 * Function : lps25h_set_active_mode
 *
 * IN   : param, a value to write to the regiter ControlRegister1
 * OUT  : 
 *
 * RET  : Return the value of register 0xControlRegister1
 *
 * Notes : From register 0xB820, bits 7:7
 *
 **************************************************************************/
unsigned char lps25h_set_active_mode( enum active_mode_enable param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lps25h_read_register(CONTROL_REGISTER_1_REG);

    /* 
     * power down control. 0: power-down mode; 1: active mode 
     */ 
    switch( param ){
        case ACTIVE_MODE_ENABLE_E: 
           value = old_value | ACTIVE_MODE_MASK; 
           break;
        case ACTIVE_MODE_DISABLE_E: 
           value = old_value & ~ ACTIVE_MODE_MASK;
           break;
    }
  

    if (value != old_value)
        lps25h_write_register(CONTROL_REGISTER_1_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lps25h_get_active_mode
 *
 * RET  : Return the value of register 0xControlRegister1
 *
 * Notes : From register 0xB820, bits 7:7
 *
 **************************************************************************/
unsigned char lps25h_get_active_mode()
  {
    unsigned char value;


    /* 
     * power down control. 0: power-down mode; 1: active mode 
     */ 
    value = (lps25h_read_register(CONTROL_REGISTER_1_REG) & ACTIVE_MODE_MASK) >> 7;
    return value;
  }


/***************************************************************************
 *
 * Function : lps25h_set_one_shot
 *
 * IN   : param, a value to write to the regiter ControlRegister2
 * OUT  : 
 *
 * RET  : Return the value of register 0xControlRegister2
 *
 * Notes : From register 0xB821, bits 0:0
 *
 **************************************************************************/
unsigned char lps25h_set_one_shot( enum one_shot_enable param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lps25h_read_register(CONTROL_REGISTER_2_REG);

    /* 
     * One shot enable. 
     */ 
    switch( param ){
        case ONE_SHOT_ENABLE_E: 
           value = old_value | ONE_SHOT_MASK; 
           break;
        case ONE_SHOT_DISABLE_E: 
           value = old_value & ~ ONE_SHOT_MASK;
           break;
    }
  

    if (value != old_value)
        lps25h_write_register(CONTROL_REGISTER_2_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lps25h_get_one_shot
 *
 * RET  : Return the value of register 0xControlRegister2
 *
 * Notes : From register 0xB821, bits 0:0
 *
 **************************************************************************/
unsigned char lps25h_get_one_shot()
  {
    unsigned char value;


    /* 
     * One shot enable. 
     */ 
    value = (lps25h_read_register(CONTROL_REGISTER_2_REG) & ONE_SHOT_MASK);
    return value;
  }


/***************************************************************************
 *
 * Function : lps25h_set_autozero
 *
 * IN   : param, a value to write to the regiter ControlRegister2
 * OUT  : 
 *
 * RET  : Return the value of register 0xControlRegister2
 *
 * Notes : From register 0xB821, bits 1:1
 *
 **************************************************************************/
unsigned char lps25h_set_autozero( enum autozero_enable param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lps25h_read_register(CONTROL_REGISTER_2_REG);

    /* 
     * Autozero enable. 
     */ 
    switch( param ){
        case AUTOZERO_ENABLE_E: 
           value = old_value | AUTOZERO_MASK; 
           break;
        case AUTOZERO_DISABLE_E: 
           value = old_value & ~ AUTOZERO_MASK;
           break;
    }
  

    if (value != old_value)
        lps25h_write_register(CONTROL_REGISTER_2_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lps25h_get_autozero
 *
 * RET  : Return the value of register 0xControlRegister2
 *
 * Notes : From register 0xB821, bits 1:1
 *
 **************************************************************************/
unsigned char lps25h_get_autozero()
  {
    unsigned char value;


    /* 
     * Autozero enable. 
     */ 
    value = (lps25h_read_register(CONTROL_REGISTER_2_REG) & AUTOZERO_MASK) >> 1;
    return value;
  }


/***************************************************************************
 *
 * Function : lps25h_set_software_reset
 *
 * IN   : param, a value to write to the regiter ControlRegister2
 * OUT  : 
 *
 * RET  : Return the value of register 0xControlRegister2
 *
 * Notes : From register 0xB821, bits 2:2
 *
 **************************************************************************/
unsigned char lps25h_set_software_reset( enum software_reset_enable param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lps25h_read_register(CONTROL_REGISTER_2_REG);

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
        lps25h_write_register(CONTROL_REGISTER_2_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lps25h_get_software_reset
 *
 * RET  : Return the value of register 0xControlRegister2
 *
 * Notes : From register 0xB821, bits 2:2
 *
 **************************************************************************/
unsigned char lps25h_get_software_reset()
  {
    unsigned char value;


    /* 
     * Software Reset Enable. 
     */ 
    value = (lps25h_read_register(CONTROL_REGISTER_2_REG) & SOFTWARE_RESET_MASK) >> 2;
    return value;
  }


/***************************************************************************
 *
 * Function : lps25h_set_comm
 *
 * IN   : param, a value to write to the regiter ControlRegister2
 * OUT  : 
 *
 * RET  : Return the value of register 0xControlRegister2
 *
 * Notes : From register 0xB821, bits 3:3
 *
 **************************************************************************/
unsigned char lps25h_set_comm( enum comm_mode param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lps25h_read_register(CONTROL_REGISTER_2_REG);

    /* 
     * 0: I2C enable;1: SPI disable 
     */ 
    switch( param ){
        case ENABLE_SPI_E: 
           value = old_value | COMM_MASK; 
           break;
        case ENABLE_I2C_E: 
           value = old_value & ~ COMM_MASK;
           break;
    }
  

    if (value != old_value)
        lps25h_write_register(CONTROL_REGISTER_2_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lps25h_get_comm
 *
 * RET  : Return the value of register 0xControlRegister2
 *
 * Notes : From register 0xB821, bits 3:3
 *
 **************************************************************************/
unsigned char lps25h_get_comm()
  {
    unsigned char value;


    /* 
     * 0: I2C enable;1: SPI disable 
     */ 
    value = (lps25h_read_register(CONTROL_REGISTER_2_REG) & COMM_MASK) >> 3;
    return value;
  }


/***************************************************************************
 *
 * Function : lps25h_set_ord_decimatione
 *
 * IN   : param, a value to write to the regiter ControlRegister2
 * OUT  : 
 *
 * RET  : Return the value of register 0xControlRegister2
 *
 * Notes : From register 0xB821, bits 4:4
 *
 **************************************************************************/
unsigned char lps25h_set_ord_decimatione( enum ord_decimation_enable param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lps25h_read_register(CONTROL_REGISTER_2_REG);

    /* 
     * Enable 1Hz ODR decimation 
     */ 
    switch( param ){
        case ORD_DECIMATION_ENABLE_E: 
           value = old_value | ORD_DECIMATIONE_MASK; 
           break;
        case ORD_DECIMATION_DISABLE_E: 
           value = old_value & ~ ORD_DECIMATIONE_MASK;
           break;
    }
  

    if (value != old_value)
        lps25h_write_register(CONTROL_REGISTER_2_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lps25h_get_ord_decimatione
 *
 * RET  : Return the value of register 0xControlRegister2
 *
 * Notes : From register 0xB821, bits 4:4
 *
 **************************************************************************/
unsigned char lps25h_get_ord_decimatione()
  {
    unsigned char value;


    /* 
     * Enable 1Hz ODR decimation 
     */ 
    value = (lps25h_read_register(CONTROL_REGISTER_2_REG) & ORD_DECIMATIONE_MASK) >> 4;
    return value;
  }


/***************************************************************************
 *
 * Function : lps25h_set_fifo_water_mark
 *
 * IN   : param, a value to write to the regiter ControlRegister2
 * OUT  : 
 *
 * RET  : Return the value of register 0xControlRegister2
 *
 * Notes : From register 0xB821, bits 5:5
 *
 **************************************************************************/
unsigned char lps25h_set_fifo_water_mark( enum fifo_water_mark_enable param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lps25h_read_register(CONTROL_REGISTER_2_REG);

    /* 
     * Enable FIFO Watermark level use 
     */ 
    switch( param ){
        case FIFO_WATER_MARK_ENABLE_E: 
           value = old_value | FIFO_WATER_MARK_MASK; 
           break;
        case FIFO_WATER_MARK_DISABLE_E: 
           value = old_value & ~ FIFO_WATER_MARK_MASK;
           break;
    }
  

    if (value != old_value)
        lps25h_write_register(CONTROL_REGISTER_2_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lps25h_get_fifo_water_mark
 *
 * RET  : Return the value of register 0xControlRegister2
 *
 * Notes : From register 0xB821, bits 5:5
 *
 **************************************************************************/
unsigned char lps25h_get_fifo_water_mark()
  {
    unsigned char value;


    /* 
     * Enable FIFO Watermark level use 
     */ 
    value = (lps25h_read_register(CONTROL_REGISTER_2_REG) & FIFO_WATER_MARK_MASK) >> 5;
    return value;
  }


/***************************************************************************
 *
 * Function : lps25h_set_fifo
 *
 * IN   : param, a value to write to the regiter ControlRegister2
 * OUT  : 
 *
 * RET  : Return the value of register 0xControlRegister2
 *
 * Notes : From register 0xB821, bits 6:6
 *
 **************************************************************************/
unsigned char lps25h_set_fifo( enum fifo_enable param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lps25h_read_register(CONTROL_REGISTER_2_REG);

    /* 
     * Enable FIFO 
     */ 
    switch( param ){
        case FIFO_ENABLE_E: 
           value = old_value | FIFO_MASK; 
           break;
        case FIFO_DISABLE_E: 
           value = old_value & ~ FIFO_MASK;
           break;
    }
  

    if (value != old_value)
        lps25h_write_register(CONTROL_REGISTER_2_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lps25h_get_fifo
 *
 * RET  : Return the value of register 0xControlRegister2
 *
 * Notes : From register 0xB821, bits 6:6
 *
 **************************************************************************/
unsigned char lps25h_get_fifo()
  {
    unsigned char value;


    /* 
     * Enable FIFO 
     */ 
    value = (lps25h_read_register(CONTROL_REGISTER_2_REG) & FIFO_MASK) >> 6;
    return value;
  }


/***************************************************************************
 *
 * Function : lps25h_set_reboot_memory_content
 *
 * IN   : param, a value to write to the regiter ControlRegister2
 * OUT  : 
 *
 * RET  : Return the value of register 0xControlRegister2
 *
 * Notes : From register 0xB821, bits 7:7
 *
 **************************************************************************/
unsigned char lps25h_set_reboot_memory_content( enum reboot_memory_content_enable param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lps25h_read_register(CONTROL_REGISTER_2_REG);

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
        lps25h_write_register(CONTROL_REGISTER_2_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lps25h_get_reboot_memory_content
 *
 * RET  : Return the value of register 0xControlRegister2
 *
 * Notes : From register 0xB821, bits 7:7
 *
 **************************************************************************/
unsigned char lps25h_get_reboot_memory_content()
  {
    unsigned char value;


    /* 
     * Reboot memory content. 
     */ 
    value = (lps25h_read_register(CONTROL_REGISTER_2_REG) & REBOOT_MEMORY_CONTENT_MASK) >> 7;
    return value;
  }


/***************************************************************************
 *
 * Function : lps25h_set_data_signal_on_int_pad
 *
 * IN   : param, a value to write to the regiter ControlRegister3
 * OUT  : 
 *
 * RET  : Return the value of register 0xControlRegister3
 *
 * Notes : From register 0xB822, bits 1:0
 *
 **************************************************************************/
unsigned char lps25h_set_data_signal_on_int_pad( enum data_signal_on_int param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lps25h_read_register(CONTROL_REGISTER_3_REG);

    /* 
     * data signal on INT1 pad control bit 
     */ 
  

     value =  old_value & ~DATA_SIGNAL_ON_INT_PAD_MASK ;

    switch(  param ){

           case DATA_SIGNAL_E:
                value =  value | DATA_SIGNAL ;
                break;
           case PRESSURE_HIGH_E:
                value =  value | PRESSURE_HIGH ;
                break;
           case PRESSURE_LOW_E:
                value =  value | PRESSURE_LOW ;
                break;
           case PRESSURE_HIGH_OR_PRESSURE_HIGH_E:
                value =  value | PRESSURE_HIGH_OR_PRESSURE_HIGH ;
                break;
    }
  

    if (value != old_value)
        lps25h_write_register(CONTROL_REGISTER_3_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lps25h_get_data_signal_on_int_pad
 *
 * RET  : Return the value of register 0xControlRegister3
 *
 * Notes : From register 0xB822, bits 1:0
 *
 **************************************************************************/
unsigned char lps25h_get_data_signal_on_int_pad()
  {
    unsigned char value;


    /* 
     * data signal on INT1 pad control bit 
     */ 
    value = (lps25h_read_register(CONTROL_REGISTER_3_REG) & DATA_SIGNAL_ON_INT_PAD_MASK);
    return value;
  }


/***************************************************************************
 *
 * Function : lps25h_set_open_drain_selection
 *
 * IN   : param, a value to write to the regiter ControlRegister3
 * OUT  : 
 *
 * RET  : Return the value of register 0xControlRegister3
 *
 * Notes : From register 0xB822, bits 6:6
 *
 **************************************************************************/
unsigned char lps25h_set_open_drain_selection( enum open_drain_enable param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lps25h_read_register(CONTROL_REGISTER_3_REG);

    /* 
     * Push-pull / Open Drain selection on pin 3. 
     */ 
    switch( param ){
        case OPEN_DRAIN_ENABLE_E: 
           value = old_value | OPEN_DRAIN_SELECTION_MASK; 
           break;
        case OPEN_DRAIN_DISABLE_E: 
           value = old_value & ~ OPEN_DRAIN_SELECTION_MASK;
           break;
    }
  

    if (value != old_value)
        lps25h_write_register(CONTROL_REGISTER_3_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lps25h_get_open_drain_selection
 *
 * RET  : Return the value of register 0xControlRegister3
 *
 * Notes : From register 0xB822, bits 6:6
 *
 **************************************************************************/
unsigned char lps25h_get_open_drain_selection()
  {
    unsigned char value;


    /* 
     * Push-pull / Open Drain selection on pin 3. 
     */ 
    value = (lps25h_read_register(CONTROL_REGISTER_3_REG) & OPEN_DRAIN_SELECTION_MASK) >> 6;
    return value;
  }


/***************************************************************************
 *
 * Function : lps25h_set_interrupt_level
 *
 * IN   : param, a value to write to the regiter ControlRegister3
 * OUT  : 
 *
 * RET  : Return the value of register 0xControlRegister3
 *
 * Notes : From register 0xB822, bits 7:7
 *
 **************************************************************************/
unsigned char lps25h_set_interrupt_level( enum level param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lps25h_read_register(CONTROL_REGISTER_3_REG);

    /* 
     * Interrupt active high. 0: active high; 1: active low 
     */ 
    switch( param ){
        case ACTIVE_LOW_E: 
           value = old_value | INTERRUPT_LEVEL_MASK; 
           break;
        case ACTIVE_HIGH_E: 
           value = old_value & ~ INTERRUPT_LEVEL_MASK;
           break;
    }
  

    if (value != old_value)
        lps25h_write_register(CONTROL_REGISTER_3_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lps25h_get_interrupt_level
 *
 * RET  : Return the value of register 0xControlRegister3
 *
 * Notes : From register 0xB822, bits 7:7
 *
 **************************************************************************/
unsigned char lps25h_get_interrupt_level()
  {
    unsigned char value;


    /* 
     * Interrupt active high. 0: active high; 1: active low 
     */ 
    value = (lps25h_read_register(CONTROL_REGISTER_3_REG) & INTERRUPT_LEVEL_MASK) >> 7;
    return value;
  }


/***************************************************************************
 *
 * Function : lps25h_set_data_ready_signal
 *
 * IN   : param, a value to write to the regiter ControlRegister4
 * OUT  : 
 *
 * RET  : Return the value of register 0xControlRegister4
 *
 * Notes : From register 0xB823, bits 0:0
 *
 **************************************************************************/
unsigned char lps25h_set_data_ready_signal( enum data_ready_enable param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lps25h_read_register(CONTROL_REGISTER_4_REG);

    /* 
     * Data ready Signal on INT1 pin. 
     */ 
    switch( param ){
        case DATA_READY_ENABLE_E: 
           value = old_value | DATA_READY_SIGNAL_MASK; 
           break;
        case DATA_READY_DISABLE_E: 
           value = old_value & ~ DATA_READY_SIGNAL_MASK;
           break;
    }
  

    if (value != old_value)
        lps25h_write_register(CONTROL_REGISTER_4_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lps25h_get_data_ready_signal
 *
 * RET  : Return the value of register 0xControlRegister4
 *
 * Notes : From register 0xB823, bits 0:0
 *
 **************************************************************************/
unsigned char lps25h_get_data_ready_signal()
  {
    unsigned char value;


    /* 
     * Data ready Signal on INT1 pin. 
     */ 
    value = (lps25h_read_register(CONTROL_REGISTER_4_REG) & DATA_READY_SIGNAL_MASK);
    return value;
  }


/***************************************************************************
 *
 * Function : lps25h_set_overrun_signal
 *
 * IN   : param, a value to write to the regiter ControlRegister4
 * OUT  : 
 *
 * RET  : Return the value of register 0xControlRegister4
 *
 * Notes : From register 0xB823, bits 1:1
 *
 **************************************************************************/
unsigned char lps25h_set_overrun_signal( enum overrunl_enable param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lps25h_read_register(CONTROL_REGISTER_4_REG);

    /* 
     * Overrun Signal on INT1 pin. 
     */ 
    switch( param ){
        case OVERRUNL_ENABLE_E: 
           value = old_value | OVERRUN_SIGNAL_MASK; 
           break;
        case OVERRUNL_DISABLE_E: 
           value = old_value & ~ OVERRUN_SIGNAL_MASK;
           break;
    }
  

    if (value != old_value)
        lps25h_write_register(CONTROL_REGISTER_4_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lps25h_get_overrun_signal
 *
 * RET  : Return the value of register 0xControlRegister4
 *
 * Notes : From register 0xB823, bits 1:1
 *
 **************************************************************************/
unsigned char lps25h_get_overrun_signal()
  {
    unsigned char value;


    /* 
     * Overrun Signal on INT1 pin. 
     */ 
    value = (lps25h_read_register(CONTROL_REGISTER_4_REG) & OVERRUN_SIGNAL_MASK) >> 1;
    return value;
  }


/***************************************************************************
 *
 * Function : lps25h_set_watermark_signal
 *
 * IN   : param, a value to write to the regiter ControlRegister4
 * OUT  : 
 *
 * RET  : Return the value of register 0xControlRegister4
 *
 * Notes : From register 0xB823, bits 2:2
 *
 **************************************************************************/
unsigned char lps25h_set_watermark_signal( enum watermark_enable param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lps25h_read_register(CONTROL_REGISTER_4_REG);

    /* 
     * Watermark Signal on INT1 pin. 
     */ 
    switch( param ){
        case WATERMARK_ENABLE_E: 
           value = old_value | WATERMARK_SIGNAL_MASK; 
           break;
        case WATERMARK_DISABLE_E: 
           value = old_value & ~ WATERMARK_SIGNAL_MASK;
           break;
    }
  

    if (value != old_value)
        lps25h_write_register(CONTROL_REGISTER_4_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lps25h_get_watermark_signal
 *
 * RET  : Return the value of register 0xControlRegister4
 *
 * Notes : From register 0xB823, bits 2:2
 *
 **************************************************************************/
unsigned char lps25h_get_watermark_signal()
  {
    unsigned char value;


    /* 
     * Watermark Signal on INT1 pin. 
     */ 
    value = (lps25h_read_register(CONTROL_REGISTER_4_REG) & WATERMARK_SIGNAL_MASK) >> 2;
    return value;
  }


/***************************************************************************
 *
 * Function : lps25h_set_empty_signal
 *
 * IN   : param, a value to write to the regiter ControlRegister4
 * OUT  : 
 *
 * RET  : Return the value of register 0xControlRegister4
 *
 * Notes : From register 0xB823, bits 3:3
 *
 **************************************************************************/
unsigned char lps25h_set_empty_signal( enum empty_signal_enable param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lps25h_read_register(CONTROL_REGISTER_4_REG);

    /* 
     * Empty Signal on INT1 pin. 
     */ 
    switch( param ){
        case EMPTY_SIGNAL_ENABLE_E: 
           value = old_value | EMPTY_SIGNAL_MASK; 
           break;
        case EMPTY_SIGNAL_DISABLE_E: 
           value = old_value & ~ EMPTY_SIGNAL_MASK;
           break;
    }
  

    if (value != old_value)
        lps25h_write_register(CONTROL_REGISTER_4_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lps25h_get_empty_signal
 *
 * RET  : Return the value of register 0xControlRegister4
 *
 * Notes : From register 0xB823, bits 3:3
 *
 **************************************************************************/
unsigned char lps25h_get_empty_signal()
  {
    unsigned char value;


    /* 
     * Empty Signal on INT1 pin. 
     */ 
    value = (lps25h_read_register(CONTROL_REGISTER_4_REG) & EMPTY_SIGNAL_MASK) >> 3;
    return value;
  }


/***************************************************************************
 *
 * Function : lps25h_set_pressure_high_event
 *
 * IN   : param, a value to write to the regiter InterruptConfiguration
 * OUT  : 
 *
 * RET  : Return the value of register 0xInterruptConfiguration
 *
 * Notes : From register 0xB824, bits 0:0
 *
 **************************************************************************/
unsigned char lps25h_set_pressure_high_event( enum pressure_high_event_enable param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lps25h_read_register(INTERRUPT_CONFIGURATION_REG);

    /* 
     * Enable interrupt generation on differential pressure high 
     * event 
     */ 
    switch( param ){
        case PRESSURE_HIGH_EVENT_ENABLE_E: 
           value = old_value | PRESSURE_HIGH_EVENT_MASK; 
           break;
        case PRESSURE_HIGH_EVENT_DISABLE_E: 
           value = old_value & ~ PRESSURE_HIGH_EVENT_MASK;
           break;
    }
  

    if (value != old_value)
        lps25h_write_register(INTERRUPT_CONFIGURATION_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lps25h_get_pressure_high_event
 *
 * RET  : Return the value of register 0xInterruptConfiguration
 *
 * Notes : From register 0xB824, bits 0:0
 *
 **************************************************************************/
unsigned char lps25h_get_pressure_high_event()
  {
    unsigned char value;


    /* 
     * Enable interrupt generation on differential pressure high 
     * event 
     */ 
    value = (lps25h_read_register(INTERRUPT_CONFIGURATION_REG) & PRESSURE_HIGH_EVENT_MASK);
    return value;
  }


/***************************************************************************
 *
 * Function : lps25h_set_pressure_low_event
 *
 * IN   : param, a value to write to the regiter InterruptConfiguration
 * OUT  : 
 *
 * RET  : Return the value of register 0xInterruptConfiguration
 *
 * Notes : From register 0xB824, bits 1:1
 *
 **************************************************************************/
unsigned char lps25h_set_pressure_low_event( enum pressure_low_event_enable param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lps25h_read_register(INTERRUPT_CONFIGURATION_REG);

    /* 
     * Enable interrupt generation on differential pressure low 
     * event 
     */ 
    switch( param ){
        case PRESSURE_LOW_EVENT_ENABLE_E: 
           value = old_value | PRESSURE_LOW_EVENT_MASK; 
           break;
        case PRESSURE_LOW_EVENT_DISABLE_E: 
           value = old_value & ~ PRESSURE_LOW_EVENT_MASK;
           break;
    }
  

    if (value != old_value)
        lps25h_write_register(INTERRUPT_CONFIGURATION_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lps25h_get_pressure_low_event
 *
 * RET  : Return the value of register 0xInterruptConfiguration
 *
 * Notes : From register 0xB824, bits 1:1
 *
 **************************************************************************/
unsigned char lps25h_get_pressure_low_event()
  {
    unsigned char value;


    /* 
     * Enable interrupt generation on differential pressure low 
     * event 
     */ 
    value = (lps25h_read_register(INTERRUPT_CONFIGURATION_REG) & PRESSURE_LOW_EVENT_MASK) >> 1;
    return value;
  }


/***************************************************************************
 *
 * Function : lps25h_set_interrupt_request_event
 *
 * IN   : param, a value to write to the regiter InterruptConfiguration
 * OUT  : 
 *
 * RET  : Return the value of register 0xInterruptConfiguration
 *
 * Notes : From register 0xB824, bits 2:2
 *
 **************************************************************************/
unsigned char lps25h_set_interrupt_request_event( enum latch_interrupt param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lps25h_read_register(INTERRUPT_CONFIGURATION_REG);

    /* 
     * Latch Interrupt request into INT_SOURCE register. 
     */ 
    switch( param ){
        case INTERRUPT_LATCHED_E: 
           value = old_value | INTERRUPT_REQUEST_EVENT_MASK; 
           break;
        case INTERRUPT_NOT_LATCHED_E: 
           value = old_value & ~ INTERRUPT_REQUEST_EVENT_MASK;
           break;
    }
  

    if (value != old_value)
        lps25h_write_register(INTERRUPT_CONFIGURATION_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lps25h_get_interrupt_request_event
 *
 * RET  : Return the value of register 0xInterruptConfiguration
 *
 * Notes : From register 0xB824, bits 2:2
 *
 **************************************************************************/
unsigned char lps25h_get_interrupt_request_event()
  {
    unsigned char value;


    /* 
     * Latch Interrupt request into INT_SOURCE register. 
     */ 
    value = (lps25h_read_register(INTERRUPT_CONFIGURATION_REG) & INTERRUPT_REQUEST_EVENT_MASK) >> 2;
    return value;
  }


/***************************************************************************
 *
 * Function : lps25h_get_differential_pressure_high
 *
 * RET  : Return the value of register 0xInterruptSource
 *
 * Notes : From register 0xB825, bits 0:0
 *
 **************************************************************************/
unsigned char lps25h_get_differential_pressure_high()
  {
    unsigned char value;


    /* 
     * High differential pressure event has occurred 
     */ 
    value = (lps25h_read_register(INTERRUPT_SOURCE_REG) & DIFFERENTIAL_PRESSURE_HIGH_MASK);
    return value;
  }


/***************************************************************************
 *
 * Function : lps25h_get_differential_pressure_low
 *
 * RET  : Return the value of register 0xInterruptSource
 *
 * Notes : From register 0xB825, bits 1:1
 *
 **************************************************************************/
unsigned char lps25h_get_differential_pressure_low()
  {
    unsigned char value;


    /* 
     * 0: no interrupt has been generated; 1: one or more 
     * interrupt events have been generated. 
     */ 
    value = (lps25h_read_register(INTERRUPT_SOURCE_REG) & DIFFERENTIAL_PRESSURE_LOW_MASK) >> 1;
    return value;
  }


/***************************************************************************
 *
 * Function : lps25h_get_interrupt_active
 *
 * RET  : Return the value of register 0xInterruptSource
 *
 * Notes : From register 0xB825, bits 2:2
 *
 **************************************************************************/
unsigned char lps25h_get_interrupt_active()
  {
    unsigned char value;


    /* 
     * 0: no interrupt has been generated; 1: one or more 
     * interrupt events have been generated. 
     */ 
    value = (lps25h_read_register(INTERRUPT_SOURCE_REG) & INTERRUPT_ACTIVE_MASK) >> 2;
    return value;
  }


/***************************************************************************
 *
 * Function : lps25h_get_temperature_data_available
 *
 * RET  : Return the value of register 0xStatusRegister
 *
 * Notes : From register 0xB827, bits 0:0
 *
 **************************************************************************/
unsigned char lps25h_get_temperature_data_available()
  {
    unsigned char value;


    /* 
     * Temperature data available. T_DA is set to 1 whenever a 
     * new Temperature sample is available. T_DA is cleared 
     * anytime TEMPERATURE_OUT_H register is read. 
     */ 
    value = (lps25h_read_register(STATUS_REGISTER_REG) & TEMPERATURE_DATA_AVAILABLE_MASK);
    return value;
  }


/***************************************************************************
 *
 * Function : lps25h_get_pressure_data_available
 *
 * RET  : Return the value of register 0xStatusRegister
 *
 * Notes : From register 0xB827, bits 1:1
 *
 **************************************************************************/
unsigned char lps25h_get_pressure_data_available()
  {
    unsigned char value;


    /* 
     * Pressure data available. 
     */ 
    value = (lps25h_read_register(STATUS_REGISTER_REG) & PRESSURE_DATA_AVAILABLE_MASK) >> 1;
    return value;
  }


/***************************************************************************
 *
 * Function : lps25h_get_temperature_data_overrun
 *
 * RET  : Return the value of register 0xStatusRegister
 *
 * Notes : From register 0xB827, bits 4:4
 *
 **************************************************************************/
unsigned char lps25h_get_temperature_data_overrun()
  {
    unsigned char value;


    /* 
     * Temperature data overrun 
     */ 
    value = (lps25h_read_register(STATUS_REGISTER_REG) & TEMPERATURE_DATA_OVERRUN_MASK) >> 4;
    return value;
  }


/***************************************************************************
 *
 * Function : lps25h_get_pressure_data_overrun
 *
 * RET  : Return the value of register 0xStatusRegister
 *
 * Notes : From register 0xB827, bits 5:5
 *
 **************************************************************************/
unsigned char lps25h_get_pressure_data_overrun()
  {
    unsigned char value;


    /* 
     * Pressure data overrun 
     */ 
    value = (lps25h_read_register(STATUS_REGISTER_REG) & PRESSURE_DATA_OVERRUN_MASK) >> 5;
    return value;
  }


/***************************************************************************
 *
 * Function : lps25h_get_pressure_data_x_lsb
 *
 * RET  : Return the value of register 0xPressureDataXLsb
 *
 * Notes : From register 0xB828, bits 7:0
 *
 **************************************************************************/
unsigned char lps25h_get_pressure_data_x_lsb()
  {
    unsigned char value;


    /* 
     * Pressure data LSB 
     */ 
    value = lps25h_read_register(PRESSURE_DATA_X_LSB_REG);
    return value;
  }


/***************************************************************************
 *
 * Function : lps25h_get_pressure_data_lsb
 *
 * RET  : Return the value of register 0xPressureDataLsb
 *
 * Notes : From register 0xB829, bits 7:0
 *
 **************************************************************************/
unsigned char lps25h_get_pressure_data_lsb()
  {
    unsigned char value;


    /* 
     * Pressure data Middle 
     */ 
    value = lps25h_read_register(PRESSURE_DATA_LSB_REG);
    return value;
  }


/***************************************************************************
 *
 * Function : lps25h_get_pressure_data_msb
 *
 * RET  : Return the value of register 0xPressureDataMsb
 *
 * Notes : From register 0xB82A, bits 7:0
 *
 **************************************************************************/
unsigned char lps25h_get_pressure_data_msb()
  {
    unsigned char value;


    /* 
     * Pressure data MSB 
     */ 
    value = lps25h_read_register(PRESSURE_DATA_MSB_REG);
    return value;
  }


/***************************************************************************
 *
 * Function : lps25h_get_temperature_data_msb
 *
 * RET  : Return the value of register 0xTemperatureDataMsb
 *
 * Notes : From register 0xB82B, bits 7:0
 *
 **************************************************************************/
unsigned char lps25h_get_temperature_data_msb()
  {
    unsigned char value;


    /* 
     * Temperature data LSB 
     */ 
    value = lps25h_read_register(TEMPERATURE_DATA_MSB_REG);
    return value;
  }


/***************************************************************************
 *
 * Function : lps25h_get_temperature_data_lsb
 *
 * RET  : Return the value of register 0xTemperatureDataLsb
 *
 * Notes : From register 0xB82C, bits 7:0
 *
 **************************************************************************/
unsigned char lps25h_get_temperature_data_lsb()
  {
    unsigned char value;


    /* 
     * Temperature data MSB 
     */ 
    value = lps25h_read_register(TEMPERATURE_DATA_LSB_REG);
    return value;
  }


/***************************************************************************
 *
 * Function : lps25h_set_fifo_threshold_level
 *
 * IN   : param, a value to write to the regiter FifoControl
 * OUT  : 
 *
 * RET  : Return the value of register 0xFifoControl
 *
 * Notes : From register 0xB82E, bits 4:0
 *
 **************************************************************************/
unsigned char lps25h_set_fifo_threshold_level( enum fifo_threshold param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lps25h_read_register(FIFO_CONTROL_REG);

    /* 
     * FFIFO threshold.Watermark level setting 
     */ 
  

     value =  old_value & ~FIFO_THRESHOLD_LEVEL_MASK ;

    switch(  param ){

           case WATERMARK_2_SAMPLES_MOVING_AVERAGE_E:
                value =  value | WATERMARK_2_SAMPLES_MOVING_AVERAGE ;
                break;
           case WATERMARK_4_SAMPLES_MOVING_AVERAGE_E:
                value =  value | WATERMARK_4_SAMPLES_MOVING_AVERAGE ;
                break;
           case WATERMARK_8_SAMPLES_MOVING_AVERAGE_E:
                value =  value | WATERMARK_8_SAMPLES_MOVING_AVERAGE ;
                break;
           case WATERMARK_16_SAMPLES_MOVING_AVERAGE_E:
                value =  value | WATERMARK_16_SAMPLES_MOVING_AVERAGE ;
                break;
           case WATERMARK_32_SAMPLES_MOVING_AVERAGE_E:
                value =  value | WATERMARK_32_SAMPLES_MOVING_AVERAGE ;
                break;
    }
  

    if (value != old_value)
        lps25h_write_register(FIFO_CONTROL_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lps25h_get_fifo_threshold_level
 *
 * RET  : Return the value of register 0xFifoControl
 *
 * Notes : From register 0xB82E, bits 4:0
 *
 **************************************************************************/
unsigned char lps25h_get_fifo_threshold_level()
  {
    unsigned char value;


    /* 
     * FFIFO threshold.Watermark level setting 
     */ 
    value = (lps25h_read_register(FIFO_CONTROL_REG) & FIFO_THRESHOLD_LEVEL_MASK);
    return value;
  }


/***************************************************************************
 *
 * Function : lps25h_set_fifo_mode_selection
 *
 * IN   : param, a value to write to the regiter FifoControl
 * OUT  : 
 *
 * RET  : Return the value of register 0xFifoControl
 *
 * Notes : From register 0xB82E, bits 7:5
 *
 **************************************************************************/
unsigned char lps25h_set_fifo_mode_selection( enum fifo_mode_selection param )
  {
    unsigned char value = 0;
    unsigned char old_value;

    old_value = lps25h_read_register(FIFO_CONTROL_REG);

    /* 
     * FIFO mode selection 
     */ 
  

     value =  old_value & ~FIFO_MODE_SELECTION_MASK ;

    switch(  param ){

           case BYPASS_E:
                value  = value  | (BYPASS << 0x5);
                break;
           case MODE_E:
                value  = value  | (MODE << 0x5);
                break;
           case STOPS_WHEN_FULL_E:
                value  = value  | (STOPS_WHEN_FULL << 0x5);
                break;
           case KEEP_THE_NEWEST_DATA_E:
                value  = value  | (KEEP_THE_NEWEST_DATA << 0x5);
                break;
           case STREAM_MODE_CHANGE_TO_FIFO_E:
                value  = value  | (STREAM_MODE_CHANGE_TO_FIFO << 0x5);
                break;
           case MODE_BYPASS_E:
                value  = value  | (MODE_BYPASS << 0x5);
                break;
           case MODE_CHANGE_TO_STREAM_E:
                value  = value  | (MODE_CHANGE_TO_STREAM << 0x5);
                break;
           case MODE_RESERVED_FOR_FUTURE_USE_E:
                value  = value  | (MODE_RESERVED_FOR_FUTURE_USE << 0x5);
                break;
           case FIFO_MEAN_E:
                value  = value  | (FIFO_MEAN << 0x5);
                break;
           case MODE_BYPASS_MODE_THEN_CHANGE_TO_FIFO_MODE_E:
                value  = value  | (MODE_BYPASS_MODE_THEN_CHANGE_TO_FIFO_MODE << 0x5);
                break;
    }
  

    if (value != old_value)
        lps25h_write_register(FIFO_CONTROL_REG, value);

    return old_value;
  }


/***************************************************************************
 *
 * Function : lps25h_get_fifo_mode_selection
 *
 * RET  : Return the value of register 0xFifoControl
 *
 * Notes : From register 0xB82E, bits 7:5
 *
 **************************************************************************/
unsigned char lps25h_get_fifo_mode_selection()
  {
    unsigned char value;


    /* 
     * FIFO mode selection 
     */ 
    value = (lps25h_read_register(FIFO_CONTROL_REG) & FIFO_MODE_SELECTION_MASK) >> 5;
    return value;
  }


/***************************************************************************
 *
 * Function : lps25h_get_fifo_status
 *
 * RET  : Return the value of register 0xFifoStatus
 *
 * Notes : From register 0xB82F, bits 7:0
 *
 **************************************************************************/
unsigned char lps25h_get_fifo_status()
  {
    unsigned char value;


    /* 
     * FIFO Status 
     */ 
    value = lps25h_read_register(FIFO_STATUS_REG);
    return value;
  }


/***************************************************************************
 *
 * Function : lps25h_get_threshold_pressure_lsb
 *
 * RET  : Return the value of register 0xThresholdPressureLsb
 *
 * Notes : From register 0xB830, bits 7:0
 *
 **************************************************************************/
unsigned char lps25h_get_threshold_pressure_lsb()
  {
    unsigned char value;


    /* 
     * Threshold value for pressure interrupt LSB 
     */ 
    value = lps25h_read_register(THRESHOLD_PRESSURE_LSB_REG);
    return value;
  }


/***************************************************************************
 *
 * Function : lps25h_get_threshold_pressure_msb
 *
 * RET  : Return the value of register 0xThresholdPressureMsb
 *
 * Notes : From register 0xB831, bits 7:0
 *
 **************************************************************************/
unsigned char lps25h_get_threshold_pressure_msb()
  {
    unsigned char value;


    /* 
     * Threshold value for pressure interrupt MSB 
     */ 
    value = lps25h_read_register(THRESHOLD_PRESSURE_MSB_REG);
    return value;
  }


/***************************************************************************
 *
 * Function : lps25h_get_final_threshold_pressure_lsb
 *
 * RET  : Return the value of register 0xFinalThresholdPressureLsb
 *
 * Notes : From register 0xB839, bits 7:0
 *
 **************************************************************************/
unsigned char lps25h_get_final_threshold_pressure_lsb()
  {
    unsigned char value;


    /* 
     * Pressure offset value after soldering differential 
     * pressure computing LSB 
     */ 
    value = lps25h_read_register(FINAL_THRESHOLD_PRESSURE_LSB_REG);
    return value;
  }


/***************************************************************************
 *
 * Function : lps25h_get_final_threshold_pressure_msb
 *
 * RET  : Return the value of register 0xFinalThresholdPressureMsb
 *
 * Notes : From register 0xB83A, bits 7:0
 *
 **************************************************************************/
unsigned char lps25h_get_final_threshold_pressure_msb()
  {
    unsigned char value;


    /* 
     * Pressure offset value after soldering differential 
     * pressure computing MSB 
     */ 
    value = lps25h_read_register(FINAL_THRESHOLD_PRESSURE_MSB_REG);
    return value;
  }




#ifdef __cplusplus
}
#endif

#endif
