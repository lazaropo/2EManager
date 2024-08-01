#ifndef MANAGERWIDGET_H
#define MANAGERWIDGET_H

#include <QList>
#include <QListWidget>
#include <QVBoxLayout>
#include <QWidget>

#include "../CombatantWidget/combatantwidget.h"
#include "../EffectDialog/EffectDialog.h"
#include "../Model/Controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class ManagerWidget;
using namespace pf2e_manager;
}  // namespace Ui
QT_END_NAMESPACE

class ManagerWidget : public QWidget {
  Q_OBJECT

 public:
  ManagerWidget(QWidget *parent = nullptr);
  ~ManagerWidget();

 private slots:
  void on_pushButton_create_effect_clicked();

  void setCurrent(QMouseEvent *event) {
    Q_UNUSED(event);
    if (_current_widget)
      _current_widget->setStyleSheet(
          "CombatantWidget{ background-color: rgb(0, 0, 0); };");
    _current_widget = static_cast<CombatantWidget *>(sender());
    _current_widget->setStyleSheet(
        "CombatantWidget {\n background-color: red; \n};");
  }

 private:
  Ui::ManagerWidget *ui;
  pf2e_manager::Controller *_controller;

  // QStandardItemModel _combatant_model;
  QList<CombatantWidget *> _combatant_list;
  QVBoxLayout *_combatants_layout;
  QWidget *_box;

  CombatantWidget *_current_widget = nullptr;
};
#endif  // MANAGERWIDGET_H
