#include "dragndropqwidget.h"

DragNDropQWidget::DragNDropQWidget(
    pf2e_manager::Controller *controller,
    std::map<pf2e_manager::Combatant *, CombatantWidget *> *widgets_collection,
    QWidget *parent)
    : QWidget(parent),
      _controller(controller),
      _combatants_list(_controller->getCombatants()),
      _widgets_collection(widgets_collection),
      _combatants_layout(new QVBoxLayout(this))

{
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
    it.second->setAttribute(Qt::WA_StyledBackground);
  }
  setAcceptDrops(true);

  setAttribute(Qt::WA_StyledBackground);
  // setAutoFillBackground(true);
  // This widget should be filled by color with code, not with qt designer
  // setStyleSheet(" {"
  //               "background-color: rgb(216,191,216);"
  //               "border-radius: 6px;"
  //               "}");
  auto palette = QPalette(QColor(212, 163, 115));
  setPalette(palette);
  if (_area) _area->setPalette(palette);

  QSizePolicy policy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
  // policy.setHeightForWidth(true);
  setSizePolicy(policy);

  // setMinimumSize(1150, 530);
}

void DragNDropQWidget::addWidget(pf2e_manager::Combatant *combatant) {
  CombatantWidget *obj = new CombatantWidget(_controller, combatant);
  _widgets_collection->insert(std::pair(obj->getCombatant(), obj));

  _combatants_layout->addWidget(/*_widgets_collection->size() - 1,*/ obj);
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
  // obj->setAttribute(Qt::WA_StyledBackground);
  // if (_combatants_layout->count() == 1)
  //     // setFixedHeight(obj->height() + _combatants_layout->spacing());
  //      _area->setMinimumHeight(obj->height() +
  //      _combatants_layout->spacing());
  // else
  //     // setFixedHeight(_combatants_layout->count() * (obj->height() +
  //     _combatants_layout->spacing())
  //     //                - _combatants_layout->spacing());
  //     _area->setMinimumHeight(_combatants_layout->count() * (obj->height() +
  //     _combatants_layout->spacing())
  //                    - _combatants_layout->spacing());
  // setSizePolicy(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
}

int DragNDropQWidget::heightForWidth(int width) const {
  int _heigth = 1150;  // minimumHeight();
  int _width = 530;    //  minimumWidth();
  return _heigth / _width * qMax(width, 1);
}

QSize DragNDropQWidget::sizeHint() const {
  // int _heigth = 1150;//minimumHeight();
  int _width = 530;  //  minimumWidth();
  return QSize(_width, heightForWidth(_width));
}

void DragNDropQWidget::mousePressEvent(QMouseEvent *event) {
  if (event->button() & Qt::LeftButton) {
    if (_current_widget) _current_widget->setBaseStyle();

    _current_widget = static_cast<CombatantWidget *>(sender());
    _current_widget_count = _combatants_layout->indexOf(_current_widget);
    if (_current_widget) {
      _current_widget->setHighlightStyle();

      _mouseStartPosition =
          QPoint(event->position().x(), event->position().y());
    } else
      _current_widget = nullptr;
  }
}

void DragNDropQWidget::mouseMoveEvent(QMouseEvent *event) {
  auto button = event->buttons();
  if (button & Qt::LeftButton) {
    auto _sender = sender();
    CombatantWidget *widget = qobject_cast<CombatantWidget *>(_sender);
    if (!widget) return;
    QDrag *drag = new QDrag(widget);
    drag->setMimeData(new QMimeData());

    drag->exec(Qt::CopyAction | Qt::MoveAction);
  }
}

void DragNDropQWidget::mouseReleaseEvent(QMouseEvent *event) {
  if (event->buttons() & Qt::LeftButton && _current_widget) {
    dropEvent(nullptr);

    if (_current_widget) {
      _combatants_layout->insertWidget(_current_widget_count, _current_widget);
      _current_widget->setBaseStyle();
      // _current_widget->show();
    }
  }
}

void DragNDropQWidget::setModelCurrentComatant(
    pf2e_manager::Combatant *combatant) {
  if (_model_current_widget) {
    _model_current_widget->_fixe_style = false;
    _model_current_widget->setBaseStyle();
  }
  _model_current_widget = (*_widgets_collection)[combatant];
  if (_model_current_widget) {
    _model_current_widget->setModelCurrentStyle();
    _model_current_widget->_fixe_style = true;
  }
}

void DragNDropQWidget::updateContent() {
  int count = 0;
  CombatantWidget *widget = nullptr;
  for (auto it : *_combatants_list) {
    widget = (*_widgets_collection)[it];
    _combatants_layout->removeWidget(widget);
    _combatants_layout->insertWidget(count++, widget);
    widget->updateContent();
  }
  // if (count == 1)
  //     _area->setFixedHeight((widget->height() +
  //     _combatants_layout->spacing()));

  // if (count > 3 && widget)
  //     _area->setFixedHeight(_combatants_layout->count()
  //                              * (widget->height() +
  //                              _combatants_layout->spacing())
  //                          - _combatants_layout->spacing());
}

void DragNDropQWidget::updateContent(pf2e_manager::SubjectBase *combatant) {
  pf2e_manager::Combatant *body =
      dynamic_cast<pf2e_manager::Combatant *>(combatant);
  if (!body) return;
  auto widget = (*_widgets_collection)[body];
  if (widget) widget->updateContent();
}

void DragNDropQWidget::dragEnterEvent(QDragEnterEvent *event) {
  event->accept();
}
void DragNDropQWidget::dragLeaveEvent(QDragLeaveEvent *event) {
  event->accept();
}

void DragNDropQWidget::dragMoveEvent(QDragMoveEvent *event) {
  if (event->buttons() & Qt::LeftButton) {
    QPoint n_coordinates = QPoint(event->position().x(), event->position().y());
    int delta = n_coordinates.y() - _mouseStartPosition.y();
    int parent_height = parentWidget()->height();
    if (delta < 0)
      _area->verticalScrollBar()->setValue(_area->verticalScrollBar()->value() -
                                           qMax(2000 / parent_height, 2));
    else if (delta > 0)
      _area->verticalScrollBar()->setValue(_area->verticalScrollBar()->value() +
                                           qMax(2000 / parent_height, 2));
    _mouseStartPosition = event->position().toPoint();
  }

  event->accept();
}

void DragNDropQWidget::dropEvent(QDropEvent *event) {
  // auto button = event->buttons();
  if (event /*&& button & Qt::LeftButton*/) {
    auto widget = qobject_cast<CombatantWidget *>(sender());

    if (!_current_widget)
      return;
    else if (!widget) {
      _combatants_layout->insertWidget(_current_widget_count, _current_widget);
      _current_widget->setBaseStyle();
      // _current_widget->show();
      _current_widget = nullptr;
    }

    auto it = std::find(_combatants_list->begin(), _combatants_list->end(),
                        _current_widget->getCombatant());
    auto it_before = std::find(_combatants_list->begin(),
                               _combatants_list->end(), widget->getCombatant());

    int ind = _combatants_layout->indexOf(widget);
    if (ind > _combatants_layout->indexOf(_current_widget)) --ind;

    if (ind == -1) return;

    if (it != it_before) {
      _controller->moveCombatant(it, it_before);
      _combatants_layout->removeWidget(_current_widget);
      _combatants_layout->insertWidget(ind, _current_widget);
      _current_widget->setBaseStyle();
      // _current_widget->show();
      _current_widget = nullptr;
    }

    setModelCurrentComatant(_controller->getCurrent());

    //    update();
    //    QVBoxLayout *new_layout = qobject_cast<QVBoxLayout
    //    *>(_combatants_layout);
    //        new_layout->update();
    this->saveGeometry();

    /*if (event)*/ event->accept();
  }
}
// void DragNDropQWidget::resizeEvent(QResizeEvent* event) {
//     //if(hasHeightForWidth()){
//         // setFixedHeight(heightForWidth(event->()));
//         // setFixedSize(event->size());
//     QSize area_size = _area->size();

//     QRect widget_rect = geometry();

//     double width_coeff = static_cast<double>(event->size().width()) /
//     qMax(event->oldSize().width(), 1); int height_coeff =
//     static_cast<double>(event->size().height()) /
//     qMax(event->oldSize().height(), 1); if(width_coeff > 1.03 || width_coeff
//     < 0.97 || height_coeff > 1.03 || height_coeff < 0.97){ int width =
//     width_coeff * widget_rect.width(); int height = height_coeff *
//     widget_rect.height();

//     QRect new_rect(widget_rect.x(), widget_rect.y(), width, height);

//     QWidget* parent = static_cast<QWidget*>(this);

//     if(parent == nullptr)
//         throw std::runtime_error("DragNDropQWidget::resizeEvent(): parent is
//         null.");

//     QRect parent_size = parent->geometry();

//     if(parent_size.width() > new_rect.width())
//         new_rect.setWidth(parent_size.width() - parent_size.x());
//     if(parent_size.height() > new_rect.height())
//         new_rect.setHeight(parent_size.height() - parent_size.y());

//     _area->setFixedSize(new_rect.size());
//     //_combatants_layout->resize(event->size());
//     update();
//         // updateGeometry();
//     //}
//           // QWidget::resizeEvent(event);
//     }
// }
// }
