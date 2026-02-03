#ifndef MENU_INCIO_H_INCLUDED
#define MENU_INCIO_H_INCLUDED

#include "raylib.h"

#define ALTO_PANTALLA 900
#define ANCHO_PANTALLA 1600

typedef enum GameScreen {
    LOGO = 0,
    TITLE,
    GAMEPLAY,
    ENDING
} GameScreen;

#endif // MENU_INCIO_H_INCLUDED
