/**
 * \file
 *
 * \brief STDIO redirection
 *
 * Copyright (C) 2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */

#include <stdio_io.h>
#include <stdio.h>

#ifndef _UNIT_TEST_
#include <yfuns.h>
#else
#define _STD_BEGIN
#define _STD_END
#define _LLIO_ERROR ((size_t)-1) /* For __read and __write. */
#define _LLIO_STDIN 0
#define _LLIO_STDOUT 1
#define _LLIO_STDERR 2
#endif

_STD_BEGIN

#pragma module_name = "?__read"

/*! \brief Reads a number of bytes, at most \a size, into the memory area
 *         pointed to by \a buffer.
 *
 * \param handle File handle to read from.
 * \param buffer Pointer to buffer to write read bytes to.
 * \param size Number of bytes to read.
 *
 * \return The number of bytes read, \c 0 at the end of the file, or
 *         \c _LLIO_ERROR on failure.
 */
size_t __read(int handle, unsigned char *buffer, size_t size)
{
	int n = 0;
	/* This implementation only reads from stdin.
	 * For all other file handles, it returns failure. */
	if (handle != _LLIO_STDIN) {
		return _LLIO_ERROR;
	}

	n = stdio_io_read((uint8_t *)buffer, size);
	if (n < 0) {
		return _LLIO_ERROR;
	}
	return n;
}

/*! \brief This routine is required by IAR DLIB library since EWAVR V6.10
 * the implementation is empty to be compatible with old IAR version.
 */
int __close(int handle)
{
	(void)(handle);
	return 0;
}

#ifndef __GNUC__
/*! \brief This routine is required by IAR DLIB library since EWAVR V6.10
 * the implementation is empty to be compatible with old IAR version.
 */
int remove(const char *val)
{
	(void)(val);
	return 0;
}
#endif

/*! \brief This routine is required by IAR DLIB library since EWAVR V6.10
 * the implementation is empty to be compatible with old IAR version.
 */
long __lseek(int handle, long val, int val2)
{
	(void)(handle);
	(void)(val2);
	return val;
}

_STD_END
