#pragma once
#include <stdint.h>

/*
 * Iconos clima 16x16 px para SSD1306
 * Formato: 16 filas x 2 bytes por fila = 32 bytes por icono
 * Bit 1 = pixel encendido, MSB a la izquierda
 *
 * Uso: ssd1306_bitmaps(&oled, x, y, icon, 16, 16, false);
 */

/* SOL (codigo OWM: 800 dia) */
static const uint8_t ICON_SOL[32] = {
    0b00000001, 0b10000000, // fila 0  - rayos arriba
    0b00000001, 0b10000000, // fila 1
    0b01000000, 0b00000010, // fila 2  - rayos diagonales
    0b00100111, 0b11100100, // fila 3  - inicio disco
    0b00011111, 0b11111000, // fila 4
    0b00001111, 0b11110000, // fila 5  - disco lleno
    0b10001111, 0b11110001, // fila 6  - rayos laterales
    0b10001111, 0b11110001, // fila 7
    0b00001111, 0b11110000, // fila 8
    0b00011111, 0b11111000, // fila 9
    0b00100111, 0b11100100, // fila 10 - fin disco
    0b01000000, 0b00000010, // fila 11 - rayos diagonales
    0b00000001, 0b10000000, // fila 12
    0b00000001, 0b10000000, // fila 13
    0b00000000, 0b00000000, // fila 14
    0b00000000, 0b00000000, // fila 15
};

/* PARCIAL (801-802 dia): sol + nube */
static const uint8_t ICON_PARCIAL[32] = {
    0b00000001, 0b10000000, // fila 0  - rayo sol arriba
    0b00000001, 0b10000000, // fila 1
    0b01000011, 0b11000010, // fila 2  - disco sol
    0b00000111, 0b11100000, // fila 3
    0b10000111, 0b11100001, // fila 4  - rayos laterales
    0b10000111, 0b11100001, // fila 5
    0b00000011, 0b11000000, // fila 6  - fin disco
    0b00001110, 0b00111000, // fila 7  - nube trasera outline
    0b00011111, 0b11111100, // fila 8
    0b00010000, 0b00011100, // fila 9  - hueco nube trasera
    0b11111000, 0b00111111, // fila 10 - nube delantera
    0b11111111, 0b11111111, // fila 11
    0b10000000, 0b00000001, // fila 12 - hueco nube delantera
    0b11111111, 0b11111111, // fila 13 - base nube
    0b01111111, 0b11111110, // fila 14
    0b00000000, 0b00000000, // fila 15
};

/* NUBLADO (803-804): nube grande con perfil bumpy */
static const uint8_t ICON_NUBLADO[32] = {
    0b00000000, 0b00000000, // fila 0
    0b00000001, 0b10000000, // fila 1  - bump izquierdo
    0b00000011, 0b11000000, // fila 2
    0b00011111, 0b11100000, // fila 3  - bump central
    0b00111111, 0b11110000, // fila 4
    0b01111001, 0b11111000, // fila 5  - bump derecho
    0b11111111, 0b11111100, // fila 6
    0b11111111, 0b11111100, // fila 7
    0b10000000, 0b00000100, // fila 8  - hueco interior
    0b10000000, 0b00000100, // fila 9
    0b11111111, 0b11111100, // fila 10 - base nube
    0b11111111, 0b11111100, // fila 11
    0b01111111, 0b11111000, // fila 12
    0b00000000, 0b00000000, // fila 13
    0b00000000, 0b00000000, // fila 14
    0b00000000, 0b00000000, // fila 15
};

/* LLUVIA (5xx) */
static const uint8_t ICON_LLUVIA[32] = {
    0b00000000, 0b00000000, // fila 0
    0b00001111, 0b11000000, // fila 1  - nube
    0b00011111, 0b11100000, // fila 2
    0b01111111, 0b11111000, // fila 3
    0b11111111, 0b11111100, // fila 4
    0b10000000, 0b00000100, // fila 5  - hueco
    0b11111111, 0b11111100, // fila 6
    0b11111111, 0b11111100, // fila 7
    0b01111111, 0b11111000, // fila 8
    0b00100100, 0b10010000, // fila 9  - gotas
    0b00100100, 0b10010000, // fila 10
    0b00010010, 0b01001000, // fila 11
    0b00010010, 0b01001000, // fila 12
    0b00001001, 0b00100100, // fila 13
    0b00001001, 0b00100100, // fila 14
    0b00000000, 0b00000000, // fila 15
};

/* LLOVIZNA (3xx) */
static const uint8_t ICON_LLOVIZNA[32] = {
    0b00000000, 0b00000000, // fila 0
    0b00001111, 0b11000000, // fila 1
    0b00011111, 0b11100000, // fila 2
    0b01111111, 0b11111000, // fila 3
    0b11111111, 0b11111100, // fila 4
    0b10000000, 0b00000100, // fila 5
    0b11111111, 0b11111100, // fila 6
    0b11111111, 0b11111100, // fila 7
    0b01111111, 0b11111000, // fila 8
    0b00010010, 0b01000000, // fila 9  - gotas pequeñas
    0b00010010, 0b01000000, // fila 10
    0b00001001, 0b00100000, // fila 11
    0b00001001, 0b00100000, // fila 12
    0b00000000, 0b00000000, // fila 13
    0b00000000, 0b00000000, // fila 14
    0b00000000, 0b00000000, // fila 15
};

/* TORMENTA (2xx) */
static const uint8_t ICON_TORMENTA[32] = {
    0b00000000, 0b00000000, // fila 0
    0b00001111, 0b11000000, // fila 1  - nube oscura
    0b00011111, 0b11100000, // fila 2
    0b01111111, 0b11111000, // fila 3
    0b11111111, 0b11111100, // fila 4
    0b10000000, 0b00000100, // fila 5
    0b11111111, 0b11111100, // fila 6
    0b11111111, 0b11111100, // fila 7
    0b01111111, 0b11111000, // fila 8
    0b00000111, 0b10000000, // fila 9  - rayo zigzag
    0b00001111, 0b00000000, // fila 10
    0b00000111, 0b10000000, // fila 11
    0b00001111, 0b00000000, // fila 12
    0b00000011, 0b00000000, // fila 13
    0b00100100, 0b10000000, // fila 14 - gotas laterales
    0b00000000, 0b00000000, // fila 15
};

/* NIEVE (6xx) */
static const uint8_t ICON_NIEVE[32] = {
    0b00000000, 0b00000000, // fila 0
    0b00001111, 0b11000000, // fila 1  - nube
    0b00011111, 0b11100000, // fila 2
    0b01111111, 0b11111000, // fila 3
    0b11111111, 0b11111100, // fila 4
    0b10000000, 0b00000100, // fila 5
    0b11111111, 0b11111100, // fila 6
    0b11111111, 0b11111100, // fila 7
    0b01111111, 0b11111000, // fila 8
    0b00100010, 0b10001000, // fila 9  - copos: cruz
    0b01110111, 0b01110000, // fila 10
    0b00100010, 0b10001000, // fila 11
    0b00010001, 0b00000100, // fila 12 - copo 2
    0b00111011, 0b10001100, // fila 13
    0b00010001, 0b00000100, // fila 14
    0b00000000, 0b00000000, // fila 15
};

/* NEBLINA (7xx) */
static const uint8_t ICON_NEBLINA[32] = {
    0b00000000, 0b00000000, // fila 0
    0b11111111, 0b11111110, // fila 1  - linea larga
    0b00000000, 0b00000000, // fila 2
    0b01111111, 0b11111100, // fila 3  - linea corta
    0b00000000, 0b00000000, // fila 4
    0b11111111, 0b11111110, // fila 5  - linea larga
    0b00000000, 0b00000000, // fila 6
    0b00111111, 0b11111000, // fila 7  - linea mas corta
    0b00000000, 0b00000000, // fila 8
    0b11111111, 0b11111110, // fila 9
    0b00000000, 0b00000000, // fila 10
    0b01111111, 0b11111100, // fila 11
    0b00000000, 0b00000000, // fila 12
    0b11111111, 0b11111110, // fila 13
    0b00000000, 0b00000000, // fila 14
    0b00000000, 0b00000000, // fila 15
};

/* NOCHE DESPEJADA (800 noche): luna menguante + estrellas */
static const uint8_t ICON_NOCHE[32] = {
    0b00000111, 0b10000000, // fila 0  - punta luna arriba
    0b00001111, 0b10000000, // fila 1
    0b00011110, 0b00100000, // fila 2  - estrella
    0b00111100, 0b00000000, // fila 3
    0b01111000, 0b00000000, // fila 4
    0b01110000, 0b00000000, // fila 5
    0b01110000, 0b01110000, // fila 6  - estrella
    0b01110000, 0b00000000, // fila 7
    0b01111000, 0b00000000, // fila 8
    0b00111100, 0b00000000, // fila 9
    0b00011111, 0b00000000, // fila 10
    0b00001111, 0b10100000, // fila 11 - estrella
    0b00000111, 0b10000000, // fila 12 - punta luna abajo
    0b00000000, 0b00000000, // fila 13
    0b00000000, 0b00000000, // fila 14
    0b00000000, 0b00000000, // fila 15
};

/*
 * Selecciona icono segun codigo OWM y sufijo dia/noche
 * icon_code: codigo numerico OWM (ej: 800)
 * is_night:  true si el sufijo del icono es 'n'
 */
static inline const uint8_t *weather_get_icon(int icon_code, bool is_night)
{
    if (is_night && icon_code == 800) return ICON_NOCHE;
    if (icon_code >= 200 && icon_code < 300) return ICON_TORMENTA;
    if (icon_code >= 300 && icon_code < 400) return ICON_LLOVIZNA;
    if (icon_code >= 500 && icon_code < 600) return ICON_LLUVIA;
    if (icon_code >= 600 && icon_code < 700) return ICON_NIEVE;
    if (icon_code >= 700 && icon_code < 800) return ICON_NEBLINA;
    if (icon_code == 800)                    return ICON_SOL;
    if (icon_code == 801 || icon_code == 802) return ICON_PARCIAL;
    return ICON_NUBLADO;
}