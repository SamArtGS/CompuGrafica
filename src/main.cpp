#pragma once

#include "MarioCraft.h"

int main() {
  MarioCraft marioCraft("Mario Craft", 0, 0, true);

  while (!marioCraft.getWindowShouldClose()) {
    marioCraft.update();

    marioCraft.render();
  };

  return 0;
}