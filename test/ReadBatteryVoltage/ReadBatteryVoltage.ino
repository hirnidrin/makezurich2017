/*
  ReadBatteryVoltage
  Reads an analog input on pin 0, converts it to voltage, and prints the result to the serial monitor.
  Graphical representation is available using serial plotter (Tools > Serial Plotter menu)
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.
*/

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {

  static uint8_t msg[6];
  
  // read the input on analog pin 0:
  int batteryValue = analogRead(A0);
  float voltageValue = 3.3; // Volt
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = 2 * batteryValue * (voltageValue / 1023.0);
  
  int batteryHex = (int) (voltage * 100);

  msg[4] = highByte(batteryHex);
  msg[5] = lowByte(batteryHex);

  // print out the value you read:
  
  Serial.print("Battery Voltage [Volt]: ");
  Serial.print(voltage);
  Serial.print("  --  Battery HEX: ");
  Serial.print(msg[4]); // Print single line
  Serial.print(" ");
  Serial.println(msg[5]); // Print to new line

  delay(1000);
}
