##SDK Version : ESP8266_RTOS_SDK_V1.4.2_16_07_04
##Platform : ESP-LAUNCHER BAOARD

##Purpose:
JSON application example.

##Procedure:
1.Enter path:/home/esp8266/Share, clone ESP8266 RTOS SDK to lubuntu environment by command: 
       
		git clone https://github.com/espressif/ESP8266_RTOS_SDK.git
	   
2.Enter SDK folder:/home/esp8266/Share/ESP8266_RTOS_SDK, Copy example folder "json_demo" next to bin/ folder in the SDK folder. The SDK folder should have folders inside it like : bin, examples, third party...with the lib - 

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
		esp_init_data_default.bin			0x1FC000
		boot_v1.5.bin					    0x00000
		user1.2048.new.5.bin                0x01000
		
		Flash download tool settings:
		CrystalFreq: 26M
		SPI SPEED: 40MHz
		SPID MODE: QIO
		FLASH SIZE: 16Mbit-C1
			
##Result:
Parse JSON textblock and rebuild object, and create a bunch of objects as demonstration. 

##UART0 log@74880:
		
	 ets Jan  8 2013,rst cause:1, boot mode:(3,
	2)

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
	  SPI Flash Size & Map: 16Mbit(1024KB+1024KB)
	jump to run user1 @ 1000

	OS SDK ver: 1.4.0(c599790) compiled @ Mar  1 2016 17:25:17
	phy ver: 762, pp ver: 10.4

	SDK version:1.4.0(c599790)
	mode : sta(5c:cf:7f:14:c7:45)
	add if0
	{
		"name":	"Jack (\"Bee\") Nimble",
		"format":	{
			"type":	"rect",
			"width":	1920,
			"height":	1080,
			"interlace":	false,
			"frame rate":	24
		}
	}
	["Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"]
	[[0, -1, 0], [1, 0, 0], [0, 0, 1]]
	{
		"Image":	{
			"Width":	800,
			"Height":	600,
			"Title":	"View from 15th Floor",
			"Thumbnail":	{
				"Url":	"http:/*www.example.com/image/481989943",
				"Height":	125,
				"Width":	"100"
			},
			"IDs":	[116, 943, 234, 38793]
		}
	}
	[{
			"precision":	"zip",
			"Latitude":	37.766800,
			"Longitude":	-122.395900,
			"Address":	"",
			"City":	"SAN FRANCISCO",
			"State":	"CA",
			"Zip":	"94107",
			"Country":	"US"
		}, {
			"precision":	"zip",
			"Latitude":	37.371991,
			"Longitude":	-122.026020,
			"Address":	"",
			"City":	"SUNNYVALE",
			"State":	"CA",
			"Zip":	"94085",
			"Country":	"US"
		}]
	Error before: [<!DOCTYPE html><html>
	<head>
	  <meta name="viewport" content="width=device-width, initial-scale=1">
	  <style type="text/css">
		html, body, iframe { margin: 0; padding: 0; height: 100%; }
		iframe { display: block; width: 100%; border: none; }
	  </style>
	<title>Application Error</title>
	</head>
	<body>
	  <iframe src=    <p>Application Error</p>
	  </iframe>
	</body>
	</html>
	]
	{
		"name":	"Jack (\"Bee\") Nimble",
		"format":	{
			"type":	"rect",
			"width":	1920,
			"height":	1080,
			"interlace":	false,
			"frame rate":	24
		}
	}
	["Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"]
	[[0, -1, 0], [1, 0, 0], [0, 0, 1]]
	{
		"Image":	{
			"Width":	800,
			"Height":	600,
			"Title":	"View from 15th Floor",
			"Thumbnail":	{
				"Url":	"http:/*www.example.com/image/481989943",
				"Height":	125,
				"Width":	"100"
			},
			"IDs":	[116, 943, 234, 38793]
		}
	}
	[{
			"precision":	"zip",
			"Latitude":	37.766800,
			"Longitude":	-122.395900,
			"Address":	"",
			"City":	"SAN FRANCISCO",
			"State":	"CA",
			"Zip":	"94107",
			"Country":	"US"
		}, {
			"precision":	"zip",
			"Latitude":	37.371991,
			"Longitude":	-122.026000,
			"Address":	"",
			"City":	"SUNNYVALE",
			"State":	"CA",
			"Zip":	"94085",
			"Country":	"US"
		}]
	{
		"number":	inf
	}
	json_task
	json_task
	............
	............
