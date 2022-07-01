void setPin(uint8_t pin, uint8_t x) {
  if (pin < 8) bitWrite(PORTD, pin, x);
  else if (pin < 14) bitWrite(PORTB, (pin - 8), x);
  else if (pin < 20) bitWrite(PORTC, (pin - 14), x);
  else return;
}

void renderCube() {
  for (uint8_t i = 0; i < 8; i++) {
    setPin(SS, LOW);
    SPI.transfer(0x01 << i);
    for (uint8_t j = 0; j < 8; j++) {
      SPI.transfer(cube[i][j]);
    }
    setPin(SS, HIGH);
    delayMicroseconds(1000);
  }
  setPin(SS, LOW);
  for (uint8_t i = 0; i < 9; i++) {
    SPI.transfer(0x00);
  }
  setPin(SS, HIGH);
}
