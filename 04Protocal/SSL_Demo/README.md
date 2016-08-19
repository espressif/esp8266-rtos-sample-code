##SDK Version : ESP8266_RTOS_SDK_V1.4.2_16_07_04
##Platform : ESP-LAUNCHER BOARD

##Purpose:
SSL demo to connect to www.baidu.com

##Procedure:
1.Enter path:/home/esp8266/Share, clone ESP8266 RTOS SDK to lubuntu environment by command: 
       
		git clone https://github.com/espressif/ESP8266_RTOS_SDK.git 
	   
2.Enter SDK folder:/home/esp8266/Share/ESP8266_RTOS_SDK, Copy example folder "app" next to SDK folder; copy folder "openssl" to include/; copy "libmbedtls.a" and "libopenssl.a" to lib/. The SDK folder should have folders inside it like : bin, examples, third party... 

    Configure router information in user_config.h
        #define SSID "WT_TEST"
        #define PASSWORD "1234567abc"

	If you want to test the openSSL client demo: you should use the defination "#define DEMO_CLIENT" int the file "ESP8266_RTOS_SDK\openssl_demo\programs\openssl_demo.c". 
	   
3 Enter example folder, run ./gen_misc.sh, and follow below steps to finish the sample code compile:
	
        Option 1 will be automatically selected, 
        Option 2 > Enter 1. 
        Option 3 > Enter Default(Just Press enter)
        Option 4 > Enter Default(Just Press enter)
        Option 5 > Enter 5.
	   
4."user1.2048.new.5.bin" should be found in "/home/esp8266/Share/ESP8266_RTOS_SDK/bin/upgrade", Flash the Binaries with ESP Flashing tool at the instructed Locations. Download bin files to ESP-LAUNCHER as below sittings.

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
For openSSL client demo, you can see it will download the "www.baidu.com" main page and print the context.

##UART0 log@74880:


	 
	
