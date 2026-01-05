#pragma once

typedef struct Scene {
  void (*Init)(struct Scene *self);   // called once when scene is loaded
  void (*Update)(struct Scene *self); // called every frame void (*draw)(struct Scene *self);   // called every frame
  void (*Unload)(struct Scene *self); // called once when scene is unloaded
} Scene;

// Scene manager
void changeScene(Scene *newScene);
