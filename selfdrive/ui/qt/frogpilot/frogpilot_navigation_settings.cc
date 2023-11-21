#include "selfdrive/ui/qt/frogpilot/frogpilot_navigation_settings.h"
#include "selfdrive/ui/qt/offroad/frogpilot_settings.h"
#include "selfdrive/ui/ui.h"

QMap<QString, QString> statesMap = {
  // Full U.S. state names and their codes
  {"AK", "Alaska"}, {"AL", "Alabama"}, {"AR", "Arkansas"},
  {"AS", "American Samoa"}, {"AZ", "Arizona"}, {"CA", "California"},
  {"CO", "Colorado"}, {"CT", "Connecticut"}, {"DC", "District of Columbia"},
  {"DE", "Delaware"}, {"FL", "Florida"}, {"GA", "Georgia"},
  {"GM", "Guam"}, {"HI", "Hawaii"}, {"IA", "Iowa"},
  {"ID", "Idaho"}, {"IL", "Illinois"}, {"IN", "Indiana"},
  {"KS", "Kansas"}, {"KY", "Kentucky"}, {"LA", "Louisiana"},
  {"MA", "Massachusetts"}, {"MD", "Maryland"}, {"ME", "Maine"},
  {"MI", "Michigan"}, {"MN", "Minnesota"}, {"MO", "Missouri"},
  {"MP", "Northern Mariana Islands"}, {"MS", "Mississippi"}, {"MT", "Montana"},
  {"NC", "North Carolina"}, {"ND", "North Dakota"}, {"NE", "Nebraska"},
  {"NH", "New Hampshire"}, {"NJ", "New Jersey"}, {"NM", "New Mexico"},
  {"NV", "Nevada"}, {"NY", "New York"}, {"OH", "Ohio"},
  {"OK", "Oklahoma"}, {"OR", "Oregon"}, {"PA", "Pennsylvania"},
  {"PR", "Puerto Rico"}, {"RI", "Rhode Island"}, {"SC", "South Carolina"},
  {"SD", "South Dakota"}, {"TN", "Tennessee"}, {"TX", "Texas"},
  {"UT", "Utah"}, {"VA", "Virginia"}, {"VI", "Virgin Islands"},
  {"VT", "Vermont"}, {"WA", "Washington"}, {"WI", "Wisconsin"},
  {"WV", "West Virginia"}, {"WY", "Wyoming"}
};

QMap<QString, QString> countriesMap = {
  // Full nation names and their codes
  {"AE", "United Arab Emirates"}, {"AF", "Afghanistan"}, {"AL", "Albania"},
  {"AM", "Armenia"}, {"AO", "Angola"}, {"AQ", "Antarctica"}, {"AR", "Argentina"},
  {"AT", "Austria"}, {"AU", "Australia"}, {"AZ", "Azerbaijan"}, {"BA", "Bosnia and Herzegovina"},
  {"BD", "Bangladesh"}, {"BE", "Belgium"}, {"BF", "Burkina Faso"}, {"BG", "Bulgaria"},
  {"BI", "Burundi"}, {"BJ", "Benin"}, {"BN", "Brunei"}, {"BO", "Bolivia"},
  {"BR", "Brazil"}, {"BS", "Bahamas"}, {"BT", "Bhutan"}, {"BW", "Botswana"},
  {"BY", "Belarus"}, {"BZ", "Belize"}, {"CA", "Canada"}, {"CD", "Congo (Kinshasa)"},
  {"CF", "Central African Republic"}, {"CG", "Congo (Brazzaville)"}, {"CH", "Switzerland"},
  {"CI", "Ivory Coast"}, {"CL", "Chile"}, {"CM", "Cameroon"}, {"CN", "China"},
  {"CO", "Colombia"}, {"CR", "Costa Rica"}, {"CU", "Cuba"}, {"CY", "Cyprus"},
  {"CZ", "Czech Republic"}, {"DE", "Germany"}, {"DJ", "Djibouti"}, {"DK", "Denmark"},
  {"DO", "Dominican Republic"}, {"DZ", "Algeria"}, {"EC", "Ecuador"}, {"EE", "Estonia"},
  {"EG", "Egypt"}, {"ER", "Eritrea"}, {"ES", "Spain"}, {"ET", "Ethiopia"},
  {"FI", "Finland"}, {"FJ", "Fiji"}, {"FK", "Falkland Islands"}, {"FR", "France"},
  {"GA", "Gabon"}, {"GB", "United Kingdom"}, {"GE", "Georgia"}, {"GH", "Ghana"},
  {"GL", "Greenland"}, {"GM", "Gambia"}, {"GN", "Guinea"}, {"GQ", "Equatorial Guinea"},
  {"GR", "Greece"}, {"GT", "Guatemala"}, {"GW", "Guinea Bissau"}, {"GY", "Guyana"},
  {"HN", "Honduras"}, {"HR", "Croatia"}, {"HT", "Haiti"}, {"HU", "Hungary"},
  {"ID", "Indonesia"}, {"IE", "Ireland"}, {"IL", "Israel"}, {"IN", "India"},
  {"IQ", "Iraq"}, {"IR", "Iran"}, {"IS", "Iceland"}, {"IT", "Italy"},
  {"JM", "Jamaica"}, {"JO", "Jordan"}, {"JP", "Japan"}, {"KE", "Kenya"},
  {"KG", "Kyrgyzstan"}, {"KH", "Cambodia"}, {"KP", "North Korea"}, {"KR", "South Korea"},
  {"KW", "Kuwait"}, {"KZ", "Kazakhstan"}, {"LA", "Laos"}, {"LB", "Lebanon"},
  {"LK", "Sri Lanka"}, {"LR", "Liberia"}, {"LS", "Lesotho"}, {"LT", "Lithuania"},
  {"LU", "Luxembourg"}, {"LV", "Latvia"}, {"LY", "Libya"}, {"MA", "Morocco"},
  {"MD", "Moldova"}, {"ME", "Montenegro"}, {"MG", "Madagascar"}, {"MK", "Macedonia"},
  {"ML", "Mali"}, {"MM", "Myanmar"}, {"MN", "Mongolia"}, {"MR", "Mauritania"},
  {"MW", "Malawi"}, {"MX", "Mexico"}, {"MY", "Malaysia"}, {"MZ", "Mozambique"},
  {"NA", "Namibia"}, {"NC", "New Caledonia"}, {"NE", "Niger"}, {"NG", "Nigeria"},
  {"NI", "Nicaragua"}, {"NL", "Netherlands"}, {"NO", "Norway"}, {"NP", "Nepal"},
  {"NZ", "New Zealand"}, {"OM", "Oman"}, {"PA", "Panama"}, {"PE", "Peru"},
  {"PG", "Papua New Guinea"}, {"PH", "Philippines"}, {"PK", "Pakistan"}, {"PL", "Poland"},
  {"PR", "Puerto Rico"}, {"PS", "West Bank"}, {"PT", "Portugal"}, {"PY", "Paraguay"},
  {"QA", "Qatar"}, {"RO", "Romania"}, {"RS", "Serbia"}, {"RU", "Russia"},
  {"RW", "Rwanda"}, {"SA", "Saudi Arabia"}, {"SB", "Solomon Islands"}, {"SD", "Sudan"},
  {"SE", "Sweden"}, {"SI", "Slovenia"}, {"SK", "Slovakia"}, {"SL", "Sierra Leone"},
  {"SN", "Senegal"}, {"SO", "Somalia"}, {"SR", "Suriname"}, {"SS", "South Sudan"},
  {"SV", "El Salvador"}, {"SY", "Syria"}, {"SZ", "Swaziland"}, {"TD", "Chad"},
  {"TF", "French Southern Territories"}, {"TG", "Togo"}, {"TH", "Thailand"}, {"TJ", "Tajikistan"},
  {"TL", "East Timor"}, {"TM", "Turkmenistan"}, {"TN", "Tunisia"}, {"TR", "Turkey"},
  {"TT", "Trinidad and Tobago"}, {"TW", "Taiwan"}, {"TZ", "Tanzania"}, {"UA", "Ukraine"},
  {"UG", "Uganda"}, {"US", "United States"}, {"UY", "Uruguay"}, {"UZ", "Uzbekistan"},
  {"VE", "Venezuela"}, {"VN", "Vietnam"}, {"VU", "Vanuatu"}, {"YE", "Yemen"},
  {"ZA", "South Africa"}, {"ZM", "Zambia"}, {"ZW", "Zimbabwe"},
};

QString formatDownloadStatus(const std::string &jsonData) {
  int totalFiles = 0, downloadedFiles = 0;
  std::string::size_type pos = 0;

  if ((pos = jsonData.find("\"total_files\":")) != std::string::npos) {
    totalFiles = std::stoi(jsonData.substr(pos + 14));
  }
  if ((pos = jsonData.find("\"downloaded_files\":")) != std::string::npos) {
    downloadedFiles = std::stoi(jsonData.substr(pos + 19));
  }

  if (totalFiles == 0) {
    return "Ready";
  }
  return totalFiles > 0 && downloadedFiles < totalFiles ?
         "Downloading: " + QString::number(downloadedFiles) + "/" + QString::number(totalFiles) :
         "Downloaded";
}

QString formatSize(unsigned long long sizeMB) {
  if (sizeMB < 1024) {
    return QString::number(sizeMB, 'f', 0) + " MB";
  } else {
    double sizeGB = sizeMB / 1024.0;
    return QString::number(sizeGB, 'f', 2) + " GB";
  }
}

FrogPilotNavigationPanel::FrogPilotNavigationPanel(SettingsWindow *parent) : ListWidget(parent) {
  mapboxSettingsLabel->setText("Device Offline. Connect to the internet to use Navigation and download maps.");
  mapboxSettingsLabel->setAlignment(Qt::AlignTop | Qt::AlignCenter);
  addItem(mapboxSettingsLabel);
  setSpacing(50);

  hasPrime = params.getInt("PrimeType") != 0;

  if (!hasPrime) {
    addItem(new SearchInput());

    createMapboxKeyControl(publicMapboxKeyControl, "Public Mapbox Key", "MapboxPublicKey", "pk.");
    createMapboxKeyControl(secretMapboxKeyControl, "Secret Mapbox Key", "MapboxSecretKey", "sk.");

    setupButton = new ButtonControl(tr("Mapbox Setup Instructions"), tr("VIEW"), tr("View the instructions to set up MapBox for Primeless Navigation."));
    QObject::connect(setupButton, &ButtonControl::clicked, this, &FrogPilotNavigationPanel::displaySetup);
    addItem(setupButton);

    setupCompleted = !params.get("MapboxPublicKey").empty() && !params.get("MapboxSecretKey").empty();
  }

  addItem(offlineMapsSize = new LabelControl(tr("Offline Maps Size"), ""));
  addItem(offlineMapsStatus = new LabelControl(tr("Offline Maps Status"), ""));

  manageOfflineMapsButton = new ButtonControl(tr("Manage Offline Maps"), tr("READY"), tr("Remove your downloaded offline maps to clear up storage space."));
  QObject::connect(manageOfflineMapsButton, &ButtonControl::clicked, [this]() {
    this->manageOfflineMaps(this);
  });
  addItem(manageOfflineMapsButton);

  selectMapsButton = new ButtonControl(tr("Offline Maps"), tr("SELECT"), tr("Select your desired maps to download."));
  QObject::connect(selectMapsButton, &ButtonControl::clicked, this, &FrogPilotNavigationPanel::selectMaps);
  addItem(selectMapsButton);

  QObject::connect(uiState(), &UIState::uiUpdate, this, &FrogPilotNavigationPanel::updateState);
}

void FrogPilotNavigationPanel::updateState() {
  if (!isVisible()) return;

  if (!hasPrime) {
    mapboxPublicKeySet = !params.get("MapboxPublicKey").empty();
    mapboxSecretKeySet = !params.get("MapboxSecretKey").empty();
    setupCompleted = mapboxSecretKeySet && mapboxPublicKeySet;
  
    publicMapboxKeyControl->setText(mapboxPublicKeySet ? tr("REMOVE") : tr("ADD"));
    secretMapboxKeyControl->setText(mapboxSecretKeySet ? tr("REMOVE") : tr("ADD"));
  
    const QString newStep = setupCompleted ? "setup_completed.png" :
                            mapboxSecretKeySet ? "both_keys_set.png" :
                            mapboxPublicKeySet ? "public_key_set.png" : "no_keys_set.png";
  
    if (imageLabel->isVisible() && currentStep != newStep) {
      currentStep = newStep;
      displaySetup();
    }
  }

  const QString ipAddress = wifi->getIp4Address();
  mapboxSettingsLabel->setText(ipAddress.isEmpty() ?
    "Device Offline. Connect to the internet to use Navigation." :
    QString(ipFormat).arg(ipAddress));

  if (manageOfflineMapsButton->text() != tr("REBOOT")) {
    offlineMapsSize->setText(formatSize(paramsMemory.getInt("OfflineMapsSize")));
    offlineMapsStatus->setText(formatDownloadStatus(params.get("OSMDownloadProgress")));

    const QDir dir("/data/media/0/osm/offline");
    manageOfflineMapsButton->setText(dir.exists() ? tr("REMOVE") :
                                     !params.get("MapSelected").empty() ? tr("DOWNLOAD") : "");
  }
}

void FrogPilotNavigationPanel::selectMaps() {
  QStringList locationNames{"United States"};
  QMap<QString, QString> locationMap;

  const auto processLocations = [&](const QMap<QString, QString> &sourceMap) {
    QStringList names;
    for (auto it = sourceMap.constBegin(); it != sourceMap.constEnd(); ++it) {
      names.append(it.value());
      locationMap.insert(it.value(), it.key());
    }
    std::sort(names.begin(), names.end());
    return names;
  };

  locationNames += processLocations(statesMap) + processLocations(countriesMap);

  const QString currentSelection = QString::fromStdString(params.get("MapSelected"));
  const QString selectedLocationName = MultiOptionDialog::getSelection(tr("Select a location to download"), locationNames, locationMap.key(currentSelection), this);

  if (!selectedLocationName.isEmpty()) {
    QString selectedCode = locationMap.value(selectedLocationName);
    QJsonObject json;
    json.insert(locationNames.contains(selectedLocationName) ? "nations" : "states", QJsonArray{selectedCode});
    params.put("MapSelected", selectedLocationName.toStdString());
    paramsMemory.put("OSMDownloadLocations", QJsonDocument(json).toJson(QJsonDocument::Compact).toStdString());
    selectMapsButton->setValue(selectedLocationName);
  }
}

void FrogPilotNavigationPanel::manageOfflineMaps(QWidget *parent) {
  if (manageOfflineMapsButton->text() == tr("REMOVE")) {
    system("pkill mapd");
    paramsMemory.remove("OSMDownloadLocations");
    params.remove("OSMDownloadProgress");
    system("rm -r /data/media/0/osm/offline");
    if (ConfirmationDialog::toggle("Reboot required to redownload maps.", "Reboot Now", parent)) {
      Hardware::reboot();
    } else {
      manageOfflineMapsButton->setText(tr("REBOOT"));
    }
  } else if (manageOfflineMapsButton->text() == tr("REBOOT")) {
    Hardware::reboot();
  } else {
    QMap<QString, QString> locationMap;
    auto populateLocationMap = [&](const QMap<QString, QString> &sourceMap) {
      for (auto it = sourceMap.begin(); it != sourceMap.end(); ++it) {
        locationMap.insert(it.value(), it.key());
      }
    };

    populateLocationMap(statesMap);
    populateLocationMap(countriesMap);

    QString currentSelection = QString::fromStdString(params.get("MapSelected"));
    QString selectedCode = locationMap.value(currentSelection);

    if (!selectedCode.isEmpty()) {
      QStringList nationNames;
      for (auto it = countriesMap.begin(); it != countriesMap.end(); ++it) {
        nationNames.append(it.value());
      }
      QString locationType = nationNames.contains(currentSelection) ? "nations" : "states";
      QJsonObject json;
      json.insert(locationType, QJsonArray{selectedCode});
      paramsMemory.put("OSMDownloadLocations", QJsonDocument(json).toJson(QJsonDocument::Compact).toStdString());
    }
  }

  updateState();
}

void FrogPilotNavigationPanel::createMapboxKeyControl(ButtonControl *&control, const QString &label, const std::string &paramKey, const QString &prefix) {
  control = new ButtonControl(label, "", tr("ADD"), this);
  QObject::connect(control, &ButtonControl::clicked, this, [this, &control, label, paramKey, prefix] {
    if (control->text() == tr("ADD")) {
      QString key = InputDialog::getText(tr("Enter your %1").arg(label), this);
      if (!key.startsWith(prefix)) {
        key = prefix + key;
      }
      if (key.length() >= 80) {
        params.put(paramKey, key.toStdString());
      }
    } else {
      params.remove(paramKey);
    }
  });
  addItem(control);
  control->setText(paramKey.empty() ? tr("ADD") : tr("REMOVE"));
}

void FrogPilotNavigationPanel::displaySetup() {
  QPixmap scaledImage = QPixmap(imagePath + currentStep).scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

  imageLabel->setPixmap(scaledImage);
  imageLabel->resize(scaledImage.size());
  imageLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  imageLabel->setAlignment(Qt::AlignCenter);

  imageLabel->show();
}
