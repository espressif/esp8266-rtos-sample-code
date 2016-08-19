##SDK Version : ESP8266_RTOS_SDK_V1.4.2_16_07_04
##Platform : ESP-LAUNCHER BAOARD

##Purpose:
Websocket demo to iot.espressif.cn.

##Procedure:
1. Enter path:/home/esp8266/Share, clone ESP8266 RTOS SDK to lubuntu environment by command: 
       
		git clone https://github.com/espressif/ESP8266_RTOS_SDK.git 

2. Enter SDK folder:/home/esp8266/Share/ESP8266_RTOS_SDK, Copy example folder "websockt_demo" next to SDK folder. The SDK folder should have folders inside it like : bin, examples, third party...and inpress your own WIFI SSID and key to the defination "SSID" and "PASSWORD", int the file "SDK\websocket_demon\user\user_main.c"
		
		sprintf(sta_config.ssid, "Smart1ap");
		sprintf(sta_config.password, "espressif0-1");
	

3. If the SDK path is not updated in gen_misc.sh, right click the script and edit the path to bin folder and SDK folder. for the current SDK, the gen_mish.sh would have a path like:
       
		export SDK_PATH="/home/esp8266/Share/ESP8266_RTOS_SDK"
		export BIN_PATH="/home/esp8266/Share/ESP8266_RTOS_SDK/bin"
	   
4. Enter example folder, run ./gen_misc.sh, and follow below steps to fininsh the sample code compile:
	
		Option 1 > will be automatically selected,. 
		Option 2 > Enter 1. 
		Option 3 > Enter Default(Just Press enter)
		Option 4 > Enter Default(Just Press enter)
		Option 5 > Enter 5.
	   
5. "user1.2048.new.5.bin" should be found in "/home/esp8266/Share/ESP8266_RTOS_SDK/bin/upgrade", Flash the Binaries with ESP Flashing tool at the instructed Locations. Download bin files to ESP-LAUNCHER as below sittings.
		
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
Websocket communication to iot.espressif.cn, and will get response from the web.

##UART0 log@74880:

	On ESP8266 Dev Board,if the log as fellow,success
	 
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
	êq
	Ð×*Åîjí¨Ín=phy ver: 762, pp ver: 10.4

	SDK version:1.4.0(c599790)
	mode : sta(5c:cf:7f:14:c7:45)
	add if0
	f r0, 
	scandone
	state: 0 -> 2 (b0)
	state: 2 -> 3 (0)
	state: 3 -> 5 (10)
	add 0
	aid 4
	pm open phy_2,ty
	pe:2 0 0
	cnt 

	connected with Smart1ap, channel 11
	dhcp client start...
	ip:19
	2.168.31.181,mask:255.255.255.0,gw:192.168.31.1
	create a TLS connection
	Received: {"status": 403, "result": "failed", "message": "not valid key, Authorization: token AUTH-TOKEN"}

	Receive
	d: {"status": 200, "epoch": 1473413768, "message": "ping success", "datetime": "2016-09-09 17:36:08"}

	Received: {"status": 200, "epoch": 1473413768, "message": "ping success", "datetime": "2016-09-09 17:36:08"}

	Received: {"status": 200, "epoch": 1473413769, "message": "ping success", "datetime": "2016-09-09 17:36:09"}

	Rec
	eived: {"status": 200, "epoch": 1473413769, "message": "ping success", "datetime": "2016-09-09 17:36:09"}

	Received: {"status": 200, "epoch": 1473413769, "message": "ping success", "datetime": "2016-09-09 17:36:09"}

	Received: {"status": 200, "epoch": 1473413769, "message": "ping success", "datetime": "2016-09-09 17:36:09"}

	Received: {"status": 200, "epoch": 1473413769, "message": "ping success", "datetime": "2016-09-09 17:36:09"}

	Received: {
	"status": 200, "epoch": 1473413770, "message": "ping success", "datetime": "2016-09-09 17:36:10"}

	Received: {"status": 200, "epoch": 1473413770, "message": "ping success", "datetime": "2016-09-09 17:36:10"}

	Received: {"status": 200, "epoch": 1473413770, "message": "ping success", "datetime": "2016-09-09 17:36:10"}

	Recei
	ved: {"status": 200, "epoch": 1473413770, "message": "ping success", "datetime": "2016-09-09 17:36:10"}

	Received: {"status": 200, "epoch": 1473413770, "message": "ping success", "datetime": "2016-09-09 17:36:10"}

	Received: {"status": 200, "epoch": 1473413771, "message": "ping success", "datetime": "2016-09-09 17:36:11"}

	R
	eceived: {"status": 200, "epoch": 1473413771, "message": "ping success", "datetime": "2016-09-09 17:36:11"}


