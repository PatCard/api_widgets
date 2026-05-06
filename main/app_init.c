#include "app_init.h"
#include "config.h"
#include "widget.h"
#include "rotation_task.h"
#include "display_task.h"
#include "widgets/w_clima.h"
#include "widgets/w_bitcoin.h"
#include "widgets/w_hora.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "esp_log.h"

static const char *TAG = "app_init";

/* -------------------------------------------------------
 * REGISTRO DE WIDGETS
 * Para agregar uno nuevo: incluir su header y agregar
 * una línea al array. Nada más cambia.
 * ------------------------------------------------------- */
static const widget_t widgets[] = {
    {
        .name             = "Clima",
        .fetch            = w_clima_fetch,
        .display          = w_clima_display,
        .fetch_interval_ms = 60000,
    },
    {
        .name             = "Bitcoin",
        .fetch            = w_bitcoin_fetch,
        .display          = w_bitcoin_display,
        .fetch_interval_ms = 30000,
    },
    {
        .name             = "Hora",
        .fetch            = w_hora_fetch,
        .display          = w_hora_display,
        .fetch_interval_ms = 1000,
    },
};

static const int WIDGET_COUNT = sizeof(widgets) / sizeof(widgets[0]);

static QueueHandle_t        display_queue = NULL;
static rotation_task_args_t rotation_args = {0};
static display_task_args_t  display_args  = {0};

esp_err_t app_init(SSD1306_t *oled)
{
    display_queue = xQueueCreate(DISPLAY_QUEUE_SIZE, sizeof(display_msg_t));
    if (!display_queue) {
        ESP_LOGE(TAG, "Error creando queue");
        return ESP_FAIL;
    }

    rotation_args.queue        = display_queue;
    rotation_args.widgets      = widgets;
    rotation_args.widget_count = WIDGET_COUNT;

    display_args.queue         = display_queue;
    display_args.oled          = oled;
    display_args.widgets       = widgets;
    display_args.widget_count  = WIDGET_COUNT;

    xTaskCreate(rotation_task, "rotation_task", ROTATION_TASK_STACK, &rotation_args, ROTATION_TASK_PRIO, NULL);
    xTaskCreate(display_task,  "display_task",  DISPLAY_TASK_STACK,  &display_args,  DISPLAY_TASK_PRIO,  NULL);

    ESP_LOGI(TAG, "%d widgets registrados", WIDGET_COUNT);
    return ESP_OK;
}
