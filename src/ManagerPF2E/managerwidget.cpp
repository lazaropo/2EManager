#include "managerwidget.h"

#include <iostream>  // <-----------------------------

#include "ui_managerwidget.h"

ManagerWidget::ManagerWidget(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::ManagerWidget),
      _controller(new pf2e_manager::Controller),
      _combatants_layout(new QVBoxLayout(this)),
      _box(new QWidget(this)) {
  ui->setupUi(this);

  using namespace pf2e_manager;

  Combatant *tmp = new Combatant(100, 36, Combatant::Side::TEAM, "Peppa");
  _controller->addCombatant(/*_controller->getCombatants().begin(),*/
                            std::move(*tmp));
  Combatant *tmp1 = new Combatant(50, 16, Combatant::Side::TEAM, "Ricky");
  _controller->addCombatant(/*_controller->getCombatants().begin(),*/
                            std::move(*tmp1));
  Combatant *tmp2 = new Combatant(200, 40, Combatant::Side::ENEAMY, "Stone");
  _controller->addCombatant(/*_controller->getCombatants().begin(),*/
                            std::move(*tmp2));
  Combatant *tmp3 = new Combatant(10, 36, Combatant::Side::TEAM, "Tree");
  _controller->addCombatant(/*_controller->getCombatants().begin(),*/
                            std::move(*tmp3));
  Combatant *tmp4 =
      new Combatant(278, 45, Combatant::Side::ENEAMY, "Sun Child");
  _controller->addCombatant(/*_controller->getCombatants().begin(),*/
                            std::move(*tmp4));
  Combatant *tmp5 = new Combatant(128, 28, Combatant::Side::TEAM, "IG-500");
  _controller->addCombatant(/*_controller->getCombatants().begin(),*/
                            std::move(*tmp5));

  auto unit_it = _controller->getCombatants().begin();

  pf2e_manager::SimpleEffectBuilder builder;
  pf2e_manager::EffectDirector director(&builder);
  director.buildClumsyEffect(2, 1);
  builder.setReciever(&(*unit_it));
  builder.setCreator(nullptr);
  _controller->addEffect(&builder, tmp);

  director.buildConfusedEffect(5);
  builder.setReciever(&(*unit_it));
  builder.setCreator(nullptr);
  _controller->addEffect(&builder, tmp);

  for (auto comb : _controller->getCombatants().begin()->getEffects())
    std::cout << comb->getName();

  _combatant_list.push_back(new CombatantWidget(tmp));
  _combatant_list.push_back(new CombatantWidget(tmp1));
  _combatant_list.push_back(new CombatantWidget(tmp2));
  _combatant_list.push_back(new CombatantWidget(tmp3));
  _combatant_list.push_back(new CombatantWidget(tmp4));
  _combatant_list.push_back(new CombatantWidget(tmp5));

  //  for(auto it : _combatant_list)
  //    it->updateContent();

  _box->setLayout(_combatants_layout);
  int count = 0;
  for (auto it : _combatant_list) {
    _combatants_layout->addWidget(it);
    QObject::connect(it, &CombatantWidget::mousePressed, this,
                     &ManagerWidget::setCurrent);
    it->setAttribute(Qt::WA_StyledBackground);
    ++count;
  }
  _box->setFixedHeight(count * (*_combatant_list.begin())->height());

  _box->layout()->setSpacing(12);

  ui->scrollArea->setWidget(_box);

  ui->scrollArea->setAttribute(Qt::WA_StyledBackground);
  ui->scrollArea->setBackgroundRole(QPalette::Window);

  //  _current_widget = _combatant_list.front();
  //  EffectDialog *dialog =
  //      new EffectDialog(_current_widget->getCombatant(), this);
  //  dialog->exec();

  //  delete dialog;
}

ManagerWidget::~ManagerWidget() {
  delete ui;
  delete _controller;
}

void ManagerWidget::on_pushButton_create_effect_clicked() {
  if (!_current_widget) return;

  pf2e_manager::SimpleEffectBuilder builder;
  pf2e_manager::EffectDirector director(&builder);
  EffectDialog dialog =
      /*new */ EffectDialog(&director, this);
  dialog.exec();

  builder.setCreator(nullptr);
  builder.setReciever(_current_widget->getCombatant());
  _controller->addEffect(&builder, _current_widget->getCombatant());

  _current_widget->updateContent();
}

void ManagerWidget::setCurrent(QMouseEvent *event) {
  if (_current_widget)
    _current_widget->setStyleSheet(
        "CombatantWidget{ background-color:  rgb(0,0,0);  };");

  // ui->verticalLayout->removeWidget(_current_widget);
  _current_widget = static_cast<CombatantWidget *>(sender());
  _current_widget->setStyleSheet(
      "CombatantWidget{ background-color:  red;  };");
  // ui->verticalLayout->addWidget(_current_widget);
}

void ManagerWidget::on_pushButton_create_combatant_clicked() {
  pf2e_manager::Combatant *body;
  CombatantDialog dialog(&body);
  dialog.exec();
  _controller->addCombatant(std::move(*body));

  CombatantWidget *obj = new CombatantWidget(body);
  _combatant_list.push_back(obj);

  _combatants_layout->addWidget(obj);
  QObject::connect(obj, &CombatantWidget::mousePressed, this,
                   &ManagerWidget::setCurrent);
  obj->setAttribute(Qt::WA_StyledBackground);
}
