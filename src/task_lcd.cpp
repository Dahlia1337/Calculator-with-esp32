#include "task_lcd.h"

// Khởi tạo đối tượng LCD (Địa chỉ, số cột, số dòng)
LiquidCrystal_I2C lcd(LCD_ADDR, 16, 2);

void lcd_init()
{
    Wire.begin(I2C_SDA, I2C_SCL);

    lcd.init();
    lcd.backlight(); // Bật đèn nền

    lcd.setCursor(0, 0);
    lcd.print("LCD ready");
};

void task_lcd(void *pvParameters)
{
    int count = 0;

    while (true)
    {
        // Cập nhật dòng 2 liên tục
        lcd.setCursor(0, 1); // Cột 0, Dòng 1
        lcd.printf("Running: %d s", count);

        count++;

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
};