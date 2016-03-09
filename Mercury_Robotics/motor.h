#ifndef MOTOR_H
#define MOTOR_H

#include <Wire.h>

class Servo {
private:
	uint8_t i2c_addr_;
	
	const uint8_t PIN;
	const uint16_t MAX;
	const uint16_t MIN;
	
	uint8_t read8(uint8_t addr) {
		Wire.beginTransmission(i2c_addr_);
		Wire.write(addr);
		Wire.endTransmission();
		Wire.requestFrom((uint8_t)i2c_addr_, (uint8_t)1);
		
		return Wire.read();
	}
	
	void write8(uint8_t addr, uint8_t d) {
		Wire.beginTransmission(i2c_addr_);
		Wire.write(addr);
		Wire.write(d);
		Wire.endTransmission();
	}
	
	void set_pwm(uint8_t num, uint16_t on, uint16_t off) {
		Wire.beginTransmission(i2c_addr_);
		Wire.write(0x6 + 4 * num);
		Wire.write(on);
		Wire.write(on >> 8);
		Wire.write(off);
		Wire.write(off >> 8);
		Wire.endTransmission();
	}
	
	template <typename T, typename N>
	inline static N normalize(T value, T min, T max, N norm_min = 0, N norm_max = 255) {
		return (((norm_max - norm_min) * ((float)(value - min) / (float)(max - min))) + norm_min);
	}

public:
	Servo(uint8_t servo_pin_number, uint16_t servo_min, uint16_t servo_max, uint8_t addr = 0x40) : 
		PIN(servo_pin_number), 
		MIN(servo_min), 
		MAX(servo_max), 
		i2c_addr_(addr) 
	{ }

	void begin() {
		Wire.begin();
		reset();
	}
	
	void reset() {
		write8(0x0, 0x0);
	}
	
	void set_freq(float freq = 60) {
		freq = freq * 0.9;
		float prescaleval = 25000000;
		
		prescaleval = prescaleval / 4096;
		prescaleval = prescaleval / freq;
		prescaleval = prescaleval - 1;
		
		uint8_t prescale = floor(prescaleval + 0.5);
		
		uint8_t oldmode = read8(0x0);
		uint8_t newmode = (oldmode & 0x7F) | 0x10;
		write8(0x0, newmode);
		write8(0xFE, prescale);
		write8(0x0, oldmode);
		delay(5);
		write8(0x0, oldmode | 0xa1);
	}
	
	void set_pos(uint16_t position, uint16_t range_min = 0, uint16_t range_max = 100) {
		if (position > range_max) {
			position = range_max;
		} else if (position < range_min) {
			position = range_min;
		}
		
		if ((range_min == MIN) && (range_max == MAX)) {
			set_pwm(PIN, 0, position);
		} else {
			set_pwm(PIN, 0, normalize<uint16_t, uint16_t>(position, range_min, range_max, MIN, MAX));
		}
	
	}
	
	void drive_servo(uint16_t speed) {
		uint16_t pulse = MAX - MIN;
		
		if (speed != 0) {
			pulse = (speed * (MAX - (MAX - MIN))) + (MAX - MIN);
		}
		set_pwm(PIN, 0, pulse);
	}
	
	// you can use this function if you'd like to set the pulse length in seconds
	// e.g. setServoPulse(0, 0.001) is a ~1 millisecond pulse width. its not precise!
	void setServoPulse(double pulse) {
		double pulselength;
  
		pulselength = 1000000;   // 1,000,000 us per second
		pulselength /= 60;   // 60 Hz
		pulselength /= 4096;  // 12 bits of resolution
		pulse *= 1000;
		pulse /= pulselength;
		set_pwm(PIN, 0, pulse);
}
	
	void set_pin(uint8_t num, uint16_t val, bool invert = false) {
		val = min(val, 4095);
		if (invert) {
			if (val == 0) {
				set_pwm(num, 4096, 0);
			} else if (val == 4095) {
				set_pwm(num, 0, 4096);
			} else {
				set_pwm(num, 0, 4095 - val);
			}
		} else {
			if (val == 4095) {
				set_pwm(num, 4096, 0);
			} else if (val == 0) {
				set_pwm(num, 0, 4096);
			} else {
				set_pwm(num, 0, val);
			}
		}
	}

	uint16_t query_max() const { return MAX; }
	
	uint16_t query_min() const { return MIN; }	
	
} claw(10, 325, 500), elbow(12, 160, 500), theta(8, 115, 500), wrist(11, 130, 550), cata(9, 115, 300);

/*
	move this namespace to a new "general" header for these sorts of things.
*/
namespace servo {
void setup() {
  claw.begin();
  claw.set_freq();
  elbow.begin();
  elbow.set_freq();
  theta.begin();
  theta.set_freq();
  wrist.begin();
  wrist.set_freq();
  cata.begin();
  cata.set_freq();
}

void tall() {
	theta.set_pos(480, theta.query_min(), theta.query_max());
	elbow.set_pos(340, elbow.query_min(), elbow.query_max());
	wrist.set_pos(420, wrist.query_min(), wrist.query_max());
}
	
void pickup() {
	theta.set_pos(480, theta.query_min(), theta.query_max());
	elbow.set_pos(160, elbow.query_min(), elbow.query_max());
	wrist.set_pos(225, wrist.query_min(), wrist.query_max());		
}
	
void look() {
	theta.set_pos(480, theta.query_min(), theta.query_max());
	elbow.set_pos(160, elbow.query_min(), elbow.query_max());
	wrist.set_pos(420, wrist.query_min(), wrist.query_max());
}
	
void load() {
	theta.set_pos(235, theta.query_min(), theta.query_max());
	elbow.set_pos(350, elbow.query_min(), elbow.query_max());
	delay(1000);
	wrist.set_pos(140, wrist.query_min(), wrist.query_max());	
}

} // namespace servo

class DC {
private:
    const uint8_t MOTOR;
    const uint8_t DIRECTION;
    bool prev_dir_;
    
public:
	enum Direction : bool { For = 1, Rev = 0 };

	DC(uint8_t motor_pin, uint8_t direction_pin) :
		MOTOR(motor_pin),
        	DIRECTION(direction_pin)
    	{
        	pinMode(MOTOR, OUTPUT);
        	pinMode(DIRECTION, OUTPUT);
    	}
    
	// pwm value is from 0 - 255
	void drive(uint8_t pwm, bool direction = 1) {
		prev_dir_ = direction;
		digitalWrite(DIRECTION, direction);
        	analogWrite(MOTOR, pwm);
    	}
    	
    	bool prev_dir() const {
    		return prev_dir_;
    	}
	
	template <typename T, typename N>
	inline static N normalize(T value, T min, T max, N norm_min = 0, N norm_max = 255) {
		return (((norm_max - norm_min) * ((float)(value - min) / (float)(max - min))) + norm_min);
	}
} l(5, 4), r(6, 7);

#endif
