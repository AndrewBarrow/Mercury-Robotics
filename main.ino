#include <led.h>
#include <motor.h>
#include <sensor.h>
#include <usb_com.h>

unsigned char buf[8];

// states
bool motor_zero = false;
bool cata_set = true;
uint8_t mode;
uint8_t claw_state;

// controller ranges
const uint16_t trig_min = 0;
const uint16_t trig_max = 254;

const uint16_t dz_min = 117;
const uint16_t dz_max = 137;

const uint16_t analog_min = 0;
const uint16_t analog_max = 254;

Sonar front(3, 2, 20);
Sonar rear(8, 2, 10);

void drive_mode() {
	if (usb.rt || usb.lt) {
		if ((usb.rt > trig_min) && !(usb.lt > trig_min)) {
			if ((usb.lsx < dz_max) && (usb.lsx > dz_min)) {
        if (usb.digital & button.A) { 
          l.drive(usb.rt, DC::For);
          r.drive(usb.rt, DC::For);  
          motor_zero = true;           
        } else {
				  front.ping();
				  if (front.at_threshold()) {
				  	l.drive(0, DC::For);
					  r.drive(0, DC::For);  
					  motor_zero = true;      
			  	} else {
				  	l.drive(usb.rt, DC::For);
				  	r.drive(usb.rt, DC::For);  
				  	motor_zero = true;  
				  } 
				} 
			}
			if ((usb.lsx < dz_min) && (usb.lsx > analog_min)) {
				// left
        if (usb.digital & button.A) { 
          l.drive(DC::normalize<uint8_t, uint8_t>(usb.lsx, analog_min, dz_min, 0, usb.rt), DC::For);
          r.drive(usb.rt, DC::For);
          motor_zero = true;        
        } else {
				  front.ping();
				  if (front.at_threshold()) { 
					  l.drive(0, DC::For);
					  r.drive(0, DC::For);
					  motor_zero = true;
			  	} else {
					  l.drive(DC::normalize<uint8_t, uint8_t>(usb.lsx, analog_min, dz_min, 0, usb.rt), DC::For);
					  r.drive(usb.rt, DC::For);
					  motor_zero = true;
				  }
        }
			}
			if ((usb.lsx > dz_max) && (usb.lsx < analog_max)) {
				// right
        if (usb.digital & button.A) { 
          l.drive(usb.rt, DC::For);
          r.drive(DC::normalize<uint8_t, uint8_t>(usb.lsx, dz_max, analog_max, 0, usb.rt), DC::For);
          motor_zero = true;    
        } else {
				  front.ping();
				  if (front.at_threshold()) {
					  l.drive(0, DC::For);
					  r.drive(0, DC::For);
					  motor_zero = true;   
				  } else {
					  l.drive(usb.rt, DC::For);
				  	r.drive(DC::normalize<uint8_t, uint8_t>(usb.lsx, dz_max, analog_max, 0, usb.rt), DC::For);
				  	motor_zero = true;
				  }
        }
			}
			if (usb.lsx == analog_min) {
				// skid left
        if (usb.digital & button.A) { 
          l.drive(usb.rt, DC::Rev);
          r.drive(usb.rt, DC::For);
          motor_zero = true;
        } else {
				  front.ping();
				  if (front.at_threshold()) {
					  l.drive(0, DC::Rev);
					  r.drive(0, DC::For);
					  motor_zero = true;
			  	} else {
					  l.drive(usb.rt, DC::Rev);
					  r.drive(usb.rt, DC::For);
				  	motor_zero = true;
				  }
        }
			}
			if (usb.lsx == analog_max) {
				// skid right
        if (usb.digital & button.A) { 
          l.drive(usb.rt, DC::For);
          r.drive(usb.rt, DC::Rev);
          motor_zero = true;
        } else {
				  front.ping();
				  if (front.at_threshold()) {
				  	l.drive(0, DC::For);
				  	r.drive(0, DC::Rev);
				  	motor_zero = true;
				  } else {
				  	l.drive(usb.rt, DC::For);
				  	r.drive(usb.rt, DC::Rev);
				  	motor_zero = true;
				  }
        }
			}
		}
      
		if ((usb.lt > trig_min) && !(usb.rt > trig_min)) {
			if ((usb.lsx < dz_max) && (usb.lsx > dz_min)) {
				if (usb.digital & button.A) { 
          l.drive(usb.lt, DC::Rev);
          r.drive(usb.lt, DC::Rev); 
          motor_zero = true;
        } else {	
				  rear.ping();
				  if (rear.at_threshold()) {
					  l.drive(0, DC::Rev);
					  r.drive(0, DC::Rev);  
					  motor_zero = true;      
				  } else {
					  l.drive(usb.lt, DC::Rev);
					  r.drive(usb.lt, DC::Rev); 
					  motor_zero = true;
				  }    
			  }
			}
			if ((usb.lsx < dz_min) && (usb.lsx > analog_min)) {
				// left
        if (usb.digital & button.A) { 
         l.drive(usb.lt, DC::Rev);
         r.drive(DC::normalize<uint8_t, uint8_t>(usb.lsx, analog_min, dz_min, 0, usb.lt), DC::Rev);
         motor_zero = true;
        } else {  
			  	rear.ping();
				  if (rear.at_threshold()) {
				  	l.drive(0, DC::Rev);
				  	r.drive(0, DC::Rev);  
					  motor_zero = true;      
				  } else {
					  l.drive(usb.lt, DC::Rev);
				  	r.drive(DC::normalize<uint8_t, uint8_t>(usb.lsx, analog_min, dz_min, 0, usb.lt), DC::Rev);
				  	motor_zero = true;
				  }
        }
			}
			if ((usb.lsx > dz_max) && (usb.lsx < analog_max)) {
				// right
        if (usb.digital & button.A) { 
          l.drive(DC::normalize<uint8_t, uint8_t>((usb.lsx), dz_max, analog_max, 0, usb.lt), DC::Rev);
          r.drive(usb.lt, DC::Rev);
          motor_zero = true;
        } else {  
				  rear.ping();
				  if (rear.at_threshold()) {
					  l.drive(0, DC::Rev);
					  r.drive(0, DC::Rev);  
					  motor_zero = true;      
			  	} else {
					  l.drive(DC::normalize<uint8_t, uint8_t>((usb.lsx), dz_max, analog_max, 0, usb.lt), DC::Rev);
					  r.drive(usb.lt, DC::Rev);
				  	motor_zero = true;
				  }
        }
			}
			if (usb.lsx == analog_min) {
				// skid left
        if (usb.digital & button.A) { 
          l.drive(usb.lt, DC::For);
          r.drive(usb.lt, DC::Rev);
          motor_zero = true;
        } else {  
				  rear.ping();
			  	if (rear.at_threshold()) {
				  	l.drive(0, DC::For);
				  	r.drive(0, DC::Rev);  
				  	motor_zero = true;      
				  } else {
					  l.drive(usb.lt, DC::For);
				  	r.drive(usb.lt, DC::Rev);
				  	motor_zero = true;
			  	}
        }
			}
			if (usb.lsx == analog_max) {
				// skid right
        if (usb.digital & button.A) { 
            l.drive(usb.lt, DC::Rev);
            r.drive(usb.lt, DC::For);
            motor_zero = true;
        } else {  
				  rear.ping();
				  if (rear.at_threshold()) {
				  	l.drive(0, DC::Rev);
				  	r.drive(0, DC::Rev);  
				  	motor_zero = true;      
				  } else {
					  l.drive(usb.lt, DC::Rev);
					  r.drive(usb.lt, DC::For);
				  	motor_zero = true;
				  }
        }
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
		  if (usb.digital & button.A) {
		    servo::und_keine_eier();  
		  } else {
		    servo::tall();
		  }
      claw_state = 1;
	}
    if (usb.digital & button.RIGHT) {
		servo::load();
    claw_state = 2;
    }
    if (usb.digital & button.DOWN) {
		servo::pickup();
    claw_state = 3;
    }
    if (usb.digital & button.LEFT) {
		servo::look();
    }
  
	if (usb.digital & button.START) {
    l.drive(0, l.prev_dir());
    r.drive(0, r.prev_dir());
		mode = 2;
	}
}

void claw_mode() {
	if (usb.lsx) {
    if (claw_state == 1) {
      theta.set_pos(254 - usb.lsx, 0, 254);
    } else if (claw_state == 2) {
      theta.set_pos(DC::normalize<uint16_t, uint16_t>(254 - usb.lsx, 0, 254, 82, 100), 82, 100);
    } else if (claw_state == 3) {
      theta.set_pos(DC::normalize<uint16_t, uint16_t>(254 - usb.lsx, 0, 254, 0, 15), 0, 15);
    }
	}
	if (usb.lsy) {
		elbow.set_pos(usb.lsy, 0, 254);  
	}
	if (usb.rsy) {
		wrist.set_pos(usb.rsy, 0, 254);  
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
    delay(1000);
    claw_state = 1;
  }
  if (usb.digital & button.RIGHT) {
    servo::tall();
    delay(1000);
    claw_state = 2;
  }
  if (usb.digital & button.DOWN) {
    servo::tall();
    delay(1000);
    claw_state = 3;
  }
  
	if (usb.digital & button.START) {
		mode = 1;
	}
}

void setup() {
	Serial.begin(9600);
  
	mode = 1;
  claw_state = 1;
	servo::setup();
	claw.set_pos(claw.query_max());
	flood.toggle(HIGH);
}

void loop() {
	if (Serial.available() > 0) {

		if (Serial.read() == 0x02) {
			for (int i = 0; i < 8; ) {
				buf[i] = Serial.read();

				if ((buf[i] != -1) && (buf[i] != 0xFF)) {
					i++;
				}
			}
			usb.assign(buf);
			
			switch (mode) {
				case 1: drive_mode();
					      break;
				case 2: claw_mode();
					      break;
			}
		}
	}	
}
