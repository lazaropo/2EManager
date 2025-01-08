#include "managerwidget.h"

#include "ui_managerwidget.h"

ManagerWidget::ManagerWidget(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::ManagerWidget),
      _controller(new pf2e_manager::Controller(std::bind(
          &ManagerWidget::getActionConfirmation, this, std::placeholders::_1,
          std::placeholders::_2, std::placeholders::_3))),
      _box_combatants(
          new DragNDropQWidget(_controller, &_combatant_list, this)),
      _box_commands(new DragNDropQWidgetCommands(_controller, this)) {
  pf2e_manager::utility::init_logger();

  try {
    ui->setupUi(this);
    setAcceptDrops(true);

    using namespace pf2e_manager;

    _controller->setCallbackFunctionUserInput(std::bind(
        &ManagerWidget::getActionConfirmation, this, std::placeholders::_1,
        std::placeholders::_2, std::placeholders::_3));

    QSizePolicy policy_combatants(QSizePolicy::MinimumExpanding,
                                  QSizePolicy::Expanding);
    QSizePolicy policy_commands(QSizePolicy::MinimumExpanding,
                                QSizePolicy::Maximum);
    _box_combatants->setSizePolicy(policy_combatants);
    _box_commands->setSizePolicy(policy_commands);

    _box_combatants->setArea(ui->scrollArea_combatants);
    _box_commands->setArea(ui->scrollArea_commands);

    for (auto it : *_controller->getCombatants())
      _box_combatants->addWidget(it);

    ui->scrollArea_combatants->setWidget(_box_combatants);
    ui->scrollArea_commands->setWidget(_box_commands);

    ui->scrollArea_combatants->setAttribute(Qt::WA_StyledBackground);
    ui->scrollArea_combatants->setBackgroundRole(QPalette::Window);

    ui->scrollArea_commands->setAttribute(Qt::WA_StyledBackground);
    ui->scrollArea_commands->setBackgroundRole(QPalette::Window);

    _box_combatants->updateContent();
    _box_commands->updateContent();

    QObject::connect(_box_commands,
                     &DragNDropQWidgetCommands::combatantsChanged,
                     _box_combatants, &DragNDropQWidget::updateContentEvent);

    _box_combatants->setModelCurrentComatant(_controller->getCurrent());
  } catch (std::exception &ex) {
    pf2e_manager::utility::print_log(ex);
  } catch (boost::exception &ex) {
    pf2e_manager::utility::print_log(ex);
  }
}

ManagerWidget::~ManagerWidget() {
  delete ui;
  delete _controller;
}

void ManagerWidget::on_pushButton_create_effect_clicked() {
  try {
    auto current_widget = _box_combatants->getCurrentWidget();
    if (!current_widget) return;

    EffectDialog dialog =
        EffectDialog(_controller, current_widget->getCombatant(), this);
    if (dialog.exec() == QDialog::Rejected) return;

    current_widget->updateContent();
    _box_commands->updateContent();
  } catch (std::exception &ex) {
    pf2e_manager::utility::print_log(ex);
  } catch (boost::exception &ex) {
    pf2e_manager::utility::print_log(ex);
  }
}

void ManagerWidget::on_pushButton_create_combatant_clicked() {
  try {
    pf2e_manager::Combatant *body;
    CombatantDialog dialog(&body);
    if (dialog.exec() == QDialog::Accepted) {
      _controller->addCombatant(body);
      _box_combatants->addWidget(body);
    }
  } catch (std::exception &ex) {
    pf2e_manager::utility::print_log(ex);
  } catch (boost::exception &ex) {
    pf2e_manager::utility::print_log(ex);
  }
}

void ManagerWidget::on_pushButton_create_command_clicked() {
  if (_controller->getCombatants()->empty()) return;
  try {
    pf2e_manager::CommandBase *command;

    CommandDialog dialog(&command, _controller);
    // command have to be set in collection from model
    if (dialog.exec() == QDialog::Rejected) return;
    _box_combatants->updateContent();

    _box_commands->addCommand(command);
  } catch (std::exception &ex) {
    pf2e_manager::utility::print_log(ex);
  } catch (boost::exception &ex) {
    pf2e_manager::utility::print_log(ex);
  }
}

void ManagerWidget::on_pushButton_create_order_clicked() {
  try {
    _controller->sortByInit();
    _box_combatants->setModelCurrentComatant(_controller->getCurrent());
    _box_combatants->updateContent();
  } catch (std::exception &ex) {
    pf2e_manager::utility::print_log(ex);
  } catch (boost::exception &ex) {
    pf2e_manager::utility::print_log(ex);
  }
}

void ManagerWidget::on_pushButton_turn_clicked() {
  try {
    //  if (_button_start_flag) {
    //    _controller->nextTurn();

    //    ui->pushButton_turn->setText("Start of Turn");
    //    ui->pushButton_turn->setStyleSheet(
    //        "QPushButton{"
    //        "font: bold 28px;"
    //        "color: black; "
    //        "background-color: rgb(246, 97, 81);"
    //        "}");
    //  } else {
    _controller->nextTurn();
    _box_combatants->setModelCurrentComatant(_controller->getCurrent());

    // ui->pushButton_turn->setText("Next Turn");
    //  ui->pushButton_turn->setStyleSheet(
    //      "QPushButton {"
    //      "font: bold 28px; "
    //      "color: black;"
    //      "background-color: rgb(143, 240, 164);"
    //      "}");
    // }

    _button_start_flag = !_button_start_flag;

    _box_combatants->updateContent();
    _box_commands->updateContent();
  } catch (std::exception &ex) {
    pf2e_manager::utility::print_log(ex);
  } catch (boost::exception &ex) {
    pf2e_manager::utility::print_log(ex);
  }
}

void ManagerWidget::on_pushButton_create_remove_clicked() {
  try {
    auto widget = _combatant_list.extract(
        _box_combatants->getCurrentWidget()->getCombatant());
    if (!widget) return;
    CombatantWidget *node = widget.mapped();
    if (node && node->getCombatant()) {
      _controller->removeCombatant(node->getCombatant());
      delete node;
      _box_combatants->updateContent();
    }
  } catch (std::exception &ex) {
    pf2e_manager::utility::print_log(ex);
  } catch (boost::exception &ex) {
    pf2e_manager::utility::print_log(ex);
  }
}

int ManagerWidget::getActionConfirmation(pf2e_manager::SubjectBase *sender,
                                         pf2e_manager::SubjectBase *reciever,
                                         const std::string &name) {
  int ret = 0;
  try {
    const std::string sender_name = sender ? sender->getName() : "User";
    if (!reciever)
      throw std::logic_error(
          "ManagerWidget: getActionConfirmation: Reciever is null.");
    ValueInputDialog dialog(&ret, sender_name, reciever->getName(), name);
    dialog.exec();
  } catch (std::exception &ex) {
    pf2e_manager::utility::print_log(ex);
  } catch (boost::exception &ex) {
    pf2e_manager::utility::print_log(ex);
  }

  // _box_commands->addCommand(_controller->getCommands().back());

  return ret;
}

void ManagerWidget::dragEnterEvent(QDragEnterEvent *event) {
  if (event->mimeData()->hasUrls()) {
    const auto urls = event->mimeData()->urls();
    if (!urls.isEmpty() &&
        urls.first().toLocalFile().endsWith(".xml", Qt::CaseInsensitive))
      event->acceptProposedAction();
    qDebug() << "dragEnterEvent triggered";
  } else
    qDebug() << "dragEnterEvent Bad Url";
}

void ManagerWidget::dropEvent(QDropEvent *event) {
  if (event->mimeData()->hasUrls()) {
    const auto urls = event->mimeData()->urls();
    if (!urls.isEmpty()) {
      QString filePath = urls.first().toLocalFile();
      if (filePath.endsWith(".xml", Qt::CaseInsensitive) && _box_combatants) {
        auto combatants = _controller->getCombatants();
        size_t comb_count = combatants->size();
        size_t count = _controller->addFromFile(filePath.toStdString());
        // auto it_end = _controller->getCombatants()->end();
        // if()

        // if (_controller->getCombatants()->size()) {
        //   qDebug() << "1st combatant "
        //            << _controller->getCombatants()->front()->getName();
        // }
        // if (it != it_end) {
        //   qDebug() << "it != it_end combatant it: " << (*it)->getName();
        //   qDebug() << "it != it_end combatant it_end - 1: "
        //            << (*(it_end - 1))->getName();
        // } else {
        //   qDebug() << "it == it_end combatant it_end - 1: "
        //            << (*(it_end - 1))->getName();
        // }

        for (int i = comb_count, i_end = combatants->size(); i < i_end; ++i)
          _box_combatants->addWidget((*combatants)[i]);

        _box_combatants->updateContent();
      }
      qDebug() << "dropEvent triggered";
    }
    qDebug() << "dropEvent Empty";
  }
  qDebug() << "dropEvent Bad Url";
}
