#pragma once

#include "raylib.h"
#include "raymath.h"
#include <stdlib.h>

// Screen struct
typedef struct Screen {
  struct Screen *parent;
  RenderTexture2D renderTexture;
  Vector2 internalResolution;
  Vector2 targetPosition;
  Vector2 targetResolution;
} Screen;

// --- Vector2 helper functions (small utility replacements for missing ops) ---
static inline Vector2 V2(float x, float y) {
  Vector2 v;
  v.x = x;
  v.y = y;
  return v;
}
static inline float minf(float a, float b) { return a < b ? a : b; }

// --- Screen API ---

// Allocate and create a new Screen. Caller should later call Screen_Unload and
// free().
Screen *Screen_New(Vector2 resolution) {
  Screen *s = (Screen *)malloc(sizeof(Screen));
  if (!s)
    return NULL;

  int virtualWidth = (int)resolution.x;
  int virtualHeight = (int)resolution.y;

  // Load render texture with internal (virtual) resolution
  s->renderTexture = LoadRenderTexture(virtualWidth, virtualHeight);
  s->internalResolution = resolution;
  s->parent = NULL;
  s->targetPosition = V2(0, 0);
  s->targetResolution = resolution;
  return s;
}

// Unload render texture and free the Screen
void Screen_Unload(Screen *s) {
  if (!s)
    return;
  UnloadRenderTexture(s->renderTexture);
  free(s);
}

// Begin drawing to this screen's render texture
void Screen_BeginDrawing(Screen *s) {
  if (!s)
    return;
  BeginTextureMode(s->renderTexture);
}

// End drawing to render texture and render it to the screen with letterboxing
void Screen_EndDrawing(Screen *s) {
  if (!s)
    return;
  EndTextureMode();
  // After finishing drawing to the texture, render it (with letterbox)
  // We'll call the common render function below:
  // (Keep behaviour same as Go: calculates scale to fit internal resolution
  // into actual render size) Note: Render() uses Raylib's current render
  // width/height. We'll just call Screen_Render here. (Kept separate for
  // clarity.) (See Screen_Render implementation below.) Render now: (function
  // defined after) Inline call:
  // -- compute RS (render size)
  Vector2 RS = V2((float)GetRenderWidth(), (float)GetRenderHeight());
  // Temporarily set targetResolution to RS so Scale() computes scale against RS
  s->targetResolution = RS;
  // Fractionally scale internal resolution
  float scale = minf(s->targetResolution.x / s->internalResolution.x,
                     s->targetResolution.y / s->internalResolution.y);
  s->targetResolution = Vector2Scale(s->internalResolution, scale);

  // Area remaining (letterbox)
  float remainingW = RS.x - s->targetResolution.x;
  float remainingH = RS.y - s->targetResolution.y;

  // Center the drawn texture
  s->targetPosition.x = remainingW * 0.5f;
  s->targetPosition.y = remainingH * 0.5f;

  // Draw the texture (note negative height to flip vertically like in Go code)
  Rectangle source = {0.0f, 0.0f, (float)s->renderTexture.texture.width,
                      -(float)s->renderTexture.texture.height};
  Rectangle dest = {s->targetPosition.x, s->targetPosition.y,
                    s->targetResolution.x, s->targetResolution.y};
  Vector2 origin = {0.0f, 0.0f};

  DrawTexturePro(s->renderTexture.texture, source, dest, origin, 0.0f, WHITE);
}

// If you want to manually render the screen (same logic as EndDrawing's render
// portion)
void Screen_Render(Screen *s) {
  if (!s)
    return;
  Vector2 RS = V2((float)GetRenderWidth(), (float)GetRenderHeight());
  // set temporarily for calculating scale
  s->targetResolution = RS;
  float scale = minf(s->targetResolution.x / s->internalResolution.x,
                     s->targetResolution.y / s->internalResolution.y);
  s->targetResolution = Vector2Scale(s->internalResolution, scale);

  float remainingW = RS.x - s->targetResolution.x;
  float remainingH = RS.y - s->targetResolution.y;

  s->targetPosition.x = remainingW * 0.5f;
  s->targetPosition.y = remainingH * 0.5f;

  Rectangle source = {0.0f, 0.0f, (float)s->renderTexture.texture.width,
                      -(float)s->renderTexture.texture.height};
  Rectangle dest = {s->targetPosition.x, s->targetPosition.y,
                    s->targetResolution.x, s->targetResolution.y};
  Vector2 origin = {0.0f, 0.0f};

  DrawTexturePro(s->renderTexture.texture, source, dest, origin, 0.0f, WHITE);
}

// Render the render texture into an arbitrary rectangle (used when drawing this
// screen into a parent or UI)
void Screen_RenderEx(Screen *s, float x, float y, float width, float height,
                     Screen *parent) {
  if (!s)
    return;
  s->parent = parent;
  s->targetPosition = V2(x, y);
  s->targetResolution = V2(width, height);

  Rectangle source = {0.0f, 0.0f, (float)s->renderTexture.texture.width,
                      -(float)s->renderTexture.texture.height};
  Rectangle dest = {s->targetPosition.x, s->targetPosition.y,
                    s->targetResolution.x, s->targetResolution.y};
  Vector2 origin = {0.0f, 0.0f};

  DrawTexturePro(s->renderTexture.texture, source, dest, origin, 0.0f, WHITE);
}

// Returns the scale factor used to fit internalResolution into current
// targetResolution
float Screen_Scale(Screen *s) {
  if (!s)
    return 1.0f;
  // Avoid division by zero
  if (s->internalResolution.x == 0 || s->internalResolution.y == 0)
    return 1.0f;
  return minf(s->targetResolution.x / s->internalResolution.x,
              s->targetResolution.y / s->internalResolution.y);
}

// Virtual mouse in screen-space (scaled to internal resolution).
Vector2 Screen_VirtualMouse(Screen *s) {
  if (!s)
    return V2(0, 0);

  Vector2 mouse;
  if (s->parent != NULL) {
    // If this screen is drawn inside another screen, get parent's virtual mouse
    // first
    mouse = Screen_VirtualMouse(s->parent);
  } else {
    mouse = V2((float)GetMouseX(), (float)GetMouseY());
  }

  float scale = Screen_Scale(s);
  // Subtract targetPosition (letterbox offset) and scale back to internal
  // resolution
  Vector2 vMouse = Vector2Subtract(mouse, s->targetPosition);
  if (scale != 0.0f)
    vMouse = Vector2Scale(vMouse, 1.0f / scale);
  return vMouse;
}
