// Program main entry point
//------------------------------------------------------------------------------------
#include "engine/engine.h"
#include "engine/scene.h"

int main(void) {
  //Initialize Scenes map
  SceneInitAll();
  Config cfg = {
      .VirtualWidth = 480,
      .VirtualHeight = 270,
      .WindowTitle = "OpenSuika",
  };
  engineRun(cfg);
  return 0;
}
