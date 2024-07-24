#include "combatantwidget.h"

#include "ui_combatantwidget.h"

CombatantWidget::CombatantWidget(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::CombatantWidget),
      _controller(new pf2e_manager::Controller()) {
  ui->setupUi(this);
  using namespace pf2e_manager;
  Combatant tmp(100, 36, Combatant::Side::TEAM, "Peppa");
  _controller->addCombatant(_controller->getCombatants().begin(),
                            std::move(tmp));
}

CombatantWidget::~CombatantWidget() {
  delete ui;
  delete _controller;
}
