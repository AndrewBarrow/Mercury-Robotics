#include <led.h>
#include <motor.h>
#include <sensor.h>

/*
  This is a demo for usb communications between Arduino and Raspberry Pi 2.
*/

//char buffer[8] = { 'a', 'b', 'c', 'd', 'e', 'f', '~', 'þ' };
char buffer[2] = { };
int buf;

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    /*for (int i = 0; i < 8; i++) {
      buffer[i] = Serial.read();
    }*/

      buffer[0] = Serial.read();
      buffer[1] = Serial.read();

    //String buf(buffer);
    //Serial.println(buf);

    l.drive(buffer[0], DC::For);
    r.drive(buffer[1], DC::Rev);
    
    //Serial.print(buffer[1]);
    //Serial.print(buffer[2]);
    //Serial.print(buffer[3]);
    //Serial.print(buffer[4]);
    //Serial.print(buffer[5]);
    //Serial.print(buffer[6]);
    //Serial.println(buffer[7]);
  }

  //buffer_drive();

}

void buffer_drive() {
  l.drive(buffer[6], DC::Rev);
  r.drive(buffer[7], DC::For);  
}

void write_to() {
  /*for (int i = 0; i < 8; i++) {
    if (i = 7) {
      Serial.println(buffer[i]);  
    } else {
      Serial.print(buffer[i]);
    }
  } */
  Serial.println("Grapist!");
  delay(1000);
}
  
