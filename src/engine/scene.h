// ADD A NEW SCENE:
// 1. add extern Scene Init<SceneName>Scene();
// 2. map SceneID to Initializer
#pragma once

#include "types.h"
enum SceneID {
  SceneID_Start,
  SceneID_Game,
  SceneID_Blank,
  TotalScenes,
};

static Scene Scenes[TotalScenes];

// Initializers are in their respective C files
extern Scene InitStartScene();
extern Scene InitGameScene();
extern Scene InitBlankScene();
  //Initialize Scenes map
static void SceneInitAll() {
  Scenes[SceneID_Start] = InitStartScene();
  Scenes[SceneID_Game] = InitGameScene();
  Scenes[SceneID_Blank] = InitBlankScene();
  //
}
