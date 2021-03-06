var app = require('express')();
var http = require('http').Server(app);
var io = require('socket.io')(http);

app.get('/', function(req, res){
   res.sendFile(__dirname + '/client.html');
});
app.get('/uplink', function(req, res){
   res.sendFile(__dirname + '/uplink.html'); 
});
http.listen(3000, function(){
  console.log('listening on *:3000');
});
io.on('connection', function(socket)
{
	console.log('Signal detected');
	socket.on('disconnect', function(){console.log('Signal Lost');});
	
	socket.on('rtcClient',function(msg){socket.emit('rtcServer',msg)});
	socket.on('rtcSever', function(msg){socket.emit('rtcClient',msg)});
	
	
	socket.on('message',  function(msg){console.log(msg);});
});
