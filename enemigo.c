#include "enemigo.h"
#include "raymath.h"

const int VEL_ENEMIGO=100;
const char* archivo_enemigo="textures/32rogues/rogues.png";
Texture2D textura_enemigo;

Enemigo EnemigoCrear(Vector2 pos_ini){
    textura_enemigo=LoadTexture(archivo_enemigo);
    Enemigo nuevo={
        pos_ini,
        textura_enemigo,
        (Rectangle){64,64,32,32},
        VEL_ENEMIGO,
        {0,0}
    };
    while(nuevo.dir.x==0 && nuevo.dir.y==0){
        nuevo.dir=(Vector2){GetRandomValue(-1,1),GetRandomValue(-1,1)};
    }
    nuevo.dir=Vector2Normalize(nuevo.dir);

    return nuevo;
}

void EnemigoActualizar(Enemigo* pe,float delta){
    pe->posicion.x+=delta*VEL_ENEMIGO*pe->dir.x;
    pe->posicion.y+=delta*VEL_ENEMIGO*pe->dir.y;
}

void EnemigoDibujar(const Enemigo* pe){
    DrawTextureRec(textura_enemigo,pe->region,pe->posicion,WHITE);
}
