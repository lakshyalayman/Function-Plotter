#define PLUG_IMPLEMENTATION
#include "plug.h"

int main() {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(WIDTH,HEIGHT, "DrawGrid Example");
  Camera2D camera = {0};
  camera.offset = (Vector2){400, 225};
  camera.target = (Vector2){0, 0};
  camera.zoom = 1.0f;
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    int width = GetScreenWidth();
    int height = GetScreenHeight();
    camera.zoom += GetMouseWheelMove() * 0.2f;
    if (camera.zoom < 0.1f) camera.zoom = 0.1f;

    if(IsKeyPressed(KEY_O)){
      camera.target.x = 0;
      camera.target.y = 0;
    }
    if(IsKeyPressed(KEY_Q))break;
    if (IsKeyDown(KEY_RIGHT)) camera.target.x += 5;
    if (IsKeyDown(KEY_LEFT))  camera.target.x -= 5;
    if (IsKeyDown(KEY_UP))    camera.target.y -= 5;
    if (IsKeyDown(KEY_DOWN))  camera.target.y += 5;
    BeginDrawing();
    ClearBackground(BLACK);
    BeginMode2D(camera);

      ScreenGrid(camera,SPACING);
      DrawMathFunction(camera);
      directions(camera);
    EndMode2D();
    EndDrawing();
  }
  CloseWindow();
}
