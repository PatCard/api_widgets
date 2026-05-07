#include "w_clima.h"
#include "config.h"
#include "weather_icons.h"
#include "esp_log.h"
#include "esp_http_client.h"
#include "cJSON.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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

/*
 * buf format: "TEMP|HUMIDITY|DESCRIPTION|ICON_CODE|IS_NIGHT"
 * ej:         "18.5|72|cielo claro|800|0"
 */
esp_err_t w_clima_fetch(char *buf, size_t len)
{
    memset(http_buf, 0, sizeof(http_buf));
    http_len = 0;

    esp_http_client_config_t cfg = {
        .url           = OWM_URL,
        .event_handler = http_event_handler,
        .timeout_ms    = 10000,
    };

    esp_http_client_handle_t client = esp_http_client_init(&cfg);
    esp_err_t err = esp_http_client_perform(client);
    esp_http_client_cleanup(client);

    if (err != ESP_OK) {
        ESP_LOGE(TAG, "HTTP error: %s", esp_err_to_name(err));
        return err;
    }

    cJSON *root = cJSON_Parse(http_buf);
    if (!root) return ESP_FAIL;

    cJSON *main_obj = cJSON_GetObjectItem(root, "main");
    cJSON *weather_arr = cJSON_GetObjectItem(root, "weather");
    cJSON *weather = cJSON_GetArrayItem(weather_arr, 0);

    if (main_obj && weather) {
        float temp       = (float)cJSON_GetObjectItem(main_obj, "temp")->valuedouble;
        int   humidity   = cJSON_GetObjectItem(main_obj, "humidity")->valueint;
        const char *desc = cJSON_GetObjectItem(weather, "description")->valuestring;
        int   icon_code  = cJSON_GetObjectItem(weather, "id")->valueint;
        const char *icon = cJSON_GetObjectItem(weather, "icon")->valuestring;
        bool is_night    = (icon && icon[strlen(icon)-1] == 'n');

        snprintf(buf, len, "%.1f|%d|%s|%d|%d", temp, humidity, desc, icon_code, is_night ? 1 : 0);
        ESP_LOGI(TAG, "Clima: %s", buf);
    } else {
        snprintf(buf, len, "0|0|sin datos|800|0");
    }

    cJSON_Delete(root);
    return ESP_OK;
}

void w_clima_display(SSD1306_t *oled, const char *data)
{
    float temp = 0;
    int   humidity = 0;
    char  desc[32] = {0};
    int   icon_code = 800;
    int   is_night = 0;

    sscanf(data, "%f|%d|%31[^|]|%d|%d", &temp, &humidity, desc, &icon_code, &is_night);

    const uint8_t *icon = weather_get_icon(icon_code, is_night);

    char line_temp[20];
    char line_hum[20];
    snprintf(line_temp, sizeof(line_temp), "%.1f C", temp);
    snprintf(line_hum,  sizeof(line_hum),  "Hum: %d%%", humidity);

    ssd1306_clear_screen(oled, false);

    /* Icono 16x16 en esquina superior izquierda */
    ssd1306_bitmaps(oled, 0, 0, icon, 16, 16, false);

    /* Texto a la derecha del icono */
    ssd1306_display_text(oled, 0, " CLIMA",    6,  false);
    ssd1306_display_text(oled, 2, line_temp,   strlen(line_temp), false);
    ssd1306_display_text(oled, 4, line_hum,    strlen(line_hum),  false);
    ssd1306_display_text(oled, 6, desc,        strlen(desc),      false);
}