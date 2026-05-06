#include "esp_log.h"
#include "ssd1306.h"
#include "hw_init.h"
#include "app_init.h"

static const char *TAG = "main";

void app_main(void)
{
    static SSD1306_t oled;

    ESP_ERROR_CHECK(hw_wifi_init());
    ESP_ERROR_CHECK(hw_oled_init(&oled));
    ESP_ERROR_CHECK(app_init(&oled));

    ESP_LOGI(TAG, "Sistema iniciado");
}
