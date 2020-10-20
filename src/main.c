#include <stdio.h>
#include <raylib.h>
#include <rlgl.h>

#include "utils.h"
#ifdef OS_WEB
#include <emscripten/emscripten.h>
#endif

#define WIDTH 800
#define HEIGHT 600

Camera3D camera = {0};
Vector3 cube_position = {0.0f, 0.0f, 0.0f};
Model grid = {0};

int secondsLoc = 0;
float seconds = 0.;
Shader my_shader = {0};

void update_frame()
{
    seconds += GetFrameTime();
        
    SetShaderValue(my_shader, secondsLoc, &seconds, UNIFORM_FLOAT);
    BeginDrawing();
    {

        ClearBackground(BLACK);
        DrawFPS(10, 10);

        BeginMode3D(camera);
        {
            // DrawModelWires(grid, (Vector3){0}, 1., RED);
            DrawModel(grid, (Vector3){0}, 1., WHITE);
            DrawCube(cube_position, 1, 1, 1, RED);
            DrawCubeWires(cube_position, 1, 1, 1, BLUE);
        }
        EndMode3D();

        if (IsKeyDown(KEY_KP_ADD))
            camera.fovy += 1.0f;
        if (IsKeyDown(KEY_KP_SUBTRACT))
            camera.fovy -= 1.0f;

        if (IsKeyPressed(KEY_LEFT))
            cube_position.x -= 1.0f;
        if (IsKeyPressed(KEY_RIGHT))
            cube_position.x += 1.0f;
        if (IsKeyPressed(KEY_UP))
            cube_position.z -= 1.0f;
        if (IsKeyPressed(KEY_DOWN))
            cube_position.z += 1.0f;
    }
    EndDrawing();
}

int main(void)
{
#ifdef OS_Windows_NT
    printf("Windows dettected\n");
#elif defined OS_Linux
    printf("LINUS dettected\n");
#elif defined OS_Darwin
    printf("MacOS dettected\n");
#endif

    InitWindow(WIDTH, HEIGHT, "This is a network test");
    SetTargetFPS(60);

    grid = LoadModelFromMesh(GenMeshPlane(10., 10., 20, 20));

    my_shader = LoadShader("assets/shader.vs", "assets/shader.fs");

    secondsLoc = GetShaderLocation(my_shader, "time");

    grid.materials->shader = my_shader;

    Image img = GenImageChecked(4, 4, 1, 1, ORANGE, DARKBLUE);
    Texture text = LoadTextureFromImage(img);
    UnloadImage(img);
   
    grid.materials[0].maps[MAP_DIFFUSE].texture = text;

    camera.fovy = 45.0f;
    camera.target = (Vector3){.0f, .0f, .0f};
    camera.position = (Vector3){0.0f, 10.0f, 10.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.type = CAMERA_PERSPECTIVE;

#ifdef OS_WEB
    emscripten_set_main_loop(update_frame, 0, 1);
#else
    while (!WindowShouldClose())
    {
        update_frame();
    }
#endif
    UnloadModel(grid);
    UnloadTexture(text);
    CloseWindow();

    return 0;
}