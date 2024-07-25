#ifndef COMBATANTWIDGET_H
#define COMBATANTWIDGET_H

#include <QListWidget>
#include <QToolTip>
#include <QWidget>

// #include "EffectListWidgetItem.h"
#include "../Model/Controller.h"
#include "MyMenuWidget.h"

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

  void addTextBrowser(QTextBrowser *text) { ui->layout_effect->addItem(text); }

 private:
  Ui::CombatantWidget *ui;
  pf2e_manager::Controller *_controller;
  pf2e_manager::SimpleEffectBuilder *_builder;
  pf2e_manager::EffectDirector *_director;
};
#endif  // COMBATANTWIDGET_H
