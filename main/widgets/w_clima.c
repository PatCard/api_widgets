#include "w_clima.h"
#include "config.h"
#include "esp_log.h"
#include "esp_http_client.h"
#include "cJSON.h"
#include <string.h>
#include <stdio.h>

static const char *TAG = "w_clima";

#define OWM_URL "http://api.openweathermap.org/data/2.5/weather?q=" \
                OWM_CITY "," OWM_COUNTRY "&appid=" OWM_API_KEY \
                "&units=metric&lang=es"

static char http_buf[1024];
static int  http_len = 0;

static esp_err_t http_event_handler(esp_http_client_event_t *evt)
{
    if (evt->event_id == HTTP_EVENT_ON_DATA) {
        int copy = evt->data_len;
        if (http_len + copy < (int)sizeof(http_buf) - 1) {
            memcpy(http_buf + http_len, evt->data, copy);
            http_len += copy;
        }
    }
    return ESP_OK;
}

esp_err_t w_clima_fetch(char *buf, size_t len)
{
    memset(http_buf, 0, sizeof(http_buf));
    http_len = 0;

    esp_http_client_config_t cfg = {
        .url            = OWM_URL,
        .event_handler  = http_event_handler,
        .timeout_ms     = 10000,
    };

    esp_http_client_handle_t client = esp_http_client_init(&cfg);
    esp_err_t err = esp_http_client_perform(client);
    esp_http_client_cleanup(client);

    if (err != ESP_OK) {
        ESP_LOGE(TAG, "HTTP error: %s", esp_err_to_name(err));
        return err;
    }

    /* Parsear JSON */
    cJSON *root = cJSON_Parse(http_buf);
    if (!root) return ESP_FAIL;

    cJSON *main  = cJSON_GetObjectItem(root, "main");
    cJSON *weather = cJSON_GetArrayItem(cJSON_GetObjectItem(root, "weather"), 0);

    if (main && weather) {
        float temp     = cJSON_GetObjectItem(main, "temp")->valuedouble;
        int   humidity = cJSON_GetObjectItem(main, "humidity")->valueint;
        const char *desc = cJSON_GetObjectItem(weather, "description")->valuestring;
        snprintf(buf, len, "%.1f C | %d%%\n%s", temp, humidity, desc);
        ESP_LOGI(TAG, "Clima: %s", buf);
    } else {
        snprintf(buf, len, "Sin datos");
    }

    cJSON_Delete(root);
    return ESP_OK;
}

void w_clima_display(SSD1306_t *oled, const char *data)
{
    char line1[32] = {0};
    char line2[32] = {0};

    sscanf(data, "%31[^\n]\n%31[^\n]", line1, line2);

    ssd1306_display_text(oled, 0, " CLIMA", 6, false);
    ssd1306_display_text(oled, 1, "--------------", 14, false);
    ssd1306_display_text(oled, 3, line1, strlen(line1), false);
    ssd1306_display_text(oled, 5, line2, strlen(line2), false);
}
