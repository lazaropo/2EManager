#ifndef COMMANDICON_H
#define COMMANDICON_H

#include <QBrush>
#include <QImage>
#include <QPalette>
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

 signals:
  void mousePressed(QMouseEvent* event = nullptr);

 protected slots:
  void mousePressEvent(QMouseEvent* event = nullptr) override {
    emit mousePressed(event);
  }

 private:
  Ui::CommandIcon* ui;
  pf2e_manager::CommandBase* _command;
};
#endif  // COMMANDICON_H
