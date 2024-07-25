#include "combatantwidget.h"

#include "ui_combatantwidget.h"

CombatantWidget::CombatantWidget(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::CombatantWidget),
      _controller(new pf2e_manager::Controller()),
      _builder(new pf2e_manager::SimpleEffectBuilder()),
      _director(new pf2e_manager::EffectDirector(_builder)) {
  ui->setupUi(this);

  using namespace pf2e_manager;
  Combatant tmp(100, 36, Combatant::Side::TEAM, "Peppa");
  _controller->addCombatant(_controller->getCombatants().begin(),
                            std::move(tmp));

  auto it = _controller->getCombatants().begin();
  ui->lineEdit_hp_curr->setText(QString::number(it->getHPCurr()));
  ui->lineEdit_hp_max->setText(QString::number(it->getHPMax()));
  ui->lineEdit_hp_tmp->setText(QString::number(it->getHPTmp()));
}

CombatantWidget::~CombatantWidget() {
  delete ui;
  delete _controller;
}
