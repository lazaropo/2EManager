#include "combatantwidget.h"

#include "ui_combatantwidget.h"

CombatantWidget::CombatantWidget(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::CombatantWidget),
      _controller(new Controller()) {
  ui->setupUi(this);
  Combatant tmp(100, 36, Combatant::Side::ALIVE, "Peppa");
  _controller->addCombatant(std::move(tmp));
}

CombatantWidget::~CombatantWidget() {
  delete ui;
  delete _controller;
}
