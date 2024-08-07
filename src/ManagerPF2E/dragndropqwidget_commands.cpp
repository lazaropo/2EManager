#include "dragndropqwidget_commands.h"

DragNDropQWidgetCommands::DragNDropQWidgetCommands(
    pf2e_manager::Controller *controller, QWidget *parent)
    : QWidget(parent),
      _controller(controller),
      _commands_list(&_controller->getCommands()),
      _commands_layout(new QBoxLayout(QBoxLayout::LeftToRight, this)) {
  setFixedSize(2000, 110);

  _commands_layout->setAlignment(Qt::AlignLeft);
  _commands_layout->setAlignment(Qt::AlignVCenter);

  setLayout(_commands_layout);
  _commands_layout->setSpacing(4);

  setAttribute(Qt::WA_StyledBackground);

  for (auto it : _widgets_collection) {
    _commands_layout->addWidget(it);
    QObject::connect(it, &CommandIcon::mousePressed, this,
                     &DragNDropQWidgetCommands::mousePressEvent);

    it->setAttribute(Qt::WA_StyledBackground);
  }
}

void DragNDropQWidgetCommands::addCommand(pf2e_manager::CommandBase *command) {
  CommandIcon *obj = new CommandIcon(command);
  _widgets_collection.push_back(obj);

  _commands_layout->addWidget(/*_commands_layout->count(),*/ obj);
  QObject::connect(obj, &CommandIcon::mousePressed, this,
                   &DragNDropQWidgetCommands::mousePressEvent);
  obj->setAttribute(Qt::WA_StyledBackground);
}

void DragNDropQWidgetCommands::mousePressEvent(QMouseEvent *event) {
  if (event->button() & Qt::LeftButton) {
    if (_current_icon) _current_icon->setBaseStyle();

    _current_icon = static_cast<CommandIcon *>(sender());
    if (!_current_icon) {
      _description->hide();
      // delete _description;
      return;
    }

    _current_icon->setHighligthStyle();

    // if (_description) delete _description;

    if (!_description) _description = new QTextBrowser();
    auto invoker = _current_icon->getCommand()->getInvoker();
    auto reciever = _current_icon->getCommand()->getReciever();
    _description->setText(
        QString("Invoker:\t%1\tReciever:\t%2\tValue:%3")
            .arg(QString::fromStdString(invoker ? invoker->getName() : "User"))
            .arg(QString::fromStdString(reciever ? reciever->getName()
                                                 : "nullptr!!!"))
            .arg(QString::number(_current_icon->getCommand()->value())));
    _description->setMinimumWidth(400);
    _description->setWindowFlag(Qt::WindowStaysOnTopHint);
    _description->show();
    _description->raise();
  }
}

void DragNDropQWidgetCommands::mouseReleaseEvent(QMouseEvent *event) {
  Q_UNUSED(event);

  setCursor(Qt::ArrowCursor);
}
