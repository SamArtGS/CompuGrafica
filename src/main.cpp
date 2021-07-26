#pragma once

#include "MarioCraft.h"
#include "sound.h"

int main() {
  MarioCraft marioCraft("Mario Craft", "resources/icono.png", 0, 0, true);
  sound* ambiental = new sound();
  ambiental->musica("./resources/sounds/ySeMarcho.ogg");
  ambiental->playMusic(100);
  while (!marioCraft.getWindowShouldClose()) {
    marioCraft.update();

    marioCraft.render();
  };

  return 0;
}