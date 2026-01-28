// Order matters: STM32FreeRTOS wants its header first
#include <STM32FreeRTOS.h>
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

// -------------------- Hardware config --------------------
#define MATRIX_PIN PA2 // WS2812 data pin
#define MATRIX_W 4
#define MATRIX_H 4
#define NUM_PIXELS (MATRIX_W * MATRIX_H)

#define BLUE_LED PB15  // heartbeat LED BLUE
#define RED_LED PD15   // input indicator LED RED
#define GREEN_LED PD11 // spare LED GREEN

#define USER_INPUT PB3 // USER button / input (PB3, INTERNAL PULL-UP)

static const bool SERPENTINE = true;

// -------------------- NeoPixel object --------------------
Adafruit_NeoPixel strip(NUM_PIXELS, MATRIX_PIN, NEO_GRB + NEO_KHZ800);

// -------------------- Global screen state --------------------
volatile uint8_t g_currentScreen = 0; // which "screen" (pattern) is active

// -------------------- Helpers --------------------
static inline uint16_t xy(uint8_t x, uint8_t y)
{
  if (x >= MATRIX_W || y >= MATRIX_H)
    return 0;

  if (SERPENTINE && (y & 0x01))
  {
    // odd row: reversed order
    return y * MATRIX_W + (MATRIX_W - 1 - x);
  }
  else
  {
    return y * MATRIX_W + x;
  }
}

static inline uint32_t rgb(uint8_t r, uint8_t g, uint8_t b)
{
  return strip.Color(r, g, b);
}

// Simple HSV → RGB (for one of the screens)
uint32_t hsvToRgb(float h, float s, float v)
{
  float r, g, b;

  int i = int(h * 6.0f);
  float f = h * 6.0f - i;
  float p = v * (1.0f - s);
  float q = v * (1.0f - f * s);
  float t = v * (1.0f - (1.0f - f) * s);

  switch (i % 6)
  {
  case 0:
    r = v;
    g = t;
    b = p;
    break;
  case 1:
    r = q;
    g = v;
    b = p;
    break;
  case 2:
    r = p;
    g = v;
    b = t;
    break;
  case 3:
    r = p;
    g = q;
    b = v;
    break;
  case 4:
    r = t;
    g = p;
    b = v;
    break;
  case 5:
    r = v;
    g = p;
    b = q;
    break;
  }

  return strip.Color(
      (uint8_t)(r * 255.0f),
      (uint8_t)(g * 255.0f),
      (uint8_t)(b * 255.0f));
}

// Fill entire matrix with one color
void fillMatrix(uint8_t r, uint8_t g, uint8_t b)
{
  uint32_t c = rgb(r, g, b);
  for (uint16_t i = 0; i < NUM_PIXELS; i++)
  {
    strip.setPixelColor(i, c);
  }
  strip.show();
}

// -------------------- Effects (startup only) --------------------

// 1) Color wipe row by row
void effectColorWipe()
{
  Serial.println("[Effect] ColorWipe");
  const uint32_t colors[] = {
      rgb(255, 0, 0),
      rgb(0, 255, 0),
      rgb(0, 0, 255),
      rgb(255, 255, 0)};

  for (uint8_t c = 0; c < 4; c++)
  {
    strip.clear();
    strip.show();
    vTaskDelay(pdMS_TO_TICKS(100));

    for (uint8_t y = 0; y < MATRIX_H; y++)
    {
      for (uint8_t x = 0; x < MATRIX_W; x++)
      {
        strip.setPixelColor(xy(x, y), colors[c]);
        strip.show();
        vTaskDelay(pdMS_TO_TICKS(40));
      }
    }

    vTaskDelay(pdMS_TO_TICKS(400));
  }
}

// 2) Bouncing dot perimeter
void effectBouncingPerimeter()
{
  Serial.println("[Effect] Bouncing perimeter");

  const uint8_t steps = 40; // how long to run
  uint8_t x = 0, y = 0;
  int8_t dx = 1, dy = 0; // start moving right

  for (uint8_t step = 0; step < steps; step++)
  {
    strip.clear();
    strip.setPixelColor(xy(x, y), rgb(0, 255, 255));
    strip.show();
    vTaskDelay(pdMS_TO_TICKS(80));

    // Move around the border of the 4x4
    if (dx == 1 && x == MATRIX_W - 1)
    {
      dx = 0;
      dy = 1; // turn down
    }
    else if (dy == 1 && y == MATRIX_H - 1)
    {
      dx = -1;
      dy = 0; // turn left
    }
    else if (dx == -1 && x == 0)
    {
      dx = 0;
      dy = -1; // turn up
    }
    else if (dy == -1 && y == 0)
    {
      dx = 1;
      dy = 0; // turn right
    }

    x += dx;
    y += dy;
  }
}

// 3) Simple rainbow cycle (using old wheel for variety)
uint32_t wheel(uint8_t pos)
{
  pos = 255 - pos;
  if (pos < 85)
  {
    return rgb(255 - pos * 3, 0, pos * 3);
  }
  else if (pos < 170)
  {
    pos -= 85;
    return rgb(0, pos * 3, 255 - pos * 3);
  }
  else
  {
    pos -= 170;
    return rgb(pos * 3, 255 - pos * 3, 0);
  }
}

void effectRainbow()
{
  Serial.println("[Effect] Rainbow");
  for (uint16_t t = 0; t < 256; t += 4)
  {
    for (uint8_t y = 0; y < MATRIX_H; y++)
    {
      for (uint8_t x = 0; x < MATRIX_W; x++)
      {
        uint8_t idx = (x + y * MATRIX_W);
        uint8_t pos = (idx * 256 / NUM_PIXELS + t) & 0xFF;
        strip.setPixelColor(xy(x, y), wheel(pos));
      }
    }
    strip.show();
    vTaskDelay(pdMS_TO_TICKS(40));
  }
}

// -------------------- "Screens" for final static mode --------------------
// Screen 0: solid blue
// Screen 1: solid green
// Screen 2: solid yellow
// Screen 3: magenta
// Screen 4: cyan gradient
#define NUM_SCREENS 12

void drawScreen(uint8_t screen)
{
  screen %= NUM_SCREENS; // safety

  switch (screen)
  {
  case 0: // blue
    fillMatrix(0, 0, 255);
    break;

  case 1: // OFF
    fillMatrix(0, 0, 0);
    break;

  case 2: // green
    fillMatrix(0, 255, 0);
    break;

  case 3: // yellow
    fillMatrix(255, 255, 0);
    break;

  case 4: // magenta
    fillMatrix(255, 0, 255);
    break;

  case 5: // magenta
    fillMatrix(255, 0, 255);
    break;

  case 6: // 
    fillMatrix(255, 120, 255);
    break;

  case 7: // 
    fillMatrix(30, 30, 0);
    break;

  case 8: // 
    fillMatrix(0, 100, 0);
    break;

  case 9: //
    effectColorWipe();
    break;

  case 10: //
    effectBouncingPerimeter();
    break;

  case 11: //
    effectRainbow();
    break;

  case 12: // simple cyan-ish gradient across matrix
  default:
    for (uint8_t y = 0; y < MATRIX_H; y++)
    {
      for (uint8_t x = 0; x < MATRIX_W; x++)
      {
        float h = 0.5f + (x + y) * 0.02f; // around cyan, slight variation
        if (h > 1.0f)
          h -= 1.0f;
        uint32_t c = hsvToRgb(h, 0.6f, 0.9f);
        strip.setPixelColor(xy(x, y), c);
      }
    }
    strip.show();
    break;
  }

  Serial.print("[Screen] Now showing screen ");
  Serial.println(screen);
}

// -------------------- FreeRTOS tasks --------------------

void TaskStatusLED(void *pvParameters)
{
  (void)pvParameters;

  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  // GREEN on
  digitalWrite(GREEN_LED, HIGH);
  vTaskDelay(2000);
  digitalWrite(GREEN_LED, LOW);

  for (;;)
  {
    // BLUE heartbeat pulse
    digitalWrite(BLUE_LED, HIGH);
    vTaskDelay(20000);
    digitalWrite(BLUE_LED, LOW);
    vTaskDelay(2000);
  }
}

void TaskInputRead(void *pvParameters)
{
  (void)pvParameters;

  pinMode(RED_LED, OUTPUT);
  pinMode(USER_INPUT, INPUT_PULLUP); // internal pull-up

  int lastState = digitalRead(USER_INPUT);

  for (;;)
  {
    int state = digitalRead(USER_INPUT);

    // RED = input state
    digitalWrite(RED_LED, !state ? HIGH : LOW);

    // Detect button press: HIGH -> LOW (active-low button)
    if (lastState == HIGH && state == LOW)
    {
      // Advance screen index
      uint8_t next = g_currentScreen + 1;
      if (next >= NUM_SCREENS)
        next = 0;
      g_currentScreen = next;

      Serial.print("[Button] Press detected, new screen = ");
      Serial.println(next);
    }

    lastState = state;
    vTaskDelay(pdMS_TO_TICKS(40));
  }
}

// Task that owns the matrix / effects
void TaskMatrix(void *pvParameters)
{
  (void)pvParameters;

  strip.begin();
  strip.setBrightness(30);
  strip.clear();
  strip.show();

  Serial.println("[Matrix] Task started");

  // ---- Startup effects run once ----
  effectColorWipe();
  effectBouncingPerimeter();
  effectRainbow();
  fillMatrix(100, 100, 100);

  // Pause briefly, then go to screen 0 (blue)
  fillMatrix(0, 0, 0);

  vTaskDelay(pdMS_TO_TICKS(5000));
  g_currentScreen = 0;
  drawScreen(g_currentScreen); // initial screen

  // ---- Final static mode: only change on button press ----
  uint8_t lastScreen = g_currentScreen;

  for (;;)
  {
    uint8_t current = g_currentScreen;

    if (current != lastScreen)
    {
      lastScreen = current;
      drawScreen(current); // update matrix ONCE, then it stays fixed
    }

    // short poll delay; DOES NOT redraw unless screen changed
    vTaskDelay(pdMS_TO_TICKS(50));
  }
        
}

// -------------------- Arduino entry points --------------------
void setup()
{
  delay(500); // small settle
  Serial.begin(115200);
  Serial.println("\n=== LED Matrix RTOS Boot ===");

  xTaskCreate(
      TaskStatusLED,
      "status",
      256,
      nullptr,
      2,
      nullptr);

  xTaskCreate(
      TaskInputRead,
      "input",
      256,
      nullptr,
      1,
      nullptr);

  xTaskCreate(
      TaskMatrix,
      "matrix",
      512,
      nullptr,
      2,
      nullptr);

  vTaskStartScheduler();

  while (1)
  {
  }
}

void loop()
{
  // Not used with FreeRTOS (everything is in tasks)
}
