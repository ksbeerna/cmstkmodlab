#include <iostream>

#include <QMutexLocker>

#include "DefoScriptableConrad.h"

DefoScriptableConrad::DefoScriptableConrad(
    DefoConradModel* conradModel
  , QObject *parent
) :
    QObject(parent)
  , conradModel_(conradModel)
{
  connect(this, SIGNAL(enableSwitch(DefoConradModel::DeviceSwitch)),
          conradModel_,SLOT(enableSwitch(DefoConradModel::DeviceSwitch)));
}

void DefoScriptableConrad::enablePanel(int panel) {
  
  QMutexLocker locker(&mutex_);

  if (panel<1 || panel>5) return;

  emit enableSwitch(static_cast<DefoConradModel::DeviceSwitch>(panel-1));
}

void DefoScriptableConrad::disablePanel(int panel) {
  
  QMutexLocker locker(&mutex_);

  if (panel<1 || panel>5) return;

  emit disableSwitch(static_cast<DefoConradModel::DeviceSwitch>(panel-1));
}

QScriptValue DefoScriptableConrad::panel(int panel) {

  QMutexLocker locker(&mutex_);

  if (panel<1 || panel>5) return QScriptValue(0);

  int state = static_cast<int>(conradModel_->getSwitchState(static_cast<DefoConradModel::DeviceSwitch>(panel-1)));
  return QScriptValue(state);
}

void DefoScriptableConrad::enableCalibrationLEDs() {

  QMutexLocker locker(&mutex_);

  emit enableSwitch(DefoConradModel::CALIBRATION_LEDS);
}

void DefoScriptableConrad::disableCalibrationLEDs() {

  QMutexLocker locker(&mutex_);

  emit disableSwitch(DefoConradModel::CALIBRATION_LEDS);
}

QScriptValue DefoScriptableConrad::calibrationLEDs() {

  QMutexLocker locker(&mutex_);

  int state = static_cast<int>(conradModel_->getSwitchState(DefoConradModel::CALIBRATION_LEDS));
  return QScriptValue(state);
}