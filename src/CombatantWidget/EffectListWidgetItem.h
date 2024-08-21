#ifndef EFFECTLISTWIDGETITEM_H
#define EFFECTLISTWIDGETITEM_H

#include <QLabel>
#include <QListWidgetItem>
#include <QMenu>
#include <QtWidgets>

#include "../Model/Controller.h"

class EffectListWidgetItem : public QListWidgetItem {
 public:
  explicit EffectListWidgetItem(pf2e_manager::EffectBase* pos,
                                QListWidget* listview = nullptr)
      : QListWidgetItem(listview), _effect(pos) {
    setText(QString());
  }

  explicit EffectListWidgetItem(pf2e_manager::EffectBase* pos,
                                const QString& text,
                                QListWidget* listview = nullptr)
      : QListWidgetItem(text, listview), _effect(pos) {}

  EffectListWidgetItem(const EffectListWidgetItem& other)
      : QListWidgetItem(other), _effect(other._effect) {}

  pf2e_manager::EffectBase* getEffect() { return _effect; }

 protected:
  pf2e_manager::EffectBase* _effect;
};

#endif  // EFFECTLISTWIDGETITEM_H
