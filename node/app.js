const express = require('express');
const app = express();

var http = require('http').Server(app);
var io = require('socket.io')(http);

const ttn = require('ttn');
const StringDecoder = require('string_decoder').StringDecoder; // decoding buffer. currently not required
const config = require('./config'); // keys and config variables stored separately

// ttn connection settings
const region = 'eu';
const appId = config.ttn_id;
const accessKey = config.ttn_key;

// parameters
const PORT = 3210;

// construct ttn client
const client = new ttn.Client(region, appId, accessKey);

// tools

function ab2str(buf) {
  return String.fromCharCode.apply(null, new Uint16Array(buf));
}

function str2ab(str) {
  var buf = new ArrayBuffer(str.length*2); // 2 bytes for each char
  var bufView = new Uint16Array(buf);
  for (var i=0, strLen=str.length; i<strLen; i++) {
    bufView[i] = str.charCodeAt(i);
  }
  return buf;
}


// run  it
client.on('connect', function(connack) {
  console.log('[DEBUG]', 'Connect:', connack);
});

client.on('error', function(err) {
  console.error('[ERROR]', err.message);
});

client.on('activation', function(deviceId, data) {
  console.log('[INFO] ', 'Activation:', deviceId, JSON.stringify(data, null, 2));
});

client.on('device', null, 'down/scheduled', function(deviceId, data) {
  console.log('[INFO] ', 'Scheduled:', deviceId, JSON.stringify(data, null, 2));
});

client.on('message', function(deviceId, data) {
  console.info('[INFO] ', 'Message:', deviceId, JSON.stringify(data, null, 2));

  if (data.payload_raw){
    var data_point = data.payload_raw;
    //const point = Buffer.from(data_point);
    console.log("data_point is: " + data_point);
  }else { 
    console.log("no payload");
  }

});

// express basic server
// set up
app.use(express.static('public'));

// routing
app.get('/', function(req, res){
  res.sendFile(__dirname + '/index.html');
});

io.on('connection', function(socket){
  console.log('connection')
  
  client.on('message', function(deviceId, data) {

      if (data.payload_raw){
        
        var data_point = ab2str(data.payload_raw);
        io.emit('chat message', data_point);

      }else { 
        
        console.log("no payload");

      }

    });


  socket.on('chat message', function(msg){
    // console.log('message: ' + msg);
    // io.emit('chat message', msg);
  });
});

//serve
http.listen(PORT, function(){
  console.log('listening on port*: ' + PORT);
});


