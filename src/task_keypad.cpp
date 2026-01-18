#include "task_keypad.h"
#include "calc_core.h"
#include "button.h"

const byte ROWS = 4;
const byte COLS = 4;

// Định nghĩa bản đồ phím (Map)
char keys[ROWS][COLS] = {
	{'7', '8', '9', '+'},
	{'4', '5', '6', '-'},
	{'1', '2', '3', '*'},
	{'0', '=', '.', '/'}};

// Khai báo chân GPIO
byte rowPins[ROWS] = {4, 5, 6, 7};
byte colPins[COLS] = {15, 16, 17, 18};

Keypad myKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void task_keypad(void *pvParameters)
{
	Serial.println("Keypad ready");

	calc_init();

	while (true)
	{
		// 1. Kiểm tra cờ xóa từ nút BOOT (Global variable)
		if (isButtonPressed())
		{
			calc_reset();
			//Serial.println("--- Clear ---");
		}

		// 2. Quét phím
		char customKey = myKeypad.getKey();

		// 3. Nếu có phím, đẩy sang cho calc_core xử lý
		if (customKey)
		{
			calc_process_input(customKey);
		}

		vTaskDelay(pdMS_TO_TICKS(20));
	}
}