##SDK Version : ESP8266_RTOS_SDK_V1.4.2_16_07_04
##Platform : ESP-LAUNCHER BAOARD

##Purpose:
Loop back test of multicast.

##Procedure:
1.Enter path:/home/esp8266/Share, clone ESP8266 RTOS SDK to lubuntu environment by command: 
       
		git clone https://github.com/espressif/ESP8266_RTOS_SDK.git
	   
2.Enter SDK folder:/home/esp8266/Share/ESP8266_RTOS_SDK, Copy example folder "Multicast_Demo" next to SDK folder. The SDK folder should have folders inside it like : bin, examples, third party...

3.Configure router and multicase ip/port information in multicast_config.h

        #define DEMO_WIFI_SSID      "test"
        #define DEMO_WIFI_PASSWORD  "espressif"
        #define MSGBUFSIZE          1024

        #define HELLO_PORT 1887                //multicast port
        #define HELLO_GROUP "239.0.18.87"      //multicast ip

        #define SEND_MODE      1              //1: enable send task.0:disable send task
        #define RECV_MODE      1              //1: enable recv task,0:disable recv task

4.If the SDK path is not updated in gen_misc.sh, right click the script and edit the path to bin folder and SDK folder. for the current SDK, the gen_mish.sh would have a path like:
       
		export SDK_PATH="/home/esp8266/Share/ESP8266_RTOS_SDK"
		export BIN_PATH="/home/esp8266/Share/ESP8266_RTOS_SDK/bin"
	   
5.Enter example folder, run ./gen_misc.sh, and follow below steps to fininsh the sample code compile:
	
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
		user1.2048.new.5.bin		        0x01000
		
		Flash download tool settings:
		CrystalFreq: 26M
		SPI SPEED: 40MHz
		SPID MODE: QIO
		FLASH SIZE: 16Mbit-C1
			
##Result:
ESP8266 will receive/print multicast which send by ESP8266 itself.

##UART0 log@74880:

	SDK version:1.4.0(c599790)
	mode : softAP(1a:fe:34:97:f3:cd)
	dhcp server start:(ip:192.168.4.1,mask:255.255.255.0,gw:192.168.4.1)
	add if1
	bcn 100
	bcn 0
	del if1
	usl
	sul 0 0
	mode : sta(18:fe:34:97:f3:cd)
	add if0
	f r0, scandone
	state: 0 -> 2 (b0)
	state: 2 -> 3 (0)
	state: 3 -> 5 (10)
	add 0
	aid 10
	pm open phy_2,type:2 0 0
	cnt 

	connected with test, channel 3
	dhcp client start...
	ip:192.168.17.131,mask:255.255.255.0,gw:192.168.17.1
	free heap size 47520 line 137 
	recv massage:
	Hello, World!
	recv massage:
	Hello, World!
	recv massage:
	Hello, World!
	recv massage:
	Hello, World!
	recv massage:
	Hello, World!
	recv massage:
	Hello, World!
	recv massage:

