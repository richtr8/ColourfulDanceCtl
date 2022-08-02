#include <Joystick.h>
#include <FastLED.h>

#define LED_PIN 8
#define NUM_PANELS 5
#define NUM_LEDS 30

CRGB leds[NUM_LEDS];
Joystick_ Joystick;

int16_t PANEL_LED[5][3] = {
  {0, 5, 0},  // up
  {1, 5, 5},  // down
  {2, 5, 10}, // left
  {3, 5, 15}, // right
  {4, 10, 20} // underglow
};

int COLOR_PROFILE = 1;

CRGB IDLE_COLORS[][5] = {
  {0xCD0066, 0x00FF00, 0x228282, 0x228282, 0x333333},
  {0xFF0000, 0x00FF00, 0x0000FF, 0xFFFFFF, 0x0000FF},
  {0xFF00FF, 0xFF00FF, 0x3333FF, 0x3333FF, 0x000000}
};

CRGB ACTIVE_COLORS[][5] = {
  {0xFF0000, 0xCD0066, 0xCD0066, 0x11B3B3, 0x11B3B3},
  {0x00FFFF, 0xFF00FF, 0xFFFF00, 0x000000, 0xFF0000},
  {0x3333FF, 0x3333FF, 0xFF00FF, 0xFF00FF, 0x333333}
};

void setIdleColors() {
  for( int k=0; k < NUM_PANELS; k++) {
    idlePanelLEDs(k);                                     
  }
}

void idlePanelLEDs(int k) {
  
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
    leds[led_index] = IDLE_COLORS[COLOR_PROFILE][panel];
  }
  for( int h=0; h < num_underglow_leds; h++) {
    underglow_index = h + start_underglow_index;
    leds[underglow_index] = IDLE_COLORS[COLOR_PROFILE][underglow]; //
  }
  FastLED.show();
}

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

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  Joystick.begin();
  setIdleColors(); 
}

int lastButtonState[4] = {0,0,0,0};

void loop() {
  for (int index = 0; index < 4; index++)
  {
  int curButtonState = !digitalRead(index + 4);
  if (curButtonState != lastButtonState[index])
    {
      Joystick.setButton(index, curButtonState);
      idlePanelLEDs(index);
      lastButtonState[index] = curButtonState;
    }
  if (curButtonState = lastButtonState[index])
    {
      activePanelLEDs(index);
    }     
  }
}
