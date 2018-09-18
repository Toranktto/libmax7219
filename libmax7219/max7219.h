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

#ifndef _MAX7219_H
#define _MAX7219_H

#include <stdlib.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#include "max7219_config.h"

#define MAX7219_REG_NOP 0x00
#define MAX7219_REG_DIG0 0x01
#define MAX7219_REG_DIG1 0x02
#define MAX7219_REG_DIG2 0x03
#define MAX7219_REG_DIG3 0x04
#define MAX7219_REG_DIG4 0x05
#define MAX7219_REG_DIG5 0x06
#define MAX7219_REG_DIG6 0x07
#define MAX7219_REG_DIG7 0x08
#define MAX7219_REG_DECODE 0x09
#define MAX7219_REG_INTENSITY 0x0A
#define MAX7219_REG_SCANLIMIT 0x0B
#define MAX7219_REG_POWER 0x0C
#define MAX7219_REG_DISPLAYTEST 0x0F

struct max7219_char {
	uint8_t ascii;
	uint8_t bitmap[8];
};

typedef uint32_t max7219_addr;

void max7219_send(max7219_addr addr, uint8_t reg, uint8_t value);

#define max7219_set_decode(x, y) max7219_send(x, MAX7219_REG_DECODE, y)
#define max7219_set_intensity(x, y) max7219_send(x, MAX7219_REG_INTENSITY, y)
#define max7219_set_scanlimit(x, y) max7219_send(x, MAX7219_REG_SCANLIMIT, y)
#define max7219_set_power(x, y) max7219_send(x, MAX7219_REG_POWER, y)
#define max7219_set_displaytest(x, y) max7219_send(x, MAX7219_REG_DISPLAYTEST, y)

void max7219_clear(max7219_addr);
void max7219_write_bitmap(max7219_addr, uint8_t *);
void max7219_negative(max7219_addr);

void max7219_refresh(max7219_addr);
void max7219_refresh_all(void);

void max7219_putc(max7219_addr, char);
void max7219_puts(char *);

void max7219_init(void);

#endif
