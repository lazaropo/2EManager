#include "dragndropqgraphicsview.h"

DragNDropQGraphicsView::DragNDropQGraphicsView(
    pf2e_manager::Controller *controller,
    std::map<pf2e_manager::Combatant *, CombatantWidget *> *_widgets_list,
    QGraphicsView *parent)
    : QGraphicsView(parent),
      _controller(controller),
      _combatants_list(&_controller->getCombatants()),
      _widgets_list(_widgets_list),
      _combatants_layout(new QVBoxLayout(this)) {
  setLayout(_combatants_layout);

  // auto combatants_layout = layout();
  for (auto it : *_widgets_list) {
    _combatants_layout->addWidget(it.second);
    QObject::connect(it.second, &CombatantWidget::mousePressed, this,
                     &DragNDropQGraphicsView::mousePressEvent);
    //    QObject::connect(it, &CombatantWidget::mouseMoved, this,
    //                     &DragNDropQWidget::mouseMoveEvent);
    _combatants_layout->addWidget(it.second);
    //    QObject::connect(it, &CombatantWidget::clicked, this,
    //                     &ManagerWidget::on_widget_drag);
    it.second->setAttribute(Qt::WA_StyledBackground);
    setFocusPolicy(Qt::NoFocus);
  }
  // setMouseTracking(true);
}

void DragNDropQGraphicsView::addWidget(pf2e_manager::Combatant *combatant) {
  CombatantWidget *obj = new CombatantWidget(combatant);
  _widgets_list->insert(std::pair(obj->getCombatant(), obj));

  _combatants_layout->insertWidget(_widgets_list->size() - 1, obj);
  QObject::connect(obj, &CombatantWidget::mousePressed, this,
                   &DragNDropQGraphicsView::mousePressEvent);
  obj->setAttribute(Qt::WA_StyledBackground);
}

// void DragNDropQWidget::updateContent() {
//   int count = 0;
//   for (auto combatant : *_combatants_list) {
//     auto to = _widgets_list->find(&combatant)->second;
//     std::cout << combatant.getName() << std::end;
//     // int ind = _combatants_layout->indexOf(count++);
////    if(ind == -1)
////        continue;
////    auto item = _combatants_layout->takeAt(count++);
////    if(!item)
////        continue;
////    auto from = item->widget();
//    _combatants_layout->insertWidget(count++, to);
//  }
//}

void DragNDropQGraphicsView::mousePressEvent(QMouseEvent *event) {
  if (event->button() & Qt::LeftButton /*&& (event->button() & Qt::TouchPointPressed) &&
        (event->button() & Qt::TouchPointReleased)*/) {
    if (_current_widget)
      _current_widget->setStyleSheet(
          "CombatantWidget{ background-color:  rgb(0,0,0);  };");

    _current_widget = static_cast<CombatantWidget *>(sender());
    _current_widget->setStyleSheet(
        "CombatantWidget{ background-color:  red;  };");

    _mouseStartPosition = QPoint(event->scenePosition().x() - x(),
                                 event->scenePosition().y() - y());
    _pressed = true;
    _long_press = false;
  } /*else {
    _pressed = false;
    _long_press = false;
  }*/
}

// void DragNDropQWidget::dropEvent(QDropEvent *event) {
//   const QMimeData *mime = event->mimeData();

//  if (!mime->hasFormat("application/x-widget-order")) {
//    return;
//  }

//  int index = mime->data("application/x-widget-order").toInt();

//  CombatantWidget *widget = static_cast<CombatantWidget *>(event->source());

//  int new_ind = _combatants_layout->indexOf(widget);

//  if (new_ind > index)
//    _combatants_layout->insertWidget(index, widget);
//  else
//    _combatants_layout->insertWidget(new_ind, widget);

//  update();

//  //  Q_UNUSED(event);
//  //  // if (ui->scrollArea->geometry().contains(event->position().toPoint()))
//  {
//  //    CombatantWidget *_drop_widget = static_cast<CombatantWidget
//  //    *>(sender()); if (!_current_widget || !_drop_widget) return; auto
//  //    _combatants = _controller->getCombatants();
//  //    _controller->moveCombatant(std::find(_combatants.begin(),
//  //    _combatants.end(),
//  // *_current_widget->getCombatant()),
//  //                               std::find(_combatants.begin(),
//  //                               _combatants.end(),
//  //                                         *_drop_widget->getCombatant()));
//  //    _current_widget->show();
//  //    _current_widget = nullptr;
//  // }
//}

void DragNDropQGraphicsView::mouseMoveEvent(QMouseEvent *event) {
  Q_UNUSED(event);
  // if (event->button() == Qt::AllButtons) {
  /*&&
    ((event->pos() - _mouseStartPosition).manhattanLength() >=
     QApplication::startDragDistance()*/ /*&& (event->button() & Qt::TouchPointPressed) &&
               !(event->button() & Qt::TouchPointReleased) )*/ // {
  // _sender_widget = static_cast<CombatantWidget*>(event->sender());
  auto button = QApplication::mouseButtons();
  setCursor(Qt::ClosedHandCursor);
  //  if (button & Qt::LeftButton && _pressed) {
  //    _long_press = true;
  //  }
  if (button & Qt::LeftButton /*&& _pressed &&
      _long_press */
      /*&& _mouseStartPosition !=  event->pos()*/) {
    QPoint n_coordinates = QPoint(event->scenePosition().x() - x(),
                                  event->scenePosition().y() - y());

    int count = (n_coordinates.y() - _mouseStartPosition.y()) /
                (_current_widget->height());
    if (!count) {
      _pressed = false;
      return;
    }

    auto it = std::find(_combatants_list->begin(), _combatants_list->end(),
                        *_current_widget->getCombatant());
    auto it_before = it;

    auto widget = _widgets_list->find(&(*it))->second;
    int ind = layout()->indexOf(widget);

    if (count < 0) {
      _controller->moveCombatant(it, --it_before);
      _combatants_layout->insertWidget(ind + 1, widget);
    } else if (count > 0) {
      _controller->moveCombatant(it, ++ ++it_before);
      _combatants_layout->insertWidget(ind + 2, widget);
    }

    // updateContent();

    update();

    //    int index = _combatants_layout->indexOf(_current_widget);
    //    // CombatantWidget *widget = static_cast<CombatantWidget
    //    // *>(event->source());

    //    // int new_ind = _combatants_layout->indexOf(widget);

    //    if (count > 0 && index - count >= 0)
    //      _combatants_layout->insertWidget(index - count, _current_widget);
    //    else if (count < 0 && index - count < _combatants_layout->count())
    //      _combatants_layout->insertWidget(index + count, _current_widget);
  }

  //    _mouseStartPosition = event->pos();
  //    QDrag *new_drag = new QDrag(this);
  //    QMimeData *mime_data = new QMimeData();

  //    mime_data->setData("application/x-widget-order", "data");

  //    new_drag->setMimeData(mime_data);

  //    Qt::DropAction action = new_drag->exec(Qt::MoveAction);
  //    Q_UNUSED(action);
}

void DragNDropQGraphicsView::mouseReleaseEvent(QMouseEvent *event) {
  Q_UNUSED(event);
  //  if (event->button() & Qt::LeftButton && _pressed &&
  //      _long_press /*&& _mouseStartPosition !=  event->pos()*/) {
  //    int count = -(_mouseStartPosition.y() - event->pos().y()) /
  //                (_current_widget->height());
  //    if (!count) {
  //      _pressed = false;
  //      return;
  //    }

  //    int index = _combatants_layout->indexOf(_current_widget);
  //    // CombatantWidget *widget = static_cast<CombatantWidget
  //    // *>(event->source());

  //    // int new_ind = _combatants_layout->indexOf(widget);

  //    if (count > 0 && index - count >= 0)
  //      _combatants_layout->insertWidget(index - count, _current_widget);
  //    else if (count < 0 && index - count < _combatants_layout->count())
  //      _combatants_layout->insertWidget(index - count, _current_widget);

  //    update();
  //  }
  _pressed = false;
  _long_press = false;

  setCursor(Qt::ArrowCursor);
}

// void DragNDropQGraphicsView::dragEnterEvent(QDragEnterEvent* event) {

//}

// void DragNDropQGraphicsView::dragLeaveEvent(QDragLeaveEvent* event);
// void DragNDropQGraphicsView::dropEvent(QDropEvent* event);
