#include <Adafruit_NeoPixel.h>
#define PIN 6
#define NUM_LEDS 8
char command;
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
  Serial.begin(9600);
}

// *** REPLACE FROM HERE ***
void loop() {
// ask for command via serial port
Serial.println("c = clear     p = police light");
Serial.println("r = red       b = blue");
Serial.println("g = green     y = flash yellow");
Serial.println("w = white     m = marquee");
Serial.println("?  ");
Serial.println("");

while(Serial.available() == 0){}
command = Serial.read();

switch(command){

  case 'r':
  Serial.println("setting strip to red");
  setStripColor(NUM_LEDS, 64,0,0);
  strip.show();
  delay(500);
  break;

  case 'b':
  Serial.println("setting strip to blue");
  setStripColor(NUM_LEDS, 0,0,128);
  strip.show();
  delay(500);
  break;  
  
  case 'c':
  Serial.println("clearing strip");
  clearStrip(NUM_LEDS);
  strip.show();
//  delay(500);
  break;

  case 'g':
  Serial.println("setting strip to green");
  setStripColor(NUM_LEDS, 0, 128, 0);
  strip.show();
  delay(500);
  break;
  
  case 'p':
  Serial.println("police lights");
  clearStrip(NUM_LEDS);
  policeFlash(NUM_LEDS, 20);
  delay(500);
  break;

  case 'w':
  Serial.println("white");
  setStripColor(NUM_LEDS, 64,64,64);
  strip.show();
  delay(500);
  break;
  
  case 'y':
  Serial.println("flash yellow");
  flashStrip(NUM_LEDS, 5, 128,64,0);
  break;

  case 'm':
  Serial.println("marquee");
  marquee(NUM_LEDS);
  break;

}


  

}

void setStripColor(int count, int red, int green, int blue){
  for(int i=0; i < count; i++){
    strip.setPixelColor(i, red, green, blue);
  }    
  return;
}

void flashStrip(int num_leds, int flashes, int red, int green, int blue){
  for(int j=0; j<flashes; j++){
    setStripColor(num_leds, red, green, blue);
    strip.show();
    delay(125);
    setStripColor(num_leds, 0,0,0);
    strip.show();
    delay(375);
     
    }
  return;
}

void policeFlash(int num_leds, int flashes){
  for(int j=0; j<flashes; j++){
    // set lower block to blue, uppper block to red
    int stripHalf = num_leds/2-1;
    for(int i = 0; i<stripHalf; i++){
      strip.setPixelColor(i, 0,0,255);
      strip.setPixelColor(i+stripHalf+2, 255,0,0);
    }
    strip.show();
    delay(125);
    for(int i = 0; i<stripHalf; i++){
      strip.setPixelColor(i, 255,0,0);
      strip.setPixelColor(i+stripHalf+2, 0,0,255);
    }
    strip.show();
    delay(125);
  }
  return;
}

void marquee(int num_leds){

 for(int i=0; i<20; i++){
  for(int j=0; j<num_leds; j++){
    setStripColor(num_leds, 128,0,0);
    strip.setPixelColor(j, 0,0,0);
    strip.show();
    delay(50);
  }
 }
 clearStrip(num_leds);
  
}

void clearStrip(int num_leds){
  for(int i=0; i<num_leds; i++){
    strip.setPixelColor(i, 0,0,0);
  }
  strip.show();
  return;
}

