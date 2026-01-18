#include "global.h"

// include task
#include "task_led.h"
#include "neo_led.h"
#include "button.h"
#include "task_keypad.h"
#include "task_lcd.h"


void setup()
{
	Serial.begin(115200);
	delay(5000);
	Serial.println("--- Start program ---");


	//int *blinkyLedPin = new int(1);

	//xTaskCreate(blinky_led, "Task blinky led", 2048, (void*) blinkyLedPin, 2, NULL);
	xTaskCreate(neo_animation, "Task Neo Animation", 4096, NULL, 2, NULL);
	//xTaskCreate(task_led, "Task button for led", 4096, NULL, 2, NULL);
	xTaskCreate(button_reading, "Task button reading", 4096, NULL, 2, NULL);
	xTaskCreate(task_keypad, "Task key pad", 8192, NULL, 2, NULL);
	//xTaskCreate(task_lcd, "Task LCD", 4096, NULL, 1, NULL);

}

void loop()
{
	//vTaskDelay(1000);
}

