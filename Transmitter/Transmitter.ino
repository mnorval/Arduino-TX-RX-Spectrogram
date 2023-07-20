/*
* Arduino Wireless Communication Tutorial
*     Example 1 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

//COMM3
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include "arduinoFFT.h"
 
#define SAMPLES 16             //SAMPLES-pt FFT. Must be a base 2 number. Max 128 for Arduino Uno.
#define SAMPLING_FREQUENCY 1024 //Ts = Based on Nyquist, must be 2 times the highest expected frequency.
 
arduinoFFT FFT = arduinoFFT();
 
unsigned int samplingPeriod;
unsigned long microSeconds;
 
double vReal[SAMPLES]; //create vector of size SAMPLES to hold real values
double vImag[SAMPLES]; //create vector of size SAMPLES to hold imaginary values

RF24 radio(9, 10); // CE, CSN

const byte address[6] = "00001";
char text[64];

void setup() {
  Serial.begin(115200); //Baud rate for the Serial Monitor
  samplingPeriod = round(1000000*(1.0/SAMPLING_FREQUENCY)); //Period in microseconds 
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
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
int Threshold = 350; 
int MapTo = 100;

//Serial.print(map(vReal[3], 0, Threshold, 0, 255));Serial.print(" ");
//Serial.print(map(vReal[4], 0, Threshold, 0, 255));Serial.print(" ");
//Serial.print(map(vReal[5], 0, Threshold, 0, 255));//Serial.print(" ");

//Serial.println();
float one_ = 1.5;
float two_ = 1.5;
float three_ = 1.5;

char TestString_1[64] = "000000000_000000000_000000000";
uint8_t RX1_1= map(vReal[3], 0, Threshold, 0, MapTo)/one_;
uint8_t RX1_2= map(vReal[4], 0, Threshold, 0, MapTo)/one_;
uint8_t RX1_3= map(vReal[5], 0, Threshold, 0, MapTo)/one_;
TestString_1[0]=(RX1_1 / 100) + '0';
TestString_1[1]=((RX1_1 / 10) % 10) + '0';
TestString_1[2]=(RX1_1 % 10) + '0';
TestString_1[3]=(RX1_2 / 100) + '0';
TestString_1[4]=((RX1_2 / 10) % 10) + '0';
TestString_1[5]=(RX1_2 % 10) + '0';
TestString_1[6]=(RX1_3 / 100) + '0';
TestString_1[7]=((RX1_3 / 10) % 10) + '0';
TestString_1[8]=(RX1_3 % 10) + '0';
//Serial.print("RX1:");Serial.print(RX1_1);Serial.print("   :TestString:   ");Serial.println(TestString);
//radio.write(&text1, sizeof(text1));


//char TestString_2[32] = "RX2_SEQ_1_000_000_000";
RX1_1= map(vReal[6], 0, Threshold, 0, MapTo)*two_;
RX1_2= map(vReal[7], 0, Threshold, 0, MapTo)*two_;
RX1_3= map(vReal[8], 0, Threshold, 0, MapTo)*two_;
TestString_1[10]=(RX1_1 / 100) + '0';
TestString_1[11]=((RX1_1 / 10) % 10) + '0';
TestString_1[12]=(RX1_1 % 10) + '0';
TestString_1[13]=(RX1_2 / 100) + '0';
TestString_1[14]=((RX1_2 / 10) % 10) + '0';
TestString_1[15]=(RX1_2 % 10) + '0';
TestString_1[16]=(RX1_3 / 100) + '0';
TestString_1[17]=((RX1_3 / 10) % 10) + '0';
TestString_1[18]=(RX1_3 % 10) + '0';
//Serial.print("RX1:");Serial.print(RX1_1);Serial.print("   :TestString:   ");Serial.println(TestString);
//radio.write(&text1, sizeof(text1));
//radio.write(TestString_2,32);


//char TestString_3[32] = "RX3_SEQ_1_000_000_000";
RX1_1= map(vReal[9], 0, Threshold, 0, MapTo)*three_;
RX1_2= map(vReal[10], 0, Threshold, 0, MapTo)*three_;
RX1_3= map(vReal[11], 0, Threshold, 0, MapTo)*three_;
TestString_1[20]=(RX1_1 / 100) + '0';
TestString_1[21]=((RX1_1 / 10) % 10) + '0';
TestString_1[22]=(RX1_1 % 10) + '0';
TestString_1[23]=(RX1_2 / 100) + '0';
TestString_1[24]=((RX1_2 / 10) % 10) + '0';
TestString_1[25]=(RX1_2 % 10) + '0';
TestString_1[26]=(RX1_3 / 100) + '0';
TestString_1[27]=((RX1_3 / 10) % 10) + '0';
TestString_1[28]=(RX1_3 % 10) + '0';
//Serial.print("RX1:");Serial.print(RX1_1);Serial.print("   :TestString:   ");Serial.println(TestString);
//radio.write(&text1, sizeof(text1));
//radio.write(TestString_3,32);
radio.write(TestString_1,64);



delay(5);

//const char text2[] = "RX2_SEQ_1";
//radio.write(&text2, sizeof(text2));
//delay(1000);

//const char text3[] = "RX3_SEQ_1";
//radio.write(&text3, sizeof(text3));
//delay(1000);

}


/*
void transmit(String value, int delay_)
{
  const char text[] = char(value);
  radio.write(&text, sizeof(text));
  delay(delay_);
}
*/
