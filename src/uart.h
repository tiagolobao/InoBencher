
/**
 * @file uart.h
 * @brief functions to use UART/Serial comminication

 * @author Devilbinder (Binder Tronics)
 * Modified by Tiago Lobao
 * 
 * @license 
 * Copyright (c) 2021 Devilbinder (Binder Tronics) https://bindertronics.com/
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 **/ 


#ifndef UART_HAL_H_
#define UART_HAL_H_

#include "FreeRTOS.h"
#include "task.h"
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define RX_BUFFER_SIZE 64

/******************************************************
 * @name uart_init
 *
 * @brief initializes the Serial communication
 *
 * @arg uint32_t baud - baud rate (9600u..115200u)
 *      uint8_t high_speed (1 means high speed)
 *
 * @return void
 *
 *****************************************************/
void uart_init(uint32_t baud,uint8_t high_speed);

/******************************************************
 * @name uart_send_byte
 *
 * @brief Sends single byte via serial UART
 *
 * @arg uint8_t baud - byte to send
 *
 * @return void
 *
 *****************************************************/
void uart_send_byte(uint8_t c);

/******************************************************
 * @name uart_send_array
 *
 * @brief Sends single byte via serial UART
 *
 * @arg uint8_t* c - array to send
 *      uint16_t len - length of the array
 *
 * @return void
 *
 *****************************************************/
void uart_send_array(uint8_t *c,uint16_t len);

/******************************************************
 * @name uart_send_string
 *
 * @brief Sends full string
 *
 * @arg uint8_t* c - string to send (needs to finish with '\0')
 *
 * @return void
 *
 *****************************************************/
void uart_send_string(uint8_t *c);

/******************************************************
 * @name uart_read_count
 *
 * @brief ?
 *
 * @arg uint8_t baud - byte to send
 *
 * @return uint16_t
 *
 *****************************************************/
uint16_t uart_read_count(void);

/******************************************************
 * @name uart_read
 *
 * @brief Receive byte from UART Serial
 *
 * @arg uint8_t baud - byte to send
 *
 * @return uint8_t
 *
 *****************************************************/
uint8_t uart_read(void);

#endif /* UART_HAL_H_ */