#ifndef MANAGERWIDGET_H
#define MANAGERWIDGET_H

#include <QList>
#include <QListWidget>
#include <QWidget>

#include "../CombatantWidget/combatantwidget.h"
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

 private:
  Ui::ManagerWidget *ui;
  pf2e_manager::Controller *_controller;

  QStandardItemModel _combatant_model;
};
#endif  // MANAGERWIDGET_H
