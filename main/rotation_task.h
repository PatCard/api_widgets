#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "widget.h"

typedef struct {
    QueueHandle_t   queue;
    const widget_t *widgets;
    int             widget_count;
} rotation_task_args_t;

void rotation_task(void *arg);
