#include <FastLED.h>
#include "lighthouse.hpp"

CRGB leds[NUM_LEDS];
LEDAnimationString LEDAnimationStrings[NUM_ANIMATION_STRINGS];

int animationDelay = 0;
int candles[] = {16, 17, 18, 19};
int candleTimer[4];

void LEDAnimation(LEDAnimationString *LEDString){
  LEDString->ledStringArray[LEDString->currentLED] = CHSV(0,0,MAX_BRIGHTNESS);
  if (MED_BRIGHTNESS + animationDelay <= MAX_BRIGHTNESS){
    LEDString->ledStringArray[(LEDString->currentLED + 1) % LEDString->num_leds] = CHSV(0,0,animationDelay + MED_BRIGHTNESS);
  }
  LEDString->ledStringArray[(LEDString->currentLED + 2) % LEDString->num_leds] = CHSV(0,0,animationDelay + MIN_BRIGHTNESS);

  if (animationDelay == 150){
    LEDString->currentLED = (LEDString->currentLED + 1) % LEDString->num_leds;
  }
  fadeDown(254, LEDString->ledStringArray, LEDString->num_leds);
}

void fadeDown(uint8_t fadeFactor, CRGB *fadeLEDS, int nLEDS) { 
  for (int i = 0; i < nLEDS; i++){
    fadeLEDS[i].nscale8(fadeFactor);
  }
}

void candleAnimation(){
  for (int i = 0; i < NUM_CANDLES; i++){
      candleTimer[i]--;
      if (candleTimer[i] == 0){
        candleTimer[i] = random8(125, 255);
        leds[candles[i]] = CHSV(25,255, random8(150, 255));
      }
  }
  fadeDown(200, &leds[16], 4);
}

void setup(){
  FastLED.addLeds<LEDTYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  LEDAnimationStrings[0].ledStringArray = leds ;
  LEDAnimationStrings[1].ledStringArray = leds + 20;

  for (int i = 0; i < NUM_CANDLES; i++){
    candleTimer[i] = random8(105, 255);
  }
}

void loop()
{
  LEDAnimation(&LEDAnimationStrings[0]);
  LEDAnimation(&LEDAnimationStrings[1]);
  candleAnimation();
  FastLED.show();

  animationDelay = (animationDelay + 1) % 150;
}