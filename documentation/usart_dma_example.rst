Introduction
============

This is the documentation for the USART DMA application.

This example receives 8 bytes of data from serial port (SERCOM3) and transmits back the same data via same serial port (SERCOM3) using DMA


Supported evaluation kit
------------------------

 - `ATSAML21-XPRO-B <http://www.atmel.com/tools/ATSAML21-XPRO-B.aspx>`_

Interface settings
------------------

- USART
	- No parity
	- 8-bit character size
	- 1 stop bit
	- 115200 baud-rate
	- Port PA23 as SERCOM3 RX pin
	- Port PA22 as SERCOM3 TX pin
	
- DMA
	- Channel 0 from USART receive operation
	- Channel 1 from USART transmit operation

Running the demo
----------------

1. Press Download Pack and save the .atzip file
2. Import .atzip file into Atmel Studio 7, File->Import->Atmel Start Project.
3. Build and flash into supported evaluation board
4. Open the serial port in Atmel Data Visualizer or any serial port monitor.
5. Press the Reset button.
6. Send 8 bytes of data from serial port monitor.
7. You will receive the same data which was sent and it displayed in the serial port monitor.
