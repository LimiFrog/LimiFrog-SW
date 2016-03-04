EXTENSION PORT DEMO - USING PRE-CONFIGURED SETTINGS
===================================================

User_Configuration.h instructs the LimiFrog initalization software to provide a number of different interfaces on the extension port :
 
// POS11: EXTI
// POS10: GPIO
// POS9: GND
// POS8: UART4_TX
// POS7: UART4_RX
// POS6: VCC_LDO
// POS5: SPI_MOSI over USART2_TX
// POS4: SPI_MISO over USART2_RX
// POS3: SPI_CK over USART2_CK
// POS2: PWM out
// POS1: MIC OUT

> Generate PWM signal on Position 2

> Send data over UART4 Tx and attempt to receive it back from UART Rx (if external loopback) -- using DMA

> Send MOSI SPI data and attempt to receive it back from MISO (if external loopback)

> Generate a pulse on GPIO and attempt to detect it using EXTI (if external connection)

Then get LED to stay fixed ON if receptions have all been succesful, else get it to blink.
