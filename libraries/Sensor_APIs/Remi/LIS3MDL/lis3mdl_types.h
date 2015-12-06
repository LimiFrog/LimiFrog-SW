/****************************************************************************
 * File : c:/Lisp/Production/sensors_st/sensors_st_lis3mdl/Linux/lis3mdl_types.h
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

#ifndef C__LISP_PRODUCTION_SENSORS_ST_SENSORS_ST_LIS3MDL_LINUX_LIS3MDL_TYPES_H
#define C__LISP_PRODUCTION_SENSORS_ST_SENSORS_ST_LIS3MDL_LINUX_LIS3MDL_TYPES_H


#ifdef __cplusplus
extern "C" {
#endif


#define WHO_IAM_REG 0xF

//  
//  ST Self-test enable.0: self-test disabled; 1: self-test enabled.
//  Register ControlRegister1 0x0020, Bits 0:0, typedef self_test_enable
//   
//  
#define SELF_TEST_MASK 0x1U
#define SELF_TEST_OFFSET 0
#define SELF_TEST_STOP_BIT 0
#define SELF_TEST_START_BIT 0
#define SELF_TEST_WIDTH 1

#define CONTROL_REGISTER_1_REG 0x20

typedef enum self_test_enable {
    SELF_TEST_DISABLE_E,
    SELF_TEST_ENABLE_E
} SELF_TEST_ENABLE_T ;
#define SELF_TEST_PARAM_MASK  0x1



//  
//  FAST_ODR enables data rates higher than 80 Hz.
//  Register ControlRegister1 0x0020, Bits 1:1, typedef fast_mode_enable
//   
//  
#define FAST_DATA_RATE_MASK 0x2U
#define FAST_DATA_RATE_OFFSET 1
#define FAST_DATA_RATE_STOP_BIT 1
#define FAST_DATA_RATE_START_BIT 1
#define FAST_DATA_RATE_WIDTH 1


typedef enum fast_mode_enable {
    FAST_MODE_DISABLE_E,
    FAST_MODE_ENABLE_E
} FAST_MODE_ENABLE_T ;
#define FAST_DATA_RATE_PARAM_MASK  0x2



//  
//  output data rate selection.
//  Register ControlRegister1 0x0020, Bits 2:4, typedef data_rate
//   
//  
#define DATA_RATE_MASK 0x1CU
#define DATA_RATE_OFFSET 4
#define DATA_RATE_STOP_BIT 4
#define DATA_RATE_START_BIT 2
#define DATA_RATE_WIDTH 3

#define  DATA_RATE_0_625_HZ 0
#define  DATA_RATE_1_25_HZ 1
#define  DATA_RATE_2_5_HZ 2
#define  DATA_RATE_5_HZ 3
#define  DATA_RATE_10_HZ 4
#define  DATA_RATE_20_HZ 5
#define  DATA_RATE_40_HZ 6
#define  DATA_RATE1_80_HZ 7

typedef enum data_rate {
    DATA_RATE_0_625_HZ_E,
    DATA_RATE_1_25_HZ_E,
    DATA_RATE_2_5_HZ_E,
    DATA_RATE_5_HZ_E,
    DATA_RATE_10_HZ_E,
    DATA_RATE_20_HZ_E,
    DATA_RATE_40_HZ_E,
    DATA_RATE1_80_HZ_E
} DATA_RATE_T ;
#define DATA_RATE_PARAM_MASK  0x1C



//  
//  X and Y axes operative mode selection.
//  Register ControlRegister1 0x0020, Bits 5:6, typedef operative_mode_selection
//   
//  
#define OPERATIVE_MODE_SELECTION_MASK 0x60U
#define OPERATIVE_MODE_SELECTION_OFFSET 6
#define OPERATIVE_MODE_SELECTION_STOP_BIT 6
#define OPERATIVE_MODE_SELECTION_START_BIT 5
#define OPERATIVE_MODE_SELECTION_WIDTH 2


typedef enum operative_mode_selection {
    OPERATIVE_MODE_UN_SELECT_E,
    OPERATIVE_MODE_SELECT_E
} OPERATIVE_MODE_SELECTION_T ;
#define OPERATIVE_MODE_SELECTION_PARAM_MASK  0x60



//  
//  Temperature sensor enable.
//  Register ControlRegister1 0x0020, Bits 7:7, typedef temperature_sensor_enable
//   
//  
#define TEMPERATURE_SENSOR_MASK 0x80U
#define TEMPERATURE_SENSOR_OFFSET 7
#define TEMPERATURE_SENSOR_STOP_BIT 7
#define TEMPERATURE_SENSOR_START_BIT 7
#define TEMPERATURE_SENSOR_WIDTH 1


typedef enum temperature_sensor_enable {
    TEMPERATURE_SENSOR_DISABLE_E,
    TEMPERATURE_SENSOR_ENABLE_E
} TEMPERATURE_SENSOR_ENABLE_T ;
#define TEMPERATURE_SENSOR_PARAM_MASK  0x80



//  
//  Software Reset Enable..
//  Register ControlRegister2 0x0021, Bits 0:0, typedef software_reset_enable
//   
//  
#define SOFTWARE_RESET_MASK 0x1U
#define SOFTWARE_RESET_OFFSET 0
#define SOFTWARE_RESET_STOP_BIT 0
#define SOFTWARE_RESET_START_BIT 0
#define SOFTWARE_RESET_WIDTH 1

#define CONTROL_REGISTER_2_REG 0x21

typedef enum software_reset_enable {
    SOFTWARE_RESET_DISABLE_E,
    SOFTWARE_RESET_ENABLE_E
} SOFTWARE_RESET_ENABLE_T ;
#define SOFTWARE_RESET_PARAM_MASK  0x1



//  
//  Reboot memory content..
//  Register ControlRegister2 0x0021, Bits 4:4, typedef reboot_memory_content_enable
//   
//  
#define REBOOT_MEMORY_CONTENT_MASK 0x10U
#define REBOOT_MEMORY_CONTENT_OFFSET 4
#define REBOOT_MEMORY_CONTENT_STOP_BIT 4
#define REBOOT_MEMORY_CONTENT_START_BIT 4
#define REBOOT_MEMORY_CONTENT_WIDTH 1


typedef enum reboot_memory_content_enable {
    REBOOT_MEMORY_CONTENT_DISABLE_E,
    REBOOT_MEMORY_CONTENT_ENABLE_E
} REBOOT_MEMORY_CONTENT_ENABLE_T ;
#define REBOOT_MEMORY_CONTENT_PARAM_MASK  0x10



//  
//  Full-scale selection.
//  Register ControlRegister2 0x0021, Bits 5:6, typedef full_scale
//   
//  
#define FULL_SCALE_MASK 0x60U
#define FULL_SCALE_OFFSET 6
#define FULL_SCALE_STOP_BIT 6
#define FULL_SCALE_START_BIT 5
#define FULL_SCALE_WIDTH 2


typedef enum full_scale {
    FullScale_0_E,
    FullScale_1_E
} FULL_SCALE_T ;
#define FULL_SCALE_PARAM_MASK  0x60



//  
//  Operating mode selection.
//  Register ControlRegister3 0x0022, Bits 0:1, typedef operating_mode
//   
//  
#define OPERATING_MODE_MASK 0x3U
#define OPERATING_MODE_OFFSET 1
#define OPERATING_MODE_STOP_BIT 1
#define OPERATING_MODE_START_BIT 0
#define OPERATING_MODE_WIDTH 2

#define CONTROL_REGISTER_3_REG 0x22
#define  CONTINUOUS_CONVERSION_MODE 0
#define  SINGLE_CONVERSION_MODE 1
#define  POWER_DOWN_MODE 2

typedef enum operating_mode {
    CONTINUOUS_CONVERSION_MODE_E,
    SINGLE_CONVERSION_MODE_E,
    POWER_DOWN_MODE_E
} OPERATING_MODE_T ;
#define OPERATING_MODE_PARAM_MASK  0x3



//  
//  SPI serial interface mode selection.
//  Register ControlRegister3 0x0022, Bits 2:2, typedef spi_mode
//   
//  
#define SPI_MODE_MASK 0x4U
#define SPI_MODE_OFFSET 2
#define SPI_MODE_STOP_BIT 2
#define SPI_MODE_START_BIT 2
#define SPI_MODE_WIDTH 1


typedef enum spi_mode {
    SPI_4_wire_interface_E,
    SPI_3_wire_interface_E
} SPI_MODE_T ;
#define SPI_MODE_PARAM_MASK  0x4



//  
//  Big/Little Endian data selection.
//  Register ControlRegister4 0x0023, Bits 1:1, typedef big_endian_mode
//   
//  
#define BIG_ENDIAN_MODE_MASK 0x2U
#define BIG_ENDIAN_MODE_OFFSET 1
#define BIG_ENDIAN_MODE_STOP_BIT 1
#define BIG_ENDIAN_MODE_START_BIT 1
#define BIG_ENDIAN_MODE_WIDTH 1

#define CONTROL_REGISTER_4_REG 0x23

typedef enum big_endian_mode {
    LITTLE_ENDIAN_DATA_E,
    BIG_ENDIAN_DATA_E
} BIG_ENDIAN_MODE_T ;
#define BIG_ENDIAN_MODE_PARAM_MASK  0x2



//  
//  Z-axis operative mode selection..
//  Register ControlRegister4 0x0023, Bits 2:3, typedef axisz_mod
//   
//  
#define AXISZ_MOD_MASK 0xCU
#define AXISZ_MOD_OFFSET 3
#define AXISZ_MOD_STOP_BIT 3
#define AXISZ_MOD_START_BIT 2
#define AXISZ_MOD_WIDTH 2


typedef enum axisz_mod {
    AXISZ_MOD_0_E,
    AXISZ_MOD_1_E
} AXISZ_MOD_T ;
#define AXISZ_MOD_PARAM_MASK  0xC



//  
//  Block data update for magnetic data. 
//  0: continuous update 
//  1: output registers not updated until MSb and LSb have been read.
//  Register ControlRegister5 0x0024, Bits 6:6, typedef update_data_mode
//   
//  
#define UPDATE_DATA_MODE_MASK 0x40U
#define UPDATE_DATA_MODE_OFFSET 6
#define UPDATE_DATA_MODE_STOP_BIT 6
#define UPDATE_DATA_MODE_START_BIT 6
#define UPDATE_DATA_MODE_WIDTH 1

#define CONTROL_REGISTER_5_REG 0x24

typedef enum update_data_mode {
    CONTINIOUS_UPDATE_E,
    UPDATE_WHEN_DATA_READED_E
} UPDATE_DATA_MODE_T ;
#define UPDATE_DATA_MODE_PARAM_MASK  0x40



//  
//  allows reading the high part of DATA OUT only in order to increase reading 
//  efficiency.
//  Register ControlRegister5 0x0024, Bits 7:7, typedef fast_read_enable
//   
//  
#define FAST_READ_MASK 0x80U
#define FAST_READ_OFFSET 7
#define FAST_READ_STOP_BIT 7
#define FAST_READ_START_BIT 7
#define FAST_READ_WIDTH 1


typedef enum fast_read_enable {
    FAST_READ_DISABLE_E,
    FAST_READ_ENABLE_E
} FAST_READ_ENABLE_T ;
#define FAST_READ_PARAM_MASK  0x80



//  
//  X-axis new data available..
//  Register StatusRegister 0x0027, Bits 0:0, typedef data_x_ready
//   
//  
#define DATA_X_READY_MASK 0x1U
#define DATA_X_READY_OFFSET 0
#define DATA_X_READY_STOP_BIT 0
#define DATA_X_READY_START_BIT 0
#define DATA_X_READY_WIDTH 1

#define STATUS_REGISTER_REG 0x27

#define DATA_X_READY_PARAM_MASK  0x1



//  
//  Y-axis new data available..
//  Register StatusRegister 0x0027, Bits 1:1, typedef data_y_ready
//   
//  
#define DATA_Y_READY_MASK 0x2U
#define DATA_Y_READY_OFFSET 1
#define DATA_Y_READY_STOP_BIT 1
#define DATA_Y_READY_START_BIT 1
#define DATA_Y_READY_WIDTH 1


#define DATA_Y_READY_PARAM_MASK  0x2



//  
//  Y-axis new data available..
//  Register StatusRegister 0x0027, Bits 2:2, typedef data_z_ready
//   
//  
#define DATA_Z_READY_MASK 0x4U
#define DATA_Z_READY_OFFSET 2
#define DATA_Z_READY_STOP_BIT 2
#define DATA_Z_READY_START_BIT 2
#define DATA_Z_READY_WIDTH 1


#define DATA_Z_READY_PARAM_MASK  0x4



//  
//  X-, Y- and Z-axis new data available.
//  Register StatusRegister 0x0027, Bits 3:3, typedef data_ready
//   
//  
#define DATA_READY_MASK 0x8U
#define DATA_READY_OFFSET 3
#define DATA_READY_STOP_BIT 3
#define DATA_READY_START_BIT 3
#define DATA_READY_WIDTH 1


#define DATA_READY_PARAM_MASK  0x8



//  
//  X-axis data overrun.
//  Register StatusRegister 0x0027, Bits 4:4, typedef data_x_overrun
//   
//  
#define DATA_X_OVERRUN_MASK 0x10U
#define DATA_X_OVERRUN_OFFSET 4
#define DATA_X_OVERRUN_STOP_BIT 4
#define DATA_X_OVERRUN_START_BIT 4
#define DATA_X_OVERRUN_WIDTH 1


#define DATA_X_OVERRUN_PARAM_MASK  0x10



//  
//  Y-axis data overrun.
//  Register StatusRegister 0x0027, Bits 5:5, typedef data_y_overrun
//   
//  
#define DATA_Y_OVERRUN_MASK 0x20U
#define DATA_Y_OVERRUN_OFFSET 5
#define DATA_Y_OVERRUN_STOP_BIT 5
#define DATA_Y_OVERRUN_START_BIT 5
#define DATA_Y_OVERRUN_WIDTH 1


#define DATA_Y_OVERRUN_PARAM_MASK  0x20



//  
//  Z-axis data overrun.
//  Register StatusRegister 0x0027, Bits 6:6, typedef data_z_overrun
//   
//  
#define DATA_Z_OVERRUN_MASK 0x40U
#define DATA_Z_OVERRUN_OFFSET 6
#define DATA_Z_OVERRUN_STOP_BIT 6
#define DATA_Z_OVERRUN_START_BIT 6
#define DATA_Z_OVERRUN_WIDTH 1


#define DATA_Z_OVERRUN_PARAM_MASK  0x40



//  
//  X-, Y- and Z-axis data overrun.
//  Register StatusRegister 0x0027, Bits 7:7, typedef data_overrun
//   
//  
#define DATA_OVERRUN_MASK 0x80U
#define DATA_OVERRUN_OFFSET 7
#define DATA_OVERRUN_STOP_BIT 7
#define DATA_OVERRUN_START_BIT 7
#define DATA_OVERRUN_WIDTH 1


typedef enum data_overrun {
    DataOverrun_0_E,
    DataOverrun_1_E
} DATA_OVERRUN_T ;
#define DATA_OVERRUN_PARAM_MASK  0x80



#define MAGNETO_X_LOW_REG 0x28

#define MAGNETO_X_HIGH_REG 0x29

#define MAGNETO_Y_LOW_REG 0x2A

#define MAGNETO_Y_HIGH_REG 0x2B

#define MAGNETO_Z_LOW_REG 0x2C

#define MAGNETO_Z_HIGH_REG 0x2D

#define TEMPERATURE_DATA_LSB_REG 0x2E

#define TEMPERATURE_DATA_MSB_REG 0x2F

//  
//  Interrupt enable on INT pin.
//  Register InterruptConfig 0x0030, Bits 0:0, typedef interrupt_pin_enable
//   
//  
#define INTERRUPT_PIN_MASK 0x1U
#define INTERRUPT_PIN_OFFSET 0
#define INTERRUPT_PIN_STOP_BIT 0
#define INTERRUPT_PIN_START_BIT 0
#define INTERRUPT_PIN_WIDTH 1

#define INTERRUPT_CONFIG_REG 0x30

typedef enum interrupt_pin_enable {
    INTERRUPT_PIN_DISABLE_E,
    INTERRUPT_PIN_ENABLE_E
} INTERRUPT_PIN_ENABLE_T ;
#define INTERRUPT_PIN_PARAM_MASK  0x1



//  
//  Latch interrupt request.
//  Register InterruptConfig 0x0030, Bits 1:1, typedef latch_interrupt_request
//   
//  
#define LATCH_INTERRUPT_REQUEST_MASK 0x2U
#define LATCH_INTERRUPT_REQUEST_OFFSET 1
#define LATCH_INTERRUPT_REQUEST_STOP_BIT 1
#define LATCH_INTERRUPT_REQUEST_START_BIT 1
#define LATCH_INTERRUPT_REQUEST_WIDTH 1


typedef enum latch_interrupt_request {
    INACTIVE_E,
    EDGE_DETECTED_E
} LATCH_INTERRUPT_REQUEST_T ;
#define LATCH_INTERRUPT_REQUEST_PARAM_MASK  0x2



//  
//  Interrupt active configuration on INT.
//  Register InterruptConfig 0x0030, Bits 2:2, typedef interrupt_enable
//   
//  
#define INTERRUPT_MASK 0x4U
#define INTERRUPT_OFFSET 2
#define INTERRUPT_STOP_BIT 2
#define INTERRUPT_START_BIT 2
#define INTERRUPT_WIDTH 1


typedef enum interrupt_enable {
    INTERRUPT_DISABLE_E,
    INTERRUPT_ENABLE_E
} INTERRUPT_ENABLE_T ;
#define INTERRUPT_PARAM_MASK  0x4



//  
//  Enable interrupt generation on Z-axise.
//  Register InterruptConfig 0x0030, Bits 5:5, typedef interrupt_z_axise_enable
//   
//  
#define INTERRUPT_Z_AXISE_MASK 0x20U
#define INTERRUPT_Z_AXISE_OFFSET 5
#define INTERRUPT_Z_AXISE_STOP_BIT 5
#define INTERRUPT_Z_AXISE_START_BIT 5
#define INTERRUPT_Z_AXISE_WIDTH 1


typedef enum interrupt_z_axise_enable {
    INTERRUPT_Z_AXISE_DISABLE_E,
    INTERRUPT_Z_AXISE_ENABLE_E
} INTERRUPT_Z_AXISE_ENABLE_T ;
#define INTERRUPT_Z_AXISE_PARAM_MASK  0x20



//  
//  Enable interrupt generation on Y-axise.
//  Register InterruptConfig 0x0030, Bits 6:6, typedef interrupt_y_axise_enable
//   
//  
#define INTERRUPT_Y_AXISE_MASK 0x40U
#define INTERRUPT_Y_AXISE_OFFSET 6
#define INTERRUPT_Y_AXISE_STOP_BIT 6
#define INTERRUPT_Y_AXISE_START_BIT 6
#define INTERRUPT_Y_AXISE_WIDTH 1


typedef enum interrupt_y_axise_enable {
    INTERRUPT_Y_AXISE_DISABLE_E,
    INTERRUPT_Y_AXISE_ENABLE_E
} INTERRUPT_Y_AXISE_ENABLE_T ;
#define INTERRUPT_Y_AXISE_PARAM_MASK  0x40



//  
//  Enable interrupt generation on X-axise.
//  Register InterruptConfig 0x0030, Bits 7:7, typedef interrupt_x_axise_enable
//   
//  
#define INTERRUPT_X_AXISE_MASK 0x80U
#define INTERRUPT_X_AXISE_OFFSET 7
#define INTERRUPT_X_AXISE_STOP_BIT 7
#define INTERRUPT_X_AXISE_START_BIT 7
#define INTERRUPT_X_AXISE_WIDTH 1


typedef enum interrupt_x_axise_enable {
    INTERRUPT_X_AXISE_DISABLE_E,
    INTERRUPT_X_AXISE_ENABLE_E
} INTERRUPT_X_AXISE_ENABLE_T ;
#define INTERRUPT_X_AXISE_PARAM_MASK  0x80



//  
//  This bit signals when an interrupt event occurs.
//  Register InterruptSource 0x0031, Bits 0:0, typedef interrupt_event
//   
//  
#define INTERRUPT_EVENT_MASK 0x1U
#define INTERRUPT_EVENT_OFFSET 0
#define INTERRUPT_EVENT_STOP_BIT 0
#define INTERRUPT_EVENT_START_BIT 0
#define INTERRUPT_EVENT_WIDTH 1

#define INTERRUPT_SOURCE_REG 0x31

typedef enum interrupt_event {
    NO_EVENT_E,
    INTERRUPT_EVENT_E
} INTERRUPT_EVENT_T ;
#define INTERRUPT_EVENT_PARAM_MASK  0x1



//  
//  Internal measurement range overflow on magnetic value.
//  Register InterruptSource 0x0031, Bits 1:1, typedef internal_overflow_value
//   
//  
#define INTERNAL_OVERFLOW_VALUE_MASK 0x2U
#define INTERNAL_OVERFLOW_VALUE_OFFSET 1
#define INTERNAL_OVERFLOW_VALUE_STOP_BIT 1
#define INTERNAL_OVERFLOW_VALUE_START_BIT 1
#define INTERNAL_OVERFLOW_VALUE_WIDTH 1


typedef enum internal_overflow_value {
    NO_OVERFLOW_E,
    INTERNAL_OVERFLOW_E
} INTERNAL_OVERFLOW_VALUE_T ;
#define INTERNAL_OVERFLOW_VALUE_PARAM_MASK  0x2



//  
//  Value on Z-axis exceeds the threshold on the negative side.
//  Register InterruptSource 0x0031, Bits 2:2, typedef threshold
//   
//  
#define THRESHOLD_NEGATIVE_Z_MASK 0x4U
#define THRESHOLD_NEGATIVE_Z_OFFSET 2
#define THRESHOLD_NEGATIVE_Z_STOP_BIT 2
#define THRESHOLD_NEGATIVE_Z_START_BIT 2
#define THRESHOLD_NEGATIVE_Z_WIDTH 1


typedef enum threshold {
    NO_EXCEEDS_THRESHOLD_E,
    VALUDE_EXCEEDS_THRESHOLD_E
} THRESHOLD_T ;
#define THRESHOLD_NEGATIVE_Z_PARAM_MASK  0x4



//  
//  Value on Y-axis exceeds the threshold on the negative side.
//  Register InterruptSource 0x0031, Bits 3:3, typedef threshold
//   
//  
#define THRESHOLD_NEGATIVE_Y_MASK 0x8U
#define THRESHOLD_NEGATIVE_Y_OFFSET 3
#define THRESHOLD_NEGATIVE_Y_STOP_BIT 3
#define THRESHOLD_NEGATIVE_Y_START_BIT 3
#define THRESHOLD_NEGATIVE_Y_WIDTH 1


#define THRESHOLD_NEGATIVE_Y_PARAM_MASK  0x8



//  
//  Value on X-axis exceeds the threshold on the negative side.
//  Register InterruptSource 0x0031, Bits 4:4, typedef threshold
//   
//  
#define THRESHOLD_NEGATIVE_X_MASK 0x10U
#define THRESHOLD_NEGATIVE_X_OFFSET 4
#define THRESHOLD_NEGATIVE_X_STOP_BIT 4
#define THRESHOLD_NEGATIVE_X_START_BIT 4
#define THRESHOLD_NEGATIVE_X_WIDTH 1


#define THRESHOLD_NEGATIVE_X_PARAM_MASK  0x10



//  
//  Value on Z-axis exceeds the threshold on the positive side.
//  Register InterruptSource 0x0031, Bits 5:5, typedef threshold
//   
//  
#define THRESHOLD_POSITIVE_Z_MASK 0x20U
#define THRESHOLD_POSITIVE_Z_OFFSET 5
#define THRESHOLD_POSITIVE_Z_STOP_BIT 5
#define THRESHOLD_POSITIVE_Z_START_BIT 5
#define THRESHOLD_POSITIVE_Z_WIDTH 1


#define THRESHOLD_POSITIVE_Z_PARAM_MASK  0x20



//  
//  Value on Y-axis exceeds the threshold on the positive side.
//  Register InterruptSource 0x0031, Bits 6:6, typedef threshold
//   
//  
#define THRESHOLD_POSITIVE_Y_MASK 0x40U
#define THRESHOLD_POSITIVE_Y_OFFSET 6
#define THRESHOLD_POSITIVE_Y_STOP_BIT 6
#define THRESHOLD_POSITIVE_Y_START_BIT 6
#define THRESHOLD_POSITIVE_Y_WIDTH 1


#define THRESHOLD_POSITIVE_Y_PARAM_MASK  0x40



//  
//  Value on X-axis exceeds the threshold on the positive side.
//  Register InterruptSource 0x0031, Bits 7:7, typedef threshold
//   
//  
#define THRESHOLD_POSITIVE_X_MASK 0x80U
#define THRESHOLD_POSITIVE_X_OFFSET 7
#define THRESHOLD_POSITIVE_X_STOP_BIT 7
#define THRESHOLD_POSITIVE_X_START_BIT 7
#define THRESHOLD_POSITIVE_X_WIDTH 1


#define THRESHOLD_POSITIVE_X_PARAM_MASK  0x80



#define INTERRUPT_THRESHOLD_LSB_REG 0x32

#define INTERRUPT_THRESHOL_M_LSB_REG 0x33
#endif
