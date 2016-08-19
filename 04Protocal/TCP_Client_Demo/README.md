##SDK Version : ESP8266_RTOS_SDK_V1.4.2_16_07_04
##Platform : ESP-LAUNCHER BOARD

##Purpose:
TCP client test.

##Procedure:
1.Enter path:/home/esp8266/Share, clone ESP8266 RTOS SDK to lubuntu environment by command: 
       
		git clone https://github.com/espressif/ESP8266_RTOS_SDK.git 
	   
2.Enter SDK folder:/home/esp8266/Share/ESP8266_RTOS_SDK, Copy example folder "TCP_Client_Demo" next to SDK folder. The SDK folder should have folders inside it like : bin, examples, third party...

3.If the SDK path is not updated in gen_misc.sh, right click the script and edit the path to bin folder and SDK folder. for the current SDK, the gen_mish.sh would have a path like:
       
		export SDK_PATH="/home/esp8266/Share/ESP8266_RTOS_SDK"
		export BIN_PATH="/home/esp8266/Share/ESP8266_RTOS_SDK/bin"

4.Configure the router information you want to connect in tcp_client.c

        #define DEMO_AP_SSID      "WT_TEST"
        #define DEMO_AP_PASSWORD "1234567abc"

    Configure TCP server information you want to connect in tcp_client.h

        const uint8 tcp_server_ip[4]={192,168,1,100};
        #define TCP_SERVER_REMOTE_PORT (7007)
	   
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
Please make sure that ESP8266 and TCP server under same gateway. Connect to the right router. Open any TCP Server Tool, configure the TCP to connect to port 7007.

##UART0 log@74880:

	If you connect tcp server succesffully, then you will see UART0 output as below. 

	"Hello!This is a tcp client test\n"
