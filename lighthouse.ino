/**
Lighthouse

Made this to illuminate a Cape Hatteras garden lighthouse model I made
for my sister's birthday.

Originally run on a Seeeduino XIAO, because I had one lying around.

Animate a line of neopixels to look like a lighthouse light.
Scales 4 lights along the strand to simulate the "lens" rotating:
  trailing, main, next main, and leading.

Uses a light sensor determine when to animate.

Place light sensor on the opposite side of the strip start to avoid getting
erroneous ambient value from the lights.

The code periodically checks the ambient light sensor, and when darkness is
detected it starts a full light rotation.
*/

#include <Adafruit_NeoPixel.h>

// The two states are playing a full light rotation and waiting for darkness.
enum State {
  PlayingLightAnimation,
  AwaitingDarkness,
};
State currentState = State::AwaitingDarkness;


// Number of NeoPixels in our light loop.
#define PIXEL_COUNT 21

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

// Ambient light below this percentage of sensor range starts the animation.
#define LIGHT_THRESHOLD 20

// Milliseconds delay between ambient light checks.
#define LIGHT_CHECK_DELAY 5000

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

// Light 
int mainLightIndex = 0;
int current_step = 0;

void setup() {
  Serial.begin(115200);
  strip.begin();
  turnOffLights();
}

void setLight(int offset, int step) {
  int pixel_index; 
  int brightness_shift;
  int brightness;
  uint32_t color;

  // Wrap if mainLightIndex plus offset is negative.
  pixel_index = (mainLightIndex + offset + PIXEL_COUNT) % PIXEL_COUNT;
  brightness_shift = step * (80 / STEPS);

  // Trailing light.
  if (offset < 0) {
    brightness = (80 * (2 + offset)) - brightness_shift;
  }
  // Main light.
  if (0 == offset) {
    brightness = 240 - brightness_shift;
  }
  // Next light and leading light.
  if (offset > 0) {
    brightness = (80 * (2 - offset)) + brightness_shift;
  }

  color = strip.Color(brightness, brightness, brightness);
  strip.setPixelColor(pixel_index, color);
}

void drawLights() {
  // Trailing light.
  setLight(-1, current_step);
  // Main light.
  setLight(0, current_step);
  // Next main light.
  setLight(1, current_step);
  // leading light.
  setLight(2, current_step);
  
  strip.show();
}

void incrementCounters() {
  current_step++;
  if (current_step > STEPS) {
    current_step = 0;
    mainLightIndex++;
  }
}

bool hasLightAnimationCompleted() {
  return mainLightIndex >= PIXEL_COUNT;
}

void resetCounters() {
  mainLightIndex = 0;
  current_step = 0;  
}

bool isDaylightOut() {
  int ambientLightPercent = analogRead(LIGHT_SENSOR_PIN) * ((float)100 / 1023.0);
  Serial.print("ambientLightPercent is ");
  Serial.println(ambientLightPercent);
  return ambientLightPercent > LIGHT_THRESHOLD;
}

void turnOffLights() {
  Serial.println("Turning off lights");
  strip.clear();
  strip.show();
}

void loop() {
  Serial.println("\n\nLoop");

  bool darkEnoughForLights = !isDaylightOut();

  Serial.print("Dark enough is ");
  Serial.println(darkEnoughForLights);

  // Still too bright to start.
  if (currentState == State::AwaitingDarkness && !darkEnoughForLights) {
    Serial.println("Still awaiting darkness");
    delay(LIGHT_CHECK_DELAY);
    return;
  }

  // It is now dark enough to start.
  if (currentState == State::AwaitingDarkness && darkEnoughForLights) {
    Serial.println("Switching to PlayingLightAnimation");
    currentState = State::PlayingLightAnimation;
  }

  bool lightAnimationCompleted = hasLightAnimationCompleted();

  // Continue the light animation
  if (currentState == State::PlayingLightAnimation && !lightAnimationCompleted) {
    Serial.println("Continue PlayingLightAnimation");

    Serial.print("mainLightIndex is ");
    Serial.print(mainLightIndex);

    Serial.print("  current_step is ");
    Serial.println(current_step);

    drawLights();
    incrementCounters();
    delay(DELAY_MS);
    return;
  }

  // Continue again from the beginning.
  if (currentState == State::PlayingLightAnimation && lightAnimationCompleted && darkEnoughForLights) {
    Serial.println("Loop PlayingLightAnimation");
    resetCounters();
    return;
  }

  // Turn off lights and change state.
  if (currentState == State::PlayingLightAnimation && lightAnimationCompleted && !darkEnoughForLights) {
    Serial.println("Switching to AwaitingDarkness");
    turnOffLights();
    resetCounters();
    currentState = State::AwaitingDarkness;
    return;
  }

}
