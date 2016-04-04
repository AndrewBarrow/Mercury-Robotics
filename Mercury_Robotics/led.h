#ifndef LED_H
#define LED_H

class LED {
private:
	const uint8_t PIN;
	bool state_;
	
public:
	LED(uint8_t led_pin) : PIN(led_pin) {
		pinMode(PIN, OUTPUT);
		state_ = false;
	}
	
	void toggle(bool on) {
		state_ = on;
		digitalWrite(PIN, state_);
	}
	
	bool state() const {
		return state_;
	}
} flood(9), los(1);

#endif