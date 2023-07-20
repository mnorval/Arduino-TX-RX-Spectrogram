/*
* Arduino Wireless Communication Tutorial
*     Example 1 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

//COMM3
//#include <SPI.h>
//#include <nRF24L01.h>
//#include <RF24.h>

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define LED_PIN    9
#define LED_COUNT 24

Adafruit_NeoPixel strip_1(LED_COUNT, 9, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_2(LED_COUNT, 10, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_3(LED_COUNT, 11, NEO_GRB + NEO_KHZ800);

#define LED_POWER 250 //250;
#define WIPE_DELAY 0 //250;
#define THRESHOLD_1 40 //250;
#define THRESHOLD_2 30 //250;
#define THRESHOLD_3 15 //250;


#include "arduinoFFT.h"
 
#define SAMPLES 16             //SAMPLES-pt FFT. Must be a base 2 number. Max 128 for Arduino Uno.
#define SAMPLING_FREQUENCY 1024 //Ts = Based on Nyquist, must be 2 times the highest expected frequency.
 
arduinoFFT FFT = arduinoFFT();
 
unsigned int samplingPeriod;
unsigned long microSeconds;
 
double vReal[SAMPLES]; //create vector of size SAMPLES to hold real values
double vImag[SAMPLES]; //create vector of size SAMPLES to hold imaginary values

//RF24 radio(9, 10); // CE, CSN

//const byte address[6] = "00001";
//char text[64];

void setup() {
  Serial.begin(115200); //Baud rate for the Serial Monitor
  samplingPeriod = round(1000000*(1.0/SAMPLING_FREQUENCY)); //Period in microseconds 
  //radio.begin();
  //radio.openWritingPipe(address);
  //radio.setPALevel(RF24_PA_MIN);
  //radio.stopListening();
    strip_1.begin();           // INITIALIZE NeoPixel strip_1 object (REQUIRED)
    strip_1.show();            // Turn OFF all pixels ASAP
    strip_1.setBrightness(LED_POWER); // Set BRIGHTNESS to about 1/5 (max = 255)

    strip_2.begin();           // INITIALIZE NeoPixel strip_1 object (REQUIRED)
    strip_2.show();            // Turn OFF all pixels ASAP
    strip_2.setBrightness(LED_POWER); // Set BRIGHTNESS to about 1/5 (max = 255)

    strip_3.begin();           // INITIALIZE NeoPixel strip_1 object (REQUIRED)
    strip_3.show();            // Turn OFF all pixels ASAP
    strip_3.setBrightness(LED_POWER); // Set BRIGHTNESS to about 1/5 (max = 255)
}

void loop() {
//************FFT******************
 /*Sample SAMPLES times*/
    for(int i=0; i<SAMPLES; i++)
    {
        microSeconds = micros();    //Returns the number of microseconds since the Arduino board began running the current script. 
     
        vReal[i] = analogRead(0); //Reads the value from analog pin 0 (A0), quantize it and save it as a real term.
        vImag[i] = 0; //Makes imaginary term 0 always

        /*remaining wait time between samples if necessary*/
        while(micros() < (microSeconds + samplingPeriod))
        {
          //do nothing
        }
    }
 
    /*Perform FFT on samples*/
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
//************FFT******************
//int Threshold = 1450; 
//int MapTo = 255;
//float Divide = 15;

//Serial.print(map(vReal[0], 0, Threshold, 0, 255));Serial.print(" ");
//Serial.print(map(vReal[1], 0, Threshold, 0, 255));Serial.print(" ");
//Serial.print(map(vReal[2], 0, Threshold, 0, 255));Serial.print(" ");

//uint8_t STRIP_1_VALUE= map(vReal[3], 0, Threshold, 0, MapTo);
//uint8_t STRIP_2_VALUE= map(vReal[4], 0, Threshold, 0, MapTo);
//uint8_t STRIP_3_VALUE= map(vReal[5], 0, Threshold, 0, MapTo);


uint8_t STRIP_1_1_VALUE= vReal[2]/THRESHOLD_1;
uint8_t STRIP_1_2_VALUE= vReal[3]/THRESHOLD_1;
uint8_t STRIP_1_3_VALUE= vReal[4]/THRESHOLD_1;

uint8_t STRIP_2_1_VALUE= vReal[5]/THRESHOLD_2;
uint8_t STRIP_2_2_VALUE= vReal[6]/THRESHOLD_2;
uint8_t STRIP_2_3_VALUE= vReal[7]/THRESHOLD_2;

uint8_t STRIP_3_1_VALUE= vReal[8]/THRESHOLD_3;
uint8_t STRIP_3_2_VALUE= vReal[9]/THRESHOLD_3;
uint8_t STRIP_3_3_VALUE= vReal[10]/THRESHOLD_3;

/*
Serial.print(0);Serial.print(" ");

Serial.print(STRIP_1_1_VALUE);Serial.print(" ");
Serial.print(STRIP_1_2_VALUE);Serial.print(" ");
Serial.print(STRIP_1_3_VALUE);Serial.print(" ");

Serial.print(STRIP_2_1_VALUE);Serial.print(" ");
Serial.print(STRIP_2_2_VALUE);Serial.print(" ");
Serial.print(STRIP_2_3_VALUE);Serial.print(" ");

Serial.print(STRIP_3_1_VALUE);Serial.print(" ");
Serial.print(STRIP_3_2_VALUE);Serial.print(" ");
Serial.print(STRIP_3_3_VALUE);

Serial.print(100);Serial.print(" ");
Serial.println();
*/


colorWipe_1(strip_1.Color(STRIP_1_1_VALUE, STRIP_1_2_VALUE,   STRIP_1_3_VALUE),WIPE_DELAY);
colorWipe_2(strip_2.Color(STRIP_2_1_VALUE, STRIP_2_2_VALUE,   STRIP_2_3_VALUE),WIPE_DELAY);
colorWipe_3(strip_3.Color(STRIP_3_1_VALUE, STRIP_3_2_VALUE,   STRIP_3_3_VALUE),WIPE_DELAY);

//colorWipe_1(strip_1.Color(0,0,0),0);
//colorWipe_1(strip_2.Color(0,0,0),0);
//colorWipe_1(strip_3.Color(0,0,0),0);




delay(5);

//const char text2[] = "RX2_SEQ_1";
//radio.write(&text2, sizeof(text2));
//delay(1000);

//const char text3[] = "RX3_SEQ_1";
//radio.write(&text3, sizeof(text3));
//delay(1000);

}

// Fill the dots one after the other with a color
void colorWipe_1(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip_1.numPixels(); i++) {
    strip_1.setPixelColor(i, c);
    strip_1.show();
    delay(wait);
  }
}

// Fill the dots one after the other with a color
void colorWipe_2(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip_2.numPixels(); i++) {
    strip_2.setPixelColor(i, c);
    strip_2.show();
    delay(wait);
  }
}

// Fill the dots one after the other with a color
void colorWipe_3(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip_3.numPixels(); i++) {
    strip_3.setPixelColor(i, c);
    strip_3.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip_1.numPixels(); i++) {
      strip_1.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip_1.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip_1.numPixels(); i++) {
      strip_1.setPixelColor(i, Wheel(((i * 256 / strip_1.numPixels()) + j) & 255));
    }
    strip_1.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip_1.numPixels(); i=i+3) {
        strip_1.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip_1.show();

      delay(wait);

      for (uint16_t i=0; i < strip_1.numPixels(); i=i+3) {
        strip_1.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow_1(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip_1.numPixels(); i=i+3) {
        strip_1.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip_1.show();

      delay(wait);

      for (uint16_t i=0; i < strip_1.numPixels(); i=i+3) {
        strip_1.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow_2(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip_2.numPixels(); i=i+3) {
        strip_2.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip_2.show();

      delay(wait);

      for (uint16_t i=0; i < strip_2.numPixels(); i=i+3) {
        strip_2.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip_1.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip_1.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip_1.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
