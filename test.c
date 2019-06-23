/*
 * avr-sdbg: One way serial debugging for AVR 8 bit MCUs using USB-to-Serial
 *           adapters.
 * Copyright (C) 2019 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file LICENSE.
 */

// this is just an usage example. don't need to be copied to your project.

#include <avr/io.h>
#include <util/delay.h>

#include "asdbg.h"

int
main(void)
{
    // PB2 as led output
    DDRB = _BV(PB2);

    asdbg_init();

    asdbg_print_byte_int_var("DDRB", DDRB);

    while (1) {
        PORTB |= _BV(PB2);
        asdbg_print_string("hi\n");
        asdbg_print_byte_hex_nl(PORTB);
        asdbg_print_byte_bin_var("PORTB", PORTB);
        _delay_ms(1000);
        PORTB &= ~_BV(PB2);
        asdbg_print_string("lo\n");
        asdbg_print_byte_hex(PORTB);
        asdbg_print_char('\n');
        asdbg_print_byte_bin_var("PORTB", PORTB);
        _delay_ms(1000);
    }

    return 0;
}
