#ifndef COMIDA_H_INCLUDED
#define COMIDA_H_INCLUDED

#include "raylib.h"
#include "prota.h"

typedef struct{
    Vector2 posicion;
    Rectangle region;
    Rectangle hitbox;
    int valor;
}Comida;

Comida ComidaCrear();

void ComidaActualizar(Comida*,Prota*);

void ComidaDibujar(const Comida*);

Vector2 ComidaMover(Comida*);

#endif // COMIDA_H_INCLUDED
