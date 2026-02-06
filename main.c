#include "raylib.h"
#include "prota.h"
#include "enemigo.h"
#include "escenario.h"
#include "Menu_incio.h"
#include <time.h>
#include <stdio.h>

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = ANCHO_PANTALLA;
    int screenHeight = ALTO_PANTALLA;
    InitWindow(screenWidth, screenHeight, "Rogue");
    GameScreen currentScreen = LOGO;
    SetTargetFPS(60);
    char texto_fps[20];
    char texto_posicion[30];
    char texto_celda[30];
    int fps_real;
    int framesCounter = 0;
    Texture2D logo = LoadTexture("textures/logo.png");
    //--------------------------------------------------------------------------------------

    SetRandomSeed(time(NULL));
    Prota prota=ProtaCrear((Vector2){384,208});
    Spawner spawner=SpawnEnemigo();
    EscenarioIniciar();
    float delta;

    Camera2D camara={
        (Vector2){screenWidth/2-16,screenHeight/2-16},
        (Vector2){0,0},
        0.0f,
        2.0f,
    };
    //Para limitar la cantidad de elementos del escenario que dibujamos
    //en base a la resolución de pantalla y al zoom
    //Se puede escribir de dos formas diferentes:
    int RANGO_HORIZONTAL=(((screenWidth/ANCHO_LOSA)/2)/camara.zoom)+2;//+2 por dar un margen de sguridad
    int RANGO_VERTICAL=screenHeight/(ALTO_LOSA*2*camara.zoom)+2;//+2 por dar un margen de sguridad
    printf("\nRANGO_HORIZONTAL=%d",RANGO_HORIZONTAL);
    printf("\nRANGO_VERTICAL=%d",RANGO_VERTICAL);

    Vector2 pos_logo;
    pos_logo.x = screenWidth/2  - (logo.width  * 0.5)/2;
    pos_logo.y = screenHeight/2 - (logo.height * 0.5)/2-200;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        switch (currentScreen){
            case LOGO:
            {
                // TODO: Update LOGO screen variables here!
                framesCounter++;    // Count frames
                // Wait for 2 seconds (120 frames) before jumping to TITLE screen
                if (framesCounter > 120){
                    currentScreen = TITLE;
                }
            } break;
            case TITLE:
            {
                // TODO: Update TITLE screen variables here!
                // Press enter to change to GAMEPLAY screen
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP)){
                    currentScreen = GAMEPLAY;
                }
            } break;
            case GAMEPLAY:
            {
                // TODO: Update GAMEPLAY screen variables here!
                // Press enter to change to ENDING screen
                delta=GetFrameTime();
                fps_real=GetFPS();
                sprintf(texto_fps,"fps: %d",fps_real);
                ProtaActualizar(&prota,delta);
                SpawnActualizar(&spawner,delta,&prota);
                sprintf(texto_posicion,"posicion: (%d,%d)",(int)(prota.posicion.x),(int)(prota.posicion.y));
                sprintf(texto_celda,"celda: (%d,%d)",(int)(prota.losa.x),(int)(prota.losa.y));

                camara.target=prota.posicion;
                //camara.zoom+=GetMouseWheelMove()*0.1f;
            } break;
            case ENDING:
            {
                // TODO: Update ENDING screen variables here!
                // Press enter to return to TITLE screen
                UnloadTexture(logo);
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    currentScreen = TITLE;
                }
            } break;
            default: break;
        }
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        switch(currentScreen){
        case LOGO:
        {
            // TODO: Draw LOGO screen here!
            DrawTexture(logo,ANCHO_PANTALLA/2-logo.width/2,ALTO_PANTALLA/2-logo.height/2,WHITE);
            DrawText("WAIT for 2 SECONDS...", 290, 150, 20, GRAY);
        } break;
        case TITLE:
        {
            // TODO: Draw TITLE screen here!
            DrawRectangle(0, 0, screenWidth, screenHeight, BLACK);
            DrawTextureEx(logo,pos_logo,0.0,0.5,WHITE);
            DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN", ANCHO_PANTALLA/3-20, ALTO_PANTALLA/2, 20, GOLD);
        } break;
        case GAMEPLAY:
        {
            // TODO: Draw GAMEPLAY screen here!
            ClearBackground(BLACK);
            BeginMode2D(camara);
            EscenarioDibujar(prota.losa,RANGO_HORIZONTAL,RANGO_VERTICAL);
            SpawnDibujar(&spawner);
            ProtaDibujar(&prota);
            EndMode2D();
            DrawText(texto_fps,10,50,30,YELLOW);
            DrawText(texto_posicion,10,100,30,WHITE);
            DrawText(texto_celda,10,150,30,ORANGE);
        } break;
        case ENDING:
        {
            // TODO: Draw ENDING screen here!
            DrawRectangle(0, 0, screenWidth, screenHeight, BLUE);
            DrawText("ENDING SCREEN", 20, 20, 40, DARKBLUE);
            DrawText("PRESS ENTER or TAP to RETURN to TITLE SCREEN", 120, 220, 20, DARKBLUE);
        } break;
        default: break;
        }
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
