#ifndef ESCENARIO_H_INCLUDED
#define ESCENARIO_H_INCLUDED

#include "raylib.h"


#define TERRENO_ANCHO 65
#define TERRENO_ALTO 37
#define ALTO_LOSA 32
#define ANCHO_LOSA 32


void EscenarioIniciar();
void EscenarioDibujar(Vector2,int,int);
bool PosicionProtaViable(Vector2);


#endif // ESCENARIO_H_INCLUDED
