download files and move them to a directory together
in that directory type
      npm install
into the command line
this will check the package.json object and install the required packages
then in command line type
      node chat.js
which will start the server, connect to the pi via its ip address and port 3000
ie
localhost:3000
or
192.168.1.xxx:3000
digital buttons are the upper 2 bytes and are mapped as follows
byte 1
		BACK||START||LB||RB||L3||R3
		BSLbRbL3R3
			(BACK)  {0b00100000;}
			(START) {0b00010000;}
			(LB)    {0b00001000;}
			(RB)    {0b00000100;}
			(L3)    {0b00000010;}
			(R3)    {0b00000001;}
byte 2
		(A||B||X||Y||UP||DOWN||LEFT||RIGHT)
		ABXYUDLR
			(B)     {0b01000000;}
			(X)     {0b00100000;}
			(Y)     {0b00010000;}
			(UP)    {0b00001000;}
			(DOWN)  {0b00000100;}
			(LEFT)  {0b00000010;}
			(RIGHT) {0b00000001;}
byte 3 => left stick y
byte 4 => left stick x
byte 5 => right stick y
byte 6 => right stick x
byte 7 => left trigger
byte 8 => right trigger

			
