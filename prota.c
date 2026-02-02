#include "prota.h"
#include "raymath.h"
#include "escenario.h"

const int VEL_INICIAL=200;
const char* archivo_andando="walk.png";
const char* archivo_parado="idle.png";
Texture2D textura_andando;
Texture2D textura_parado;
Rectangle frames[6][8];
int filaFrame=0;
int colFrame=0;
int protaFPS=8;
float protaTiempo=0.0f;


Prota ProtaCrear(Vector2 pos_ini){
    //Cargo las texturas
    textura_andando=LoadTexture(archivo_andando);
    textura_parado=LoadTexture(archivo_parado);
    //Construyo array de fotogramas del personaje
    for(int i=0;i<6;i++){
        for(int j=0;j<8;j++){
            frames[i][j]=(Rectangle){
                j*PROTA_ANCHO_FRAME,
                i*PROTA_ALTO_FRAME,
                PROTA_ANCHO_FRAME,
                PROTA_ALTO_FRAME
            };
        }
    }
    //Intancio el prota
    Prota nuevo={
        pos_ini,
        textura_parado,
        (Rectangle){0,0,48,64},
        (Rectangle){pos_ini.x+PROTA_X_HITBOX,pos_ini.y+PROTA_Y_HITBOX,PROTA_ANCHO_HITBOX,PROTA_ALTO_HITBOX},
        VEL_INICIAL,
        (Vector2){0,0}
    };
    return nuevo;
}

void ProtaActualizar(Prota* pp, float delta){
    //Calculo la dirección en que se quiere mover
    Vector2 dir={0,0};
    if(IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) dir.x--;
    if(IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) dir.x++;
    if(IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) dir.y--;
    if(IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) dir.y++;

    //En función de la dirección, decido la animación
    if(dir.x>0){
        if(dir.y<0) filaFrame=4;
        else filaFrame=5;
    }else if(dir.x<0){
        if(dir.y<0) filaFrame=2;
        else filaFrame=1;
    }else{//dir.x==0
        if(dir.y<0) filaFrame=3;
        else if(dir.y>0) filaFrame=0;
    }
    //En base al tiempo transcurrido cambio de un frame a otro en la misma animación
    protaTiempo+=delta;
    if(protaTiempo>=1.0f/protaFPS){
        colFrame++;
        if(colFrame==8) colFrame=0;
        protaTiempo=0;
    }

    pp->region=frames[filaFrame][colFrame];


    //La normalizo
    pp->dir=Vector2Normalize(dir);

    //Calculo destino del desplazamiento y el nuevo hitbox que tendría allí
    Vector2 destino={pp->posicion.x+(pp->dir.x*pp->velocidad*delta), pp->posicion.y+(pp->dir.y*pp->velocidad*delta)};
    Rectangle nuevoHitbox={
        destino.x+PROTA_X_HITBOX,
        destino.y+PROTA_Y_HITBOX,
        PROTA_ANCHO_HITBOX,
        PROTA_ALTO_HITBOX
    };

    //Compruebo que me pueda mover
    if(!UbicacionLibre(nuevoHitbox)) return;

    //Lo desplazo en esa dirección
    pp->posicion=destino;
     //Actualizo el hitbox
    pp->hitbox=nuevoHitbox;
    //Calculo la losa
    pp->losa.x=(int)(pp->posicion.x/ANCHO_LOSA);
    pp->losa.y=(int)(pp->posicion.y/ALTO_LOSA);

}

void ProtaDibujar(const Prota* pp){
    if (pp->dir.x==0 & pp->dir.y==0){
        DrawTextureRec(textura_parado,pp->region,pp->posicion,WHITE);
    }else{
        DrawTextureRec(textura_andando,pp->region,pp->posicion,WHITE);
    }
}
