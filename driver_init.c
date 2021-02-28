/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_init.h"
#include <peripheral_clk_config.h>
#include <utils.h>
#include <hal_init.h>
#include <hpl_gclk_base.h>
#include <hpl_pm_base.h>
#include <hpl_rtc_base.h>

struct crc_sync_descriptor CRC_0;
struct timer_descriptor    TIMER_0;

struct i2c_m_sync_desc I2C_0;

struct usart_sync_descriptor UART_W;
struct usart_sync_descriptor UART_DBG;
struct usart_sync_descriptor UART_E;
struct usart_sync_descriptor UART_S;
struct usart_sync_descriptor UART_N;

struct pwm_descriptor PWM_0;
struct pwm_descriptor PWM_1;
struct pwm_descriptor PWM_2;

/**
 * \brief CRC initialization function
 *
 * Enables CRC peripheral, clocks and initializes CRC driver
 */
void CRC_0_init(void)
{
	_pm_enable_bus_clock(PM_BUS_AHB, DSU);
	_pm_enable_bus_clock(PM_BUS_APBB, PAC1);
	crc_sync_init(&CRC_0, DSU);
}

void UART_W_PORT_init(void)
{

	gpio_set_pin_function(P_UART_W_TX, PINMUX_PA04D_SERCOM0_PAD0);

	gpio_set_pin_function(P_UART_W_RX, PINMUX_PA05D_SERCOM0_PAD1);
}

void UART_W_CLOCK_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, SERCOM0);
	_gclk_enable_channel(SERCOM0_GCLK_ID_CORE, CONF_GCLK_SERCOM0_CORE_SRC);
}

void UART_W_init(void)
{
	UART_W_CLOCK_init();
	usart_sync_init(&UART_W, SERCOM0, (void *)NULL);
	UART_W_PORT_init();
}

void I2C_0_PORT_init(void)
{

	gpio_set_pin_pull_mode(P_I2C_SDA,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(P_I2C_SDA, PINMUX_PA16C_SERCOM1_PAD0);

	gpio_set_pin_pull_mode(P_I2C_SCL,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(P_I2C_SCL, PINMUX_PA17C_SERCOM1_PAD1);
}

void I2C_0_CLOCK_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, SERCOM1);
	_gclk_enable_channel(SERCOM1_GCLK_ID_CORE, CONF_GCLK_SERCOM1_CORE_SRC);
	//_gclk_enable_channel(SERCOM1_GCLK_ID_SLOW, CONF_GCLK_SERCOM1_SLOW_SRC);
}

void I2C_0_init(void)
{
	I2C_0_CLOCK_init();
	i2c_m_sync_init(&I2C_0, SERCOM1);
	I2C_0_PORT_init();
}

void UART_DBG_PORT_init(void)
{

	gpio_set_pin_function(P_UART_DBG_TX, PINMUX_PA08D_SERCOM2_PAD0);

	gpio_set_pin_function(P_UART_DBG_RX, PINMUX_PA09D_SERCOM2_PAD1);
}

void UART_DBG_CLOCK_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, SERCOM2);
	_gclk_enable_channel(SERCOM2_GCLK_ID_CORE, CONF_GCLK_SERCOM2_CORE_SRC);
}

void UART_DBG_init(void)
{
	UART_DBG_CLOCK_init();
	usart_sync_init(&UART_DBG, SERCOM2, (void *)NULL);
	UART_DBG_PORT_init();
}

void UART_E_PORT_init(void)
{

	gpio_set_pin_function(P_UART_E_TX, PINMUX_PA22C_SERCOM3_PAD0);

	gpio_set_pin_function(P_UART_E_RX, PINMUX_PA23C_SERCOM3_PAD1);
}

void UART_E_CLOCK_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, SERCOM3);
	_gclk_enable_channel(SERCOM3_GCLK_ID_CORE, CONF_GCLK_SERCOM3_CORE_SRC);
}

void UART_E_init(void)
{
	UART_E_CLOCK_init();
	usart_sync_init(&UART_E, SERCOM3, (void *)NULL);
	UART_E_PORT_init();
}

void UART_S_PORT_init(void)
{

	gpio_set_pin_function(P_UART_S_TX, PINMUX_PA12D_SERCOM4_PAD0);

	gpio_set_pin_function(P_UART_S_RX, PINMUX_PA13D_SERCOM4_PAD1);
}

void UART_S_CLOCK_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, SERCOM4);
	_gclk_enable_channel(SERCOM4_GCLK_ID_CORE, CONF_GCLK_SERCOM4_CORE_SRC);
}

void UART_S_init(void)
{
	UART_S_CLOCK_init();
	usart_sync_init(&UART_S, SERCOM4, (void *)NULL);
	UART_S_PORT_init();
}

void UART_N_PORT_init(void)
{

	gpio_set_pin_function(P_UART_N_TX, PINMUX_PB02D_SERCOM5_PAD0);

	gpio_set_pin_function(P_UART_N_RX, PINMUX_PB03D_SERCOM5_PAD1);
}

void UART_N_CLOCK_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, SERCOM5);
	_gclk_enable_channel(SERCOM5_GCLK_ID_CORE, CONF_GCLK_SERCOM5_CORE_SRC);
}

void UART_N_init(void)
{
	UART_N_CLOCK_init();
	usart_sync_init(&UART_N, SERCOM5, (void *)NULL);
	UART_N_PORT_init();
}

/**
 * \brief Timer initialization function
 *
 * Enables Timer peripheral, clocks and initializes Timer driver
 */
static void TIMER_0_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBA, RTC);
	_gclk_enable_channel(RTC_GCLK_ID, CONF_GCLK_RTC_SRC);
	timer_init(&TIMER_0, RTC, _rtc_get_timer());
}

void PWM_0_PORT_init(void)
{

	gpio_set_pin_function(P_LED_R, PINMUX_PA15E_TC3_WO1);
}

void PWM_0_CLOCK_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, TC3);
	_gclk_enable_channel(TC3_GCLK_ID, CONF_GCLK_TC3_SRC);
}

void PWM_0_init(void)
{
	PWM_0_CLOCK_init();
	PWM_0_PORT_init();
	pwm_init(&PWM_0, TC3, _tc_get_pwm());
}

void PWM_1_PORT_init(void)
{

//	gpio_set_pin_function(P_LED_G, PINMUX_PB08E_TC4_WO0);
	gpio_set_pin_function(P_LED_G, PINMUX_PB09E_TC4_WO1);
}

void PWM_1_CLOCK_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, TC4);
	_gclk_enable_channel(TC4_GCLK_ID, CONF_GCLK_TC4_SRC);
}

void PWM_1_init(void)
{
	PWM_1_CLOCK_init();
	PWM_1_PORT_init();
	pwm_init(&PWM_1, TC4, _tc_get_pwm());
}

void PWM_2_PORT_init(void)
{
	gpio_set_pin_function(P_LED_B, PINMUX_PB11E_TC5_WO1);
}

void PWM_2_CLOCK_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, TC5);
	_gclk_enable_channel(TC5_GCLK_ID, CONF_GCLK_TC5_SRC);
}

void PWM_2_init(void)
{
	PWM_2_CLOCK_init();
	PWM_2_PORT_init();
	pwm_init(&PWM_2, TC5, _tc_get_pwm());
}

void system_init(void)
{
	init_mcu();

	// GPIO on PA19

	// Set pin direction to output
	gpio_set_pin_direction(IO_DBG, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(IO_DBG,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_function(IO_DBG, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PA27

	// Set pin direction to output
	gpio_set_pin_direction(LED, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(LED,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   true);

	gpio_set_pin_function(LED, GPIO_PIN_FUNCTION_OFF);

	CRC_0_init();

	I2C_0_init();

        UART_W_init();
	UART_DBG_init();
	UART_E_init();
	UART_S_init();
	UART_N_init();

	TIMER_0_init();

	PWM_0_init();
	PWM_1_init();
	PWM_2_init();
}
