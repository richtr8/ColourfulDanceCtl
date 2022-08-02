/* ColourfulDanceCtl - arduino joystick code with addressable LED support.

pre-testing alpha whipped up by richtr8 02/08/2022 */

// include necessary libraries for joystick & addressable LED functionality
#include <Joystick.h>
#include <FastLED.h>

// define arduino pin #8 as the LED data pin & the number of panels (aka places w/ LEDs) as 5.
// the quantity of LEDs in the strip is set here as 30 in this example.
// you can set as many as you want provided you drive them all sufficiently.
#define LED_PIN 8
#define NUM_PANELS 5
#define NUM_LEDS 30

// initialize the strip & joystick in the FastLED & Joystick libraries, respectively.
CRGB leds[NUM_LEDS];
Joystick_ Joystick;

// define an array known as PANEL_LED to provide a per-panel map of LEDs:
// column [0] is the panel ID number,
// column [1] is the number of LEDs in the panel,
// column [2] is the offset of the first LED in that panel.
int16_t PANEL_LED[5][3] = {
  {0, 5, 0},  // up
  {1, 5, 5},  // down
  {2, 5, 10}, // left
  {3, 5, 15}, // right
  {4, 10, 20} // underglow
};

// define the integer COLOR_PROFILE to provide an index of switchable colour profiles.
// the default value is 0, which corresponds to the "test" colour profile.
int COLOR_PROFILE = 1;

// define the CRGB colour arrays for the idle panel colours.
CRGB IDLE_COLORS[][5] = {

                   //  up,       down,     left,     right,    under
  /* 0 - test      */ {0xCD0066, 0x00FF00, 0x228282, 0x228282, 0x333333},
  /* 1 - othertest */ {0xFF0000, 0x00FF00, 0x0000FF, 0xFFFFFF, 0x0000FF},
  /* 2 - ddr       */ {0xFF00FF, 0xFF00FF, 0x3333FF, 0x3333FF, 0x000000}

};

// define the CRGB colour arrays for the active panel colours.
CRGB ACTIVE_COLORS[][5] = {

                   //  up,       down,     left,     right,    under
  /* 0 - test      */ {0xFF0000, 0xCD0066, 0xCD0066, 0x11B3B3, 0x11B3B3},
  /* 1 - othertest */ {0x00FFFF, 0xFF00FF, 0xFFFF00, 0x000000, 0xFF0000},
  /* 2 - ddr       */ {0x3333FF, 0x3333FF, 0xFF00FF, 0xFF00FF, 0x333333}

};

// define the function "setIdleColors()".
// this function will turn on the LEDs & sets them to their idle colours.
// during setup, this will be called on line 160.
void setIdleColors() {

  // this "for" loop defines the integer "k" to be used as a per-panel index.
  // you can google 'arduino for' to bring up documentation on how this works.
  for( int k=0; k < NUM_PANELS; k++) {  

    // after defining the loop, we immediately call the "idlePanelLEDs" function with the value of "k" passed to it.
    // this will effectively lopp through & perform the "idlePanelLEDs" function on each panel.
    idlePanelLEDs(k);                   
                                        
  }
}

// define the function "idlePanelLEDs".
// this function will set the panels & underglow to their idle colours.
// it will be called during the looping part of the code whenever there is no input.
void idlePanelLEDs(int k) {
  
  // sets variable integer "panel"
  // points to the row in the PANEL_LED array referenced by "k" & column [0].
  int panel = PANEL_LED[k][0];

  // sets variable integer "num_panel_leds".
  // points to the row in the PANEL_LED array referenced by "k" & column [1].
  int num_panel_leds = PANEL_LED[k][1];

  // sets variable integer "start_index".
  // points to the row in the PANEL_LED array references by "k" & column [2].
  int start_index = PANEL_LED[k][2];

  // sets variable integer "led_index" as 0.
  int led_index = 0;

  // the following 4 lines do the same as above, but for the underglow LED.
  // we know the underglow is in a fixed position (NOT panel dependent), so we point directly to row [4] & its respective columns.
  int underglow = PANEL_LED[4][0];
  int num_underglow_leds = PANEL_LED[4][1];
  int start_underglow_index = PANEL_LED[4][2];
  int underglow_index = 0;

  // here we use another "for" loop to provide an index value for the panel LEDs.
  // this particular loop happens to use the letter "j" instead of "k" for no other reason than to this variable be unique.
  for( int  j=0; j < num_panel_leds; j++) {

    //we define the variable "led_index" as the value of "j" added to the value of "start_index".
    led_index = j + start_index;
    
    // we use FastLED's "leds" function to set the colour of whichever panel has been indexed by "panel"
    // the colours have been mapped by "PANEL_LED[k][0]", & the LEDs have been addressed in sequence according to "led_index".
    leds[led_index] = IDLE_COLORS[COLOR_PROFILE][panel];
  }

  // this is a clone of the same "for" loop we just got out of, but using the variables set for the underglow LEDs.
  // we use the letter "h" as our indexing variable integer here, again just to keep it separate from "k" &/or "j".
  for( int h=0; h < num_underglow_leds; h++) {
    underglow_index = h + start_underglow_index;
    leds[underglow_index] = IDLE_COLORS[COLOR_PROFILE][underglow]; //
  }

  // finally, we call "FastLED.show", which is FastLED's "turn on or update physical LEDs" function.
  FastLED.show();
}

// this is another function identical to the last, but this one references the active colour arrays instead of the idle.
void activePanelLEDs(int k) {
  int panel = PANEL_LED[k][0];
  int num_panel_leds = PANEL_LED[k][1];
  int start_index = PANEL_LED[k][2];
  int led_index = 0;
  int underglow = PANEL_LED[4][0];
  int num_underglow_leds = PANEL_LED[4][1];
  int start_underglow_index = PANEL_LED[4][2];
  int underglow_index = 0;
  for( int  j=0; j < num_panel_leds; j++) {
    led_index = j + start_index;
    leds[led_index] = ACTIVE_COLORS[COLOR_PROFILE][panel];
  }
  for( int h=0; h < num_underglow_leds; h++) {
    underglow_index = h + start_underglow_index;
    leds[underglow_index] = ACTIVE_COLORS[COLOR_PROFILE][underglow];
  }
  FastLED.show();
}

// this is the setup part of the code. on arduino startup, this will happen once & only once.
void setup() {

  // we used "FastLED.addLeds" here to initialize the physical LED strip hardware.
  // like the "for" loop you can google "fastled addleds" to research this function & its usage.
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);

  // define arduino pins which will correspond to joystick input
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);

  //intialize the joystick.
  Joystick.begin();

  // call the "setIdleColors" function.
  setIdleColors();
  
}

// after exiting the setup loop, we define a variable, 4-value integer array.
// these 4 values will all be defined as zeroes for now.
int lastButtonState[4] = {0,0,0,0};

// this is the looping portion of the code.
// this will run again & again, as long as the arduino is powered on.
void loop() {

  // as before, we use a "for" loop to generate an index that iterates through each button pin.
  // the value "4" is chosen here because we are using arduino pins 4, 5, 6 & 7.
  for (int index = 0; index < 4; index++)
  {
  
  // define the variable "curButtonState" as the result of adding 4 to the "index" value.
  int curButtonState = !digitalRead(index + 4);

  // if the "curButtonState" is NOT equal to the value of "index" in the "lastButtonState" array...
  if (curButtonState != lastButtonState[index])
    {
      // we call the joystick library's "setButton" function to set the "curButtonState" of the button number returned by "index".
      // effectively, this will set the "curButtonState" to 1 (pressed/on).
      Joystick.setButton(index, curButtonState);

      // now that the button has been pressed, we call the "activePanelLEDs" function.
      // we pass it the value of "index", aka the joystick button number.
      idlePanelLEDs(index);

      // finally, we return the "lastButtonState" value of "index" to the "curButtonState".
      // effectively, this will set the "curButtonState" to 0 (not pressed/off).
      lastButtonState[index] = curButtonState;
    }

  // if the "curButtonState" IS equal to the value of "index" in the "lastButtonState" array...
  if (curButtonState = lastButtonState[index])
    {
      // we simply call the activePanelLEDs function & pass it its respective "index" value.
      activePanelLEDs(index);
    } 
    
  }

}
