#include <Adafruit_CircuitPlayground.h>

#define NEOPIX_PIN A2
static constexpr int nb_leds    = 30;
static int           brightness = 255;

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
        auto falloff  = 0.8f;
        strip.setPixelColor(i,
                            (red(prev_col) * falloff),
                            (green(prev_col) * falloff),
                            (blue(prev_col) * falloff));
    }
}

void ping_pong(Adafruit_CPlay_NeoPixel& strip)
{
    struct Ball {
        int     pos;
        int     dir;
        uint8_t r;
        uint8_t g;
        uint8_t b;

        void set_col(Adafruit_CPlay_NeoPixel& strip)
        {
            strip.setPixelColor(pos, r, g, b);
        }

        void advance()
        {
            pos += dir;
            if (pos < 0 || pos > nb_leds) {
                dir *= -1;
            }
        }

        void check_intersection(Ball& b)
        {
            if (pos == b.pos) {
                dir *= -1;
                b.dir *= -1;
                advance();
                b.advance();
            }
        }
    };
    static Ball ball1 = {
        10,
        1,
        255,
        110,
        200};
    static Ball ball2 = {
        24,
        -1,
        110,
        255,
        200};
    static Ball ball3 = {
        16,
        1,
        200,
        110,
        255};
    static int frame = 0;
    ball1.set_col(strip);
    ball2.set_col(strip);
    ball3.set_col(strip);
    ball1.advance();
    ball2.advance();
    ball3.advance();
    ball1.check_intersection(ball2);
    ball1.check_intersection(ball3);
    ball2.check_intersection(ball3);
    fade(strip);
    frame++;
}

void setup()
{
    CircuitPlayground.begin();
    CircuitPlayground.clearPixels();
    strip.begin();
}

void loop()
{
    strip.setBrightness(brightness);
    if (CircuitPlayground.slideSwitch()) {
        gradient(strip);
    }
    else {
        ping_pong(strip);
    }
    strip.show();
    delay(50);
    if (CircuitPlayground.leftButton()) {
        brightness = clamp(brightness - 10);
    }
    if (CircuitPlayground.rightButton()) {
        brightness = clamp(brightness + 10);
    }
}
