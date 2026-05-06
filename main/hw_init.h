#pragma once

#include "esp_err.h"
#include "ssd1306.h"

esp_err_t hw_oled_init(SSD1306_t *oled);
esp_err_t hw_wifi_init(void);
