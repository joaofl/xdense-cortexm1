/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "router.h"

//static uint8_t pck_example[] = "UUUUUUUUUUUUUUUU";
//static uint8_t pck_tx[PCK_SIZE] = "aaaaaaaaaaaaaaaa";

//static uint8_t pck_tx[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//static uint8_t pck_example[] = {0b00000001, 0b00000011, 0b00000111, 0b00001111, 0b00011111, 0b00111111, 0b01111111, 0b11111111, 
//                                        0b00000001, 0b00000011, 0b00000111, 0b00001111, 0b00011111, 0b00111111, 0b01111111, 0b11111111};


////////////////////////////////////////////////////////////////////////////////
void router_log_debug(const char* function, const char* message_type, const char* msg){
    #ifdef ROUTER_DEBUG
        printf("[%s] [ROUTER] [%s] %s\n", message_type, function, msg);
    #endif
}

///////////////////////// ALL PORTS ////////////////////////////////////////////
void enable_DMA_UART(struct usart_sync_descriptor *const UART_descr){
    if(UART_descr == &UART_E){
        enable_DMA_UART_E();
    } else if(UART_descr == &UART_W){
        enable_DMA_UART_W();
    } else if(UART_descr == &UART_N){
        enable_DMA_UART_N();
    } else if(UART_descr == &UART_S){
        enable_DMA_UART_S();
    }
}
void disable_DMA_UART(struct usart_sync_descriptor *const UART_descr){
    if(UART_descr == &UART_E){
        disable_DMA_UART_E();
    } else if(UART_descr == &UART_W){
        disable_DMA_UART_W();
    } else if(UART_descr == &UART_N){
        disable_DMA_UART_N();
    } else if(UART_descr == &UART_S){
        disable_DMA_UART_S();
    }
}

///////////////////////// EAST PORT ////////////////////////////////////////////

void enable_DMA_UART_E(void){
    _dma_enable_transaction(RX_DMA_CH_UART_E, false);
}

void disable_DMA_UART_E(void){
    DMAC_CRITICAL_SECTION_ENTER();
    ((Dmac *)DMAC)->CHID.reg = RX_DMA_CH_UART_E;
    ((Dmac *)DMAC)->CHCTRLA.reg &= ~DMAC_CHCTRLA_ENABLE;
    DMAC_CRITICAL_SECTION_LEAVE();
}

void set_destination_RX_address_DMA_UART_E(uint8_t * buffer_dst){
    _dma_set_destination_address(RX_DMA_CH_UART_E, buffer_dst);
    _dma_set_data_amount(RX_DMA_CH_UART_E, (uint32_t) PCK_SIZE);
}

void write_UART_E(void)
{
    _dma_enable_transaction(TX_DMA_CH_UART_E, false);
}
void tx_cb_UART_E(struct _dma_resource *const resource)
{
    /* Transfer completed */
//    printf("TX_E complete\n");
}


void rx_cb_UART_E(struct _dma_resource *const resource)
{
    uint8_t * new_buffer_dst_RX_address;
    
    router_log_debug(__FUNCTION__, "OK", "Packet received");
    /* Transfer completed */
    ringbuffer_xdense_transaction_DMA_completed_packet(&ringback_descr_RX_E);

    new_buffer_dst_RX_address = ringbuffer_xdense_reserve_packet(&ringback_descr_RX_E, PCK_SIZE);
    if(new_buffer_dst_RX_address != NULL){
        set_destination_RX_address_DMA_UART_E(new_buffer_dst_RX_address);
    } else {
        new_buffer_dst_RX_address = ringbuffer_xdense_force_reserve_packet(&ringback_descr_RX_E, PCK_SIZE);
        set_destination_RX_address_DMA_UART_E(new_buffer_dst_RX_address);
        router_log_debug(__FUNCTION__, "WARNING", "ringbuffer_xdense full! Last packet received dropped.");
    }
    
    //DEBUG
    printf("%d bytes in ringback buffer\n", ringbuffer_xdense_num(&ringback_descr_RX_E));
    
    
    enable_DMA_UART_E();
}
void tx_err_cb_UART_E(struct _dma_resource *const resource)
{
    /* Transfer error */
    printf("TX_E error\n");
}
void rx_err_cb_UART_E(struct _dma_resource *const resource)
{
    /* Transfer error */
    printf("RX_E error\n");
}
void config_UART_E(void)
{
    uint8_t * new_buffer_dst_RX_address;

    buffer_tx_E[0] = '0';
    
    usart_sync_enable(&UART_E);

    //// Configure TX
    _dma_set_source_address(TX_DMA_CH_UART_E, (uint8_t*) buffer_tx_E);
    _dma_set_destination_address(TX_DMA_CH_UART_E, (uint32_t) & (((Sercom *)(UART_E.device.hw))->USART.DATA.reg));
    _dma_set_data_amount(TX_DMA_CH_UART_E, (uint32_t)PCK_SIZE);
    // callback
    struct _dma_resource *resource_tx;
    _dma_get_channel_resource(&resource_tx, TX_DMA_CH_UART_E);
    resource_tx->dma_cb.transfer_done = tx_cb_UART_E;
    resource_tx->dma_cb.error         = tx_err_cb_UART_E;
    // Enable DMA transfer complete interrupt
    _dma_set_irq_state(TX_DMA_CH_UART_E, DMA_TRANSFER_COMPLETE_CB, true);  

    ///Configure Ringback buffers TX
    if (ERR_NONE != ringbuffer_xdense_init(&ringback_descr_RX_E, ringback_buffer_RX_E, PCK_SIZE*MAX_PCK_WAITING)) {
        router_log_debug(__FUNCTION__, "ERROR", "ringbuffer_xdense_init ERROR");
    } else {
        router_log_debug(__FUNCTION__, "OK", "ringbuffer_xdense_init OK");
    }

    new_buffer_dst_RX_address = ringbuffer_xdense_reserve_packet(&ringback_descr_RX_E, PCK_SIZE);
    //// Configure RX
    _dma_set_source_address(RX_DMA_CH_UART_E, (uint32_t) & (((Sercom *)(UART_E.device.hw))->USART.DATA.reg));
    _dma_set_destination_address(RX_DMA_CH_UART_E, new_buffer_dst_RX_address);
    _dma_set_data_amount(RX_DMA_CH_UART_E, (uint32_t)PCK_SIZE);
    // callback
    struct _dma_resource *resource_rx;
    _dma_get_channel_resource(&resource_rx, RX_DMA_CH_UART_E);
    resource_rx->dma_cb.transfer_done = rx_cb_UART_E;
    resource_rx->dma_cb.error         = rx_err_cb_UART_E;
    // Enable DMA transfer complete interrupt
    _dma_set_irq_state(RX_DMA_CH_UART_E, DMA_TRANSFER_COMPLETE_CB, true);
    // Enable the receive transaction for the copy to happen as soon as the packet arrives
    _dma_enable_transaction(RX_DMA_CH_UART_E, false);

}
///////////////////////// WEST PORT ////////////////////////////////////////////
void enable_DMA_UART_W(void){
    _dma_enable_transaction(RX_DMA_CH_UART_W, false);
}
void disable_DMA_UART_W(void){
    DMAC_CRITICAL_SECTION_ENTER();
    ((Dmac *)DMAC)->CHID.reg = RX_DMA_CH_UART_W;
    ((Dmac *)DMAC)->CHCTRLA.reg &= ~DMAC_CHCTRLA_ENABLE;
    DMAC_CRITICAL_SECTION_LEAVE();
}
void set_destination_RX_address_DMA_UART_W(uint8_t * buffer_dst){
    _dma_set_destination_address(RX_DMA_CH_UART_W, buffer_dst);
    _dma_set_data_amount(RX_DMA_CH_UART_W, (uint32_t) PCK_SIZE);
}
void write_UART_W(void)
{
    _dma_enable_transaction(TX_DMA_CH_UART_W, false);
}
void tx_cb_UART_W(struct _dma_resource *const resource)
{
    /* Transfer completed */
    //TODO: dequeue and transmit next packet 
    //printf("TX_W complete\n");
}
void rx_cb_UART_W(struct _dma_resource *const resource)
{
    uint8_t * new_buffer_dst_RX_address;
    
    router_log_debug(__FUNCTION__, "OK", "Packet received");
    /* Transfer completed */
    ringbuffer_xdense_transaction_DMA_completed_packet(&ringback_descr_RX_W);

    new_buffer_dst_RX_address = ringbuffer_xdense_reserve_packet(&ringback_descr_RX_W, PCK_SIZE);
    if(new_buffer_dst_RX_address != NULL){
        set_destination_RX_address_DMA_UART_W(new_buffer_dst_RX_address);
    } else {
        new_buffer_dst_RX_address = ringbuffer_xdense_force_reserve_packet(&ringback_descr_RX_W, PCK_SIZE);
        set_destination_RX_address_DMA_UART_W(new_buffer_dst_RX_address);
        router_log_debug(__FUNCTION__, "WARNING", "ringbuffer_xdense full! Last packet received dropped.");
    }
    
    //DEBUG
    printf("%d bytes in ringback buffer\n", ringbuffer_xdense_num(&ringback_descr_RX_W));
    
    enable_DMA_UART_W();
}
void tx_err_cb_UART_W(struct _dma_resource *const resource)
{
    /* Transfer error */
    printf("TX_W error\n");
}
void rx_err_cb_UART_W(struct _dma_resource *const resource)
{
    /* Transfer error */
    printf("RX_W error\n");
}
void config_UART_W(void)
{
    uint8_t * new_buffer_dst_RX_address;

    //Only to avoid warnings from the compiler for not used vars.
    buffer_tx_W[0] = '0';

    
    usart_sync_enable(&UART_W);

    //// Configure TX
    _dma_set_source_address(TX_DMA_CH_UART_W, (uint8_t*) buffer_tx_W);
    _dma_set_destination_address(TX_DMA_CH_UART_W, (uint32_t) & (((Sercom *)(UART_W.device.hw))->USART.DATA.reg));
    _dma_set_data_amount(TX_DMA_CH_UART_W, (uint32_t)PCK_SIZE);
    // callback
    struct _dma_resource *resource_tx;
    _dma_get_channel_resource(&resource_tx, TX_DMA_CH_UART_W);
    resource_tx->dma_cb.transfer_done = tx_cb_UART_W;
    resource_tx->dma_cb.error         = tx_err_cb_UART_W;
    // Enable DMA transfer complete interrupt
    _dma_set_irq_state(TX_DMA_CH_UART_W, DMA_TRANSFER_COMPLETE_CB, true);

    ///Configure Ringback buffers TX
    if (ERR_NONE != ringbuffer_xdense_init(&ringback_descr_RX_W, ringback_buffer_RX_W, PCK_SIZE*MAX_PCK_WAITING)) {
        router_log_debug(__FUNCTION__, "ERROR", "ringbuffer_xdense_init ERROR");
    } else {
        router_log_debug(__FUNCTION__, "OK", "ringbuffer_xdense_init OK");
    }

    new_buffer_dst_RX_address = ringbuffer_xdense_reserve_packet(&ringback_descr_RX_W, PCK_SIZE);

    //// Configure RX
    _dma_set_source_address(RX_DMA_CH_UART_W, (uint32_t) & (((Sercom *)(UART_W.device.hw))->USART.DATA.reg));
    _dma_set_destination_address(RX_DMA_CH_UART_W, new_buffer_dst_RX_address);
    _dma_set_data_amount(RX_DMA_CH_UART_W, (uint32_t)PCK_SIZE);
    // callback
    struct _dma_resource *resource_rx;
    _dma_get_channel_resource(&resource_rx, RX_DMA_CH_UART_W);
    resource_rx->dma_cb.transfer_done = rx_cb_UART_W;
    resource_rx->dma_cb.error         = rx_err_cb_UART_W;
    // Enable DMA transfer complete interrupt
    _dma_set_irq_state(RX_DMA_CH_UART_W, DMA_TRANSFER_COMPLETE_CB, true);
    // Enable the receive transaction for the copy to happen as soon as the packet arrives
    _dma_enable_transaction(RX_DMA_CH_UART_W, false);
}
///////////////////////// NORTH PORT ////////////////////////////////////////////
void enable_DMA_UART_N(void){
    _dma_enable_transaction(RX_DMA_CH_UART_N, false);
}
void disable_DMA_UART_N(){
    DMAC_CRITICAL_SECTION_ENTER();
    ((Dmac *)DMAC)->CHID.reg = RX_DMA_CH_UART_N;
    ((Dmac *)DMAC)->CHCTRLA.reg &= ~DMAC_CHCTRLA_ENABLE;
    DMAC_CRITICAL_SECTION_LEAVE();
}
void set_destination_RX_address_DMA_UART_N(uint8_t * buffer_dst){
    _dma_set_destination_address(RX_DMA_CH_UART_N, buffer_dst);
    _dma_set_data_amount(RX_DMA_CH_UART_N, (uint32_t) PCK_SIZE);
}
void write_UART_N(void)
{
    _dma_enable_transaction(TX_DMA_CH_UART_N, false);
}
void tx_cb_UART_N(struct _dma_resource *const resource)
{
    /* Transfer completed */
    //TODO: dequeue and transmit next packet 
//    printf("TX_N complete\n");
}
void rx_cb_UART_N(struct _dma_resource *const resource)
{
    uint8_t * new_buffer_dst_RX_address;
    
    router_log_debug(__FUNCTION__, "OK", "Packet received");
    /* Transfer completed */
    ringbuffer_xdense_transaction_DMA_completed_packet(&ringback_descr_RX_N);

    new_buffer_dst_RX_address = ringbuffer_xdense_reserve_packet(&ringback_descr_RX_N, PCK_SIZE);
    if(new_buffer_dst_RX_address != NULL){
        set_destination_RX_address_DMA_UART_N(new_buffer_dst_RX_address);
    } else {
        new_buffer_dst_RX_address = ringbuffer_xdense_force_reserve_packet(&ringback_descr_RX_N, PCK_SIZE);
        set_destination_RX_address_DMA_UART_N(new_buffer_dst_RX_address);
        router_log_debug(__FUNCTION__, "WARNING", "ringbuffer_xdense full! Last packet received dropped.");
    }
    
    //DEBUG
    printf("%d bytes in ringback buffer\n", ringbuffer_xdense_num(&ringback_descr_RX_N));
    
    enable_DMA_UART_N();
}
void tx_err_cb_UART_N(struct _dma_resource *const resource)
{
    /* Transfer error */
    printf("TX_N error\n");
}
void rx_err_cb_UART_N(struct _dma_resource *const resource)
{
    /* Transfer error */
    printf("RX_N error\n");
}
void config_UART_N(void)
{
    uint8_t * new_buffer_dst_RX_address;

    buffer_tx_N[0] = '0';
    
    usart_sync_enable(&UART_N);

    //// Configure TX
    _dma_set_source_address(TX_DMA_CH_UART_N, (uint8_t*) buffer_tx_N);
    _dma_set_destination_address(TX_DMA_CH_UART_N, (uint32_t) & (((Sercom *)(UART_N.device.hw))->USART.DATA.reg));
    _dma_set_data_amount(TX_DMA_CH_UART_N, (uint32_t)PCK_SIZE);
    // callback
    struct _dma_resource *resource_tx;
    _dma_get_channel_resource(&resource_tx, TX_DMA_CH_UART_N);
    resource_tx->dma_cb.transfer_done = tx_cb_UART_N;
    resource_tx->dma_cb.error         = tx_err_cb_UART_N;
    // Enable DMA transfer complete interrupt
    _dma_set_irq_state(TX_DMA_CH_UART_N, DMA_TRANSFER_COMPLETE_CB, true);

    ///Configure Ringback buffers TX
    if (ERR_NONE != ringbuffer_xdense_init(&ringback_descr_RX_N, ringback_buffer_RX_N, PCK_SIZE*MAX_PCK_WAITING)) {
        router_log_debug(__FUNCTION__, "ERROR", "ringbuffer_xdense_init ERROR");
    } else {
        router_log_debug(__FUNCTION__, "OK", "ringbuffer_xdense_init OK");
    }

    new_buffer_dst_RX_address = ringbuffer_xdense_reserve_packet(&ringback_descr_RX_N, PCK_SIZE);

    //// Configure RX
    _dma_set_source_address(RX_DMA_CH_UART_N, (uint32_t) & (((Sercom *)(UART_N.device.hw))->USART.DATA.reg));
    _dma_set_destination_address(RX_DMA_CH_UART_N, new_buffer_dst_RX_address);
    _dma_set_data_amount(RX_DMA_CH_UART_N, (uint32_t)PCK_SIZE);
    // callback
    struct _dma_resource *resource_rx;
    _dma_get_channel_resource(&resource_rx, RX_DMA_CH_UART_N);
    resource_rx->dma_cb.transfer_done = rx_cb_UART_N;
    resource_rx->dma_cb.error         = rx_err_cb_UART_N;
    // Enable DMA transfer complete interrupt
    _dma_set_irq_state(RX_DMA_CH_UART_N, DMA_TRANSFER_COMPLETE_CB, true);
    // Enable the receive transaction for the copy to happen as soon as the packet arrives
    _dma_enable_transaction(RX_DMA_CH_UART_N, false);
}
///////////////////////// SOUTH PORT ////////////////////////////////////////////
void enable_DMA_UART_S(void){
    _dma_enable_transaction(RX_DMA_CH_UART_S, false);
}
void disable_DMA_UART_S(void){
    DMAC_CRITICAL_SECTION_ENTER();
    ((Dmac *)DMAC)->CHID.reg = RX_DMA_CH_UART_S;
    ((Dmac *)DMAC)->CHCTRLA.reg &= ~DMAC_CHCTRLA_ENABLE;
    DMAC_CRITICAL_SECTION_LEAVE();
}
void set_destination_RX_address_DMA_UART_S(uint8_t * buffer_dst){
    _dma_set_destination_address(RX_DMA_CH_UART_S, buffer_dst);
    _dma_set_data_amount(RX_DMA_CH_UART_S, (uint32_t) PCK_SIZE);
}
void write_UART_S(void)
{
    _dma_enable_transaction(TX_DMA_CH_UART_S, false);
}
void tx_cb_UART_S(struct _dma_resource *const resource)
{
    /* Transfer completed */
    //TODO: dequeue and transmit next packet 
//    printf("TX_S complete\n");
}
void rx_cb_UART_S(struct _dma_resource *const resource)
{
    uint8_t * new_buffer_dst_RX_address;
    
    router_log_debug(__FUNCTION__, "OK", "Packet received");
    /* Transfer completed */
    ringbuffer_xdense_transaction_DMA_completed_packet(&ringback_descr_RX_S);

    new_buffer_dst_RX_address = ringbuffer_xdense_reserve_packet(&ringback_descr_RX_S, PCK_SIZE);
    if(new_buffer_dst_RX_address != NULL){
        set_destination_RX_address_DMA_UART_S(new_buffer_dst_RX_address);
    } else {
        new_buffer_dst_RX_address = ringbuffer_xdense_force_reserve_packet(&ringback_descr_RX_S, PCK_SIZE);
        set_destination_RX_address_DMA_UART_S(new_buffer_dst_RX_address);
        router_log_debug(__FUNCTION__, "WARNING", "ringbuffer_xdense full! Last packet received dropped.");
    }
    
    //DEBUG
    printf("%d bytes in ringback buffer\n", ringbuffer_xdense_num(&ringback_descr_RX_S));
    
    enable_DMA_UART_S();
}
void tx_err_cb_UART_S(struct _dma_resource *const resource)
{
    /* Transfer error */
    printf("TX_S error\n");
}
void rx_err_cb_UART_S(struct _dma_resource *const resource)
{
    /* Transfer error */
    printf("RX_S error\n");
}
void config_UART_S(void)
{
    uint8_t * new_buffer_dst_RX_address;

    buffer_tx_S[0] = '0';

    
    usart_sync_enable(&UART_S);

    //// Configure TX
    _dma_set_source_address(TX_DMA_CH_UART_S, (uint8_t*) buffer_tx_S);
    _dma_set_destination_address(TX_DMA_CH_UART_S, (uint32_t) & (((Sercom *)(UART_S.device.hw))->USART.DATA.reg));
    _dma_set_data_amount(TX_DMA_CH_UART_S, (uint32_t)PCK_SIZE);
    // callback
    struct _dma_resource *resource_tx;
    _dma_get_channel_resource(&resource_tx, TX_DMA_CH_UART_S);
    resource_tx->dma_cb.transfer_done = tx_cb_UART_S;
    resource_tx->dma_cb.error         = tx_err_cb_UART_S;
    // Enable DMA transfer complete interrupt
    _dma_set_irq_state(TX_DMA_CH_UART_S, DMA_TRANSFER_COMPLETE_CB, true);  

    ///Configure Ringback buffers TX
    if (ERR_NONE != ringbuffer_xdense_init(&ringback_descr_RX_S, ringback_buffer_RX_S, PCK_SIZE*MAX_PCK_WAITING)) {
        router_log_debug(__FUNCTION__, "ERROR", "ringbuffer_xdense_init ERROR");
    } else {
        router_log_debug(__FUNCTION__, "OK", "ringbuffer_xdense_init OK");
    }

    new_buffer_dst_RX_address = ringbuffer_xdense_reserve_packet(&ringback_descr_RX_S, PCK_SIZE);

    //// Configure RX
    _dma_set_source_address(RX_DMA_CH_UART_S, (uint32_t) & (((Sercom *)(UART_S.device.hw))->USART.DATA.reg));
    _dma_set_destination_address(RX_DMA_CH_UART_S, new_buffer_dst_RX_address);
    _dma_set_data_amount(RX_DMA_CH_UART_S, (uint32_t)PCK_SIZE);
    // callback
    struct _dma_resource *resource_rx;
    _dma_get_channel_resource(&resource_rx, RX_DMA_CH_UART_S);
    resource_rx->dma_cb.transfer_done = rx_cb_UART_S;
    resource_rx->dma_cb.error         = rx_err_cb_UART_S;
    // Enable DMA transfer complete interrupt
    _dma_set_irq_state(RX_DMA_CH_UART_S, DMA_TRANSFER_COMPLETE_CB, true);
    // Enable the receive transaction for the copy to happen as soon as the packet arrives
    _dma_enable_transaction(RX_DMA_CH_UART_S, false);
}
///////////////////////// DEBUG PORT ///////////////////////////////////////////
void config_UART_DBG(void)
{
//    usart_async_register_callback(&UART_DBG, USART_ASYNC_RXC_CB, rx_cb_UART_W);
//    usart_async_register_callback(&UART_N, USART_ASYNC_TXC_CB, tx_cb_UART_N);
    usart_sync_enable(&UART_DBG);
    stdio_io_init(&UART_DBG.io);
}

//////////////////////// LOCAL PORT ////////////////////////////////////////////
void config_LOCAL_PORT(void){
    /*
    ///Configure Ringback buffers TX
    if (ERR_NONE != ringbuffer_init(&ringback_descr_tx_L, ringback_buffer_tx_L, PCK_SIZE*MAX_PCK_WAITING)) {
        router_log_debug(__FUNCTION__, "ERROR", "ringbuffer_init ERROR");
    } else {
        router_log_debug(__FUNCTION__, "OK", "ringbuffer_init OK");
    } 
    */
}

///////////////////////// ROUTING //////////////////////////////////////////////
///////////////////////// ROUTING //////////////////////////////////////////////
///////////////////////// ROUTING //////////////////////////////////////////////
///////////////////////// ROUTING //////////////////////////////////////////////
void sendPacket(uint8_t ports_mask, uint8_t * pck){
    if((ports_mask >> PORT_E) & 1)
    {
        memcpy(buffer_tx_E, pck, PCK_SIZE);
        write_UART_E();
    }
    if((ports_mask >> PORT_W) & 1)
    {
        memcpy(buffer_tx_W, pck, PCK_SIZE);
        write_UART_W();
    }
    if((ports_mask >> PORT_S) & 1)
    {
        memcpy(buffer_tx_S, pck, PCK_SIZE);
        write_UART_S();
    }
    if((ports_mask >> PORT_N) & 1)
    {
        memcpy(buffer_tx_N, pck, PCK_SIZE);
        write_UART_N();
    }
//    printf("TX_E:");
//    for (int i = 0; i < PCK_SIZE; i++) {
//        putc(pck_tx_e[i], stdout);
//    }
//    printf("\n");
}
//void receivePacket(uint8_t port, uint8_t * pck){
void receivePacket(uint8_t port, uint8_t * pck){
/*
    if(packet_check(pck){
        router_log_debug(__FUNCTION__, "OK", "packet_check OK");

        if (port == PORT_N && packet_get_d_y(pck) > -126) {
            packet_increment_s_y(pck, -1);
            packet_increment_d_y(pck, -1);
        } else if (port == PORT_S && packet_get_d_y(pck) < 126) {
            packet_increment_s_y(pck, 1);
            packet_increment_d_y(pck, 1);
        } else if (port == PORT_E && packet_get_d_x(pck) < 126) {
            packet_increment_s_x(pck, 1);
            packet_increment_d_x(pck, 1);
        } else if (port == PORT_W && packet_get_d_x(pck) > -126) {
            packet_increment_s_x(pck, -1);
            packet_increment_d_x(pck, -1);
        } else {
            router_log_debug(__FUNCTION__, "WARNING", "Packet dropped since the counter have exceeded its limits.");
            return;
        }
        if ( router_protocol_packet_analysis(port, pck) == false ){
            router_log_debug(__FUNCTION__, "OK", "Packet redirected, not for this node.");
        } else {
            router_log_debug(__FUNCTION__, "OK", "Packet for this node.");
        }

    } else {
        router_log_debug(__FUNCTION__, "WARNING", "BCC error in packet_check. Packet dropped.");
        bytes_read = 0; //BCC error
    }

*/
    uint8_t pck_received[PCK_SIZE];
    if(port == PORT_E)
    {
//        memcpy(buffer_tx_E, pck, PCK_SIZE);
//        write_UART_E(); 
        printf("RX_E:");
        /*
        if(ringbuffer_xdense_get_packet(&ringback_descr_RX_E, pck_received, PCK_SIZE) != ERR_NONE){
            router_log_debug(__FUNCTION__, "ERROR", "ringbuffer_xdense_get_packet ERROR");
        } else {
            router_log_debug(__FUNCTION__, "OK", "ringbuffer_xdense_get_packet OK");
        }
        */
        printf(" %d bytes in ringback buffer\n", ringbuffer_xdense_num(&ringback_descr_RX_E));

    } else if(port == PORT_W)
    {
        //dest, origin, size
//        memcpy(buffer_tx_W, pck, PCK_SIZE);
//        write_UART_W();       
        printf("RX_W:");
    }
    /*
    for (int i = 0; i < PCK_SIZE; i++)
        putc(pck_received[i], stdout);        
    printf("\n");
    */
    
}
/*
bool router_protocol_packet_analysis (uint8_t port, uint8_t * pck){
    
    bool accept_packet=false;
    
    switch(packet_get_protocol(pck)){
        case PROTOCOL_UNICAST:
            if (packet_get_d_x(pck) == 0 && packet_get_d_y(pck) == 0){
                accept_packet = true;
                application_add_packet_to_queue(pck);
            } else {
                accept_packet = false;
                router_redirect_packet_unicast(pck);
            }
        break;
        case PROTOCOL_MULTICAST_1:
            if(packet_get_d_x(pck) == 0 && packet_get_d_y(pck) == 0){
                accept_packet = false;
                switch_redirect_packet_multicast_1(pck);
            } else {
                accept_packet = false;
                switch_redirect_packet_unicast(pck); //redirect as unicast packet
                //accept_packet = true;
                //application_packet_received(pck);
            }
        break;
        case PROTOCOL_BROADCAST:
            accept_packet = true;
            switch_redirect_packet_broadcast(pck);
            application_add_packet_to_queue(pck);           
        break;      
    }
    
    return accept_packet;
}
//////HERE!
uint8_t router_redirect_packet_unicast(uint8_t * pck){

    if( packet_get_app_packet_type(pck) == APP_PROTOCOL_REQUEST){
        if (packet_get_d_x(pck) > 0) //Travel x-
            switch_write_packet(PORT_EAST_MASK, pck);
        else if (packet_get_d_x(pck) < 0) ////Travel x+
            switch_write_packet(PORT_WEST_MASK, pck);
        else { // = 0, travel Y {
            if (packet_get_d_y(pck) > 0) //Travel y-
                switch_write_packet(PORT_SOUTH_MASK, pck);
            else if (pck->d_y < 0) //Travel y+  
                switch_write_packet(PORT_NORTH_MASK, pck);
        }
    } else if( packet_get_app_packet_type(pck) == APP_PROTOCOL_RESPONSE) {
        if (pck->d_y > 0) //Travel y-
            switch_write_packet(PORT_SOUTH_MASK, pck);
        else if (pck->d_y < 0) //Travel y+
            switch_write_packet(PORT_NORTH_MASK, pck);  
        else { // = 0, travel Y {
            if (pck->d_x > 0) //Travel x-
                switch_write_packet(PORT_EAST_MASK, pck);
            else if (pck->d_x < 0) ////Travel x+
                switch_write_packet(PORT_WEST_MASK, pck);
        }
    }
    return 0;
}

uint8_t router_redirect_packet_multicast_1(xd_packet * pck){
    
    pck->protocol = PROTOCOL_UNICAST;
    
    pck->d_x=0; pck->d_y=-1;
    switch_write_packet(PORT_NORTH_MASK, pck);
    pck->d_x=0; pck->d_y=1;
    switch_write_packet(PORT_SOUTH_MASK, pck);
    pck->d_x=-1;    pck->d_y=0;
    switch_write_packet(PORT_WEST_MASK, pck);
    pck->d_x=1; pck->d_y=0;
    switch_write_packet(PORT_EAST_MASK, pck);
    return 0;
}

void router_redirect_packet_broadcast(xd_packet * pck){
    if(pck->s_x <= 0 && pck->s_y <= 0) {
        switch_write_packet(PORT_SOUTH_MASK, pck);
    } 
    if(pck->s_x >= 0 && pck->s_y <= 0) {
        switch_write_packet(PORT_WEST_MASK, pck);
    } 
    if(pck->s_x >= 0 && pck->s_y >= 0) {
        switch_write_packet(PORT_NORTH_MASK, pck);
    } 
    if(pck->s_x <= 0 && pck->s_y >= 0) {
        switch_write_packet(PORT_EAST_MASK, pck);
    }
    
    return; 
}
*/
