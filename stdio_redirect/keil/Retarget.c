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

#include <stdio.h>

#ifdef _UNIT_TEST_
#undef fputc
#undef fgetc
#undef ferror
#define fputc ut_fputc
#define fgetc ut_fgetc
#define ferror ut_ferror
#endif

#include <stdio_io.h>

/* Disable semihosting */
#pragma import(__use_no_semihosting_swi)

#ifndef __GNUC__
struct __FILE {
	int handle;
};
#endif
FILE __stdout;
FILE __stdin;
FILE __stderr;

int fputc(int ch, FILE *f)
{
	if ((f == stdout) || (f == stderr)) {
		uint8_t tmp = (uint8_t)ch;
		if (stdio_io_write(&tmp, 1) < 0) {
			return EOF;
		}
		return ch;
	} else {
		return EOF;
	}
}

int fgetc(FILE *f)
{
	if (f == stdin) {
		uint8_t tmp = 0;
		if (stdio_io_read(&tmp, 1) < 0) {
			return EOF;
		}
		return tmp;
	} else {
		return EOF;
	}
}

void _ttywrch(int ch)
{
	uint8_t tmp = (uint8_t)ch;
	stdio_io_write(&tmp, 1);
}

int ferror(FILE *f)
{
	(void)f;
	/* Your implementation of ferror */
	return EOF;
}

void _sys_exit(int return_code)
{
	(void)return_code;
	while (1) {
	}; /* endless loop */
}
