#include "button.h"

volatile bool flagShortPress = false;
volatile bool flagLongPress = false;

unsigned long pressStartTime = 0;
bool isHolding = false;
bool longPressTriggered = false;

void button_init()
{
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    Serial.println("Button ready");
};

void button_reading(void *pvParameters)
{
    button_init();

    while (1)
    {

        if (digitalRead(BUTTON_PIN) == LOW)
        {
            if (!isHolding)
            {
                vTaskDelay(pdMS_TO_TICKS(50));
                if (digitalRead(BUTTON_PIN) == LOW)
                {
                    //Serial.println("---button pressed---");
                    isHolding = true;
                    pressStartTime = millis(); // Ghi lại thời gian bắt đầu
                    longPressTriggered = false;
                }
            }
            else{
                if (!longPressTriggered && (millis() - pressStartTime > 1000)) {
                    //Serial.println("--- Event: Long Press Detected (>1s) ---");
                    flagLongPress = true;      // Bật cờ Long Press
                    longPressTriggered = true; // Đánh dấu đã báo rồi, không báo lại nữa
                }
            }

        }

        else {
            if (isHolding) {
                // Tính tổng thời gian đã giữ
                unsigned long holdTime = millis() - pressStartTime;
                
                // Nếu nhả ra trước 1 giây -> Đây là Short Press
                if (holdTime < 1000) {
                    //Serial.println("--- Event: Short Press Detected ---");
                    flagShortPress = true;
                }
                
                // Reset trạng thái
                isHolding = false;
            }
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
};

bool isButtonPressed()
{
    if (flagShortPress) {
        flagShortPress = false; // Reset ngay sau khi đọc
        return true;
    }
    return false;
};

bool isButtonPressed1s() {
if (flagLongPress) {
        flagLongPress = false; // Reset ngay sau khi đọc
        return true;
    }
    return false;
};