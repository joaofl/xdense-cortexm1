#include "atmel_start.h"


/**
 * Initializes MCU, drivers and middleware in the project
**/
void atmel_start_init(void)
{
    stdio_redirect_init();

    system_init();

    config_UART_DBG();
    config_UART_E();
    config_UART_W();
    config_UART_S();
    config_UART_N();

    config_I2C();

    timer_start(&TIMER_0);
}
