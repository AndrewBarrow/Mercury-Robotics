var serialPort = require("serialport");
var SerialPort = require("serialport").SerialPort;
var sp = new SerialPort("/dev/ttyACM0", {
	baudrate: 9600,
	parser: serialPort.parsers.readline("\n")
});
sp.on('open',onOpen);
sp.on('data',onData);
function onOpen()
{
	console.log('port open. Data rate: ' + sp.options.baudRate);
}
function onData(data)
{
	console.log(data);
}
