#include <PS3USB.h>
//#include <PS3BT.h>
#include <usbhub.h>

#include <motor.h>
#include <led.h>

#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

USB Usb;
//BTD Btd(&Usb);
//PS3BT PS3(&Btd, 0x13, 0x71, 0xDA, 0x7D, 0x1A, 0x00);
PS3USB PS3(&Usb); // for usb mode

bool cata_set = true;

void setup() {
  Serial.begin(115200);

  servo::setup();

  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));

  servo::setup();
  claw.set_pos(claw.query_max());
  flood.toggle(HIGH);
}

void loop() {
  Usb.Task();

  /*
    if (PS3.PS3Connected) {
      if (PS3.getButtonClick(PS)) {
        PS3.disconnect();  
      }

      add another } at the very end
    */

  if (PS3.getAnalogHat(LeftHatX)) {
    theta.set_pos(255 - PS3.getAnalogHat(LeftHatX), 0, 255);
  }
  if (PS3.getAnalogHat(LeftHatY)) {
    elbow.set_pos(PS3.getAnalogHat(LeftHatY), 0, 255);  
  }
  if (PS3.getAnalogHat(RightHatX)) {
    wrist.set_pos(PS3.getAnalogHat(RightHatY), 0, 255);  
  }

  if (PS3.getButtonPress(L1) == true) {
    if (PS3.getButtonClick(CIRCLE)) {
      if (cata_set) {
        cata.set_pos(100);
        cata_set = false;  
      } else {
        cata.set_pos(0);
        cata_set = true;  
      }
    }  
  }

  if (PS3.getButtonPress(R1) == true) {
    claw.set_pos(0);  
  } else {
    claw.set_pos(100);  
  }
}



