#include <engine.h>

static struct {
  int Dih;
} self;

static void Load(Context cfg) { self.Dih = 67; }
static bool Update(Context cfg) {
  return false; //
}
static SceneID Unload(Context cfg) {
  return SceneID_Start; //
}

Scene InitBlankScene() {
  Scene s;
  s.Load = Load;
  s.Update = Update;
  s.Unload = Unload;
  return s;
}
