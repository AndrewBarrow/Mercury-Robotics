var app = require('express')();
var http = require('http').Server(app);
var io = require('socket.io')(http);
var msg

app.get('/', function(req, res){
   res.sendFile(__dirname + '/client.html');
});
app.get('/uplink', function(req, res){
   res.sendFile(__dirname + '/uplink.html');
});
app.get('/camtest', function(req, res){
   res.sendFile(__dirname + '/Videosrctest.html');
});
http.listen(3000, function(){
  console.log('listening on *:3000');
});
io.on('connection', function(socket)
{
	console.log('Signal detected');
	socket.on('disconnect', function(){console.log('Signal Lost');});
	
	socket.on('rtcClient', uplink);
	socket.on('rtcSever', uplinkclient);
	
	
	socket.on('message',  function(msg){console.log(msg);});
});
function uplink()
{
	console.log('Video uplink established');
		socket.emit('rtcUplinkData',msg);
}
function uplinkclient()
{
	console.log('Video uplink requested');
		socket.emit('rtcClientData',msg);
}
