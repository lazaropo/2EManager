#ifndef COMBATANTMODELDELEGETE_H
#define COMBATANTMODELDELEGETE_H

#include <QStyledItemDelegate>

#include "dragndropqwidget.h"

class CombatantModelDelegete : public QStyledItemDelegate {
  Q_OBJECT
 public:
  explicit CombatantModelDelegete(DragNDropQWidget *model,
                                  QObject *parent = nullptr);

 protected:
  void paint(QPainter *painter, const QStyleOptionViewItem &option,
             const QModelIndex &index) const override;

  bool editorEvent(QEvent *event, QAbstractItemModel *model,
                   const QStyleOptionViewItem &option,
                   const QModelIndex &index) override;

  QSize sizeHint(const QStyleOptionViewItem &option,
                 const QModelIndex &index) const override {
    Q_UNUSED(option);
    CombatantWidget *widget = _model->at(index.row());
    return widget->size();
  }

 private:
  DragNDropQWidget *_model;
  CombatantWidget *_curent;
};

#endif  // COMBATANTMODELDELEGETE_H
