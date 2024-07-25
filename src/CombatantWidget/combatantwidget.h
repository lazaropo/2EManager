#ifndef COMBATANTWIDGET_H
#define COMBATANTWIDGET_H

#include <QWidget>

#include "../Model/Controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class CombatantWidget;
using namespace pf2e_manager;
}  // namespace Ui
QT_END_NAMESPACE

class CombatantWidget : public QWidget {
  Q_OBJECT

 public:
  CombatantWidget(QWidget *parent = nullptr);
  ~CombatantWidget();

 private:
  Ui::CombatantWidget *ui;
  pf2e_manager::Controller *_controller;
  pf2e_manager::SimpleEffectBuilder *_builder;
  pf2e_manager::EffectDirector *_director;
};
#endif  // COMBATANTWIDGET_H
