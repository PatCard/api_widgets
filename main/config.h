#pragma once
#include "vars_env.h"

/* -------------------------------------------------------
 * WiFi
 * ------------------------------------------------------- */
//#define WIFI_SSID        WIFI_SSID
//#define WIFI_PASSWORD    WIFI_PASSWORD

/* -------------------------------------------------------
 * API Keys
 * ------------------------------------------------------- */
//#define OWM_API_KEY      OWM_API_KEY
#define OWM_CITY         "Santiago"
#define OWM_COUNTRY      "CL"

/* -------------------------------------------------------
 * Pines I2C - LilyGo T3 V1.6.1
 * ------------------------------------------------------- */
#define I2C_SDA_PIN      21
#define I2C_SCL_PIN      22

/* -------------------------------------------------------
 * Widget rotation
 * ------------------------------------------------------- */
#define WIDGET_ROTATE_MS     10000   // tiempo entre widgets (ms)
#define WIDGET_FETCH_MS      60000   // cada cuanto se actualiza cada widget (ms)

/* -------------------------------------------------------
 * Queue
 * ------------------------------------------------------- */
#define DISPLAY_QUEUE_SIZE   5

/* -------------------------------------------------------
 * Tasks
 * ------------------------------------------------------- */
#define ROTATION_TASK_STACK  4096
#define ROTATION_TASK_PRIO   5
#define DISPLAY_TASK_STACK   4096
#define DISPLAY_TASK_PRIO    4
#define FETCH_TASK_STACK     8192
#define FETCH_TASK_PRIO      3
