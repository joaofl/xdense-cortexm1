#ifndef ATMEL_START_H_INCLUDED
#define ATMEL_START_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "driver_init.h"
#include "stdio_start.h"
#include "xdense/router.h"
#include "xdense/terminal.h"
#include "drivers/i2c_xdense_driver.h"

/**
 * Initializes MCU, drivers and middleware in the project
**/
void atmel_start_init(void);

#ifdef __cplusplus
}
#endif
#endif
