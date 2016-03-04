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

/* Includes ------------------------------------------------------------------*/
#include "stm32xxx_hal.h"

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

/* USER CODE BEGIN 0 */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "vl6180x_api.h"
#include "x-nucleo-6180xa1.h"

#ifdef DEBUG
	//TODO
#include "diag/trace.h"
    #define debug(msg, ...)   trace_printf(msg,__VA_ARGS__)
    #define trace_warn(msg,...) trace_printf("W %s %d" msg "\n", __func__, __LINE__, __VA_ARGS__)
#else
    #define debug(msg, ...)  (void)0
#endif

#define DigitDisplay_ms     1 /* ms each digit is kept on */
#if VL6180x_HAVE_DMAX_RANGING
#define DMaxDispTime     0 /* Set to 1000 to display Dmax during 1 sec when no target is detected */
#else
#define DMaxDispTime     0
#endif

#define OutORangeDispfTime  800

    
#define ErrRangeDispTime    0 /* Set to 800 ms to display error code when no target os detected */
#if ErrRangeDispTime == 0 
/*   supress Warning[Pe186]: pointless comparison of unsigned integer with zero */ 
#   ifdef __ARMCC_VERSION /* ARM/KEIL */
#   pragma diag_suppress 186
#   endif  /* _ARMCC_VERSION */
#   ifdef __ICCARM__ /* IAR */
#       pragma diag_suppress=Pe186
#   endif  /* _ARMCC_VERSION */    
#endif 
    
#define ScaleDispTime       800
#define AlrmDispTime        800

#define PressBPSwicthTime   1000 /* if user keep bp press more that this mean swicth mode else rooll over use c&se in mode */

#define AlarmKeepDispTime   250  /*  alarm message retain time after it fires */
    
#define ALLOW_DISABLE_WAF_FROM_BLUE_BUTTON 0 /* set to 1 to add 3 extra modes to the demo where WAF is disabled (to see impact of WAF) */

void WaitMilliSec(int ms);

/**
 * VL6180x CubeMX F401 i2c porting implementation
 */

#define theVL6180xDev   0x52    // what we use as "API device

#define i2c_bus      (&hi2c1)
#define def_i2c_time_out 100

int VL6180x_I2CWrite(VL6180xDev_t addr, uint8_t  *buff, uint8_t len){
    int status;
    status = HAL_I2C_Master_Transmit(i2c_bus,  addr, buff, len , def_i2c_time_out);
    if( status ){
        XNUCLEO6180XA1_I2C1_Init(&hi2c1);
    }
    return status;
}

int VL6180x_I2CRead(VL6180xDev_t addr, uint8_t  *buff, uint8_t len){
    int status;
    status = HAL_I2C_Master_Receive(i2c_bus,  addr, buff, len , def_i2c_time_out);
    if( status ){
        XNUCLEO6180XA1_I2C1_Init(&hi2c1);
    }

    return status;
}

void XNUCLEO6180XA1_WaitMilliSec(int n){
    WaitMilliSec(n);
}


volatile int IntrFired=0;

/* VL6180x shield user interrupt handler */
void XNUCLEO6180XA1_UserIntHandler(void){
    IntrFired ++;
}

/**
 * DISPLAY public
 */
/***************  DISPLAY PUBLIC *********************/
const char *DISP_NextString;
/***************  DISPLAY PRIVATE *********************/
static char DISP_CurString[10];
static int DISP_Loop=0;

void DISP_ExecLoopBody(void){
    if (DISP_NextString != NULL) {
        strncpy(DISP_CurString, DISP_NextString, sizeof(DISP_CurString) - 1);
        DISP_CurString[sizeof(DISP_CurString) - 1] = 0;
        DISP_NextString = NULL;
    }
    XNUCLEO6180XA1_DisplayString(DISP_CurString, DigitDisplay_ms);
    DISP_Loop++;
}

void DISP_Task(const void *arg) {
    do {
        DISP_ExecLoopBody();
    } while (1);
}

#if !FREE_RTOS

volatile uint32_t g_TickCnt;
char buff[10]="---.--";
float v=0000.1;
void HAL_SYSTICK_Callback(void){
    g_TickCnt++;
}

void WaitMilliSec(int ms){
    uint32_t start, now;
    int dif;
    start=g_TickCnt;
    //debug("waiting %d @%d\n",ms, g_TickCnt);
    do{
        now=g_TickCnt;
        dif= now -start;
    }
    while(dif<ms);
    //debug("waited  %d @%d\n",dif, g_TickCnt);
}

#else
//for FreeRtos ue os wait
void WaitMilliSec(int ms)   vTaskDelay( ms/ portTICK_PERIOD_MS)

#endif
        
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
    XNUCLEO6180XA1_EXTI_CallBackHandle(GPIO_Pin);
}

#define BSP_BP_PORT GPIOC
#define BSP_BP_PIN  GPIO_PIN_13
int BSP_GetPushButton(void){
    GPIO_PinState state ;
    state = HAL_GPIO_ReadPin(BSP_BP_PORT, BSP_BP_PIN);
    return state;
}

void SetDisplayString(const char *msg) {
    DISP_NextString=msg;
}
/**
 * call in the main loop
 * when running under debugger it enable doing direct vl6180x reg access
 * typcilay breaking at entrance
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
            debug("Wr W 0x%X = %d", reg_index,(int) reg_data);
            break;

        case -3:
            VL6180x_WrDWord(theVL6180xDev, reg_index, reg_data);
            debug("WrDW 0x%X = %d", reg_index, (int)reg_data);
            break;

        case 1:
            reg_data=0;
            VL6180x_RdByte(theVL6180xDev, reg_index, (uint8_t*)&reg_data);
            debug("RD B 0x%X = %d", reg_index, (int)reg_data);
            break;
        case 2:
            reg_data=0;
            VL6180x_RdWord(theVL6180xDev, reg_index, (uint16_t*)&reg_data);
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

volatile int VL6180x_IsrFired=0;

/**
*/

int nErr=0;
void OnErrLog(void){
    /* just log */
    nErr++;
}

enum runmode_t{
    RunRangePoll=0,
    RunAlsPoll,
    InitErr,
    ScaleSwap,
    WaitForReset,
    AlrmStart,
    AlrmRun,
    FromSwitch,
};

char buffer[10];

struct state_t {
    int OutofRAnge:1;
    int AutoScale:1;
    int FilterEn:1;
    uint8_t mode;
    int8_t ScaleSwapCnt;
    uint8_t InitScale;

    uint8_t CurAlrm;
    uint8_t AlrmFired; /* just used to keep display at least min time */
}State;

uint32_t TimeStarted;       /* various display and mode delay starting time */
VL6180x_AlsData_t   Als;    /* ALS measurement */
VL6180x_RangeData_t Range;  /* Range measurmeent  */

int alpha =(int)(0.85*(1<<16));    /* range distance running average cofs */
uint16_t range;             /* range average distance */

#define AutoThreshHigh  80  /*auto scale high thresh => AutoThreshHigh *  max_raneg => scale ++  */
#define AutoThreshLow   33  /*auto scale low thresh  => AutoThreshHigh *  max_raneg => scale ++  */

void AbortErr( const char * msg ){
    SetDisplayString( msg);
    State.mode=  WaitForReset;
}

/**
 * ALS mode idle run loops
 */
void AlsState(void)
{
    int status;
    status = VL6180x_AlsPollMeasurement(theVL6180xDev, &Als);
    if (status) {
        SetDisplayString("Er 4");
    } else {
        if (Als.lux > 9999) {
            sprintf(buffer, "L----" );
        }
        else if (Als.lux > 999) {
            sprintf(buffer, "L%d.%02d", (int) Als.lux / 1000, (int) (Als.lux % 1000) / 10); /* show LX.YY  X k Lux 2 digit*/
        } else {
            sprintf(buffer, "l%3d", (int) Als.lux);
        }
        SetDisplayString( buffer );
    }
}

void InitAlsMode(void){
    //anything after prepare and prior to go into AlsState
    int time = 100;
    VL6180x_AlsSetIntegrationPeriod(theVL6180xDev, time);
}


/**
 * Manage UI and state for scale change
 *
 * @param scaling the next scaling factor
 */
void DoScalingSwap(int scaling){
    if( State.AutoScale){
        if( State.FilterEn )
            SetDisplayString("Sf A");
        else
            SetDisplayString("Sc A");
    }
    else{
        if( State.FilterEn )
            sprintf(buffer, "Sf %d", (int)scaling);
        else
            sprintf(buffer, "Sc %d", (int)scaling);
        SetDisplayString(buffer);

    }
    State.mode = ScaleSwap;
    TimeStarted=g_TickCnt;
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
int PusbButton_WaitUnPress(void){
    TimeStarted = g_TickCnt;
    while( !BSP_GetPushButton() ){ ; /* debounce */
        DISP_ExecLoopBody();
        if( g_TickCnt - TimeStarted> PressBPSwicthTime){
            SetDisplayString (" rb ");
        }
    }
    return  g_TickCnt - TimeStarted>PressBPSwicthTime;

}

void AlarmShowMode(const char *msg)
{
    SetDisplayString( msg);
    TimeStarted=g_TickCnt;
    do {
        DISP_ExecLoopBody();
    } while (g_TickCnt - TimeStarted < AlrmDispTime);
}

void AlarmLowThreshUseCase(void){
    AlarmShowMode("A-Lo");

    /* make sure from now on all register in group are not fetched by device */
    VL6180x_SetGroupParamHold(theVL6180xDev, 1);

    /* get interrupt whenever we go below 200mm */
    VL6180x_RangeSetThresholds(theVL6180xDev, 200, 0, 0 );
    /* set range interrupt reporting low threshold*/
    VL6180x_RangeConfigInterrupt(theVL6180xDev, CONFIG_GPIO_INTERRUPT_LEVEL_LOW);

    /* leave device peak up all new register in group */
    VL6180x_SetGroupParamHold(theVL6180xDev, 0);

    /* clear any interrupt that should ensure a new edge get generated even if we missed it */
    VL6180x_RangeClearInterrupt(theVL6180xDev);
}

void AlarmHighThreshUseCase(void){
    AlarmShowMode("A-hi");
    /* make sure from now on all register in group are not fetched by device */
    VL6180x_SetGroupParamHold(theVL6180xDev, 1);

    /* get interrupt whenever  higher than 200mm (low threshold don't care) */
    VL6180x_RangeSetThresholds(theVL6180xDev, 0, 200, 0 );

    /* set range interrupt reporting high threshold*/
    VL6180x_RangeConfigInterrupt(theVL6180xDev, CONFIG_GPIO_INTERRUPT_LEVEL_HIGH);

    /* leave device peak up all new register in group */
    VL6180x_SetGroupParamHold(theVL6180xDev, 0);

    /* clear any interrupt that should ensure a new edge get generated even if we missed it */
    VL6180x_RangeClearInterrupt(theVL6180xDev);

}

void AlarmWindowThreshUseCase(void){

    AlarmShowMode("A-0o");

    /* make sure from now on all register in group are not fetched by device */
    VL6180x_SetGroupParamHold(theVL6180xDev, 1);

    /* get interrupt whenever  out of  100mm  250mm  range */
    VL6180x_RangeSetThresholds(theVL6180xDev, 100, 200, 0 );

    /* set range interrupt reporting out of window  */
    VL6180x_RangeConfigInterrupt(theVL6180xDev, CONFIG_GPIO_INTERRUPT_OUT_OF_WINDOW);

    /* leave device peak up all new register in group */
    VL6180x_SetGroupParamHold(theVL6180xDev, 0);

    /* clear any interrupt that should ensure a new edge get generated even if we missed it */
    VL6180x_RangeClearInterrupt(theVL6180xDev);

}

void AlarmUpdateUseCase(void)
{
    State.CurAlrm =(State.CurAlrm%3);

    switch ( State.CurAlrm) {
    case 0: /* low thresh */
        AlarmLowThreshUseCase();
        break;
    case 1: /* high thresh */
        AlarmHighThreshUseCase();;
        break;
    case 2: /* out of window */
        AlarmWindowThreshUseCase();
    }
    VL6180x_RangeClearInterrupt(theVL6180xDev); /* clear any active interrupt it will ensure we get a new active edge is raised */
}


void AlarmStop(void){
    VL6180x_RangeSetSystemMode(theVL6180xDev, MODE_CONTINUOUS|MODE_START_STOP);
    /* Wait some time for last potential measure to stop ?
     * TODO can we poll check something to avoid that delay? */
    WaitMilliSec(100);
    /* Clear any left pending interrupt
     * these is not mandatory or a left uncleared status can mess-up next intr mode change and status check  without a prior intr clear */
    VL6180x_ClearAllInterrupt(theVL6180xDev);

    /* Anover way to stop is to switch and trigger a single shot measure (in a safe way)
     * set interrupt report mode new sample ready
     * clear interrupt
     * kick of a measure
     * poll for measure ready
     * all that can take up to arround 2x max convergence time typically set to 50ms  */

    /* TODO we can also disable the output pin to save some current */

    /* disable  interrupt handling at CPU level */
    XNUCLEO6180XA1_DisableInterrupt();

}

/**
 * Initiate alarm (interrupt mode on distance threshold)
 */
void AlarmInit(void){
    State.mode = AlrmRun;
    TimeStarted=g_TickCnt;
    uint16_t InterMeasPeriod=50; /* 10 ms is the minimal */
    /* We assume device is stopped  */

    VL6180x_Prepare(theVL6180xDev);
    /* Increase convergence time to the max (this is because proximity config of API is used) */
    VL6180x_RangeSetMaxConvergenceTime(theVL6180xDev, 63);
    /* set max upscale so we can work up to some  50cm */
    VL6180x_UpscaleSetScaling(theVL6180xDev, 3);

    /* set inter measurement period (that is in fact inter measure time)
     * note that when low refresh rate  is need time like 100ms is best to keep power low  */
    VL6180x_RangeSetInterMeasPeriod(theVL6180xDev, InterMeasPeriod);
    /* if fast reaction is required then set a time of 0 (will set minimal possible) */
    /* VL6180x_RangeSetInterMeasPeriod(theVL6180xDev, 0); */

    /* setup gpio1 pin to range interrupt output with high polarity (rising edge) */
    VL6180x_SetupGPIO1(theVL6180xDev, GPIOx_SELECT_GPIO_INTERRUPT_OUTPUT, INTR_POL_HIGH);
    /* set threshold for current used case and update the display */
    AlarmUpdateUseCase();
    /* enable interrupt at CPU level */
    XNUCLEO6180XA1_EnableInterrupt();
    /*Clear any pending device interrupt even if already active it should force a new edge so we can pick up*/
    VL6180x_ClearAllInterrupt(theVL6180xDev);

    /* start continuous mode */
    VL6180x_RangeSetSystemMode(theVL6180xDev, MODE_START_STOP|MODE_CONTINUOUS);
    /* from now vl6180x is running on it's own and will interrupt us when condition is met
     * the interrupt set a flag peek-up in AlarmState run loop*/
}


/**
 * Alarm mode idle run
 *
 * We only here look at the volatile interrupt flags set that from isr
 * the isr manage to clear interrupt at cpu level
 * we Here clear and re-arm/clear interrupt at the the device level and do the UI and display
 */
void AlarmState(void){
    IntrStatus_t IntStatus;
    int status;

    if (IntrFired != 0) {
    /* Interrupt did fired Get interrupt  causes */
        status = VL6180x_RangeGetInterruptStatus(theVL6180xDev, &IntStatus.val);
        if (status) {
            AbortErr("Al 1");
            goto done;
        }
        switch( IntStatus.status.Range ) {
        case RES_INT_STAT_GPIO_LOW_LEVEL_THRESHOLD :
            SetDisplayString("L---");
            break;
        case RES_INT_STAT_GPIO_HIGH_LEVEL_THRESHOLD :
            SetDisplayString("H---");
            break;
        case RES_INT_STAT_GPIO_OUT_OF_WINDOW :
            SetDisplayString("O---");
            break;
        case RES_INT_STAT_GPIO_NEW_SAMPLE_READY:
            SetDisplayString("n---");
            break;
        }
        VL6180x_RangeClearInterrupt(theVL6180xDev); /* clear it */
        IntrFired = 0;
        TimeStarted=g_TickCnt;
        State.AlrmFired = 1;
    }
    else{
        int flush=0;
        //sanity check we are not in a state where i/o is active without an edge
        if( g_TickCnt-TimeStarted> 5000 ){
            if( flush )
                VL6180x_RangeClearInterrupt(theVL6180xDev); /* clear it */
            TimeStarted=g_TickCnt;
        }
    }
    if( State.AlrmFired ){
        /* After an interrupt fire keep the display message for some minimal time
         * over wise it could not be visible at all */
        if( g_TickCnt-TimeStarted > AlarmKeepDispTime )
            State.AlrmFired = 0;
    }
    else{
        /* show what alarm mode we are one */
        switch( State.CurAlrm ){
            case 0 :
                SetDisplayString("L"); /* low */
                break;
            case 1 :
                SetDisplayString("H"); /* high */
                break;
            case 2:
                SetDisplayString("O"); /* window */
                break;
        }
    }
    /* keep On refreshing display at every idle loop */
    DISP_ExecLoopBody();

    if( !BSP_GetPushButton() ){
        /* when button get presses wait it get release (keep doing display) */
        status = PusbButton_WaitUnPress();
        if( status ){
            /* BP stay pressed very long time switch back to range/als  */
            AlarmStop();
            State.mode=FromSwitch;
        }
        else{
            /* BP short pressed switch use case  */
            State.CurAlrm=(State.CurAlrm+1)%3;
            AlarmUpdateUseCase();
        }
    }

done:
    ;
}

void GoToAlaramState(void) {
    AlarmInit();
}

/**
 * Ranging mode idle loop
 */
void RangeState(void) {
    int status;
    uint16_t hlimit;
    uint8_t scaling;

    scaling = VL6180x_UpscaleGetScaling(theVL6180xDev);
    status = VL6180x_RangePollMeasurement(theVL6180xDev, &Range); /* these invoke dipslay for  polling */
    if (status) {
        AbortErr("Er r");
        return;
    }

    hlimit = VL6180x_GetUpperLimit(theVL6180xDev);
    if (Range.range_mm >= (hlimit * AutoThreshHigh) / 100 && scaling < 3 && State.AutoScale) {
        VL6180x_UpscaleSetScaling(theVL6180xDev, scaling + 1);
    }
    if (Range.range_mm < (hlimit * AutoThreshLow) / 100 && scaling > 1 && State.AutoScale) {
        VL6180x_UpscaleSetScaling(theVL6180xDev, scaling - 1);
    }

    if (Range.errorStatus) {
        /* no valid ranging*/
        if (State.OutofRAnge) {
#if VL6180x_HAVE_DMAX_RANGING
            if (g_TickCnt - TimeStarted >= ErrRangeDispTime &&  g_TickCnt - TimeStarted <  ErrRangeDispTime + DMaxDispTime ){
                    sprintf(buffer, "d%3d", (int)Range.DMax);
                    SetDisplayString(buffer);
            }
            else
            
#endif
            if(g_TickCnt - TimeStarted < ErrRangeDispTime  )
            {

                sprintf(buffer, "rE%2d", (int) Range.errorStatus);
                SetDisplayString(buffer);
            }
            else{
                State.OutofRAnge=0; /* back to out of range display */
                TimeStarted=g_TickCnt;
            }
        }
        else {
            int FilterEn;
#if VL6180x_WRAP_AROUND_FILTER_SUPPORT
            FilterEn = VL6180x_FilterGetState(theVL6180xDev);
            if (FilterEn && VL6180x_RangeIsFilteredMeasurement(&Range) ){
                SetDisplayString("F---");
            }
            else
                SetDisplayString("r---");
#else
            SetDisplayString("r---");
#endif
            if( g_TickCnt - TimeStarted > OutORangeDispfTime ) {
                State.OutofRAnge = 1;
                TimeStarted = g_TickCnt;
            }
        }
    }
    else {
        State.OutofRAnge = 0;
        TimeStarted = g_TickCnt;
        range = (range * alpha + Range.range_mm * ((1 << 16) - alpha)) >> 16;
        sprintf(buffer, "r%3d", (int) range);
        if (State.AutoScale) {
            if (scaling == 1) {
                buffer[0] = '_';
            }
            else
                if (scaling == 2)
                    buffer[0] = '=';
                else
                    buffer[0] = '~';
        }

        SetDisplayString(buffer);
    }

#define max_scale 3
    if (!BSP_GetPushButton()) {
        TimeStarted = g_TickCnt;
        status = PusbButton_WaitUnPress();
        if (status) {
            GoToAlaramState();
            return;
        }
        State.ScaleSwapCnt++;
        if (State.ScaleSwapCnt % (max_scale + 1) == max_scale) {
            State.AutoScale = 1;
            scaling = max_scale;
        }
        else {
#if ALLOW_DISABLE_WAF_FROM_BLUE_BUTTON
            /* togle filtering every time we roll over all scaling(pass by autoscale) */
            if (State.AutoScale)
                State.FilterEn = !State.FilterEn;
#endif
            State.AutoScale = 0;
            scaling = State.InitScale + (State.ScaleSwapCnt % max_scale);
            if (scaling > max_scale)
                scaling = scaling - (max_scale);
        }

        status = VL6180x_UpscaleSetScaling(theVL6180xDev, scaling);
        if (status<0) {
            AbortErr("ErUp");
            State.mode = InitErr;
        }
        else {
            /* do not check status may fail when filter support not active */
            VL6180x_FilterSetState(theVL6180xDev, State.FilterEn);
            DoScalingSwap(scaling);
        }
    }
}

/**
 * Idle mode Error (do nothing)
 */
void ErState(void){

}

/* USER CODE END 0 */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);

int main(void)
{

  /* USER CODE BEGIN 1 */
    int status;
    int new_switch_state;
    int switch_state = -1;
    State.mode = 1;
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* System interrupt init*/
#ifdef STM32F401xE  
  /* Sets the priority grouping field */
  HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_0);
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
#endif

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();

  /* USER CODE BEGIN 2 */
  /* these almost just redo what already done just above by CubeMx Init
   * but it get tested and can be re place cube-mx init code :) */
    XNUCLEO6180XA1_GPIO_Init();
    XNUCLEO6180XA1_I2C1_Init(&hi2c1);

  /* USER CODE END 2 */

  /* USER CODE BEGIN 3 */
    /* SysTick end of count event each 1ms */
    SysTick_Config(HAL_RCC_GetHCLKFreq() / 1000);

    /* reset_test(); */
    XNUCLEO6180XA1_Reset(0);
    WaitMilliSec(10);
    XNUCLEO6180XA1_Reset(1);
    WaitMilliSec(1);
    /* Note that as we waited  1msec we could bypass VL6180x_WaitDeviceBooted(theVL6180xDev); */
    VL6180x_WaitDeviceBooted(theVL6180xDev);
    VL6180x_InitData(theVL6180xDev);

    State.InitScale=VL6180x_UpscaleGetScaling(theVL6180xDev);
    State.FilterEn=VL6180x_FilterGetState(theVL6180xDev);
    
    /* Enable Dmax calculation only if value is displayed (to save computation power) */
    VL6180x_DMaxSetState(theVL6180xDev, DMaxDispTime>0);

    switch_state=-1 ; /* force what read from switch to set new working mode */
    State.mode = AlrmStart;
    /* Infinite loop */
    while (1) {
        new_switch_state = XNUCLEO6180XA1_GetSwitch();
        if (new_switch_state != switch_state) {
            switch_state=new_switch_state;
            status = VL6180x_Prepare(theVL6180xDev);
            /* Increase convergence time to the max (this is because proximity config of API is used) */
            VL6180x_RangeSetMaxConvergenceTime(theVL6180xDev, 63);
            if (status) {
                AbortErr("ErIn");
            }
            else{
                if (switch_state == SWITCH_VAL_RANGING) {
                    VL6180x_SetupGPIO1(theVL6180xDev, GPIOx_SELECT_GPIO_INTERRUPT_OUTPUT, INTR_POL_HIGH);
                    VL6180x_ClearAllInterrupt(theVL6180xDev);
                    State.ScaleSwapCnt=0;
                    DoScalingSwap( State.InitScale);
                } else {
                     State.mode = RunAlsPoll;
                     InitAlsMode();
                }
            }
        }

        switch (State.mode) {
        case RunRangePoll:
            RangeState();
            break;

        case RunAlsPoll:
            AlsState();
            break;

        case InitErr:
            TimeStarted = g_TickCnt;
            State.mode = WaitForReset;
            break;

        case AlrmStart:
           GoToAlaramState();
           break;

        case AlrmRun:
            AlarmState();
            break;

        case FromSwitch:
            /* force reading swicth as re-init selected mode  */
            switch_state=!XNUCLEO6180XA1_GetSwitch();
            break;

        case ScaleSwap:

            if (g_TickCnt - TimeStarted >= ScaleDispTime) {
                State.mode = RunRangePoll;
                TimeStarted=g_TickCnt; /* reset as used for --- to er display */
            }
            else
                DISP_ExecLoopBody();
            break;

        default:
#if !FREE_RTOS
            DISP_ExecLoopBody();
#endif
            if (g_TickCnt - TimeStarted >= 5000) {
                NVIC_SystemReset();
            }
        }

        debug_stuff();
    }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
#ifdef STM32F401xE
void SystemClock_Config(void)
{

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

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);

}
#endif
#ifdef STM32L053xx
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

  __PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_4;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_2;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1);

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

  __SYSCFG_CLK_ENABLE();
}
#endif

#ifdef STM32L476xx
void SystemClock_Config(void)
{
	 RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4);

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

  __PWR_CLK_ENABLE();

  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}
#endif

/* I2C1 init function */
#ifdef STM32F401xE
void MX_I2C1_Init(void)
{

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
#endif
#ifdef STM32L053xx
void MX_I2C1_Init(void)
{

  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x00000000;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLED;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLED;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLED;
  HAL_I2C_Init(&hi2c1);

  /**Configure Analogue filter 
  */
  HAL_I2CEx_AnalogFilter_Config(&hi2c1, I2C_ANALOGFILTER_ENABLED);
}
#endif

#ifdef STM32L476xx
void MX_I2C1_Init(void)
{

  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x00702991;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLED;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLED;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLED;
  HAL_I2C_Init(&hi2c1);

    /**Configure Analogue filter 
    */
  HAL_I2CEx_AnalogFilter_Config(&hi2c1, I2C_ANALOGFILTER_ENABLED);

}
#endif

#ifdef STM32F401xE
/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
     PA2   ------> USART2_TX
     PA3   ------> USART2_RX
*/
void MX_GPIO_Init(void)
{

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
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_5 
                          |GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PA2 PA3 */
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PA6 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB10 PB4 PB5 
                           PB6 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_10|GPIO_PIN_4|GPIO_PIN_5 
                          |GPIO_PIN_6;
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
#endif
#ifdef STM32L053xx
/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

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

  /*Configure GPIO pin : PA5 */
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}
#endif


#ifdef STM32L476xx
/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
     PA2   ------> USART2_TX
     PA3   ------> USART2_RX
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __GPIOC_CLK_ENABLE();
  __GPIOH_CLK_ENABLE();
  __GPIOA_CLK_ENABLE();
  __GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA2 PA3 */
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PA5 */
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}
#endif

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

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

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
