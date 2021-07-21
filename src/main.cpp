#pragma once

#include "MarioCraft.h"

int main() {
  MarioCraft marioCraft("Mario Craft", "resources/icono.png", 0, 0, true);

  while (!marioCraft.getWindowShouldClose()) {
    marioCraft.update();

    marioCraft.render();
  };

  return 0;
}