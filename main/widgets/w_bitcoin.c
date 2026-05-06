#include "w_bitcoin.h"
#include "esp_log.h"
#include "esp_http_client.h"
#include "cJSON.h"
#include <string.h>
#include <stdio.h>

static const char *TAG = "w_bitcoin";

#define BTC_URL "https://api.coingecko.com/api/v3/simple/price?ids=bitcoin&vs_currencies=usd"

static char http_buf[512];
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

esp_err_t w_bitcoin_fetch(char *buf, size_t len)
{
    memset(http_buf, 0, sizeof(http_buf));
    http_len = 0;

    esp_http_client_config_t cfg = {
        .url           = BTC_URL,
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

    cJSON *btc = cJSON_GetObjectItem(root, "bitcoin");
    if (btc) {
        double price = cJSON_GetObjectItem(btc, "usd")->valuedouble;
        snprintf(buf, len, "$%.0f USD", price);
        ESP_LOGI(TAG, "Bitcoin: %s", buf);
    } else {
        snprintf(buf, len, "Sin datos");
    }

    cJSON_Delete(root);
    return ESP_OK;
}

void w_bitcoin_display(SSD1306_t *oled, const char *data)
{
    ssd1306_display_text(oled, 0, " BITCOIN", 8, false);
    ssd1306_display_text(oled, 1, "--------------", 14, false);
    ssd1306_display_text(oled, 3, (char *)data, strlen(data), false);
}
