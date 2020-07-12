#include <FastLED.h>
#include "lighthouse.hpp"

CRGB leds[NUM_LEDS];
LEDAnimationString LEDAnimationStrings[NUM_ANIMATION_STRINGS];
int animationDelay = 0;

void LEDAnimation(LEDAnimationString *LEDString){
  LEDString->ledStringArray[LEDString->currentLED] = CHSV(0,0,MAX_BRIGHTNESS);
  if (MED_BRIGHTNESS + animationDelay <= MAX_BRIGHTNESS){
    LEDString->ledStringArray[(LEDString->currentLED + 1) % LEDString->num_leds] = CHSV(0,0,animationDelay + MED_BRIGHTNESS);
  }
  LEDString->ledStringArray[(LEDString->currentLED + 2) % LEDString->num_leds] = CHSV(0,0,animationDelay + MIN_BRIGHTNESS);

  if (animationDelay == 150){
    LEDString->currentLED = (LEDString->currentLED + 1) % LEDString->num_leds;
  }
}

void fadedown() { 
  for (int i = 0; i < NUM_LEDS; i++){
    leds[i].nscale8(FADE_FACTOR);
  }
}

void setup(){
  FastLED.addLeds<LEDTYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  LEDAnimationStrings[0].ledStringArray = leds;
  LEDAnimationStrings[1].ledStringArray = leds + 20;
}

void loop()
{
  fadedown();
  LEDAnimation(&LEDAnimationStrings[0]);
  LEDAnimation(&LEDAnimationStrings[1]);
  FastLED.show();
  if (animationDelay == 150) animationDelay = 0;
  animationDelay++;
}