/**
Lighthouse

Made this to illuminate a Cape Hatteras garden lighthouse model I made
for my sister's birthday.

Originally run on a Seeeduino XIAO, because I had one lying around.

Animate a line of neopixels to look like a lighthouse light.
Scales 4 lights (one trailing, main, two leading) along the strand to
simulate the "lens" rotating.
Uses a light sensor determine when to animate.
*/

#include <Adafruit_NeoPixel.h>

// Number of NeoPixels in our light loop.
#define PIXEL_COUNT 16

// Digital IO pin connected to the NeoPixels.
#define PIXEL_PIN 10

// Steps in a light increment per offset.
#define STEPS 40        

// Milliseoncds for one rotation of the light.
// Cape Hatteras lighthouse has a characteristic of one flash
// every 7.5 seconds.
#define PERIOD_MS 7500

// Delay between loops so that a full cycle takes PERIOD_MS.
#define DELAY_MS PERIOD_MS / (PIXEL_COUNT * STEPS)

// Digital IO pin connected to the light sensor.
#define LIGHT_SENSOR_PIN 9

// How many times main() should loop before checking light.
// 30 minutes * 60 sec/min * 1000 ms/sec = 1800000
#define LOOPS_PER_CHECK 1800000 / 6500 

// Milliseconds to delay if light is detected.
// 50 mins * 60sec/min * 1000ms/sec = 300000
#define LIGHT_CHECK_DELAY 300000

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  strip.begin();
}

int position = 0, current_step = 0, loops = 0;

// position can be negative, we wrap that.
void setLight(int position, int offset, int step) {
  int pixel_index; 
  int brightness_shift;
  int brightness;
  uint32_t color;

  // Wrap if position plus offset is negative.
  pixel_index = (position + offset + PIXEL_COUNT) % PIXEL_COUNT;
  brightness_shift = step * (80 / STEPS);

  if (offset < 0) {
    brightness = (80 * (2 + offset)) - brightness_shift;
  }
  if (0 == offset) {
    brightness = 240 - brightness_shift;
  }
  if (offset > 0) {
    brightness = (80 * (2 - offset)) + brightness_shift;
  }

  color = strip.Color(brightness, brightness, brightness);
  strip.setPixelColor(pixel_index, color);
}

void drawLights() {
  setLight(position, -1, current_step);
  setLight(position, 0, current_step);
  setLight(position, 1, current_step);
  setLight(position, 2, current_step);
  strip.show();
}

void incrementCounters() {
  current_step++;
  if (current_step > STEPS) {
    current_step = 0;
    position = (position + 1) % PIXEL_COUNT;
  }
  if ((0 == position ) && (0 == current_step)) {
    loops++;
  }
}

bool isDaylightOut() {
  int ambientLightPercent = analogRead(LIGHT_SENSOR_PIN) * ((float)100 / 1023.0);
  Serial.print("ambientLightPercent is ");
  Serial.println(ambientLightPercent);
  return ambientLightPercent > 20;
}

void turnOffLights() {
  Serial.println("Turning off lights");
  strip.clear();
  strip.show();
}

bool pauseDuringDaylight() {
  if (isLightOut()) {
    turnOffLights();
    delay(1000);
    return true;
  }
  return false;
}

void loop() {
  Serial.println("Loop");

  if (pauseDuringDaylight()) {
    return;
  }
  drawLights();
  incrementCounters();

  delay(DELAY_MS);
}
