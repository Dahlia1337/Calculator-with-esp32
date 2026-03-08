#ifndef TASK_WEBSERVER_H
#define TASK_WEBSERVER_H

#include "global.h"
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include <Preferences.h>

void task_webserver(void *parameter);

#endif