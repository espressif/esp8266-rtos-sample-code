##SDK Version : ESP8266_RTOS_SDK_V1.4.2_16_07_04
##Platform : ESP-LAUNCHER BOARD

##Purpose:
ADC read test with TOUT pin.

##Procedure:
1.Enter path:/home/esp8266/Share, clone ESP8266 RTOS SDK to lubuntu environment by command: 
       
		git clone https://github.com/espressif/ESP8266_RTOS_SDK.git 
	   
2.Enter SDK folder:/home/esp8266/Share/ESP8266_RTOS_SDK, Copy example folder "AnalogReadSerial" next to SDK folder. The SDK folder should have folders inside it like : bin, examples, third party...

3.If the SDK path is not updated in gen_misc.sh, right click the script and edit the path to bin folder and SDK folder. for the current SDK, the gen_mish.sh would have a path like:
       
		export SDK_PATH="/home/esp8266/Share/ESP8266_RTOS_SDK"
		export BIN_PATH="/home/esp8266/Share/ESP8266_RTOS_SDK/bin"
	   
4.Enter example folder, run ./gen_misc.sh, and follow below steps to finish the sample code compile:
	
		Option 1 will be automatically selected, 
		Option 2 > Enter 1. 
		Option 3 > Enter Default(Just Press enter)
		Option 4 > Enter Default(Just Press enter)
		Option 5 > Enter 5.
	   
5.In the Flash tool, go to RF Config tab and Change the ADC To TOUT_EN. This will change the 107th byte to 33 in the table below. Then generate the NEW esp_init_data_default.bin and replace the standard esp_init_data_default.bin in the sdk/bin folder.  

6."user1.2048.new.5.bin" should be found in "/home/esp8266/Share/ESP8266_RTOS_SDK/bin/upgrade", Flash the Binaries with ESP Flashing tool at the instructed Locations. Download bin files to ESP-LAUNCHER as below sittings.
		
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
Connect a potentiometer to the TOUT Pin of 8266. Make sure the input voltage is 0~1V.The Values will be displayed on uart0 output. 

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
	  SPI Flash Size & Map: 8Mbit(512KB+512KB)
	jump to run user1 @ 1000

	OS SDK ver: 1.4.0(c599790) compiled @ Mar  1 2016 17:25:17
	phy ver: 762, pp ver: 10.4

	SDK version:1.4.0(c599790)
	ADC TEST27
	27
	26
	25
	25
	22
	22
	21
	21
	20
	20
	20
	19
	19
	19
	19
	18
	18
	18
	18
	18
	18
	18
	18
	17
	17
	17
	17
	17
	17
	17
	17
	17
	17
	17
	17
	17
	17
	17



