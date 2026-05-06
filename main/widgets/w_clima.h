#pragma once

#include "esp_err.h"
#include "ssd1306.h"

esp_err_t w_clima_fetch(char *buf, size_t len);
void      w_clima_display(SSD1306_t *oled, const char *data);
