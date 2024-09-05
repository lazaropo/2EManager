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
  ui->setupUi(this);

  using namespace pf2e_manager;

  _box_combatants->setArea(ui->scrollArea_combatants);
  _box_commands->setArea(ui->scrollArea_commands);

  for (auto it : *_controller->getCombatants()) _box_combatants->addWidget(it);

  ui->scrollArea_combatants->setWidget(_box_combatants);
  ui->scrollArea_commands->setWidget(_box_commands);

  ui->scrollArea_combatants->setAttribute(Qt::WA_StyledBackground);
  ui->scrollArea_combatants->setBackgroundRole(QPalette::Window);

  ui->scrollArea_commands->setAttribute(Qt::WA_StyledBackground);
  ui->scrollArea_commands->setBackgroundRole(QPalette::Window);

  _box_combatants->updateContent();

  _box_combatants->setModelCurrentComatant(_controller->getCurrent());
}

ManagerWidget::~ManagerWidget() {
  delete ui;
  delete _controller;
}

void ManagerWidget::on_pushButton_create_effect_clicked() {
  auto current_widget = _box_combatants->getCurrentWidget();
  if (!current_widget) return;

  EffectDialog dialog =
      /*new */ EffectDialog(_controller, current_widget->getCombatant(), this);
  if (dialog.exec() == QDialog::Rejected) return;

  current_widget->updateContent();
}


void ManagerWidget::on_pushButton_create_combatant_clicked() {
  pf2e_manager::Combatant *body;
  CombatantDialog dialog(&body);
  if (dialog.exec() == QDialog::Accepted) {
    _controller->addCombatant(body);
    _box_combatants->addWidget(body);
  }
}

void ManagerWidget::on_pushButton_create_command_clicked() {
  pf2e_manager::CommandBase *command;
  CommandDialog dialog(&command, _controller);
  // command have to be set in collection from model
  if (dialog.exec() == QDialog::Rejected) return;
  _box_combatants->updateContent();

  _box_commands->addCommand(command);
}

void ManagerWidget::on_pushButton_create_order_clicked() {
  _controller->sortByInit();
  _box_combatants->setModelCurrentComatant(_controller->getCurrent());
  _box_combatants->updateContent();
}

void ManagerWidget::on_pushButton_turn_clicked() {
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
}

void ManagerWidget::on_pushButton_create_remove_clicked() {
  auto widget = _combatant_list.extract(
      _box_combatants->getCurrentWidget()->getCombatant());
  if (widget.mapped() && widget.mapped()->getCombatant()) {
    _controller->removeCombatant(widget.mapped()->getCombatant());
    delete widget.mapped();
    _box_combatants->updateContent();
  }
}

int ManagerWidget::getActionConfirmation(pf2e_manager::SubjectBase *sender,
                                         pf2e_manager::SubjectBase *reciever,
                                         const std::string &name) {
  int ret = 0;
  const std::string sender_name = sender ? sender->getName() : "User";
  if (!reciever)
    throw std::logic_error(
        "ManagerWidget: getActionConfirmation: Reciever is null.");
  ValueInputDialog dialog(&ret, sender_name, reciever->getName(), name);
  dialog.exec();

  // _box_commands->addCommand(_controller->getCommands().back());

  return ret;
}
