#include <PS3BT.h>
#include <usbhub.h>

#include <motor.h>
#include <led.h>

#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

USB Usb;
BTD Btd(&Usb);
PS3BT PS3(&Btd, 0x13, 0x71, 0xDA, 0x7D, 0x1A, 0x00);

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
  claw.set_position(claw.query_max());
  flood.toggle(HIGH);
}

void loop() {
  Usb.Task();

  if (PS3.PS3Connected) {
    if (PS3.getButtonClick(PS)) {
      PS3.disconnect();  
    }

  if (PS3.getAnalogButton(R2) || PS3.getAnalogButton(L2)) {
    if ((PS3.getAnalogButton(L2) > trig_min)&& (!PS3.getAnalogButton(R2) > trig_min)) {
      if ((PS3.getAnalogHat(LeftHatX) < dz_max) && (PS3.getAnalogHat(LeftHatX) > dz_min)) {
        l.drive(PS3.getAnalogButton(L2), DC::Forward);
        r.drive(PS3.getAnalogButton(L2), DC::Forward);  
        motor_zero = true;    
      }
      if ((PS3.getAnalogHat(LeftHatX) < dz_min) && (PS3.getAnalogHat(LeftHatX) > analog_min)) {
        // left
        l.drive(DC::normalize<uint8_t, uint8_t>(PS3.getAnalogHat(LeftHatX), (analog_min + 1), dz_min, PS3.getAnalogButton(L2)), DC::Forward);
        r.drive(PS3.getAnalogButton(L2), DC::Forward);
        motor_zero = true;
      }
      if ((PS3.getAnalogHat(LeftHatX) > dz_max) && (PS3.getAnalogHat(LeftHatX) < analog_max)) {
        // right
        l.drive(PS3.getAnalogButton(L2), DC::Forward);
        r.drive(DC::normalize<uint8_t, uint8_t>((analog_max - PS3.getAnalogHat(LeftHatX)), dz_max, (analog_max - 1), 0, PS3.getAnalogButton(L2)), DC::Forward);
        motor_zero = true;
      }
      if (PS3.getAnalogHat(LeftHatX) == analog_min) {
        // skid left
        l.drive(PS3.getAnalogButton(L2), DC::Reverse);
        r.drive(PS3.getAnalogButton(L2), DC::Forward);
        motor_zero = true;
      }
      if (PS3.getAnalogHat(LeftHatX) == analog_max) {
        // skid right
        l.drive(PS3.getAnalogButton(L2), DC::Forward);
        r.drive(PS3.getAnalogButton(L2), DC::Reverse);
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
        cata.set_position(cata.query_max());
        cata_set = false;  
      } else {
        cata.set_position(cata.query_min());
        cata_set = true;  
      }
    }  
  }

  if (PS3.getButtonPress(R1) == true) {
    claw.set_position(claw.query_min());  
  } else {
    claw.set_position(claw.query_max());  
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
}


