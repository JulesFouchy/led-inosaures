#include <Adafruit_CircuitPlayground.h>

#define NEOPIX_PIN A2
static constexpr int nb_leds = 30;

Adafruit_CPlay_NeoPixel strip = Adafruit_CPlay_NeoPixel(nb_leds, NEOPIX_PIN, NEO_GRB + NEO_KHZ800);

void gradient(Adafruit_CPlay_NeoPixel& strip)
{
    static int frame = 0;
    strip.setBrightness(255);
    for (int i = 0; i < nb_leds; ++i) {
        float t = sin(frame * 0.01 + i * 0.1) * 0.5 + 0.5;
        int   r = t * 255;
        int   b = (1. - t) * 255;
        strip.setPixelColor(i, r * 0.3, 30 * 0.3, b * 0.3);
    }
    frame = (frame + 1);
}

void setup()
{
    CircuitPlayground.begin();
    CircuitPlayground.clearPixels();
    strip.begin();
}

int time = 0;

void loop()
{
    gradient(strip);
    strip.show();
    delay(50);
}
