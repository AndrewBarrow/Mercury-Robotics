CHANGELOG

led.h
	2/22/2016 (Barrow)
		-inital check-in

motor.h
	4/4/2016 (Barrow)
		Servo class
			- removed methods drive_servo(), setServoPulse(), and set_pin()
	3/1/2016 (Barrow)
		DC class
			- added bool prev_dir_ variable to hold the last direction used
			- added prev_dir() function to return prev_dir_
			- prev_dir_ is set in drive()
	2/15/2016 (Barrow)
		DC class
			- added enum Direction for forwards and reverse
	2/11/2016 (Barrow)
		DC class
			- added DC class to control the DC motor
			- added drive() function to move a motor forwards or backwards at a set pwm
			- added normalize() function to normalize controller value to the pwm (0 - 255)
		namespace servo
			- created namespace servo for "loose" functions
		Servo class
			- placed servo_setup() in the namespace servo
			- added normalize() function in the Servo class to normalize a (0 - 255) number to the servo (MIN - MAX) range
	2/10/2016 (Barrow)
		Servo class
			- renamed the class Servo_Driver to Servo
			- made variables MAX and MIN private and added access functions max() and min() to return their values
	2/2/2016 (Barrow)
		- initial check-in
	
sensor.h
	3/1/2016 (Barrow)
		Sonar class
			- Renamed mid_threshold() to at_mid_threshold()
			- Renamed query_mid_threshold() to mid_threshold()
			- Renamed mid_threshold() to at_mid_threshold()
			- Renamed query_threshold() to threshold()
			- Renamed threshold() to at_threshold()
	2/22/2016 (Barrow)
		Sonar class
			- added mid_threshold_ variable for side sensors
			- added additonal constructor that assigns mid_threshold_
			- added query_mid_threshold(), mid_threshold(), and set_mid_threshold()
	2/12/2016 (Barrow)
		Sonar class
			- added override_ variable of type bool
			- added function set_override() to change override state
			- added function override() to check whether or not to override sensors
			- set override_ to FALSE in the constructor
	2/11/2016 (Barrow)
		Sonar class
			- moved duration_ assignment to ping()
			- added query_threshold() to return threshold_
			- made ECHO and TRIG of type uint8_t
	2/10/2016 (Barrow)
		- renamed the header from sonar.h to sensor.h
	2/6/2016 (Barrow)
		Sonar class
			- added an additional constructor for Sonar class
			- added the variable threshold_
			- added set_threshold() to change threshold_
			- added threshold() to check if we have reached the threshold distance
	2/5/2016 (Barrow)
		- initial check-in
		- based off the example provided by Nick
		
usb_com.h
	4/4/2016 (Barrow)
		- initial check-in
		USB_Input struct
			- added variables to store digital and analog buttons
			- added assign() to assign our buffer cells to the various button variables
		Digital_Button_Mask struct
			- created masks for the XboxOne buttons
