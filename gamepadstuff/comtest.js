var Gpio=require('onoff').Gpio;
var los=new Gpio(21,'out');
var selection=new Gpio(4,'out');
var enable1=new Gpio(17,'out');
var enable2=new Gpio(18,'out');
var flashlight=new Gpio(20,'out');

var app = require('express')();
var http = require('http').Server(app);
var io = require('socket.io')(http);
var serialport = require("serialport");
var SerialPort = serialport.SerialPort;
var serialPort = new SerialPort("/dev/ttyACM0", {
  baudrate: 9600,
  parser: serialport.parsers.readline("\n")
});
var controller=0;
var controllerold=0;
var Bu=0,Ly=0,Ry=0,Rt=0;
var Bl=0,Lx=0,Rx=0,Lt=0;
var count=0;
var LOS=0;
var buffer= new Buffer([2,Bu,Bl,Ly,Lx,Ry,Rx,Lt,Rt]);
//var ary={0x11,0x22,0x33,0x44,0x55,0x66,0x77,0xFF};

app.get('/', function(req, res){
   res.sendFile(__dirname + '/gamepadToArduino.html'); 
});

http.listen(3000, function(){
  console.log('listening on *:3000');
});
io.on('connection', function(socket)
{
	console.log('Signal detected');
	socket.on('disconnect', function(){console.log('Signal Lost');});
	socket.on('ButtonsUpper',function(msg){Bu=msg;});
	socket.on('LeftY'   ,function(msg){Ly=msg;});
	socket.on('RightY'  ,function(msg){Ry=msg;});
	socket.on('TriggerLeft',function(msg){Lt=msg;});
	socket.on('ButtonsLower',function(msg){Bl=msg;});
	socket.on('LeftX'   ,function(msg){Lx=msg;});
	socket.on('RightX'  ,function(msg){Rx=msg;});
	socket.on('TriggerRight',function(msg){Rt=msg;});
	socket.on('camera',function(msg){camera(msg);});
	socket.on('flashlight',function(msg){flashlight.writeSync(msg);
		console.log("flashlight toggled");});
	socket.on('message',  function(msg)
	{
	  console.log(msg);
	  controller=msg;
	  //serialPort.write(msg);
	});
});

function camera(cam)
{
		 if(cam==1)
	{console.log("camera front"); //camA
		selection.writeSync(0);
		enable1.writeSync(0);
		enable2.writeSync(1);}
	else if(cam==2)
	{console.log("camera claw"); //camB
		selection.writeSync(1);
		enable1.writeSync(0);
		enable2.writeSync(1);}
	else if(cam==3) 
	{console.log("camera c"); //camC
		selection.writeSync(0);
		enable1.writeSync(1);
		enable2.writeSync(0);}
	else if(cam==4)
	{console.log("camera d"); //camD
		selection.writeSync(1);
		enable1.writeSync(1);
		enable2.writeSync(0);}
}
function flashlight(light)
{
	if (light==0)
	{console.log("flashlight off");
		flashlight.writeSync(0);}
	else if (light==1)
	{console.log("flashlight on");
		flashlight.writeSync(0);}
}

serialPort.on('open', showPortOpen);
serialPort.on('data', onData);
serialPort.on('close', showPortClose);
serialPort.on('error', showError);
//serialport.on('open',);

function showPortOpen() 
{
   console.log('port open. Data rate: ' + serialPort.options.baudRate);
   //var buffer = new Buffer([0,0xF3,0xA3]);
   
   //serialPort.write(buffer);
   setInterval(toSend,33);
   //serialPort.write("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
   //setInterval(function(){serialPort.write(test);},1000);
}
 
function onData(data)
{
	msg=data;
	console.log("in "+msg);
	//console.log(data);
}
 
function showPortClose() {
   console.log('port closed.');
}
 
function showError(error) {
   console.log('Serial port error: ' + error);
}

function toSend()
{
	//console.log(Bu+" "+Bl+" "+Ly+" "+Lx+" "+Ry+" "+Rx+" "+Lt+" "+Rt);
	buffer= new Buffer([2,Bu,Bl,Ly,Lx,Ry,Rx,Lt,Rt]);
	//var buffer= new Buffer([2,71,114,97,112,101,100,254,32]);
	controller=Bu+Bl+Ly+Lx+Ry+Rx+Lt+Rt;
	//serialPort.write(buffer);
	//console.log("cksum= "+controller);
	//serialPort.write("Grap" + 0x65);
	if (controllerold==controller)
	{count++;}
	else
	{count=0;}
	controllerold=controller;
	if(count<=60)
	{//serialPort.write("Grapist!\n");
	serialPort.write(buffer);
	console.log("cksum= "+controller);
	//console.log(c));
	los.writeSync(0);}
	else
	{
	buffer=new Buffer([2,0,0,0,0,0,0,0,0]);
	serialPort.write(buffer);
	//console.log(0x0000000000000000);
	los.writeSync(1);}
	
}
