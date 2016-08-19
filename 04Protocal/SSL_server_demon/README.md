##SDK Version : ESP8266_RTOS_SDK_V1.4.2_16_07_04
##Platform : ESP-LAUNCHER BAOARD

##Purpose:
SSL server demo by IE browser.

##Procedure:
1.Enter path:/home/esp8266/Share, clone ESP8266 RTOS SDK to lubuntu environment by command: 
       
		git clone https://github.com/espressif/esp8266-rtos-sample-code.git
	   
2.Enter SDK folder:/home/esp8266/Share/ESP8266_RTOS_SDK, Copy example folder "ssl_server_demo" next to SDK folder. The SDK folder should have folders inside it like : bin, examples, third party...and config AP SSID and PASSWORD in soft_ap.c.

	#define SOFT_AP_SSID "DEMO_AP"
	#define SOFT_AP_PASSWORD "12345678"

3.If the SDK path is not updated in gen_misc.sh, right click the script and edit the path to bin folder and SDK folder. for the current SDK, the gen_mish.sh would have a path like:
       
		export SDK_PATH="/home/esp8266/Share/ESP8266_RTOS_SDK"
		export BIN_PATH="/home/esp8266/Share/ESP8266_RTOS_SDK/bin"
	   
4.Enter example folder, run ./gen_misc.sh, and follow below steps to fininsh the sample code compile:
	
        Option 1 will be automatically selected, 
        Option 2 > Enter 1. 
        Option 3 > Enter Default(Just Press enter)
        Option 4 > Enter Default(Just Press enter)
        Option 5 > Enter 5.
	   
5."user1.2048.new.5.bin" should be found in "/home/esp8266/Share/ESP8266_RTOS_SDK/bin/upgrade", Flash the Binaries with ESP Flashing tool at the instructed Locations. Download bin files to ESP-LAUNCHER as below sittings.
		
		Download address of each bin files:
		blank.bin				            0x1FE000
		esp_init_data_default.bin           0x1FC000
		boot_v1.5.bin					    0x00000
		user1.2048.new.5.bin		        0x01000
		
		Flash download tool settings:
		CrystalFreq: 26M
		SPI SPEED: 40MHz
		SPID MODE: QIO
		FLASH SIZE: 16Mbit-C1
			
##Result:
On ESP8266 Dev Board, connect a serial terminal at 74880 Baud Rate, start your IE browser of microsoft. 
You should input the context of "https://192.168.17.128", the IP of your module may not be 192.168.17.128, you should input your module's IP
You may see that it shows the website is not able to be trusted, that you should select that "go on to visit it"You should wait for a moment until your see the "hello word" in your IE page

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
	阸?舗E挲ㄉn=醦hy ver: 762, pp ver: 10.4

	SDK version:1.4.0(c599790) 44808
	mode : sta(18:fe:34:ed:87:e3)
	add if0
	f r0, scandone
	state: 0 -> 2 (b0)
	state: 2 -> 3 (0)
	state: 3 -> 5 (10)
	add 0
	aid 5
	pm open phy_2,type:2 0 0
	cnt 

	connected with DEMO_AP, channel 11
	dhcp client start...
	ip:192.168.31.157,mask:255.255.255.0,gw:192.168.31.1
	server SSL context create ......OK
	server SSL context set fragment ......OK
	server SSL context set own certification......OK
	server SSL context set private key......OK
	server create socket ......OK
	server socket bind ......OK
	server socket listen ......OK
	server SSL create ......OK
	server socket accept client ......OK
	server SSL accept client ......OK
	server SSL read message ......result 0
	server SSL create ......OK
	server socket accept client ......OK
	server SSL accept client ......OK
	server SSL read message ......result 0
	server SSL create ......OK
	server socket accept client ......OK
	server SSL accept client ......OK
	server SSL read message ......result 0
	server SSL create ......OK
	server socket accept client ......OK
	server SSL accept client ......OK
	server SSL read message ......result 251
	server SSL create ......OK
	server socket accept client ......OK
	server SSL accept client ......OK
	server SSL read message ......


