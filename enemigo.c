#include "enemigo.h"
#include "raymath.h"
#include "escenario.h"
#include <stdio.h>

const int VEL_ENEMIGO=100;
const char* archivo_enemigo="textures/32rogues/rogues.png";
Texture2D textura_enemigo;

Spawner SpawnEnemigo(){
    Spawner sp;
    Vector2 pos_fake={-10000000,10000000};
    sp.plazo=PLAZO_INICIAL_POOL;
    sp.tiempo=0.0f;
    sp.contador=0;
    for (int i = 0; i < CAPACIDAD_POOL; i++){
        Enemigo nuevo=EnemigoCrear(pos_fake);
        sp.pool[i]=nuevo;
    }
    return sp;
}

void SpawnActualizar(Spawner* s,float delta,const Prota* p){
    //activamos uno nuevo si se ha cumplido el plazo
    s->tiempo+=delta;
    if(s->tiempo > s->plazo){
        EnemigoActivar(s);
        s->tiempo=0.0f;
    }
    //actualizamos solo los activos
    for (int i = 0; i < CAPACIDAD_POOL; i++){
        // Accedemos directamente a la direcci¢n de memoria del enemigo en el array
        if(s->pool[i].activo) EnemigoActualizar(&(s->pool[i]), delta, p);
    }

}

void SpawnDibujar(const Spawner* s){
    for (int i = 0; i < CAPACIDAD_POOL; i++){
        if(s->pool[i].activo) EnemigoDibujar(&(s->pool[i]));
    }
}

void EnemigoActivar(Spawner* s){
    //si ya estan todos activos no hago nada
    for (int i = 0; i < CAPACIDAD_POOL; i++){
        if(!s->pool[i].activo){
            s->pool[i].activo = true; // Modificamos el original
            s->pool[i].posicion = EscaleraAleatoria();

            // Si EscaleraAleatoria devuelve coordenadas de rejilla (0,1,2...), multipl¡calas:
            // s->pool[i].posicion.x *= ANCHO_LOSA;
            // s->pool[i].posicion.y *= ALTO_LOSA;

            s->contador++;
            // Usamos printf con el dato real para debug
            printf("\n... Activando enemigo %d en %.0f,%.0f", s->contador, s->pool[i].posicion.x, s->pool[i].posicion.y);
            break;
        }
    }
    //contabilizo el activo
}

void EnemigoDesactivar(Spawner* s,Enemigo* e){
    e->activo=false;
    s->contador--;
}

Enemigo EnemigoCrear(Vector2 pos_ini){
    textura_enemigo=LoadTexture(archivo_enemigo);
    Enemigo nuevo={
        pos_ini,
        textura_enemigo,
        (Rectangle){64,64,32,32},
        VEL_ENEMIGO,
        {0,0},
        PATRULLA,
        false,
        20
    };
    while(nuevo.dir.x==0 && nuevo.dir.y==0){
        nuevo.dir=(Vector2){GetRandomValue(-1,1),GetRandomValue(-1,1)};
    }
    //nuevo.dir=Vector2Normalize(nuevo.dir);

    return nuevo;
}

void EnemigoActualizar(Enemigo* pe,float delta,const Prota* pp){
    //Si estamos a su alcance, se dirige a nosotros
    if(Vector2Distance(pe->posicion,pp->posicion)<ALCANCE_ENEMIGO){
        pe->dir=Vector2Subtract(pp->posicion,pe->posicion);
        pe->estado=SIGUIENDO;
    }else{
        if(pe->estado!=PATRULLA){
            do{
                pe->dir=(Vector2){GetRandomValue(-1,1),GetRandomValue(-1,1)};
            }while(pe->dir.x==0 && pp->dir.y==0);
            pe->estado=PATRULLA;
        }
    }
    pe->dir=Vector2Normalize(pe->dir);


    //nuevo.dir=Vector2Normalize(nuevo.dir);
    Vector2 destino={
        pe->posicion.x+delta*VEL_ENEMIGO*pe->dir.x,
        pe->posicion.y+delta*VEL_ENEMIGO*pe->dir.y
    };
    //El area que ocupa si se mueve
    Rectangle r={destino.x,destino.y,pe->region.width,pe->region.height};
    //si no esta libre... no se puede mover all¡. Rebota
    if(UbicacionLibre(r)){
        pe->posicion=destino;
    }else{
        pe->dir=Vector2Negate(pe->dir);
    }
}

void EnemigoDibujar(const Enemigo* pe){
    DrawTextureRec(textura_enemigo,pe->region,pe->posicion,WHITE);
}
