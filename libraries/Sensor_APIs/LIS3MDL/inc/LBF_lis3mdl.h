/*******************************************************************************
 * LBF_lis3mdl.h
 * 
 * Adapted by: LimiFrog, 2015
 *
 *
 * from original file lis3mdl_types.h
 *
 * Generated on the 03/11/2015 19:31 by the 'super-cool' code generator 
 * by  Rémi PRUD'HOMME 
 * Generator written in Common Lisp
 ***************************************************************************/



#ifndef __LBF_LIS3MDL_H
#define __LBF_LIS3MDL_H


#ifdef __cplusplus
extern "C" {
#endif

#define LIS3MDL_WHO_IAM_REG 0xF


#define LIS3MDL_CONTROL_REGISTER_1_REG 0x20

#define LIS3MDL_CONTROL_REGISTER_2_REG 0x21

#define LIS3MDL_CONTROL_REGISTER_3_REG 0x22

#define LIS3MDL_CONTROL_REGISTER_4_REG 0x23

#define LIS3MDL_CONTROL_REGISTER_5_REG 0x24


#define LIS3MDL_STATUS_REGISTER_REG 0x27


#define LIS3MDL_MAGNETO_X_LOW_REG 0x28

#define LIS3MDL_MAGNETO_X_HIGH_REG 0x29

#define LIS3MDL_MAGNETO_Y_LOW_REG 0x2A

#define LIS3MDL_MAGNETO_Y_HIGH_REG 0x2B

#define LIS3MDL_MAGNETO_Z_LOW_REG 0x2C

#define LIS3MDL_MAGNETO_Z_HIGH_REG 0x2D


#define LIS3MDL_TEMPERATURE_DATA_LSB_REG 0x2E

#define LIS3MDL_TEMPERATURE_DATA_MSB_REG 0x2F


#define LIS3MDL_INTERRUPT_CONFIG_REG 0x30

#define LIS3MDL_INTERRUPT_SOURCE_REG 0x31

#define LIS3MDL_INTERRUPT_THRESHOLD_LSB_REG 0x32

#define LIS3MDL_INTERRUPT_THRESHOL_M_LSB_REG 0x33


#endif
