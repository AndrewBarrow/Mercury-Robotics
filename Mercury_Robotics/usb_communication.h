#ifndef USB_COMMUNICATION_H
#define USB_COMMUNICATION_H

class Send {
private
	HardwareSerial& serial_;

public:
	Send(HardwareSerial& s) : serial_(s) 
	{ }
	
	template<typename T>
	void send(T input) {
		serial_.println(input);
	}
} send(Serial);

class Recieve {
private:
	HardwareSerial& serial_;
	uint16_t control_;
	uint16_t value_;
	
	void parser() {
		// parse incoming data and assign values to control_ and value_.
	}

public:
	Recieve(HardwareSerial& s) : serial_(s) 
	{ }
	
	void standby() {
		serial_.available();
	}
	
	uint16_t read() {
		// split Serial.read() into
		parser(serial_.read() - '0');
	}
} rec(Serial);

#endif