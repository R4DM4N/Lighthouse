#include <FastLED.h>

#define LED_PIN  0
#define NUM_LEDS 18
#define NUM_CANDLES 2
#define LEDTYPE WS2812B
#define COLOR_ORDER GRB
#define NUM_ANIMATION_STRINGS 1
#define MAX_BRIGHTNESS 255
#define MED_BRIGHTNESS (MAX_BRIGHTNESS/2)
#define MIN_BRIGHTNESS 0
#define FADE_FACTOR 254
#define CANDLE_FADE_FACTOR 255

extern "C" { 
 // int __cxa_guard_acquire(__guard g) {return !(char )(g);};
 // void __cxa_guard_release (__guard *g) {(char *)g = 1;};
  volatile unsigned long timer0_millis = 0;
};

typedef struct {
  uint8_t currentLED = 0;
  int num_leds = 16;
  CRGB *ledStringArray;
} LEDAnimationString;

void fadedown();

void LEDAnimation(LEDAnimationString*);