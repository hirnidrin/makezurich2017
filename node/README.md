# Node web app

## Installation
Install [nodejs & npm](https://docs.npmjs.com/getting-started/installing-node), then clone node directory and run `npm install`.

## Configuration
config.js must be added manually to node root folder:

```javascript
//config.js
var appId = "TTN_APP_ID";
var accessKey = "TTN_ACCESS_KEY";

exports.ttn_id = appId;
exports.ttn_key = accessKey;
```
Instead of using the separate file config.js you can also paste credentials directly to app.js and remove the line where config.js is required

## Run the app

`npm start` or `node app.js` in terminal

