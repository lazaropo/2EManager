#ifndef MANAGERWIDGET_H
#define MANAGERWIDGET_H

// #include <QList>
#include <QListWidget>
#include <QWidget>
#include <list>

#include "../CombatantDialog/combatantdialog.h"
#include "../CombatantWidget/combatantwidget.h"
#include "../EffectDialog/EffectDialog.h"
#include "../Model/Controller.h"
#include "dragndropqwidget.h"
#include "dragndropqwidget_commands.h"

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

  // void setCurrent(QMouseEvent *event);

  void on_pushButton_create_combatant_clicked();

  //   void mousePressEvent(QMouseEvent* event);
  // void mouseMoveEvent(QMouseEvent *event);
  //  void mouseReleaseEvent(QMouseEvent *event);

  //  void dragEnterEvent(QDragEnterEvent *event);
  //  void dragMoveEvent(QDragMoveEvent *event);
  // void dropEvent(QDropEvent *event) override;

  // void on_widget_drag(QMouseEvent *event);

 private:
  Ui::ManagerWidget *ui;
  pf2e_manager::Controller *_controller;

  // QStandardItemModel _combatant_model;
  std::map<pf2e_manager::Combatant *, CombatantWidget *> _combatant_list;

  DragNDropQWidget *_box_combatants;
  DragNDropQWidgetCommands *_box_commands;

  QPoint _mouseStartPosition;  // <------------- possibly dummy var
};
#endif  // MANAGERWIDGET_H
