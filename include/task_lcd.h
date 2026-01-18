#if !defined(__LCD__)
#define __LCD__

#include "global.h"

#define LCD_ADDR 0x27 

void lcd_init();

void task_lcd(void *pvParameters);

#endif // __LCD__
