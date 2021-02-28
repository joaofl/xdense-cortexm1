#include "ringback_packet_xdense.h"

/**
 * \brief Ringbuffer init
 */
int32_t ringbuffer_xdense_init(struct ringbuffer_xdense *const rb, void *buf, uint32_t size)
{
	ASSERT(rb && buf && size);

	/*
	 * buf size must be aligned to power of 2
	 */
	if ((size & (size - 1)) != 0) {
		return ERR_INVALID_ARG;
	}

	/* size - 1 is faster in calculation */
	rb->size        	= size - 1;
	rb->read_index  	= 0;
	rb->write_index 	= rb->read_index;
	rb->DMA_write_index = rb->read_index;
	rb->buf         	= (uint8_t *)buf;

	return ERR_NONE;
}

/**
 * \brief Get one packet from ringbuffer
 *
 */
int32_t ringbuffer_xdense_get_packet(struct ringbuffer_xdense *const rb, uint8_t *data, uint8_t n_bytes)
{
	ASSERT(rb && data);
	int i;
	if(ringbuffer_xdense_num(rb) >= n_bytes){
		if (rb->write_index != rb->read_index) {
			for(i = 0; i < n_bytes; i++){
				data[i] = rb->buf[rb->read_index & rb->size];
				rb->read_index++;
			}
			return ERR_NONE;
		}
	}
	return ERR_NOT_FOUND;
}
/**
 * \brief Reserve n_bytes in ringbuffer, return address of the buffer where DMA should store data
 *
 */
uint8_t * ringbuffer_xdense_reserve_packet(struct ringbuffer_xdense *const rb, uint8_t n_bytes)
{
	ASSERT(rb);

	uint8_t * buff_position_address = &(rb->buf[rb->write_index & rb->size]);

	//rb->buf[rb->write_index & rb->size] = data;

	/*
	 * buffer full strategy: new data will overwrite the oldest data in
	 * the buffer
	 */
	if ((rb->write_index - rb->read_index) > rb->size) {
		//rb->read_index = rb->write_index - rb->size;
		return NULL;
	}

	rb->DMA_write_index+=n_bytes;

	return buff_position_address;
}
uint8_t * ringbuffer_xdense_force_reserve_packet(struct ringbuffer_xdense *const rb, uint8_t n_bytes)
{
	ASSERT(rb);

	rb->write_index-=n_bytes;

	uint8_t * buff_position_address = &(rb->buf[rb->write_index & rb->size]);

	return buff_position_address;
}
void ringbuffer_xdense_transaction_DMA_completed_packet(struct ringbuffer_xdense *const rb)
{
	ASSERT(rb);
	rb->write_index = rb->DMA_write_index; 

	return;
}

/**
 * \brief Return the element number of ringbuffer
 */
uint32_t ringbuffer_xdense_num(const struct ringbuffer_xdense *const rb)
{
	ASSERT(rb);

	return rb->write_index - rb->read_index;
}

/**
 * \brief Flush ringbuffer
 */
uint32_t ringbuffer_xdense_flush(struct ringbuffer_xdense *const rb)
{
	ASSERT(rb);

	rb->read_index = rb->write_index;

	return ERR_NONE;
}
