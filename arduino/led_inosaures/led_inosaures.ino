#include <Adafruit_CircuitPlayground.h>

#define NEOPIX_PIN A2
static constexpr int nb_leds = 30;

Adafruit_CPlay_NeoPixel strip = Adafruit_CPlay_NeoPixel(nb_leds, NEOPIX_PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
    CircuitPlayground.begin();
    CircuitPlayground.clearPixels();
    strip.begin();
    strip.setBrightness(30);
}

int time = 0;

void loop()
{
    for (int i = 0; i < nb_leds; ++i) {
        strip.setPixelColor(i, CircuitPlayground.colorWheel(CircuitPlayground.lightSensor()));
    }
    time++;

    strip.show();
    delay(10);
}
