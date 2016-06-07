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
	
	/// Normalize a number from one range of values to another.
	///	INPUT:	number to normalize
	///		original range minimum
	///		original range maximum
	///        	new range minimum
	///		new range maximum
	template <typename T, typename N>
	inline static N normalize(T value, T min, T max, N norm_min = 0, N norm_max = 255) {
		return (((norm_max - norm_min) * ((float)(value - min) / (float)(max - min))) + norm_min);
	}

public:
	///	Construct an servo object to represent a servo on the bot.
	///	INPUT:	servo pin number on the Servo Shield
	///		minimum range of motion of the servo between 0 and 4096 (used to prevent damage to the servo)
	///		maximum range of motion of the servo between 0 and 4096 (used to prevent damage to the servo)
	///		I2C address
	Servo(uint8_t servo_pin_number, uint16_t servo_min, uint16_t servo_max, uint8_t addr = 0x40) : 
		PIN(servo_pin_number), 
		MIN(servo_min), 
		MAX(servo_max), 
		i2c_addr_(addr) 
	{ }
	
	///	Establishes I2C communications with the Servo Shield.
	///	NOTE:	Use servo::setup() below to quickly setup I2C for all servos
	void begin() {
		Wire.begin();
		reset();
	}
	
	///	Resets I2C communications.
	void reset() {
		write8(0x0, 0x0);
	}
	
	///	Set the frequency for a servo.
	///	INPUT:	frequency (Hz) from 40 to 1000
	///	NOTE:	Use servo::setup() below to quickly setup I2C for all servos
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
	
	///	Move servo to a certain position.
	///	INPUT:	position from range_min to range_max
	///		servo minimum range
	///		servo maximum range
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

	uint16_t query_max() const { return MAX; }
	
	uint16_t query_min() const { return MIN; }	
	
} claw(10, 325, 500), elbow(12, 160, 500), theta(8, 115, 500), wrist(11, 200, 550), cata(9, 115, 300);

namespace servo {
///	Quickly establishes I2C communications and sets the frequency for each servo on the bot.
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

///	Quick selction positions.
void tall() {
	theta.set_pos(480, theta.query_min(), theta.query_max());
	elbow.set_pos(330, elbow.query_min(), elbow.query_max());
	wrist.set_pos(235, wrist.query_min(), wrist.query_max());
}
void pickup() {
	theta.set_pos(469, theta.query_min(), theta.query_max());
	elbow.set_pos(160, elbow.query_min(), elbow.query_max());
	wrist.set_pos(450, wrist.query_min(), wrist.query_max());		
}	
void look() {	
	theta.set_pos(469, theta.query_min(), theta.query_max());
	elbow.set_pos(220, elbow.query_min(), elbow.query_max());
	wrist.set_pos(510, wrist.query_min(), wrist.query_max());	
}
void load() {
	theta.set_pos(235, theta.query_min(), theta.query_max());
	elbow.set_pos(350, elbow.query_min(), elbow.query_max());
	delay(1000);
	wrist.set_pos(550, wrist.query_min(), wrist.query_max());	
}
void und_keine_eier() {
	theta.set_pos(469, theta.query_min(), theta.query_max());
	elbow.set_pos(230, elbow.query_min(), elbow.query_max());
	wrist.set_pos(250, wrist.query_min(), wrist.query_max());		
}

} // namespace servo

class DC {
private:
    const uint8_t MOTOR;
    const uint8_t DIRECTION;
	float modifier_;
    bool prev_dir_;
    
public:
	/// Boolean enum to be used in drive() below.
	enum Direction : bool { For = 1, Rev = 0 };

	///	Construct an DC motor object to represent a DC motor on the bot.
	///	INPUT:	motor pin on the Arduino
	///		direction pin on the Arduino
	///		value to modify the PWM being sent to the motor driver board (to check the bot driving straight)
	DC(uint8_t motor_pin, uint8_t direction_pin, float modifier) :
		MOTOR(motor_pin),
		DIRECTION(direction_pin),
		modifier_(modifier)
    	{
        	pinMode(MOTOR, OUTPUT);
        	pinMode(DIRECTION, OUTPUT);
    	}
    
	///	Turns the DC motor on at desired speed and direction.
	///	INPUT:	speed from 0 to 254
	///		direction, forwards (For) or backwards (Rev)
	///	NOTE:	Once turned on the DC motor does not stop until the speed is set back to 0
	void drive(uint8_t pwm, bool direction = 1) {
		if (pwm > 254) {
			pwm = 254;
		} else if (pwm < 0) {
			pwm = 0;
		}
		
		prev_dir_ = direction;
		digitalWrite(DIRECTION, direction);
        analogWrite(MOTOR, pwm * modifier_);
    }
    	
	///	Returns the last inputed direction.
    bool prev_dir() const {
    	return prev_dir_;
    }
	
	/// Normalize a number from one range of values to another.
	///	INPUT:	number to normalize
	///		original range minimum
	///		original range maximum
	///		new range minimum
	///		new range maximum
	template <typename T, typename N>
	inline static N normalize(T value, T min, T max, N norm_min = 0, N norm_max = 255) {
		return (((norm_max - norm_min) * ((float)(value - min) / (float)(max - min))) + norm_min);
	}
} l(5, 4, 1.0), r(6, 7, 0.9);

#endif
