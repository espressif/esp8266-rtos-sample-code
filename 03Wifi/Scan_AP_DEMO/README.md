##SDK Version : ESP8266_RTOS_SDK_V1.4.2_16_07_04
##Platform : ESP-LAUNCHER BOARD

##Purpose:
Start ESP8266 under station mode, and scan ap information around.

##Procedure:
1.Enter path:/home/esp8266/Share, clone ESP8266 RTOS SDK to lubuntu environment by command: 
       
		git clone https://github.com/espressif/ESP8266_RTOS_SDK.git 
	   
2.Enter SDK folder:/home/esp8266/Share/ESP8266_RTOS_SDK, Copy example folder "Scan_AP_DEMO" next to bin/ folder in the SDK folder. The SDK folder should have folders inside it like : bin, examples, third party...

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
UART0 will output ap information around.

##UART0 log@74880:
	
	f r0, now entering the scan AP test..... 
	scandone
	now doing the scan_done... 
	(4,"IOT_DEMO_TEST",-52,"a4:56:02:47:30:07",1)
	(4,"MESH_2_ED863A",-57,"1a:fe:34:ed:86:3a",1)
	(0,"TP-LINK_feedback",-60,"fc:d7:33:f8:6b:d0",1)
	(3,"wifi-11",-60,"94:b4:0f:c6:0c:e0",1)
	(0,"TP-LINK_FD",-50,"80:89:17:ce:eb:c6",1)
	(4,"MESH_2_ED8759",-64,"1a:fe:34:ed:87:59",1)
	(3,"MESH_BH_1_0A13FE",-60,"5e:cf:7f:0a:13:fe",1)
	(4,"MESH_2_14C642",-63,"5e:cf:7f:14:c6:42",1)
	(0,"ESP_14C562",-54,"5e:cf:7f:14:c5:62",1)
	(4,"MESH_3_ED869A",-70,"1a:fe:34:ed:86:9a",1)
	(4,"MESH_1_A48C60",-67,"1a:fe:34:a4:8c:60",1)
	(4,"WS860s",-60,"e8:cd:2d:2a:26:40",1)
	(0,"liu_test",-56,"90:8d:78:c9:0c:8e",1)
	(4,"MESH_3_ED8693",-68,"1a:fe:34:ed:86:93",1)
	(4,"wifi-1",-59,"c8:d7:19:d9:e8:22",1)
	(0,"ESP_00015D",-70,"62:01:94:00:01:5d",1)
	(3,"TP_LINK_WR740N",-78,"cc:34:29:89:eb:40",1)
	(0,"ESPTEST_360R",-43,"08:10:79:94:bc:d2",2)
	(4,"esp8266-test",-50,"20:76:93:27:91:7c",2)
	(3,"ROBOTWIFI",-53,"c8:3a:35:40:44:e0",3)
	(3,"ESP_WROOM",-67,"0c:72:2c:bf:ed:2e",3)
	(0,"EAP",-70,"02:24:bd:77:67:c2",1)
