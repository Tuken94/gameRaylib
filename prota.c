#include "prota.h"
#include "raymath.h"

const int VEL_INICIAL=100;
const char* archivo_prota="textures/Sprites/Walk/walk.png";
Rectangle frame[0][0];
int filaframe=0;
int colFrame=0
int protaFPS=5;

Prota ProtaCrear(Vector2 pos_ini){
    Prota nuevo={
        pos_ini,
        LoadTexture(archivo_prota),
        (Rectangle){0,0,48,64},
        VEL_INICIAL,
        (Vector2){0,0}
    };
    return nuevo;
}

void ProtaActualizar(Prota* pp, float delta){
    //calculo la direccion a la que se quiere mover
    Vector2 dir={0,0};
    if(IsKeyDown(KEY_A)||(IsKeyDown(KEY_LEFT))) dir.x--;
    if(IsKeyDown(KEY_D)||(IsKeyDown(KEY_RIGHT))) dir.x++;
    if(IsKeyDown(KEY_W)||(IsKeyDown(KEY_UP))) dir.y--;
    if(IsKeyDown(KEY_S)||(IsKeyDown(KEY_DOWN))) dir.y++;

    /*
    //en funcion de la direccion pondra un frame

    if(dir.x>0){
        if(dir.y<0) filaFrame-4;
        else filaFrame-5;

    }

    */
    //normalizo la direccion
    pp->dir=Vector2Normalize(dir);
    //calculo destino del desplazamiento
    Vector2 destino={pp->posicion.x+(pp->dir.x*pp->velocidad*delta), pp->posicion.y+(pp->dir.y*pp->velocidad*delta)};
    //compruebo si me puedo mover
    if(!PosicionProtaViable(destino)) return;
    //se desplaza
    pp->posicion=destino;
    //calculo la losa
    pp->losa.x=(int)(pp->posicion.x/ANCHO_LOSA);
    pp->losa.y=(int)(pp->posicion.y/ALTO_LOSA);

    //
}

void ProtaDibujar(const Prota* pp){
    DrawTextureRec(pp->textura,pp->region,pp->posicion,WHITE);
}
