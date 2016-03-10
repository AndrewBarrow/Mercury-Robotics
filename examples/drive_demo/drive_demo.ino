/*
  This is a demo of driving.
  Controls:
    R2/RT - drive forward
    L2/LT - drive reverse
    Left Analog Stick x-axis - steering
    
    UP - auto claw tall
    DOWN - auto claw pickup
    LEFT - auto claw look
    RIGHT - auto claw load
    
    R1/RB - open claw
    L1/LB - catapult safety
    CIRCLE/B - launch catapult
*/

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

bool motor_zero = false;
bool cata_set = true;

// controller ranges
const uint16_t trig_min = 0;
const uint16_t trig_max = 255;

const uint16_t dz_min = 117;
const uint16_t dz_max = 137;

const uint16_t analog_min = 0;
const uint16_t analog_max = 255;

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
   * if (PS3.PS3Connected) {
    if (PS3.getButtonClick(PS)) {
      PS3.disconnect();  
    }
    */

  if (PS3.getAnalogButton(R2) || PS3.getAnalogButton(L2)) {
    if ((PS3.getAnalogButton(R2) > trig_min) && (!PS3.getAnalogButton(L2) > trig_min)) {
      if ((PS3.getAnalogHat(LeftHatX) < dz_max) && (PS3.getAnalogHat(LeftHatX) > dz_min)) {
        l.drive(PS3.getAnalogButton(R2), DC::For);
        r.drive(PS3.getAnalogButton(R2), DC::For);
        Serial.println(PS3.getAnalogButton(R2));  
        motor_zero = true;    
      }
      if ((PS3.getAnalogHat(LeftHatX) < dz_min) && (PS3.getAnalogHat(LeftHatX) > analog_min)) {
        // left
        l.drive(DC::normalize<uint8_t, uint8_t>(PS3.getAnalogHat(LeftHatX), analog_min, dz_min, 0, PS3.getAnalogButton(R2)), DC::For);
        r.drive(PS3.getAnalogButton(R2), DC::For);
        motor_zero = true;
      }
      if ((PS3.getAnalogHat(LeftHatX) > dz_max) && (PS3.getAnalogHat(LeftHatX) < analog_max)) {
        // right
        l.drive(PS3.getAnalogButton(R2), DC::For);
        r.drive(DC::normalize<uint8_t, uint8_t>((PS3.getAnalogHat(LeftHatX)), dz_max, analog_max, 0, PS3.getAnalogButton(R2)), DC::For);
        motor_zero = true;
      }
      if (PS3.getAnalogHat(LeftHatX) == analog_min) {
        // skid left
        l.drive(PS3.getAnalogButton(R2), DC::Rev);
        r.drive(PS3.getAnalogButton(R2), DC::For);
        motor_zero = true;
      }
      if (PS3.getAnalogHat(LeftHatX) == analog_max) {
        // skid right
        l.drive(PS3.getAnalogButton(R2), DC::For);
        r.drive(PS3.getAnalogButton(R2), DC::Rev);
        motor_zero = true;
      } 
    }

    if ((PS3.getAnalogButton(L2) > trig_min) && (!PS3.getAnalogButton(R2) > trig_min)) {
      if ((PS3.getAnalogHat(LeftHatX) < dz_max) && (PS3.getAnalogHat(LeftHatX) > dz_min)) {
        l.drive(PS3.getAnalogButton(L2), DC::Rev);
        r.drive(PS3.getAnalogButton(L2), DC::Rev);
        Serial.println(PS3.getAnalogButton(L2));  
        motor_zero = true;    
      }
      if ((PS3.getAnalogHat(LeftHatX) < dz_min) && (PS3.getAnalogHat(LeftHatX) > analog_min)) {
        // left
        l.drive(PS3.getAnalogButton(L2), DC::Rev);
        r.drive(DC::normalize<uint8_t, uint8_t>(PS3.getAnalogHat(LeftHatX), analog_min, dz_min, 0, PS3.getAnalogButton(L2)), DC::Rev);
        motor_zero = true;
      }
      if ((PS3.getAnalogHat(LeftHatX) > dz_max) && (PS3.getAnalogHat(LeftHatX) < analog_max)) {
        // right
        l.drive(DC::normalize<uint8_t, uint8_t>((PS3.getAnalogHat(LeftHatX)), dz_max, analog_max, 0, PS3.getAnalogButton(L2)), DC::Rev);
        r.drive(PS3.getAnalogButton(L2), DC::Rev);
        motor_zero = true;
      }
      if (PS3.getAnalogHat(LeftHatX) == analog_min) {
        // skid left
        l.drive(PS3.getAnalogButton(L2), DC::For);
        r.drive(PS3.getAnalogButton(L2), DC::Rev);
        motor_zero = true;
      }
      if (PS3.getAnalogHat(LeftHatX) == analog_max) {
        // skid right
        l.drive(PS3.getAnalogButton(L2), DC::Rev);
        r.drive(PS3.getAnalogButton(L2), DC::For);
        motor_zero = true;
      } 
    }
  } else if (motor_zero == true) {
    l.drive(0, l.prev_dir());
    r.drive(0, r.prev_dir());
    motor_zero = false;  
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

    if (PS3.getButtonClick(UP)) {
      servo::tall();
    }
    if (PS3.getButtonClick(RIGHT)) {
      servo::load();
    }
    if (PS3.getButtonClick(DOWN)) {
      servo::pickup();
    }
    if (PS3.getButtonClick(LEFT)) {
      servo::look();
    }

  }



