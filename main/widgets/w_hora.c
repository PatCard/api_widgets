#include "w_hora.h"
#include "esp_log.h"
#include "esp_sntp.h"
#include <time.h>
#include <stdio.h>
#include <string.h>

static const char *TAG = "w_hora";
static bool sntp_initialized = false;

esp_err_t w_hora_fetch(char *buf, size_t len)
{
    if (!sntp_initialized) {
        esp_sntp_setoperatingmode(SNTP_OPMODE_POLL);
        esp_sntp_setservername(0, "pool.ntp.org");
        esp_sntp_init();

        /* Zona horaria Santiago */
        setenv("TZ", "CLT4CLST,M10.2.6/24,M3.2.6/24", 1);
        tzset();

        sntp_initialized = true;
        ESP_LOGI(TAG, "SNTP iniciado");

        /* Esperar sincronización */
        int retry = 0;
        while (sntp_get_sync_status() == SNTP_SYNC_STATUS_RESET && retry < 10) {
            vTaskDelay(pdMS_TO_TICKS(2000));
            retry++;
        }
    }

    time_t now;
    struct tm timeinfo;
    time(&now);
    localtime_r(&now, &timeinfo);

    strftime(buf, len, "%H:%M:%S\n%d/%m/%Y", &timeinfo);
    ESP_LOGI(TAG, "Hora: %s", buf);
    return ESP_OK;
}

void w_hora_display(SSD1306_t *oled, const char *data)
{
    char line1[32] = {0};
    char line2[32] = {0};

    sscanf(data, "%31[^\n]\n%31[^\n]", line1, line2);

    ssd1306_display_text(oled, 0, " HORA NTP", 9, false);
    ssd1306_display_text(oled, 1, "--------------", 14, false);
    ssd1306_display_text(oled, 3, line1, strlen(line1), false);
    ssd1306_display_text(oled, 5, line2, strlen(line2), false);
}
