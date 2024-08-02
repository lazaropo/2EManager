#ifndef MANAGERWIDGET_H
#define MANAGERWIDGET_H

#include <QList>
#include <QListWidget>
#include <QVBoxLayout>
#include <QWidget>

#include "../CombatantDialog/combatantdialog.h"
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

  void setCurrent(QMouseEvent *event);

  void on_pushButton_create_combatant_clicked();

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
