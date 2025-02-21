#ifndef DRAGNDROPQWidget_H
#define DRAGNDROPQWidget_H

//+++++++++++QT+++++++++++
#include <QDrag>
#include <QMimeData>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QWidget>
#include <QtMinMax>
//+++++++++++STL+++++++++++
#include <map>
//+++++++++++CUSTOM+++++++++++
#include "combatantwidget.h"

class DragNDropQWidget : public QWidget {
  Q_OBJECT
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

  void setArea(QScrollArea* area) { _area = area; }

  void setModelCurrentComatant(pf2e_manager::Combatant* combatant);

  CombatantWidget* getCurrentWidget() { return _current_widget; }
  void updateContent();
  void updateContent(pf2e_manager::SubjectBase* combatant);

  void addWidget(pf2e_manager::Combatant* combatant);

  virtual int heightForWidth(int width) const override;
  virtual QSize sizeHint() const override;

 public slots:
  void mousePressEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
  void dragEnterEvent(QDragEnterEvent* event) override;
  void dragLeaveEvent(QDragLeaveEvent* event) override;
  void dragMoveEvent(QDragMoveEvent* event) override;
  void dropEvent(QDropEvent* event) override;
  void updateContentEvent() { updateContent(); }

 private:
  QScrollArea* _area = nullptr;
  pf2e_manager::Controller* _controller;
  pf2e_manager::utility::t_combatant_container* _combatants_list;

  std::map<pf2e_manager::Combatant*, CombatantWidget*>* _widgets_collection;
  QVBoxLayout* _combatants_layout;

  QPoint _mouseStartPosition = QPoint();

  CombatantWidget* _current_widget = nullptr;
  CombatantWidget* _model_current_widget = nullptr;
  int _current_widget_count = 0;
};

#endif  // DRAGNDROPQWidget_H
