#include "commandicon.h"

#include "ui_commandicon.h"

CommandIcon::CommandIcon(pf2e_manager::CommandBase *command, QWidget *parent)
    : QWidget(parent), ui(new Ui::CommandIcon), _command(command) {
  ui->setupUi(this);
  QPalette palette(this->palette());
  QImage image(":/path/images/images/sword.jpg");
  palette.setBrush(QPalette::Window, image);
  setPalette(palette);

  // setAutoFillBackground(true);
  //  this->setStyleSheet(
  //        "background-image: url(:/path/images/images/sword.jpg);"
  //        "border: solid 10px rgb(0,0,0);"
  //        "border-radius: 10px;");

  // setToolTip(QString::fromStdString(_command->getName()));
}

CommandIcon::~CommandIcon() { delete ui; }
