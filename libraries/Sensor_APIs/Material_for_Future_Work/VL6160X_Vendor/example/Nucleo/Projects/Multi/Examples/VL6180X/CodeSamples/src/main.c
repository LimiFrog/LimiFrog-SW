/**
 ******************************************************************************
 * File Name          : main.c
 * Date               : 21/10/2014 09:21:14
 * Description        : Main program body
 ******************************************************************************
 *
 * COPYRIGHT(c) 2014 STMicroelectronics
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

#include "stm32xxx_hal.h"

I2C_HandleTypeDef hi2c1;

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "vl6180x_api.h"
#include "x-nucleo-6180xa1.h"

#ifdef DEBUG
#include "diag/trace.h"
#define debug(msg, ...)   trace_printf(msg,__VA_ARGS__)
#define trace_warn(msg,...) trace_printf("W %s %d" msg "\n", __func__, __LINE__, __VA_ARGS__)
#else
#define debug(msg, ...)  (void)0
#endif

#define DigitDisplay_ms     1 /* ms each digit is kept on */
#define PressBPSwicthTime   1000 /* if user keep bp press more that this mean swicth mode else rooll over use c&se in mode */

void WaitMilliSec(int ms);

/**
 * VL6180x CubeMX F401 i2c porting implementation
 */

#define theVL6180xDev   0x52    // what we use as "API device
#define i2c_bus      (&hi2c1)
#define def_i2c_time_out 100
#if VL6180x_SINGLE_DEVICE_DRIVER
int VL6180x_I2CWrite(VL6180xDev_t addr, uint8_t *buff, uint8_t len) {
    int status;
    status = HAL_I2C_Master_Transmit(i2c_bus, addr, buff, len, def_i2c_time_out);
    if (status) {
        XNUCLEO6180XA1_I2C1_Init(&hi2c1);
    }
    return status;
}

int VL6180x_I2CRead(VL6180xDev_t addr, uint8_t *buff, uint8_t len) {
    int status;
    status = HAL_I2C_Master_Receive(i2c_bus, addr, buff, len, def_i2c_time_out);
    if (status) {
        XNUCLEO6180XA1_I2C1_Init(&hi2c1);
    }

    return status;
}
#else
int VL6180x_I2CWrite(VL6180xDev_t dev, uint8_t *buff, uint8_t len) {
    int status;
    status = HAL_I2C_Master_Transmit(i2c_bus, dev->I2cAddr, buff, len, def_i2c_time_out);
    if (status) {
        XNUCLEO6180XA1_I2C1_Init(&hi2c1);
    }
    return status;
}

int VL6180x_I2CRead(VL6180xDev_t dev, uint8_t *buff, uint8_t len) {
    int status;
    status = HAL_I2C_Master_Receive(i2c_bus, dev->I2cAddr, buff, len, def_i2c_time_out);
    if (status) {
        XNUCLEO6180XA1_I2C1_Init(&hi2c1);
    }

    return status;
}

#endif

/**
 * platform and application specific for VL6180x_Shield
 */
void XNUCLEO6180XA1_WaitMilliSec(int n) {
    WaitMilliSec(n);
}

volatile int IntrFired = 0;

void XNUCLEO6180XA1_UserIntHandler(void) {
    IntrFired++;
}

/**
 * DISPLAY public
 */
/***************  DISPLAY PUBLIC *********************/
const char *DISP_NextString;
/***************  DISPLAY PRIVATE *********************/
static char DISP_CurString[10];
static int DISP_Loop = 0;
uint32_t TimeStarted; /* various display and mode delay starting time */

void DISP_ExecLoopBody(void) {
    if (DISP_NextString != NULL) {
        strncpy(DISP_CurString, DISP_NextString, sizeof(DISP_CurString) - 1);
        DISP_CurString[sizeof(DISP_CurString) - 1] = 0;
        DISP_NextString = NULL;
    }
    XNUCLEO6180XA1_DisplayString(DISP_CurString, DigitDisplay_ms);
    DISP_Loop++;
}

/**
 * Nucleo board specific
 *
 */

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
    XNUCLEO6180XA1_EXTI_CallBackHandle(GPIO_Pin);
}

volatile uint32_t g_TickCnt;
void HAL_SYSTICK_Callback(void){
    g_TickCnt++;
}

#define BSP_BP_PORT GPIOC
#define BSP_BP_PIN  GPIO_PIN_13
int BSP_GetPushButton(void) {
    GPIO_PinState state;
    state = HAL_GPIO_ReadPin(BSP_BP_PORT, BSP_BP_PIN);
    return state;
}

void SetDisplayString(const char *msg) {
    DISP_NextString = msg;
}

void WaitMilliSec(int ms) {
    HAL_Delay(ms); /* it's milli sec  cos we do set systick to 1KHz */
}

/**
 * call in the main loop
 * when running under debugger it enable doing direct vl6180x reg access
 * After  breaking at entrance
 * change  the the local index/data and cmd variable to do what needed
 * reg_cmd -1 wr byte -2wr word -3 wr dword
 * reg_cmd 1 rd byte 2 rd word 3 rd dword
 * step to last statement before return and read variable to get rd result exit
 */
void debug_stuff(void) {
    int reg_cmd = 0;
    static uint32_t reg_data;
    static uint16_t reg_index;

    if (reg_cmd) {
        switch (reg_cmd) {
            case -1:
                VL6180x_WrByte(theVL6180xDev, reg_index, reg_data);
                debug("Wr B 0x%X = %d", reg_index, (int)reg_data);
                break;
            case -2:
                VL6180x_WrWord(theVL6180xDev, reg_index, reg_data);
                debug("Wr W 0x%X = %d", reg_index, (int) reg_data);
                break;

            case -3:
                VL6180x_WrDWord(theVL6180xDev, reg_index, reg_data);
                debug("WrDW 0x%X = %d", reg_index, (int)reg_data);
                break;

            case 1:
                reg_data = 0;
                VL6180x_RdByte(theVL6180xDev, reg_index, (uint8_t*) &reg_data);
                debug("RD B 0x%X = %d", reg_index, (int)reg_data);
                break;
            case 2:
                reg_data = 0;
                VL6180x_RdWord(theVL6180xDev, reg_index, (uint16_t*) &reg_data);
                debug("RD W 0x%X = %d", reg_index, (int)reg_data);
                break;

            case 3:
                VL6180x_RdDWord(theVL6180xDev, reg_index, &reg_data);
                debug("RD DW 0x%X = %d", reg_index, (int)reg_data);
                break;
            default:
                debug("Invalid command %d", reg_cmd);
                /* nothing to do*/
                ;
        }
    }
}

/**
 * When button is already pressed it Wait for user to release it
 * if button remain pressed for given time it return true
 * These is used to detect mode switch by long press on blue Push Button
 *
 * As soon as time is elapsed -rb- is displayed  to let user know order
 * the  request to switch mode is taken into account
 *
 * @return True if button remain pressed more than specified time
 */
int PusbButton_WaitUnPress(void) {
    uint32_t TimeStarted = HAL_GetTick();
    uint32_t tick;

    while (!BSP_GetPushButton()) {
        ; /* debounce */
        DISP_ExecLoopBody();
        tick = HAL_GetTick();
        if (-TimeStarted > PressBPSwicthTime) {
            SetDisplayString(" rb ");
        }
    }
    return tick - TimeStarted > PressBPSwicthTime;
}

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);

void Sample_FreeRunningRanging(void);
void Sample_SimpleRanging(void);
void Sample_SimpleAls(void);
uint8_t Sample_OffsetCalibrate(void);
void Sample_XTalkCalibrate(int initDevice);
void Sample_AlternateRangeAls(void);
void Sample_Interrupt(void);

int main(void) {
    uint8_t offset;

    /* MCU Configuration----------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* Configure the system clock */
    SystemClock_Config();

    /* System interrupt init*/
    /* Sets the priority grouping field */
    HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_0);
    HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_I2C1_Init();

    /* these almost just redo what already done just above by CubeMx Init */
    XNUCLEO6180XA1_GPIO_Init();
    XNUCLEO6180XA1_I2C1_Init(&hi2c1);

    /* SysTick end of count event each 1ms */
    SysTick_Config(HAL_RCC_GetHCLKFreq() / 1000);

    while (1) {

        Sample_SimpleRanging();
        
        Sample_FreeRunningRanging();

        Sample_SimpleAls();

        Sample_AlternateRangeAls();

        offset = Sample_OffsetCalibrate();
        
        Sample_XTalkCalibrate(offset);

        Sample_Interrupt();
    }
    /* USER CODE END 3 */

}

/** System Clock Configuration
 */
void SystemClock_Config(void) {

    RCC_ClkInitTypeDef RCC_ClkInitStruct;
    RCC_OscInitTypeDef RCC_OscInitStruct;

    __PWR_CLK_ENABLE();

    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = 6;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = 16;
    RCC_OscInitStruct.PLL.PLLN = 336;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
    RCC_OscInitStruct.PLL.PLLQ = 7;
    HAL_RCC_OscConfig(&RCC_OscInitStruct);

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);

}

/* I2C1 init function */
void MX_I2C1_Init(void) {

    hi2c1.Instance = I2C1;
    hi2c1.Init.ClockSpeed = 400000;
    hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
    hi2c1.Init.OwnAddress1 = 0;
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLED;
    hi2c1.Init.OwnAddress2 = 0;
    hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLED;
    hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLED;
    HAL_I2C_Init(&hi2c1);

}

/** Configure pins as 
 * Analog
 * Input
 * Output
 * EVENT_OUT
 * EXTI
 PA2   ------> USART2_TX
 PA3   ------> USART2_RX
 */
void MX_GPIO_Init(void) {

    GPIO_InitTypeDef GPIO_InitStruct;

    /* GPIO Ports Clock Enable */
    __GPIOC_CLK_ENABLE();
    __GPIOH_CLK_ENABLE();
    __GPIOA_CLK_ENABLE();
    __GPIOB_CLK_ENABLE();

    /*Configure GPIO pin : PC13 */
    GPIO_InitStruct.Pin = GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /*Configure GPIO pins : PA0 PA1 PA4 PA5
     PA8 PA9 */
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_8 | GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*Configure GPIO pins : PA2 PA3 */
    GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*Configure GPIO pins : PA6 PA7 */
    GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*Configure GPIO pins : PB0 PB10 PB4 PB5
     PB6 */
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_10 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /*Configure GPIO pin : PC7 */
    GPIO_InitStruct.Pin = GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

}

#ifdef USE_FULL_ASSERT

/**
 * @brief Reports the name of the source file and the source line number
 * where the assert_param error has occurred.
 * @param file: pointer to the source file name
 * @param line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t* file, uint32_t line)
{
    /* USER CODE BEGIN 6 */
    trace_printf("assert_param() failed: file \"%s\", line %d\n", file, line);
    exit(1);
    /* USER CODE END 6 */

}

#endif

