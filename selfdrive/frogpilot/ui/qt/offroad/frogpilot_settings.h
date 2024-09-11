#pragma once

#include "selfdrive/ui/qt/offroad/settings.h"

class FrogPilotSettingsWindow : public ListWidget {
  Q_OBJECT
public:
  explicit FrogPilotSettingsWindow(SettingsWindow *parent);

signals:
  void closeParentToggle();
  void closeSubParentToggle();
  void closeSubSubParentToggle();
  void openParentToggle();
  void openSubParentToggle();
  void openSubSubParentToggle();
  void updateMetric();

private:
  Params params;
  Params paramsMemory{"/dev/shm/params"};

  FrogPilotButtonsControl *forceStartedBtn;
};
