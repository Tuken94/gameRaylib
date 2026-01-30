#include "raylib.h"
#include "prota.h"
#include "escenario.h"
#include <time.h>
#include <stdio.h>

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 1600;
    int screenHeight = 900;
    InitWindow(screenWidth, screenHeight, "Rogue");
    SetTargetFPS(0);
    char texto_fps[20];
    char texto_posicion[30];
    char texto_celda[30];
    int fps_real;
    //--------------------------------------------------------------------------------------

    SetRandomSeed(time(NULL));
    Prota prota=ProtaCrear((Vector2){384,208});
    EscenarioIniciar();
    float delta;
    Camera2D camara={
        (Vector2){screenWidth/2-16,screenHeight/2-16},
        (Vector2){0,0},
        0.0f,
        2.0f,
    };

    //para limitar el renderizado de elementos que se general en el juego para solo dibujar las que se ven en pantalla

    int RANGO_HORIZONTAL=screenWidth/(ANCHO_LOSA*2*camara.zoom)+2;//(((screenWidth/ANCHO_LOSA)/2)/camara.zoom)+2;
    int RANGO_VERTICAL=screenHeight/(ALTO_LOSA*2*camara.zoom)+2;
    printf("\nRangoH %d \nRangoV %d\n",RANGO_HORIZONTAL,RANGO_VERTICAL);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        delta=GetFrameTime();
        fps_real=GetFPS();
        sprintf(texto_fps,"fps: %d",fps_real);

        ProtaActualizar(&prota,delta);

        sprintf(texto_posicion,"posicion: (%d,%d)",(int)(prota.posicion.x),(int)(prota.posicion.y));
        //Vector2 p=GetWorldToScreen2D(prota.posicion,camara);
        sprintf(texto_celda,"posvent: (%d,%d)",(int)(prota.losa.x),(int)(prota.losa.y));

        camara.target=prota.posicion;
        camara.zoom+=GetMouseWheelMove()*0.1f;


        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode2D(camara);
        EscenarioDibujar(prota.losa,RANGO_HORIZONTAL,RANGO_VERTICAL);
        ProtaDibujar(&prota);
        EndMode2D();
        DrawText(texto_fps,10,50,30,YELLOW);
        DrawText(texto_posicion,10,100,30,WHITE);
        DrawText(texto_celda,10,150,30,ORANGE);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
