#include <Arduino.h>

/*
  Keyboard Message test
  For the Adafruit Neo Trinkey
  Sends a text string when a one touchpad is pressed, opens up Notepad if the other is pressed
*/

#include <Adafruit_NeoPixel.h>
#include "Adafruit_FreeTouch.h"
#include "Mouse.h"

// Create the neopixel strip with the built in definitions NUM_NEOPIXEL and PIN_NEOPIXEL
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_NEOPIXEL, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

// Create the two touch pads on pins 1 and 2:
Adafruit_FreeTouch qt_1 = Adafruit_FreeTouch(1, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);
Adafruit_FreeTouch qt_2 = Adafruit_FreeTouch(2, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);

bool previousTouch1State = false; // for checking the state of touch 1
bool previousTouch2State = false; // for checking the state of touch 1
int touch1counter = 0;            // touch 1 counter
int last_interaction = millis();
int last_move = millis();

void setup()
{
  Serial.begin(9600);
  // while (!Serial) delay(10);

  

  strip.begin();           // start pixels
  strip.setBrightness(10); // not too bright!
  strip.show();            // Initialize all pixels to 'off'

  if (!qt_1.begin())
    Serial.println("Failed to begin qt on pin 1");
  if (!qt_2.begin())
    Serial.println("Failed to begin qt on pin 2");

  // initialize control over the keyboard:
  Mouse.begin();
}

int color_0 = 0x0;
int color_1 = 0x0;
int color_2 = 0x0;
int color_3 = 0x0;

void set_second(int color)
{
  bool update_needed = false;
  if (color_0 != color)
  {
    strip.setPixelColor(0, color);
    color_0 = color;
    update_needed = true;
  }
  if (color_1 != color)
  {
    strip.setPixelColor(1, color);
    color_1 = color;
    update_needed = true;
  }
  if (update_needed)
  {
    strip.show();
  }
}

void set_first(int color)
{
  bool update_needed = false;
  if (color_2 != color)
  {
    strip.setPixelColor(2, color);
    color_2 = color;
    update_needed = true;
  }
  if (color_3 != color)
  {
    strip.setPixelColor(3, color);
    color_3 = color;
    update_needed = true;
  }
  if (update_needed)
  {
    strip.show();
  }
}

bool first()
{
  uint16_t touch1 = qt_1.measure();
  bool status = false;
  while (touch1 > 300)
  {
    last_interaction = millis();
    set_first(0x00ff00);
    set_second(0x00);
    touch1 = qt_1.measure();
    status = true;
  }

  return status;
}

bool second()
{
  uint16_t touch2 = qt_2.measure();
  bool status = false;
  while (touch2 > 300)
  {
    last_interaction = millis();
    set_first(0x0);
    set_second(0xff0000);
    touch2 = qt_2.measure();
    status = true;
  }

  return status;
}

bool on = false;

int OFF = 0;
int CHANGED_ON = 1;
int CHANGED_OFF = 2;
int MOVED = 3;

int mode = OFF;

void render()
{
  if (millis() - last_interaction < 1000)
  {
    if (mode == CHANGED_ON)
    {
      set_first(0x00ff00);
      set_second(0x00ff00);
    }
    else if (mode == CHANGED_OFF)
    {
      set_first(0xff0000);
      set_second(0xff0000);
    }
    else if (mode == MOVED)
    {
      set_first(0x0000ff);
      set_second(0x0000ff);
    }
  }
  else
  {
    set_first(0x0);
    set_second(0x0);
  }
}

void loop()
{

  if (first())
  {
    mode = CHANGED_ON;
    on = true;
    last_move = 480001;
  }
  if (second())
  {
    mode = CHANGED_OFF;
    on = false;
  }

  if (on)
  {
    if (millis() - last_move > 480000)
    {
      mode = MOVED;
      Mouse.move(-40, 0);
      delay(10);
      Mouse.move(40, 0);
      Serial.println("Move");
      last_move = millis();
      last_interaction = millis();
    }
  }

  render();

  delay(10); // and pause a moment
}