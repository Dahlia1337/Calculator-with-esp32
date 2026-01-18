#ifndef __TASK_LED_H__
#define __TASK_LED_H__

#include "global.h"
#include "button.h"

void led_init();

void blinky_led(void* pvParameters);

void led_write(int ledNum, int state);

void task_led(void* pvParameters);

#endif
