#ifndef PROTA_H_INCLUDED
#define PROTA_H_INCLUDED

#include "raylib.h"
#define PROTA_ANCHO_FRAME 48
#define PROTA_ALTO_FRAME 64
#define PROTA_ANCHO_HITBOX 14
#define PROTA_ALTO_HITBOX 26
#define PROTA_X_HITBOX 18
#define PROTA_Y_HITBOX 20
#define PROTA_VIDA_MAX 100
#define PROTA_ALTO_BARRA_VIDA 3

typedef struct{
    Vector2 posicion;
    Texture2D textura;
    Rectangle region;
    Rectangle hitbox;
    int velocidad;
    Vector2 dir;
    Vector2 losa;
    int vida;
}Prota;

Prota ProtaCrear(Vector2);//posicion inicial

void ProtaActualizar(Prota*,float);//referencia, delta

void ProtaDibujar(const Prota*);//referencia


#endif // PROTA_H_INCLUDED
