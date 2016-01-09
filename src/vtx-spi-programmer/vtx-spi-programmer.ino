#include <SPI.h>
#include "config.h"
#include "VTX.h"

enum ledBlinkLength {
	LONG,
	SHORT
};

uint32_t btnDownLast = 0;
uint8_t ledBlinkLength;
uint32_t ledBlinkNext = 0;
uint8_t ledBlinks = 0;
uint8_t ledOn = 0;
VTX vtx = VTX(PIN_SPI_SELECT);

void setup() {
	
	#ifdef DEBUG
	Serial.begin(9600);
	#endif
	
	// button
	pinMode(PIN_BTN, INPUT);
	digitalWrite(PIN_BTN, LOW);
	
	// LED
	pinMode(PIN_LED, OUTPUT);
}

void loop() {
	
	// user feedback
	blinkLED();
	
	// watch button
	checkButton();
}

void blinkLED() {
	
	uint32_t now = millis();
	
	// turn off
	if (ledOn && now > ledBlinkNext) {
		ledOn = 0;
		digitalWrite(PIN_LED, LOW);
		
		// decrement counter
		if (ledBlinks > 0) {
			ledBlinks -= 1;
			ledBlinkNext = now + (1000 - (ledBlinkLength == LONG ? LED_MILLIS_LONG : LED_MILLIS_SHORT));
		}
		
	// turn on
	} else if (ledBlinks && !ledOn && now > ledBlinkNext) {
		ledBlinkNext = now + (ledBlinkLength == LONG ? LED_MILLIS_LONG : LED_MILLIS_SHORT);
		ledOn = 1;
		digitalWrite(PIN_LED, HIGH);
	}
}

void checkButton() {
	
	uint8_t btnPressed = digitalRead(PIN_BTN);
	
	// press started
	if (btnDownLast == 0 && btnPressed) {
		btnDownLast = millis();
		ledBlinkNext = 0;
		ledBlinks = 0;
		
	// press ended
	} else if (btnDownLast > 0 && !btnPressed) {
		uint32_t pressLength = millis() - btnDownLast;
		
		// long press - increment band, blink number
		if (pressLength > BTN_MILLIS_LONG) {
			ledBlinkLength = LONG;
			ledBlinks = vtx.incrementBand() + 1;
			vtx.save();
			
		// short press - increment channel, blink number
		} else if (pressLength > BTN_MILLIS_SHORT) {
			ledBlinkLength = SHORT;
			ledBlinks = vtx.incrementChannel() + 1;
			vtx.save();
		}
		
		btnDownLast = 0;
	}
}
