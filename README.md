# API Widgets — LilyGo T3 V1.6.1

Proyecto ESP32 que consume APIs REST y muestra información rotativa en una pantalla OLED SSD1306 de 128x64 px. Desarrollado con ESP-IDF v5.3.1 en entorno dockerizado.

---

## Hardware

| Componente | Detalle |
|---|---|
| Placa | LilyGo TTGO T3 V1.6.1 |
| MCU | ESP32 |
| Display | OLED SSD1306 128x64 I2C |
| SDA | GPIO 21 |
| SCL | GPIO 22 |

---

## Entorno de desarrollo

- ESP-IDF v5.3.1 en contenedor Docker
- VS Code + Remote SSH + Dev Containers
- Librería OLED: [nopnop2002/esp-idf-ssd1306](https://github.com/nopnop2002/esp-idf-ssd1306)

### Levantar el entorno

```bash
# Desde VS Code en tu PC
# 1. Conectar por SSH al servidor
# 2. Abrir carpeta /home/user/esp32/api_widgets
# 3. Ctrl+Shift+P → "Dev Containers: Reopen in Container"
```

### Compilar y flashear

```bash
idf.py set-target esp32
idf.py build
idf.py -p /dev/ttyACM0 flash monitor
```

---

## Funcionalidades

### Sistema de widgets rotativo
Cada widget es una struct con función de fetch y función de display. La rotación es automática cada N segundos (configurable). Para agregar un nuevo widget solo se agrega un elemento al array en `app_init.c` sin modificar el resto del código.

```c
typedef struct {
    const char *name;
    esp_err_t  (*fetch)(char *buf, size_t len);
    void       (*display)(SSD1306_t *oled, const char *data);
    uint32_t   fetch_interval_ms;
} widget_t;
```

### Widgets disponibles

| Widget | API | Intervalo |
|---|---|---|
| Clima | OpenWeatherMap | 60 s |
| Bitcoin | CoinGecko | 30 s |
| Hora | NTP (pool.ntp.org) | 1 s |

### Iconos OLED monocromo
El widget de clima muestra un ícono 16x16 px según la condición climática reportada por OpenWeatherMap:

| Condición | Código OWM |
|---|---|
| Sol | 800 día |
| Noche despejada | 800 noche |
| Parcialmente nublado | 801-802 |
| Nublado | 803-804 |
| Llovizna | 3xx |
| Lluvia | 5xx |
| Tormenta | 2xx |
| Nieve | 6xx |
| Neblina / Niebla | 7xx |

---

## Estructura del proyecto

```
api_widgets/
├── .devcontainer/
│   ├── devcontainer.json
│   └── Dockerfile
├── CMakeLists.txt
├── components/
│   └── ssd1306/              ← componente local nopnop2002
└── main/
    ├── main.c                ← solo llamadas a init
    ├── config.h              ← constantes, pines, API keys
    ├── widget.h              ← struct widget_t y display_msg_t
    ├── hw_init.c/h           ← WiFi, I2C, OLED
    ├── app_init.c/h          ← registro de widgets, queue, tasks
    ├── rotation_task.c/h     ← rota widgets cada N segundos
    ├── display_task.c/h      ← recibe de queue, actualiza OLED
    ├── CMakeLists.txt
    ├── idf_component.yml
    └── widgets/
        ├── weather_icons.h   ← bitmaps 16x16 por condición
        ├── w_clima.c/h       ← OpenWeatherMap
        ├── w_bitcoin.c/h     ← CoinGecko
        └── w_hora.c/h        ← NTP
```

---

## Configuración

Editar `main/config.h`:

```c
#define WIFI_SSID        "tu_red"
#define WIFI_PASSWORD    "tu_password"
#define OWM_API_KEY      "tu_api_key"
#define OWM_CITY         "Santiago"
#define OWM_COUNTRY      "CL"
#define WIDGET_ROTATE_MS  10000   // tiempo entre widgets (ms)
```

---

## Cómo agregar un nuevo widget

1. Crear `main/widgets/w_nuevo.h` y `w_nuevo.c` con las funciones `fetch` y `display`
2. Incluir el header en `app_init.c`
3. Agregar una entrada al array `widgets[]`:

```c
{
    .name              = "Nuevo",
    .fetch             = w_nuevo_fetch,
    .display           = w_nuevo_display,
    .fetch_interval_ms = 30000,
},
```

4. Agregar el `.c` al `CMakeLists.txt` del main
5. Compilar — nada más cambia

---

## Arquitectura

```
WiFi/Internet
      │
      ▼
rotation_task  ──fetch──►  widget.fetch()  ──►  API REST
      │
      │ queue (display_msg_t)
      ▼
display_task  ──►  widget.display()  ──►  OLED SSD1306
```
