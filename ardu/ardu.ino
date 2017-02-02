#include <rn2xx3.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <SHT2x.h>

// define the arduino digital i/o pins that emulate the serial connection to the Lora module
SoftwareSerial mySerial(7, 8); // RX, TX
#define RST  2

// The TTN credentials, using ABP authentication mode
//
// Copy the following lines from TTN Console -> Devices -> Overview tab -> "EXAMPLE CODE"
// const char *devAddr = "00000000";
// const char *nwkSKey = "00000000000000000000000000000000";
// const char *appSKey = "00000000000000000000000000000000";
// For easy code sharing, load credentials from file that is not under source control
#include "myLoraCredentials.h"

// bind the emulated serial port to the Lora module library
rn2xx3 myLora(mySerial);

// Setup routine runs once when you press reset
void setup() {
  pinMode(13, OUTPUT);
  led_on();

  // init the HW serial that connects to the FTDI, for logging back to the local terminal
  Serial.begin(57600);
  Serial.println("Startup");

  // init the i2c wire lib, pins A4 A5
  Wire.begin();


  // init the emulated serial that connects to the Lora module
  mySerial.begin(9600);

  // HW reset the rn2xx3
  pinMode(RST, OUTPUT);
  digitalWrite(RST, HIGH);
  digitalWrite(RST, LOW);
  delay(500);
  digitalWrite(RST, HIGH);

  // Initialise the rn2xx3 module, and log some info about the Lora module
  myLora.autobaud();
  Serial.println("When using OTAA, register this DevEUI: ");
  Serial.println(myLora.hweui());
  Serial.print("Microchip RN2xx3 version number: ");
  Serial.println(myLora.sysver());
  myLora.initABP(devAddr, appSKey, nwkSKey);

  led_off();
  delay(2000);
}

// the loop routine runs over and over again forever:
void loop() {
  led_on();

  int i;
  float f;
  static uint8_t msg[4];
  
  // get temp, convert 22.58 to 226 to transmit an integer / byte value ... todo: round to 1 decimal
  f = SHT2x.GetTemperature(); // returns float nn.nn
  i = (int) (f * 100);
  // pack into byte array
  msg[0] = highByte(i);
  msg[1] = lowByte(i);
  
  Serial.print("Temperature [C]: ");
  Serial.print(f); Serial.print(" / "); Serial.print(i);

  // get hum, convert 89.58 to 6789 to transmit an integer / byte value ... todo: round to 1 decimal
  f = SHT2x.GetHumidity(); // returns float nn.nn
  i = (int) (f * 100);
  // pack into byte array
  msg[2] = highByte(i);
  msg[3] = lowByte(i);

  Serial.print(" -- Humidity [%RH]: ");
  Serial.print(f); Serial.print(" / "); Serial.println(i);

  // send the byte array
  myLora.txBytes(msg, 4);

  led_off();
  delay(60000);
}

void led_on()
{
  digitalWrite(13, 1);
}

void led_off()
{
  digitalWrite(13, 0);
}

