
#include <Adafruit_NeoPixel.h>
#define NUM_LEDS  8
#define PIN       6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

uint32_t magenta = strip.Color(255, 0, 255);
uint32_t red = strip.Color(255, 0, 0);
uint32_t orange = strip.Color(255, 128, 128);
uint32_t yellow = strip.Color(255, 255, 128);
uint32_t green = strip.Color(0, 255, 0);
uint32_t blue = strip.Color(0, 0, 255);
uint32_t violet = strip.Color(128, 0, 255);
uint32_t white = strip.Color(255, 255, 255);
uint32_t off = strip.Color(0, 0, 0);

uint32_t color[] = {off, white, orange, blue, red, yellow};

//uint32_t  = strip.Color( , , );
// -------------------------------------------------------------------------------------

void setup(){
  strip.begin();
  strip.show();     // init to all off
}
// -------------------------------------------------------------------------------------

void loop(){
  for(int event=1; event<6; event++){
    colorFill(color[event], 5000);
    strobe(color[event]);
  }
}

// code to fill strip

void colorFill(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }
  strip.show();
  delay(wait);
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void strobe(uint32_t color){
  for(int z=0; z<100; z++){
    colorFill(color,0);
    delay(50);
    colorFill(off,0);
    delay(50);
  }
}

