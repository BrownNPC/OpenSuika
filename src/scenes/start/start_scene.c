#include <scene.h>
#include "raylib.h"

static struct {
  int Dih;
} self;

static void Load(Context cfg) { self.Dih = 67; }
static bool Update(Context cfg) {
  ClearBackground(GREEN);
  DrawText(TextFormat("%d", self.Dih), 0, 0, 21, GREEN);
  if (IsKeyPressed(KEY_A)){
    return true;
  }
  
  return false; //
}
static SceneID Unload(Context cfg) {
  return SceneID_Game; //
}

Scene InitStartScene() {
  Scene s;
  s.Load = Load;
  s.Update = Update;
  s.Unload = Unload;
  return s;
}
