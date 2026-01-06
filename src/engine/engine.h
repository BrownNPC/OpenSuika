#pragma once

#include <stc/cstr.h>

typedef struct {
  int VirtualWidth, VirtualHeight;
  cstr WindowTitle;
} Config;

void static inline engineRun(Config cfg) {}
