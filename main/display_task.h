#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "ssd1306.h"
#include "widget.h"

typedef struct {
    QueueHandle_t  queue;
    SSD1306_t     *oled;
    const widget_t *widgets;
    int             widget_count;
} display_task_args_t;

void display_task(void *arg);
