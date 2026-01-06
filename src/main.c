// Program main entry point
//------------------------------------------------------------------------------------
#include <engine/engine.h>
#include <engine/scene.h>

int main(void) {
  // Initialize Scenes map
  SceneInitAll();
  Config cfg = {
      .VirtualResolution = (Vector2){480, 270},
      .WindowTitle = "OpenSuika",
  };
  engineRun(cfg);
  return 0;
}
