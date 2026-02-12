#include "enemigo.h"
#include "raymath.h"
#include "escenario.h"
#include <stdio.h>

const int VEL_ENEMIGO=100;
const char* archivo_enemigo="textures/32rogues/rogues.png";
Texture2D textura_enemigo;

Spawner SpawnEnemigo(){
    Spawner sp;
    Vector2 pos_fake=(Vector2){-1000.0f,-1000.0f};
    sp.plazo=PLAZO_INICIAL_POOL;
    sp.tiempo=0.0f;
    sp.contador=0;
    for (int i = 0; i < CAPACIDAD_POOL; i++){
        Enemigo nuevo=EnemigoCrear(pos_fake);
        sp.pool[i]=nuevo;
    }
    return sp;
}

void SpawnActualizar(Spawner* s,float delta,Prota* p){
    //activamos uno nuevo si se ha cumplido el plazo
    s->tiempo+=delta;
    if(s->tiempo > s->plazo){
        EnemigoActivar(s);
        s->tiempo=0.0f;
    }
    //actualizamos solo los activos
    for (int i = 0; i < CAPACIDAD_POOL; i++){
        // Accedemos directamente a la direcci�n de memoria del enemigo en el array
        if(s->pool[i].activo) EnemigoActualizar(&(s->pool[i]), delta, p,s);
    }

}

void SpawnDibujar(const Spawner* s){
    for (int i = 0; i < CAPACIDAD_POOL; i++){
        if(s->pool[i].activo) EnemigoDibujar(&(s->pool[i]));
    }
}

void EnemigoActivar(Spawner* s){
    //Si ya están todos activos no hago nada
    if(s->contador>=CAPACIDAD_POOL) return;
    //cc activo el primero que me encuentr inactivo y lo pongo en escalera aleatoria
    for(int i=0;i<CAPACIDAD_POOL;i++){
        //Enemigo e=s->pool[i];
        if(!s->pool[i].activo){
            s->pool[i].activo=true;
            Vector2 e=EscaleraAleatoria();//coordenadas de la escalera en losas
            s->pool[i].posicion=(Vector2){e.x*ANCHO_LOSA,e.y*ALTO_LOSA};
            s->contador+=1;
            break;
        }
    }
    //printf("\n... Activando enemigo %d en %d,%d",s->contador, e.posicion.x,e.posicion.y);
}

void EnemigoDesactivar(Spawner* s,Enemigo* e){
    e->activo = false;
    s->contador--;

    // Movemos la hitbox a un lugar donde sea imposible que colisione
    e->hitbox = (Rectangle){ -1000, -1000, 0, 0 };
    e->posicion = (Vector2){ -1000, -1000 };
}


Enemigo EnemigoCrear(Vector2 pos_ini){
    textura_enemigo=LoadTexture(archivo_enemigo);
    Enemigo nuevo={
        pos_ini,
        textura_enemigo,
        (Rectangle){64,64,32,32},
        (Rectangle){0,0,0,0},
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

void EnemigoActualizar(Enemigo* pe,float delta, Prota* pp,Spawner* ps){

    /////////// Colision con prota //////////////////
    if(CheckCollisionRecs(pe->hitbox,pp->hitbox)){
        pp->vida-=pe->danio;
        EnemigoDesactivar(ps,pe);
        printf("\n--------- %d\n",pp->vida);
        return;
    }

    /////////// Movimiento //////////////////

    //Si estamos a su alcance, se dirige a nosotros
    if(Vector2Distance(pe->posicion,pp->posicion)<ALCANCE_ENEMIGO){
        pe->dir=Vector2Subtract(pp->posicion,pe->posicion);
        pe->estado=SIGUIENDO;
    }else{//Si no estaba patrullando ya, lo paso a patrulla y reclaculo dirección aleatoria
        if(pe->estado!=PATRULLA){
            do{
                pe->dir=(Vector2){GetRandomValue(-1,1),GetRandomValue(-1,1)};
            }while(pe->dir.x==0 && pe->dir.y==0);
            pe->estado=PATRULLA;
        }
    }
    pe->dir=Vector2Normalize(pe->dir);

    Vector2 destino={
        pe->posicion.x+delta*VEL_ENEMIGO*pe->dir.x,
        pe->posicion.y+delta*VEL_ENEMIGO*pe->dir.y
    };
    Rectangle nuevoHitbox={destino.x,destino.y,pe->region.width,pe->region.height};

    //Si no está libre... no se puede mover allí. Rebota
    if(UbicacionLibre(nuevoHitbox)){
        pe->posicion=destino;
        pe->hitbox=nuevoHitbox;
    }else{
        pe->dir=Vector2Negate(pe->dir);
    }
}

void EnemigoDibujar(const Enemigo* pe){
    DrawTextureRec(textura_enemigo,pe->region,pe->posicion,WHITE);
}
