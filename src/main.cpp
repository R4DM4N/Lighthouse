#include <FastLED.h>

#define LED_PIN  8
#define NUM_LEDS_IN_STRING 16
#define NUM_LEDS 36 //4 candle + 16Lighthouse animation + 16Lighthouse animation 
#define NUM_CANDLES 4
#define MEDBRIGHTNESS 150
#define LEDTYPE WS2812B
#define COLOR_ORDER GRB
#define NUM_ANIMATION_STRINGS 2

void fadeDown();
void LEDAnimationString(LEDAnimationString*);

typedef struct {
  int fadeCount = 0;
  int leadingLightBrightness = 0;
  int LEDIndex = 0;
  CRGB *leds;
  
} LEDAnimationString;

CRGB leds[NUM_LEDS];
LEDAnimationString LEDAnimationsStrings[NUM_ANIMATION_STRINGS];

//Setup Delay Timer Variables
int delayTimer = 0;  //set lighthouse delay timer between light rotation pulses
int leadingLightBrightness2;

boolean LedChange = false;   //Initialise flage to call fastled.show only when a led have changed

//initilize rotation variables
int leadingLightBrightness = 0;
int FirstRotatingLedLight1 = 0;
int iRotationLedDecay = 100;    //number of scans before fn fadeled is called to smooth animation

//initilaze candlearrays
int CandleArray[NUM_CANDLES][9];//LED,Count Down timer Variable,  hue constant,  saturation constant, v Variable,  lo time, hi time, rndlowv, rndhiv,
int ITCandleTimer[] = {10, 20, 30, 40, 50,20, 30, 10, 20, 30, 40, 50, 20, 30};// initialize CandleTimer Count Down timer arrays global
int IVCandleArray[] = {10 ,20 ,255 ,255 ,50,20 ,255,20 ,255 ,255 ,50,20 ,255,255};

void LEDAnimation(LEDAnimationString *LEDString){
  if(LEDString->LEDIndex % NUM_LEDS_IN_STRING == 0) { 
    LEDString->LEDIndex = FirstRotatingLedLight1;
  }
  LEDString->LEDIndex++;  //main light full brightness brightest
  leds[LEDString->LEDIndex] = CHSV(0, 0, 255); //turn led on full   
  delayTimer = 0;  //Reset ILHDelayTimer

  // Slowely increase the brightness of the proceeding two leds to give 
  // smooth rotation animation
  leadingLightBrightness = 150 + delayTimer;
  if (leadingLightBrightness > 255) leadingLightBrightness = 255;
  
  leadingLightBrightness2 = delayTimer;
  leds[LEDString->LEDIndex + 1] = CHSV(0, 0, leadingLightBrightness);
  leds[LEDString->LEDIndex + 2] = CHSV(0, 0, leadingLightBrightness2);
    
  fadedown();  //Fade down trailing lights for smooth rotation animation
  LEDString->fadeCount++;
  if (LEDString->fadeCount == iRotationLedDecay)
  {
    fadedown();  //Fade down trailing lights for smooth rotation animation
    LEDString->fadeCount =0;
  }
}


//fade Light House leds 
void fadedown() { 
  int i = FirstRotatingLedLight1+   1;
  do{
    leds[i].nscale8(254); //50 gives us 2 trailing leds was for uno 253, 255 for attiny8
    i++; 
  } while(i < NUM_LEDS);
}

void setup(){
  FastLED.addLeds<LEDTYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS); 
  delay(1000); // stoftstart LED protection
}


void loop()
{
  int candle=0;  // initialize to first candle
  while (candle<NUM_CANDLES) // test with three less calndles
  {

      ITCandleTimer[candle]--;// initialize CandleTimer Count Down timer arrays global Decrement 

      if (ITCandleTimer[candle]==0) // Degrade Candel timer by 1
      {
          ITCandleTimer[candle]  = random8(125, 255); //set new random timer
          IVCandleArray[candle]  = random8(50, 255); //set new random V Value...if really low it is spooky mood.
          leds[candle] = CHSV(15,255, IVCandleArray[candle]);  //(20,255,X) Give you a nice yellow light    
          LedChange = true; //Set LedChage to true to call fastled.show at the end of the loop
          //FastLED.show();
       }//end if
          candle++;
     }// end while
  
    
//Rotating Light
    delayTimer++;
    if(delayTimer==150){    //delay timer for rotation pulse aka rotational speed
      LEDAnimation();
    }
     
  FastLED.show();
}