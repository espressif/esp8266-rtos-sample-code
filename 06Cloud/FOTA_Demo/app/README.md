##SDK Version : ESP8266_RTOS_SDK_V1.4.2_16_07_04
##Platform : ESP-LAUNCHER BAOARD

##Operation Steps:

1. Enter path:/home/esp8266/Share, clone ESP8266 RTOS SDK to lubuntu environment by command: 
       
		git clone https://github.com/espressif/ESP8266_RTOS_SDK.git 
	   
2. Enter SDK folder:/home/esp8266/Share/ESP8266_RTOS_SDK, Copy example folder "FOTA_Demo" next to bin/ folder in the SDK folder. The SDK folder should have folders inside it like : bin, examples, third party...,and inpress your own WIFI SSID and key to the defination "SSID" , "PASSWORD", "REMOTE SERVER IP" and "PORT"......int the file "ota_config.h"

		for example:
		#define DEMO_SERVER "192.168.17.130"
		#define DEMO_SERVER_PORT 80
		#define DEMO_WIFI_SSID     "test"
		#define DEMO_WIFI_PASSWORD  "espressif"

3. If the SDK path is not updated in gen_misc.sh, right click the script and edit the path to bin folder and SDK folder. for the current SDK, the gen_mish.sh would have a path like:
       
		export SDK_PATH="/home/esp8266/Share/ESP8266_RTOS_SDK"
		export BIN_PATH="/home/esp8266/Share/ESP8266_RTOS_SDK/bin"
	   
4. Enter example folder, run ./gen_misc.sh, and follow below steps to fininsh the sample code compile:
	
		Option 1 will be automatically selected, 
		Option 2 > Enter 1. 
		Option 3 > Enter Default(Just Press enter)
		Option 4 > Enter Default(Just Press enter)
		Option 5 > Enter 5.
	   
5. "user1.2048.new.5.bin" should be found in "/home/esp8266/Share/ESP8266_RTOS_SDK/bin/upgrade", Flash the Binaries with ESP Flashing tool at the instructed Locations. Download bin files to ESP-LAUNCHER as below sittings.
		
		Download address of each bin files:
		blank.bin				            0x1FE000
		esp_init_data_default.bin			    0x1FC000
		boot_v1.5.bin					    0x00000
		user1.2048.new.5.bin			            0x01000
		
		Flash download tool settings:
		CrystalFreq: 26M
		SPI SPEED: 40MHz
		SPID MODE: QIO
		FLASH SIZE: 16Mbit-C11

6. put "user1.2048.new.5.bin" and "user2.2048.new.5.bin" in remote server and rename them with "user1.bin" ¡¢"user2.bin".you can choose a Webserver ,for example Mini-Webserver software.

##FOR VERIFY: 
UART0 print as below after boot up.

	mode : sta(18:fe:34:97:f3:cd)
	add if0
	f r0, scandone
	state: 0 -> 2 (b0)
	state: 2 -> 3 (0)
	state: 3 -> 5 (10)
	add 0
	aid 14
	pm open phy_2,type:2 0 0
	cnt 

	connected with test, channel 3
	dhcp client start...
	ip:192.168.17.131,mask:255.255.255.0,gw:192.168.17.1
	sta got ip , creat fota task
	Hello, welcome to client!
	socket ok!
	connect ok!
	GET /user2.bin HTTP/1.0
	Host: "192.168.17.130":80
	Connection: keep-alive
	Cache-Control: no-cache
	User-Agent: Mozilla/5.0 (Windows NT 5.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/30.0.1599.101 Safari/537.36 
	Accept: */*
	Accept-Encoding: gzip,deflate,sdch
	Accept-Language: zh-CN,zh;q=0.8

	send success
	upgrade file download start.
	flash erase over
	sumlength = 289716
	totallen = 1460
	...............
	...............
	totallen = 287045
	totallen = 288485
	totallen = 289716
	upgrade file download finished.
	fw_bin_sec 257 sumlength 289716
	img_crc = 2137943150
	flash_crc = 2137943150
	go to ota recycle
	reboot to use2
	state: 5 -> 0 (0)
	rm 0
	pm close 7 0 0/30543311
	del if0
	usl
	sul 0 0

####When you see reboot to use2 and hard reset log is running user2.bin ,you are success.

