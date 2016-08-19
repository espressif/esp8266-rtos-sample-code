##SDK Version : ESP8266_RTOS_SDK_V1.4.2_16_07_04
##Platform : ESP-LAUNCHER BOARD

##Purpose:
UART loopback test.

##Procedure:
1.Enter path:/home/esp8266/Share, clone ESP8266 RTOS SDK to lubuntu environment by command: 
       
		git clone https://github.com/espressif/ESP8266_RTOS_SDK.git 
	   
2.Enter SDK folder:/home/esp8266/Share/ESP8266_RTOS_SDK, Copy example folder "UART0" next to bin/ folder in the SDK folder. The SDK folder should have folders inside it like : bin, examples, third party...

3.If the SDK path is not updated in gen_misc.sh, right click the script and edit the path to bin folder and SDK folder. for the current SDK, the gen_mish.sh would have a path like:
       
		export SDK_PATH="/home/esp8266/Share/ESP8266_RTOS_SDK"
		export BIN_PATH="/home/esp8266/Share/ESP8266_RTOS_SDK/bin"
	   
4.Enter example folder, run ./gen_misc.sh, and follow below steps to finish the sample code compile:
	
		Option 1 will be automatically selected, 
		Option 2 > Enter 1. 
		Option 3 > Enter Default(Just Press enter)
		Option 4 > Enter Default(Just Press enter)
		Option 5 > Enter 5.
	   
5."user1.2048.new.5.bin" should be found in "/home/esp8266/Share/ESP8266_RTOS_SDK/bin/upgrade", Flash the Binaries with ESP Flashing tool at the instructed Locations. Download bin files to ESP-LAUNCHER as below sittings.
		
		Download address of each bin files:
		blank.bin				            0x1FE000
		esp_init_data_default.bin			0x1FC000
		boot_v1.5.bin					    0x00000
		user1.2048.new.5.bin			    0x01000
		
		Flash download tool settings:
		CrystalFreq: 26M
		SPI SPEED: 40MHz
		SPID MODE: QIO
		FLASH SIZE: 16Mbit-C1
			
##Result: 
Monitor uart0 by a serial terminal at 74880 Baud Rate. No Flow control enabled. 
Enter a string of different characters, and you will get an echo back.
Sample Code is written to trigger a UART Interrupt for every 10 characters sent.

##UART0 log@74880:
	when you enter "abcdefg" in serial port tool,the log will as follows:

	
		 ets Jan  8 2013,rst cause:1, boot mode:(3,2)

	load 0x40100000, len 1856, room 16 
	tail 0
	chksum 0x63
	load 0x3ffe8000, len 776, room 8 
	tail 0
	chksum 0x02
	load 0x3ffe8310, len 552, room 8 
	tail 0
	chksum 0x79
	csum 0x79

	2nd boot version : 1.5
	  SPI Speed      : 40MHz
	  SPI Mode       : QIO
	  SPI Flash Size & Map: 8Mbit(512KB+512KB)
	jump to run user1 @ 1000

	OS SDK ver: 1.4.0(c599790) compiled @ Mar  1 2016 17:25:17
	phy ver: 762, pp ver: 10.4

	THIS IS A UART LOOPBACK DEMO...
	uart_init_new
	UART CONFIG HERE..
	uart0_rx_intr_handler
	line   371  
	empty
	mode : softAP(1a:fe:34:ed:87:e3)
	dhcp server start:(ip:192.168.4.1,mask:255.255.255.0,gw:192.168.4.1)
	add if1
	bcn 100
	uart0_rx_intr_handler
	line   371  
	abcdefg



