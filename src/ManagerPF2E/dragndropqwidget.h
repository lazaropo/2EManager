#ifndef DRAGNDROPQWidget_H
#define DRAGNDROPQWidget_H

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

class DragNDropQWidget : public QWidget {
 public:
  DragNDropQWidget(QWidget* parent = nullptr)
      : QWidget(parent), _combatants_layout(new QVBoxLayout(this)) {}

  DragNDropQWidget(
      pf2e_manager::Controller* controller,
      std::map<pf2e_manager::Combatant*, CombatantWidget*>* widgets_list,
      QWidget* parent = nullptr);

  void setController(pf2e_manager::Controller* controller) {
    _controller = controller;
    _combatants_list = controller->getCombatants();
  }

  void setWidgets(
      std::map<pf2e_manager::Combatant*, CombatantWidget*>* widgets_list) {
    _widgets_collection = widgets_list;
  }

  void setArea(QScrollArea* area) {
    _area = area;
    _area_heigth = _area->height();
  }

  void setModelCurrentComatant(pf2e_manager::Combatant* combatant) {
    if (_model_current_widget) {
      _model_current_widget->_fixe_style = false;
      _model_current_widget->setBaseStyle();
    }
    _model_current_widget = (*_widgets_collection)[combatant];
    _model_current_widget->setModelCurrentStyle();
    _model_current_widget->_fixe_style = true;
  }

  CombatantWidget* getCurrentWidget() { return _current_widget; }
  void updateContent();
  void updateContent(pf2e_manager::SubjectBase* combatant);

  void addWidget(pf2e_manager::Combatant* combatant);

 public slots:
  void mousePressEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
  void dragEnterEvent(QDragEnterEvent* event) override;
  void dragLeaveEvent(QDragLeaveEvent* event) override;
  void dragMoveEvent(QDragMoveEvent* event) override;
  void dropEvent(QDropEvent* event) override;

 private:
  QScrollArea* _area = nullptr;
  pf2e_manager::Controller* _controller;
  std::list<pf2e_manager::Combatant*>* _combatants_list;

  std::map<pf2e_manager::Combatant*, CombatantWidget*>* _widgets_collection;
  QVBoxLayout* _combatants_layout;

  QPoint _mouseStartPosition = QPoint();

  CombatantWidget* _current_widget = nullptr;
  CombatantWidget* _model_current_widget = nullptr;
  int _area_heigth = 0;
};

#endif  // DRAGNDROPQWidget_H
