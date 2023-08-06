// run floating cube animation
void runFloatingCube() {
  t_travCube travCube = {
      {3.5, (int8_t)random(TRAV_FRAMES_MIN, TRAV_FRAMES_MAX + 1)},
      {0.8, (int8_t)random(TRAV_FRAMES_MIN, TRAV_FRAMES_MAX + 1)},
      {6.5, (int8_t)random(TRAV_FRAMES_MIN, TRAV_FRAMES_MAX + 1)}};

  while (true) {
    renderFloatingFrame(travCube);
    moveFloatingCube(travCube);
  }
}

// render cube with grey level
void renderFloatingFrame(t_travCube travCube) {
  for (uint8_t grey = 0; grey < GREY_LEVEL; grey++) {
    
    for (uint8_t layer = 0; layer < 8; layer++) {
      for (uint8_t row = 0; row < 8; row++) {
        cube[layer][row] = 0x00;
      }
    }
    
    renderFloatingCube(travCube, grey);
  }
}

bool calcBrightness(float br, uint8_t grey) {
  if (br < 0.05) return false;
  else if (br < 0.5) return 2 * br * GREY_LEVEL > grey;
  else return true;
}

void renderFloatingCube(t_travCube travCube, uint8_t grey) {
  uint8_t xfloor = (uint8_t)travCube.axisx.pos;
  uint8_t yfloor = (uint8_t)travCube.axisy.pos;
  uint8_t zfloor = (uint8_t)travCube.axisz.pos;

  float xright = travCube.axisx.pos - (uint8_t)travCube.axisx.pos;
  float yright = travCube.axisy.pos - (uint8_t)travCube.axisy.pos;
  float zright = travCube.axisz.pos - (uint8_t)travCube.axisz.pos;

  uint8_t line00 = 0x00;
  uint8_t line01 = 0x00;
  uint8_t line10 = 0x00;
  uint8_t line11 = 0x00;
  
  if (xfloor < 7) {
    if (calcBrightness((1 - xright) * (1 - yright) * (1 - zright), grey)) line00 = 0x02;
    if (calcBrightness((1 - xright) * (yright) * (1 - zright), grey)) line01 = 0x02;
    if (calcBrightness((1 - xright) * (1 - yright) * (zright), grey)) line10 = 0x02;
    if (calcBrightness((1 - xright) * (yright) * (zright), grey)) line11 = 0x02;
  }
  
  if (calcBrightness((xright) * (1 - yright) * (1 - zright), grey)) line00 |= 0x01;
  if (calcBrightness((xright) * (yright) * (1 - zright), grey)) line01 |= 0x01;
  if (calcBrightness((xright) * (1 - yright) * (zright), grey)) line10 |= 0x01;
  if (calcBrightness((xright) * (yright) * (zright), grey)) line11 |= 0x01;
  line00 <<= (6 - xfloor);
  line01 <<= (6 - xfloor);
  line10 <<= (6 - xfloor);
  line11 <<= (6 - xfloor);

  cube[zfloor][yfloor] = line00;
  if (yfloor < 7) cube[zfloor][yfloor + 1] = line01;
  if (zfloor < 7) cube[zfloor + 1][yfloor] = line10;
  if (yfloor < 7 && zfloor < 7) cube[zfloor + 1][yfloor + 1] = line11;

  if (zfloor == 7) zfloor = 6;
  renderFloatingPoint(zfloor);
}

void renderFloatingPoint(uint8_t dataLayer) {
  for (uint8_t layer = dataLayer; layer < dataLayer + 2; layer++) {
    // set layer
    setPin(SS, LOW);
    SPI.transfer(0x01 << layer);
    for (uint8_t row = 0; row < 8; row++) {
      SPI.transfer(cube[layer][row]);
    }
    setPin(SS, HIGH);
    // lights layer
    delayMicroseconds(RENDER_DELAY);
  }
  // reset lights
  setPin(SS, LOW);
  for (uint8_t i = 0; i < 9; i++) {
    SPI.transfer(0x00);
  }
  setPin(SS, HIGH);
}

void moveFloatingCube(t_travCube& travCube) {
  changeFloatingCubeParam(travCube.axisx);
  changeFloatingCubeParam(travCube.axisy);
  changeFloatingCubeParam(travCube.axisz);
}

void changeFloatingCubeParam(t_travAxis& axis) {
  if (axis.vel != 0) axis.pos += 1. / axis.vel;
  
  if (axis.pos <= 0) {
    axis.pos = 0;
    axis.vel = -axis.vel + (int8_t)random(-TRAV_FRAMES_DELTA, TRAV_FRAMES_DELTA + 1);
    if (axis.vel > TRAV_FRAMES_MAX) axis.vel = TRAV_FRAMES_MAX;
    else if (axis.vel < 0 || axis.vel < TRAV_FRAMES_MIN) axis.vel = TRAV_FRAMES_MIN;
  } else if (axis.pos >= 7) {
    axis.pos = 7;
    axis.vel = -axis.vel + (int8_t)random(-TRAV_FRAMES_DELTA, TRAV_FRAMES_DELTA + 1);
    if (axis.vel < -TRAV_FRAMES_MAX) axis.vel = -TRAV_FRAMES_MAX;
    else if (axis.vel > 0 || axis.vel > -TRAV_FRAMES_MIN) axis.vel = -TRAV_FRAMES_MIN;
  }
}
