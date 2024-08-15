#include "dragndropqwidget.h"

DragNDropQWidget::DragNDropQWidget(
    pf2e_manager::Controller *controller,
    std::map<pf2e_manager::Combatant *, CombatantWidget *> *_widgets_collection,
    QWidget *parent)
    : QWidget(parent),
      _controller(controller),
      _combatants_list(_controller->getCombatants()),
      _widgets_collection(_widgets_collection),
      _combatants_layout(new QVBoxLayout(this)) {
  setLayout(_combatants_layout);
  _combatants_layout->setSpacing(7);

  for (auto it : *_widgets_collection) {
    _combatants_layout->addWidget(it.second);
    QObject::connect(it.second, &CombatantWidget::mousePressed, this,
                     &DragNDropQWidget::mousePressEvent);
    //    QObject::connect(it, &CombatantWidget::mouseMoved, this,
    //                     &DragNDropQWidget::mouseMoveEvent);
    // _combatants_layout->addWidget(it.second);
    //    QObject::connect(it, &CombatantWidget::clicked, this,
    //                     &ManagerWidget::on_widget_drag);
    it.second->setAttribute(Qt::WA_StyledBackground);
  }
  // this->setFixedHeight(1000);
}

void DragNDropQWidget::addWidget(pf2e_manager::Combatant *combatant) {
  CombatantWidget *obj = new CombatantWidget(combatant);
  _widgets_collection->insert(std::pair(obj->getCombatant(), obj));

  _combatants_layout->insertWidget(_widgets_collection->size() - 1, obj);
  QObject::connect(obj, &CombatantWidget::mousePressed, this,
                   &DragNDropQWidget::mousePressEvent);
  obj->setAttribute(Qt::WA_StyledBackground);
  this->setFixedHeight(height() + _combatants_layout->spacing() +
                       obj->height());
}

void DragNDropQWidget::mousePressEvent(QMouseEvent *event) {
  if (event->button() & Qt::LeftButton) {
    if (_current_widget) _current_widget->setBaseStyle();

    _current_widget = static_cast<CombatantWidget *>(sender());
    _current_widget->setHighlightStyle();

    _mouseStartPosition = QPoint(event->scenePosition().x() - x(),
                                 event->scenePosition().y() - y());
  }
}

void DragNDropQWidget::mouseMoveEvent(QMouseEvent *event) {
  Q_UNUSED(event);

  auto button = QApplication::mouseButtons();
  setCursor(Qt::ClosedHandCursor);

  if (button & Qt::LeftButton) {
    QPoint n_coordinates = QPoint(event->scenePosition().x() - x(),
                                  event->scenePosition().y() - y());
    int delta = n_coordinates.y() - _mouseStartPosition.y();
    if (delta < 0)
      _area->verticalScrollBar()->setValue(_area->verticalScrollBar()->value() -
                                           2);
    else if (delta > 0)
      _area->verticalScrollBar()->setValue(_area->verticalScrollBar()->value() +
                                           2);

    int count = delta / (_current_widget->height());
    if (!count || !_area) return;

    auto it = std::find(_combatants_list->begin(), _combatants_list->end(),
                        _current_widget->getCombatant());
    auto it_before = it;

    // auto widget = _widgets_collection->find(&(*it))->second;
    int layout_size = _combatants_layout->count();
    int ind = _combatants_layout->indexOf(_current_widget);
    if (ind == -1) return;

    if (count < 0 && ind > 0) {
      _controller->moveCombatant(it, --it_before);
      _combatants_layout->removeWidget(_current_widget);
      _combatants_layout->insertWidget(ind - 1, _current_widget);
      _mouseStartPosition -= QPoint(0, _current_widget->height());
      _area->verticalScrollBar()->setValue(_area->verticalScrollBar()->value() -
                                           100);
      // scroll(0, -1000);
    } else if (count > 0 && ind < layout_size - 1) {
      _controller->moveCombatant(it, ++ ++it_before);
      _combatants_layout->removeWidget(_current_widget);
      _combatants_layout->insertWidget(ind + 1, _current_widget);
      _mouseStartPosition += QPoint(0, _current_widget->height());
      _area->verticalScrollBar()->setValue(_area->verticalScrollBar()->value() +
                                           100);
    }
    update();
    QVBoxLayout *new_layout =
        qobject_cast<QVBoxLayout *>(_combatants_layout /*this->layout()*/);
    new_layout->update();
    this->saveGeometry();

    //    int delta = 0;
    //    if (n_coordinates.y() < 0.5 * _area_heigth && count < 0)
    //      delta = -200;
    //    else if (n_coordinates.y() > 0.5 * _area_heigth && count > 0)
    //      delta = 70;

    //    // _mouseStartPosition = event->position().toPoint();
    //    if (!delta) return;

    //    // QScrollArea *area = qobject_cast<QScrollArea *>(parent());
    //    _area->scroll(0, delta);
    //    QWheelEvent *wheel = new QWheelEvent(
    //        event->position() - QPointF(x(), y()), event->position(),
    //        QPoint(), QPoint(delta, delta), event->buttons(),
    //        event->modifiers(), Qt::ScrollEnd, false);
    //    QApplication::instance()->postEvent(this->parent(), wheel);
  }
}

void DragNDropQWidget::mouseReleaseEvent(QMouseEvent *event) {
  Q_UNUSED(event);

  setCursor(Qt::ArrowCursor);
}

void DragNDropQWidget::updateContent() {
  int count = 0;
  for (auto it : *_combatants_list) {
    auto widget = (*_widgets_collection)[it];
    _combatants_layout->removeWidget(widget);
    _combatants_layout->insertWidget(count++, widget);
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
