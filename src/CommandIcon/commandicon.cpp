#include "commandicon.h"

#include "ui_commandicon.h"

CommandIcon::CommandIcon(pf2e_manager::CommandBase *command, QWidget *parent)
    : QWidget(parent), ui(new Ui::CommandIcon), _command(command) {
  ui->setupUi(this);
  QBoxLayout *layout = new QBoxLayout(QBoxLayout::LeftToRight);
  layout->setAlignment(Qt::AlignCenter);
  setLayout(layout);

  setAutoFillBackground(true);

  setAttribute(Qt::WA_StyledBackground);

  setGeometry(QRect(0, 0, 100, 100));
  setFixedSize(100, 100);

  using namespace pf2e_manager;

  if (dynamic_cast<HarmCommand *>(_command)) {
    base_style =
        "QWidget#CommandIcon {"
        "background: url(:/images/harm.png) center;"
        "border-radius: 10px; "
        " }";
    highligth_style =
        "QWidget#CommandIcon {"
        "background: url(:/images/harm_small.png) center;"
        "border: none;"
        "border-radius: 9px; "
        "margin: 7px 3px 3px 3px; "
        "}";
  } else if (dynamic_cast<HealCommand *>(_command)) {
    base_style =
        "QWidget#CommandIcon {"
        "background: url(:/images/heal.png) center;"
        "border-radius: 10px; "
        " }";
    highligth_style =
        "QWidget#CommandIcon {"
        "background: url(:/images/heal_small.png) center;"
        "background-clip: content;"
        "border: none;"
        "border-radius: 9px; "
        "margin-top: 3px; "
        "}";
  } else if (dynamic_cast<MassHarmCommand *>(_command)) {
    base_style =
        "QWidget#CommandIcon {"
        "background: url(:/images/massharm.png) center;"
        "border-radius: 10px; "
        " }";
    highligth_style =
        "QWidget#CommandIcon {"
        "background: url(:/images/massharm_small.png) center;"
        "border: none;"
        "border-radius: 9px; "
        "margin: 7px 3px 3px 3px; "
        "}";
  } else if (dynamic_cast<MassHealCommand *>(_command)) {
    base_style =
        "QWidget#CommandIcon {"
        "background: url(:/images/massheal.png) center;"
        "border-radius: 10px; "
        " }";
    highligth_style =
        "QWidget#CommandIcon {"
        "background: url(:/images/massheal_small.png) center;"
        "background-clip: content;"
        "border: none;"
        "border-radius: 9px; "
        // "border-image: solid 10px red;"
        "margin-top: 3px; "
        "}";
  } else if (dynamic_cast<DecreaseMaxHpCommand *>(_command)) {
    base_style =
        "QWidget#CommandIcon {"
        "background: url(:/images/decreasemaxhpcommand.png) center;"
        "border-radius: 10px; "
        " }";
    highligth_style =
        "QWidget#CommandIcon {"
        "background: url(:/images/decreasemaxhpcommand_small.png) center;"
        "background-clip: content;"
        "border: none;"
        "border-radius: 9px; "
        // "border-image: solid 10px red;"
        "margin-top: 3px; "
        "}";
  }

  setStyleSheet(base_style);
}

CommandIcon::~CommandIcon() {
  // close();
  delete ui;
}
