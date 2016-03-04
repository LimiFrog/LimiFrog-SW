#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "../Console.h"

unsigned char Device_Address;
extern I2C_HandleTypeDef hi2c1;

//variables globales
unsigned char readTransaction;
unsigned char writeTransaction;

void lps25h_init(unsigned char deviceAddress)
{
  Device_Address = deviceAddress;
}

//HAL : _MEM_ means i2c Combined cycle @device+ @register => read
unsigned char lps25h_read_register(unsigned char Register)
{
  readTransaction = 0;
  unsigned char data;
  
  if( HAL_I2C_Mem_Read_IT(&hi2c1, (uint16_t)Device_Address,(uint16_t)Register,I2C_MEMADD_SIZE_8BIT,  (uint8_t *)&data, 1) !=HAL_OK)
      {
        Sendlog("fonction hts221_read_register failure");
      };

  while (readTransaction==0);

  return data;
}

void lps25h_write_register(unsigned char Register,unsigned char Data)
{
 unsigned char data = Data; // = Data ajout SF0
  writeTransaction = 0;
  
  if( HAL_I2C_Mem_Write_IT(&hi2c1, (uint16_t)Device_Address,(uint16_t)Register,I2C_MEMADD_SIZE_8BIT,(uint8_t *) &data, 1) !=HAL_OK)
      {
        Sendlog("fonction hts221_write_register failure");
      }
    while (writeTransaction==0);

}

void HAL_I2C_MemTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
  writeTransaction = 1;
}

void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
  readTransaction = 1;
}
