# Overview
HSPI_Slave demo is based on the SPI communication between two ESP8266. The communication test followed the steps below.

- Master sends 32-byte data to slave.
- Master receive data from slave.
- Master read data from the status register of the slave.
- Master writes data to the status register of the slave.

The slave will receive interrupts in order from SPI_SLV_WR_BUF_DONE,
SPI_SLV_RD_BUF_DONE, SPI_SLV_RD_STA_DONE, SPI_SLV_WR_STA_DONE.

# Hardware Introduction
HSPI_Slave demo use two **ESP8266 DEMO BOARD**,The master and the slave are connected via HSPI.

- GPIO14 is SPI Clock
- GPIO15 is SPI CS pin
- GPIO12 is SPI MISO
- GPIO13 is SPI MOSI

*Note: If you also are using two ESP8266 DEMO BOARD, please remove pin C8(top left corner
) and pin R58(bottom right corner),GPIO13 is used for buttons(C8), GPIO14 is used for Infrared(R58).*


# Compiling and flashing the project

1.Enter path:/home/esp8266/Share, clone ESP8266 RTOS SDK to lubuntu environment by command: 
       
		git clone https://github.com/espressif/ESP8266_RTOS_SDK.git 
	   
2.Enter SDK folder:/home/esp8266/Share/ESP8266_RTOS_SDK, Copy example folder "HSPI_Slave" next to bin/ folder in the SDK folder. The SDK folder should have folders inside it like : bin, examples, third party...

3. If the SDK path is not updated in gen_misc.sh, right click the script and edit the path to bin folder and SDK folder. for the current SDK, the gen_mish.sh would have a path like:
       
		export SDK_PATH="/home/esp8266/Share/ESP8266_RTOS_SDK"
		export BIN_PATH="/home/esp8266/Share/ESP8266_RTOS_SDK/bin"
	   
4. Enter example folder, run ./gen_misc.sh, and follow below steps to finish the sample code compile:
	
		Option 1 > Enter y.
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

6. For SPI master demo, you only need rename the example folder "HSPI_Slave" to "HSPI_Master", edit the file user_main.c, change 1 to 0 in line 252, and then repeat step 4 to 5.
