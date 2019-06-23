/*
 * avr-sdbg: One way serial debugging for AVR 8 bit MCUs using USB-to-Serial
 *           adapters.
 * Copyright (C) 2019 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file LICENSE.
 */

#include <stddef.h>
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

#if defined(ASDBG_DISABLE_INTR)
#include <avr/interrupt.h>
#endif

#include "./asdbg.h"


#if defined(ASDBG_ENABLE) || \
    defined(ASDBG_ENABLE_BYTE_FUNCS) || \
    defined(ASDBG_ENABLE_BYTE_NL_FUNCS) || \
    defined(ASDBG_ENABLE_BYTE_VAR_FUNCS)

static inline void
_asdbg_hi()
{
    ASDBG_PORT |= _BV(ASDBG_PIN);
}


static inline void
_asdbg_lo()
{
    ASDBG_PORT &= ~_BV(ASDBG_PIN);
}


static inline void
_asdbg_set_pin(uint8_t val)
{
    ASDBG_PORT ^= (-val ^ ASDBG_PORT) & _BV(ASDBG_PIN);
}


static inline void
_asdbg_delay()
{
    _delay_us(1000000/ASDBG_BAUD_RATE);
}


void
asdbg_init()
{
    ASDBG_DDR |= _BV(ASDBG_PIN);
}


void
asdbg_print_char(char c)
{
#if defined(ASDBG_DISABLE_INTR)
    cli();
#endif

    _asdbg_lo();
    _asdbg_delay();

    for (size_t i = 0; i < 8; i++) {
        _asdbg_set_pin((c >> i) & 1);
        _asdbg_delay();
    }

    _asdbg_hi();
    _asdbg_delay();

#if defined(ASDBG_DISABLE_INTR)
    sei();
#endif
}


void
asdbg_print_string(const char *s)
{
    for (size_t i = 0; s[i] != 0; i++)
        asdbg_print_char(s[i]);
}

#endif


#if defined(ASDBG_ENABLE_BYTE_FUNCS) || \
    defined(ASDBG_ENABLE_BYTE_NL_FUNCS) || \
    defined(ASDBG_ENABLE_BYTE_VAR_FUNCS)

void
asdbg_print_byte_bin(uint8_t b)
{
    asdbg_print_char('0');
    asdbg_print_char('b');

    for (size_t i = 0; i < 8; i++)
        asdbg_print_char(b & (1 << (7 - i)) ? '1' : '0');
}


void
asdbg_print_byte_hex(uint8_t b)
{
    asdbg_print_char('0');
    asdbg_print_char('x');

    uint8_t t = b / 16;
    asdbg_print_char(t > 9 ? t + ('a' - 10) : t + '0');

    t = b % 16;
    asdbg_print_char(t > 9 ? t + ('a' - 10) : t + '0');
}


void
asdbg_print_byte_int(uint8_t b)
{
    // max int stored in one byte is 255
    if (b / 100) {
        asdbg_print_char((b / 100) + '0');
        b %= 100;
    }

    if (b / 10) {
        asdbg_print_char((b / 10) + '0');
        b %= 10;
    }

    asdbg_print_char(b + '0');
}

#endif


#if defined(ASDBG_ENABLE_BYTE_NL_FUNCS) || \
    defined(ASDBG_ENABLE_BYTE_VAR_FUNCS)

void
asdbg_print_byte_bin_nl(uint8_t b)
{
    asdbg_print_byte_bin(b);
    asdbg_print_char('\n');
}

void
asdbg_print_byte_hex_nl(uint8_t b)
{
    asdbg_print_byte_hex(b);
    asdbg_print_char('\n');
}

void
asdbg_print_byte_int_nl(uint8_t b)
{
    asdbg_print_byte_int(b);
    asdbg_print_char('\n');
}

#endif


#if defined(ASDBG_ENABLE_BYTE_VAR_FUNCS)

static void
print_var(const char *var)
{
    asdbg_print_string(var);
    asdbg_print_string(" = ");
}


void
asdbg_print_byte_bin_var(const char *var, uint8_t b)
{
    print_var(var);
    asdbg_print_byte_bin_nl(b);
}


void
asdbg_print_byte_hex_var(const char *var, uint8_t b)
{
    print_var(var);
    asdbg_print_byte_hex_nl(b);
}


void
asdbg_print_byte_int_var(const char *var, uint8_t b)
{
    print_var(var);
    asdbg_print_byte_int_nl(b);
}

#endif
