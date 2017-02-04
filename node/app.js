const express = require('express');
const app = express();
const bodyParser = require('body-parser');

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

function convert_readings(data){
  // input must be array
  console.log("*** converting ***");
  console.log(data);
  if (data){
    max_len = data.length;
    var readings = [];
    for (var i = 0; i < max_len; i += 2){
      var double = data.slice(i, i+2);
      var reading_value = double[0] * 256 + double[1];
      readings.push(reading_value);
    }
  
    var output = {};
    output.bat = readings[0];
    output.tmp = readings[1] / 100;
    output.hum = readings[2] / 100;
    output.ts = new Date();
  
    return output;

  } else {
    console.log("no data. input is " + data);
  }
}


// DB setup
const MongoClient = require('mongodb').MongoClient;
const assert = require('assert');

// Connection url
var url = 'mongodb://localhost:4321/ttn'; // mongodb://localhost:4321/ttn

function readingMongoInsert(ttnMsg, sensordata) {

  MongoClient.connect(url, function(err, db) {
    // Use the admin database for the operation
    assert.equal(null, err);

    console.log("db connected");
    var collection = db.collection('makezh');
    var reading = {};
    
    reading.raw = ttnMsg; // saving complete message

    reading.ts = sensordata.ts;
    reading.bat = sensordata.bat;
    reading.tmp = sensordata.tmp;
    reading.hum = sensordata.hum;

    collection.insert(reading, function(err, result){
      console.log(result);
    });
    
    // List all the available databases
    db.close();

  });

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

client.on('message', function(deviceId, msg) {

    var data = new Uint16Array(msg.payload_raw);
      // check if message contains payload
      if (data){
        var sensordata = convert_readings(data); // convert sensor readings in payload_raw
        readingMongoInsert(msg, sensordata); // insert raw data and converted data to db     
      // complain if no payload
      }else { 
        console.log("no payload");
      }
});

//// express server
// set up
app.use(express.static('public'));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded());
// in latest body-parser use like below.
app.use(bodyParser.urlencoded({ extended: true }));

// routing
app.get('/', function(req, res){
  res.sendFile(__dirname + '/index.html');
});


app.get('/historic', function(req, res){
  res.sendFile(__dirname + '/historic.html');
});

app.post('/historic',function(req,res){
   console.log(req.body);
});


// open websocket connection
io.on('connection', function(socket){
  
  console.log('socket connection');
  // listen for incoming ttn messages;
  client.on('message', function(deviceId, msg) {
      console.log("**** MESSAGE RECEIVED ****");
      console.log(msg);
      var data = new Uint16Array(msg.payload_raw);

      // check if message contains payload
      if (data){
        console.log("we have payload: " + data);
        var sensordata = convert_readings(data); // convert sensor readings in payload_raw 
        io.emit('data_refresh', sensordata); // emit socket message to all connected clients
      
      // complain if no payload
      }else { 
        console.log("no payload");
      }
    });
});


// run server
http.listen(PORT, function(){
  console.log('listening on port*: ' + PORT);
});


