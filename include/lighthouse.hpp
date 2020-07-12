#include <FastLED.h>

#define LED_PIN  8
#define NUM_LEDS 36
#define NUM_CANDLES 4
#define LEDTYPE WS2812B
#define COLOR_ORDER GRB
#define NUM_ANIMATION_STRINGS 2
#define MAX_BRIGHTNESS 255
#define MED_BRIGHTNESS (MAX_BRIGHTNESS/2)
#define MIN_BRIGHTNESS 0
#define FADE_FACTOR 254

typedef struct {
  uint8_t currentLED = 0;
  int num_leds = 16;
  CRGB *ledStringArray;
} LEDAnimationString;

void fadedown();
void LEDAnimation(LEDAnimationString*);