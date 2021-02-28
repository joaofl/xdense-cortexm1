/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   router.h
 * Author: joao
 *
 * Created on April 11, 2017, 5:23 PM
 */

#ifndef ROUTER_H
#define ROUTER_H

#include <stdio.h>
#include <hpl_dma.h>

#include "driver_init.h"
#include "packet.h"

//#include "hal/utils/include/utils_ringbuffer.h"
#include "xdense_utils/ringback_packet_xdense.h"


#define ROUTER_DEBUG


#define PCK_SIZE 16
#define MAX_PCK_WAITING 8 // PCK_SIZE * MAX_PCK_WAITING must be power of 2 (MAX_PCK_WAITING = 1,2,4,8,16,..)

// DMA channel numbers for receive and transmit
#define RX_DMA_CH_UART_N 10
#define TX_DMA_CH_UART_N 11

#define RX_DMA_CH_UART_E 6
#define TX_DMA_CH_UART_E 7

#define RX_DMA_CH_UART_W 0
#define TX_DMA_CH_UART_W 1

#define RX_DMA_CH_UART_S 8
#define TX_DMA_CH_UART_S 9

// PORTS MASK
// 0 b 0 0 0 L W E S N
//Local West East South North
#define PORT_MASK_E     0b00000001
#define PORT_MASK_S     0b00000010
#define PORT_MASK_W     0b00000100
#define PORT_MASK_N     0b00001000
#define PORT_MASK_L     0b00010000
#define PORT_MASK_ALL   0b00011111

#define PORT_E 0 //PORT EAST
#define PORT_S 1 //PORT SOUTH
#define PORT_W 2 //PORT WEST
#define PORT_N 3 //PORT NORTH
#define PORT_L 4 //PORT LOCAL
#define PORT_D 5 //PORT DEBUG

///////////////////////// ROUTING //////////////////////////////////////////////
void sendPacket(uint8_t ports_mask, uint8_t * pck);
void receivePacket(uint8_t port, uint8_t * pck);
///////////////////////// DEBUG PORT ///////////////////////////////////////////
struct io_descriptor *io_uart_dbg;
void config_UART_DBG(void);
///////////////////////// ALL PORTS //////////////////////////////////////////// 
void enable_DMA_UART(struct usart_sync_descriptor *const UART_descr);
void disable_DMA_UART(struct usart_sync_descriptor *const UART_descr);

///////////////////////// EAST PORT ////////////////////////////////////////////
struct ringbuffer_xdense ringback_descr_RX_E;
static uint8_t ringback_buffer_RX_E[PCK_SIZE*MAX_PCK_WAITING];

static uint8_t buffer_tx_E[PCK_SIZE];// = "pck-tx-east-port";

void enable_DMA_UART_E(void);
void disable_DMA_UART_E(void);
void write_UART_E(void);
void enable_RX_UART_E(void);
void tx_cb_UART_E(struct _dma_resource *const resource);
void rx_cb_UART_E(struct _dma_resource *const resource);
void tx_err_cb_UART_E(struct _dma_resource *const resource);
void rx_err_cb_UART_E(struct _dma_resource *const resource);
void config_UART_E(void);
///////////////////////// WEST PORT ////////////////////////////////////////////
struct ringbuffer_xdense ringback_descr_RX_W;
static uint8_t ringback_buffer_RX_W[PCK_SIZE*MAX_PCK_WAITING];

static uint8_t buffer_tx_W[PCK_SIZE];// = "pck-tx-west-port";

void enable_DMA_UART_W(void);
void disable_DMA_UART_W(void);
void write_UART_W(void);
void enable_RX_UART_W(void);
void tx_cb_UART_W(struct _dma_resource *const resource);
void rx_cb_UART_W(struct _dma_resource *const resource);
void tx_err_cb_UART_W(struct _dma_resource *const resource);
void rx_err_cb_UART_W(struct _dma_resource *const resource);
void config_UART_W(void);
///////////////////////// NORTH PORT ////////////////////////////////////////////
struct ringbuffer_xdense ringback_descr_RX_N;
static uint8_t ringback_buffer_RX_N[PCK_SIZE*MAX_PCK_WAITING];

static uint8_t buffer_tx_N[PCK_SIZE];// = "pck-tx-nort-port";

void enable_DMA_UART_N(void);
void disable_DMA_UART_N(void);
void write_UART_N(void);
void enable_RX_UART_N(void);
void tx_cb_UART_N(struct _dma_resource *const resource);
void rx_cb_UART_N(struct _dma_resource *const resource);
void tx_err_cb_UART_N(struct _dma_resource *const resource);
void rx_err_cb_UART_N(struct _dma_resource *const resource);
void config_UART_N(void);
///////////////////////// SOUTH PORT ////////////////////////////////////////////
struct ringbuffer_xdense ringback_descr_RX_S;
static uint8_t ringback_buffer_RX_S[PCK_SIZE*MAX_PCK_WAITING];

static uint8_t buffer_tx_S[PCK_SIZE];// = "pck-tx-west-port";

void enable_DMA_UART_S();
void disable_DMA_UART_S();
void write_UART_S(void);
void enable_RX_UART_S(void);
void tx_cb_UART_S(struct _dma_resource *const resource);
void rx_cb_UART_S(struct _dma_resource *const resource);
void tx_err_cb_UART_S(struct _dma_resource *const resource);
void rx_err_cb_UART_S(struct _dma_resource *const resource);
void config_UART_S(void);
//////////////////////// LOCAL PORT /////////////////////////////////////////////
//struct ringbuffer ringback_descr_tx_L;
//static uint8_t ringback_buffer_tx_L[PCK_SIZE*MAX_PCK_WAITING];


#ifdef __cplusplus
}
#endif

#endif /* ROUTER_H */

