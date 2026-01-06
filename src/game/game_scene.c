#include "../engine/scene.h"
#include "raylib.h"

static struct {
  int Dih;
} self;

static void Load(Context cfg) { self.Dih = 67; }
static bool Update(Context cfg) {
  ClearBackground(RED);
  return false; //
}
static SceneID Unload(Context cfg) {
  return SceneID_Start; //
}

Scene InitGameScene() {
  Scene s;
  s.Load = Load;
  s.Update = Update;
  s.Unload = Unload;
  return s;
}
