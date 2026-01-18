#include "neo_led.h"

void neo_animation(void *pvParameters){
    Adafruit_NeoPixel strip(1, NEO_PIN, NEO_GRB + NEO_KHZ800);

    strip.begin();
    strip.setBrightness(20);

    while (true) {
    // Vòng lặp tạo màu cầu vồng (0 -> 65535)
    for(long firstPixelHue = 0; firstPixelHue < 65536; firstPixelHue += 256) {
      // Chuyển đổi giá trị Hue sang màu RGB
      int pixelHue = firstPixelHue + (0 * 65536L / strip.numPixels());
      strip.setPixelColor(0, strip.gamma32(strip.ColorHSV(pixelHue)));
      strip.show();
      
      vTaskDelay(pdMS_TO_TICKS(20)); 
    }
  }

};