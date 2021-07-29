#pragma once

#include "MarioCraft.h"
#include "sound.h"

int main() {
  MarioCraft marioCraft("Mario Craft", "resources/icono.png", 0, 0, true);
  sound* ambiental = new sound();
  ambiental->musica("./resources/sounds/Halland.ogg");
  ambiental->playMusic(50);
  while (!marioCraft.getWindowShouldClose()) {
    marioCraft.update();

    marioCraft.render();
  };

  return 0;
}