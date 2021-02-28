/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "flasher.h"

static const uint16_t crc16Table[256] = {
    0x0000,0x1021,0x2042,0x3063,0x4084,0x50a5,0x60c6,0x70e7,
    0x8108,0x9129,0xa14a,0xb16b,0xc18c,0xd1ad,0xe1ce,0xf1ef,
    0x1231,0x0210,0x3273,0x2252,0x52b5,0x4294,0x72f7,0x62d6,
    0x9339,0x8318,0xb37b,0xa35a,0xd3bd,0xc39c,0xf3ff,0xe3de,
    0x2462,0x3443,0x0420,0x1401,0x64e6,0x74c7,0x44a4,0x5485,
    0xa56a,0xb54b,0x8528,0x9509,0xe5ee,0xf5cf,0xc5ac,0xd58d,
    0x3653,0x2672,0x1611,0x0630,0x76d7,0x66f6,0x5695,0x46b4,
    0xb75b,0xa77a,0x9719,0x8738,0xf7df,0xe7fe,0xd79d,0xc7bc,
    0x48c4,0x58e5,0x6886,0x78a7,0x0840,0x1861,0x2802,0x3823,
    0xc9cc,0xd9ed,0xe98e,0xf9af,0x8948,0x9969,0xa90a,0xb92b,
    0x5af5,0x4ad4,0x7ab7,0x6a96,0x1a71,0x0a50,0x3a33,0x2a12,
    0xdbfd,0xcbdc,0xfbbf,0xeb9e,0x9b79,0x8b58,0xbb3b,0xab1a,
    0x6ca6,0x7c87,0x4ce4,0x5cc5,0x2c22,0x3c03,0x0c60,0x1c41,
    0xedae,0xfd8f,0xcdec,0xddcd,0xad2a,0xbd0b,0x8d68,0x9d49,
    0x7e97,0x6eb6,0x5ed5,0x4ef4,0x3e13,0x2e32,0x1e51,0x0e70,
    0xff9f,0xefbe,0xdfdd,0xcffc,0xbf1b,0xaf3a,0x9f59,0x8f78,
    0x9188,0x81a9,0xb1ca,0xa1eb,0xd10c,0xc12d,0xf14e,0xe16f,
    0x1080,0x00a1,0x30c2,0x20e3,0x5004,0x4025,0x7046,0x6067,
    0x83b9,0x9398,0xa3fb,0xb3da,0xc33d,0xd31c,0xe37f,0xf35e,
    0x02b1,0x1290,0x22f3,0x32d2,0x4235,0x5214,0x6277,0x7256,
    0xb5ea,0xa5cb,0x95a8,0x8589,0xf56e,0xe54f,0xd52c,0xc50d,
    0x34e2,0x24c3,0x14a0,0x0481,0x7466,0x6447,0x5424,0x4405,
    0xa7db,0xb7fa,0x8799,0x97b8,0xe75f,0xf77e,0xc71d,0xd73c,
    0x26d3,0x36f2,0x0691,0x16b0,0x6657,0x7676,0x4615,0x5634,
    0xd94c,0xc96d,0xf90e,0xe92f,0x99c8,0x89e9,0xb98a,0xa9ab,
    0x5844,0x4865,0x7806,0x6827,0x18c0,0x08e1,0x3882,0x28a3,
    0xcb7d,0xdb5c,0xeb3f,0xfb1e,0x8bf9,0x9bd8,0xabbb,0xbb9a,
    0x4a75,0x5a54,0x6a37,0x7a16,0x0af1,0x1ad0,0x2ab3,0x3a92,
    0xfd2e,0xed0f,0xdd6c,0xcd4d,0xbdaa,0xad8b,0x9de8,0x8dc9,
    0x7c26,0x6c07,0x5c64,0x4c45,0x3ca2,0x2c83,0x1ce0,0x0cc1,
    0xef1f,0xff3e,0xcf5d,0xdf7c,0xaf9b,0xbfba,0x8fd9,0x9ff8,
    0x6e17,0x7e36,0x4e55,0x5e74,0x2e93,0x3eb2,0x0ed1,0x1ef0
};

uint8_t io_put(struct io_descriptor *const io_descr, uint8_t value){
    uint8_t write_value[1];
    write_value[0] = value;
    return io_write(io_descr, write_value, 1);
}

uint8_t read_from_serial_port(struct io_descriptor *const io_descr, uint8_t *buffer, int size, int timeout){
    uint8_t data_received = 0;
    int _time = 0;
    
    //TODO: Improve timeout using TIMERs (http://start.atmel.com/#examples/SAMD21XplainedPro/timers)
    while(1){
        
        if (usart_sync_is_rx_not_empty(io_descr)){
            data_received += io_read(io_descr, &buffer[data_received], 1); //size - data_received);
        } else {
            delay_us(10);
            _time++;
        }
        if(data_received == size || _time >= timeout * 100) {                                                                 
            return data_received;
        }
    }    
}
uint8_t get_from_serial_port(struct io_descriptor *const io_descr){
    uint8_t data_received = 0;
    uint8_t data = 0;
    int _time = 0;
    int default_timeout = TIMEOUT_QUICK;

    //TODO: Improve timeout using TIMERs (http://start.atmel.com/#examples/SAMD21XplainedPro/timers)

    while(1){
        if (usart_sync_is_rx_not_empty(io_descr)){
            data_received += io_read(io_descr, &data, 1);
        } else {
            delay_us(10);
            _time++;
        }
        if(data_received == 1 || _time >= default_timeout * 100) {                                                                       
                return data;
        }
    }
}
uint16_t crc16Calc(const uint8_t *data, int len)
{
    uint16_t crc16 = 0;

    while (len-- > 0)
        crc16 = (crc16 << 8) ^ crc16Table[((crc16 >> 8) ^ *(uint8_t*) data++) & 0xff];
    return crc16;
}

void crc16Add(uint8_t *blk)
{
    uint16_t crc16;

    crc16 = crc16Calc(&blk[3], XMODEM_BLK_SIZE);
    blk[XMODEM_BLK_SIZE + 3] = (crc16 >> 8) & 0xff;
    blk[XMODEM_BLK_SIZE + 4] = crc16 & 0xff;
}

uint16_t read_local_flash(uint32_t flash_src_addr, uint8_t *dst_buffer, uint16_t size){
    int i = 0;
    uint8_t *_flash_src_addr = flash_src_addr;
    uint16_t n_total_pages = FLASH_NB_OF_PAGES - 128;
    uint8_t page_size = NVMCTRL_PAGE_SIZE;

    for (i = 0; i < size; i++) {
        dst_buffer[i] = *(_flash_src_addr+i);   
    }

    return i;
}


void writeXmodem(const uint8_t* buffer, int size)
{
    uint8_t blk[XMODEM_BLK_SIZE + 5];
    uint32_t blkNum = 1;
    int retries;
    int bytes;

    //TODO: configure serial port
    //TODO: deactivate io serial interrupt

    for (retries = 0; retries < XMODEM_MAX_RETRIES; retries++)
    {
        if(get_from_serial_port(&UART_E.io) == XMODEM_START){
            break;
        }
    }
    if (retries == XMODEM_MAX_RETRIES){
        flasher_log_debug(__FUNCTION__, "ERROR", "XMODEM_MAX_RETRIES");
        return;
    }

    while (size > 0)
    {
        blk[0] = XMODEM_SOH;
        blk[1] = (blkNum & 0xff);
        blk[2] = ~(blkNum & 0xff);
        memmove(&blk[3], buffer, min(size, XMODEM_BLK_SIZE));
        if (size < XMODEM_BLK_SIZE)
            memset(&blk[3] + size, 0, XMODEM_BLK_SIZE - size);
        crc16Add(blk);

        for (retries = 0; retries < XMODEM_MAX_RETRIES; retries++)
        {
            bytes = io_write(&UART_E.io, blk, sizeof(blk));
            if (bytes != sizeof(blk))
                flasher_log_debug(__FUNCTION__, "ERROR", "io_write");

            if (get_from_serial_port(&UART_E.io) == XMODEM_ACK)
                break;
        }

        if (retries == XMODEM_MAX_RETRIES){
            flasher_log_debug(__FUNCTION__, "ERROR", "XMODEM_MAX_RETRIES");
            return;
        }

        buffer += XMODEM_BLK_SIZE;
        size -= XMODEM_BLK_SIZE;
        blkNum++;
    }

    for (retries = 0; retries < XMODEM_MAX_RETRIES; retries++)
    {
        io_put(&UART_E.io, XMODEM_EOT);
        if (get_from_serial_port(&UART_E.io) == XMODEM_ACK)
            break;
    }
    if (retries == XMODEM_MAX_RETRIES){
        flasher_log_debug(__FUNCTION__, "ERROR", "XMODEM_MAX_RETRIES");
        return;
    }
}

void flasher_log_debug(const char* function, const char* message_type, const char* msg){
    
    #ifdef FLASHER_DEBUG
        printf("[%s] [FLASHER] [%s] %s\n", message_type, function, msg);
    #endif
}


bool flasher_init(struct io_descriptor *const io_descr)
{
    char version[50]={'\0'};
    uint8_t cmd[64];
    uint8_t dummy[10];
    uint8_t size;

    flasher_log_debug(__FUNCTION__, "OK", "Initializing...");
    
    // Flush garbage
    flasher_log_debug(__FUNCTION__, "OK", "Flushing garbage...");
    read_from_serial_port(io_descr, dummy, sizeof(dummy), TIMEOUT_QUICK); 

    // RS-232 auto-baud sequence
    flasher_log_debug(__FUNCTION__, "OK", "Sending auto-baud...");
    io_put(io_descr, 0x80);
    get_from_serial_port(io_descr);
    io_put(io_descr, 0x80);
    get_from_serial_port(io_descr);
    io_put(io_descr, '#');
    read_from_serial_port(io_descr, cmd, 3, TIMEOUT_QUICK);
    
    // Setting binary mode
    flasher_log_debug(__FUNCTION__, "OK", "Setting binary mode...");
    cmd[0] = 'N';
    cmd[1] = '#';
    io_write(io_descr, cmd, 2);
    read_from_serial_port(io_descr, cmd, 2, TIMEOUT_QUICK);

    // Getting Version
    flasher_log_debug(__FUNCTION__, "OK", "Getting Version....");
    cmd[0] = 'V';
    cmd[1] = '#';
    io_write(io_descr, cmd, 2);

    size = read_from_serial_port(io_descr, version, sizeof(version) - 1, TIMEOUT_QUICK);
    if(size <= 0){
        flasher_log_debug(__FUNCTION__, "ERROR", "Version string size = 0");
        return false;
    } else {
        if(version[0] != 'v'){
            flasher_log_debug(__FUNCTION__, "ERROR", "Wrong version name.");
            return false;
        } else {
            flasher_log_debug(__FUNCTION__, "OK", version);    
        }   
    }

    //Erasing Chip
    flasher_log_debug(__FUNCTION__, "OK", "Erasing Chip....");
    int l = snprintf((char*) cmd, sizeof(cmd), "X%08X#", 0x00002000);
    if (io_write(io_descr, cmd, l) != l)
        flasher_log_debug(__FUNCTION__, "ERROR", "io_write");
    read_from_serial_port(io_descr, cmd, 3, TIMEOUT_LONG);  // Expects "X\n\r"
    if (cmd[0] != 'X'){
        flasher_log_debug(__FUNCTION__, "ERROR", "Didn't received the expected \"X\\n\\r\"");
        return false;
    } else {
       flasher_log_debug(__FUNCTION__, "OK", "Chip Erased"); 
    }

    //Fuses? (guess)
    l = snprintf((char*) cmd, sizeof(cmd), "W%08X,%08X#", 0x20004030, 0x00000010);
    if (io_write(io_descr, cmd, l) != l){
        flasher_log_debug(__FUNCTION__, "WARNING", "Writing (fuse?)");
    }
    
    l = snprintf((char*) cmd, sizeof(cmd), "W%08X,%08X#", 0x20004020, 0x20008000);
    if (io_write(io_descr, cmd, l) != l){
        flasher_log_debug(__FUNCTION__, "WARNING", "Writing (fuse?)");
    }

    return true;

}




void flasher_loadBuffer(struct io_descriptor *const io_descr, uint8_t* buffer, uint32_t size)
{
    char msg_debug[70]={'\0'};
    uint8_t cmd[20];
    
    snprintf(msg_debug, sizeof(msg_debug), "Uploading to neighbor's RAM addr=%#x (size=%#x)...", SRAM_START_ADDR, size);
    flasher_log_debug(__FUNCTION__, "OK", msg_debug);
    
    snprintf((char*) cmd, sizeof(cmd), "S%08X,%08X#", SRAM_START_ADDR, size);
    if (io_write(io_descr, cmd, sizeof(cmd) - 1) != sizeof(cmd) - 1)
        flasher_log_debug(__FUNCTION__, "ERROR", "io_write");

    writeXmodem(buffer, size);
}


void flasher_writeBuffer(struct io_descriptor *const io_descr, uint32_t src_addr, uint32_t dst_addr, uint32_t size)
{

    //Transfer the stored firmware from Neighbor's RAM to Neighbor's FLASH
    char msg_debug[70]={'\0'};

    if (size > _CHECKSUM_BUFFER_SIZE){
        flasher_log_debug(__FUNCTION__, "ERROR", "Byte steps too high!");
        return;
    }
    
    snprintf(msg_debug, sizeof(msg_debug), "Neighbor's RAM to FLASH S=%#x D=%#x size=%#x...", (unsigned int) src_addr, (unsigned int) dst_addr, (unsigned int) size);
    flasher_log_debug(__FUNCTION__, "OK", msg_debug);

    //Setting src_addr of transfer
    uint8_t cmd[64];
    int l = snprintf((char*) cmd, sizeof(cmd), "Y%08X,0#", src_addr);
    if (io_write(io_descr, cmd, l) != l)
        flasher_log_debug(__FUNCTION__, "ERROR", "io_write");
    cmd[0] = 0;
    read_from_serial_port(io_descr, cmd, 3, TIMEOUT_QUICK); // Expects "Y\n\r"
    if (cmd[0] != 'Y'){
        flasher_log_debug(__FUNCTION__, "ERROR", "Setting src_addr > unexpected response from neighbor.");
        return;
    }

    //Setting dst_addr and size of transfer
    l = snprintf((char*) cmd, sizeof(cmd), "Y%08X,%08X#", dst_addr, size);
    if (io_write(io_descr, cmd, l) != l){
        flasher_log_debug(__FUNCTION__, "ERROR", "io_write");
        return;
    }
    cmd[0] = 0;
    read_from_serial_port(io_descr, cmd, 3, TIMEOUT_LONG); // Expects "Y\n\r"
    if (cmd[0] != 'Y'){
        flasher_log_debug(__FUNCTION__, "ERROR", "Setting dst_addr > unexpected response from neighbor.");
        return;
    }
}

void flasher_reset(struct io_descriptor *const io_descr){
    uint8_t cmd[64];
/*
    int l = snprintf((char*) cmd, sizeof(cmd), "w%08X,4#", 0x00000000);
    if (io_write(io_descr, cmd, l) != l)
        printf("throw SambaError();\n");
    read_from_serial_port(io_descr, cmd, 4, TIMEOUT_NORMAL);

    l = snprintf((char*) cmd, sizeof(cmd), "w%08X,4#", 0xE000ED00);
    if (io_write(io_descr, cmd, l) != l)
        printf("throw SambaError();\n");
    read_from_serial_port(io_descr, cmd, 4, TIMEOUT_NORMAL);

    l = snprintf((char*) cmd, sizeof(cmd), "w%08X,4#", 0x41002018);
    if (io_write(io_descr, cmd, l) != l)
        printf("throw SambaError();\n");
    read_from_serial_port(io_descr, cmd, 4, TIMEOUT_NORMAL);
*/
    //Resetting chip
    int l = snprintf((char*) cmd, sizeof(cmd), "W%08X,%08X#", 0xE000ED0C, 0x05FA0004);
    if (io_write(io_descr, cmd, l) != l){
        flasher_log_debug(__FUNCTION__, "ERROR", "io_write");
        return;
    } else {
        flasher_log_debug(__FUNCTION__, "OK", "Chip Reseted!");
    }
    return;
}


void flasher_configure_serial_port_BAUD(struct usart_sync_descriptor *const UART_descr, uint32_t baudrate){
    usart_sync_set_baud_rate(UART_descr, 65536 - ((65536 * 16.0f * baudrate) / CONF_SERCOMX_FREQUENCY )); // CONF_GCLK_SERCOM3_CORE_FREQUENCY));
    delay_us(50);
}


void flasher_programNeighboringNode(struct usart_sync_descriptor *const UART_descr){
    //TODO: Improve n_total_pages check (saved in memory?).
    //TODO: Improve this funtion
    //TODO: Verification and retries
    //TODO: defines (bytes_steps, etc)

    uint16_t n_total_pages = 500;// FLASH_NB_OF_PAGES - 128;// 3968; flash_get_total_pages(&FLASH_0);
    uint8_t page_size = NVMCTRL_PAGE_SIZE;
    uint32_t bytes_to_write = n_total_pages * page_size;
    uint32_t bytes_step = 4096;
    uint16_t offset = 0;

    uint8_t *local_flash_address = FLASH_START_ADDR;
    
    //Enter in boot mode
    disable_DMA_UART(UART_descr);
    flasher_configure_serial_port_BAUD(UART_descr, CONF_BOOTLOADER_BAUD);
    
    if ( flasher_init(&(UART_descr->io) )) {
        while(1){
            if(bytes_to_write > bytes_step){ 
                flasher_loadBuffer(&(UART_descr->io), local_flash_address, bytes_step);
                flasher_writeBuffer(&(UART_descr->io), SRAM_START_ADDR, FLASH_START_ADDR + offset, bytes_step);
                
                local_flash_address += bytes_step;
                offset += bytes_step;
                bytes_to_write -= bytes_step;
            } else {
                flasher_loadBuffer(&(UART_descr->io), local_flash_address, bytes_to_write);
                flasher_writeBuffer(&(UART_descr->io), SRAM_START_ADDR, FLASH_START_ADDR + offset, bytes_to_write);
                break;
            }
        }
        flasher_reset(&(UART_descr->io));
    }

    flasher_configure_serial_port_BAUD(UART_descr, CONF_NETWORK_BAUD);
    enable_DMA_UART(UART_descr);
    return;
}





/*
uint16_t checksumBuffer(uint32_t start_addr, uint32_t size)
{
    //TODO: configure serial port

    if (size > _CHECKSUM_BUFFER_SIZE)
        printf("throw SambaError();\n");
        
    printf("%s(start_addr=%#x, size=%#x) = ", __FUNCTION__, start_addr, size);

    uint8_t cmd[64];
    int l = snprintf((char*) cmd, sizeof(cmd), "Z%08X,%08X#", start_addr, size);
    if (io_write(io_uart_e, cmd, l) != l)
        printf("throw SambaError();\n");
    //TODO: timeout
    //_port->timeout(TIMEOUT_LONG);
    cmd[0] = 0;
    //TODO: read
    //_port->read(cmd, 12); // Expects "Z00000000#\n\r"
    //TODO: timeout
    //_port->timeout(TIMEOUT_NORMAL);
    if (cmd[0] != 'Z')
        printf("throw SambaError();\n");

    cmd[9] = 0;
    uint32_t res;// = cmd[1] << 8 | cmd[2];
    if (sscanf((const char *)(cmd+1), "%x", &res) != 1)
	   printf("throw SambaError();\n");
    
    printf("%x\n", res);
    
    return res;
}
*/