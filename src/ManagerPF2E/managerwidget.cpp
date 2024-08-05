#include "managerwidget.h"

#include <iostream>  // <-----------------------------

#include "ui_managerwidget.h"

ManagerWidget::ManagerWidget(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::ManagerWidget),
      _controller(new pf2e_manager::Controller) /*,
       _box(new DragNDropQGraphicsView(_controller, &_combatant_list, this))*/
{
  ui->setupUi(this);

  ui->graphicsView->setController(_controller);
  ui->graphicsView->setWidgets(&_combatant_list);

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

  //  for (auto comb : _controller->getCombatants().begin()->getEffects())
  //    std::cout << comb->getName();

  ui->graphicsView->addWidget(tmp);
  ui->graphicsView->addWidget(tmp1);
  ui->graphicsView->addWidget(tmp2);
  ui->graphicsView->addWidget(tmp3);
  ui->graphicsView->addWidget(tmp4);
  ui->graphicsView->addWidget(tmp5);

  //  for(auto it : _combatant_list)
  //    it->updateContent();

  ui->graphicsView->setFixedHeight(_combatant_list.size() *
                                   (_combatant_list.begin()->second)->height());

  ui->graphicsView->layout()->setSpacing(12);

  // _box->setMouseTracking(true);
  // setMouseTracking(true);

  //  ui->scrollArea->setWidget(_box);

  //  ui->scrollArea->setAttribute(Qt::WA_StyledBackground);
  //  ui->scrollArea->setBackgroundRole(QPalette::Window);
  //  ui->scrollArea->setMouseTracking(true);

  // ui->graphicsView->addScrollBarWidget(ui->scrollArea, Qt::AlignTop);
  // ui->graphicsView->setLayout(_box->layout());
}

ManagerWidget::~ManagerWidget() {
  delete ui;
  delete _controller;
}

void ManagerWidget::on_pushButton_create_effect_clicked() {
  auto current_widget = ui->graphicsView->getCurrentWidget();
  if (!current_widget) return;

  pf2e_manager::SimpleEffectBuilder builder;
  pf2e_manager::EffectDirector director(&builder);
  EffectDialog dialog =
      /*new */ EffectDialog(&director, this);
  dialog.exec();

  builder.setCreator(nullptr);
  builder.setReciever(current_widget->getCombatant());
  _controller->addEffect(&builder, current_widget->getCombatant());

  current_widget->updateContent();
}

// void ManagerWidget::setCurrent(QMouseEvent *event) {
//   Q_UNUSED(event);

//}

void ManagerWidget::on_pushButton_create_combatant_clicked() {
  pf2e_manager::Combatant *body;
  CombatantDialog dialog(&body);
  dialog.exec();
  _controller->addCombatant(std::move(*body));

  ui->graphicsView->addWidget(body);
}

// void ManagerWidget::mouseMoveEvent(QMouseEvent *event) {
//   if (event->button() == Qt::LeftButton &&
//       ui->scrollArea->geometry().contains(event->pos()) &&
//       ((event->pos() - _mouseStartPosition).manhattanLength() >=
//        QApplication::startDragDistance())) {
//     QDrag *new_drag = new QDrag(this);
//     QMimeData *mime_data = new QMimeData();

//    // mime_data->setData(mimeType, data);

//    new_drag->setMimeData(mime_data);

//    Qt::DropAction action = new_drag->exec(Qt::MoveAction);
//    Q_UNUSED(action);

//    (*std::find(_combatant_list.begin(), _combatant_list.end(),
//                _current_widget))
//        ->hide();
//    //  _combatants_layout->removeItem(_current_widget);
//  }
//}

// void ManagerWidget::mouseReleaseEvent(QMouseEvent* event) {
//   if (event->button() == Qt::LeftButton &&
//       ui->scrollArea->geometry().contains(event->pos()) &&
//       ((event->pos() - _mouseStartPosition).manhattanLength() >=
//        QApplication::startDragDistance()))
// }

// void ManagerWidget::on_widget_drag(QMouseEvent *event) {

//}
