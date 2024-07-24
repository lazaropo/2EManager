#ifndef COMBATANTWIDGET_H
#define COMBATANTWIDGET_H

#include <QWidget>

#include "../Model/Controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class CombatantWidget;
}
QT_END_NAMESPACE

class CombatantWidget : public QWidget {
  Q_OBJECT

 public:
  CombatantWidget(QWidget *parent = nullptr);
  ~CombatantWidget();

 private:
  Ui::CombatantWidget *ui;
  Controller *_controller;
};
#endif  // COMBATANTWIDGET_H
