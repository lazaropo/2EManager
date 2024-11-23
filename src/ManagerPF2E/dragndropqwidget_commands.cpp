#include "dragndropqwidget_commands.h"

DragNDropQWidgetCommands::DragNDropQWidgetCommands(
    pf2e_manager::Controller *controller, QWidget *parent)
    : QWidget(parent),
      _controller(controller),
      _commands_list(&_controller->getCommands()),
      _commands_layout(new QBoxLayout(QBoxLayout::LeftToRight, this)) {
  // setFixedHeight(110);

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

  // if (_area) {
  // _area->setPalette(palette);
  //     _area->setMaximumHeight(120);
    // }
}

void DragNDropQWidgetCommands::addCommand(pf2e_manager::CommandBase *command) {
  CommandIcon *obj = new CommandIcon(command);
  _widgets_collection.push_back(obj);

  _commands_layout->addWidget(/*_commands_layout->count(),*/ obj);
  QObject::connect(obj, &CommandIcon::mousePressed, this,
                   &DragNDropQWidgetCommands::mousePressEvent);
  obj->setAttribute(Qt::WA_StyledBackground);
  if (_commands_layout->count() * (_commands_layout->spacing() + obj->width()) > width())
      // this->setFixedWidth(width() + _commands_layout->spacing() + obj->width());
    _area->setMinimumWidth(width() + _commands_layout->spacing() + obj->width());
  // setSizePolicy(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
  // QSizePolicy policy( QSizePolicy::Minimum, QSizePolicy::Maximum);
  // policy.setHeightForWidth(true);
  // setSizePolicy(policy);
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

    //    if (count >  && widget != _widgets_collection.end())
    //      this->setFixedWidth();
    //          _commands_layout->count() *
    //              ((*widget)->height() + _commands_layout->spacing()) -
    //          _commands_layout->spacing());
  }

}

void DragNDropQWidgetCommands::mousePressEvent(QMouseEvent *event) {
  if (event->button() & Qt::LeftButton) {
      _current_icon = static_cast<CommandIcon *>(sender());
      if (!_current_icon)
          return;
      else if (_description) {
          _prev_icon->setBaseStyle();
          _description->close();
      }

      _current_icon->setBaseStyle();

      _current_icon->setHighligthStyle();

      if (!_description)
          _description = new ClosebleTextBrowser();
      auto invoker = _current_icon->getCommand()->getInvoker();
      auto reciever = _current_icon->getCommand()->getReciever();

      _description->setStyleSheet("QTextBrowser {"
                                  "background-color: rgb(250, 238, 221);"
                                  "font: 14px 'Arial';"
                                  "color: black;"
                                  "}"
                                  "");

      QObject::connect(_description, &ClosebleTextBrowser::closed, [&](QCloseEvent* event){
          _current_icon->setBaseStyle();
          QWidget::closeEvent(event);
      });

      QString text;

      pf2e_manager::MassHarmCommand *mass_harm_cmd = dynamic_cast<pf2e_manager::MassHarmCommand *>(
          _current_icon->getCommand());
      pf2e_manager::MassHealCommand *mass_heal_cmd = dynamic_cast<pf2e_manager::MassHealCommand *>(
          _current_icon->getCommand());

      if (mass_harm_cmd) {
          for (auto cmd : mass_harm_cmd->getInfo()) {
              invoker = cmd->getInvoker();
              reciever = cmd->getReciever();
              text += QString("Invoker:\t%1\tReciever:\t%2\tValue:%3\n")
                          .arg(QString::fromStdString(invoker ? invoker->getName() : "User"))
                          .arg(QString::fromStdString(reciever ? reciever->getName() : "nullptr!!!"))
                          .arg(QString::number(cmd->value()));
          }
      } else if (mass_heal_cmd) {
          for (auto cmd : mass_heal_cmd->getInfo()) {
              invoker = cmd->getInvoker();
              reciever = cmd->getReciever();
              text += QString("Invoker:\t%1\tReciever:\t%2\tValue:%3\n")
                          .arg(QString::fromStdString(invoker ? invoker->getName() : "User"))
                          .arg(QString::fromStdString(reciever ? reciever->getName() : "nullptr!!!"))
                          .arg(QString::number(cmd->value()));
          }
      } else {
          text = QString("Invoker:\t%1\tReciever:\t%2\tValue:%3\n")
                     .arg(QString::fromStdString(invoker ? invoker->getName() : "User"))
                     .arg(QString::fromStdString(reciever ? reciever->getName() : "nullptr!!!"))
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

// void DragNDropQWidgetCommands::resizeEvent(QResizeEvent* event) {
//     //if(hasHeightForWidth()){
//     // setFixedHeight(heightForWidth(event->()));
//     // setFixedSize(event->size());
//     QSize area_size = _area->size();
//     double width_coeff = static_cast<double>(event->size().width()) / qMax(event->oldSize().width(), 1);
//     //int height_coeff = static_cast<double>(event->size().height()) / qMax(event->oldSize().height(), 1);
//     if(width_coeff > 1.03 || width_coeff < 0.97 /*|| height_coeff > 1.03 || height_coeff < 0.97*/){
//         int width = width_coeff * area_size.width();
//         int height = 120;/*height_coeff **/ area_size.height();

//         QSize new_size(width, height);

//         QWidget* parent = static_cast<QWidget*>(this);

//         if(parent == nullptr)
//             throw std::runtime_error("DragNDropQWidgetCommands::resizeEvent(): parent is null.");

//         QSize parent_size = parent->size();

//         if(parent_size.width() > new_size.width())
//             new_size.setWidth(parent_size.width());
//         // if(parent_size.height() > new_size.height())
//         //     new_size.setHeight(parent_size.height());

//         _area->setFixedSize(new_size);
//         _area->setMaximumHeight(120);
//         //_combatants_layout->resize(event->size());
//         update();
//         // updateGeometry();
//     //}
//     // QWidget::resizeEvent(event);

// }
// }

// void DragNDropQWidgetCommands::mouseReleaseEvent(QMouseEvent *event) {
//   Q_UNUSED(event);

//  setCursor(Qt::ArrowCursor);
//}
