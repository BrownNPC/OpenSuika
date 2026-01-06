#include <engine/engine.h>

static struct { //
} self;

static void Load(Context ctx) { //
}
static bool Update(Context ctx) { //
  return false;
}
static SceneID Unload(Context ctx) { //
  return SceneID_Start;
}

Scene InitBlankScene() {
  Scene s;
  s.Load = Load;
  s.Update = Update;
  s.Unload = Unload;
  return s;
}
