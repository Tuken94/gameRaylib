#ifndef PROTA_H_INCLUDED
#define PROTA_H_INCLUDED

#include "raylib.h"
#include "escenario.h"

#define PROTA_ANCHO_HITBOX
#define PROTA_ALTO_HITBOX
#define PROTA_X_HITBOX
#define PROTA_Y_HITBOX

typedef struct{
    Vector2 posicion;
    Texture2D textura;
    Rectangle region;
    int velocidad;
    Vector2 dir;
    Vector2 losa;
}Prota;

Prota ProtaCrear(Vector2);//posicion inicial

void ProtaActualizar(Prota*,float);//referencia, direccion

void ProtaDibujar(const Prota*);//referencia


#endif // PROTA_H_INCLUDED
