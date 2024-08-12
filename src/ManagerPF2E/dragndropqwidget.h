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

class DragNDropQWidget : public QAbstractListModel {
 public:
  DragNDropQWidget(QObject* parent = nullptr)
      : QAbstractListModel(parent) /*,
         _combatants_layout(new QVBoxLayout(this)) */
  {}

  DragNDropQWidget(
      pf2e_manager::Controller* controller,
      std::map<pf2e_manager::Combatant*, CombatantWidget*>* widgets_list,
      QObject* parent = nullptr);

  void setController(pf2e_manager::Controller* controller) {
    _controller = controller;
    _combatants_list = controller->getCombatants();
  }

  void setWidgets(
      std::map<pf2e_manager::Combatant*, CombatantWidget*>* widgets_list) {
    _widgets_collection = widgets_list;
  }

  CombatantWidget* getCurrentWidget() { return _current_widget; }
  void updateContent();
  void updateContent(pf2e_manager::SubjectBase* combatant);

  void addWidget(pf2e_manager::Combatant* combatant);

 public:
  int rowCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    if (_combatants_list)
      return _combatants_list->size();
    else
      return 0;
  }

  int columnCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return 1;
  }

  QVariant data(const QModelIndex& index, int role) const;

  void add(pf2e_manager::Combatant* widget);

  CombatantWidget* at(int index) const;

 public slots:
  //  void mousePressEvent(QMouseEvent* event);
  //  void mouseMoveEvent(QMouseEvent* event);
  //  void mouseReleaseEvent(QMouseEvent* event);

  //    void dragEnterEvent(QDragEnterEvent* event);
  //    void dragLeaveEvent(QDragLeaveEvent* event);
  // void dropEvent(QDropEvent* event);

 private:
  pf2e_manager::Controller* _controller;
  std::vector<pf2e_manager::Combatant*>* _combatants_list;

  int _id_root = 0;

  std::map<pf2e_manager::Combatant*, CombatantWidget*>* _widgets_collection;
  // QVBoxLayout* _combatants_layout;

  QPoint _mouseStartPosition = QPoint();

  CombatantWidget* _current_widget = nullptr;
};

#endif  // DRAGNDROPQWidget_H
