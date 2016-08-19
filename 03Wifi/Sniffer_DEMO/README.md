##SDK Version : ESP8266_RTOS_SDK_V1.4.2_16_07_04
##Platform : ESP-LAUNCHER BOARD

##Purpose:
Sniffer mode test.

##Procedure:
1.Enter path:/home/esp8266/Share, clone ESP8266 RTOS SDK to lubuntu environment by command: 
       
		git clone https://github.com/espressif/ESP8266_RTOS_SDK.git 
	   
2.Enter SDK folder:/home/esp8266/Share/ESP8266_RTOS_SDK, Copy example folder "Sniffer_DEMO" next to bin/ folder in the SDK folder. The SDK folder should have folders inside it like : bin, examples, third party...

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
		user1.2048.new.5.bin		        0x01000
		
		Flash download tool settings:
		CrystalFreq: 26M
		SPI SPEED: 40MHz
		SPID MODE: QIO
		FLASH SIZE: 16Mbit-C1
		
##Result:
UART0 print as below after boot up.The UART will firstly print out all the SSID nearby, then it will continue to print out H2M9 with the length of different packages it can detect in the specific channel.

##UART0 log@74880:
	
	Sniffer testing mode ....: 1.4.0(c599790)
	f r0, wifi_station_scan ok
	scandone
	ssid wifi-1, channel 1, authmode 4, rssi -59
	ssid IOT_DEMO_TEST, channel 1, authmode 4, rssi -48
	ssid MESH_BH_1_0A13FE, channel 1, authmode 3, rssi -51
	ssid wifi-11, channel 1, authmode 3, rssi -50
	ssid TP-LINK_feedback, channel 1, authmode 0, rssi -63
	ssid MESH_2_14C642, channel 1, authmode 4, rssi -57
	ssid TP-LINK_FD, channel 1, authmode 0, rssi -48
	ssid liu_test, channel 1, authmode 0, rssi -61
	ssid ESP_ED8752, channel 1, authmode 0, rssi -61
	ssid MESH_3_ED8693, channel 1, authmode 4, rssi -69
	ssid ESP_00015D, channel 1, authmode 0, rssi -63
	ssid ESP_14C562, channel 1, authmode 0, rssi -52
	ssid MESH_1_A48C60, channel 1, authmode 4, rssi -68
	ssid MESH_2_ED8759, channel 1, authmode 4, rssi -66
	ssid MESH_2_ED863A, channel 1, authmode 4, rssi -71
	ssid esp8266-test, channel 2, authmode 4, rssi -43
	ssid ESPTEST_360R, channel 2, authmode 0, rssi -45
	sshmode 0, rssi -83
	current channel1 1 2615546
	H2M14
	H2M13
	H2M11

