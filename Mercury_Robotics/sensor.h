#ifndef SENSOR_H
#define SENSOR_H

class Sonar {
private:
	const uint8_t ECHO;
	const uint8_t TRIG;
	
	uint16_t duration_;
	uint16_t threshold_;
	uint16_t mid_threshold_;
	bool override_;

public:
	///	Construct an sonar object to represent a sonar on the bot.
	///	INPUT: echo pin on the Arduino
	///		   trigger pin on the Arduino
	///		   safety threshold(s) (cm)
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
		ECHO( echo_pin),
		TRIG(trig_pin),
		mid_threshold_(middle_threshold),
		threshold_(threshold)
	{
		pinMode(ECHO, INPUT);
		pinMode(TRIG, OUTPUT);
		override_ = false;
	}
	
	///	"Pings" the sonar device and stores the length of the pulse (μs) in duration_. 
	void ping() {
		digitalWrite(TRIG, HIGH);
		digitalWrite(TRIG, LOW);

		duration_ = pulseIn(ECHO, HIGH);
	}
	
	///	Query the distance of the sonar pulse.
	///	RETURN: pulse distance (cm)
	uint16_t query_distance() const {
		return ((duration_ / 2) / 29.1);
	}
	
	///	Set the safety threhold mark.
	///	INPUT: threshold distance (cm)
	void set_threshold(uint16_t threshold) {
		threshold_ = threshold;
	}
	void set_mid_threshold(uint16_t middle_threshold) {
		mid_threshold_ = middle_threshold;
	}
	
	uint16_t threshold() const {
		return threshold_;
	}
	uint16_t mid_threshold() const {
		return mid_threshold_;
	}

	///	Check whether or not the pulse has exceed the safety threshold.
	bool at_threshold() const {
		return (query_distance() <= threshold_);
	}
	bool at_mid_threshold() const {
		return (query_distance() <= mid_threshold_);
	}

	///	Set an override to be used to disregard the sonar ping.
	/// INPUT: override state
	void set_override(bool state) {
		override_ = state;
	}

	bool override() const {
		return override_;
	}
};

class Encoder {
	/*
		here lies my hopes and dreams for an encoder.
		
		:'(
	*/
};

#endif