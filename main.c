#define PLUG_IMPLEMENTATION
#include "plug.h"

int main(int argc,char *argv[]) {
  if(argc == 1){
    printf("BAD USAGE: ./run.sh \"function\"");
    return -1;
  }
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(WIDTH,HEIGHT, "Function Plotter");
  Camera2D camera = {0};
  camera.offset = (Vector2){400, 225};
  camera.target = (Vector2){0, 0};
  camera.zoom = 1.0f;
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    camera.offset = (Vector2){ GetScreenWidth()/2.0f, GetScreenHeight()/2.0f };
    camera.zoom += GetMouseWheelMove() * 0.2f;
    if (camera.zoom < 0.1f) camera.zoom = 0.1f;
    if(camera.zoom > 3.0f) camera.zoom = 3.0f;
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
      DrawMathFunction(camera,argv[1]);
    
      directions(camera);
    EndMode2D();
      DrawText(TextFormat("Target: X:%.0f Y:%.0f", camera.target.x, -camera.target.y), 10, 10, 20, BLUE);
    EndDrawing();
  }
  CloseWindow();
}
