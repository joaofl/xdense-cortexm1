#ifndef _RINGBACK_PACKET_XDENSE_H_INCLUDED
#define _RINGBACK_PACKET_XDENSE_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "../hal/utils/include/compiler.h"
#include "../hal/utils/include/utils_assert.h"

/**
 * \brief Ring buffer element type
 */
struct ringbuffer_xdense {
	uint8_t *buf;
	uint32_t size;
	uint32_t read_index;
	uint32_t write_index;
	uint32_t DMA_write_index;
};

/**
 * \brief Ring buffer init
 *
 * \param[in] rb The pointer to a ringbuffer structure instance
 * \param[in] buf Space to store the data
 * \param[in] size buffer length, must be aligned with power of 2
 *
 * \return ERR_NONE on success, or an error code on failure.
 */
int32_t ringbuffer_xdense_init(struct ringbuffer_xdense *const rb, void *buf, uint32_t size);

//TODO: documentation
int32_t ringbuffer_xdense_get_packet(struct ringbuffer_xdense *const rb, uint8_t *data, uint8_t n_bytes);

//TODO: documentation
uint8_t * ringbuffer_xdense_reserve_packet(struct ringbuffer_xdense *const rb, uint8_t n_bytes);

//TODO: documentation
uint8_t * ringbuffer_xdense_force_reserve_packet(struct ringbuffer_xdense *const rb, uint8_t n_bytes);

//TODO: documentation
void ringbuffer_xdense_transaction_DMA_completed_packet(struct ringbuffer_xdense *const rb);

/**
 * \brief Return the element number of ringbuffer
 *
 * \param[in] rb The pointer to a ringbuffer structure instance
 *
 * \return The number of element in ringbuffer [0, rb->size]
 */
uint32_t ringbuffer_xdense_num(const struct ringbuffer_xdense *const rb);

/**
 * \brief Flush ringbuffer, user needs to handle the concurrent access on buffer
 * via put/get/flush
 *
 * \param[in] rb The pointer to a ringbuffer structure instance
 *
 * \return ERR_NONE on success, or an error code on failure.
 */
uint32_t ringbuffer_xdense_flush(struct ringbuffer_xdense *const rb);



/**@}*/

#ifdef __cplusplus
}
#endif
#endif /* _RINGBACK_PACKET_XDENSE_H_INCLUDED */
