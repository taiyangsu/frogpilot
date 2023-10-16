#include <filesystem>

#include "selfdrive/ui/qt/offroad/frogpilot_settings.h"

FrogPilotControlsPanel::FrogPilotControlsPanel(QWidget *parent) : FrogPilotPanel(parent) {
  setDefaultParams();

  mainLayout = new QVBoxLayout(this);

  QLabel *const descriptionLabel = new QLabel("Click on the toggle names to see a detailed toggle description", this);
  mainLayout->addWidget(descriptionLabel);
  mainLayout->addSpacing(25);
  mainLayout->addWidget(whiteHorizontalLine());

  static const std::vector<std::tuple<QString, QString, QString, QString>> toggles = {
    {"AlwaysOnLateral", "Always on Lateral / No disengage on Brake Pedal", "Keep openpilot lateral control when using either the brake or gas pedals. openpilot is only disengaged by deactivating the 'Cruise Control' button.", "../assets/offroad/icon_always_on_lateral.png"},
    {"ConditionalExperimental", "Conditional Experimental Mode", "Automatically activate 'Experimental Mode' based on specified conditions.", "../assets/offroad/icon_conditional.png"},
    {"CustomPersonalities", "Custom Driving Personalities", "Customize the driving personality profiles to your liking.", "../assets/offroad/icon_custom.png"},
    {"DeviceShutdownTimer", "Device Shutdown Timer", "Set the timer for when the device turns off after being offroad to reduce energy waste and prevent battery drain.", "../assets/offroad/icon_time.png"},
    {"ExperimentalModeViaWheel", "Experimental Mode Via Steering Wheel / Screen", "Enable or disable Experimental Mode by double-clicking the 'Lane Departure'/LKAS button on the steering wheel (Toyota/Lexus Only) or double tapping the screen for other makes.\n\nOverrides 'Conditional Experimental Mode'. ", "../assets/img_experimental_white.svg"},
    {"LateralTuning", "Lateral Tuning", "Change the way openpilot steers.", "../assets/offroad/icon_lateral_tune.png"},
    {"LongitudinalTuning", "Longitudinal Tuning", "Change the way openpilot accelerates and brakes.", "../assets/offroad/icon_longitudinal_tune.png"},
  };

  for (const auto &[key, label, desc, icon] : toggles) {
    ParamControl *control = createParamControl(key, label, desc, icon, this);
    if (key == "AlwaysOnLateral") {
      createSubControl(key, label, desc, icon, {}, {
        {"AlwaysOnLateralMain", "Enable AOL On Cruise Main", "Enables Always On Lateral by simply turning on cruise control as opposed to requiring openpilot to be enabled first."}
      });
    } else if (key == "ConditionalExperimental") {
      createSubControl(key, label, desc, icon, {
        createDualParamControl(new ConditionalSpeed(), new ConditionalSpeedLead()),
      });
      createSubButtonControl(key, {
        {"ConditionalCurves", "Curves"},
        {"ConditionalCurvesLead", "Curves W/ Lead"},
        {"ConditionalSlowerLead", "Slower Lead"},
        {"ConditionalStopLights", "Stop Lights"},
        {"ConditionalSignal", "Turn Signal"}
      }, mainLayout);
    } else if (key == "CustomPersonalities") {
      createSubControl(key, label, desc, icon, {
        createDualParamControl(new AggressivePersonality(), new AggressiveJerk()),
        createDualParamControl(new StandardPersonality(), new StandardJerk()),
        createDualParamControl(new RelaxedPersonality(), new RelaxedJerk()),
      });
    } else if (key == "DeviceShutdownTimer") {
      mainLayout->addWidget(new DeviceShutdownTimer());
      mainLayout->addWidget(horizontalLine());
    } else if (key == "LateralTuning") {
      createSubControl(key, label, desc, icon, {}, {
        {"AverageDesiredCurvature", "Average Desired Curvature", "Use Pfeiferj's distance based curvature adjustment for smoother handling of curves."},
      });
    } else if (key == "LongitudinalTuning") {
      createSubControl(key, label, desc, icon, {
        new AccelerationProfile(),
      }, {
        {"AggressiveAcceleration", "Aggressive Acceleration With Lead", "Accelerate more aggressively behind a lead when starting from a stop."},
      });
    } else {
      mainLayout->addWidget(control);
      if (key != std::get<0>(toggles.back())) mainLayout->addWidget(horizontalLine());
    }
  }
  setInitialToggleStates();
}

FrogPilotVehiclesPanel::FrogPilotVehiclesPanel(QWidget *parent) : FrogPilotPanel(parent) {
  mainLayout = new QVBoxLayout(this);

  QHBoxLayout *gmLayout = new QHBoxLayout();
  gmLayout->setSpacing(25);
  gmLayout->setContentsMargins(0, 0, 0, 0);

  QLabel *gmIconLabel = new QLabel(this);
  gmIconLabel->setPixmap(QPixmap("../assets/offroad/icon_gm.png").scaledToWidth(80, Qt::SmoothTransformation));

  QLabel *gmTextLabel = new QLabel("GM", this);

  gmLayout->addWidget(gmIconLabel);
  gmLayout->addWidget(gmTextLabel);
  gmLayout->addStretch(1);
  mainLayout->addLayout(gmLayout);
  mainLayout->addWidget(whiteHorizontalLine());

  static const std::vector<std::tuple<QString, QString, QString, QString>> gmToggles = {
  };

  for (const auto &[key, label, desc, icon] : gmToggles) {
    ParamControl *control = createParamControl(key, label, desc, icon, this);
    mainLayout->addWidget(control);
    if (key != std::get<0>(gmToggles.back())) mainLayout->addWidget(horizontalLine());
  }

  mainLayout->addWidget(whiteHorizontalLine());
  mainLayout->setSpacing(25);
  QHBoxLayout *toyotaLayout = new QHBoxLayout();
  toyotaLayout->addWidget(whiteHorizontalLine());
  toyotaLayout->setSpacing(25);
  toyotaLayout->setContentsMargins(0, 0, 0, 0);

  QLabel *toyotaIconLabel = new QLabel(this);
  toyotaIconLabel->setPixmap(QPixmap("../assets/offroad/icon_toyota.png").scaledToWidth(80, Qt::SmoothTransformation));

  QLabel *toyotaTextLabel = new QLabel("Toyota", this);

  toyotaLayout->addWidget(toyotaIconLabel);
  toyotaLayout->addWidget(toyotaTextLabel);
  toyotaLayout->addStretch(1);
  mainLayout->addLayout(toyotaLayout);
  mainLayout->addWidget(whiteHorizontalLine());

  static const std::vector<std::tuple<QString, QString, QString, QString>> toyotaToggles = {
  };

  for (const auto &[key, label, desc, icon] : toyotaToggles) {
    ParamControl *control = createParamControl(key, label, desc, icon, this);
    mainLayout->addWidget(control);
    if (key != std::get<0>(toyotaToggles.back())) mainLayout->addWidget(horizontalLine());
  }

  setInitialToggleStates();
}

FrogPilotVisualsPanel::FrogPilotVisualsPanel(QWidget *parent) : FrogPilotPanel(parent) {
  mainLayout = new QVBoxLayout(this);

  QLabel *const descriptionLabel = new QLabel("Click on the toggle names to see a detailed toggle description", this);
  mainLayout->addWidget(descriptionLabel);
  mainLayout->addSpacing(25);
  mainLayout->addWidget(whiteHorizontalLine());

  static const std::vector<std::tuple<QString, QString, QString, QString>> toggles = {
    {"CustomTheme", "Custom Theme", "Enable the ability to use custom themes.", "../assets/frog.png"},
    {"CustomRoadUI", "Custom Road UI", "Customize the road UI to your liking.", "../assets/offroad/icon_road.png"},
    {"DeveloperUI", "Developer UI", "Display various information about openpilot and the device itself.", "../assets/offroad/icon_developer.png"},
    {"ScreenBrightness", "Screen Brightness", "Choose a custom screen brightness level or use the default 'Auto' brightness setting.", "../assets/offroad/icon_light.png"},
    {"SteeringWheel", "Steering Wheel Icon", "Replace the stock openpilot steering wheel icon with a custom icon.\n\nWant to submit your own steering wheel? Message me on Discord\n@FrogsGoMoo!", "../assets/offroad/icon_openpilot.png"},
  };

  for (const auto &[key, label, desc, icon] : toggles) {
    ParamControl *control = createParamControl(key, label, desc, icon, this);
    if (key == "CustomRoadUI") {
      createSubControl(key, label, desc, icon, {
        createDualParamControl(new LaneLinesWidth(), new RoadEdgesWidth()),
        createDualParamControl(new PathWidth(), new PathEdgeWidth()),
      });
      createSubButtonControl(key, {
        {"AccelerationPath", "Acceleration Path"},
        {"BlindSpotPath", "Blind Spot Path"},
        {"UnlimitedLength", "'Unlimited' Road UI Length"},
      }, mainLayout);
    } else if (key == "CustomTheme") {
      createSubControl(key, label, desc, icon, {
        createDualParamControl(new CustomColors(), new CustomIcons()),
        createDualParamControl(new CustomSignals(), new CustomSounds()),
      });
    } else if (key == "DeveloperUI") {
      mainLayout->addWidget(new DeveloperUI());
      mainLayout->addWidget(horizontalLine());
    } else if (key == "ScreenBrightness") {
      mainLayout->addWidget(new ScreenBrightness());
      mainLayout->addWidget(horizontalLine());
    } else if (key == "SteeringWheel") {
      mainLayout->addWidget(new SteeringWheel());
      mainLayout->addWidget(horizontalLine());
    } else {
      mainLayout->addWidget(control);
      if (key != std::get<0>(toggles.back())) mainLayout->addWidget(horizontalLine());
    }
  }
  setInitialToggleStates();
}

ParamControl *FrogPilotPanel::createParamControl(const QString &key, const QString &label, const QString &desc, const QString &icon, QWidget *parent) {
  ParamControl *control = new ParamControl(key, label, desc, icon);
  connect(control, &ParamControl::toggleFlipped, [=](bool state) {
    paramsMemory.putBool("FrogPilotTogglesUpdated", true);
    static const QMap<QString, QString> parameterWarnings = {
      {"AggressiveAcceleration", "This will make openpilot driving more aggressively behind lead vehicles!"},
      {"AlwaysOnLateralMain", "This is very experimental and isn't guaranteed to work. If you run into any issues please report it in the FrogPilot Discord!"},
    };
    if (parameterWarnings.contains(key) && params.getBool(key.toStdString())) {
      ConfirmationDialog::toggleAlert("WARNING: " + parameterWarnings[key], "I understand the risks.", parent);
    }
    static const QSet<QString> parameterReboots = {
    };
    if (parameterReboots.contains(key)) {
      if (ConfirmationDialog::toggle("Reboot required to take effect.", "Reboot Now", parent)) {
        Hardware::reboot();
      }
    }
    auto it = childControls.find(key.toStdString());
    if (it != childControls.end()) {
      for (QWidget *widget : it->second) {
        widget->setVisible(state);
      }
    }
  });
  return control;
}

QFrame *FrogPilotPanel::horizontalLine(QWidget *parent) const {
  QFrame *line = new QFrame(parent);
  line->setFrameShape(QFrame::StyledPanel);
  line->setStyleSheet(R"(
    border-width: 1px;
    border-bottom-style: solid;
    border-color: gray;
  )");
  line->setFixedHeight(2);
  return line;
}

QFrame *FrogPilotPanel::whiteHorizontalLine(QWidget *parent) const {
  QFrame *line = new QFrame(parent);
  line->setFrameShape(QFrame::StyledPanel);
  line->setStyleSheet(R"(
    border-width: 1px;
    border-bottom-style: solid;
    border-color: white;
  )");
  line->setFixedHeight(2);
  return line;
}

QWidget *FrogPilotPanel::createDualParamControl(ParamValueControl *control1, ParamValueControl *control2) {
  QWidget *mainControl = new QWidget(this);
  QHBoxLayout *layout = new QHBoxLayout();
  layout->addWidget(control1);
  layout->addStretch();
  layout->addWidget(control2);
  mainControl->setLayout(layout);
  return mainControl;
}

QWidget *FrogPilotPanel::addSubControls(const QString &parentKey, QVBoxLayout *layout, const std::vector<std::tuple<QString, QString, QString>> &controls) {
  QWidget *mainControl = new QWidget(this);
  mainControl->setLayout(layout);
  mainLayout->addWidget(mainControl);
  mainControl->setVisible(params.getBool(parentKey.toStdString()));
  for (const auto &[key, label, desc] : controls) addControl(key, "   " + label, desc, layout);
  return mainControl;
}

void FrogPilotPanel::addControl(const QString &key, const QString &label, const QString &desc, QVBoxLayout *layout, const QString &icon) {
  layout->addWidget(createParamControl(key, label, desc, icon, this));
  layout->addWidget(horizontalLine());
}

void FrogPilotPanel::createSubControl(const QString &key, const QString &label, const QString &desc, const QString &icon, const std::vector<QWidget*> &subControls, const std::vector<std::tuple<QString, QString, QString>> &additionalControls) {
  ParamControl *control = createParamControl(key, label, desc, icon, this);
  mainLayout->addWidget(control);
  mainLayout->addWidget(horizontalLine());
  QVBoxLayout *subControlLayout = new QVBoxLayout();
  for (QWidget *subControl : subControls) {
    subControlLayout->addWidget(subControl);
    subControlLayout->addWidget(horizontalLine());
  }
  QWidget *mainControl = addSubControls(key, subControlLayout, additionalControls);
  connect(control, &ParamControl::toggleFlipped, [=](bool state) { mainControl->setVisible(state); });
}

void FrogPilotPanel::createSubButtonControl(const QString &parentKey, const std::vector<QPair<QString, QString>> &buttonKeys, QVBoxLayout *subControlLayout) {
  QHBoxLayout *buttonsLayout = new QHBoxLayout();
  QWidget *line = horizontalLine();
  buttonsLayout->addStretch();
  for (const auto &[key, label] : buttonKeys) {
    FrogPilotButtonParamControl* button = new FrogPilotButtonParamControl(key, label);
    mainLayout->addWidget(button);
    buttonsLayout->addWidget(button);
    buttonsLayout->addStretch();
    button->setVisible(params.getBool(parentKey.toStdString()));
    childControls[parentKey.toStdString()].push_back(button);
  }
  subControlLayout->addLayout(buttonsLayout);
  line = horizontalLine();
  mainLayout->addWidget(line);
  childControls[parentKey.toStdString()].push_back(line);
}

void FrogPilotPanel::setInitialToggleStates() {
  for (const auto& [key, controlSet] : childControls) {
    bool state = params.getBool(key);
    for (QWidget *widget : controlSet) {
      widget->setVisible(state);
    }
  }
}

void FrogPilotPanel::setDefaultParams() {
  std::map<std::string, std::string> default_values = {
    {"AccelerationPath", "1"},
    {"AccelerationProfile", "3"},
    {"AggressiveAcceleration", "1"},
    {"AggressiveJerk", "5"},
    {"AggressivePersonality", "12"},
    {"AlwaysOnLateral", "1"},
    {"AlwaysOnLateralMain", "0"},
    {"AverageDesiredCurvature", "0"},
    {"BlindSpotPath", "1"},
    {"Compass", "1"},
    {"ConditionalExperimental", "1"},
    {"ConditionalCurves", "1"},
    {"ConditionalCurvesLead", "0"},
    {"ConditionalSlowerLead", "0"},
    {"ConditionalSpeed", "0"},
    {"ConditionalSpeedLead", "0"},
    {"ConditionalStopLights", "1"},
    {"ConditionalSignal", "1"},
    {"CurveSensitivity", "100"},
    {"CustomColors", "1"},
    {"CustomIcons", "1"},
    {"CustomPersonalities", "1"},
    {"CustomSignals", "1"},
    {"CustomSounds", "1"},
    {"CustomTheme", "1"},
    {"CustomRoadUI", "1"},
    {"DeveloperUI", "0"},
    {"DeviceShutdownTimer", "9"},
    {"DisableAllLogging", "0"},
    {"DisableOnroadUploads", "0"},
    {"ExperimentalModeViaWheel", "1"},
    {"EVTable", "0"},
    {"FireTheBabysitter", "0"},
    {"GreenLightAlert", "0"},
    {"IncreasedStoppingDistance", "3"},
    {"LaneChangeTimer", "0"},
    {"LaneDetection", "1"},
    {"LaneLinesWidth", "4"},
    {"LateralTuning", "1"},
    {"LongitudinalTuning", "1"},
    {"LowerVolt", "0"},
    {"Model", "0"},
    {"MuteDM", "1"},
    {"MuteDoor", "1"},
    {"MuteSeatbelt", "1"},
    {"MuteSystemOverheat", "1"},
    {"NNFF", "0"},
    {"NudgelessLaneChange", "1"},
    {"NumericalTemp", "1"},
    {"OneLaneChange", "1"},
    {"PauseLateralOnSignal", "0"},
    {"PathEdgeWidth", "20"},
    {"PathWidth", "61"},
    {"PersonalitiesViaWheel", "1"},
    {"RelaxedJerk", "50"},
    {"RelaxedPersonality", "30"},
    {"RoadEdgesWidth", "2"},
    {"RotatingWheel", "1"},
    {"ScreenBrightness", "101"},
    {"Sidebar", "1"},
    {"SilentMode", "0"},
    {"SmootherBraking", "1"},
    {"SNGHack", "0"},
    {"StandardJerk", "10"},
    {"StandardPersonality", "15"},
    {"SteeringWheel", "1"},
    {"TSS2Tune", "1"},
    {"TurnAggressiveness", "100"},
    {"TurnDesires", "1"},
    {"UnlimitedLength", "1"},
    {"VisionTurnControl", "1"},
    {"WideCameraDisable", "1"}
  };

  bool rebootRequired = false;
  for (const auto& [key, value] : default_values) {
    if (params.get(key).empty()) {
      params.put(key, value);
      rebootRequired = true;
    }
  }

  if (rebootRequired) {
    while (!std::filesystem::exists("/data/openpilot/prebuilt")) {
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    rebootRequired = false;
    Hardware::reboot();
  }
}