#include "dragndropqwidget_commands.h"

DragNDropQWidgetCommands::DragNDropQWidgetCommands(
    pf2e_manager::Controller *controller, QWidget *parent)
    : QWidget(parent),
      _controller(controller),
      _commands_list(&_controller->getCommands()),
      _commands_layout(new QBoxLayout(QBoxLayout::LeftToRight, this)) {
  setFixedHeight(110);

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
  setAttribute(Qt::WA_StyledBackground);
  setPalette(QPalette(QColor(250, 238, 221)));
}

void DragNDropQWidgetCommands::addCommand(pf2e_manager::CommandBase *command) {
  CommandIcon *obj = new CommandIcon(command);
  _widgets_collection.push_back(obj);

  _commands_layout->addWidget(/*_commands_layout->count(),*/ obj);
  QObject::connect(obj, &CommandIcon::mousePressed, this,
                   &DragNDropQWidgetCommands::mousePressEvent);
  obj->setAttribute(Qt::WA_StyledBackground);
  this->setFixedWidth(width() + _commands_layout->spacing() + obj->width());
}

void DragNDropQWidgetCommands::mousePressEvent(QMouseEvent *event) {
  if (event->button() & Qt::LeftButton) {
    if (_current_icon) _current_icon->setBaseStyle();

    _current_icon = static_cast<CommandIcon *>(sender());
    if (!_current_icon) {
      // delete _description;
      return;
    } else if (_description)
      _description->hide();

    _current_icon->setHighligthStyle();

    if (!_description) _description = new QTextBrowser();
    auto invoker = _current_icon->getCommand()->getInvoker();
    auto reciever = _current_icon->getCommand()->getReciever();

    QString text;

    pf2e_manager::MassHarmCommand *mass_harm_cmd =
        dynamic_cast<pf2e_manager::MassHarmCommand *>(
            _current_icon->getCommand());
    pf2e_manager::MassHealCommand *mass_heal_cmd =
        dynamic_cast<pf2e_manager::MassHealCommand *>(
            _current_icon->getCommand());

    if (mass_harm_cmd) {
      for (auto cmd : mass_harm_cmd->getInfo()) {
        invoker = cmd->getInvoker();
        reciever = cmd->getReciever();
        text += QString("Invoker:\t%1\tReciever:\t%2\tValue:%3\n")
                    .arg(QString::fromStdString(invoker ? invoker->getName()
                                                        : "User"))
                    .arg(QString::fromStdString(reciever ? reciever->getName()
                                                         : "nullptr!!!"))
                    .arg(QString::number(cmd->value()));
      }
    } else if (mass_heal_cmd) {
      for (auto cmd : mass_heal_cmd->getInfo()) {
        invoker = cmd->getInvoker();
        reciever = cmd->getReciever();
        text += QString("Invoker:\t%1\tReciever:\t%2\tValue:%3\n")
                    .arg(QString::fromStdString(invoker ? invoker->getName()
                                                        : "User"))
                    .arg(QString::fromStdString(reciever ? reciever->getName()
                                                         : "nullptr!!!"))
                    .arg(QString::number(cmd->value()));
      }
    } else {
      text = QString("Invoker:\t%1\tReciever:\t%2\tValue:%3\n")
                 .arg(QString::fromStdString(invoker ? invoker->getName()
                                                     : "User"))
                 .arg(QString::fromStdString(reciever ? reciever->getName()
                                                      : "nullptr!!!"))
                 .arg(QString::number(_current_icon->getCommand()->value()));
    }

    _description->setText(text);

    _description->setMinimumWidth(500);
    _description->setWindowFlag(Qt::WindowStaysOnTopHint);
    _description->show();
    _description->raise();
  }
}

void DragNDropQWidgetCommands::mouseReleaseEvent(QMouseEvent *event) {
  Q_UNUSED(event);

  setCursor(Qt::ArrowCursor);
}
