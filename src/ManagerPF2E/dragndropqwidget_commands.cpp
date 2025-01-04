#include "dragndropqwidget_commands.h"

DragNDropQWidgetCommands::DragNDropQWidgetCommands(
    pf2e_manager::Controller *controller, QWidget *parent)
    : QWidget(parent),
      _controller(controller),
      _commands_list(&_controller->getCommands()),
      _commands_layout(new QBoxLayout(QBoxLayout::LeftToRight, this)) {
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
  // This widget should be filled by color with code, not with qt designer
  auto palette = QPalette(QColor(204, 213, 174));
  setPalette(palette);
}

void DragNDropQWidgetCommands::addCommand(pf2e_manager::CommandBase *command) {
  if (!command) return;

  CommandIcon *obj = new CommandIcon(command);
  _widgets_collection.push_back(obj);

  _commands_layout->addWidget(obj);
  QObject::connect(obj, &CommandIcon::mousePressed, this,
                   &DragNDropQWidgetCommands::mousePressEvent);
  obj->setAttribute(Qt::WA_StyledBackground);
}

void DragNDropQWidgetCommands::updateContent() {
  int count = 0;

  QList<CommandIcon *>::iterator widget = _widgets_collection.end();
  for (auto it : *_commands_list) {
    widget = std::find_if(
        _widgets_collection.begin(), _widgets_collection.end(),
        [&](CommandIcon *icon) { return icon->getCommand() == it; });
    // (*_widgets_collection)[it];
    if (widget != _widgets_collection.end()) {
      _commands_layout->removeWidget(*widget);
      _commands_layout->insertWidget(count++, *widget);
    } else
      addCommand(it);
  }
}

void DragNDropQWidgetCommands::mousePressEvent(QMouseEvent *event) {
  auto button = event->button();
  if (button & Qt::RightButton) {
    _current_icon = static_cast<CommandIcon *>(sender());
    QContextMenuEvent *menu_event = new QContextMenuEvent(
        QContextMenuEvent::Mouse, event->pos(), event->globalPos());
    QWidget::contextMenuEvent(menu_event);
  }
  if (button & Qt::LeftButton) {
    _current_icon = static_cast<CommandIcon *>(sender());
    if (!_current_icon)
      return;
    else if (_description) {
      _prev_icon->setBaseStyle();
      _description->close();
    }

    _current_icon->setBaseStyle();

    _current_icon->setHighligthStyle();

    if (!_description) _description = new ClosebleTextBrowser();
    auto invoker = _current_icon->getCommand()->getInvoker();
    auto reciever = _current_icon->getCommand()->getReciever();

    _description->setStyleSheet(
        "QTextBrowser {"
        "background-color: rgb(250, 238, 221);"
        "font: 14px 'Arial';"
        "color: black;"
        "}");

    QObject::connect(_description, &ClosebleTextBrowser::closed,
                     [&](QCloseEvent *event) {
                       _current_icon->setBaseStyle();
                       QWidget::closeEvent(event);
                     });

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

    _prev_icon = _current_icon;

    _description->setText(text);

    _description->setMinimumWidth(500);
    _description->setWindowFlag(Qt::WindowStaysOnTopHint);
    _description->show();
    _description->raise();
  }
}

void DragNDropQWidgetCommands::contextMenuEvent(QContextMenuEvent *event) {
  QMenu menu(this->parentWidget());
  menu.setStyleSheet(_menu_style);

  CommandIcon *instance = _current_icon;
  pf2e_manager::CommandBase *picked_command = nullptr;
  if (instance)
    picked_command = instance->getCommandBase();
  else
    return;

  bool is_active = picked_command->isActive();

  QAction *do_undo_command =
      menu.addAction(is_active ? "Undo Command" : "Do Command");
  QAction *remove_command = menu.addAction("Remove Command");

  QAbstractItemDelegate::connect(do_undo_command, &QAction::triggered, [=]() {
    if (is_active)
      picked_command->undo();
    else
      picked_command->execute();
    emit combatantsChanged();
  });

  QAbstractItemDelegate::connect(remove_command, &QAction::triggered, [=]() {
    _controller->removeCommand(picked_command);
    _widgets_collection.removeOne(_current_icon);
    // removeItemWidget(item(count));
    updateContent();
    delete picked_command;
    delete _current_icon;
    _current_icon = nullptr;
    emit combatantsChanged();
  });

  menu.exec(event->globalPos());
}
