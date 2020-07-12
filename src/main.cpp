#include <FastLED.h>

#define LED_PIN  8
#define NUM_LEDS 36
#define NUM_CANDLES 4
#define LEDTYPE WS2812B
#define COLOR_ORDER GRB
#define NUM_ANIMATION_STRINGS 2

typedef struct {
  uint8_t currentLED = 0;
  int num_leds_in_string = 16;
  CRGB *ledStringArray;
} LEDAnimationString;

void fadedown();
void LEDAnimation(LEDAnimationString*);

CRGB leds[NUM_LEDS];
LEDAnimationString LEDAnimationStrings[NUM_ANIMATION_STRINGS];
int animationDelay = 0;

void LEDAnimation(LEDAnimationString *LEDString){
  LEDString->ledStringArray[LEDString->currentLED] = CHSV(0,0,255);
  if (150 + animationDelay <= 255){
    LEDString->ledStringArray[(LEDString->currentLED + 1) % LEDString->num_leds_in_string] = CHSV(0,0,animationDelay + 150);
  }
  LEDString->ledStringArray[(LEDString->currentLED + 2) % LEDString->num_leds_in_string] = CHSV(0,0,animationDelay + 0);

  if (animationDelay == 150){
    LEDString->currentLED = (LEDString->currentLED + 1) % LEDString->num_leds_in_string;
  }
}


//fade Lighthouse leds 
void fadedown() { 
  for (int i = 0; i < NUM_LEDS; i++){
    leds[i].nscale8(252);
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