#ifndef COMMANDICON_H
#define COMMANDICON_H

#include <QIcon>
#include <QWidget>

#include "../Model/Controller.h"

class CommandIcon : public QWidget {
  Q_OBJECT
 public:
  CommandIcon(pf2e_manager::CommandBase* command, QWidget* parent = nullptr);

  pf2e_manager::CommandBase* getCommand() { return _command; }

 signals:
  void mousePressed(QMouseEvent* event = nullptr);

 protected slots:
  void mousePressEvent(QMouseEvent* event = nullptr) override {
    emit mousePressed(event);
  }

 private:
  pf2e_manager::CommandBase* _command;
};

#endif  // COMMANDICON_H
