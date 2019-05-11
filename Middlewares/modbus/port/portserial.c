/*
 * FreeModbus Libary: BARE Port
 * Copyright (C) 2006 Christian Walter <wolti@sil.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id$
 */

#include "port.h"

/* ----------------------- Modbus includes ---------------------------------*/
#include "../include/mb.h"
#include "../include/mbport.h"

/* ----------------------- Drivers includes ---------------------------------*/
#include "../Drivers/externs.h"

/* -------------------------- Macros --------------------------------------- */
#define MDSERIAL 	UART1

/* ----------------------- static functions ---------------------------------*/
static void prvvUARTTxReadyISR( void );
static void prvvUARTRxISR( void );
static void prvvMBPortSerialISR( void );

/* ----------------------- Static variables -------------------------------- */
BOOL bTXEnabled;
BOOL bRXEnabled;

/* ----------------------- Start implementation -----------------------------*/
void
vMBPortSerialEnable( BOOL xRxEnable, BOOL xTxEnable )
{
    /*
     * If xRXEnable enable serial receive interrupts. If xTxENable enable
     * transmitter empty interrupts.
     */
    if( xRxEnable )
    {
        bRXEnabled = TRUE;
        MDSERIAL->C2 |= UART_C2_RIE_MASK;
    }
    else
    {
        bRXEnabled = FALSE;
        MDSERIAL->C2 &= ~UART_C2_RIE_MASK;
    }
    if( xTxEnable )
    {
        bTXEnabled = TRUE;
        MDSERIAL->C2 |= UART_C2_TIE_MASK;
    }
    else
    {
        bTXEnabled = FALSE;
        MDSERIAL->C2 &= ~UART_C2_TIE_MASK;
    }

}

BOOL
xMBPortSerialInit( UCHAR ucPORT, ULONG ulBaudRate, UCHAR ucDataBits, eMBParity eParity )
{
	uart_Init(MDSERIAL, 2, (uint32_t)ulBaudRate);
	uart_add_callback(MDSERIAL,prvvMBPortSerialISR);
	uart_enable_irq(MDSERIAL);
    return TRUE;
}

BOOL
xMBPortSerialPutByte( CHAR ucByte )
{
    /*
     * Put a byte in the UARTs transmit buffer. This function is called
     * by the protocol stack if pxMBFrameCBTransmitterEmpty( ) has been
     * called.
     */
	while(!(MDSERIAL->S1 & UART_S1_TDRE_MASK));
	MDSERIAL->D = (uint8_t)ucByte;
	MDSERIAL->C2 |= UART_C2_TIE_MASK ;
    return TRUE;
}

BOOL
xMBPortSerialGetByte( CHAR * pucByte )
{
    /*
     * Return the byte in the UARTs receive buffer. This function is called
     * by the protocol stack after pxMBFrameCBByteReceived( ) has been called.
     */
	while(!(MDSERIAL->S1 & UART0_S1_TDRE_MASK));
	*pucByte = MDSERIAL->D;
    return TRUE;
}

/*
 * Create an interrupt handler for the transmit buffer empty interrupt
 * (or an equivalent) for your target processor. This function should then
 * call pxMBFrameCBTransmitterEmpty( ) which tells the protocol stack that
 * a new character can be sent. The protocol stack will then call 
 * xMBPortSerialPutByte( ) to send the character.
 */
static void prvvUARTTxReadyISR( void )
{
    pxMBFrameCBTransmitterEmpty(  );
}

/*
 * Create an interrupt handler for the receive interrupt for your target
 * processor. This function should then call pxMBFrameCBByteReceived( ). The
 * protocol stack will then call xMBPortSerialGetByte( ) to retrieve the
 * character.
 */
static void prvvUARTRxISR( void )
{
    pxMBFrameCBByteReceived(  );
}

/*
 * IRQ Uart
 */
void prvvMBPortSerialISR( void )
{
    if( bTXEnabled && ( MDSERIAL->S1 & UART_S1_TC_MASK ) )
    {
        ( void )pxMBFrameCBTransmitterEmpty(  );
    }
    if( bRXEnabled && ( MDSERIAL->S1 & UART_S1_RDRF_MASK ) )
    {
        ( void )pxMBFrameCBByteReceived(  );
    }
}
