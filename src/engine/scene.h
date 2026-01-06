#pragma once
#include "engine.h"



typedef enum {
  SceneId_Start,
} SceneID;

typedef struct Scene Scene;
struct Scene {
  // called once when scene is loaded
  void (*Load)(Config cfg);
  // called every frame (unloads if return true)
  bool (*Update)(Config cfg);
  // called once when scene is unloaded
  SceneID (*Unload)(Config cfg);
};

Scene InitStartScene();
