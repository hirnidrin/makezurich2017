const ttn = require('ttn');
const StringDecoder = require('string_decoder').StringDecoder; // decoding buffer
const config = require('./config'); // keys and config variables stored separately

// ttn connection settings
const region = 'eu';
const appId = config.ttn_id;
const accessKey = config.ttn_key;

//more


// construct client
const client = new ttn.Client(region, appId, accessKey);


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
  
  const decoder = new StringDecoder('utf8');



  if (data.payload_raw){
    var data_point = data.payload_raw;
    //const point = Buffer.from(data_point);
    console.log("data_point is: " + data_point);
  }else { 
    console.log("no payload");
  }

});

client.on('message', null, 'led', function(deviceId, led) {

  // Toggle the LED
  var payload = {
    led: !led
  };

  // If you don't have an encoder payload function:
  // var payload = [led ? 0 : 1];

  console.log('[DEBUG]', 'Sending:', JSON.stringify(payload));
  client.send(deviceId, payload);
});