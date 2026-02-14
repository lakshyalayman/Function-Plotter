#ifndef PLUG_H
#define PLUG_H

#include <raylib.h>
#include <math.h>
#include <complex.h>

#define WIDTH 800
#define HEIGHT 450
#define SPACING 40.0f
#define N (3*WIDTH/SPACING + 1)

void directions(Camera2D camera);
void DrawMathFunction(Camera2D camera);
void ScreenGrid(Camera2D camera,float spacing);

#endif // !PLUG_H
#ifdef PLUG_IMPLEMENTATION

void DrawMathFunction(Camera2D camera) {
  int width = GetScreenWidth();
  Vector2 points[width];
  for (int i = 0; i < width; i++) {
    Vector2 worldPos = GetScreenToWorld2D((Vector2){ (float)i, 0 }, camera);
    float x = worldPos.x / SPACING; 
    float y = (x*x)*SPACING;  
    points[i] = (Vector2){ worldPos.x, -y }; 
  }
  DrawLineStrip(points, width, LIME);
}

void directions(Camera2D camera){
  Vector2 pos = GetScreenToWorld2D((Vector2){0,0}, camera);
  DrawText(TextFormat("X: %f",camera.target.x),pos.x,pos.y,20,BLUE);
  DrawText(TextFormat("Y: %f",camera.target.y),pos.x,pos.y+20,20,BLUE);
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
