#include <Arduino.h>
#include <FastLED.h>
#define MAX_BRIGHT 150
#define DEBUG_WIRING false

CRGB leds[4];
int hue = 0;
int counter = 0;

void setup() {
  // Pins 2,3,4 = Strip 1: R,G,B
  // Pins 5,6,7 = Strip 2: R,G,B
  // Pins 8,9,10 = Strip 3: R,G,B
  // Pins 11,12,13 = Strip 4: R,G,B
  FastPin<2>::setOutput();
  FastPin<3>::setOutput();
  FastPin<4>::setOutput();
  FastPin<5>::setOutput();
  FastPin<6>::setOutput();
  FastPin<7>::setOutput();
  FastPin<8>::setOutput();
  FastPin<9>::setOutput();
  FastPin<10>::setOutput();
  FastPin<11>::setOutput();
  FastPin<12>::setOutput();
  FastPin<13>::setOutput();
}

#if DEBUG_WIRING
int debug, color, strip = 0;
#endif

void loop() {
#if DEBUG_WIRING
  debug_wiring_loop();
#else
  normal_loop();
#endif
}

void normal_loop() {
  rainbow_swirl();
  draw();
}

void rainbow_swirl() {
  if (counter >= 100) {
    counter = 0;
    hue = (hue + 1) % 256;
  }
  counter++;

  leds[0] = CHSV(hue, 255, 255);
  leds[1] = CHSV((hue + 8) % 256, 255, 255);
  leds[2] = CHSV((hue + 16) % 256, 255, 255);
  leds[3] = CHSV((hue + 32) % 256, 255, 255);
}

void draw() {
  int i;
  for (i = 0; i <= 255; i++) {
    if (i <= leds[0].r && i <= MAX_BRIGHT) { FastPin<2>::hi(); } else { FastPin<2>::lo(); }
    if (i <= leds[1].r && i <= MAX_BRIGHT) { FastPin<5>::hi(); } else { FastPin<5>::lo(); }
    if (i <= leds[2].r && i <= MAX_BRIGHT) { FastPin<8>::hi(); } else { FastPin<8>::lo(); }
    if (i <= leds[3].r && i <= MAX_BRIGHT) { FastPin<11>::hi(); } else { FastPin<11>::lo(); }

    if (i <= leds[0].g && i <= MAX_BRIGHT) { FastPin<3>::hi(); } else { FastPin<3>::lo(); }
    if (i <= leds[1].g && i <= MAX_BRIGHT) { FastPin<6>::hi(); } else { FastPin<6>::lo(); }
    if (i <= leds[2].g && i <= MAX_BRIGHT) { FastPin<9>::hi(); } else { FastPin<9>::lo(); }
    if (i <= leds[3].g && i <= MAX_BRIGHT) { FastPin<12>::hi(); } else { FastPin<12>::lo(); }

    if (i <= leds[0].b && i <= MAX_BRIGHT) { FastPin<4>::hi(); } else { FastPin<4>::lo(); }
    if (i <= leds[1].b && i <= MAX_BRIGHT) { FastPin<7>::hi(); } else { FastPin<7>::lo(); }
    if (i <= leds[2].b && i <= MAX_BRIGHT) { FastPin<10>::hi(); } else { FastPin<10>::lo(); }
    if (i <= leds[3].b && i <= MAX_BRIGHT) { FastPin<13>::hi(); } else { FastPin<13>::lo(); }
  }
}

#if DEBUG_WIRING
void debug_wiring_loop() {
  if (debug > 1000) {
    debug = 0;

    color++;
    if (color > 2) {
      color = 0;
      strip++;
      if (strip > 3) {
        strip = 0;
      }
    }
  }

  if (color == 0) {
    leds[0].r = leds[1].r = leds[2].r = leds[3].r = 0;
    leds[0].g = leds[1].g = leds[2].g = leds[3].g = 0;
    leds[0].b = leds[1].b = leds[2].b = leds[3].b = 0;
    leds[strip].r = 255;
  }
  if (color == 1) {
    leds[0].r = leds[1].r = leds[2].r = leds[3].r = 0;
    leds[0].g = leds[1].g = leds[2].g = leds[3].g = 0;
    leds[0].b = leds[1].b = leds[2].b = leds[3].b = 0;
    leds[strip].g = 255;
  }
  if (color == 2) {
    leds[0].r = leds[1].r = leds[2].r = leds[3].r = 0;
    leds[0].g = leds[1].g = leds[2].g = leds[3].g = 0;
    leds[0].b = leds[1].b = leds[2].b = leds[3].b = 0;
    leds[strip].b = 255;
  }
  debug++;
  draw();
  return;
}
#endif
