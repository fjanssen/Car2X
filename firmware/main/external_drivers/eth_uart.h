/*
 * eth_uart.h
 *
 *  Created on: 06.12.2013
 *      Author: Florian
 */

#ifndef ETH_UART_H_
#define ETH_UART_H_

// Import interfaces
#include <alt_types.h>
#include "altera_up_avalon_rs232.h"

typedef alt_u8 data_t;

/*
 * Class implements a socket to the Eth_to_UART chip via UART.
 *
 * It uses the altera_up_avalon_rs232 lib and the corresponding IP-core in the FPGA.
 * You may only build this file if the Altera-University-Program is installed on your system. To
 * get the installer visit http://www.altera.com/education/univ/software/upds/unv-upds.html
 *
 * The IP-core consists of two 128 byte FIFOs for receiving and sending. Thus the max. size of
 * the buffers used in this class can be set to 128. Please make sure that the buffer size of
 * the IP-core may change sometime (if there is not enough space in the FPGA).
 */
class CEth_UART_Socket
{

public:
	/*
	 * Constructor which opens the rs232 socket. The iTxFrameNr is set to 0.
	 */
	CEth_UART_Socket();

	/*
	 * Empty destructor.
	 */
	~CEth_UART_Socket();

	/*
	 * Sends the given byte data of iLength. Blocking until the whole data was send.
	 * Note: There is no maximum run-time because we have to wait for the calls
	 * alt_up_rs232_get_available_space_in_write_FIFO(..) and alt_up_rs232_write_data(..)
	 * which have no run-time-maximum on their own!
	 */
	bool Send(data_t *p_Data, alt_u32 iLength);

	/*
	 * Receives bytes from the socket and stores them in the given byte array. Only the given
	 * number (iLength) bytes will be received.
	 * This method blocks until:
	 *     time-out: The time-out refers to the waiting time in which no byte is in the
	 *               receive FIFO. There is no exact unit for the time-out but it is approx. in ms.
	 *     iLength bytes have been read.
	 *     no more bytes in FIFO.
	 *
	 * The receive consists of:
	 * --+--> CHECK FIFO --+-(bytes found)-------->+--> READ uiCount BYTES --> DELAY 1 ms --+
	 *   A   (uiCount set) |                       A                                        |
	 *   |                 +-(FIFO is empty)---+   |                                        |
	 *   |                                     |   +--(bytes found)--+--- CHECK FIFO <------+
	 *   +--(no time-out)--+-INCREASE TIMEOUT<-+                     |   (uiCount set)
	 *                     |                       +-(FIFO is empty)-+
	 *                     |                       |
	 *                     |					   V
	 *                     +--(time-out reached)-->+--------------------------------> EXIT
	 *
	 * It is guaranteed that no more than iLength bytes are read.
	 * Please keep the DELAY of 1 ms in mind!
	 *
	 * That said the runtime can be max:
	 * timeOut (ms) + iLength * 1 ms + time in READ and CHECK
	 * Although this runtime is very high it can be less then repeated calls of Receive(..)
	 * see below.
	 *
	 * return: the count of read bytes
	 */
	alt_32 Receive(data_t *p_Data, alt_u32 iLength, alt_u32 iTimeOut);

	/*
	 * The same as the Receive(..) method but without the time-out and the delay of 1 ms:
	 * -----> CHECK FIFO --+-(bytes found)-------->+--> READ uiCount BYTES -----------------+
	 *       (uiCount set) |                       A                                        |
	 *                     +-(FIFO is empty)---+   |                                        |
	 *                                         |   +--(bytes found)--+--- CHECK FIFO <------+
	 *                                         |                     |   (uiCount set)
	 *                                         |   +-(FIFO is empty)-+
	 *                                         |   |
	 *                                         |   V
	 *                                         +-->+--------------------------------> EXIT
	 *
	 * It is guaranteed that no more than iLength bytes are read.
	 * This is a much faster implementation. The runtime can be max in O(iLength) + time in READ
	 * and CHECK. Thereby this method waits not for an incoming packet and can so return with 0
	 * bytes read. This method is recommended in the hard-timed part of the working cycle.
	 *
	 * return: the count of read bytes
	 */
	alt_32 ReceiveImmediate(data_t *p_Data, alt_u32 iLength);

	/*
	 * Sets TxFrameNr back to 0.
	 * return: always true.
	 */
	bool Reset();

private:
	alt_up_rs232_dev *m_pDevice; // Reference to the device driver.
	alt_u32 m_iTxFrameNr;        // Number of the send frames (not used yet).

};

#endif /* ETH_UART_H_ */
