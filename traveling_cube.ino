void runFloatingCube() {
  t_travCube travCube = {
    {3, random(TRAV_FRAMES_MIN, TRAV_FRAMES_MAX + 1), 0},
    {3, random(TRAV_FRAMES_MIN, TRAV_FRAMES_MAX + 1), 0},
    {3, random(TRAV_FRAMES_MIN, TRAV_FRAMES_MAX + 1), 0}
  };

  while (true) {
    renderFloatingCube(travCube);
    moveFloatingCube(&travCube);
  }
}

void renderFloatingCube(t_travCube travCube) {
  for (uint8_t layer = 0; layer < 8; layer++) {
    for (uint8_t row = 0; row < 8; row++) {
      if (layer < travCube.axisz.pos || layer > travCube.axisz.pos + 1) cube[layer][row] = 0x00;
      else if (row < travCube.axisy.pos || row > travCube.axisy.pos + 1) cube[layer][row] = 0x00;
      else cube[layer][row] = 0x03 << travCube.axisx.pos;
    }
  }
  renderCube();
}

void moveFloatingCube(t_travCube* travCube) {
  changeFloatingCubeParam(&travCube->axisx);
  changeFloatingCubeParam(&travCube->axisy);
  changeFloatingCubeParam(&travCube->axisz);
}

void changeFloatingCubeParam(t_travAxis* axis) {
  if ((axis->vel > 0 && axis->frame >= axis->vel) || (axis->vel < 0 && axis->frame >= -axis->vel)) {
    axis->frame = 0;
    if (axis->vel > 0) axis->pos++;
    else axis->pos--;
    changeFloatingCubeVelosity(axis);
  } else axis->frame++;
}

void changeFloatingCubeVelosity(t_travAxis* axis) {
  uint8_t delta;
  if (axis->pos >= 6) {
    delta = random(-10, 11);
    axis->vel += delta;
    if (axis->vel > 0) axis->vel = -axis->vel;
    if (axis->vel < -TRAV_FRAMES_MAX) axis->vel = -TRAV_FRAMES_MAX;
    if (axis->vel > -TRAV_FRAMES_MIN) axis->vel = -TRAV_FRAMES_MIN;
  } else if (axis->pos <= 0) {
    delta = random(-10, 11);
    axis->vel += delta;
    if (axis->vel < 0) axis->vel = -axis->vel;
    if (axis->vel < TRAV_FRAMES_MIN) axis->vel = TRAV_FRAMES_MIN;
    if (axis->vel > TRAV_FRAMES_MAX) axis->vel = TRAV_FRAMES_MAX;
  }
}
