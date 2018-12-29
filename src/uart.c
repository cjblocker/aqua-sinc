/*
 * This file is part of the 1bitsy project.
 *
 * Copyright (C) 2017 Piotr Esden-Tempski <piotr@esden.net>
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>

#include "uart.h"

void uart_init(void)
{
	/* Enable clock for the GPIO bank and USART peripheral blocks. */
	rcc_periph_clock_enable(RCC_GPIOC);
	rcc_periph_clock_enable(RCC_UART5);

	/* Setup GPIO pins for USART3 transmit. */
	gpio_mode_setup(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO12);

	/* Setup USART3 TX pin as alternate function. */
	gpio_set_af(GPIOC, GPIO_AF8, GPIO12);

	/* Setup USART2 parameters. */
	usart_set_baudrate(UART5, 38400);
	usart_set_databits(UART5, 8);
	usart_set_stopbits(UART5, USART_STOPBITS_1);
	usart_set_mode(UART5, USART_MODE_TX);
	usart_set_parity(UART5, USART_PARITY_NONE);
	usart_set_flow_control(UART5, USART_FLOWCONTROL_NONE);

	/* Finally enable the USART. */
	usart_enable(UART5);
}

size_t uart_write_blocking(const char *buf, size_t len)
{
	for (size_t i = 0; i < len; i++) {
		usart_send_blocking(UART5, buf[i]);
	}

	return len;
}