#include "VTX.h"

// frequencies
const uint16_t frequencies[] PROGMEM = {
	// A
	0x7981, // 5865
	0x758D, // 5845
	0x7199, // 5825
	0x6DA5, // 5805
	0x69B1, // 5785
	0x65BD, // 5765
	0x6209, // 5745
	0x5E15, // 5725
	// B
	0x5F9D, // 5733
	0x6338, // 5752
	0x6713, // 5771
	0x6AAE, // 5790
	0x6E89, // 5809
	0x7224, // 5828
	0x75BF, // 5847
	0x799A, // 5866
	// C
	0x510A, // 5658
	0x5827, // 5695
	0x5F84, // 5732
	0x66A1, // 5769
	0x6DBE, // 5806
	0x751B, // 5843
	0x7C38, // 5880
	0x8395, // 5917
	// E
	0x5A21, // 5705
	0x562D, // 5685
	0x5239, // 5665
	0x4E85, // 5645
	0x7D35, // 5885
	0x8129, // 5905
	0x851D, // 5925
	0x8911, // 5945
	// F
	0x610C, // 5740
	0x6500, // 5760
	0x68B4, // 5780
	0x6CA8, // 5800
	0x709C, // 5820
	0x7490, // 5840
	0x7884, // 5860
	0x7C38  // 5880
};

VTX::VTX(uint8_t _pinSelect) {
	
	// set select pin
	this->pinSelect = _pinSelect;
	pinMode(this->pinSelect, OUTPUT);
	
	// init SPI
	SPI.begin();
}

uint8_t VTX::incrementBand() {
	this->band = this->band >= BANDS - 1 ? 0 : this->band + 1;
	return this->band;
}

uint8_t VTX::incrementChannel() {
	this->channel = this->channel >= CHANNELS_PER_BAND - 1 ? 0 : this->channel + 1;
	return this->channel;
}

void VTX::save() {
	
	#ifdef LOG
		Serial.print("Setting band ");
		Serial.print(this->band + 1);
		Serial.print(", channel ");
		Serial.println(this->channel + 1);
	#endif
	
	// look up frequency
	uint32_t data = (pgm_read_word_near(frequencies + (band * CHANNELS_PER_BAND + channel)));
	
	// write via SPI
	digitalWrite(this->pinSelect, LOW);
	SPI.transfer(0x01);
	SPI.transfer(data + 0x00040000);
	digitalWrite(this->pinSelect, HIGH); 
}
