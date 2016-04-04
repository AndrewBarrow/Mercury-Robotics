#ifndef USB_COM_H
#define USB_COM_H

struct USB_Input {
	uint16_t digital;
	uint16_t lsy;	// make it uint8_t?
	uint16_t lsx;	// make it uint8_t?
	uint16_t rsy;	// make it uint8_t?
	uint16_t rsx;	// make it uint8_t?
	uint16_t lt;	// make it uint8_t?
	uint16_t rt;	// make it uint8_t?

	void assign(uint8_t b[]) {
		digital = ((b[0] << 8) + b[1]);
		lsy = b[2];
		lsx = b[3];
		rsy = b[4];
		rsx = b[5];
		lt = b[6];
		rt = b[7];
	}
} usb;

struct Digital_Button_Mask {
	uint16_t BACK = 0x2000;
	uint16_t START = 0x1000;
	uint16_t LB = 0x0800;
	uint16_t RB = 0x0400;
	uint16_t L3 = 0x0200;
	uint16_t R3 = 0x0100;
	
	uint8_t A = 0x80;
	uint8_t B = 0x40;
	uint8_t X = 0x20;
	uint8_t Y = 0x10;
	uint8_t UP = 0x08;
	uint8_t DOWN = 0x04;
	uint8_t LEFT = 0x02;
	uint8_t RIGHT = 0x01;
} button;
#endif