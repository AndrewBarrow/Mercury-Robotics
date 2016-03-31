#include <led.h>
#include <motor.h>
#include <sensor.h>

/*
  This is a demo for usb communications between Arduino and Raspberry Pi 2.
*/

char buffer[8] = { };

struct usb_input {
  unsigned int digital;
  unsigned int ls;
  unsigned int rs;
  unsigned char lt;
  unsigned char rt;  
};

bool motor_zero = false;

usb_input ui;

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    for (int i = 0; i < 8; i++) {
      buffer[i] = Serial.read();
    }

  ui.digital = ((buffer[0] << 8) + buffer[1]);
  ui.ls = ((buffer[2] << 8) + buffer[3]);
  ui.rs = ((buffer[4] << 8) + buffer[5]);
  ui.lt = buffer[6];
  ui.rt = buffer[7];

  if ((ui.lt) || (ui.rt)) {
    if ((ui.rt > 0) && !(ui.lt > 0)) {
      l.drive(ui.rt, DC::For);
      r.drive(ui.rt, DC::For);
      motor_zero = true;  
    }
  } else if (motor_zero == true){
    l.drive(0, l.prev_dir());
    r.drive(0, l.prev_dir());
    motor_zero = false;  
  }
    

   //for (int i = 0; i < 8; i++) {
   //   Serial.print(buffer[i]);
   // }

   Serial.print(ui.rt);

/*
Serial.print(buffer[1], HEX);
Serial.print(" ");
Serial.print(buffer[2], HEX);
Serial.print(" ");
Serial.print(buffer[3], HEX);
Serial.print(" ");
Serial.print(buffer[4], HEX);
Serial.print(" ");
Serial.print(buffer[5], HEX);
Serial.print(" ");
Serial.print(buffer[6], HEX);
Serial.print(" ");
Serial.print(buffer[7], HEX);
Serial.print(" ");
Serial.println(buffer[8], HEX);
*/
/*
Serial.print(ui.digital, HEX);
Serial.print(" ");
Serial.print(ui.ls, HEX);
Serial.print(" ");
Serial.print(ui.rs, HEX);
Serial.print(" ");
Serial.print(ui.lt, HEX);
Serial.print(" ");
Serial.println(ui.rt, HEX);
*/
  }
}
  
