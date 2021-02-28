/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_examples.h"
#include "driver_init.h"
#include "utils.h"

/* CRC Data in flash */
COMPILER_ALIGNED(4)
static const uint32_t crc_datas[] = {0x00000000,
                                     0x11111111,
                                     0x22222222,
                                     0x33333333,
                                     0x44444444,
                                     0x55555555,
                                     0x66666666,
                                     0x77777777,
                                     0x88888888,
                                     0x99999999};

/**
 * Example of using CRC_0 to Calculate CRC32 for a buffer.
 */
void CRC_0_example(void)
{
	/* The initial value used for the CRC32 calculation usually be 0xFFFFFFFF,
	 * but can be, for example, the result of a previous CRC32 calculation if
	 * generating a common CRC32 of separate memory blocks.
	 */
	uint32_t crc = 0xFFFFFFFF;
	uint32_t crc2;
	uint32_t ind;

	crc_sync_enable(&CRC_0);
	crc_sync_crc32(&CRC_0, (uint32_t *)crc_datas, 10, &crc);

	/* The read value must be complemented to match standard CRC32
	 * implementations or kept non-inverted if used as starting point for
	 * subsequent CRC32 calculations.
	 */
	crc ^= 0xFFFFFFFF;

	/* Calculate the same data with subsequent CRC32 calculations, the result
	 * should be same as previous way.
	 */
	crc2 = 0xFFFFFFFF;
	for (ind = 0; ind < 10; ind++) {
		crc_sync_crc32(&CRC_0, (uint32_t *)&crc_datas[ind], 1, &crc2);
	}
	crc2 ^= 0xFFFFFFFF;

	/* The calculate result should be same. */
	while (crc != crc2)
		;
}

/**
 * Example of using UART_W to write "Hello World" using the IO abstraction.
 */
void UART_W_example(void)
{
	struct io_descriptor *io;
	usart_sync_get_io_descriptor(&UART_W, &io);
	usart_sync_enable(&UART_W);

	io_write(io, (uint8_t *)"Hello World!", 12);
}

void I2C_0_example(void)
{
	struct io_descriptor *I2C_0_io;

	i2c_m_sync_get_io_descriptor(&I2C_0, &I2C_0_io);
	i2c_m_sync_enable(&I2C_0);
	i2c_m_sync_set_slaveaddr(&I2C_0, 0x12, I2C_M_SEVEN);
	io_write(I2C_0_io, (uint8_t *)"Hello World!", 12);
}

/**
 * Example of using UART_DBG to write "Hello World" using the IO abstraction.
 */
void UART_DBG_example(void)
{
	struct io_descriptor *io;
	usart_sync_get_io_descriptor(&UART_DBG, &io);
	usart_sync_enable(&UART_DBG);

	io_write(io, (uint8_t *)"Hello World!", 12);
}

/**
 * Example of using UART_E to write "Hello World" using the IO abstraction.
 */
void UART_E_example(void)
{
	struct io_descriptor *io;
	usart_sync_get_io_descriptor(&UART_E, &io);
	usart_sync_enable(&UART_E);

	io_write(io, (uint8_t *)"Hello World!", 12);
}

/**
 * Example of using UART_S to write "Hello World" using the IO abstraction.
 */
void UART_S_example(void)
{
	struct io_descriptor *io;
	usart_sync_get_io_descriptor(&UART_S, &io);
	usart_sync_enable(&UART_S);

	io_write(io, (uint8_t *)"Hello World!", 12);
}

/**
 * Example of using UART_N to write "Hello World" using the IO abstraction.
 */
void UART_N_example(void)
{
	struct io_descriptor *io;
	usart_sync_get_io_descriptor(&UART_N, &io);
	usart_sync_enable(&UART_N);

	io_write(io, (uint8_t *)"Hello World!", 12);
}

static struct timer_task TIMER_0_task1, TIMER_0_task2;
/**
 * Example of using TIMER_0.
 */
static void TIMER_0_task1_cb(const struct timer_task *const timer_task)
{
}

static void TIMER_0_task2_cb(const struct timer_task *const timer_task)
{
}

void TIMER_0_example(void)
{
	TIMER_0_task1.interval = 100;
	TIMER_0_task1.cb       = TIMER_0_task1_cb;
	TIMER_0_task1.mode     = TIMER_TASK_REPEAT;
	TIMER_0_task2.interval = 200;
	TIMER_0_task2.cb       = TIMER_0_task2_cb;
	TIMER_0_task2.mode     = TIMER_TASK_REPEAT;

	timer_add_task(&TIMER_0, &TIMER_0_task1);
	timer_add_task(&TIMER_0, &TIMER_0_task2);
	timer_start(&TIMER_0);
}

/**
 * Example of using PWM_0.
 */
void PWM_0_example(void)
{
	pwm_set_parameters(&PWM_0, 10000, 5000);
	pwm_enable(&PWM_0);
}

/**
 * Example of using PWM_1.
 */
void PWM_1_example(void)
{
	pwm_set_parameters(&PWM_1, 10000, 5000);
	pwm_enable(&PWM_1);
}

/**
 * Example of using PWM_2.
 */
void PWM_2_example(void)
{
	pwm_set_parameters(&PWM_2, 10000, 5000);
	pwm_enable(&PWM_2);
}
