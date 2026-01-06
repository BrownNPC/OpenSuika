#include "imports.h"
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {

  Config cfg = {
      .VirtualWidth = 480,
      .VirtualHeight = 270,
      .WindowTitle = "OpenSuika",
  };
  engineRun(cfg);
  return 0;
}
