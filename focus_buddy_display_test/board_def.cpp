#include "board_def.h"

Arduino_DataBus *bus = new Arduino_ESP32QSPI(
  LCD_CS,
  LCD_SCLK,
  LCD_SDIO0,
  LCD_SDIO1,
  LCD_SDIO2,
  LCD_SDIO3);

Arduino_CO5300 *gfx = new Arduino_CO5300(
  bus,
  LCD_RESET,
  0,
  LCD_WIDTH,
  LCD_HEIGHT,
  6,
  0,
  0,
  0);

bool gfx_init() {
  Serial.println("[DISPLAY_INIT] start");
  pinMode(BOOT_BTN_PIN, INPUT_PULLUP);
  Wire.begin(IIC_SDA, IIC_SCL);

  bool ok = gfx->begin();
  Serial.print("[DISPLAY_INIT] gfx->begin() = ");
  Serial.println(ok ? "OK" : "FAILED");
  if (!ok) {
    return false;
  }

  gfx->fillScreen(RGB565_BLACK);
  gfx->setBrightness(128);
  Serial.println("[DISPLAY_INIT] done");
  return true;
}

void gfx_display_test_loop() {
  while (true) {
    Serial.println("[DISPLAY_TEST] RED");
    gfx->fillScreen(RGB565_RED);
    delay(1000);

    Serial.println("[DISPLAY_TEST] GREEN");
    gfx->fillScreen(RGB565_GREEN);
    delay(1000);

    Serial.println("[DISPLAY_TEST] BLUE");
    gfx->fillScreen(RGB565_BLUE);
    delay(1000);

    Serial.println("[DISPLAY_TEST] WHITE");
    gfx->fillScreen(RGB565_WHITE);
    delay(1000);

    Serial.println("[DISPLAY_TEST] BLACK");
    gfx->fillScreen(RGB565_BLACK);
    delay(1000);
  }
}

void board_log(const char *tag, const char *msg) {
#if DEBUG_LOG
  Serial.print("[");
  Serial.print(tag);
  Serial.print("] ");
  Serial.print(msg);
  Serial.print(" at ");
  Serial.print(millis());
  Serial.println("ms");
#else
  (void)tag;
  (void)msg;
#endif
}
