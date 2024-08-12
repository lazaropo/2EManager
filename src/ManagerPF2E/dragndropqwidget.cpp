#include "dragndropqwidget.h"

DragNDropQWidget::DragNDropQWidget(
    pf2e_manager::Controller *controller,
    std::map<pf2e_manager::Combatant *, CombatantWidget *> *_widgets_collection,
    QObject *parent)
    : QAbstractListModel(parent),
      _controller(controller),
      _combatants_list(_controller->getCombatants()),
      _widgets_collection(_widgets_collection) /*,
       _combatants_layout(new QVBoxLayout(this))*/
{
  // setLayout(_combatants_layout);
  // _combatants_layout->setSpacing(12);

  for (auto it : *_widgets_collection) {
    // _combatants_layout->addWidget(it.second);

    //    QObject::connect(it.second, &CombatantWidget::mousePressed, this,
    //                     &DragNDropQWidget::mousePressEvent);

    it.second->setAttribute(Qt::WA_StyledBackground);
  }
}

void DragNDropQWidget::addWidget(pf2e_manager::Combatant *combatant) {
  CombatantWidget *obj = new CombatantWidget(combatant);
  obj->_id = ++_id_root;
  _widgets_collection->insert(std::pair(obj->getCombatant(), obj));

  // _combatants_layout->insertWidget(_widgets_collection->size() - 1, obj);
  //  QObject::connect(obj, &CombatantWidget::mousePressed, this,
  //                   &DragNDropQWidget::mousePressEvent);
  obj->setAttribute(Qt::WA_StyledBackground);

  emit layoutChanged();
  //  this->setFixedHeight(height() + _combatants_layout->spacing() +
  //                       obj->height());
}

/** ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * +++++++++++++++++++++++++++++++It works++++++++++++++++++++++++++++++++++++++
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */
// void DragNDropQWidget::mousePressEvent(QMouseEvent *event) {
//   if (event->button() & Qt::LeftButton) {
//     if (_current_widget) _current_widget->setBaseStyle();

//    _current_widget = static_cast<CombatantWidget *>(sender());
//    _current_widget->setHighlightStyle();

//    _mouseStartPosition = QPoint(event->scenePosition().x() - x(),
//                                 event->scenePosition().y() - y());
//  }
//}

// void DragNDropQWidget::mouseMoveEvent(QMouseEvent *event) {
//   Q_UNUSED(event);

//  auto button = QApplication::mouseButtons();
//  setCursor(Qt::ClosedHandCursor);

//  if (button & Qt::LeftButton) {
//    QPoint n_coordinates = QPoint(event->scenePosition().x() - x(),
//                                  event->scenePosition().y() - y());

//    int count = (n_coordinates.y() - _mouseStartPosition.y()) /
//                (_current_widget->height());
//    if (!count) return;

//    auto it = std::find(_combatants_list->begin(), _combatants_list->end(),
//                        _current_widget->getCombatant());
//    auto it_before = it;

//    // auto widget = _widgets_collection->find(&(*it))->second;
//    int layout_size = _combatants_layout->count();
//    int ind = _combatants_layout->indexOf(_current_widget);
//    if (ind == -1) return;

//    if (count < 0 && ind > 0) {
//      _controller->moveCombatant(it, --it_before);
//      _combatants_layout->removeWidget(_current_widget);
//      _combatants_layout->insertWidget(ind - 1, _current_widget);
//      _mouseStartPosition -= QPoint(0, _current_widget->height());
//    } else if (count > 0 && ind < layout_size - 1) {
//      _controller->moveCombatant(it, ++ ++it_before);
//      _combatants_layout->removeWidget(_current_widget);
//      _combatants_layout->insertWidget(ind + 1, _current_widget);
//      _mouseStartPosition += QPoint(0, _current_widget->height());
//    }
//    update();
//    QVBoxLayout *new_layout =
//        qobject_cast<QVBoxLayout *>(_combatants_layout /*this->layout()*/);
//    new_layout->update();
//    this->saveGeometry();
//  }
//}

// void DragNDropQWidget::mouseReleaseEvent(QMouseEvent *event) {
//   Q_UNUSED(event);

//  setCursor(Qt::ArrowCursor);
//}

void DragNDropQWidget::updateContent() {
  // int count = 0;
  for (auto it : *_combatants_list) {
    auto widget = (*_widgets_collection)[it];
    //    _combatants_layout->removeWidget(widget);
    //    _combatants_layout->insertWidget(count++, widget);
    widget->updateContent();
  }
}

void DragNDropQWidget::updateContent(pf2e_manager::SubjectBase *combatant) {
  pf2e_manager::Combatant *body =
      dynamic_cast<pf2e_manager::Combatant *>(combatant);
  if (!body) return;
  auto widget = (*_widgets_collection)[body];
  if (widget) widget->updateContent();
}

QVariant DragNDropQWidget::data(const QModelIndex &index, int role) const {
  CombatantWidget *widget = at(index.row());
  if (widget && widget->getCombatant()) {
    switch (role) {
      case Qt::DisplayRole:
        return QString::fromStdString(widget->getCombatant()->getName());
      case Qt::SizeHintRole:
        return widget->size();
      default:
        return QVariant();
    };
  }
  return QVariant();
}

void DragNDropQWidget::add(pf2e_manager::Combatant *widget) {
  addWidget(widget);
}

CombatantWidget *DragNDropQWidget::at(int index) const {
  pf2e_manager::Combatant *combatant = (*_combatants_list)[index];
  return _widgets_collection->at(combatant);
}
