#pragma once

#include "selfdrive/ui/qt/offroad/settings.h"

class UtilitiesPanel : public ListWidget {
  Q_OBJECT
public:
  explicit UtilitiesPanel(SettingsWindow *parent);

private:
  Params params;
  Params paramsMemory{"/dev/shm/params"};

  FrogPilotButtonsControl *forceStartedBtn;
};
