#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <raylib.h>

#define WIDTH 800
#define HEIGHT 450
#define SPACING 50.0f
#define N (3*WIDTH/SPACING + 1)

Vector2 foo[800];
Vector2 doofoo[800];
Vector2 labubu[800];
Vector2 damru[800];
void bar(){
  for(int i = 0;i<800;i++){
    float val = cexp((float)7*i/800);
    foo[i].x =   i;
    doofoo[i].x =   i;
    foo[i].y =  -i;
    doofoo[i].y =  -val;
    labubu[i].x =   i;
    labubu[i].y =  (float) -1*i*i/WIDTH;
    damru[i].x =   i;
    damru[i].y =  -50*cosf(i/(8*PI)); 
    if(fabsf(doofoo[i].y - foo[i].y) < 0.01f)DrawCircleV(foo[i],10,RED);
  }
}

void upgradedGrid(Camera2D camera,float spacing){
  int width = GetScreenWidth();
  int height = GetScreenHeight();

  Vector2 topLeft = GetScreenToWorld2D((Vector2){0,0}, camera);
  Vector2 bottomRight = GetScreenToWorld2D((Vector2){width,height}, camera);

  float startX = floorf(topLeft.x / spacing) * spacing;
  float startY = floorf(topLeft.y / spacing) * spacing;

  for (float x = startX; x <= bottomRight.x; x += spacing) {
    float thickness = (fabsf(x) < 0.1f) ? 3.0f : 1.0f; 
    Color col = (fabsf(x) < 0.1f) ? WHITE : DARKGRAY;
    DrawLineEx((Vector2){ x, topLeft.y }, (Vector2){ x, bottomRight.y }, thickness, col);
  }
  for (float y = startY; y <= bottomRight.y; y += spacing) {
    float thickness = (fabsf(y) < 0.1f) ? 3.0f : 1.0f; // Thicker line for the X-axis (y=0)
    Color col = (fabsf(y) < 0.1f) ? WHITE : DARKGRAY;
    DrawLineEx((Vector2){ topLeft.x, y }, (Vector2){ bottomRight.x, y }, thickness, col);
  }
}

int count = 0;

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
    if(IsKeyPressed(KEY_Q))break;
    if (IsKeyDown(KEY_RIGHT)) camera.target.x += 5;
    if (IsKeyDown(KEY_LEFT))  camera.target.x -= 5;
    if (IsKeyDown(KEY_UP))    camera.target.y -= 5;
    if (IsKeyDown(KEY_DOWN))  camera.target.y += 5;
    BeginDrawing();
    ClearBackground(BLACK);
    BeginMode2D(camera);
      bar();
      upgradedGrid(camera,SPACING);
      DrawLineStrip(foo,800-1,GOLD);
      DrawLineStrip(doofoo,800-1,LIME);
      DrawLineStrip(labubu,800-1,SKYBLUE);
      DrawLineStrip(damru,800-1,RED);
      
    EndMode2D();
    EndDrawing();
  }
  CloseWindow();
}
