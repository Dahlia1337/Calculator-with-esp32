#include "task_led.h"

void led_init(){
    pinMode(LED1_PIN, OUTPUT);
	pinMode(LED2_PIN, OUTPUT);
	digitalWrite(LED1_PIN, HIGH);
	digitalWrite(LED2_PIN, HIGH);

    Serial.println("LED ready");
};

void blinky_led(void* pvParameters){
    led_init();
    int pinNumber = *((int*) pvParameters) + 42;

    while (1)
    {
        digitalWrite(pinNumber, LOW);
        vTaskDelay(pdMS_TO_TICKS(500));
        digitalWrite(pinNumber, HIGH);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
    
};

void led_write(int ledNum, int state){
    int pinNumber = ledNum + 42;

    if (state == 1){
        digitalWrite(pinNumber, LOW);
    }
    else digitalWrite(pinNumber, HIGH);   
};

void task_led(void* pvParameters){
    led_init();
    
    while (1){
        if (isButtonPressed()){
            togglePin(LED1_PIN);
        }

        if (isButtonPressed1s()){
            togglePin(LED2_PIN);
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
};
