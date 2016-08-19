##SDK Version : ESP8266_RTOS_SDK_V1.4.2_16_07_04
##Platform : ESP-LAUNCHER BOARD

##Purpose:
Connect to specific router test.

##Procedure:
1.Enter path:/home/esp8266/Share, clone ESP8266 RTOS SDK to lubuntu environment by command: 
       
		git clone https://github.com/espressif/ESP8266_RTOS_SDK.git 
	   
2.Enter SDK folder:/home/esp8266/Share/ESP8266_RTOS_SDK, Copy example folder "Conn_AP_DEMO" next to bin/ folder in the SDK folder. The SDK folder should have folders inside it like : bin, examples, third party...

3.Configure below setting to the router ssid/password you need to connect to.

        #define DEMO_AP_SSID      "WT_TEST"
        #define DEMO_AP_PASSWORD "1234567abc"

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
		esp_init_data_default.bin           0x1FC000
		boot_v1.5.bin					    0x00000
		user1.2048.new.5.bin                0x01000
		
		Flash download tool settings:
		CrystalFreq: 26M
		SPI SPEED: 40MHz
		SPID MODE: QIO
		FLASH SIZE: 16Mbit-C1
		
##Result:
ESP8266 will connect to the router you configured.

##UART0 log@74880:

	scandone
	state: 0 -> 2 (b0)
	state: 2 -> 3 (0)
	state: 3 -> 5 (10)
	add 0
	aid 9
	cnt 

	connected with WT_TEST, channel 11
	dhcp client start...


	When you see connect to ssid xxx, channel xxx, then connecting to AP is successful.
