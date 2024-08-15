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
  _combatants_layout->setSpacing(12);

  for (auto it : *_widgets_collection) {
    _combatants_layout->addWidget(it.second);
    QObject::connect(it.second, &CombatantWidget::mousePressed, this,
                     &DragNDropQWidget::mousePressEvent);
    QObject::connect(it.second, &CombatantWidget::mouseMoved, this,
                     &DragNDropQWidget::mouseMoveEvent);
    QObject::connect(it.second, &CombatantWidget::dragMoved, this,
                     &DragNDropQWidget::dragMoveEvent);
    QObject::connect(it.second, &CombatantWidget::dragEntered, this,
                     &DragNDropQWidget::dragEnterEvent);
    QObject::connect(it.second, &CombatantWidget::dragLeaved, this,
                     &DragNDropQWidget::dragLeaveEvent);
    QObject::connect(it.second, &CombatantWidget::droped, this,
                     &DragNDropQWidget::dropEvent);
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
  QObject::connect(obj, &CombatantWidget::mouseMoved, this,
                   &DragNDropQWidget::mouseMoveEvent);
  QObject::connect(obj, &CombatantWidget::dragMoved, this,
                   &DragNDropQWidget::dragMoveEvent);
  QObject::connect(obj, &CombatantWidget::dragEntered, this,
                   &DragNDropQWidget::dragEnterEvent);
  QObject::connect(obj, &CombatantWidget::dragLeaved, this,
                   &DragNDropQWidget::dragLeaveEvent);
  QObject::connect(obj, &CombatantWidget::droped, this,
                   &DragNDropQWidget::dropEvent);
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
  //  setCursor(Qt::ClosedHandCursor);

  if (button & Qt::LeftButton) {
    auto _sender = sender();
    CombatantWidget *widget = qobject_cast<CombatantWidget *>(_sender);
    if (!widget) return;
    QDrag *drag = new QDrag(widget);
    drag->setMimeData(new QMimeData());

    if (!_drag_started && _current_widget) {
      _combatants_layout->removeWidget(_current_widget);
      _current_widget->hide();
      _drag_started = true;
    }

    drag->exec(Qt::CopyAction | Qt::MoveAction);
  }
}

void DragNDropQWidget::mouseReleaseEvent(QMouseEvent *event) {
  Q_UNUSED(event);

  setCursor(Qt::ArrowCursor);
}

void DragNDropQWidget::dragEnterEvent(QDragEnterEvent *event) {
  event->accept();
}
void DragNDropQWidget::dragLeaveEvent(QDragLeaveEvent *event) {
  event->accept();
}

void DragNDropQWidget::dragMoveEvent(QDragMoveEvent *event) {
  Q_UNUSED(event);
  //  int delta = 0;
  //  if (event->position().y() < 0.3 * this->height() &&
  //      _mouseStartPosition.y() - event->position().y() > 0)
  //    delta = -120;
  //  else if (event->position().y() > 0.7 * this->height() &&
  //           _mouseStartPosition.y() - event->position().y() < 0)
  //    delta = 120;

  //  _mouseStartPosition = event->position().toPoint();
  //  if (!delta) return;

  //  QWheelEvent *wheel = new QWheelEvent(
  //      event->position(), event->position(), QPoint(), QPoint(0, delta),
  //      event->buttons(), event->modifiers(), Qt::ScrollEnd, false);
  //  QApplication::instance()->postEvent(this, wheel);
}

void DragNDropQWidget::dropEvent(QDropEvent *event) {
  //  QPoint n_coordinates =
  //      QPoint(event->position().x() - x(), event->position().y() - y());

  //  int count = (n_coordinates.y() - _mouseStartPosition.y()) /
  //              (_current_widget->height());
  //  if (!count) return;

  auto widget = qobject_cast<CombatantWidget *>(sender());

  if (widget && widget == _current_widget) return;

  auto it = std::find(_combatants_list->begin(), _combatants_list->end(),
                      _current_widget->getCombatant());
  auto it_before = std::find(_combatants_list->begin(), _combatants_list->end(),
                             widget->getCombatant());

  int ind = _combatants_layout->indexOf(widget);
  // int ind = _combatants_layout->indexOf(*it_before);
  if (ind == -1) return;

  if (it != it_before) {
    _controller->moveCombatant(it, it_before);
    _combatants_layout->removeWidget(_current_widget);
    _combatants_layout->insertWidget(ind, _current_widget);
    _current_widget->show();
    //  _mouseStartPosition -= QPoint(0, _current_widget->height());
  }
  // else if (count > 0 && ind < layout_size - 1) {
  //    _controller->moveCombatant(it, ++ ++it_before);
  //    _combatants_layout->removeWidget(_current_widget);
  //    _combatants_layout->insertWidget(ind + 1, _current_widget);
  //    _mouseStartPosition += QPoint(0, _current_widget->height());
  //  }
  update();
  QVBoxLayout *new_layout = qobject_cast<QVBoxLayout *>(_combatants_layout
                                                        /*this->layout()*/);
  new_layout->update();
  this->saveGeometry();
  _drag_started = false;
  event->accept();
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
