#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#define LED1_PIN 43
#define LED2_PIN 44
#define NEO_PIN 48
#define BUTTON_PIN 0

#define I2C_SDA 14
#define I2C_SCL 13

//extern volatile bool clear_requested;

void togglePin(int pin);

#endif