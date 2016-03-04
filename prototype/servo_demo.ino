#include <XBOXONE.h>

#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

#include <motor.h>

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
  }
}
