#ifndef ENEMIGO_H_INCLUDED
#define ENEMIGO_H_INCLUDED


#include "raylib.h"
#define ENEMIGO_ANCHO_FRAME 32
#define ENEMIGO_ALTO_FRAME 32

typedef struct{
    Vector2 posicion;
    Texture2D textura;
    Rectangle region;
    int velocidad;
    Vector2 dir;
}Enemigo;

Enemigo EnemigoCrear(Vector2);//posicion inicial

void EnemigoActualizar(Enemigo*,float);//referencia, delta

void EnemigoDibujar(const Enemigo*);//referencia


#endif // ENEMIGO_H_INCLUDED
