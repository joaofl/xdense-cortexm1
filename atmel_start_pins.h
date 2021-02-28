/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */
#ifndef ATMEL_START_PINS_H_INCLUDED
#define ATMEL_START_PINS_H_INCLUDED

#include <hal_gpio.h>

// SAMD21 has 8 pin functions

#define LOW 1
#define HIGH 0

#define GPIO_PIN_FUNCTION_A 0
#define GPIO_PIN_FUNCTION_B 1
#define GPIO_PIN_FUNCTION_C 2
#define GPIO_PIN_FUNCTION_D 3
#define GPIO_PIN_FUNCTION_E 4
#define GPIO_PIN_FUNCTION_F 5
#define GPIO_PIN_FUNCTION_G 6
#define GPIO_PIN_FUNCTION_H 7

#define P_UART_W_TX GPIO(GPIO_PORTA, 4)
#define P_UART_W_RX GPIO(GPIO_PORTA, 5)
#define P_UART_DBG_TX GPIO(GPIO_PORTA, 8)
#define P_UART_DBG_RX GPIO(GPIO_PORTA, 9)
#define P_UART_S_TX GPIO(GPIO_PORTA, 12)
#define P_UART_S_RX GPIO(GPIO_PORTA, 13)
#define P_LED_R GPIO(GPIO_PORTA, 15)
#define P_I2C_SDA GPIO(GPIO_PORTA, 16)
#define P_I2C_SCL GPIO(GPIO_PORTA, 17)
#define IO_DBG GPIO(GPIO_PORTA, 19)
#define P_UART_E_TX GPIO(GPIO_PORTA, 22)
#define P_UART_E_RX GPIO(GPIO_PORTA, 23)
#define LED GPIO(GPIO_PORTA, 27)
#define P_UART_N_TX GPIO(GPIO_PORTB, 2)
#define P_UART_N_RX GPIO(GPIO_PORTB, 3)
#define P_LED_G GPIO(GPIO_PORTB, 9)
#define P_LED_B GPIO(GPIO_PORTB, 11)

#endif // ATMEL_START_PINS_H_INCLUDED
