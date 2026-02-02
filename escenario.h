#ifndef ESCENARIO_H_INCLUDED
#define ESCENARIO_H_INCLUDED

#include "raylib.h"

#define TERRENO_ANCHO 65
#define TERRENO_ALTO 37*2
#define ANCHO_LOSA 32
#define ALTO_LOSA 32


void EscenarioIniciar();
void EscenarioDibujar(Vector2,int,int);
bool UbicacionLibre(Rectangle);
Vector2 EscaleraAleatoria();

#endif // ESCENARIO_H_INCLUDED
