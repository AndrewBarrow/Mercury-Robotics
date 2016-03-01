#include <motor.h>
#include <led.h>

void setup() {
  servo::setup();
  servo::tall();
}

void loop() {
  r.drive(255, DC::Reverse);
  l.drive(255, DC::Reverse);
}
