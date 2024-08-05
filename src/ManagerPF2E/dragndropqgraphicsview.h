#ifndef DRAGNDROPQGRAPHICSVIEW_H
#define DRAGNDROPQGRAPHICSVIEW_H

//+++++++++++QT+++++++++++
#include <QDrag>
#include <QMimeData>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QWidget>
//+++++++++++STL+++++++++++
#include <map>
//+++++++++++CUSTOM+++++++++++
#include "../CombatantWidget/combatantwidget.h"

class DragNDropQGraphicsView : public QGraphicsView {
 public:
  DragNDropQGraphicsView(QWidget* parent = nullptr)
      : QGraphicsView(parent), _combatants_layout(new QVBoxLayout(this)) {}

  DragNDropQGraphicsView(
      pf2e_manager::Controller* controller,
      std::map<pf2e_manager::Combatant*, CombatantWidget*>* widgets_list,
      QGraphicsView* parent = nullptr);

  void setController(pf2e_manager::Controller* controller) {
    _controller = controller;
    _combatants_list = &controller->getCombatants();
  }

  void setWidgets(
      std::map<pf2e_manager::Combatant*, CombatantWidget*>* widgets_list) {
    _widgets_list = widgets_list;
  }

  CombatantWidget* getCurrentWidget() { return _current_widget; }
  void updateContent();

  void addWidget(pf2e_manager::Combatant* combatant);

 public slots:
  void mousePressEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
  //    void dragEnterEvent(QDragEnterEvent* event);
  //    void dragLeaveEvent(QDragLeaveEvent* event);
  // void dropEvent(QDropEvent* event);

 private:
  pf2e_manager::Controller* _controller;
  std::list<pf2e_manager::Combatant>* _combatants_list;

  std::map<pf2e_manager::Combatant*, CombatantWidget*>* _widgets_list;
  QVBoxLayout* _combatants_layout;

  QPoint _mouseStartPosition = QPoint();

  CombatantWidget* _current_widget = nullptr;
  CombatantWidget* _sender_widget = nullptr;

  bool _pressed = false;
  bool _long_press = false;
};

#endif  // DRAGNDROPQGRAPHICSVIEW_H
