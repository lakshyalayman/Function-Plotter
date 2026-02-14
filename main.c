#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <raylib.h>

#define WIDTH 800
#define HEIGHT 450
#define SPACING 35.0f
#define N (3*WIDTH/SPACING + 1)

Vector2 foo[800];
Vector2 doofoo[800];
//linear function
void bar(){
  for(int i = 0;i<800;i++){
    float val = cexp((float)7*i/800);
    foo[i].x = (float)WIDTH/2 + i;
    doofoo[i].x = (float)WIDTH/2 + i;
    foo[i].y = (float)HEIGHT/2 - i;
    doofoo[i].y = (float)HEIGHT/2 - val;
  }
}

int makeGrid(float spacing){
  float midx = (float) WIDTH/2;
  float midy = (float) HEIGHT/2;
  int numero = 0;
  for(float x =midx;x<=2*WIDTH;x+= spacing){
    if(x == midx)
      DrawLineEx((Vector2){(float)WIDTH/2,(float)-HEIGHT}, (Vector2){(float)WIDTH/2,(float)2*HEIGHT},3.0f,WHITE);
    else
      DrawLine(x,-HEIGHT,x,2*HEIGHT,RAYWHITE);
    numero++;
  }
  for(float x = midx;x>=-WIDTH;x-= spacing){
    if(x == midx)continue;
    DrawLine(x,-HEIGHT,x,2*HEIGHT,RAYWHITE);
    numero++;
  }
  for(float y = midy;y<=2*HEIGHT;y+= spacing){
    if(y == midy)
      DrawLineEx((Vector2){(float)-WIDTH,(float)HEIGHT/2},(Vector2){(float)2*WIDTH,(float)HEIGHT/2},3.0f,WHITE);
    else
      DrawLine(-WIDTH, y,2*WIDTH,y,RAYWHITE);
  }
  for(float y = midy;y>=-HEIGHT;y-= spacing){
    DrawLine(-WIDTH, y,2*WIDTH,y,RAYWHITE);
  }
  return numero;
}

int count = 0;

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
    if (IsKeyDown(KEY_RIGHT)) camera.target.x += 5;
    if (IsKeyDown(KEY_LEFT))  camera.target.x -= 5;
    if (IsKeyDown(KEY_UP))    camera.target.y -= 5;
    if (IsKeyDown(KEY_DOWN))  camera.target.y += 5;
    BeginDrawing();
    ClearBackground(BLACK);
    BeginMode2D(camera);
      bar();
      int curr = makeGrid(SPACING);
      if(count != curr){
        count = curr;
        printf("%d\n",count);
        printf("%d\n",(int)(3*WIDTH/SPACING + 1));
      }
      DrawLineStrip(foo,800-1,GOLD);
      DrawLineStrip(doofoo,800-1,LIME);
      
    EndMode2D();
    EndDrawing();
  }
  CloseWindow();
}
