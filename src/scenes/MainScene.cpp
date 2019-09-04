#include "MainScene.h"

#include "log.h"

#include "../ble/BLEPeripheral.h"
#include "../charging/Charger.h"
#include "../drawing/tft/TFTDrawingContext.h"
#include "../utils/format.h"

#include "../resources/charging_indicator.h"

MainScene::MainScene() {
  _animation.setBlackHoles(_clockView.frame(), _batteryView.frame());
  _chargingIndicatorFrame =
      Rect(_batteryView.frame().left() - charging_indicator_width - 8,
           _batteryView.frame().top() + 8, charging_indicator_width, charging_indicator_height);
}

bool MainScene::update(bool forceRedraw) {
  auto now = DateTime::now();
  DateTime time(now);
  if (now > 1000 * 60 * 60) {
    _clockView.timeString(formatTime(time, false));
  }
  _batteryView.batteryLevel(BLEPeripheral.remoteDevice()->batteryLevel());
  _batteryView.isCharging(Charger.isCharging());
  return true;
}

void MainScene::redraw() {
  _animation.redraw();
  _clockView.redraw(true);   // Always force to redraw
  _batteryView.redraw(true); // Always force redraw
  _drawChargingIndicator();

  #ifdef DRAW_CONSTRUCTION_LINE
  auto context = TFTDrawingContext::getScreenDrawingContext();
  context->drawCircle(context->bounds().middlePoint(), context->size().width / 2 - 1, DRAW_CONSTRUCTION_LINE);
  #endif
}

void MainScene::_drawChargingIndicator() {
  auto context = TFTDrawingContext::getScreenDrawingContext();
  if (Charger.isCharging()) {
    context->drawXBitmap(charging_indicator_bits,
                         Rect(_chargingIndicatorFrame.left(), _chargingIndicatorFrame.top(),
                              _chargingIndicatorFrame.width(), _chargingIndicatorFrame.height()),
                         TFT_WHITE);
  } else {
    context->fillRect(Rect(_chargingIndicatorFrame.left(), _chargingIndicatorFrame.top(),
                           _chargingIndicatorFrame.width(), _chargingIndicatorFrame.height()),
                      TFT_BLACK);
  }
}