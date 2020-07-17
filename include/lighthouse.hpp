#include <FastLED.h>

#define LED_PIN  0
#define NUM_LEDS 36
#define NUM_CANDLES 4
#define LEDTYPE WS2812B
#define COLOR_ORDER GRB
#define NUM_ANIMATION_STRINGS 2
#define MAX_BRIGHTNESS 255
#define MED_BRIGHTNESS (MAX_BRIGHTNESS/2)
#define MIN_BRIGHTNESS 0
#define FADE_FACTOR 254
#define CANDLE_FADE_FACTOR 255

#if !defined(__UNO__)
extern "C" { 
 // int __cxa_guard_acquire(__guard g) {return !(char )(g);};
 // void __cxa_guard_release (__guard *g) {(char *)g = 1;};
  volatile unsigned long timer0_millis = 0;
};
#endif

#if defined(UNO)
  #warning "UNO defined"
#endif

typedef struct {
  uint8_t currentLED = 0;
  int num_leds = 16;
  int LEDOffset;
  CRGB *ledStringArray;
  int fadeFactor = FADE_FACTOR;
} LEDAnimationString;

void fadeDown(uint8_t, int, int);

void LEDAnimation(LEDAnimationString*);