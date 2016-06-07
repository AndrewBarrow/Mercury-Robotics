#ifndef LED_H
#define LED_H

class LED {
private:
	const uint8_t PIN;
	bool state_;
	
public:
	///	Construct an LED object to represent a LED on the bot.
	///	INPUT:	LED pin number on the Arduino
	LED(uint8_t led_pin) : PIN(led_pin) {
		pinMode(PIN, OUTPUT);
		state_ = false;
	}
	
	///	Turn LED light on or off.
	///	INPUT:	LED state
	void toggle(bool on) {
		state_ = on;
		digitalWrite(PIN, state_);
	}
	
	bool state() const {
		return state_;
	}
} flood(9), los(1);

#endif
