#include <FastLED.h>

#define LED_PIN  8
#define NUM_LEDS 36 //4 candle + 16Lighthouse animation + 16Lighthouse animation 
#define NUM_CANDLES 4

#define LEDTYPE WS2812B
#define COLOR_ORDER GRB

//initialize fastled array
CRGB leds[NUM_LEDS];

//Setup Delay Timer Variables
unsigned long time;
unsigned long ulTimeBeginScan;
unsigned long ulTimeEndScan;
unsigned int slTimeDelay;
int Ifadecount = 0;    //Timer Counter for iRotationLedDecay  //does not have any effect
int ILHDelayTimer = 0;  //set lighthouse delay timer between light rotation pulses
int ILHlight = 8;       //set lighthouse light position form from candels to end of lights
int ILHlight1 = ILHlight + 1;
int ILHlight2 = ILHlight1 + 1;
int ICcandle = 0; //int counter led candel counter

boolean TimerPulse = false;  //initialise Global tiimer pulse for timer 1 and Flickering Candle routien
boolean LedChange  =false;   //Initialise flage to call fastled.show only when a led have changed

//initilize rotation variables
int iLeadingLightBright = 0;
int iLeadingLightBright2 = 0;
int iFirstRotatingLedLight1 = 0;
int iFirstRotatingLedLight2 = 20;  //Number of candles plus the first rotation LED light1
int iRotationLedDecay = 100;    //number of scans before fn fadeled is called to smooth animation
//initilaze caldlearrays
//int CandleArray[NUM_CANDLES][9];//LED,Count Down timer Variable,  hue constant,  saturation constant, v Variable,  lo time, hi time, rndlowv, rndhiv,
int ITCandleTimer[] = {10, 20, 30, 40, 50,20, 30, 10, 20, 30, 40, 50, 20, 30};// initialize CandleTimer Count Down timer arrays global
int IVCandleArray[] = {10 ,20 ,255 ,255 ,50,20 ,255,20 ,255 ,255 ,50,20 ,255,255};

//fade Light House leds 
void fadedown() { 
    int i = iFirstRotatingLedLight1+1;
    do{
      leds[i].nscale8(254); //50 gives us 2 trailing leds was for uno 253, 255 for attiny85
      leds[iFirstRotatingLedLight2+i].nscale8(254); //50 gives us 2 trailing leds was for uno 253, 255 for attiny85
      i++; 
    }while(i < NUM_LEDS);
}

void setup()
{

FastLED.addLeds<LEDTYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  
delay(1000); // stoftstart LED protection
}


void loop()
{

//  ulTimeBeginScan = micros();
// timers
  int Icandle=0;  // initialize to first candle
    while (Icandle<NUM_CANDLES) // test with three less calndles
    {  //I just couldn't seem to get the for next loop working

      ITCandleTimer[Icandle]--;// initialize CandleTimer Count Down timer arrays global Decrement 

      if (ITCandleTimer[Icandle]==0) // Degrade Candel timer by 1
      {
          ITCandleTimer[Icandle]  = random8(125, 255); //set new random timer
          IVCandleArray[Icandle]  = random8(50, 255); //set new random V Value...if really low it is spooky mood.
          leds[Icandle] = CHSV(15,255, IVCandleArray[Icandle]);  //(20,255,X) Give you a nice yellow light    
          LedChange     = true; //Set LedChage to true to call fastled.show at the end of the loop
          //FastLED.show();
       }//end if
          Icandle++;
     }// end while
  
    
//Rotating Light
    
ILHDelayTimer++;
     if(ILHDelayTimer==150){    //delay timer for rotation pulse aka rotational speed

      if(ILHlight==NUM_LEDS-1) { // because first led starts at 0
        ILHlight=iFirstRotatingLedLight1;    //Highouse begins where candles leave off
      }
      if(ILHlight1==NUM_LEDS-1) { // because first led starts at 0
        ILHlight1=iFirstRotatingLedLight1;    //Highouse begins where candles leave off
      }
      if(ILHlight2==NUM_LEDS-1) { // because first led starts at 0
        ILHlight2=iFirstRotatingLedLight1;    //Highouse begins where candles leave off
      }
      ILHlight++;  //main light full brightness brightest
      ILHlight1++; //first light infront of main light bright
      ILHlight2++; //second light infront of the main light dim
      leds[ILHlight] = CHSV(0, 0, 255); //turn led on full  
      leds[iFirstRotatingLedLight2+ILHlight] = CHSV(0, 0, 255); //turn led on full  
     ILHDelayTimer=0;  //Reset ILHDelayTimer
     }         // WE need a delay in running internal execution of loop not external.

    // Slowely increase the brightness of the proceeding two leds to give 
    // smooth rotation animation
    iLeadingLightBright    =  150 +ILHDelayTimer;
    if (iLeadingLightBright>  255) iLeadingLightBright=255;
    
    iLeadingLightBright2   =  ILHDelayTimer;
    leds[ILHlight1] = CHSV(0, 0, iLeadingLightBright);
    leds[ILHlight2] = CHSV(0, 0, iLeadingLightBright2);
    leds[iFirstRotatingLedLight2+ILHlight1] = CHSV(0, 0, iLeadingLightBright);
    leds[iFirstRotatingLedLight2+ILHlight2] = CHSV(0, 0, iLeadingLightBright2);
    
    fadedown();  //Fade down trailing lights for smooth rotation animation
  
/*
ILHDelayTimer++;
     if(ILHDelayTimer==100){

     if(ILHlight==NUM_LEDS-1) { // because first led starts at 0
        ILHlight=iFirstRotatingLedLight1;    //Highouse begins where candles leave off
      }
      if(ILHlight1==NUM_LEDS-1) { // because first led starts at 0
        ILHlight1=iFirstRotatingLedLight1;    //Highouse begins where candles leave off
      }
      if(ILHlight2==NUM_LEDS-1) { // because first led starts at 0
        ILHlight2=iFirstRotatingLedLight1;    //Highouse begins where candles leave off
      }
      ILHlight++;  //main light full brightness brightest
      ILHlight1++; //first light infront of main light bright
      ILHlight2++; //second light infront of the main light dim
     
 //     leds[NUM_LEDS-1] = CHSV(0, 0, 255); //turn led on full  
   
     ILHDelayTimer=0;  //Reset ILHDelayTimer
     }         // WE need a delay in running internal execution of loop not external.

    // Slowely increase the brightness of the proceeding two leds to give 
    // smooth rotation animation
    iLeadingLightBright     =  150  +ILHDelayTimer;
    if (iLeadingLightBright >  255) //continued next lign
        iLeadingLightBright =  255;
    
    iLeadingLightBright2    =  ILHDelayTimer;
    leds[ILHlight2] = CHSV(0, 0, iLeadingLightBright2);
    leds[ILHlight1] = CHSV(0, 0, iLeadingLightBright);
*/
Ifadecount++;
  if (Ifadecount == iRotationLedDecay)
   {
     fadedown();  //Fade down trailing lights for smooth rotation animation
     Ifadecount =0;
  }
     
  FastLED.show();

//vfmsdelay(1000);  //only use once and at the end of the loop
}