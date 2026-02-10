#include "comida.h"
#include "escenario.h"


const char* ARCHIVO_COMIDA="textures/32rogues/tiles.png";
Texture2D texturaComida;

Comida ComidaCrear(){
    texturaComida=LoadTexture(ARCHIVO_COMIDA);
    Comida comida={
        (Vector2){0,0},
        (Rectangle){32,640,32,32},
        (Rectangle){0,0,0,0},
        15
    };
    ComidaMover(&comida);
    return comida;
}

void ComidaActualizar(Comida* c, Prota* p){
    if(CheckCollisionRecs(c->hitbox,p->hitbox)){
        ComidaMover(c);
        p->vida+=c->valor;
    }
}

void ComidaDibujar(const Comida* c){
    DrawTextureRec(texturaComida,c->region,c->posicion,WHITE);
}

Vector2 ComidaMover(Comida* c){
    Vector2 nueva=PosicionLibreAleatoria();
    c->posicion=nueva;
    c->hitbox=(Rectangle){nueva.x,nueva.y,32,32};
}










