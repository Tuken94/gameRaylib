#ifndef ENEMIGO_H_INCLUDED
#define ENEMIGO_H_INCLUDED


#include "raylib.h"
#include "prota.h"
#include <stdbool.h>
#define ENEMIGO_ANCHO_FRAME 32
#define ENEMIGO_ALTO_FRAME 32
#define CAPACIDAD_POOL 100
#define ALCANCE_ENEMIGO 160
#define PLAZO_INICIAL_POOL 3.0f

typedef enum estadoEnemigo {PATRULLA=0, SIGUIENDO}estadoEnemigo;

typedef struct{
    Vector2 posicion;
    Texture2D textura;
    Rectangle region;
    int velocidad;
    Vector2 dir;
    estadoEnemigo estado;
    bool activo
}Enemigo;

typedef struct{
    Enemigo pool[CAPACIDAD_POOL];
    float plazo;//segundos entre creacion de enemigos
    float tiempo;
    int contador;
}Spawner;

Spawner SpawnEnemigo();

void SpawnActualizar(Spawner*,float,const);

void SpawnDibujar();

void EnemigoActivar(Spawner*)

Enemigo EnemigoCrear(Vector2);//posicion inicial

void EnemigoActualizar(Enemigo*,float,Prota*);//referencia, delta

void EnemigoDibujar(const Enemigo*);//referencia


#endif // ENEMIGO_H_INCLUDED
