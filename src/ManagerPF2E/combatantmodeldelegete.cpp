#include "combatantmodeldelegete.h"

CombatantModelDelegete::CombatantModelDelegete(DragNDropQWidget *model,
                                               QObject *parent)
    : QStyledItemDelegate{parent}, _model(model) {}

void CombatantModelDelegete::paint(QPainter *painter,
                                   const QStyleOptionViewItem &option,
                                   const QModelIndex &index) const {
  if (index.column() == 0) {
    CombatantWidget *widget = _model->at(index.row());
    if (widget) {
      //      QRect rect = QRect(widget->x(),
      //                         widget->y() + index.row() * (widget->height() +
      //                         12), widget->width(), widget->height());
      //      QPixmap pixmap = widget->grab();
      //      painter->drawPixmap(option.rect, pixmap);
      return;
    }
  }
  QStyledItemDelegate::paint(painter, option, index);
}

bool CombatantModelDelegete::editorEvent(QEvent *event,
                                         QAbstractItemModel *model,
                                         const QStyleOptionViewItem &option,
                                         const QModelIndex &index) {
  // auto view = qobject_cast<QListView *>(parent());
  // if (view) view->openPersistentEditor(index);
  CombatantWidget *widget = _model->at(index.row());
  if (widget) widget->show();
  return QStyledItemDelegate::editorEvent(event, model, option, index);
}
