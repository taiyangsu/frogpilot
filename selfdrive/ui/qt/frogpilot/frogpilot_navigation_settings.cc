#include "selfdrive/ui/qt/frogpilot/frogpilot_navigation_settings.h"
#include "selfdrive/ui/qt/offroad/frogpilot_settings.h"


FrogPilotNavigationPanel::FrogPilotNavigationPanel(QWidget *parent) : FrogPilotPanel(parent) {
  primelessLayout->addWidget(mapboxSettingsLabel, 0, Qt::AlignTop | Qt::AlignCenter);
  primelessLayout->addSpacing(25);
  primelessLayout->addWidget(horizontalLine());

  createMapboxKeyControl(publicMapboxKeyControl, "Public Mapbox Key", "MapboxPublicKey", "pk.");
  createMapboxKeyControl(secretMapboxKeyControl, "Secret Mapbox Key", "MapboxSecretKey", "sk.");

  primelessLayout->addWidget(new SearchInput());
  primelessLayout->addWidget(horizontalLine());

  ButtonControl *setupButton = new ButtonControl(tr("Mapbox Setup Instructions"), "", tr("VIEW"), this);
  setupButton->setText(tr("VIEW"));
  QObject::connect(setupButton, &ButtonControl::clicked, this, &FrogPilotNavigationPanel::displaySetup);
  primelessLayout->addWidget(setupButton);
  primelessLayout->addWidget(horizontalLine());

  QObject::connect(updateTimer, &QTimer::timeout, this, [this] {
    refresh(publicMapboxKeyControl, "MapboxPublicKey");
    refresh(secretMapboxKeyControl, "MapboxSecretKey");
  });

  setupCompleted = !params.get("MapboxPublicKey").empty() && !params.get("MapboxSecretKey").empty();

  mainLayout->addLayout(primelessLayout);

  offlineMapsSize = new LabelControl(tr("Offline Maps Size"), formatSize(paramsMemory.getInt("OfflineMapsSize")));
  mainLayout->addWidget(offlineMapsSize);
  mainLayout->addWidget(horizontalLine());

  offlineMapsStatus = new LabelControl(tr("Offline Maps Status"), formatDownloadStatus(params.get("OSMDownloadProgress")));
  mainLayout->addWidget(offlineMapsStatus);
  mainLayout->addWidget(horizontalLine());

  removeOfflineMapsButton = new ButtonControl(tr("Remove Offline Maps"), "", tr("REMOVE"), this);
  removeOfflineMapsButton->setText(tr("REMOVE"));
  QObject::connect(removeOfflineMapsButton, &ButtonControl::clicked, [this]() {
    this->removeOfflineMaps(this);
  });
  mainLayout->addWidget(removeOfflineMapsButton);
  mainLayout->addWidget(horizontalLine());

  selectMapsButton = new ButtonControl(tr("Offline Maps"), tr("SELECT"));
  selectMapsButton->setText(tr("SELECT"));
  QObject::connect(selectMapsButton, &ButtonControl::clicked, this, &FrogPilotNavigationPanel::selectMaps);
  mainLayout->addWidget(selectMapsButton);
}

void FrogPilotNavigationPanel::refresh(ButtonControl *control, const std::string &paramKey) {
  if (!isVisible()) return;

  QString key = QString::fromStdString(params.get(paramKey));

  control->setText(key.isEmpty() ? tr("ADD") : tr("REMOVE"));

  mapboxPublicKeySet = !params.get("MapboxPublicKey").empty();
  mapboxSecretKeySet = !params.get("MapboxSecretKey").empty();

  if (!mapboxSecretKeySet || !mapboxPublicKeySet) {
    setupCompleted = false;
  }

  QString previousStep = currentStep;
  currentStep = setupCompleted ? "setup_completed.png" :
                mapboxSecretKeySet ? "both_keys_set.png" :
                mapboxPublicKeySet ? "public_key_set.png" : 
                "no_keys_set.png";
  if (imageLabel->isVisible() && previousStep != currentStep) {
    displaySetup();
  }

  if (wifi->getIp4Address().isEmpty()) {
    mapboxSettingsLabel->setText("Device Offline. Connect to the internet to use Navigation.");
  } else {
    mapboxSettingsLabel->setText(QString(ipFormat).arg(wifi->getIp4Address()));
  }

  offlineMapsSize->setText(formatSize(paramsMemory.getInt("OfflineMapsSize")));
  offlineMapsStatus->setText(formatDownloadStatus(params.get("OSMDownloadProgress")));

  QDir dir("/data/media/0/osm/offline");
  if (dir.exists()) {
    removeOfflineMapsButton->setText(tr("REMOVE"));
  } else {
    removeOfflineMapsButton->setText(tr("REDOWNLOAD"));
  }
}

void FrogPilotNavigationPanel::showEvent(QShowEvent *event) {
  QWidget::showEvent(event);

  if (params.getInt("PrimeType") != 0) {
    for (int i = 0; i < mainLayout->count(); ++i) {
      QWidget *widget = mainLayout->itemAt(i)->widget();
      if (widget) widget->setVisible(false);
    }
  }
  imageLabel->hide();

  updateTimer->start(50);
}

void FrogPilotNavigationPanel::hideEvent(QHideEvent *event) {
  QWidget::hideEvent(event);

  for (int i = 0; i < mainLayout->count(); ++i) {
    QWidget *widget = mainLayout->itemAt(i)->widget();
    if (widget) widget->setVisible(true);
  }
  for (int i = 0; i < primelessLayout->count(); ++i) {
    QWidget *widget = primelessLayout->itemAt(i)->widget();
    if (widget) widget->setVisible(true);
  }
  imageLabel->hide();

  updateTimer->stop();
}

void FrogPilotNavigationPanel::selectMaps() {
  QStringList locationNames{"United States"}, stateNames, nationNames;
  QMap<QString, QString> locationMap;
  for (const QString &stateCode : statesMap.keys()) {
    QString stateName = statesMap[stateCode];
    stateNames.append(stateName);
    locationMap[stateName] = stateCode;
  }
  for (const QString &countryCode : countriesMap.keys()) {
    QString countryName = countriesMap[countryCode];
    nationNames.append(countryName);
    locationMap[countryName] = countryCode;
  }
  std::sort(stateNames.begin(), stateNames.end());
  std::sort(nationNames.begin(), nationNames.end());
  locationNames += stateNames + nationNames;
  QString currentSelection = QString::fromStdString(params.get("MapSelected"));
  QString currentLocationName = locationMap.key(currentSelection, QString());
  QString selectedLocationName = MultiOptionDialog::getSelection(tr("Select a location to download"), locationNames, currentLocationName, this);
  if (!selectedLocationName.isEmpty()) {
    QString selectedCode = locationMap[selectedLocationName];
    QJsonObject json;
    json.insert(nationNames.contains(selectedLocationName) ? "nations" : "states", QJsonArray{selectedCode});
    params.put("MapSelected", selectedLocationName.toStdString());
    paramsMemory.put("OSMDownloadLocations", QJsonDocument(json).toJson(QJsonDocument::Compact).toStdString());
    selectMapsButton->setValue(selectedLocationName);
  }
}

void FrogPilotNavigationPanel::removeOfflineMaps(QWidget *parent) {
  if (removeOfflineMapsButton->text() == tr("REMOVE")) {
    if (ConfirmationDialog::toggle("Reboot required.", "Remove Maps", parent)) {
      system("pkill mapd");
      paramsMemory.remove("OSMDownloadLocations");
      params.remove("OSMDownloadProgress");
      system("rm -r /data/media/0/osm/offline");
      Hardware::reboot();
    }
  } else {
    QMap<QString, QString> locationMap;
    for (const QString &stateCode : statesMap.keys()) {
      locationMap[statesMap[stateCode]] = stateCode;
    }
    for (const QString &countryCode : countriesMap.keys()) {
      locationMap[countriesMap[countryCode]] = countryCode;
    }

    QString currentSelection = QString::fromStdString(params.get("MapSelected"));
    QString selectedCode = locationMap.value(currentSelection);

    if (!selectedCode.isEmpty()) {
      QStringList nationNames;
      for (const QString &countryCode : countriesMap.keys()) {
        nationNames.append(countriesMap[countryCode]);
      }
      QString locationType = nationNames.contains(currentSelection) ? "nations" : "states";
      QJsonObject json;
      json.insert(locationType, QJsonArray{selectedCode});
      paramsMemory.put("OSMDownloadLocations", QJsonDocument(json).toJson(QJsonDocument::Compact).toStdString());
    }
  }

  refresh(removeOfflineMapsButton, "");
}

void FrogPilotNavigationPanel::createMapboxKeyControl(ButtonControl *&control, const QString &label, const std::string &paramKey, const QString &prefix) {
  control = new ButtonControl(label, "", tr("ADD"), this);
  QObject::connect(control, &ButtonControl::clicked, this, [this, &control, label, paramKey, prefix] {
    if (control->text() == tr("ADD")) {
      QString key = InputDialog::getText(tr(("Enter your " + label).toStdString().c_str()), this);
      if (!key.startsWith(prefix)) {
        key = prefix + key;
      }
      if (key.length() >= 80) {
        params.put(paramKey, key.toStdString());
      }
    } else {
      params.remove(paramKey);
    }
    refresh(control, paramKey);
  });
  primelessLayout->addWidget(control);
  primelessLayout->addWidget(horizontalLine());
  refresh(control, paramKey);
}

void FrogPilotNavigationPanel::displaySetup() {
  QPixmap scaledImage = QPixmap(imagePath + currentStep).scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

  imageLabel->setPixmap(scaledImage);
  imageLabel->resize(scaledImage.size());
  imageLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  imageLabel->setAlignment(Qt::AlignCenter);

  for (int i = 0; i < mainLayout->count(); ++i) {
    QWidget *widget = mainLayout->itemAt(i)->widget();
    if (widget) widget->setVisible(false);
  }
  for (int i = 0; i < primelessLayout->count(); ++i) {
    QWidget *widget = primelessLayout->itemAt(i)->widget();
    if (widget) widget->setVisible(false);
  }

  imageLabel->show();
}
