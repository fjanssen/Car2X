/*
 * See header file for documentation.
 * eth_uart.cpp
 *
 *  Created on: 06.12.2013
 *      Author: Florian
 */

// Export interface
#include "eth_uart.h"

// Import interfaces
#include <system.h>
#include "..\etc\utility.h"

#define UARTNAME "/dev/uart_0"

CEth_UART_Socket::CEth_UART_Socket()
{
	m_pDevice = alt_up_rs232_open_dev(UARTNAME);

	m_iTxFrameNr = 0;
}

CEth_UART_Socket::~CEth_UART_Socket()
{


}


bool CEth_UART_Socket::Send(data_t *p_Data, alt_u32 iLength)
{
	alt_u32 uiFreeSpace = 0;
	bool fail = false;

	while(iLength > 0)
	{
		uiFreeSpace = alt_up_rs232_get_available_space_in_write_FIFO(m_pDevice);

		if(uiFreeSpace > iLength)
			uiFreeSpace = iLength;

		for (alt_u32 i = 0; i < uiFreeSpace; i++)
		{
			fail = fail || (alt_up_rs232_write_data(m_pDevice, *p_Data) < 0);
			p_Data++;
		}
		iLength = iLength - uiFreeSpace;
	}


	return !fail;
}

alt_32 CEth_UART_Socket::Receive(data_t *p_Data, alt_u32 iLength, alt_u32 iTimeOut)
{
	alt_u32 iTime = 10;
	alt_u32 uiCount = 0;
	alt_u8 uiParity = 0;
	alt_u32 i = 0;

	iTimeOut *= 400;

	do
	{
		uiCount = alt_up_rs232_get_used_space_in_read_FIFO(m_pDevice);
		iTime += 5;
		if(iTime > iTimeOut)
			return 0;
	}while(uiCount == 0);

	while(uiCount > 0 && iLength > 0)
	{
		while(uiCount > 0 && iLength > 0)
		{
			alt_up_rs232_read_data(m_pDevice, (alt_u8*) p_Data+i, &uiParity);
			uiCount--;
			iLength--;
			i++;
		}
		delay(1);
		uiCount = alt_up_rs232_get_used_space_in_read_FIFO(m_pDevice);
	}

	return i;
}

alt_32 CEth_UART_Socket::ReceiveImmediate(data_t *p_Data, alt_u32 iLength)
{
	alt_u32 uiCount = 0;
	alt_u8 uiParity = 0;
	alt_u32 i = 0;

	uiCount = alt_up_rs232_get_used_space_in_read_FIFO(m_pDevice);

	while(uiCount > 0 && iLength > 0)
	{
		while(uiCount > 0 && iLength > 0)
		{
			alt_up_rs232_read_data(m_pDevice, (alt_u8*) p_Data+i, &uiParity);
			uiCount--;
			iLength--;
			i++;
		}
		uiCount = alt_up_rs232_get_used_space_in_read_FIFO(m_pDevice);
	}

	return i;
}

bool CEth_UART_Socket::Reset()
{
	m_iTxFrameNr = 0;
	return true;
}
