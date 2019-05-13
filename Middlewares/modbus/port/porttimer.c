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

/* ----------------------- Platform includes --------------------------------*/
#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "../include/mb.h"
#include "../include/mbport.h"

/* ----------------------- Drivers includes ----------------------------------*/
#include "../Drivers/externs.h"

/*-------- Macro to convert a microsecond period to raw count value ---------*/
#define USEC_TO_COUNT(us, clockFreqInHz) 	(uint32_t)((uint64_t)us * clockFreqInHz / 1000000U)
#define CHANNEL_PIT_MODBUS					PIT_CH_0

/* ----------------------- static variable ---------------------------------*/
//static uint16_t timeout = 0;
//static uint16_t downcounter = 0;

/* ----------------------- static functions ---------------------------------*/
static void prvvTIMERExpiredISR( uint8_t ch );

/* ----------------------- Start implementation -----------------------------*/
BOOL
xMBPortTimersInit( USHORT usTim1Timerout50us )
{
	uint32_t time = 0;
	//timeout = usTim1Timerout50us;
	time = (uint32_t)( USEC_TO_COUNT( (usTim1Timerout50us * 49/*T: 50us */),SystemCoreClock) );
	pit_Init( time, CHANNEL_PIT_MODBUS );
	pit_Add_Callback(prvvTIMERExpiredISR);
    return TRUE;
}


inline void
vMBPortTimersEnable(  )
{
    /* Enable the timer with the timeout passed to xMBPortTimersInit( ) */
	//downcounter = timeout;
	pit_Start( CHANNEL_PIT_MODBUS );
}

inline void
vMBPortTimersDisable(  )
{
    /* Disable any pending timers. */
	pit_Stop( CHANNEL_PIT_MODBUS );
}

/* Create an ISR which is called whenever the timer has expired. This function
 * must then call pxMBPortCBTimerExpired( ) to notify the protocol stack that
 * the timer has expired.
 */
static void prvvTIMERExpiredISR( uint8_t ch )
{
	if(ch == CHANNEL_PIT_MODBUS)
	{
		//if (!--downcounter)
		//{
			( void )pxMBPortCBTimerExpired(  );
		//}
	}
}

