#include "rotation_task.h"
#include "config.h"
#include "esp_log.h"
#include <string.h>

static const char *TAG = "rotation_task";

void rotation_task(void *arg)
{
    rotation_task_args_t *args = (rotation_task_args_t *)arg;
    int current = 0;

    /* Cache de datos por widget */
    static char cache[8][128];
    static uint32_t last_fetch[8] = {0};

    while (1) {
        const widget_t *w = &args->widgets[current];
        uint32_t now = xTaskGetTickCount() * portTICK_PERIOD_MS;

        /* Fetch si es la primera vez o si venció el intervalo */
        if (last_fetch[current] == 0 || (now - last_fetch[current]) >= w->fetch_interval_ms) {
            ESP_LOGI(TAG, "Fetching widget: %s", w->name);
            esp_err_t err = w->fetch(cache[current], sizeof(cache[current]));
            if (err != ESP_OK) {
                snprintf(cache[current], sizeof(cache[current]), "Error");
            }
            last_fetch[current] = now;
        }

        /* Enviar a display_task */
        display_msg_t msg;
        msg.widget_index = current;
        strncpy(msg.data, cache[current], sizeof(msg.data) - 1);
        xQueueSend(args->queue, &msg, pdMS_TO_TICKS(1000));

        /* Esperar antes de rotar */
        vTaskDelay(pdMS_TO_TICKS(WIDGET_ROTATE_MS));

        current = (current + 1) % args->widget_count;
    }
}
