void setPin(uint8_t pin, uint8_t x) {
  if (pin < 8) bitWrite(PORTD, pin, x);
  else if (pin < 14) bitWrite(PORTB, (pin - 8), x);
  else if (pin < 20) bitWrite(PORTC, (pin - 14), x);
  else return;
}

void renderCube() {
  for (uint8_t layer = 0; layer < 8; layer++) {
    setPin(SS, LOW);
    SPI.transfer(0x01 << layer);
    for (uint8_t row = 0; row < 8; row++) {
      SPI.transfer(cube[layer][row]);
    }
    setPin(SS, HIGH);
    delayMicroseconds(RENDER_DELAY);
  }
  setPin(SS, LOW);
  for (uint8_t i = 0; i < 9; i++) {
    SPI.transfer(0x00);
  }
  setPin(SS, HIGH);
}
