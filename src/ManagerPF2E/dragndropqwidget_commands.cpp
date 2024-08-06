#include "dragndropqwidget_commands.h"

DragNDropQWidgetCommands::DragNDropQWidgetCommands(
    pf2e_manager::Controller *controller, QWidget *parent)
    : QWidget(parent),
      _controller(controller),
      _commands_list(&_controller->getCommands()),
      _commands_layout(new QHBoxLayout(this)) {
  setLayout(_commands_layout);
  _commands_layout->setSpacing(12);

  for (auto it : _widgets_collection) {
    _commands_layout->addWidget(it);
    QObject::connect(it, &CommandIcon::mousePressed, this,
                     &DragNDropQWidgetCommands::mousePressEvent);
    _commands_layout->addWidget(it);

    it->setAttribute(Qt::WA_StyledBackground);
    setFocusPolicy(Qt::NoFocus);
  }
}

void DragNDropQWidgetCommands::addCommand(pf2e_manager::CommandBase *command) {
  CommandIcon *obj = new CommandIcon(command);
  _widgets_collection.push_back(obj);

  _commands_layout->insertWidget(_widgets_collection.size() - 1, obj);
  QObject::connect(obj, &CommandIcon::mousePressed, this,
                   &DragNDropQWidgetCommands::mousePressEvent);
  obj->setAttribute(Qt::WA_StyledBackground);
}

void DragNDropQWidgetCommands::mousePressEvent(QMouseEvent *event) {
  if (event->button() & Qt::LeftButton) {
    if (_current_icon)
      _current_icon->setStyleSheet(
          "CommandIcon{ border-width:  10px;\n"
          "border-radius: 10px;  };");

    _current_icon = static_cast<CommandIcon *>(sender());
    _current_icon->setStyleSheet(
        "CommandIcon{ border-color:  red;\n"
        "  border-width: 0px;\n"
        "border-radius: 10px; };");

    _mouseStartPosition = QPoint(event->scenePosition().x() - x(),
                                 event->scenePosition().y() - y());
  }
}

void DragNDropQWidgetCommands::mouseMoveEvent(QMouseEvent *event) {
  Q_UNUSED(event);

  auto button = QApplication::mouseButtons();
  setCursor(Qt::ClosedHandCursor);

  if (button & Qt::LeftButton) {
    QPoint n_coordinates = QPoint(event->scenePosition().x() - x(),
                                  event->scenePosition().y() - y());

    int count = (n_coordinates.x() - _mouseStartPosition.x()) /
                (_current_icon->width());
    if (!count) return;

    auto it = std::find(_commands_list->begin(), _commands_list->end(),
                        _current_icon->getCommand());
    auto it_before = it;

    // auto widget = _widgets_collection->find(&(*it))->second;
    int layout_size = _commands_layout->count();
    int ind = _commands_layout->indexOf(_current_icon);
    if (ind == -1) return;

    if (count < 0 && ind > 0) {
      _controller->moveCombatant(it, --it_before);
      _commands_layout->removeWidget(_current_icon);
      _commands_layout->insertWidget(ind - 1, _current_icon);
      _mouseStartPosition -= QPoint(0, _current_icon->height());
    } else if (count > 0 && ind < layout_size - 1) {
      _controller->moveCombatant(it, ++ ++it_before);
      _commands_layout->removeWidget(_current_icon);
      _commands_layout->insertWidget(ind + 1, _current_icon);
      _mouseStartPosition += QPoint(0, _current_icon->height());
    }
    update();
    QVBoxLayout *new_layout =
        qobject_cast<QVBoxLayout *>(_commands_layout /*this->layout()*/);
    new_layout->update();
    this->saveGeometry();
  }
}

void DragNDropQWidgetCommands::mouseReleaseEvent(QMouseEvent *event) {
  Q_UNUSED(event);

  setCursor(Qt::ArrowCursor);
}

// void DragNDropQWidgetCommands::dragEnterEvent(QDragEnterEvent* event) {

//}

// void DragNDropQWidgetCommands::dragLeaveEvent(QDragLeaveEvent* event);
// void DragNDropQWidgetCommands::dropEvent(QDropEvent* event);
