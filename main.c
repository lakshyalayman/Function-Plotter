#include <raylib.h>
#include <stdio.h>
#include <rlgl.h>

int main(void){
  printf("Hello, World!\n");
  const int w = 800,h = 600;
  InitWindow(w,h,"VAMOS");
  Camera2D camera = {0};
  camera.zoom = 1.0f;
  SetTargetFPS(60);
  while(!WindowShouldClose()){
    if(IsKeyPressed(KEY_Q))break;
    BeginDrawing();
    BeginMode2D(camera);
    rlPushMatrix();
      rlTranslatef(0,25*50,0);
      rlRotatef(90,1,0,0);
      DrawGrid(100,50);
    rlPopMatrix();
    EndMode2D();
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
