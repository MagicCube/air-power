#pragma once

#include <Arduino.h>

#include <TFT_eSPI.h>

#ifndef NSTARS
#define NSTARS 40
#endif

#define MAX_STAR_SIZE 5

class StarfieldAnimation {
public:
  StarfieldAnimation(TFT_eSPI *tft);
  void begin();
  void redraw();

private:
  TFT_eSPI *_canvas;
  uint8_t _za, _zb, _zc, _zx;
  uint8_t sx[NSTARS] = {};
  uint8_t sy[NSTARS] = {};
  uint8_t sz[NSTARS] = {};
  unsigned long _lastUpdate = 0;

  bool _isInCanvas(int x, int y);
  void _drawStar(uint8_t x, uint8_t y, uint8_t size, uint32_t color);
  uint8_t _rng();
  int _xScale(uint8_t x, uint8_t z);
  int _yScale(uint8_t y, uint8_t z);
  int _zScale(uint8_t z);
  int _colorScale(uint8_t z);
};