
#include "../engine/scene.h"

static void Load(Config cfg) {}
static bool Update(Config cfg) { return false; }
static SceneID Unload(Config cfg) { return SceneId_Start; }

Scene InitStartScene() {
  Scene s;
  s.Load = Load;
  s.Update = Update;
  s.Unload = Unload;
  return s;
}
