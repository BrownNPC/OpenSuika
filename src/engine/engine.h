#pragma once

#include "raylib.h"
#include "scene.h"
#include "types.h"

// Run the engine
void static inline engineRun(Config cfg) {
  // Entry point scene is Start
  static auto ActiveSceneId = SceneID_Start;
  auto ActiveScene = Scenes[ActiveSceneId];

  // Context is passed to Scenes
  auto ctx = (Context){
      .cfg = cfg,
  };

  // --------------BEGIN--------------
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(0, 0, cfg.WindowTitle);
  InitAudioDevice();

  ActiveScene.Load(ctx);

  while (!WindowShouldClose()) {
    if (IsKeyPressed(KEY_F11)) {
      ToggleBorderlessWindowed();
    }

    BeginDrawing();
    ClearBackground(BLACK);
    // -------UPDATE SCENE---------
    bool unloadActiveScene = ActiveScene.Update(ctx);
    EndDrawing();
    if (unloadActiveScene) {
      // -------UNLOAD SCENE-------
      ActiveSceneId = ActiveScene.Unload(ctx);
      ActiveScene = Scenes[ActiveSceneId];
      // Load next scene
      ActiveScene.Load(ctx);
    }
  };
}
