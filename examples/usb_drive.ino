#include <motor.h>
#include <led.h>
#include <sensor.h>
#include <usb_com.h>

unsigned char buf[8];

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
  Serial.begin(9600);
  
  servo::setup();
  claw.set_position(claw.query_max());
  flood.toggle(HIGH);
}

void loop() {
  if (Serial.available() > 0) {

    if (Serial.read() == 0x02) {
      for (int i = 0; i < 8; ) {
        buf[i] = Serial.read();

        // Only increment our buffer when buf[i] has a valid character (ie no -1 or 0xFF)
        if ((buf[i] != -1) && (buf[i] != 0xFF)) {
          i++;
        }
      }
		usb.assign(buf);

	if (usb.rt || usb.lt) {
    if ((usb.rt > trig_min) && (!usb.lt > trig_min)) {
      if ((usb.lsx < dz_max) && (usb.lsx > dz_min)) {
        l.drive(usb.rt, DC::For);
        r.drive(usb.rt, DC::For);  
        motor_zero = true;    
      }
      if ((usb.lsx < dz_min) && (usb.lsx > analog_min)) {
        // left
        l.drive(DC::normalize<uint8_t, uint8_t>(usb.lsx, analog_min, dz_min, 0, usb.rt), DC::For);
        r.drive(usb.rt, DC::For);
        motor_zero = true;
      }
      if ((usb.lsx > dz_max) && (usb.lsx < analog_max)) {
        // right
        l.drive(usb.rt, DC::For);
        r.drive(DC::normalize<uint8_t, uint8_t>((usb.lsx), dz_max, analog_max, 0, usb.rt), DC::For);
        motor_zero = true;
      }
      if (usb.lsx == analog_min) {
        // skid left
        l.drive(usb.rt, DC::Rev);
        r.drive(usb.rt, DC::For);
        motor_zero = true;
      }
      if (usb.lsx == analog_max) {
        // skid right
        l.drive(usb.rt, DC::For);
        r.drive(usb.rt, DC::Rev);
        motor_zero = true;
      } 
    }

    if ((usb.lt > trig_min) && (!usb.rt > trig_min)) {
      if ((usb.lsx < dz_max) && (usb.lsx > dz_min)) {
        l.drive(usb.lt, DC::Rev);
        r.drive(usb.lt, DC::Rev); 
        motor_zero = true;    
      }
      if ((usb.lsx < dz_min) && (usb.lsx > analog_min)) {
        // left
        l.drive(usb.lt, DC::Rev);
        r.drive(DC::normalize<uint8_t, uint8_t>(usb.lsx, analog_min, dz_min, 0, usb.lt), DC::Rev);
        motor_zero = true;
      }
      if ((usb.lsx > dz_max) && (usb.lsx < analog_max)) {
        // right
        l.drive(DC::normalize<uint8_t, uint8_t>((usb.lsx), dz_max, analog_max, 0, usb.lt), DC::Rev);
        r.drive(usb.lt, DC::Rev);
        motor_zero = true;
      }
      if (usb.lsx == analog_min) {
        // skid left
        l.drive(usb.lt, DC::For);
        r.drive(usb.lt, DC::Rev);
        motor_zero = true;
      }
      if (usb.lsx == analog_max) {
        // skid right
        l.drive(usb.lt, DC::Rev);
        r.drive(usb.lt, DC::For);
        motor_zero = true;
      } 
    }
  } else if (motor_zero == true) {
    l.drive(0, l.prev_dir());
    r.drive(0, r.prev_dir());
    motor_zero = false;  
  }

  if (usb.digital & button.LB) {
    if (usb.digital & button.B) {
      if (cata_set) {
        cata.set_pos(100);
        cata_set = false;  
      } else {
        cata.set_pos(0);
        cata_set = true;  
      }
    }  
  }

  if (usb.digital & button.RB) {
    claw.set_pos(0);  
  } else {
    claw.set_pos(100);  
  }

    if (usb.digital & button.UP) {
      servo::tall();
    }
    if (usb.digital & button.RIGHT) {
      servo::load();
    }
    if (usb.digital & button.DOWN) {
      servo::pickup();
    }
    if (usb.digital & button.LEFT) {
      servo::look();
    }
    }
  }
}
