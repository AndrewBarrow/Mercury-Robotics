/*
  This is a demo for usb communications between Arduino and Raspberry Pi 2.
  The Pi sends 9 byte (0x02 start byte + 8 byte message) to the Arduino, 
  the Arduino fills its buffer with the 8 byte message and sends it back to the Pi.
*/

unsigned char buf[8];

void setup() {
  Serial.begin(9600);
}

void loop() {
  read_write();
}

void read_write() {
  if (Serial.available() > 0) {

    // Only start reading the message once we encounter the start byte and then remove it from the Serial buffer
    if (Serial.read() == 0x02) {
      for (int i = 0; i < 8; ) {
        buf[i] = Serial.read();

        // Only increment our buffer when buf[i] has a valid character (ie no -1 or 0xFF)
        if ((buf[i] != -1) && (buf[i] != 0xFF)) {
          i++;
        }
      } 

      // Write back to the Pi.  The last print should be a println.
      for (int i = 0; i < 7; i++) {
        Serial.print(buf[i]);  
      }
      Serial.println(buf[7]);
    }
  }
}
  
