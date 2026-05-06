#pragma once

#include "esp_err.h"
#include "ssd1306.h"

esp_err_t w_hora_fetch(char *buf, size_t len);
void      w_hora_display(SSD1306_t *oled, const char *data);
