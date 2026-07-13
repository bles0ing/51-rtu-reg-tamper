Practice: 51 MCU Simulated Industrial RTU Register Tampering
Overview
This project simulates a tampering attack on an industrial RTU's holding register using a 51 microcontroller and an AT24C02 EEPROM. The device exposes an unprotected UART debug interface that allows reading and modifying the register value without authentication.
Attack chain:
	Physical access to UART debug port
	Send SETcommand to modify register value
	Logic analyzer captures I2C bus traffic during EEPROM write
	(Future) Offline EEPROM modification via CH341A programmer
Hardware
	51 MCU board (STC89C52RC @ 11.0592MHz)
	AT24C02 I2C EEPROM (stores 4-byte register at address 0x00-0x03)
	CH340 USB-to-Serial adapter
	24MHz 8-channel logic analyzer (FX2 clone)
Software
	Keil C51 (MCU firmware)
	PulseView (logic analyzer)
	Python 3 + pyserial (attack script)
Implementation Details
MCU Firmware code/main.c
	Initialization: On boot, reads 4-byte register from EEPROM address 0x00-0x03
	Normal operation: Button press increments register by 1, writes back to EEPROM
	UART command parsing: Uses timeout-based detection (1 second idle = end of command)
	READ: Sends 4 bytes (big-endian) via UART
	SET XXXX: Parses next 4 bytes as ASCII digits, adds 0x30 offset, writes to EEPROM
	Other input: Clears buffer, resets state machine
Logic Analyzer Capture
	UART: Captured continuous 4-byte READ response 0x310x320x330x34="1234"
	I2C: Captured EEPROM write frame (Device 0x50, Addr 0x00, Data 0x31 0x32 0x33 0x34)
Key Challenges
TI flag race condition:Interrupt service routine's if(TI){ TI=0; }interfered with main loop's while(!TI)during consecutive Uart_SendBytecalls. Solved by disabling serial interrupt ES=0 during multi-byte transmission.
Timeout threshold tuning:1000ms proved too long for rapid command sequences; reduced to 200ms for better responsiveness.
Corresponding Real-World Scenarios 
This Practice	Industrial Context
AT24C02 stores 4-byte register	PLC holding register / RTU configuration EEPROM
UART SETcommand without password	Debug port without authentication (CVE-2019-10945 etc.)
Logic analyzer captures I2C bus	Non-invasive bus sniffing / forensic analysis
Offline EEPROM modification (planned)	Configuration tampering (similar to Stuxnet approach)
Next Steps
	Implement offline EEPROM modification using CH341A programmer
	Port to STM32 with hardware I2C and Modbus RTU protocol
	Add CRC checksum to prevent simple tampering (defense perspective)
