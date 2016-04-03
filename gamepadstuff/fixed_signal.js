var serialPort = require("serialport");
var SerialPort = require("serialport").SerialPort;

var sp = new SerialPort("/dev/ttyACM0", {
	baudrate: 9600,
	dataBits: 8, // this is the default for Arduino serial communication
	parity: 'none', // this is the default for Arduino serial communication
	stopBits: 1, // this is the default for Arduino serial communication
	flowControl: false, // this is the default for Arduino serial communication
	parser: serialPort.parsers.readline("\n")
});
/*
var bp = new SerialPort("/dev/ttyUSB0", {
	baudrate: 9600,
	dataBits: 8, // this is the default for Arduino serial communication
	parity: 'none', // this is the default for Arduino serial communication
	stopBits: 1, // this is the default for Arduino serial communication
	flowControl: false, // this is the default for Arduino serial communication
	parser: serialPort.parsers.readline("\n")
});
*/
var message = new Buffer([0x31,0x32,0x33,0x34,0x35]);


sp.on('open', showPortOpen);
sp.on('data', onData);
sp.on('close', showPortClose);
sp.on('error', showError);

function showPortOpen() 
{
	console.log('port open. Data rate: ' + sp.options.baudRate);
	setInterval(write,1000);
}

function onData(data)
{
	msg=data;
	console.log("data in");
	console.log("in "+msg);
	console.log(data);
}

function write() {
	//console.log(message);
 //sp.write(message);
 //bp.write(message);
}
function showPortClose() {
   console.log('port closed.');
}
 
function showError(error) {
   console.log('Serial port error: ' + error);
}
