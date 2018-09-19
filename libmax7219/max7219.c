/*
 * Copyright (c) 2018 Łukasz Derlatka
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "max7219.h"

uint8_t		max7219_screen[MAX7219_DEVICES * 8];

struct max7219_char {
	uint8_t ascii;
	uint8_t bitmap[8];
};

/* Font */
const struct max7219_char MAX7219_CHAR_TABLE[] PROGMEM = {
	{' ', {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}},
	{'A', {0x00, 0x22, 0x22, 0x3E, 0x22, 0x22, 0x22, 0x1C}},
};

void
max7219_send(max7219_addr addr, uint8_t reg, uint8_t value)
{
	uint8_t		buf[MAX7219_DEVICES * 2];
	uint32_t	i;
	uint8_t		j;

	memset(buf, 0x00, sizeof(buf));

	buf[addr * 2] = value;
	buf[addr * 2 + 1] = reg;

	MAX7219_CS_PORT &= ~(1 << MAX7219_CS);

	for (i = MAX7219_DEVICES * 2; i > 0; i--) {
		for (j = 8; j > 0; j--) {
			MAX7219_CLK_PORT &= ~(1 << MAX7219_CLK);

			if (buf[i - 1] & (1 << (j - 1))) {
				MAX7219_DIN_PORT |= (1 << MAX7219_DIN);
			} else {
				MAX7219_DIN_PORT &= ~(1 << MAX7219_DIN);
			}

			MAX7219_CLK_PORT |= (1 << MAX7219_CLK);
		}
	}

	MAX7219_CS_PORT |= (1 << MAX7219_CS);
}

void
max7219_write_bitmap(max7219_addr addr, uint8_t * bitmap)
{
	uint8_t		i;

	for (i = 0; i < 8; ++i)
		max7219_screen[addr * 8 + i] = bitmap[i];
}

void
max7219_clear(max7219_addr addr)
{
	memset(max7219_screen + (addr * 8), 0x00, 8);
}

void
max7219_negative(max7219_addr addr)
{
	uint8_t		i;

	for (i = 0; i < 8; ++i)
		max7219_screen[addr * 8 + i] = ~max7219_screen[addr * 8 + i];
}

void
max7219_refresh(max7219_addr addr)
{
	uint8_t		i;

	for (i = 0; i < 8; ++i)
		max7219_send(addr, i + 1, max7219_screen[addr * 8 + i]);
}

void
max7219_refresh_all(void)
{
	max7219_addr	i;

	for (i = 0; i < MAX7219_DEVICES; i++)
		max7219_refresh(i);
}

void
max7219_putc(max7219_addr addr, char c)
{
	uint32_t	i;
	uint8_t		buf[8];

	for (i = 0; i < sizeof(MAX7219_CHAR_TABLE) / sizeof(struct max7219_char); i++) {
		if (pgm_read_byte(&(MAX7219_CHAR_TABLE[i].ascii)) == c) {
			memcpy_P(buf, MAX7219_CHAR_TABLE[i].bitmap, sizeof(buf));
			max7219_write_bitmap(addr, buf);
			return;
		}
	}
}

void
max7219_puts(char *str)
{
	max7219_addr	i;

	for (i = 0; i < MAX7219_DEVICES; i++)
		max7219_putc(i, *str++);
}

void
max7219_init(void)
{
	max7219_addr	i;

	memset(max7219_screen, 0x00, sizeof(max7219_screen));

	MAX7219_CS_DDR |= (1 << MAX7219_CS);
	MAX7219_DIN_DDR |= (1 << MAX7219_DIN);
	MAX7219_CLK_DDR |= (1 << MAX7219_CLK);

	for (i = 0; i < MAX7219_DEVICES; i++) {
		max7219_set_displaytest(i, 0);
		max7219_set_scanlimit(i, 7);
		max7219_set_decode(i, 0);
		max7219_set_intensity(i, 15);
		max7219_set_power(i, 1);
	}
}
