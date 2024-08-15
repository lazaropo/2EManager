#include "managerwidget.h"

#include <iostream>  // <-----------------------------

#include "ui_managerwidget.h"

ManagerWidget::ManagerWidget(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::ManagerWidget),
      _controller(new pf2e_manager::Controller),
      _box_combatants(
          new DragNDropQWidget(_controller, &_combatant_list, this)),
      _box_commands(new DragNDropQWidgetCommands(_controller, this)) {
  ui->setupUi(this);

  //  ui->graphicsView->setController(_controller);
  //  ui->graphicsView->setWidgets(&_combatant_list);

  using namespace pf2e_manager;

  _box_combatants->setArea(ui->scrollArea_combatants);

  //  Combatant *tmp = new Combatant(100, 36, Combatant::Side::TEAM, "Peppa");
  //  _controller->addCombatant(tmp);
  //  Combatant *tmp1 = new Combatant(50, 16, Combatant::Side::TEAM, "Ricky");
  //  _controller->addCombatant(tmp1);
  //  Combatant *tmp2 = new Combatant(200, 40, Combatant::Side::ENEAMY,
  //  "Stone"); _controller->addCombatant(tmp2); Combatant *tmp3 = new
  //  Combatant(10, 36, Combatant::Side::TEAM, "Tree");
  //  _controller->addCombatant(tmp3);
  //  Combatant *tmp4 =
  //      new Combatant(278, 45, Combatant::Side::ENEAMY, "Sun Child");
  //  _controller->addCombatant(tmp4);
  //  Combatant *tmp5 = new Combatant(128, 28, Combatant::Side::TEAM, "IG-500");
  //  _controller->addCombatant(tmp5);

  // auto unit_it = _controller->getCombatants()->begin();

  //  pf2e_manager::SimpleEffectBuilder builder;
  //  pf2e_manager::EffectDirector director(&builder);
  //  director.buildClumsyEffect(2, 1);
  //  builder.setReciever(*unit_it);
  //  builder.setCreator(nullptr);
  //  _controller->addEffect(&builder, *unit_it);

  //  director.buildConfusedEffect(5);
  //  builder.setReciever(*unit_it);
  //  builder.setCreator(nullptr);
  //  _controller->addEffect(&builder, *unit_it);

  //  for (auto comb : _controller->getCombatants().begin()->getEffects())
  //    std::cout << comb->getName();

  for (auto it : *_controller->getCombatants()) _box_combatants->addWidget(it);
  //  _box_combatants->addWidget(tmp);
  //  _box_combatants->addWidget(tmp1);
  //  _box_combatants->addWidget(tmp2);
  //  _box_combatants->addWidget(tmp3);
  //  _box_combatants->addWidget(tmp4);
  //  _box_combatants->addWidget(tmp5);

  //  for(auto it : _combatant_list)
  //    it->updateContent();
  // setMouseTracking(true);

  //  _box_commands->addCommand(_controller->makeCommand(
  //      nullptr, static_cast<SubjectBase *>(tmp), "command:harm", 10));
  //  _box_commands->addCommand(_controller->makeCommand(
  //      nullptr, static_cast<SubjectBase *>(tmp1), "command:harm", 10));
  //  _box_commands->addCommand(_controller->makeCommand(
  //      static_cast<SubjectBase *>(tmp), static_cast<SubjectBase *>(tmp2),
  //      "command:harm", 10));
  //  _box_commands->addCommand(_controller->makeCommand(
  //      nullptr, static_cast<SubjectBase *>(tmp3), "command:harm", 10));
  //  _box_commands->addCommand(_controller->makeCommand(
  //      static_cast<SubjectBase *>(tmp), static_cast<SubjectBase *>(tmp2),
  //      "command:heal", 10));
  //  _box_commands->addCommand(_controller->makeCommand(
  //      nullptr, static_cast<SubjectBase *>(tmp1), "command:harm", 10));

  ui->scrollArea_combatants->setWidget(_box_combatants);
  ui->scrollArea_commands->setWidget(_box_commands);

  ui->scrollArea_combatants->setAttribute(Qt::WA_StyledBackground);
  ui->scrollArea_combatants->setBackgroundRole(QPalette::Window);

  ui->scrollArea_commands->setAttribute(Qt::WA_StyledBackground);
  ui->scrollArea_commands->setBackgroundRole(QPalette::Window);

  _box_combatants->updateContent();
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

// void ManagerWidget::setCurrent(QMouseEvent *event) {
//   Q_UNUSED(event);

//}

void ManagerWidget::on_pushButton_create_combatant_clicked() {
  pf2e_manager::Combatant *body;
  CombatantDialog dialog(&body);
  dialog.exec();
  _controller->addCombatant(body);

  _box_combatants->addWidget(body);
}

void ManagerWidget::on_pushButton_create_effect_2_clicked() {
  pf2e_manager::CommandBase *command;
  CommandDialog dialog(&command, _controller);
  // command have to be set in collection from model
  if (dialog.exec() == QDialog::Rejected) return;
  _box_combatants->updateContent(command->getReciever());

  _box_commands->addCommand(command);
}

void ManagerWidget::on_pushButton_create_order_clicked() {
  _controller->sortByInit();
  _box_combatants->updateContent();
}

void ManagerWidget::on_pushButton_turn_clicked(bool checked) {
  if (checked) {
    _controller->startTurn();
  } else {
    _controller->nextTurn();
    // TODO:
    // make new _current_widget;
  }
}

void ManagerWidget::on_pushButton_create_remove_clicked() {
  auto widget = _combatant_list.extract(
      _box_combatants->getCurrentWidget()->getCombatant());
  if (widget.mapped() && widget.mapped()->getCombatant()) {
    _controller->removeCombatant(widget.mapped()->getCombatant());
    delete widget.mapped();
  }
}
