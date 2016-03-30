var app = require('express')();
var http = require('http').Server(app);
var io = require('socket.io')(http);
var SerialPort = require("serialport").SerialPort
var serialPort = new SerialPort("/dev/ttyACM0", {
  baudrate: 9600
});


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
  console.log('a user connected to index');
  socket.on('disconnect', function(){
    console.log('user left index');
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
		socket.on('message',  function(msg)
	{
	  console.log(msg);
	  serialPort.write(msg);
	});
});



http.listen(3000, function(){
  console.log('listening on *:3000');
});
