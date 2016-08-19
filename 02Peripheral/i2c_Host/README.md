##SDK Version : ESP8266_RTOS_SDK_V1.4.2_16_07_04
##Platform : ESP-LAUNCHER BOARD

##Purpose:
I2C host function test with MPU6050.

##Procedure:
1. Connect MPU6050 to ESP8266, PIN definition is in I2C_MASTER.h.
2. Enter path:/home/esp8266/Share, clone ESP8266 RTOS SDK to lubuntu environment by command: 

        git clone https://github.com/espressif/ESP8266_RTOS_SDK.git 
	   
3. Enter SDK folder:/home/esp8266/Share/ESP8266_RTOS_SDK, Copy example folder "i2c_Host" next to bin/ folder in the SDK folder. The SDK folder should have folders inside it like : bin, examples, third party...

4. If the SDK path is not updated in gen_misc.sh, right click the script and edit the path to bin folder and SDK folder. for the current SDK, the gen_mish.sh would have a path like:
       
		export SDK_PATH="/home/esp8266/Share/ESP8266_RTOS_SDK"
		export BIN_PATH="/home/esp8266/Share/ESP8266_RTOS_SDK/bin"
	   
5. Enter example folder, run ./gen_misc.sh, and follow below steps to finish the sample code compile:
	
		Option 1 will be automatically selected, 
		Option 2 > Enter 1. 
		Option 3 > Enter Default(Just Press enter)
		Option 4 > Enter Default(Just Press enter)
		Option 5 > Enter 5.
	   
6. "user1.2048.new.5.bin" should be found in "/home/esp8266/Share/ESP8266_RTOS_SDK/bin/upgrade", Flash the Binaries with ESP Flashing tool at the instructed Locations. Download bin files to ESP-LAUNCHER as below sittings.
		
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
UART0 port will output RAW values. Open Serial Monitor to verify.

##UART0 log@74880:

	start MPU6050stop MPU6050
		Acx :23445
		Acy :5671
		Acz :65535
		Tem :43213
		Gyx :32123
		Gyy :11121
		Gyz :31245

