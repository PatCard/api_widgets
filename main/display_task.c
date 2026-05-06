#include "display_task.h"
#include "esp_log.h"

static const char *TAG = "display_task";

void display_task(void *arg)
{
    display_task_args_t *args = (display_task_args_t *)arg;
    display_msg_t msg;

    ssd1306_clear_screen(args->oled, false);
    ssd1306_display_text(args->oled, 0, "  API Widgets", 13, false);
    ssd1306_display_text(args->oled, 1, "  Iniciando...", 14, false);

    ESP_LOGI(TAG, "Display task iniciada");

    while (1) {
        if (xQueueReceive(args->queue, &msg, portMAX_DELAY) == pdTRUE) {
            const widget_t *w = &args->widgets[msg.widget_index];
            ssd1306_clear_screen(args->oled, false);
            w->display(args->oled, msg.data);
        }
    }
}
