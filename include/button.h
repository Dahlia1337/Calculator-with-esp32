#if !defined(__BUTTON_H__)
#define __BUTTON_H__

#include "global.h"

void button_init();

void button_reading(void * pvParameters);

bool isButtonPressed();

bool isButtonPressed1s();

#endif

