#include "global.h"

//volatile bool clear_requested = false;

void togglePin(int pin) {
    digitalWrite(pin, !digitalRead(pin));
}