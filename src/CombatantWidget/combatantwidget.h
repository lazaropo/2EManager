#ifndef COMBATANTWIDGET_H
#define COMBATANTWIDGET_H

#include <QListWidget>
#include <QToolTip>
#include <QWidget>
#include <QtWidgets>

// #include "EffectListWidgetItem.h"
#include "../CombatantWidget/MyMenuWidget.h"
#include "../Model/Controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class CombatantWidget;
// class MyMenuWidget;
using namespace pf2e_manager;
}  // namespace Ui
QT_END_NAMESPACE

class CombatantWidget : public QWidget {
  Q_OBJECT

 public:
  CombatantWidget(pf2e_manager::Combatant *_combatant,
                  QWidget *parent = nullptr);
  ~CombatantWidget();

  pf2e_manager::Combatant *getCombatant() { return _combatant; }

  void updateContent();

 protected slots:
  void mousePressEvent(QMouseEvent *event = nullptr) {
    emit mousePressed(event);
  }

 signals:
  void mousePressed(QMouseEvent *event = nullptr);

 private:
  Ui::CombatantWidget *ui;
  pf2e_manager::Combatant *_combatant;
};
#endif  // COMBATANTWIDGET_H
