#include <led.h>

void setup() { }

void loop() {
	flood.toggle(HIGH);
	delay(3000);
	flood.toggle(LOW);
	delay(3000);
}
