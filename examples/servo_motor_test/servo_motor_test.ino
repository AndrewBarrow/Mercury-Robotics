#include <motor.h>


void setup() {
  servo::setup();

  //claw.set_position(claw.query_max());
  servo::tall();
}

void loop() {

  claw.set_position(claw.query_min());
  delay(1000);
    claw.set_position(claw.query_max()); 

delay(3000);
  servo::load();
delay(3000);
    claw.set_position(claw.query_min());
  delay(1000);
    claw.set_position(claw.query_max()); 
delay(3000);
servo::tall();
delay(3000);

 //delay(5000);
}

