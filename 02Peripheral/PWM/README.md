##SDK Version : ESP8266_RTOS_SDK_V1.4.2_16_07_04
##Platform : ESP-LAUNCHER BOARD

##Purpose:
PWM function test.

##Procedure:
1. Hardware configuration. Connect LED, R connect to GPIO12, G connect to GPIO13,B connect to GPIO14

2. Enter path:/home/esp8266/Share, clone ESP8266 RTOS SDK to lubuntu environment by command: 
       
		git clone https://github.com/espressif/ESP8266_RTOS_SDK.git 
	   
3.Enter SDK folder:/home/esp8266/Share/ESP8266_RTOS_SDK, Copy example folder "PMW" next to bin/ folder in the SDK folder. The SDK folder should have folders inside it like : bin, examples, third party...

4.If the SDK path is not updated in gen_misc.sh, right click the script and edit the path to bin folder and SDK folder. for the current SDK, the gen_mish.sh would have a path like:
       
		export SDK_PATH="/home/esp8266/Share/ESP8266_RTOS_SDK"
		export BIN_PATH="/home/esp8266/Share/ESP8266_RTOS_SDK/bin"
	   
5.Enter example folder, run ./gen_misc.sh, and follow below steps to finish the sample code compile:
	
		Option 1 will be automatically selected, 
		Option 2 > Enter 1. 
		Option 3 > Enter Default(Just Press enter)
		Option 4 > Enter Default(Just Press enter)
		Option 5 > Enter 5.
	   
6."user1.2048.new.5.bin" should be found in "/home/esp8266/Share/ESP8266_RTOS_SDK/bin/upgrade", Flash the Binaries with ESP Flashing tool at the instructed Locations. Download bin files to ESP-LAUNCHER as below sittings.
		
		Download address of each bin files:
		blank.bin				            0x1FE000
		esp_init_data_default.bin			0x1FC000
		boot_v1.5.bin					    0x00000
		user1.2048.new.5.bin                0x01000
		
		Flash download tool settings:
		CrystalFreq: 26M
		SPI SPEED: 40MHz
		SPID MODE: QIO
		FLASH SIZE: 16Mbit-C1
		
##Result:
The colors on the LED will change.

##UART0 log@74880:
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
	  SPI Flash Size & Map: 16Mbit(1024KB+1024KB)
	jump to run user1 @ 1000

	OS SDK ver: 1.4.0(c599790) compiled @ Mar  1 2016 17:25:17
	phy ver: 762, pp ver: 10.4

