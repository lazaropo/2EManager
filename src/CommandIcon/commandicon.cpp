#include "commandicon.h"

#include "ui_commandicon.h"

CommandIcon::CommandIcon(pf2e_manager::CommandBase *command, QWidget *parent)
    : QWidget(parent), ui(new Ui::CommandIcon), _command(command) {
  ui->setupUi(this);
  QBoxLayout *layout = new QBoxLayout(QBoxLayout::LeftToRight);
  layout->setAlignment(Qt::AlignCenter);
  setLayout(layout);
  //  QPalette palette(this->palette());
  //  QImage image(":/images/sword.png");
  //  // image.scaled(size(), Qt::KeepAspectRatio);
  //  palette.setBrush(QPalette::Window, image);
  //  setPalette(palette);

  setAutoFillBackground(true);

  setAttribute(Qt::WA_StyledBackground);

  setGeometry(QRect(0, 0, 100, 100));
  setFixedSize(100, 100);

  using namespace pf2e_manager;

  if (dynamic_cast<HarmCommand *>(_command)) {
    base_style =
        "QWidget#CommandIcon {"
        "background-image: url(:/images/sword.png);"
        "border-radius: 10px; "
        " }";
    highligth_style =
        "QWidget#CommandIcon {"
        "background: url(:/images/sword.png) content center;"
        "background-clip: content;"
        "border: none;"
        "border-radius: 9px; "
        "border-image: solid 10px red;"
        // "outline-radius: 7px;"
        "padding: 7px 7px 7px 7px; "
        "padding-radius: 10px; "
        // "margin: 7px 7px 7px 7px; "
        // "background-size: 90px 90px;"
        "}";
  }

  setStyleSheet(base_style);

  // setAttribute(Qt::WA_OpaquePaintEvent);
  //  this->setStyleSheet(
  //        "background-image: url(:/path/images/images/sword.jpg);"
  //        "border: solid 10px rgb(0,0,0);"
  //        "border-radius: 10px;");

  // setToolTip(QString::fromStdString(_command->getName()));
}

CommandIcon::~CommandIcon() { delete ui; }

// void CommandIcon::paintEvent(QPaintEvent *event) {
//   Q_UNUSED(event);
//   QPainter painter(this);
//   painter.drawImage(0, 0, QImage(":/images/sword.png"));
// }
