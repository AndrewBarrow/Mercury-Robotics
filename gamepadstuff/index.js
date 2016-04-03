var app = require('express')();
var http = require('http').Server(app);
var io = require('socket.io')(http);
var serialport = require("serialport");
var SerialPort = serialport.SerialPort;
var serialPort = new SerialPort("/dev/ttyACM2", {
  baudrate: 9600,
  parser: serialport.parsers.readline("\n")
});
var controller=0;
var controllerold=0;
var B=0,L=0,R=0,T=0;
var count=0;
var LOS=0;

app.get('/', function(req, res){
   res.sendFile(__dirname + '/gamepadToArduino.html'); //remember eventually this should be the index page again
});
app.get('/chat', function(req, res){
   res.sendFile(__dirname + '/chat.html');
});
app.get('/gametest', function(req, res){
   res.sendFile(__dirname + '/gamepadToArduino.html');
});

io.on('connection', function(socket){
  console.log('Signal Aquired');
  socket.on('disconnect', function(){
    console.log('Signal Lost');
  });
});
  // so apperently there is no rule about reusing the same event, it just adds to the functionallity
  // so i could combine them but thats super cool and i dont want to forget that
io.on('connection', function(socket){
  socket.on('chat message', function(msg){
    console.log('message: ' + msg);
     io.emit('chat message', msg);
	});
  socket.on('index message', function(msg){
    console.log('index message: ' + msg);
	});
  });
io.on('connection', function(socket)
{
	/*
		socket.on('message',  function(msg)
	{
	  //console.log(msg);
	  controller=msg;
	  //serialPort.write(msg);
	});
	*/
	socket.on('Buttons',function(msg){B=msg;});
	socket.on('Left'   ,function(msg){L=msg;});
	socket.on('Right'  ,function(msg){R=msg;});
	socket.on('Trigger',function(msg){T=msg;});
});
serialPort.on('open', showPortOpen);
serialPort.on('data', sendSerialData);
serialPort.on('close', showPortClose);
serialPort.on('error', showError);

function showPortOpen() {
   console.log('port open. Data rate: ' + serialPort.options.baudRate);
   setInterval(toSend,33);
}
 
function sendSerialData(data) {
   console.log("res" +data);
}
 
function showPortClose() {
   console.log('port closed.');
}
 
function showError(error) {
   console.log('Serial port error: ' + error);
}

function toSend()
{
	console.log(B+" "+L+" "+R+" "+T);
	serialPort.write(B);
	serialPort.write(L);
	serialPort.write(R);
	serialPort.write(T);
	/*
	if (controllerold==controller)
	{count++;}
	else
	{count=0;}
	controllerold=controller;
	if(count<=25)
	{serialPort.write(hex2a(controller));
	console.log(controller);
	//console.log(c));
	LOS=0;}
	else
	{//serialPort.write(0x0000000000000000);
	//console.log(0x0000000000000000);
	LOS=1;}
	*/
}

http.listen(3000, function(){
  console.log('listening on *:3000');
});

function hex2a(hexx) {
    var hex = hexx.toString();//force conversion
    var str = '';
    for (var i = 0; i < hex.length; i += 2)
        str += String.fromCharCode(parseInt(hex.substr(i, 2), 16));
    return str;
}
function a2hex(str) {
  var arr = [];
  for (var i = 0, l = str.length; i < l; i ++) {
    var hex = Number(str.charCodeAt(i)).toString(16);
    arr.push(hex);
  }
  return arr.join('');
}

