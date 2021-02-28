/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   flasher.h
 * Author: joao
 *
 * Created on July 12, 2017, 8:53 PM
 */

#ifndef FLASHER_H
#define FLASHER_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdio_io.h>
//#include <peripheral_clk_config.h>
#include <hpl_sercom_config.h>
#include "packet.h"
#include "driver_init.h"
#include "utils.h"
#include "router.h"

#define FLASHER_DEBUG

#define BOOT_DOUBLE_TAP_ADDRESS     (0x20007FFCul)
#define DOUBLE_TAP_MAGIC            0x07738135
#define BOOT_DOUBLE_TAP_DATA        (*((volatile uint32_t *) BOOT_DOUBLE_TAP_ADDRESS))

#define BOOT_PORT_SELECTED_ADDRESS  (0x20007EFCul)
#define BOOT_PORT_SELECT_UART_DBG   0x00000000 //default
#define BOOT_PORT_SELECT_UART_N     0x03210001
#define BOOT_PORT_SELECT_UART_S     0x03210002
#define BOOT_PORT_SELECT_UART_E     0x03210003
#define BOOT_PORT_SELECT_UART_W     0x03210004
#define BOOT_PORT_SELECTED_DATA     (*((volatile uint32_t *) BOOT_PORT_SELECTED_ADDRESS))

#define FLASH_START_ADDR 	0x00002000
#define SRAM_START_ADDR 	0x20005000

// XMODEM definitions
#define XMODEM_BLK_SIZE    128
#define XMODEM_MAX_RETRIES 5
#define XMODEM_SOH         0x01
#define XMODEM_EOT         0x04
#define XMODEM_ACK         0x06
#define XMODEM_NAK         0x15
#define XMODEM_CAN         0x18
#define XMODEM_START       'C'

#define _CHECKSUM_BUFFER_SIZE 4096

#define TIMEOUT_QUICK   100
#define TIMEOUT_NORMAL  1000
#define TIMEOUT_LONG    5000

uint16_t read_local_flash(uint32_t flash_src_addr, uint8_t *dst_buffer, uint16_t size);
bool flasher_init(struct io_descriptor *const io_descr);
void flasher_loadBuffer(struct io_descriptor *const io_descr, uint8_t* buffer, uint32_t size);
void flasher_writeBuffer(struct io_descriptor *const io_descr, uint32_t src_addr, uint32_t dst_addr, uint32_t size);
void flasher_reset(struct io_descriptor *const io_descr);
void flasher_programNeighboringNode(struct usart_sync_descriptor *const UART_descr);


#ifdef __cplusplus
}
#endif

#endif /* FLASHER_H */

