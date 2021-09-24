#include <Adafruit_CircuitPlayground.h>

#define NEOPIX_PIN A2
static constexpr int nb_leds = 30;

Adafruit_CPlay_NeoPixel strip = Adafruit_CPlay_NeoPixel(nb_leds, NEOPIX_PIN, NEO_GRB + NEO_KHZ800);

uint8_t red(uint32_t col)
{
    return (col >> 16) & 255;
}

uint8_t green(uint32_t col)
{
    return (col >> 8) & 255;
}

uint8_t blue(uint32_t col)
{
    return col & 255;
}

int clamp(int x)
{
    return min(max(x, 0), 255);
}

void gradient(Adafruit_CPlay_NeoPixel& strip)
{
    strip.setBrightness(255);
    static int frame = 0;
    for (int i = 0; i < nb_leds; ++i) {
        float t = sin(frame * 0.01 + i * 0.1) * 0.5 + 0.5;
        int   r = t * 255;
        int   b = (1. - t) * 255;
        strip.setPixelColor(i, r * 0.3, 30 * 0.3, b * 0.3);
    }
    frame = (frame + 1);
}

void fade(Adafruit_CPlay_NeoPixel& strip)
{
    for (int i = 0; i < nb_leds; ++i) {
        auto prev_col = strip.getPixelColor(i);
        auto falloff  = 10;
        strip.setPixelColor(i,
                            clamp(red(prev_col) - falloff),
                            clamp(green(prev_col) - falloff),
                            clamp(blue(prev_col) - falloff));
    }
}

void ping_pong(Adafruit_CPlay_NeoPixel& strip)
{
    static int pos1 = 10;
    static int dir1 = 1;
    static int pos2 = 17;
    static int dir2 = -1;
    if (pos1 == 10)
        strip.setPixelColor(0, 255, 110, 200);
    pos1 = 1;
    fade(strip);
}

void setup()
{
    CircuitPlayground.begin();
    CircuitPlayground.clearPixels();
    strip.begin();
}

void loop()
{
    ping_pong(strip);
    strip.show();
    delay(50);
}
