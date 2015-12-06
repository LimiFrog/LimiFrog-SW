/****************************************************************************
 * File : c:/Lisp/Production/sensors_st/sensors_st_lps25h/Linux/lps25h_types.h
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

#ifndef C__LISP_PRODUCTION_SENSORS_ST_SENSORS_ST_LPS25H_LINUX_LPS25H_TYPES_H
#define C__LISP_PRODUCTION_SENSORS_ST_SENSORS_ST_LPS25H_LINUX_LPS25H_TYPES_H


#ifdef __cplusplus
extern "C" {
#endif


#define REFERENCE_REGISTER_X_LSB_REG 0xB808

#define REFERENCE_REGISTER_LSB_REG 0xB809

#define REFERENCE_REGISTER_MSB_REG 0xB80A

#define WHO_IAM_REG 0xB80F

//  
//  To select the numbers of averaged temperature samples.
//  Register ResolutionMode 0xB810, Bits 0:1, typedef temperature_average
//   
//  
#define AVERAGED_TEMPERATURE_SAMPLES_MASK 0x3U
#define AVERAGED_TEMPERATURE_SAMPLES_OFFSET 1
#define AVERAGED_TEMPERATURE_SAMPLES_STOP_BIT 1
#define AVERAGED_TEMPERATURE_SAMPLES_START_BIT 0
#define AVERAGED_TEMPERATURE_SAMPLES_WIDTH 2

#define RESOLUTION_MODE_REG 0xB810
#define  TEMPERATURE_AVERAGE_8 0
#define  TEMPERATURE_AVERAGE_16 1
#define  TEMPERATURE_AVERAGE_32 2
#define  TEMPERATURE_AVERAGE_64 3

typedef enum temperature_average {
    TEMPERATURE_AVERAGE_8_E,
    TEMPERATURE_AVERAGE_16_E,
    TEMPERATURE_AVERAGE_32_E,
    TEMPERATURE_AVERAGE_64_E
} TEMPERATURE_AVERAGE_T ;
#define AVERAGED_TEMPERATURE_SAMPLES_PARAM_MASK  0x3



//  
//  To select the numbers of averaged pressure samples.
//  Register ResolutionMode 0xB810, Bits 2:3, typedef pressure_average
//   
//  
#define AVERAGED_PRESSURE_SAMPLES_MASK 0xCU
#define AVERAGED_PRESSURE_SAMPLES_OFFSET 3
#define AVERAGED_PRESSURE_SAMPLES_STOP_BIT 3
#define AVERAGED_PRESSURE_SAMPLES_START_BIT 2
#define AVERAGED_PRESSURE_SAMPLES_WIDTH 2

#define  PRESSURE_AVERAGE_8 0
#define  PRESSURE_AVERAGE_32 1
#define  PRESSURE_AVERAGE_128 2
#define  PRESSURE_AVERAGE_512 3

typedef enum pressure_average {
    PRESSURE_AVERAGE_8_E,
    PRESSURE_AVERAGE_32_E,
    PRESSURE_AVERAGE_128_E,
    PRESSURE_AVERAGE_512_E
} PRESSURE_AVERAGE_T ;
#define AVERAGED_PRESSURE_SAMPLES_PARAM_MASK  0xC



//  
//  SPI Serial Interface Mode selection. 0: 4-wire interface; 1: 3-wire 
//  interface.
//  Register ControlRegister1 0xB820, Bits 0:0, typedef spi_wire
//   
//  
#define SPI_WIRE_MASK 0x1U
#define SPI_WIRE_OFFSET 0
#define SPI_WIRE_STOP_BIT 0
#define SPI_WIRE_START_BIT 0
#define SPI_WIRE_WIDTH 1

#define CONTROL_REGISTER_1_REG 0xB820

typedef enum spi_wire {
    SPI_4_WIRE_E,
    SPI_3_WIRE_E
} SPI_WIRE_T ;
#define SPI_WIRE_PARAM_MASK  0x1



//  
//  Reset AutoZero function. Reset REF_P reg, set pressure to default value in 
//  RPDS.
//  Register ControlRegister1 0xB820, Bits 1:1, typedef reset_auto_zero
//   
//  
#define RESET_AUTO_ZEROFUNCTION_MASK 0x2U
#define RESET_AUTO_ZEROFUNCTION_OFFSET 1
#define RESET_AUTO_ZEROFUNCTION_STOP_BIT 1
#define RESET_AUTO_ZEROFUNCTION_START_BIT 1
#define RESET_AUTO_ZEROFUNCTION_WIDTH 1


typedef enum reset_auto_zero {
    RESET_AUTOZERO_E,
    DISABLE_RESET_AUTOZERO_E
} RESET_AUTO_ZERO_T ;
#define RESET_AUTO_ZEROFUNCTION_PARAM_MASK  0x2



//  
//  block data update 0: continuous update; 1: output registers not updated until MSB and 
//  LSB reading.
//  Register ControlRegister1 0xB820, Bits 2:2, typedef continuous_update_enable
//   
//  
#define CONTINUOUS_UPDATE_MASK 0x4U
#define CONTINUOUS_UPDATE_OFFSET 2
#define CONTINUOUS_UPDATE_STOP_BIT 2
#define CONTINUOUS_UPDATE_START_BIT 2
#define CONTINUOUS_UPDATE_WIDTH 1


typedef enum continuous_update_enable {
    CONTINUOUS_UPDATE_ENABLE_E,
    CONTINUOUS_UPDATE_DISABLE_E
} CONTINUOUS_UPDATE_ENABLE_T ;
#define CONTINUOUS_UPDATE_PARAM_MASK  0x4



//  
//  Interrupt circuit enable..
//  Register ControlRegister1 0xB820, Bits 3:3, typedef interrupt_circuit_enable
//   
//  
#define INTERRUPT_CIRCUIT_MASK 0x8U
#define INTERRUPT_CIRCUIT_OFFSET 3
#define INTERRUPT_CIRCUIT_STOP_BIT 3
#define INTERRUPT_CIRCUIT_START_BIT 3
#define INTERRUPT_CIRCUIT_WIDTH 1


typedef enum interrupt_circuit_enable {
    INTERRUPT_CIRCUIT_DISABLE_E,
    INTERRUPT_CIRCUIT_ENABLE_E
} INTERRUPT_CIRCUIT_ENABLE_T ;
#define INTERRUPT_CIRCUIT_PARAM_MASK  0x8



//  
//  output data rate selection.
//  Register ControlRegister1 0xB820, Bits 4:6, typedef data_rate
//   
//  
#define DATA_RATE_MASK 0x70U
#define DATA_RATE_OFFSET 6
#define DATA_RATE_STOP_BIT 6
#define DATA_RATE_START_BIT 4
#define DATA_RATE_WIDTH 3

#define  ONE_SHOT 0
#define  DATA_RATE_1HZ 1
#define  DATA_RATE_7HZ 2
#define  DATA_RATE_12_5HZ 3
#define  DATA_RATE_15_5HZ 4

typedef enum data_rate {
    ONE_SHOT_E,
    DATA_RATE_1HZ_E,
    DATA_RATE_7HZ_E,
    DATA_RATE_12_5HZ_E,
    DATA_RATE_15_5HZ_E
} DATA_RATE_T ;
#define DATA_RATE_PARAM_MASK  0x70



//  
//  power down control. 0: power-down mode; 1: active mode.
//  Register ControlRegister1 0xB820, Bits 7:7, typedef active_mode_enable
//   
//  
#define ACTIVE_MODE_MASK 0x80U
#define ACTIVE_MODE_OFFSET 7
#define ACTIVE_MODE_STOP_BIT 7
#define ACTIVE_MODE_START_BIT 7
#define ACTIVE_MODE_WIDTH 1


typedef enum active_mode_enable {
    ACTIVE_MODE_DISABLE_E,
    ACTIVE_MODE_ENABLE_E
} ACTIVE_MODE_ENABLE_T ;
#define ACTIVE_MODE_PARAM_MASK  0x80



//  
//  One shot enable..
//  Register ControlRegister2 0xB821, Bits 0:0, typedef one_shot_enable
//   
//  
#define ONE_SHOT_MASK 0x1U
#define ONE_SHOT_OFFSET 0
#define ONE_SHOT_STOP_BIT 0
#define ONE_SHOT_START_BIT 0
#define ONE_SHOT_WIDTH 1

#define CONTROL_REGISTER_2_REG 0xB821

typedef enum one_shot_enable {
    ONE_SHOT_DISABLE_E,
    ONE_SHOT_ENABLE_E
} ONE_SHOT_ENABLE_T ;
#define ONE_SHOT_PARAM_MASK  0x1



//  
//  Autozero enable..
//  Register ControlRegister2 0xB821, Bits 1:1, typedef autozero_enable
//   
//  
#define AUTOZERO_MASK 0x2U
#define AUTOZERO_OFFSET 1
#define AUTOZERO_STOP_BIT 1
#define AUTOZERO_START_BIT 1
#define AUTOZERO_WIDTH 1


typedef enum autozero_enable {
    AUTOZERO_DISABLE_E,
    AUTOZERO_ENABLE_E
} AUTOZERO_ENABLE_T ;
#define AUTOZERO_PARAM_MASK  0x2



//  
//  Software Reset Enable..
//  Register ControlRegister2 0xB821, Bits 2:2, typedef software_reset_enable
//   
//  
#define SOFTWARE_RESET_MASK 0x4U
#define SOFTWARE_RESET_OFFSET 2
#define SOFTWARE_RESET_STOP_BIT 2
#define SOFTWARE_RESET_START_BIT 2
#define SOFTWARE_RESET_WIDTH 1


typedef enum software_reset_enable {
    SOFTWARE_RESET_DISABLE_E,
    SOFTWARE_RESET_ENABLE_E
} SOFTWARE_RESET_ENABLE_T ;
#define SOFTWARE_RESET_PARAM_MASK  0x4



//  
//  0: I2C enable;1: SPI disable.
//  Register ControlRegister2 0xB821, Bits 3:3, typedef comm_mode
//   
//  
#define COMM_MASK 0x8U
#define COMM_OFFSET 3
#define COMM_STOP_BIT 3
#define COMM_START_BIT 3
#define COMM_WIDTH 1


typedef enum comm_mode {
    ENABLE_I2C_E,
    ENABLE_SPI_E
} COMM_MODE_T ;
#define COMM_PARAM_MASK  0x8



//  
//  Enable 1Hz ODR decimation.
//  Register ControlRegister2 0xB821, Bits 4:4, typedef ord_decimation_enable
//   
//  
#define ORD_DECIMATIONE_MASK 0x10U
#define ORD_DECIMATIONE_OFFSET 4
#define ORD_DECIMATIONE_STOP_BIT 4
#define ORD_DECIMATIONE_START_BIT 4
#define ORD_DECIMATIONE_WIDTH 1


typedef enum ord_decimation_enable {
    ORD_DECIMATION_DISABLE_E,
    ORD_DECIMATION_ENABLE_E
} ORD_DECIMATION_ENABLE_T ;
#define ORD_DECIMATIONE_PARAM_MASK  0x10



//  
//  Enable FIFO Watermark level use.
//  Register ControlRegister2 0xB821, Bits 5:5, typedef fifo_water_mark_enable
//   
//  
#define FIFO_WATER_MARK_MASK 0x20U
#define FIFO_WATER_MARK_OFFSET 5
#define FIFO_WATER_MARK_STOP_BIT 5
#define FIFO_WATER_MARK_START_BIT 5
#define FIFO_WATER_MARK_WIDTH 1


typedef enum fifo_water_mark_enable {
    FIFO_WATER_MARK_DISABLE_E,
    FIFO_WATER_MARK_ENABLE_E
} FIFO_WATER_MARK_ENABLE_T ;
#define FIFO_WATER_MARK_PARAM_MASK  0x20



//  
//  Enable FIFO.
//  Register ControlRegister2 0xB821, Bits 6:6, typedef fifo_enable
//   
//  
#define FIFO_MASK 0x40U
#define FIFO_OFFSET 6
#define FIFO_STOP_BIT 6
#define FIFO_START_BIT 6
#define FIFO_WIDTH 1


typedef enum fifo_enable {
    FIFO_DISABLE_E,
    FIFO_ENABLE_E
} FIFO_ENABLE_T ;
#define FIFO_PARAM_MASK  0x40



//  
//  Reboot memory content..
//  Register ControlRegister2 0xB821, Bits 7:7, typedef reboot_memory_content_enable
//   
//  
#define REBOOT_MEMORY_CONTENT_MASK 0x80U
#define REBOOT_MEMORY_CONTENT_OFFSET 7
#define REBOOT_MEMORY_CONTENT_STOP_BIT 7
#define REBOOT_MEMORY_CONTENT_START_BIT 7
#define REBOOT_MEMORY_CONTENT_WIDTH 1


typedef enum reboot_memory_content_enable {
    REBOOT_MEMORY_CONTENT_DISABLE_E,
    REBOOT_MEMORY_CONTENT_ENABLE_E
} REBOOT_MEMORY_CONTENT_ENABLE_T ;
#define REBOOT_MEMORY_CONTENT_PARAM_MASK  0x80



//  
//  data signal on INT1 pad control bit.
//  Register ControlRegister3 0xB822, Bits 0:1, typedef data_signal_on_int
//   
//  
#define DATA_SIGNAL_ON_INT_PAD_MASK 0x3U
#define DATA_SIGNAL_ON_INT_PAD_OFFSET 1
#define DATA_SIGNAL_ON_INT_PAD_STOP_BIT 1
#define DATA_SIGNAL_ON_INT_PAD_START_BIT 0
#define DATA_SIGNAL_ON_INT_PAD_WIDTH 2

#define CONTROL_REGISTER_3_REG 0xB822
#define  DATA_SIGNAL 0
#define  PRESSURE_HIGH 1
#define  PRESSURE_LOW 2
#define  PRESSURE_HIGH_OR_PRESSURE_HIGH 3

typedef enum data_signal_on_int {
    DATA_SIGNAL_E,
    PRESSURE_HIGH_E,
    PRESSURE_LOW_E,
    PRESSURE_HIGH_OR_PRESSURE_HIGH_E
} DATA_SIGNAL_ON_INT_T ;
#define DATA_SIGNAL_ON_INT_PAD_PARAM_MASK  0x3



//  
//  Push-pull / Open Drain selection on pin 3..
//  Register ControlRegister3 0xB822, Bits 6:6, typedef open_drain_enable
//   
//  
#define OPEN_DRAIN_SELECTION_MASK 0x40U
#define OPEN_DRAIN_SELECTION_OFFSET 6
#define OPEN_DRAIN_SELECTION_STOP_BIT 6
#define OPEN_DRAIN_SELECTION_START_BIT 6
#define OPEN_DRAIN_SELECTION_WIDTH 1


typedef enum open_drain_enable {
    OPEN_DRAIN_DISABLE_E,
    OPEN_DRAIN_ENABLE_E
} OPEN_DRAIN_ENABLE_T ;
#define OPEN_DRAIN_SELECTION_PARAM_MASK  0x40



//  
//  Interrupt active high. 0: active high; 1: active low.
//  Register ControlRegister3 0xB822, Bits 7:7, typedef level
//   
//  
#define INTERRUPT_LEVEL_MASK 0x80U
#define INTERRUPT_LEVEL_OFFSET 7
#define INTERRUPT_LEVEL_STOP_BIT 7
#define INTERRUPT_LEVEL_START_BIT 7
#define INTERRUPT_LEVEL_WIDTH 1


typedef enum level {
    ACTIVE_HIGH_E,
    ACTIVE_LOW_E
} LEVEL_T ;
#define INTERRUPT_LEVEL_PARAM_MASK  0x80



//  
//  Data ready Signal on INT1 pin..
//  Register ControlRegister4 0xB823, Bits 0:0, typedef data_ready_enable
//   
//  
#define DATA_READY_SIGNAL_MASK 0x1U
#define DATA_READY_SIGNAL_OFFSET 0
#define DATA_READY_SIGNAL_STOP_BIT 0
#define DATA_READY_SIGNAL_START_BIT 0
#define DATA_READY_SIGNAL_WIDTH 1

#define CONTROL_REGISTER_4_REG 0xB823

typedef enum data_ready_enable {
    DATA_READY_DISABLE_E,
    DATA_READY_ENABLE_E
} DATA_READY_ENABLE_T ;
#define DATA_READY_SIGNAL_PARAM_MASK  0x1



//  
//  Overrun Signal on INT1 pin..
//  Register ControlRegister4 0xB823, Bits 1:1, typedef overrunl_enable
//   
//  
#define OVERRUN_SIGNAL_MASK 0x2U
#define OVERRUN_SIGNAL_OFFSET 1
#define OVERRUN_SIGNAL_STOP_BIT 1
#define OVERRUN_SIGNAL_START_BIT 1
#define OVERRUN_SIGNAL_WIDTH 1


typedef enum overrunl_enable {
    OVERRUNL_DISABLE_E,
    OVERRUNL_ENABLE_E
} OVERRUNL_ENABLE_T ;
#define OVERRUN_SIGNAL_PARAM_MASK  0x2



//  
//  Watermark Signal on INT1 pin..
//  Register ControlRegister4 0xB823, Bits 2:2, typedef watermark_enable
//   
//  
#define WATERMARK_SIGNAL_MASK 0x4U
#define WATERMARK_SIGNAL_OFFSET 2
#define WATERMARK_SIGNAL_STOP_BIT 2
#define WATERMARK_SIGNAL_START_BIT 2
#define WATERMARK_SIGNAL_WIDTH 1


typedef enum watermark_enable {
    WATERMARK_DISABLE_E,
    WATERMARK_ENABLE_E
} WATERMARK_ENABLE_T ;
#define WATERMARK_SIGNAL_PARAM_MASK  0x4



//  
//  Empty Signal on INT1 pin..
//  Register ControlRegister4 0xB823, Bits 3:3, typedef empty_signal_enable
//   
//  
#define EMPTY_SIGNAL_MASK 0x8U
#define EMPTY_SIGNAL_OFFSET 3
#define EMPTY_SIGNAL_STOP_BIT 3
#define EMPTY_SIGNAL_START_BIT 3
#define EMPTY_SIGNAL_WIDTH 1


typedef enum empty_signal_enable {
    EMPTY_SIGNAL_DISABLE_E,
    EMPTY_SIGNAL_ENABLE_E
} EMPTY_SIGNAL_ENABLE_T ;
#define EMPTY_SIGNAL_PARAM_MASK  0x8



//  
//  Enable interrupt generation on differential pressure high event.
//  Register InterruptConfiguration 0xB824, Bits 0:0, typedef pressure_high_event_enable
//   
//  
#define PRESSURE_HIGH_EVENT_MASK 0x1U
#define PRESSURE_HIGH_EVENT_OFFSET 0
#define PRESSURE_HIGH_EVENT_STOP_BIT 0
#define PRESSURE_HIGH_EVENT_START_BIT 0
#define PRESSURE_HIGH_EVENT_WIDTH 1

#define INTERRUPT_CONFIGURATION_REG 0xB824

typedef enum pressure_high_event_enable {
    PRESSURE_HIGH_EVENT_DISABLE_E,
    PRESSURE_HIGH_EVENT_ENABLE_E
} PRESSURE_HIGH_EVENT_ENABLE_T ;
#define PRESSURE_HIGH_EVENT_PARAM_MASK  0x1



//  
//  Enable interrupt generation on differential pressure low event.
//  Register InterruptConfiguration 0xB824, Bits 1:1, typedef pressure_low_event_enable
//   
//  
#define PRESSURE_LOW_EVENT_MASK 0x2U
#define PRESSURE_LOW_EVENT_OFFSET 1
#define PRESSURE_LOW_EVENT_STOP_BIT 1
#define PRESSURE_LOW_EVENT_START_BIT 1
#define PRESSURE_LOW_EVENT_WIDTH 1


typedef enum pressure_low_event_enable {
    PRESSURE_LOW_EVENT_DISABLE_E,
    PRESSURE_LOW_EVENT_ENABLE_E
} PRESSURE_LOW_EVENT_ENABLE_T ;
#define PRESSURE_LOW_EVENT_PARAM_MASK  0x2



//  
//  Latch Interrupt request into INT_SOURCE register..
//  Register InterruptConfiguration 0xB824, Bits 2:2, typedef latch_interrupt
//   
//  
#define INTERRUPT_REQUEST_EVENT_MASK 0x4U
#define INTERRUPT_REQUEST_EVENT_OFFSET 2
#define INTERRUPT_REQUEST_EVENT_STOP_BIT 2
#define INTERRUPT_REQUEST_EVENT_START_BIT 2
#define INTERRUPT_REQUEST_EVENT_WIDTH 1


typedef enum latch_interrupt {
    INTERRUPT_NOT_LATCHED_E,
    INTERRUPT_LATCHED_E
} LATCH_INTERRUPT_T ;
#define INTERRUPT_REQUEST_EVENT_PARAM_MASK  0x4



//  
//  High differential pressure event has occurred.
//  Register InterruptSource 0xB825, Bits 0:0, typedef differential_pressure_high
//   
//  
#define DIFFERENTIAL_PRESSURE_HIGH_MASK 0x1U
#define DIFFERENTIAL_PRESSURE_HIGH_OFFSET 0
#define DIFFERENTIAL_PRESSURE_HIGH_STOP_BIT 0
#define DIFFERENTIAL_PRESSURE_HIGH_START_BIT 0
#define DIFFERENTIAL_PRESSURE_HIGH_WIDTH 1

#define INTERRUPT_SOURCE_REG 0xB825

typedef enum differential_pressure_high {
    NO_INTERRUPT_HIGH_HAS_BEEN_GENERATED_E,
    HIGH_DIFFERENTIAL_PRESSURE_EVENT_HAS_OCCURRED_E
} DIFFERENTIAL_PRESSURE_HIGH_T ;
#define DIFFERENTIAL_PRESSURE_HIGH_PARAM_MASK  0x1



//  
//  0: no interrupt has been generated; 1: one or more interrupt events have been 
//  generated..
//  Register InterruptSource 0xB825, Bits 1:1, typedef differential_pressure_low
//   
//  
#define DIFFERENTIAL_PRESSURE_LOW_MASK 0x2U
#define DIFFERENTIAL_PRESSURE_LOW_OFFSET 1
#define DIFFERENTIAL_PRESSURE_LOW_STOP_BIT 1
#define DIFFERENTIAL_PRESSURE_LOW_START_BIT 1
#define DIFFERENTIAL_PRESSURE_LOW_WIDTH 1


typedef enum differential_pressure_low {
    NO_INTERRUPT_LOW_HAS_BEEN_GENERATED_E,
    LOW_DIFFERENTIAL_PRESSURE_EVENT_HAS_OCCURRED_E
} DIFFERENTIAL_PRESSURE_LOW_T ;
#define DIFFERENTIAL_PRESSURE_LOW_PARAM_MASK  0x2



//  
//  0: no interrupt has been generated; 1: one or more interrupt events have been 
//  generated..
//  Register InterruptSource 0xB825, Bits 2:2, typedef interrupt_active
//   
//  
#define INTERRUPT_ACTIVE_MASK 0x4U
#define INTERRUPT_ACTIVE_OFFSET 2
#define INTERRUPT_ACTIVE_STOP_BIT 2
#define INTERRUPT_ACTIVE_START_BIT 2
#define INTERRUPT_ACTIVE_WIDTH 1


typedef enum interrupt_active {
    NO_INTERRUPT_HAS_BEEN_GENERATED_E,
    ONE_OR_MORE_INTERRUPT_EVENTS_HAVE_BEEN_GENERATED_E
} INTERRUPT_ACTIVE_T ;
#define INTERRUPT_ACTIVE_PARAM_MASK  0x4



//  
//  Temperature data available. T_DA is set to 1 whenever a new Temperature sample is 
//  available. T_DA is cleared anytime TEMPERATURE_OUT_H register is read..
//  Register StatusRegister 0xB827, Bits 0:0, typedef data_available
//   
//  
#define TEMPERATURE_DATA_AVAILABLE_MASK 0x1U
#define TEMPERATURE_DATA_AVAILABLE_OFFSET 0
#define TEMPERATURE_DATA_AVAILABLE_STOP_BIT 0
#define TEMPERATURE_DATA_AVAILABLE_START_BIT 0
#define TEMPERATURE_DATA_AVAILABLE_WIDTH 1

#define STATUS_REGISTER_REG 0xB827

typedef enum data_available {
    DATA_NOT_YET_AVAILABLE_E,
    DATA_AVAILABLE_E
} DATA_AVAILABLE_T ;
#define TEMPERATURE_DATA_AVAILABLE_PARAM_MASK  0x1



//  
//  Pressure data available..
//  Register StatusRegister 0xB827, Bits 1:1, typedef pressure_data_available
//   
//  
#define PRESSURE_DATA_AVAILABLE_MASK 0x2U
#define PRESSURE_DATA_AVAILABLE_OFFSET 1
#define PRESSURE_DATA_AVAILABLE_STOP_BIT 1
#define PRESSURE_DATA_AVAILABLE_START_BIT 1
#define PRESSURE_DATA_AVAILABLE_WIDTH 1


typedef enum pressure_data_available {
    PressureDataAvailable_0_E,
    PressureDataAvailable_1_E
} PRESSURE_DATA_AVAILABLE_T ;
#define PRESSURE_DATA_AVAILABLE_PARAM_MASK  0x2



//  
//  Temperature data overrun.
//  Register StatusRegister 0xB827, Bits 4:4, typedef temperature_overrun
//   
//  
#define TEMPERATURE_DATA_OVERRUN_MASK 0x10U
#define TEMPERATURE_DATA_OVERRUN_OFFSET 4
#define TEMPERATURE_DATA_OVERRUN_STOP_BIT 4
#define TEMPERATURE_DATA_OVERRUN_START_BIT 4
#define TEMPERATURE_DATA_OVERRUN_WIDTH 1


typedef enum temperature_overrun {
    TEMPERATURE_NO_OVERRUN_E,
    TEMPERATURE_OVERRUN_E
} TEMPERATURE_OVERRUN_T ;
#define TEMPERATURE_DATA_OVERRUN_PARAM_MASK  0x10



//  
//  Pressure data overrun.
//  Register StatusRegister 0xB827, Bits 5:5, typedef pressure_overun
//   
//  
#define PRESSURE_DATA_OVERRUN_MASK 0x20U
#define PRESSURE_DATA_OVERRUN_OFFSET 5
#define PRESSURE_DATA_OVERRUN_STOP_BIT 5
#define PRESSURE_DATA_OVERRUN_START_BIT 5
#define PRESSURE_DATA_OVERRUN_WIDTH 1


typedef enum pressure_overun {
    PRESSURE_NO_OVERRUN_E,
    PRESSURE_OVERRUN_E
} PRESSURE_OVERUN_T ;
#define PRESSURE_DATA_OVERRUN_PARAM_MASK  0x20



#define PRESSURE_DATA_X_LSB_REG 0xB828

#define PRESSURE_DATA_LSB_REG 0xB829

#define PRESSURE_DATA_MSB_REG 0xB82A

#define TEMPERATURE_DATA_MSB_REG 0xB82B

#define TEMPERATURE_DATA_LSB_REG 0xB82C

//  
//  FFIFO threshold.Watermark level setting.
//  Register FifoControl 0xB82E, Bits 0:4, typedef fifo_threshold
//   
//  
#define FIFO_THRESHOLD_LEVEL_MASK 0x1FU
#define FIFO_THRESHOLD_LEVEL_OFFSET 4
#define FIFO_THRESHOLD_LEVEL_STOP_BIT 4
#define FIFO_THRESHOLD_LEVEL_START_BIT 0
#define FIFO_THRESHOLD_LEVEL_WIDTH 5

#define FIFO_CONTROL_REG 0xB82E
#define  WATERMARK_2_SAMPLES_MOVING_AVERAGE 0
#define  WATERMARK_4_SAMPLES_MOVING_AVERAGE 1
#define  WATERMARK_8_SAMPLES_MOVING_AVERAGE 2
#define  WATERMARK_16_SAMPLES_MOVING_AVERAGE 3
#define  WATERMARK_32_SAMPLES_MOVING_AVERAGE 4

typedef enum fifo_threshold {
    WATERMARK_2_SAMPLES_MOVING_AVERAGE_E,
    WATERMARK_4_SAMPLES_MOVING_AVERAGE_E,
    WATERMARK_8_SAMPLES_MOVING_AVERAGE_E,
    WATERMARK_16_SAMPLES_MOVING_AVERAGE_E,
    WATERMARK_32_SAMPLES_MOVING_AVERAGE_E
} FIFO_THRESHOLD_T ;
#define FIFO_THRESHOLD_LEVEL_PARAM_MASK  0x1F



//  
//  FIFO mode selection.
//  Register FifoControl 0xB82E, Bits 5:7, typedef fifo_mode_selection
//   
//  
#define FIFO_MODE_SELECTION_MASK 0xE0U
#define FIFO_MODE_SELECTION_OFFSET 7
#define FIFO_MODE_SELECTION_STOP_BIT 7
#define FIFO_MODE_SELECTION_START_BIT 5
#define FIFO_MODE_SELECTION_WIDTH 3

#define  BYPASS 0
#define  MODE 1
#define  STOPS_WHEN_FULL 2
#define  KEEP_THE_NEWEST_DATA 3
#define  STREAM_MODE_CHANGE_TO_FIFO 4
#define  MODE_BYPASS 5
#define  MODE_CHANGE_TO_STREAM 6
#define  MODE_RESERVED_FOR_FUTURE_USE 7
#define  FIFO_MEAN 8
#define  MODE_BYPASS_MODE_THEN_CHANGE_TO_FIFO_MODE 9

typedef enum fifo_mode_selection {
    BYPASS_E,
    MODE_E,
    STOPS_WHEN_FULL_E,
    KEEP_THE_NEWEST_DATA_E,
    STREAM_MODE_CHANGE_TO_FIFO_E,
    MODE_BYPASS_E,
    MODE_CHANGE_TO_STREAM_E,
    MODE_RESERVED_FOR_FUTURE_USE_E,
    FIFO_MEAN_E,
    MODE_BYPASS_MODE_THEN_CHANGE_TO_FIFO_MODE_E
} FIFO_MODE_SELECTION_T ;
#define FIFO_MODE_SELECTION_PARAM_MASK  0xE0



#define FIFO_STATUS_REG 0xB82F

#define THRESHOLD_PRESSURE_LSB_REG 0xB830

#define THRESHOLD_PRESSURE_MSB_REG 0xB831

#define FINAL_THRESHOLD_PRESSURE_LSB_REG 0xB839

#define FINAL_THRESHOLD_PRESSURE_MSB_REG 0xB83A
#endif
