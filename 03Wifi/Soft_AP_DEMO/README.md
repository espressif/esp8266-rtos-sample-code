##SDK Version : ESP8266_RTOS_SDK_V1.4.2_16_07_04
##Platform : ESP-LAUNCHER BOARD

##Purpose:
ESP8266 work under softap mode and configure softap ssid/password.

##Procedure:
1.Enter path:/home/esp8266/Share, clone ESP8266 RTOS SDK to lubuntu environment by command: 
       
		git clone https://github.com/espressif/ESP8266_RTOS_SDK.git 
	   
2.Enter SDK folder:/home/esp8266/Share/ESP8266_RTOS_SDK, Copy example folder "Soft_AP_DEMO" next to bin/ folder in the SDK folder. The SDK folder should have folders inside it like : bin, examples, third party...

3.You can configure softap ssid/password in soft_ap.c. And there is more setting in soft_AP_Init.

        #define SOFT_AP_SSID "DEMO_AP"
        #define SOFT_AP_PASSWORD "12345678"

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
		user1.2048.new.5.bin			    0x01000
		
		Flash download tool settings:
		CrystalFreq: 26M
		SPI SPEED: 40MHz
		SPID MODE: QIO
		FLASH SIZE: 16Mbit-C1
		
##Result:
Use a PC or smartphone to connect to ESP8266 softap, and uart0 will output station connected print.

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

	test new compile..
	mode : softAP(1a:fe:34:ed:87:e3)
	dhcp server start:(ip:192.168.4.1,mask:255.255.255.0,gw:192.168.4.1)
	add if1
	bcn 100
	test line 109test line 115bcn 0
	del if1
	usl
	sul 0 0
	dhcp server start:(ip:192.168.4.1,mask:255.255.255.0,gw:192.168.4.1)
	add if1
	bcn 100
	test line 126test line 135test line 139test line 149test line 155test line 157test line 160add 1
	aid 1
	station: 94:fe:22:49:e6:f9 join, AID = 1

