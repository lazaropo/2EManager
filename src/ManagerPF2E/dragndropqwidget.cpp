#include "dragndropqwidget.h"

DragNDropQWidget::DragNDropQWidget(
    pf2e_manager::Controller *controller,
    std::vector<pf2e_manager::Combatant *, CombatantWidget *>
        *_widgets_collection,
    QObject *parent)
    : QAbstractListModel(parent),
      _controller(controller),
      _combatants_list(_controller->getCombatants()) /*,
       _combatants_layout(new QVBoxLayout(this))*/
{
  // setLayout(_combatants_layout);
  // _combatants_layout->setSpacing(12);

  _widgets_collection->reserve(3);
}

void DragNDropQWidget::addWidget(pf2e_manager::Combatant *combatant) {
  CombatantWidget *obj = new CombatantWidget(combatant);
  obj->_id = ++_id_root;
  _widgets_collection->insert(std::pair(obj->getCombatant(), obj));

  // _combatants_layout->insertWidget(_widgets_collection->size() - 1, obj);
  //  QObject::connect(obj, &CombatantWidget::mousePressed, this,
  //                   &DragNDropQWidget::mousePressEvent);
  obj->setAttribute(Qt::WA_StyledBackground);

  emit layoutChanged();
  //  this->setFixedHeight(height() + _combatants_layout->spacing() +
  //                       obj->height());
}

void DragNDropQWidget::updateContent() {
  // int count = 0;
  for (auto it : *_combatants_list) {
    auto widget = (*_widgets_collection)[it];
    widget->updateContent();
  }
}

void DragNDropQWidget::updateContent(pf2e_manager::SubjectBase *combatant) {
  pf2e_manager::Combatant *body =
      dynamic_cast<pf2e_manager::Combatant *>(combatant);
  if (!body) return;
  auto widget = (*_widgets_collection)[body];
  if (widget) widget->updateContent();
}

QVariant DragNDropQWidget::data(const QModelIndex &index, int role) const {
  CombatantWidget *widget = at(index.row());
  if (widget && widget->getCombatant()) {
    switch (role) {
      case Qt::DisplayRole:
        return QString::fromStdString(widget->getCombatant()->getName());
      case Qt::SizeHintRole:
        return widget->size();
      default:
        return QVariant();
    };
  }
  return QVariant();
}

void DragNDropQWidget::add(pf2e_manager::Combatant *widget) {
  addWidget(widget);
}

CombatantWidget *DragNDropQWidget::at(int index) const {
  pf2e_manager::Combatant *combatant = (*_combatants_list)[index];
  return _widgets_collection->at(combatant);
}
