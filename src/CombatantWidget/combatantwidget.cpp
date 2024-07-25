#include "combatantwidget.h"

#include "ui_combatantwidget.h"

CombatantWidget::CombatantWidget(QWidget* parent)
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
  ui->label_name->setText(QString::fromStdString(it->getName()));
  ui->lineEdit_hp_curr->setText(QString::number(it->getHPCurr()));
  ui->lineEdit_hp_max->setText(QString::number(it->getHPMax()));
  ui->lineEdit_hp_tmp->setText(QString::number(it->getHPTmp()));

  _director->buildClumsyEffect(2, 1);
  _builder->setReciever(&(*it));
  _builder->setCreator(nullptr);
  _controller->addEffect(_builder, it);

  auto it_eff = it->getEffects().begin();
  // QLabel* label = new QLabel();
  // label->setText(QString("%1:%2\tDuratoin:%3\tValue:%4").arg(QString::fromStdString((*it_eff)->getName())).
  //                arg(QString::fromStdString((*it_eff)->getObject()->getName())).
  //                arg(QString::number((*it_eff)->getDuration())).
  //                arg(QString::number((*it_eff)->getValue())));

  QListWidgetItem* item = new QListWidgetItem();
  item->setText(
      QString("%1 from %2 on %3\tDuratoin:%4\tValue:%5")
          .arg(QString::fromStdString((*it_eff)->getName()))
          .arg(QString::fromStdString((*it_eff)->getCreator()
                                          ? (*it_eff)->getCreator()->getName()
                                          : "User"))
          .arg(QString::fromStdString((*it_eff)->getObject()->getName()))
          .arg(QString::number((*it_eff)->getDuration()))
          .arg(QString::number((*it_eff)->getValue())));
  ui->listWidget_effect->addItem(item);
}

CombatantWidget::~CombatantWidget() {
  delete ui;
  delete _controller;
}
