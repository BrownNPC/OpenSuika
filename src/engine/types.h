#pragma once

// Passed to engineRun
#include "raylib.h"
#include <components/memory/arena.h>
typedef struct {
  Vector2 VirtualResolution;
  char *WindowTitle;
} Config;

// Passed to every function
typedef struct {
  Config cfg;
  Arena *arena;
} Context;

typedef enum SceneID SceneID;

typedef struct Scene Scene;
struct Scene {
  // called once when scene is loaded
  void (*Load)(Context ctx);
  // called every frame (unloads if return true)
  bool (*Update)(Context ctx);
  // called once when scene is unloaded
  SceneID (*Unload)(Context ctx);
};
