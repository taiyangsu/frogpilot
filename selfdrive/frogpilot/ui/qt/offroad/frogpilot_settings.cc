#include "selfdrive/frogpilot/navigation/ui/navigation_settings.h"
#include "selfdrive/frogpilot/ui/qt/offroad/driving_settings.h"
#include "selfdrive/frogpilot/ui/qt/offroad/frogpilot_settings.h"
#include "selfdrive/frogpilot/ui/qt/offroad/utilities.h"
#include "selfdrive/frogpilot/ui/qt/offroad/vehicle_settings.h"
#include "selfdrive/frogpilot/ui/qt/offroad/visual_settings.h"

FrogPilotSettingsWindow::FrogPilotSettingsWindow(SettingsWindow *parent) : ListWidget(parent) {
  FrogPilotDrivingPanel *frogpilotDriving = new FrogPilotDrivingPanel(this);
  QObject::connect(frogpilotDriving, &FrogPilotDrivingPanel::openParentToggle, this, [this]() { emit openParentToggle(); });
  QObject::connect(frogpilotDriving, &FrogPilotDrivingPanel::openSubParentToggle, this, [this]() { emit openSubParentToggle(); });
  QObject::connect(frogpilotDriving, &FrogPilotDrivingPanel::openSubSubParentToggle, this, [this]() { emit openSubSubParentToggle(); });

  FrogPilotVisualsPanel *frogpilotVisuals = new FrogPilotVisualsPanel(this);
  QObject::connect(frogpilotVisuals, &FrogPilotVisualsPanel::openParentToggle, this, [this]() { emit openParentToggle(); });
  QObject::connect(frogpilotVisuals, &FrogPilotVisualsPanel::openSubParentToggle, this, [this]() { emit openSubParentToggle(); });

  setSpacing(50);

  ButtonControl *manageDeviceControls = new ButtonControl(tr("Manage Device Controls"), tr("MANAGE"));
  connect(manageDeviceControls, &ButtonControl::clicked, [=]() {});
  addItem(manageDeviceControls);

  ButtonControl *manageNavigationSettings = new ButtonControl(tr("Manage Navigation Settings"), tr("MANAGE"));
  connect(manageNavigationSettings, &ButtonControl::clicked, [=]() {});
  addItem(manageNavigationSettings);

  ButtonControl *manageDrivingControls = new ButtonControl(tr("Manage openpilot Driving Controls"), tr("MANAGE"));
  connect(manageDrivingControls, &ButtonControl::clicked, [=]() {});
  addItem(manageDrivingControls);

  ButtonControl *manageSoundControls = new ButtonControl(tr("Manage openpilot Sounds"), tr("MANAGE"));
  connect(manageSoundControls, &ButtonControl::clicked, [=]() {});
  addItem(manageSoundControls);

  ButtonControl *manageVisualControls = new ButtonControl(tr("Manage openpilot Visuals"), tr("MANAGE"));
  connect(manageVisualControls, &ButtonControl::clicked, [=]() {});
  addItem(manageVisualControls);

  ButtonControl *manageQOL = new ButtonControl(tr("Manage Quality of Life Settings"), tr("MANAGE"));
  connect(manageQOL, &ButtonControl::clicked, [=]() {});
  addItem(manageQOL);
}
