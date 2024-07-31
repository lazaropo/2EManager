#include "managerwidget.h"

#include "ui_managerwidget.h"

ManagerWidget::ManagerWidget(QWidget *parent)
    : ManagerWidget(parent),
      ui(new Ui::ManagerWidget),
      _controller(new pf2e_manager::Controller()) {
  ui->setupUi(this);

  using namespace pf2e_manager;

  Combatant tmp(100, 36, Combatant::Side::TEAM, "Peppa");
  _controller->addCombatant(_controller->getCombatants().begin(),
                            std::move(tmp));

  auto unit_it = _controller->getCombatants().begin();

pf2e_manager:
  SimpleEffectBuilder builder;
  pf2e_manager::EffectDirector director(&builder);
  director.buildClumsyEffect(2, 1);
  builder.setReciever(&(*unit_it));
  builder.setCreator(nullptr);
  _controller->addEffect(&builder, unit_it);

  director.buildConfusedEffect(5);
  builder.setReciever(&(*unit_it));
  builder.setCreator(nullptr);
  _controller->addEffect(&builder, unit_it);

  _combatant_widgets.push_back(new CombatantWidget(tmp, this));

  for (auto it : _combatant_widgets) ui->combatans_list->add
}

ManagerWidget::~ManagerWidget() {
  delete ui;
  delete _controller;
}
