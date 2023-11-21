#pragma once

#include "selfdrive/ui/qt/network/wifi_manager.h"
#include "selfdrive/ui/qt/offroad/settings.h"

class FrogPilotNavigationPanel : public ListWidget {
  Q_OBJECT

public:
  explicit FrogPilotNavigationPanel(SettingsWindow *parent);

private:
  void createMapboxKeyControl(ButtonControl *&control, const QString &label, const std::string &paramKey, const QString &prefix);
  void displaySetup();
  void manageOfflineMaps(QWidget *parent);
  void selectMaps();
  void updateState();

  ButtonControl *publicMapboxKeyControl;
  ButtonControl *secretMapboxKeyControl;
  ButtonControl *manageOfflineMapsButton;
  ButtonControl *selectMapsButton;
  ButtonControl *setupButton;

  LabelControl *offlineMapsSize;
  LabelControl *offlineMapsStatus;

  Params params;
  Params paramsMemory{"/dev/shm/params"};

  QLabel *imageLabel = new QLabel(this);
  QLabel *setupStep = new QLabel(this);
  QLabel *mapboxSettingsLabel = new QLabel("Device Offline. Connect to the internet to use Navigation.", this);

  WifiManager *wifi = new WifiManager(this);

  static constexpr const char *imagePath = "../assets/images/";
  static constexpr const char *ipFormat = "Manage your mapbox settings at %1:8082";

  bool hasPrime = false;
  bool mapboxPublicKeySet = false;
  bool mapboxSecretKeySet = false;
  bool setupCompleted = false;

  QString currentStep = "no_keys_set.png";
};
