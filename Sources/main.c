/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "MKL25Z4.h"
#include "../Drivers/externs.h"
#include "../Middlewares/modbus/include/mb.h"
#include "../Middlewares/modbus/include/mbport.h"
#include "../Middlewares/modbus/include/mbutils.h"

#define REG_INPUT_START 				1000
#define REG_INPUT_NREGS 				8
#define REG_HOLDING_START           	2000
#define REG_HOLDING_NREGS           	50
#define REG_COILS_START					0
#define REG_COILS_NREGS					50
#define REG_DISCRETE_COILS_START		100
#define REG_DISCRETE_NREGS				50

static UCHAR usRegDiscreteCoilsStart 	= REG_DISCRETE_COILS_START;
static UCHAR usRegCoilsStart 			= REG_COILS_START;
static USHORT usRegHoldingStart 		= REG_HOLDING_START;
static USHORT usRegInputStart 			= REG_INPUT_START;

static UCHAR usRegDiscreteCoilsBuf[REG_DISCRETE_NREGS];
static UCHAR usRegCoilsBuf[REG_COILS_NREGS];
static USHORT usRegHoldingBuf[REG_HOLDING_NREGS];
static USHORT usRegInputBuf[REG_INPUT_NREGS];

int main(void)
{
	// inicializa modbus
	eMBInit( MB_RTU, 1, 0, 19200, MB_PAR_NONE );
	eMBEnable();

	// Inicializa PTB18 - LED Vermelho
	gpio_Init(GPIOB,18,OUTPUT,NO_PULL_RESISTOR);

	for (;;)
    {
		eMBPoll();
        gpio_Toggle(GPIOB,18);
    }
    /* Never leave main */
    return 0;
}
/****************************************************************************************
*
*****************************************************************************************/
eMBErrorCode eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs )
{
    eMBErrorCode    eStatus = MB_ENOERR;
    int             iRegIndex;

    if(( usAddress >= REG_INPUT_START ) && ( usAddress + usNRegs <= REG_INPUT_START + REG_INPUT_NREGS ))
    {
        iRegIndex = ( int )( usAddress - usRegInputStart );
        while( usNRegs > 0 )
        {
            *pucRegBuffer++ = ( unsigned char )( usRegInputBuf[iRegIndex] >> 8 );
            *pucRegBuffer++ = ( unsigned char )( usRegInputBuf[iRegIndex] & 0xFF );
            iRegIndex++;
            usNRegs--;
        }
    }
    else
    {
        eStatus = MB_ENOREG;
    }
    return eStatus;
}
/****************************************************************************************
*
*****************************************************************************************/
eMBErrorCode eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode )
{
    //return MB_ENOREG;
	eMBErrorCode eStatus = MB_ENOERR;
	int iRegIndex;

	if((usAddress >= REG_HOLDING_START) && (usAddress + usNRegs <= REG_HOLDING_START + REG_HOLDING_NREGS))
	{
		iRegIndex = (int)(usAddress - usRegHoldingStart);
		switch(eMode)
		{
		/* Pass current register values to the protocol stack. */
		case MB_REG_READ:
			while(usNRegs > 0)
			{
				*pucRegBuffer++ = (unsigned char)(usRegHoldingBuf[iRegIndex] >> 8);
				*pucRegBuffer++ = (unsigned char)(usRegHoldingBuf[iRegIndex] & 0xFF);
				iRegIndex++;
				usNRegs--;
			}
			break;

			/* Update current register values with new values from the
			 * protocol stack. */
		case MB_REG_WRITE:
			while(usNRegs > 0)
			{
				usRegHoldingBuf[iRegIndex] = *pucRegBuffer++ << 8;
				usRegHoldingBuf[iRegIndex] |= *pucRegBuffer++;
				iRegIndex++;
				usNRegs--;
			}
		}
	}
	else
	{
		eStatus = MB_ENOREG;
	}
	return eStatus;
}
/****************************************************************************************
*
*****************************************************************************************/
eMBErrorCode eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils, eMBRegisterMode eMode )
{
   // return MB_ENOREG;
    eMBErrorCode eStatus = MB_ENOERR;
    int iRegIndex;

    if((usAddress >= REG_COILS_START) && (usAddress + usNCoils <= REG_COILS_START + REG_COILS_NREGS))
    {
        iRegIndex = (int)(usAddress - usRegCoilsStart);

        switch(eMode)
        {
            case MB_REG_READ:
            {
                while(usNCoils > 0)
                {
                    UCHAR ucResult = xMBUtilGetBits(usRegCoilsBuf, iRegIndex, 1);
                    xMBUtilSetBits(pucRegBuffer, iRegIndex - (usAddress - usRegCoilsStart), 1, ucResult);
                    iRegIndex++;
                    usNCoils--;
                }
                break;
            }
            case MB_REG_WRITE:
            {
                while ( usNCoils > 0 )
                {
                    UCHAR ucResult = xMBUtilGetBits(pucRegBuffer, iRegIndex - (usAddress - usRegCoilsStart), 1);
                    xMBUtilSetBits(usRegCoilsBuf, iRegIndex, 1, ucResult );
                    iRegIndex++;
                    usNCoils--;
                }
                break;
            }
        }
    }
    else
    {
        eStatus = MB_ENOREG;
    }
    return eStatus;
}
/****************************************************************************************
*
*****************************************************************************************/
eMBErrorCode eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
{
    //return MB_ENOREG;
	eMBErrorCode eStatus = MB_ENOERR;
	int  iRegIndex;

	if((usAddress >= REG_DISCRETE_COILS_START) && (usAddress + usNDiscrete <= REG_DISCRETE_COILS_START + REG_DISCRETE_NREGS))
	{
		iRegIndex = (int)(usAddress - usRegDiscreteCoilsStart);
		while(usNDiscrete > 0)
		{
			UCHAR ucResult = xMBUtilGetBits(usRegDiscreteCoilsBuf, iRegIndex, 1);
			xMBUtilSetBits(pucRegBuffer, iRegIndex - (usAddress - usRegDiscreteCoilsStart), 1, ucResult);
			iRegIndex++;
			usNDiscrete--;
		}
	}
	else
	{
		eStatus = MB_ENOREG;
	}
	return eStatus;
}
/****************************************************************************************
*
*****************************************************************************************/
