#include "selfdrive/ui/qt/offroad/frogpilot_settings.h"

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
