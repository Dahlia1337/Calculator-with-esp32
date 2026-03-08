#include "global.h"

volatile bool clear_requested = false;
QueueHandle_t keyQueue = NULL;
String currentDisplay = "0";

void togglePin(int pin) {
    digitalWrite(pin, !digitalRead(pin));
}