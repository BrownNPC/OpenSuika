// ADD A NEW SCENE:
// 1. add extern Scene Init<SceneName>Scene();
// 2. map SceneID to Initializer
#pragma once

#include "types.h"
enum SceneID {
  SceneID_Start,
  TotalScenes,
};

static Scene Scenes[TotalScenes];

// Initializers are in their respective C files
extern Scene InitStartScene();

static void SceneInitAll() {
  Scenes[SceneID_Start] = InitStartScene();
  //
}
