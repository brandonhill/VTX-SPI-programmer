#ifndef _VTX_H_
#define _VTX_H_

#include <Arduino.h>
#include <SPI.h>

#define BANDS 5
#define CHANNELS_PER_BAND 8
#define LOG

class VTX {
public:
	VTX(uint8_t pinSelect);
	uint8_t incrementBand();
	uint8_t incrementChannel();
	void save();
private:
	uint8_t band = 0;
	uint8_t channel = 0;
	uint8_t pinSelect = 0;
};

#endif // _VTX_H_
