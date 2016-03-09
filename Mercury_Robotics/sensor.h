#ifndef SENSOR_H
#define SENSOR_H

/*
    Note to self for later:
        make sure we can override the sonar either by a button or otherwise
*/
class Sonar {
private:
	const uint8_t ECHO;
	const uint8_t TRIG;
	
	uint16_t duration_;
	uint16_t threshold_;
	uint16_t mid_threshold_;
	bool override_;   // use XOR(^) 1 to flip it on/off

public:
	Sonar(uint8_t echo_pin, uint8_t trig_pin) :
		ECHO(echo_pin),
		TRIG(trig_pin)
	{
		pinMode(ECHO, INPUT);
		pinMode(TRIG, OUTPUT);
		override_ = false;
	}
	
	Sonar(uint8_t echo_pin, uint8_t trig_pin, uint16_t threshold) :
		ECHO(echo_pin),
		TRIG(trig_pin),
		threshold_(threshold)
	{
		pinMode(ECHO, INPUT);
		pinMode(TRIG, OUTPUT);
		override_ = false;
	}

	Sonar(uint8_t echo_pin, uint8_t trig_pin, uint16_t middle_threshold, uint16_t threshold) :
		ECHO(echo_pin),
		TRIG(trig_pin),
		mid_threshold_(middle_threshold),
		threshold_(threshold)
	{
		pinMode(ECHO, INPUT);
		pinMode(TRIG, OUTPUT);
		override_ = false;
	}

	void ping() {
		digitalWrite(TRIG, HIGH);
		digitalWrite(TRIG, LOW);

		duration_ = pulseIn(ECHO, HIGH);
	}
	
	// returns result in cm
	uint16_t query_distance() const {
		return ((duration_ / 2) / 29.1);
	}
	
	void set_mid_threshold(uint16_t middle_threshold) {
		mid_threshold_ = middle_threshold;
	}

	uint16_t mid_threshold() const {
		return mid_threshold_;
	}

	bool at_mid_threshold() const {
		return (query_distance() <= mid_threshold_);
	}

	void set_threshold(uint16_t threshold) {
		threshold_ = threshold;
	}
	
	uint16_t threshold() const {
		return threshold_;
	}
	
	bool at_threshold() const {
		return (query_distance() <= threshold_);
	}

	void set_override(bool state) {
		override_ = state;
	}

	bool override() const {
		return override_;
	}
};

#endif
