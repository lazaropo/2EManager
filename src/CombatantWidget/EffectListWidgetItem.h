#ifndef EFFECTLISTWIDGETITEM_H
#define EFFECTLISTWIDGETITEM_H

#include <QLabel>
#include <QListWidgetItem>
#include <QMenu>
#include <QtWidgets>

#include "../Model/Controller.h"

// QT_BEGIN_NAMESPACE
// namespace Ui {
// class EffectListWidgetItem;
// }
// QT_END_NAMESPACE

class EffectListWidgetItem : public QListWidgetItem {
 public:
  explicit EffectListWidgetItem(pf2e_manager::Combatant::t_pos_eff pos,
                                QListWidget* listview = nullptr)
      : _effect(pos), QListWidgetItem(listview) {}

  explicit EffectListWidgetItem(pf2e_manager::Combatant::t_pos_eff pos,
                                const QString& text,
                                QListWidget* listview = nullptr)
      : _effect(pos), QListWidgetItem(text, listview) {}

  EffectListWidgetItem(const EffectListWidgetItem& other)
      : _effect(other._effect), QListWidgetItem(other) {}

  pf2e_manager::Combatant::t_pos_eff getEffect() { return _effect; }

 protected:
  pf2e_manager::Combatant::t_pos_eff _effect;
};

#endif  // EFFECTLISTWIDGETITEM_H
