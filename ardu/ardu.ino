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

int i;
float f;
static uint8_t msg[6];

// the loop routine runs over and over again forever:
void loop() {
  led_on();

  // get the battery voltage: read the voltage on analog pin 0, represents half of battery voltage 
  int voltageA0 = analogRead(A0); // returns an integer in the range 0..1023 (10bit A/D converter)
  // convert the integer to a float (0 - 3.3V):
  float f = voltageA0 * 3.3 / 1024.0;
  // the voltage in f (at the A0 pin) represents half of the battery level -> adjust for this
  f = 2 * f; // the real current battery voltage level
  // convert 4.87 to 487 (we must transmit an integer / byte value)
  int i = (int) (f * 100);
  // pack into byte array
  msg[0] = highByte(i);
  msg[1] = lowByte(i);
  // log to console
  Serial.print("Batt [V]: ");
  Serial.print(f); Serial.print(" / "); Serial.print(i);
  
  // get temp, convert 22.58 to 2258 (we must transmit an integer / byte value)
  f = SHT2x.GetTemperature(); // returns float nn.nn
  i = (int) (f * 100);
  // pack into byte array
  msg[2] = highByte(i);
  msg[3] = lowByte(i);
  // log to console
  Serial.print(" -- Temp [C]: ");
  Serial.print(f); Serial.print(" / "); Serial.print(i);

  // get hum, convert 89.58 to 6789 to transmit an integer / byte value ... todo: round to 1 decimal
  f = SHT2x.GetHumidity(); // returns float nn.nn
  i = (int) (f * 100);
  // pack into byte array
  msg[4] = highByte(i);
  msg[5] = lowByte(i);
  // log to console
  Serial.print(" -- Hum [%RH]: ");
  Serial.print(f); Serial.print(" / "); Serial.println(i);

  // send the byte array
  myLora.txBytes(msg, 6);

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

