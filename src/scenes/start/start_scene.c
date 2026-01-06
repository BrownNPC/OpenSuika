#include "raylib.h"
#include <components/memory/arena.h>
#include <components/render/screen.h>
#include <engine/scene.h>

static struct {
  Screen *screen;
} self;

static void Load(Context ctx) {
  self.screen = Screen_New(ctx.arena, ctx.cfg.VirtualResolution);
}
static bool Update(Context ctx) {
  Screen_BeginDrawing(self.screen);
  ClearBackground(GREEN);

  Screen_EndDrawing(self.screen);

  if (IsKeyPressed(KEY_A)) {
    return true;
  }

  return false;
}
static SceneID Unload(Context ctx) {
  Screen_Unload(self.screen);
  Arena_Reset(ctx.arena);
  return SceneID_Game;
}

Scene InitStartScene() {
  Scene s;
  s.Load = Load;
  s.Update = Update;
  s.Unload = Unload;
  return s;
}
