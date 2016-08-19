##SDK Version : ESP8266_RTOS_SDK_V1.4.2_16_07_04
##Platform : ESP-LAUNCHER BAOARD

##Operation Steps:

1.Enter path:/home/esp8266/Share, clone ESP8266 RTOS SDK to lubuntu environment by command: 
       
		git clone https://github.com/espressif/esp8266-rtos-sample-code.git
	   
2.Enter SDK folder:/home/esp8266/Share/ESP8266_RTOS_SDK, Copy example folder "app" next to bin/ folder in the SDK folder. The SDK folder should have folders inside it like : bin, examples, third party...copy ./include/mebedtls.rar to SDK/include,copy ./third_part/esp_iot_sdk_v1.3.0_gizwits.zip to SDK/third_part,copy ./lib/libmbedls.a to SDK/lib,then uncompress mebedtls.rar and config SSID and esp_iot_sdk_v1.3.0_gizwits.zip ,PASSWORD
			
		for example:
		#define SSID "ASUS_WAC"
		#define PASSWORD "12345678"

3.If the SDK path is not updated in gen_misc.sh, right click the script and edit the path to bin folder and SDK folder. for the current SDK, the gen_mish.sh would have a path like:
       
		export SDK_PATH="/home/esp8266/Share/ESP8266_RTOS_SDK"
		export BIN_PATH="/home/esp8266/Share/ESP8266_RTOS_SDK/bin"
	   
4.Enter example folder, run ./gen_misc.sh, and follow below steps to fininsh the sample code compile:
	
		Option 1 > Enter Y/y, 
		Option 2 > Enter 1. 
		Option 3 > Enter Default(Just Press enter)
		Option 4 > Enter Default(Just Press enter)
		Option 5 > Enter 5.
	   
5."user1.2048.new.5.bin" should be found in "/home/esp8266/Share/ESP8266_RTOS_SDK/bin/upgrade", Flash the Binaries with ESP Flashing tool at the instructed Locations. Download bin files to ESP-LAUNCHER as below sittings.
		
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
			
##FOR VERIFY: 
	On ESP8266 Dev Board,if current log as bellow,success.
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

	OS SDK ver: 1.4.0(c599790) compiled @ Feb 26 2016 11:08:14
	阸?舗E戍ㄍn-醦hy ver: 762, pp ver: 10.4

	SDK version:1.4.0(c599790) 44112
	mode : sta(5c:cf:7f:14:c7:45)
	add if0
	f r0, scandone
	state: 0 -> 2 (b0)
	state: 2 -> 3 (0)
	state: 3 -> 5 (10)
	add 0
	aid 5
	pm open phy_2,type:2 0 0
	cnt 

	connected with Xiaomi_CF8, channel 11
	dhcp client start...
	ip:192.168.31.181,mask:255.255.255.0,gw:192.168.31.1
	sta got ip , creat task 41072
	free_heap 36888

	  . Seeding the random number generator... ok
	  . Loading the client cert. and key... ok (0 skipped)
	  . Connecting to tcp/iot.espressif.cn/443... ok
	  . Setting up the SSL/TLS structure... ok 31792
	  . Performing the SSL/TLS handshake... ok
	  . Verifying peer X.509 certificate... ok
	  > Write to server: 18 bytes written

	GET / HTTP/1.0

	  < Read from server: 255 bytes read

	HTTP/1.1 200 OK
	Server: nginx/1.6.2
	Date: Tue, 13 Sep 2016 10:02:50 GMT
	Content-Type: text/html
	Content-Length: 4056
	Last-Modified: Sat, 20 Aug 2016 10:07:42 GMT
	Connection: close
	ETag: "57b82bee-fd8"
	Expires: Tue, 13 Sep 2016 10:02:49 GMT
	Cache- 255 bytes read

	Control: no-cache
	Accept-Ranges: bytes

	<!DOCTYPE html>
	<html lang="zh-Hans" ng-app="iotApp">
	  <head>
		<meta charset="utf-8">
		<meta property="qc:admins" content="25312773246530253316636" />
		<meta http-equiv="X-UA-Compatible" content="IE=edg 255 bytes read

	e">
		<meta name="viewport" content="width=device-width, initial-scale=1">
		<meta name="description" content="a Bucket of Internet Of Things">
		<meta name="author" content="cloudzhou">
		<link rel="icon" href="https://espressif.com/sites/all/the 255 bytes read

	mes/espressif/favicon.ico" type="image/x-icon">

		<title>{{ title }} 路 IotBucket</title>

		<link href="/static/css/bootstrap.min.css" rel="stylesheet">
		<link href="/static/css/app.css" rel="stylesheet">

		<script src="/static/js/angular.min. 4 bytes read

	js"> 255 bytes read

	</script>
		<script src="/static/js/angular-resource.min.js"></script>
		<script src="/static/js/angular-route.min.js"></script>
		<script src="/static/js/angular-cookies.min.js"></script>
		<script src="/static/js/angular-sanitize.min.js"></scrip 255 bytes read

	t>
		<script src="/static/js/ngStorage.min.js"></script>
		<script src="/static/js/jquery.min.js"></script>
		<script src="/static/js/bootstrap.min.js"></script>
		<script src="/static/js/moment.min.js"></script>
		<script src="/static/js/moment 255 bytes read

	-zh-cn.js"></script>
		<script src="/static/js/moment-zh-tw.js"></script>
		<script src="/static/js/qrcode.min.js"></script>

		<script src="/static/js/highcharts.js"></script>
		<script src="/static/js/exporting.js"></script>

		<script src="/s 255 bytes read

	tatic/js/const.js"></script>
		<script src="/static/js/common.js"></script>
		<script src="/static/js/app.js"></script>
		<script src="/static/js/controllers.js"></script>
		<script src="/static/js/directives.js"></script>

		<!--script src="/st 4 bytes read

	atic 255 bytes read

	/js/angular-animate.min.js"></script>
		<script src="/static/js/angular-loader.min.js"></script>
		<script src="/static/js/angular-touch.min.js"></script-->
	  </head>

	  <body>
		<div id="header-wrapper" ng-controller="userCtrl">
		  <div id="head 255 bytes read

	er" class="container">
			<ul class="nav nav-pills pull-right">
			  <li ng-if="user != null && user.unread_message_count > 0"><a href="#/user/messages/">{{'message'|xlat}} <span class="label label-danger"> {{user.unread_message_count}} </span>< 255 bytes read

	/a></li>
			  <li ng-if="user != null"><a href="#/devices/">{{'device-develop'|xlat}}</a></li>
			  <li ng-if="user != null"><a href="#/products/">{{'product-manage'|xlat}}</a></li>
			  <li class="dropdown">
				<a href="javascript 255 bytes read

	:" class="dropdown-toggle" data-toggle="dropdown"><span class="glyphicon glyphicon-th"></span> {{'start'|xlat}} <b class="caret"></b></a>
				<ul class="dropdown-menu">
				  <li><a href="#/api/">{{'api-docs'|xlat}}</a></li>
				   4 bytes read

	<li  255 bytes read

	class="divider"></li>
				  <li><a href="#/help/">{{'help'|xlat}}</a></li>
				</ul>
			  </li>
			  <li class="dropdown" ng-if="user != null">
				<a href="javascript:" class="dropdown-toggle" data-toggle="dropdown"><spa 255 bytes read

	n class="glyphicon glyphicon-user"></span> {{ user.username }} <b class="caret"></b></a>
				<ul class="dropdown-menu">
				  <li><a href="#/user/devices/">{{'my-devices'|xlat}}</a></li>
				  <li><a href="#/user/messages/">{{'my-m 255 bytes read

	essages'|xlat}} <span ng-if="user.unread_message_count > 0" class="label label-danger"> {{user.unread_message_count}} </span></a></li>
				  <li><a href="#/settings/">{{'settings'|xlat}}</a></li>
				  <li class="divider"></li>
				255 bytes read

	   <li><a ng-click="logout()" href="#/logout/">{{'logout'|xlat}}</a></li>
				</ul>
			  </li>
			  <li ng-if="user == null"><a href="#/join/">{{'join'|xlat}}</a></li>
			  <li ng-if="user == null"><a href="#/login/">{{'login'|xlat} 4 bytes read

	}</a 255 bytes read

	></li>
			</ul>
			<h2 class="logo"><a href="/"><strong>Iot</strong>Bucket</a></h2>
		  </div>
		</div>

		<div id="main-wrapper">
		  <div id="main" class="container">
			<div ng-view></div>
		  </div>
		</div>

	  </body>
	</htm 3 bytes read

	l>
	Last error was: -30848 - 

