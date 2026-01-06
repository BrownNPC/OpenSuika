#pragma once

#include "raylib.h"
#include "scene.h"
#include "types.h"

void static inline engineRun(Config cfg) {
  auto ActiveSceneId = SceneID_Start;
  auto ActiveScene = Scenes[ActiveSceneId];

  // --------------BEGIN--------------
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(0, 0, cfg.WindowTitle);
}
