#ifndef PLUG_H
#define PLUG_H

#include <raylib.h>
#include <math.h>
#include <complex.h>
#include "tinyexpr.h"
#include <stdio.h>

#define WIDTH 800
#define HEIGHT 450
#define SPACING 40.0f
#define N (3*WIDTH/SPACING + 1)

extern int counta;

void directions(Camera2D camera);
void DrawMathFunction(Camera2D camera,char *stringFunction,int curr);
void ScreenGrid(Camera2D camera,float spacing);

#endif // !PLUG_H
// #define PLUG_IMPLEMENTATION
#ifdef PLUG_IMPLEMENTATION

void DrawMathFunction(Camera2D camera,char *stringFunction,int curr) {
  int width = GetScreenWidth();
  double x_var = 0;
  Vector2 points[width];
  Vector2 bottomPoints[width];
  Color color;
  int count = 0;
  bool marker = false;
  te_variable vars[] = {
    {"x",&x_var}
  };
  int err;
  te_expr *userFunction = te_compile(stringFunction,vars,1,&err);
  if(userFunction){
    for (int i = 0; i < width; i++) {
      Vector2 worldPos = GetScreenToWorld2D((Vector2){ (float)i, 0 }, camera);
      x_var = worldPos.x / SPACING; 
      float y = te_eval(userFunction)*SPACING;
      points[i] = (Vector2){worldPos.x, -y }; 
    }
    te_free(userFunction);
    color = ColorFromHSV(360*((float)curr/counta),1.00,1.00);
    DrawLineStrip(points, width,color);
  }else{
    int width = GetScreenWidth();
    int height = GetScreenHeight();
    DrawText("code broke :(",(float)width/2,(float)height/2,30,RED);
  }
}

void directions(Camera2D camera){
  DrawCircle(camera.target.x,camera.target.y,2,RED);
}

void ScreenGrid(Camera2D camera,float spacing){
  float width = GetScreenWidth();
  float height = GetScreenHeight();

  Vector2 topLeft = GetScreenToWorld2D((Vector2){0,0}, camera);
  Vector2 bottomRight = GetScreenToWorld2D((Vector2){width,height}, camera);

  float startX = floorf(topLeft.x / spacing) * spacing;
  float startY = floorf(topLeft.y / spacing) * spacing;

  for (float x = startX; x <= bottomRight.x; x += spacing) {
    float thickness = (fabsf(x) < 0.1f) ? 2.0f : 1.0f; 
    Color col = (fabsf(x) < 0.1f) ? WHITE : DARKGRAY;
    DrawLineEx((Vector2){ x, topLeft.y }, (Vector2){ x, bottomRight.y }, thickness, col);
  }

  for (float y = startY; y <= bottomRight.y; y += spacing) {
    float thickness = (fabsf(y) < 0.1f) ? 3.0f : 1.0f;
    Color col = (fabsf(y) < 0.1f) ? WHITE : DARKGRAY;
    DrawLineEx((Vector2){ topLeft.x, y }, (Vector2){ bottomRight.x, y }, thickness, col);
  }
}
#endif
