#pragma once

#include <cmath>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QTimer>

#include "selfdrive/ui/qt/widgets/controls.h"

void updateFrogPilotToggles();

QColor loadThemeColors(const QString &colorKey);

const QString buttonStyle = R"(
  QPushButton {
    border-radius: 50px;
    font-size: 40px;
    font-weight: 500;
    height: 100px;
    padding: 0 25px;
    color: #E4E4E4;
    background-color: #393939;
  }
  QPushButton:pressed {
    background-color: #4a4a4a;
  }
  QPushButton:checked:enabled {
    background-color: #33Ab4C;
  }
  QPushButton:disabled {
    color: #33E4E4E4;
  }
)";

class FrogPilotConfirmationDialog : public ConfirmationDialog {
  Q_OBJECT

public:
  explicit FrogPilotConfirmationDialog(const QString &prompt_text, const QString &confirm_text,
                                       const QString &cancel_text, const bool rich, QWidget *parent);
  static bool toggle(const QString &prompt_text, const QString &confirm_text, QWidget *parent);
  static bool toggleAlert(const QString &prompt_text, const QString &button_text, QWidget *parent);
  static bool yesorno(const QString &prompt_text, QWidget *parent);
};

class FrogPilotListWidget : public QWidget {
  Q_OBJECT

public:
  explicit FrogPilotListWidget(QWidget *parent = nullptr) : QWidget(parent), outer_layout(this), inner_layout() {
    outer_layout.setMargin(0);
    outer_layout.setSpacing(0);
    outer_layout.addLayout(&inner_layout);

    inner_layout.setMargin(0);
    inner_layout.setSpacing(25);  // default spacing is 25
    outer_layout.addStretch();
  }

  inline void addItem(QWidget *w) {
    inner_layout.addWidget(w);
    adjustStretch();
  }

  inline void addItem(QLayout *layout) {
    inner_layout.addLayout(layout);
    adjustStretch();
  }

protected:
  void paintEvent(QPaintEvent *event) {
    QPainter p(this);
    p.setPen(Qt::gray);

    std::vector<QRect> visibleRects;
    for (int i = 0; i < inner_layout.count(); ++i) {
      QWidget *widget = inner_layout.itemAt(i)->widget();
      if (widget && widget->isVisible()) {
        visibleRects.push_back(widget->geometry());
      }
    }

    int lineOffset = inner_layout.spacing() / 2;
    for (size_t i = 0; i + 1 < visibleRects.size(); ++i) {
      int bottom = visibleRects[i].bottom() + lineOffset;
      p.drawLine(visibleRects[i].left() + 40, bottom, visibleRects[i].right() - 40, bottom);
    }
  }

private:
  void adjustStretch() {
    if (inner_layout.count() > 3) {
      outer_layout.addStretch();
    }
  }

  QVBoxLayout outer_layout;
  QVBoxLayout inner_layout;
};

class FrogPilotButtonsControl : public AbstractControl {
  Q_OBJECT

public:
  FrogPilotButtonsControl(const QString &title, const QString &desc,
                          const std::vector<QString> &button_labels,
                          bool checkable = false, int minimum_button_width = 225,
                          QWidget *parent = nullptr)
    : AbstractControl(title, desc, ""), button_group(new QButtonGroup(this)) {

    button_group->setExclusive(true);

    for (int i = 0; i < button_labels.size(); ++i) {
      QPushButton *button = new QPushButton(button_labels[i], this);
      button->setCheckable(checkable);
      button->setStyleSheet(buttonStyle);
      button->setMinimumWidth(minimum_button_width);

      hlayout->addWidget(button);

      button_group->addButton(button, i);

      connect(button, &QPushButton::clicked, this, [this, i]() { emit buttonClicked(i); });
    }
  }

  void setEnabled(bool enable) {
    for (QAbstractButton *btn : button_group->buttons()) {
      btn->setEnabled(enable);
    }
  }

  void setCheckedButton(int id) {
    if (QAbstractButton *button = button_group->button(id)) {
      button->setChecked(true);
    }
  }

  void setEnabledButtons(int id, bool enable) {
    if (QPushButton *button = qobject_cast<QPushButton *>(button_group->button(id))) {
      button->setEnabled(enable);
    }
  }

  void setText(int id, const QString &text) {
    if (QPushButton *button = qobject_cast<QPushButton *>(button_group->button(id))) {
      button->setText(text);
    }
  }

private:
  QButtonGroup *button_group;

signals:
  void buttonClicked(int id);
};

class FrogPilotButtonToggleControl : public ParamControl {
  Q_OBJECT

public:
  FrogPilotButtonToggleControl(const QString &param, const QString &title, const QString &desc,
                               const std::vector<QString> &button_params, const std::vector<QString> &button_labels,
                               const int minimum_button_width = 225, QWidget *parent = nullptr)
    : ParamControl(param, title, desc, "", parent),
      key(param.toStdString()),
      button_params(button_params),
      button_group(new QButtonGroup(this)) {

    button_group->setExclusive(false);

    for (int i = 0; i < button_labels.size(); ++i) {
      QPushButton *button = new QPushButton(button_labels[i], this);
      button->setCheckable(true);
      button->setStyleSheet(buttonStyle);
      button->setMinimumWidth(minimum_button_width);

      hlayout->addWidget(button);
      hlayout->insertWidget(hlayout->indexOf(&toggle) - 1, button);

      button_group->addButton(button, i);

      connect(button, &QPushButton::clicked, this, [this, i, button_params](bool checked) {
        params.putBool(button_params[i].toStdString(), checked);
        button_group->button(i)->setChecked(checked);
        emit buttonClicked(i);
      });
    }

    connect(this, &ToggleControl::toggleFlipped, this, &FrogPilotButtonToggleControl::refresh);
  }

  void refresh() {
    bool state = params.getBool(key);
    if (state != toggle.on) {
      toggle.togglePosition();
    }

    const QList<QAbstractButton *> buttons = button_group->buttons();
    for (QAbstractButton *button : buttons) {
      if (button) {
        button->setVisible(state);
        int buttonIndex = buttons.indexOf(button);
        button->setChecked(params.getBool(button_params[buttonIndex].toStdString()));
      }
    }
  }

  void showEvent(QShowEvent *event) override {
    refresh();
    QWidget::showEvent(event);
  }

private:
  Params params;
  QButtonGroup *button_group;
  std::string key;
  std::vector<QString> button_params;

signals:
  void buttonClicked(int id);
};

class FrogPilotParamManageControl : public ParamControl {
  Q_OBJECT

public:
  FrogPilotParamManageControl(const QString &param, const QString &title, const QString &desc, const QString &icon, QWidget *parent = nullptr)
    : ParamControl(param, title, desc, icon, parent),
      key(param.toStdString()),
      manage_button(new ButtonControl("", tr("MANAGE"))) {

    hlayout->insertWidget(hlayout->indexOf(&toggle) - 1, manage_button);

    connect(this, &ToggleControl::toggleFlipped, this, &FrogPilotParamManageControl::refresh);
    connect(manage_button, &ButtonControl::clicked, this, &FrogPilotParamManageControl::manageButtonClicked);
  }

protected:
  void showEvent(QShowEvent *event) {
    ParamControl::showEvent(event);
    refresh();
  }

signals:
  void manageButtonClicked();

private:
  void refresh() {
    manage_button->setVisible(params.getBool(key));
  }

  ButtonControl *manage_button;
  Params params;
  std::string key;
};

class FrogPilotParamValueControl : public ParamControl {
  Q_OBJECT

public:
  FrogPilotParamValueControl(const QString &param, const QString &title, const QString &desc, const QString &icon,
                             const float &minValue, const float &maxValue, const std::map<int, QString> &valueLabels,
                             QWidget *parent = nullptr, const bool &loop = true, const QString &label = "",
                             const float &division = 1.0f, const float &interval = 1.0f)
      : ParamControl(param, title, desc, icon, parent),
        minValue(minValue), maxValue(maxValue), valueLabelMappings(valueLabels), loop(loop), labelText(label),
        division(division), interval(interval), previousValue(0.0f), value(0.0f) {
    key = param.toStdString();

    valueLabel = new QLabel(this);
    hlayout->addWidget(valueLabel);

    QPushButton *decrementButton = createButton("-", this);
    QPushButton *incrementButton = createButton("+", this);

    hlayout->addWidget(decrementButton);
    hlayout->addWidget(incrementButton);

    countdownTimer = new QTimer(this);
    countdownTimer->setInterval(150);
    countdownTimer->setSingleShot(true);

    connect(countdownTimer, &QTimer::timeout, this, &FrogPilotParamValueControl::handleTimeout);

    connect(decrementButton, &QPushButton::pressed, this, [=]() { updateValue(-interval); });
    connect(incrementButton, &QPushButton::pressed, this, [=]() { updateValue(interval); });

    connect(decrementButton, &QPushButton::released, this, &FrogPilotParamValueControl::restartTimer);
    connect(incrementButton, &QPushButton::released, this, &FrogPilotParamValueControl::restartTimer);

    toggle.hide();
  }

  void restartTimer() {
    countdownTimer->stop();
    countdownTimer->start();

    emit valueChanged(value);
  }

  void handleTimeout() {
    previousValue = value;
  }

  void updateValue(float intervalChange) {
    int previousValueAdjusted = round(previousValue * 100) / 100 / intervalChange;
    int valueAdjusted = round(value * 100) / 100 / intervalChange;

    if (std::fabs(previousValueAdjusted - valueAdjusted) > 5 && std::fmod(valueAdjusted, 5) == 0) {
      intervalChange *= 5;
    }

    value += intervalChange;

    if (loop) {
      if (value < minValue) {
        value = maxValue;
      } else if (value > maxValue) {
        value = minValue;
      }
    } else {
      value = std::max(minValue, std::min(maxValue, value));
    }

    params.putFloat(key, value);
    refresh();
  }

  void refresh() {
    value = params.getFloat(key);

    QString text;
    auto it = valueLabelMappings.find(value);
    int decimals = interval < 1.0f ? static_cast<int>(-std::log10(interval)) : 2;

    if (division > 1.0f) {
      text = QString::number(value / division, 'g', division >= 10.0f ? 4 : 3);
    } else {
      if (it != valueLabelMappings.end()) {
        text = it->second;
      } else {
        if (value >= 100.0f) {
          text = QString::number(value, 'f', 0);
        } else {
          text = QString::number(value, interval < 1.0f ? 'f' : 'g', decimals);
        }
      }
    }

    if (!labelText.isEmpty()) {
      text += labelText;
    }

    valueLabel->setText(text);
    valueLabel->setStyleSheet("QLabel { color: #E0E879; }");
  }

  void updateControl(float newMinValue, float newMaxValue, const QString &newLabel, float newDivision = 1.0f) {
    minValue = newMinValue;
    maxValue = newMaxValue;
    labelText = newLabel;
    division = newDivision;
  }

  void showEvent(QShowEvent *event) {
    refresh();
    previousValue = value;
  }

signals:
  void valueChanged(float value);

private:
  Params params;

  bool loop;

  float division;
  float interval;
  float maxValue;
  float minValue;
  float previousValue;
  float value;

  QLabel *valueLabel;
  QString labelText;

  std::map<int, QString> valueLabelMappings;
  std::string key;

  QTimer *countdownTimer;

  QPushButton *createButton(const QString &text, QWidget *parent) {
    QPushButton *button = new QPushButton(text, parent);
    button->setFixedSize(150, 100);
    button->setAutoRepeat(true);
    button->setAutoRepeatInterval(150);
    button->setAutoRepeatDelay(500);
    button->setStyleSheet(R"(
      QPushButton {
        border-radius: 50px;
        font-size: 50px;
        font-weight: 500;
        height: 100px;
        padding: 0 25 0 25;
        color: #E4E4E4;
        background-color: #393939;
      }
      QPushButton:pressed {
        background-color: #4a4a4a;
      }
    )");
    return button;
  }
};

class FrogPilotParamValueToggleControl : public FrogPilotParamValueControl {
  Q_OBJECT

public:
  FrogPilotParamValueToggleControl(const QString &param, const QString &title, const QString &desc, const QString &icon,
                                   const float &minValue, const float &maxValue, const std::map<int, QString> &valueLabels,
                                   QWidget *parent = nullptr, const bool &loop = true, const QString &label = "",
                                   const float &division = 1.0f, const float &interval = 1.0f,
                                   const std::vector<QString> &button_params = std::vector<QString>(), const std::vector<QString> &button_labels = std::vector<QString>(),
                                   const int minimum_button_width = 225)
      : FrogPilotParamValueControl(param, title, desc, icon, minValue, maxValue, valueLabels, parent, loop, label, division, interval) {

    button_group = new QButtonGroup(this);
    button_group->setExclusive(false);

    for (int i = 0; i < button_labels.size(); ++i) {
      QPushButton *button = new QPushButton(button_labels[i], this);
      button->setCheckable(true);
      button->setChecked(params.getBool(button_params[i].toStdString()));
      button->setStyleSheet(buttonStyle);
      button->setMinimumWidth(minimum_button_width);
      button_group->addButton(button, i);

      connect(button, &QPushButton::clicked, [this, button_params, i](bool checked) {
        params.putBool(button_params[i].toStdString(), checked);
        emit buttonClicked();
        refresh();
      });

      buttons[button_params[i]] = button;
      hlayout->insertWidget(3, button);
    }
  }

  void refresh() {
    FrogPilotParamValueControl::refresh();

    auto keys = buttons.keys();
    for (const QString &param : keys) {
      QPushButton *button = buttons.value(param);
      button->setChecked(params.getBool(param.toStdString()));
    }
  }

signals:
  void buttonClicked();

private:
  Params params;
  QButtonGroup *button_group;
  QMap<QString, QPushButton*> buttons;
};

class FrogPilotDualParamControl : public QFrame {
  Q_OBJECT

public:
  FrogPilotDualParamControl(FrogPilotParamValueControl *control1, FrogPilotParamValueControl *control2, QWidget *parent = nullptr)
    : QFrame(parent), control1(control1), control2(control2) {
    QHBoxLayout *hlayout = new QHBoxLayout(this);
    hlayout->addWidget(control1);
    hlayout->addWidget(control2);
  }

  void updateControl(float newMinValue, float newMaxValue, const QString &newLabel, float newDivision = 1.0f) {
    control1->updateControl(newMinValue, newMaxValue, newLabel, newDivision);
    control2->updateControl(newMinValue, newMaxValue, newLabel, newDivision);
  }

  void refresh() {
    control1->refresh();
    control2->refresh();
  }

private:
  FrogPilotParamValueControl *control1;
  FrogPilotParamValueControl *control2;
};
