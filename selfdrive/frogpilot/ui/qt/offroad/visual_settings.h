#pragma once

#include <set>

#include "selfdrive/ui/qt/offroad/settings.h"
#include "selfdrive/ui/ui.h"

class FrogPilotVisualsPanel : public FrogPilotListWidget {
  Q_OBJECT

public:
  explicit FrogPilotVisualsPanel(SettingsWindow *parent);

signals:
  void openParentToggle();

private:
  void hideToggles();
  void updateCarToggles();
  void updateMetric();
  void updateState(const UIState &s);

  std::set<QString> alertVolumeControlKeys = {};
  std::set<QString> customAlertsKeys = {};
  std::set<QString> customOnroadUIKeys = {"CustomPaths"};
  std::set<QString> customThemeKeys = {};
  std::set<QString> modelUIKeys = {};
  std::set<QString> qolKeys = {};
  std::set<QString> screenKeys = {};

  std::map<std::string, ParamControl*> toggles;

  Params params;

  bool hasBSM;
  bool hasOpenpilotLongitudinal;
  bool isMetric = params.getBool("IsMetric");
  bool started;
};
