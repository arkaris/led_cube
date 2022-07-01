#include <SPI.h>
#include "traveling_cube.h"

uint8_t cube[8][8];

void setup() {
  randomSeed(analogRead(0));
  SPI.begin();
  SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));
}

void loop() {
  runFloatingCube();
}
