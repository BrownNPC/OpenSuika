#include "raylib.h"
#include <engine/scene.h>

static struct { //
} self;

static void Load(Context ctx) { //
}
static bool Update(Context ctx) {
  ClearBackground(RED);
  return false; //
}
static SceneID Unload(Context ctx) {
  return SceneID_Start; //
}

Scene InitGameScene() {
  Scene s;
  s.Load = Load;
  s.Update = Update;
  s.Unload = Unload;
  return s;
}
