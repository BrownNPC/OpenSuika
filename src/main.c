// Program main entry point
//------------------------------------------------------------------------------------
#include "engine/engine.h"
int main(void) {

  Config cfg = {
      .VirtualWidth = 480,
      .VirtualHeight = 270,
      .WindowTitle = "OpenSuika",
  };
  engineRun(cfg);
  return 0;
}
