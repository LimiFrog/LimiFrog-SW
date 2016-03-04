/*******************************************************************************
 * LBF_EXTI_ExtPort_lowlevAPI.c
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/


#include "LBF_lowlev_API.h"

#include "IT_Priorities_UserDefinable.h"

#include "stm32l4xx_ll_exti.h"   // to use EXTI low-level driver


/********
* Function :	
	void LBF_Enable_EXTI_ExtPort(uint16_t  GPIO_Pin, IT_RisingTrigger_t  IT_RisingTrigger, IT_FallingTrigger_t IT_FallingTrigger); 

* Description :	
	Enables the EXTI interrupt line associated to the specified pin ( since all GPIOs of different ports bearing the same pin number are associated to the same EXTI, only the pin number is necessary here – see also note below). It is assumed that the GPIO pin of interest has already been setup as external interrupt source (and disabled) – this is covered by the LBF_Init() function based on the directives found in user file User_Configuration.h.

* Parameters : 
	> GPIO_Pin : pin number (or alias) of the GPIO pin available on the extension port which needs to be enabled as EXTI interrupt line. See file LBF_pin_aliases.h for a proposal list of meaningful port name and pin number aliases.
	> IT_RisingTrigger : set to RISING_TRIGGER_TRUE to specify that a rsing edge must trigger an EXTI interrupt, or to RISING_TRIGGER_FALSE to ignore a rising edge. It is possible to specify both rising and falling edge triggers (see below for falling).
	>  IT_FallingTrigger : set to FALLING_TRIGGER_TRUE to specify that a rsing edge must trigger an EXTI interrupt, or to FALLING_TRIGGER_FALSE to ignore a falling edge It is possible to specify both rising and falling edge triggers (see above for rising).

* Return Value:  -

* Note :   
	All pins of same numbers on ports GPIOA, GPIOB, GPIOC are associated to the same EXTI line (for example PA0, PB0 and PC0 can all drive EXTI0). It is recommended to enable only one of them at a time. If only using pins available on the extension port, this is guaranteed by design.However, a couple of STM32 pins that bear IT from on-board chips share the same pin number as some GPIOs available on the extension port. These are INT1 from LSM6DS3 (on PC6 – same pin number as CONN_POS2 = PA6) and INT from VL6180X (on PB2 – same pin number as CONN_POS5 = PA2). 
***********/

void LBF_Enable_EXTI_ExtPort ( uint16_t  GPIO_Pin, IT_RisingTrigger_t  IT_RisingTrigger, IT_FallingTrigger_t IT_FallingTrigger)
{
    // CONN_POS_1  not available as IT input (Mic. out)

    // --- CONN_POS_2    ----------------------------------------
    if ( GPIO_Pin == CONN_POS2_PIN )  //PA6 --> EXTI5_9
    {
        LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_6); 

	if (IT_RisingTrigger == RISING_TRIGGER_TRUE)
          LL_EXTI_EnableRisingTrig_0_31(LL_EXTI_LINE_6); 

	if (IT_FallingTrigger == FALLING_TRIGGER_TRUE)
          LL_EXTI_EnableFallingTrig_0_31(LL_EXTI_LINE_6); 
    }
    // CAUTION: Conflict if also using INT1 from LSM6DS3 on PC6 
    // as it means 2 sources of IRQ on the same EXTI6


    // --- CONN_POS_3    ----------------------------------------
    if ( GPIO_Pin == CONN_POS3_PIN )  //PA4 --> EXTI4
    {
        LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_4); 

	if (IT_RisingTrigger == RISING_TRIGGER_TRUE)
          LL_EXTI_EnableRisingTrig_0_31(LL_EXTI_LINE_4); 

	if (IT_FallingTrigger == FALLING_TRIGGER_TRUE)
          LL_EXTI_EnableFallingTrig_0_31(LL_EXTI_LINE_4); 
    }

    // --- CONN_POS_4    ----------------------------------------
    if ( GPIO_Pin == CONN_POS4_PIN )  //PA3 --> EXTI3
    {
        LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_3); 

	if (IT_RisingTrigger == RISING_TRIGGER_TRUE)
          LL_EXTI_EnableRisingTrig_0_31(LL_EXTI_LINE_3); 

	if (IT_FallingTrigger == FALLING_TRIGGER_TRUE)
          LL_EXTI_EnableFallingTrig_0_31(LL_EXTI_LINE_3); 
    }

    // --- CONN_POS_5    ----------------------------------------
   if ( GPIO_Pin == CONN_POS5_PIN )  //PA2 --> EXTI2
    {
        LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_2); 

	if (IT_RisingTrigger == RISING_TRIGGER_TRUE)
          LL_EXTI_EnableRisingTrig_0_31(LL_EXTI_LINE_2); 

	if (IT_FallingTrigger == FALLING_TRIGGER_TRUE)
          LL_EXTI_EnableFallingTrig_0_31(LL_EXTI_LINE_2); 
    }
    // CAUTION: Conflict if also using IRQ from VL6180X on PB2 
    // as it means 2 sources of IRQ on the same EXTI2


    // CONN_POS_6 - Not available as IT input (VCC_LDO)
   

    // --- CONN_POS_7    ----------------------------------------
   if ( GPIO_Pin == CONN_POS7_PIN )  //PA1 --> EXTI1
    {
        LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_1); 

	if (IT_RisingTrigger == RISING_TRIGGER_TRUE)
          LL_EXTI_EnableRisingTrig_0_31(LL_EXTI_LINE_1); 

	if (IT_FallingTrigger == FALLING_TRIGGER_TRUE)
          LL_EXTI_EnableFallingTrig_0_31(LL_EXTI_LINE_1); 
    }

    // --- CONN_POS_8    ----------------------------------------
   if ( GPIO_Pin == CONN_POS8_PIN )  //PA0 --> EXTI0
    {
        LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_0); 

	if (IT_RisingTrigger == RISING_TRIGGER_TRUE)
          LL_EXTI_EnableRisingTrig_0_31(LL_EXTI_LINE_0); 

	if (IT_FallingTrigger == FALLING_TRIGGER_TRUE)
          LL_EXTI_EnableFallingTrig_0_31(LL_EXTI_LINE_0); 
    }

    // CONN_POS_9 - Not available as IT input (GND)


    // --- CONN_POS_10    ----------------------------------------
   if ( GPIO_Pin == CONN_POS10_PIN )  //PB8 --> EXTI5_9
    {
        LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_8); 

	if (IT_RisingTrigger == RISING_TRIGGER_TRUE)
          LL_EXTI_EnableRisingTrig_0_31(LL_EXTI_LINE_8); 

	if (IT_FallingTrigger == FALLING_TRIGGER_TRUE)
          LL_EXTI_EnableFallingTrig_0_31(LL_EXTI_LINE_8); 
    }

    // --- CONN_POS_11    ----------------------------------------
   if ( GPIO_Pin == CONN_POS11_PIN )  //PB9 --> EXTI5_9
    {
        LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_9); 

	if (IT_RisingTrigger == RISING_TRIGGER_TRUE)
          LL_EXTI_EnableRisingTrig_0_31(LL_EXTI_LINE_9); 

	if (IT_FallingTrigger == FALLING_TRIGGER_TRUE)
          LL_EXTI_EnableFallingTrig_0_31(LL_EXTI_LINE_9); 
    }

}



/*****************
* Function :	
	void LBF_Disable_EXTI_ExtPort(uint16_t  GPIO_Pin); 
* Description :	
	Disables the EXTI interrupt line associated to the specified pin ( since all GPIOs of different ports bearing the same pin number are associated to the same EXTI, only the pin number is necessary here – see also note below). 
* Parameters : GPIO_Pin : pin number (or alias) of the GPIO pin available on the extension port which needs to be enabled as EXTI interrupt line. See file LBF_pin_aliases.h for a proposal list of meaningful port name and pin number aliases.
* Return Value:  -
*****************/

void LBF_Disable_EXTI_ExtPort( uint16_t  GPIO_Pin)
{
    if ( GPIO_Pin == CONN_POS2_PIN )  //PA6 --> EXTI5_9
    {
        LL_EXTI_DisableIT_0_31(LL_EXTI_LINE_6); 
        LL_EXTI_DisableRisingTrig_0_31(LL_EXTI_LINE_6); 
        LL_EXTI_DisableFallingTrig_0_31(LL_EXTI_LINE_6); 
    }
    // CAUTION: Conflict if also using INT1_ACC_GYR_PIN (from LSM6DS3)
    // as it also uses pin6 (PC6)

    if ( GPIO_Pin == CONN_POS3_PIN )  //PA4 --> EXTI4
    {
        LL_EXTI_DisableIT_0_31(LL_EXTI_LINE_4); 
        LL_EXTI_DisableRisingTrig_0_31(LL_EXTI_LINE_4); 
        LL_EXTI_DisableFallingTrig_0_31(LL_EXTI_LINE_4); 
    }

    if ( GPIO_Pin == CONN_POS4_PIN )  //PA3 --> EXTI3
    {
        LL_EXTI_DisableIT_0_31(LL_EXTI_LINE_3); 
        LL_EXTI_DisableRisingTrig_0_31(LL_EXTI_LINE_3); 
        LL_EXTI_DisableFallingTrig_0_31(LL_EXTI_LINE_3); 
    }

    if ( GPIO_Pin == CONN_POS5_PIN )  //PA2 --> EXTI2
    {
        LL_EXTI_DisableIT_0_31(LL_EXTI_LINE_2); 
        LL_EXTI_DisableRisingTrig_0_31(LL_EXTI_LINE_2); 
        LL_EXTI_DisableFallingTrig_0_31(LL_EXTI_LINE_2); 
    }

    if ( GPIO_Pin == CONN_POS7_PIN )  //PA1 --> EXTI1
    {
        LL_EXTI_DisableIT_0_31(LL_EXTI_LINE_1); 
        LL_EXTI_DisableRisingTrig_0_31(LL_EXTI_LINE_1); 
        LL_EXTI_DisableFallingTrig_0_31(LL_EXTI_LINE_1); 
    }

    if ( GPIO_Pin == CONN_POS8_PIN )  //PA0 --> EXTI0
    {
        LL_EXTI_DisableIT_0_31(LL_EXTI_LINE_0); 
        LL_EXTI_DisableRisingTrig_0_31(LL_EXTI_LINE_0); 
        LL_EXTI_DisableFallingTrig_0_31(LL_EXTI_LINE_0); 
    }

    if ( GPIO_Pin == CONN_POS10_PIN )  //PB8 --> EXTI5_9
    {
        LL_EXTI_DisableIT_0_31(LL_EXTI_LINE_8); 
        LL_EXTI_DisableRisingTrig_0_31(LL_EXTI_LINE_8); 
        LL_EXTI_DisableFallingTrig_0_31(LL_EXTI_LINE_8); 
    }

    if ( GPIO_Pin == CONN_POS11_PIN )  //PB9 --> EXTI5_9
    {
        LL_EXTI_DisableIT_0_31(LL_EXTI_LINE_9); 
        LL_EXTI_DisableRisingTrig_0_31(LL_EXTI_LINE_9); 
        LL_EXTI_DisableFallingTrig_0_31(LL_EXTI_LINE_9); 
    }

}


/********
* Function :	
	void LBF_SoftIT_EXTI_ExtPort(uint16_t  GPIO_Pin); 
* Description :	
	Generates a software interrupt (sets the interrupt pending flag) on the EXTI interrupt line associated to the specified pin ( since all GPIOs of different ports bearing the same pin number are associated to the same EXTI, only the pin number is necessary here ). 
* Parameters : 
	> GPIO_Pin : pin number (or alias) of the GPIO pin available on the extension port which needs to be enabled as EXTI interrupt line. See file LBF_pin_aliases.h for a proposal list of meaningful port name and pin number aliases.
* Return Value:  -
********/

void LBF_SoftIT_EXTI_ExtPort( uint16_t  GPIO_Pin)
{
    if ( GPIO_Pin == CONN_POS2_PIN )  //PA6 --> EXTI5_9
    {
        LL_EXTI_GenerateSWI_0_31(LL_EXTI_LINE_6); 
    }

    if ( GPIO_Pin == CONN_POS3_PIN )  //PA4 --> EXTI4
    {
        LL_EXTI_GenerateSWI_0_31(LL_EXTI_LINE_4); 
    }

    if ( GPIO_Pin == CONN_POS4_PIN )  //PA3 --> EXTI3
    {
        LL_EXTI_GenerateSWI_0_31(LL_EXTI_LINE_3); 
    }

    if ( GPIO_Pin == CONN_POS5_PIN )  //PA2 --> EXTI2
    {
        LL_EXTI_GenerateSWI_0_31(LL_EXTI_LINE_2); 
    }

   if ( GPIO_Pin == CONN_POS7_PIN )  //PA1 --> EXTI1
    {
        LL_EXTI_GenerateSWI_0_31(LL_EXTI_LINE_1); 
    }

   if ( GPIO_Pin == CONN_POS8_PIN )  //PA0 --> EXTI0
    {
        LL_EXTI_GenerateSWI_0_31(LL_EXTI_LINE_0); 
    }

   if ( GPIO_Pin == CONN_POS10_PIN )  //PB8 --> EXTI5_9
    {
        LL_EXTI_GenerateSWI_0_31(LL_EXTI_LINE_8); 
    }

   if ( GPIO_Pin == CONN_POS11_PIN )  //PB9 --> EXTI5_9
    {
        LL_EXTI_GenerateSWI_0_31(LL_EXTI_LINE_9); 
    }

}

/**********
* Function :	
	bool LBF_IsPending_EXTI_ExtPort(uint16_t  GPIO_Pin); 
* Description :	
	Indicates if an interrupt is pending on the EXTI  line associated to the specified pin ( since all GPIOs of different ports bearing the same pin number are associated to the same EXTI, only the pin number is necessary here ). 
* Parameters : 
	> GPIO_Pin : pin number (or alias) of the GPIO pin available on the extension port which needs to be enabled as EXTI interrupt line. See file LBF_pin_aliases.h for a proposal list of meaningful port name and pin number aliases.
* Return Value:  
	true if EXTI interrupt is pending, else false
***********/

bool LBF_IsPending_EXTI_ExtPort( uint16_t  GPIO_Pin)
{
bool status = false;

    if ( GPIO_Pin == CONN_POS2_PIN )  //PA6 --> EXTI5_9
    {
        status = LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_6); 
    }

    if ( GPIO_Pin == CONN_POS3_PIN )  //PA4 --> EXTI4
    {
        status = LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_4); 
    }

    if ( GPIO_Pin == CONN_POS4_PIN )  //PA3 --> EXTI3
    {
        status = LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_3); 
    }

    if ( GPIO_Pin == CONN_POS5_PIN )  //PA2 --> EXTI2
    {
        status = LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_2); 
    }

    if ( GPIO_Pin == CONN_POS7_PIN )  //PA1 --> EXTI1
    {
        status = LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_1); 
    }

    if ( GPIO_Pin == CONN_POS8_PIN )  //PA0 --> EXTI0
    {
        status = LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_0); 
    }

    if ( GPIO_Pin == CONN_POS10_PIN )  //PB8 --> EXTI5_9
    {
        status = LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_8); 
    }

    if ( GPIO_Pin == CONN_POS11_PIN )  //PB9 --> EXTI5_9
    {
        status = LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_9); 
    }
    return status;
}


/***********
* Function :	
	void LBF_Clear_EXTI_ExtPort(uint16_t  GPIO_Pin); 
* Description :	
	Clears any pending interrupt on the EXTI  line associated to the specified pin ( since all GPIOs of different ports bearing the same pin number are associated to the same EXTI, only the pin number is necessary here ). 
* Parameters : 
	> GPIO_Pin : pin number (or alias) of the GPIO pin available on the extension port which needs to be enabled as EXTI interrupt line. See file LBF_pin_aliases.h for a proposal list of meaningful port name and pin number aliases.
* Return Value:  -
*************/

void LBF_Clear_EXTI_ExtPort( uint16_t  GPIO_Pin)
{
    if ( GPIO_Pin == CONN_POS2_PIN )  //PA6 --> EXTI5_9
    {
        LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_6); 
    }

    if ( GPIO_Pin == CONN_POS3_PIN )  //PA4 --> EXTI4
    {
        LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_4); 
    }

    if ( GPIO_Pin == CONN_POS4_PIN )  //PA3 --> EXTI3
    {
        LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_3); 
    }

    if ( GPIO_Pin == CONN_POS5_PIN )  //PA2 --> EXTI2
    {
        LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_2); 
    }

    if ( GPIO_Pin == CONN_POS7_PIN )  //PA1 --> EXTI1
    {
        LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_1); 
    }

    if ( GPIO_Pin == CONN_POS8_PIN )  //PA0 --> EXTI0
    {
        LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_0); 
    }

    if ( GPIO_Pin == CONN_POS10_PIN )  //PB8 --> EXTI5_9
    {
        LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_8); 
    }

    if ( GPIO_Pin == CONN_POS11_PIN )  //PB9 --> EXTI5_9
    {
        LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_9); 
    }

}


/**********
* Function :	
	void LBF_Enable_NVIC_EXTI_ExtPort(uint16_t  GPIO_Pin); 
* Description :	
	Enables the NVIC for the *group* of interrupt sources containing the EXTI line associated to the specified pin (see also note below). The priority of this interrupt group is set according to __EXTIxx_IRQn_PRIO specified in user file IT_Priorities_UserDefinable.h. The subpriority is irrelevant as the NVIC has been set to not use subpriority bits at the baord initialization phase.
* Parameters : 
	> GPIO_Pin :  based on this parameter (pin number or alias), the correspoding EXTI line is identified and it is the group to which this EXTI belongs that gets enabled at NVIC level
* Return Value:  -
* Note :   
	Some interrupt sources are combined before entering the NVIC. In the case of EXTI interrupts from STM32 GPIOs, EXTI0 to EXTI4 are independent, EXTI5 to EXTI9 are grouped into EXTI5_9 and EXTI10 to EXTI15 are grouped into EXTI15_10.
**********/

void LBF_Enable_NVIC_EXTI_ExtPort( uint16_t  GPIO_Pin )
{

  // ---- Set Nested Vectored Interrupt Controller (NVIC)  ---

  // BEWARE :
  // Several lines are mapped to the same input of the STM32L4's NVIC :
  // Lines 0 to 4 are independent
  // Lines 5-9 are combined into EXTI5_9
  // Lines 10-10 are combined into EXTI10_15
  // Note also that one line may come from any STM32 pin that bears
  // that number (e.g. Line0 combines PA0, PB0, PC0...
  // So better enable only one pin of a given rank as EXTI

  // --------------------------------------------------------------------
  // EXTI0 :

    if ( GPIO_Pin == CONN_POS8_PIN )  //Position 8 = PA0 --> EXTI0
    {
#ifdef __EXTI0_IRQn_PRIO
         HAL_NVIC_SetPriority(EXTI0_IRQn, __EXTI0_IRQn_PRIO , 0); 
#else
         HAL_NVIC_SetPriority(EXTI0_IRQn, 0xA , 0);  // default priority level if not user specified
#endif
         HAL_NVIC_EnableIRQ(EXTI0_IRQn);  
    }

  // --------------------------------------------------------------------
  // EXTI1 :

    if ( GPIO_Pin == CONN_POS7_PIN )  //Position 7 = PA1 --> EXTI1
    {
#ifdef __EXTI1_IRQn_PRIO
         HAL_NVIC_SetPriority(EXTI1_IRQn, __EXTI1_IRQn_PRIO , 0); 
#else
         HAL_NVIC_SetPriority(EXTI1_IRQn, 0xA , 0);  // default priority level if not user specified
#endif
         HAL_NVIC_EnableIRQ(EXTI1_IRQn);  
    }

  // --------------------------------------------------------------------
  // EXTI2 :

    if ( GPIO_Pin == CONN_POS5_PIN )  //Position 5 = PA2 --> EXTI2
    {
#ifdef __EXTI2_IRQn_PRIO
         HAL_NVIC_SetPriority(EXTI2_IRQn, __EXTI2_IRQn_PRIO , 0); 
#else
         HAL_NVIC_SetPriority(EXTI2_IRQn, 0xA , 0);  // default priority level if not user specified
#endif
         HAL_NVIC_EnableIRQ(EXTI2_IRQn);  
    }
    // CAUTION: Conflict if also using IRQ from VL6180X on PB2 
    // as it means 2 sources of IRQ on the same EXTI2


  // --------------------------------------------------------------------
  // EXTI3 :

    if ( GPIO_Pin == CONN_POS4_PIN )  //Position 4 = PA3 --> EXTI3
    {
#ifdef __EXTI3_IRQn_PRIO
         HAL_NVIC_SetPriority(EXTI3_IRQn, __EXTI3_IRQn_PRIO , 0); 
#else
         HAL_NVIC_SetPriority(EXTI3_IRQn, 0xA , 0);  // default priority level if not user specified
#endif
         HAL_NVIC_EnableIRQ(EXTI3_IRQn);  
    }

  // --------------------------------------------------------------------
  // EXTI4 :

    if ( GPIO_Pin == CONN_POS3_PIN )  //Position 3 = PA4 --> EXTI4
    {
#ifdef __EXTI4_IRQn_PRIO
         HAL_NVIC_SetPriority(EXTI4_IRQn, __EXTI4_IRQn_PRIO , 0); 
#else
         HAL_NVIC_SetPriority(EXTI4_IRQn, 0xA , 0);  // default priority level if not user specified
#endif
         HAL_NVIC_EnableIRQ(EXTI4_IRQn);  
    }

  // --------------------------------------------------------------------
  // EXTI9_5 :

    if  (  ( GPIO_Pin == CONN_POS2_PIN )   //Position 2  = PA6 --> EXTI9_5
	|| ( GPIO_Pin == CONN_POS10_PIN )  //Position 10 = PB8 --> EXTI9_5
	|| ( GPIO_Pin == CONN_POS11_PIN )) //Position 11 = PB9 --> EXTI9_5
    {
#ifdef __EXTI9_5_IRQn_PRIO
         HAL_NVIC_SetPriority(EXTI9_5_IRQn, __EXTI9_5_IRQn_PRIO , 0); 
#else
         HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0xA , 0);  // default priority level if not user specified
#endif
         HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);  
    }
    // CAUTION: Conflict if also using INT1 from LSM6DS3 on PC6 
    // as it means 2 sources of IRQ on the same EXTI6



  // --------------------------------------------------------------------
  // EXTI15_10 :
  //  No pin on the extension port using EXTI15_10



}


/*****************
* Function :	
	void LBF_Disable_NVIC_EXTI_ExtPort(uint16_t  GPIO_Pin); 
* Description :	
	Disables the NVIC for the *group* of interrupt sources containing the EXTI line associated to the specified pin (see also note below). 
* Parameters : 
	> GPIO_Pin : PIO_Pin : based on this parameter (pin number or alias), the correspoding EXTI line is identified and it is the group to which this EXTI belongs that gets diabled at NVIC level
* Return Value:  -
* Note :   
	CAUTION - Since the complete group of EXTI which contains the EXTI associated to the specified pin gets disabled, care must be taken that disabling the NVIC may impact the visibility of another IT that would be sharing the same EXTI group. For example, calling LBF_Disable_NVIC_EXTI_ExtPort(CONN_POS11_PIN), with CONN_POS11_PIN being an alias for GPIO_Pin_9, will disable EXTI5_9 at NVIC level and therefore also stop the STM32 from servicing any interrupt raised by EXT5 to EXTI8.
******************/

void LBF_Disable_NVIC_EXTI_ExtPort( uint16_t  GPIO_Pin )
{

  // ---- Set Nested Vectored Interrupt Controller (NVIC)  ---

  // BEWARE :
  // Several lines are mapped to the same input of the STM32L4's NVIC :
  // Lines 0 to 4 are independent
  // Lines 5-9 are combined into EXTI5_9
  // Lines 10-10 are combined into EXTI10_15
  // Note also that one line may come from any STM32 pin that bears
  // that number (e.g. Line0 combines PA0, PB0, PC0...
  // So better enable only one pin of a given rank as EXTI

  // --------------------------------------------------------------------
  // EXTI0 :

    if ( GPIO_Pin == CONN_POS8_PIN )  //Position 8 = PA0 --> EXTI0
    {
         HAL_NVIC_DisableIRQ(EXTI0_IRQn);  
    }

  // --------------------------------------------------------------------
  // EXTI1 :

    if ( GPIO_Pin == CONN_POS7_PIN )  //Position 7 = PA1 --> EXTI1
    {
         HAL_NVIC_DisableIRQ(EXTI1_IRQn);  
    }

  // --------------------------------------------------------------------
  // EXTI2 :

    if ( GPIO_Pin == CONN_POS5_PIN )  //Position 5 = PA2 --> EXTI2
    {
         HAL_NVIC_DisableIRQ(EXTI2_IRQn);  
    }


  // --------------------------------------------------------------------
  // EXTI3 :

    if ( GPIO_Pin == CONN_POS4_PIN )  //Position 4 = PA3 --> EXTI3
    {
         HAL_NVIC_DisableIRQ(EXTI3_IRQn);  
    }

  // --------------------------------------------------------------------
  // EXTI4 :

    if ( GPIO_Pin == CONN_POS3_PIN )  //Position 3 = PA4 --> EXTI4
    {
         HAL_NVIC_DisableIRQ(EXTI4_IRQn);  
    }

  // --------------------------------------------------------------------
  // EXTI9_5 :

    if  (  ( GPIO_Pin == CONN_POS2_PIN )   //Position 2  = PA6 --> EXTI9_5
	|| ( GPIO_Pin == CONN_POS10_PIN )  //Position 10 = PB8 --> EXTI9_5
	|| ( GPIO_Pin == CONN_POS11_PIN )) //Position 11 = PB9 --> EXTI9_5
    {
         HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);  
    }
    // CAUTION: Disabling EXTI9_5 at NVIC level means ALL EXTI
    // combined into EXTI9_5 get disabled 
    // (so calling LBF_Disable_NVIC_EXTI_ExtPort(CONN_POS2_PIN) for example
    //  also means EXTI8 and EXTI9 associated to CONN_POS10_PIN and
    // CONN_POS11_PIN get disabled too.



  // --------------------------------------------------------------------
  // EXTI15_10 :
  //  No pin on the extension port using EXTI15_10

}


/***************************************************************END OF FILE****/
