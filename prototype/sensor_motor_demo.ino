#include <motor.h>
#include <sensor.h>

Sonar front(3, 2, 20);

void setup() { }

void loop() {
	front.ping();
	if (!(front.at_threshold())) {
		l.drive(0, DC::Forward);
		r.drive(0, DC::Forward);	
	} else {
		l.drive(255, DC::Forward);
		r.drive(255, DC::Forward);
	}
}
