#ifndef COMMANDICON_H
#define COMMANDICON_H

#include <QBrush>
#include <QHBoxLayout>
#include <QImage>
#include <QLabel>
#include <QPainter>
#include <QPalette>
#include <QPixmap>
#include <QWidget>

#include "../Model/Controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class CommandIcon;
}
QT_END_NAMESPACE

class CommandIcon : public QWidget {
  Q_OBJECT

 public:
  CommandIcon(pf2e_manager::CommandBase* command, QWidget* parent = nullptr);
  ~CommandIcon();

  pf2e_manager::CommandBase* getCommand() { return _command; }

  void setBaseStyle() {
    setFixedSize(100, 100);
    setStyleSheet(base_style);
  }
  void setHighligthStyle() {
    setFixedSize(0.85 * width(), 0.85 * height());
    setStyleSheet(highligth_style);
  }

 signals:
  void mousePressed(QMouseEvent* event = nullptr);

 protected slots:
  void mousePressEvent(QMouseEvent* event = nullptr) override {
    emit mousePressed(event);
  }

  // void paintEvent(QPaintEvent* event) override;

 private:
  Ui::CommandIcon* ui;
  pf2e_manager::CommandBase* _command;
  QString base_style;
  QString highligth_style;
};
#endif  // COMMANDICON_H
