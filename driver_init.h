/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */
#ifndef DRIVER_INIT_INCLUDED
#define DRIVER_INIT_INCLUDED

#include "atmel_start_pins.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <hal_atomic.h>
#include <hal_delay.h>
#include <hal_gpio.h>
#include <hal_init.h>
#include <hal_io.h>
#include <hal_sleep.h>
#include <hal_crc_sync.h>
#include <hal_usart_sync.h>
#include <hal_i2c_m_sync.h>
#include <hal_timer.h>
#include <hal_pwm.h>
#include <hpl_tc_base.h>

extern struct crc_sync_descriptor CRC_0;

extern struct i2c_m_sync_desc I2C_0;

extern struct usart_sync_descriptor UART_W;
extern struct usart_sync_descriptor UART_DBG;
extern struct usart_sync_descriptor UART_E;
extern struct usart_sync_descriptor UART_S;
extern struct usart_sync_descriptor UART_N;

extern struct timer_descriptor      TIMER_0;

extern struct pwm_descriptor PWM_0;
extern struct pwm_descriptor PWM_1;
extern struct pwm_descriptor PWM_2;

void UART_W_PORT_init(void);
void UART_W_CLOCK_init(void);
void UART_W_init(void);

void I2C_0_CLOCK_init(void);
void I2C_0_init(void);
void I2C_0_PORT_init(void);

void UART_DBG_PORT_init(void);
void UART_DBG_CLOCK_init(void);
void UART_DBG_init(void);

void UART_E_PORT_init(void);
void UART_E_CLOCK_init(void);
void UART_E_init(void);

void UART_S_PORT_init(void);
void UART_S_CLOCK_init(void);
void UART_S_init(void);

void UART_N_PORT_init(void);
void UART_N_CLOCK_init(void);
void UART_N_init(void);

void PWM_0_PORT_init(void);
void PWM_0_CLOCK_init(void);
void PWM_0_init(void);

void PWM_1_PORT_init(void);
void PWM_1_CLOCK_init(void);
void PWM_1_init(void);

void PWM_2_PORT_init(void);
void PWM_2_CLOCK_init(void);
void PWM_2_init(void);

/**
 * \brief Perform system initialization, initialize pins and clocks for
 * peripherals
 */
void system_init(void);

#ifdef __cplusplus
}
#endif
#endif // DRIVER_INIT_INCLUDED
