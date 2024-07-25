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

  ui->listWidget_effect->setUI(this);

  EffectListWidgetItem* item =
      new EffectListWidgetItem(it_eff, QString::number(1));
  item->setText(
      QString("%1 from %2 on %3\tDuratoin:%4\tValue:%5")
          .arg(QString::fromStdString((*it_eff)->getName()))
          .arg(QString::fromStdString((*it_eff)->getCreator()
                                          ? (*it_eff)->getCreator()->getName()
                                          : "User"))
          .arg(QString::fromStdString((*it_eff)->getObject()->getName()))
          .arg(QString::number((*it_eff)->getDuration()))
          .arg(QString::number((*it_eff)->getValue())));
  item->setToolTip(QString::fromStdString((*it_eff)->what()));
  // ToolTip::add(item, QString::fromStdString((*it_eff)->what()));

  // setFocusPolicy(Qt::NoFocus);
  // item->setToolTipDuration(10000);
  ui->listWidget_effect->addItem(item);
}

CombatantWidget::~CombatantWidget() {
  delete ui;
  delete _controller;
}

// void CombatantWidget::on_listWidget_effect_itemEntered(QListWidgetItem*
// item_unused) {
//   QLabel* item = new QLabel();
//   item->setScaledContents(true);
//   item->setMaximumSize(ui->layout_effect->maximumSize().rwidth(),
//   ui->layout_effect->maximumSize().rheight()); auto it_eff =
//   _controller->getCombatants().begin()->getEffects().begin();
//   item->setToolTip(QString("%1").arg(QString::fromStdString((*it_eff)->what())));
//   ui->layout_effect->addWidget(item);
// }

// void CombatantWidget::on_listWidget_effect_itemClicked(QListWidgetItem*
// item_unused) {
//   QLabel* item = new QLabel();
//   item->setScaledContents(true);
//   item->setMaximumSize(ui->layout_effect->maximumSize().rwidth(),
//   ui->layout_effect->maximumSize().rheight()); auto it_eff =
//   _controller->getCombatants().begin()->getEffects().begin();
//   item->setText(QString("%1").arg(QString::fromStdString((*it_eff)->what())));
//   item->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
//   ui->layout_effect->addWidget(item);
// }
