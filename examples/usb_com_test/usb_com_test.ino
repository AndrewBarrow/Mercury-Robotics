/*
  This is a demo for usb communications between Arduino and Raspberry Pi 2.
*/

char buffer[7] = {};

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    Serial.readBytes(buffer, 8);

    for (int i = 0; i < 8; i++) {
      Serial.print(buffer[i]);
    }
  }
}
  
