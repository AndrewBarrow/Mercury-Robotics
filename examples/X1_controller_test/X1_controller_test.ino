#include <XBOXONE.h>

#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

#include <motor.h>
#include <led.h>

USB Usb;
XBOXONE xbox(&Usb);

bool motor_zero = false;
bool cata_set = true;

// controller analog ranges
const uint16_t trig_min = 0;
const uint16_t trig_max = 1023;

const int16_t dz_min = -7500;
const int16_t dz_max = 7500;

const int16_t analog_min = -32768;
const int16_t analog_max = 32767;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1);
  }
  Serial.print(F("\r\nXBOX USB Library Started"));
  
  servo::setup();
  claw.set_position(claw.query_max());
}
void loop() {
  Usb.Task();
  if (xbox.XboxOneConnected) {
    if ((xbox.getButtonPress(R2) > trig_min) && !(xbox.getButtonPress(L2) > trig_min)) {
      if ((xbox.getAnalogHat(LeftHatX) < dz_max) && (xbox.getAnalogHat(LeftHatX) > dz_min)) {
        // forward
        l.drive(DC::normalize<uint16_t, uint8_t>(xbox.getButtonPress(R2), trig_min, trig_max, 0, 255), DC::Forward);
        r.drive(DC::normalize<uint16_t, uint8_t>(xbox.getButtonPress(R2), trig_min, trig_max, 0, 255), DC::Forward);
      }
      if ((xbox.getAnalogHat(LeftHatX) < dz_min) && (xbox.getAnalogHat(LeftHatX) > analog_min)) {
        // left
        l.drive(
          DC::normalize<int16_t, uint8_t>(
            xbox.getAnalogHat(LeftHatX), 
            (analog_min + 1), 
            dz_min, 
            trig_min, 
            DC::normalize<uint16_t, uint8_t>(xbox.getButtonPress(R2), trig_min, trig_max, 0, 255)), 
          DC::Forward
        );
        r.drive(DC::normalize<uint16_t, uint8_t>(xbox.getButtonPress(R2), trig_min, trig_max, 0, 255), DC::Forward);
      }
      if ((xbox.getAnalogHat(LeftHatX) > dz_max) && (xbox.getAnalogHat(LeftHatX) < analog_max)) {
        // right
        l.drive(DC::normalize<uint16_t, uint8_t>(xbox.getButtonPress(R2), trig_min, trig_max, 0, 255), DC::Forward);
        r.drive(
          DC::normalize<int16_t, uint8_t>(
            (analog_max - xbox.getAnalogHat(LeftHatX)), 
            dz_max, 
            (analog_max - 1), 
            trig_min, 
            DC::normalize<uint16_t, uint8_t>(xbox.getButtonPress(R2), trig_min, trig_max, 0, 255)), 
          DC::Forward
        );
      }
      if (xbox.getAnalogHat(LeftHatX) == analog_min) {
        // skid left
        l.drive(DC::normalize<uint16_t, uint8_t>(xbox.getButtonPress(R2), trig_min, trig_max, 0, 255), DC::Reverse);
        r.drive(DC::normalize<uint16_t, uint8_t>(xbox.getButtonPress(R2), trig_min, trig_max, 0, 255), DC::Forward);
      }
      if (xbox.getAnalogHat(LeftHatX) == analog_max) {
        // skid right
        l.drive(DC::normalize<uint16_t, uint8_t>(xbox.getButtonPress(R2), trig_min, trig_max, 0, 255), DC::Forward);
        r.drive(DC::normalize<uint16_t, uint8_t>(xbox.getButtonPress(R2), trig_min, trig_max, 0, 255), DC::Reverse);
      }
      
      motor_zero = true;
    } else if (motor_zero == true) {
      l.drive(0, l.prev_dir());
      r.drive(0, r.prev_dir());
      motor_zero = false;
    }
    
    if ((xbox.getButtonPress(L2) > trig_min) && !(xbox.getButtonPress(R2) > trig_min)) {
      if ((xbox.getAnalogHat(LeftHatX) < dz_max) && (xbox.getAnalogHat(LeftHatX) > dz_min)) {
        // reverse
        l.drive(DC::normalize<uint16_t, uint8_t>(xbox.getButtonPress(L2), trig_min, trig_max, 0, 255), DC::Reverse);
        r.drive(DC::normalize<uint16_t, uint8_t>(xbox.getButtonPress(L2), trig_min, trig_max, 0, 255), DC::Reverse);
      }
      if ((xbox.getAnalogHat(LeftHatX) < dz_min) && (xbox.getAnalogHat(LeftHatX) > analog_min)) {
        // left
        l.drive(DC::normalize<uint16_t, uint8_t>(xbox.getButtonPress(L2), trig_min, trig_max, 0, 255), DC::Reverse);
        r.drive(
          DC::normalize<int16_t, uint8_t>(
            (analog_max - xbox.getAnalogHat(LeftHatX)), 
            dz_max, 
            (analog_max - 1), 
            trig_min, 
            DC::normalize<uint16_t, uint8_t>(xbox.getButtonPress(L2), trig_min, trig_max, 0, 255)), 
          DC::Reverse
        );
      }
      if ((xbox.getAnalogHat(LeftHatX) > dz_max) && (xbox.getAnalogHat(LeftHatX) < analog_max)) {
        // right
        l.drive(
          DC::normalize<int16_t, uint8_t>(
            xbox.getAnalogHat(LeftHatX), 
            (analog_min + 1), 
            dz_min, 
            trig_min, 
            DC::normalize<uint16_t, uint8_t>(xbox.getButtonPress(L2), trig_min, trig_max, 0, 255)), 
          DC::Reverse
        );
        r.drive(DC::normalize<uint16_t, uint8_t>(xbox.getButtonPress(L2), trig_min, trig_max, 0, 255), DC::Reverse);
      }
      if (xbox.getAnalogHat(LeftHatX) == analog_min) {
        // skid left
        l.drive(DC::normalize<uint16_t, uint8_t>(xbox.getButtonPress(L2), trig_min, trig_max, 0, 255), DC::Forward);
        r.drive(DC::normalize<uint16_t, uint8_t>(xbox.getButtonPress(L2), trig_min, trig_max, 0, 255), DC::Reverse);
      }
      if (xbox.getAnalogHat(LeftHatX) == analog_max) {
        // skid right
        l.drive(DC::normalize<uint16_t, uint8_t>(xbox.getButtonPress(L2), trig_min, trig_max, 0, 255), DC::Reverse);
        r.drive(DC::normalize<uint16_t, uint8_t>(xbox.getButtonPress(L2), trig_min, trig_max, 0, 255), DC::Forward);
      }
      
      motor_zero = true;
    } else if (motor_zero == true) {
      l.drive(0, l.prev_dir());
      r.drive(0, r.prev_dir());
      motor_zero = false;
    }
    
  if (xbox.getButtonPress(L1) == true) {
    if (xbox.getButtonClick(B)) {
      // fire Catapult
      if (cata_set) {
        cata.set_position(cata.query_max());
        cata_set = false;
      } else {
        cata.set_position(cata.query_min());
        cata_set = true;
      }
    }
  }
  if (xbox.getButtonPress(R1) == true) {
    // open claw when RB is held
    claw.set_position(claw.query_min());
  } else {
    // close claw when RB is NOT being held
    claw.set_position(claw.query_max());
  }
  
    if (xbox.getButtonClick(UP)) {
    servo::tall();
  }
    if (xbox.getButtonClick(DOWN)) {
    servo::pickup();
  }
    if (xbox.getButtonClick(LEFT)) {
    servo::look();
  }
    if (xbox.getButtonClick(RIGHT)) {
    servo::load();
  }
  
  if (xbox.getButtonClick(START)) {
    // switch drive mode
  }
  if (xbox.getButtonClick(BACK)) {
    // switch override
  }
  
  if (xbox.getButtonClick(Y)) {
    // toggle floodlight
    if (flood.state()) {
      flood.toggle(LOW);
    } else {
      flood.toggle(HIGH);
    }
  }
  }
}
