#include "raylib.h"
#include <stdlib.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 450

void makeGrid(float spacing){
  float midx = (float) WIDTH/2;
  float midy = (float) HEIGHT/2;
  for(float x =midx;x<2*WIDTH;x+= spacing){
    if(x == midx)
      DrawLineEx((Vector2){(float)WIDTH/2,(float)-HEIGHT}, (Vector2){(float)WIDTH/2,(float)2*HEIGHT},3.0f,WHITE);
    else
      DrawLine(x,-HEIGHT,x,2*HEIGHT,RAYWHITE);
  }
  for(float x = midx;x>-WIDTH;x-= spacing){
    DrawLine(x,-HEIGHT,x,2*HEIGHT,RAYWHITE);
  }
  for(float y = midy;y<2*HEIGHT;y+= spacing){
    if(y == midy)
      DrawLineEx((Vector2){(float)-WIDTH,(float)HEIGHT/2},(Vector2){(float)2*WIDTH,(float)HEIGHT/2},3.0f,WHITE);
    else
      DrawLine(-WIDTH, y,2*WIDTH,y,RAYWHITE);
  }
  for(float y = midy;y>-HEIGHT;y-= spacing){
    DrawLine(-WIDTH, y,2*WIDTH,y,RAYWHITE);
  }
}

int main() {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(WIDTH,HEIGHT, "DrawGrid Example");
  Camera2D camera = {0};
  camera.offset = (Vector2){400, 225};
  camera.target = (Vector2){(float)WIDTH/2, (float)HEIGHT/2};
  camera.zoom = 1.0f;

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    int width = GetScreenWidth();
    int height = GetScreenHeight();
    camera.zoom += GetMouseWheelMove() * 0.1f;
    if (camera.zoom < 0.1f) camera.zoom = 0.1f;
    if(IsKeyPressed(KEY_Q))break;
    if (IsKeyDown(KEY_RIGHT)) camera.target.x += 2;
    if (IsKeyDown(KEY_LEFT))  camera.target.x -= 2;
    if (IsKeyDown(KEY_UP))    camera.target.y -= 2;
    if (IsKeyDown(KEY_DOWN))  camera.target.y += 2;
    BeginDrawing();
    ClearBackground(BLACK);
    BeginMode2D(camera);
        makeGrid(35.0f);
    EndMode2D();
    EndDrawing();
  }
  CloseWindow();
}
