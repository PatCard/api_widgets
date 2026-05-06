#pragma once

#include "esp_err.h"
#include "ssd1306.h"

/* -------------------------------------------------------
 * Struct que define un widget
 * Para agregar uno nuevo: implementar fetch + display
 * y agregar al array en app_init.c
 * ------------------------------------------------------- */
typedef struct {
    const char *name;
    esp_err_t  (*fetch)(char *buf, size_t len);
    void       (*display)(SSD1306_t *oled, const char *data);
    uint32_t   fetch_interval_ms;
} widget_t;

/* Mensaje que viaja por la queue al display_task */
typedef struct {
    char data[128];
    int  widget_index;
} display_msg_t;
