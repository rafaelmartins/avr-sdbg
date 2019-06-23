/*
 * avr-sdbg: One way serial debugging for AVR 8 bit MCUs using USB-to-Serial
 *           adapters.
 * Copyright (C) 2019 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file LICENSE.
 */

#pragma once

// TX pin configuration
#define ASDBG_BAUD_RATE     9600
#define ASDBG_DDR           DDRB
#define ASDBG_PORT          PORTB
#define ASDBG_PIN           PB3


#include <stdint.h>


#if defined(ASDBG_ENABLE) || \
    defined(ASDBG_ENABLE_BYTE_FUNCS) || \
    defined(ASDBG_ENABLE_BYTE_NL_FUNCS) || \
    defined(ASDBG_ENABLE_BYTE_VAR_FUNCS)

void asdbg_init();
void asdbg_print_char(char c);
void asdbg_print_string(const char *s);

#else

#define asdbg_init() ((void)0)
#define asdbg_print_char(a) ((void)0)
#define asdbg_print_string(a) ((void)0)

#endif


#if defined(ASDBG_ENABLE_BYTE_FUNCS) || \
    defined(ASDBG_ENABLE_BYTE_NL_FUNCS) || \
    defined(ASDBG_ENABLE_BYTE_VAR_FUNCS)

void asdbg_print_byte_bin(uint8_t b);
void asdbg_print_byte_hex(uint8_t b);
void asdbg_print_byte_int(uint8_t b);

#else

#define asdbg_print_byte_bin(a) ((void)0)
#define asdbg_print_byte_hex(a) ((void)0)
#define asdbg_print_byte_int(a) ((void)0)

#endif


#if defined(ASDBG_ENABLE_BYTE_NL_FUNCS) || \
    defined(ASDBG_ENABLE_BYTE_VAR_FUNCS)

void asdbg_print_byte_bin_nl(uint8_t b);
void asdbg_print_byte_hex_nl(uint8_t b);
void asdbg_print_byte_int_nl(uint8_t b);

#else

#define asdbg_print_byte_bin_nl(b) ((void)0)
#define asdbg_print_byte_hex_nl(b) ((void)0)
#define asdbg_print_byte_int_nl(b) ((void)0)

#endif


#if defined(ASDBG_ENABLE_BYTE_VAR_FUNCS)

void asdbg_print_byte_bin_var(const char *var, uint8_t b);
void asdbg_print_byte_hex_var(const char *var, uint8_t b);
void asdbg_print_byte_int_var(const char *var, uint8_t b);

#else

#define asdbg_print_byte_bin_var(a, b) ((void)0)
#define asdbg_print_byte_hex_var(a, b) ((void)0)
#define asdbg_print_byte_int_var(a, b) ((void)0)

#endif
