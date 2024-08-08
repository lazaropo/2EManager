#ifndef COMBATANTWIDGET_H
#define COMBATANTWIDGET_H

#include <QDrag>
#include <QListWidget>
#include <QToolTip>
#include <QWidget>
#include <QtWidgets>

// #include "EffectListWidgetItem.h"
#include "../CombatantWidget/MyMenuWidget.h"
#include "../Model/Controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class CombatantWidget;
// class MyMenuWidget;
using namespace pf2e_manager;
}  // namespace Ui
QT_END_NAMESPACE

class CombatantWidget : public QWidget {
  Q_OBJECT

 public:
  CombatantWidget(pf2e_manager::Combatant *_combatant,
                  QWidget *parent = nullptr);
  ~CombatantWidget();

  pf2e_manager::Combatant *getCombatant() { return _combatant; }
  void setCombatant(pf2e_manager::Combatant *other) { _combatant = other; }

  void setBaseStyle() { setStyleSheet(_base_style); }

  void setHighlightStyle() { setStyleSheet(_highlight_style); }

  void setHoverStyle() { setStyleSheet(_hover_style); }

  void updateContent();

 signals:
  void mousePressed(QMouseEvent *event = nullptr);

 protected slots:
  void mousePressEvent(QMouseEvent *event = nullptr) override {
    emit mousePressed(event);
  }

  //  void enterEvent(QEnterEvent *event) override;
  //  void leaveEvent(QEvent *event) override;

 private slots:
  // void lineEditCurrHPFinished();

  // void mouseMoved(QMouseEvent *event = nullptr);

 private:
  Ui::CombatantWidget *ui;

  MyMenuWidget *listWidget_effect = new MyMenuWidget(this);
  pf2e_manager::Combatant *_combatant = nullptr;

  QString _base_style{
      "QWidget#CombatantWidget {"
      "background-color: rgb(0,0,0);"
      "}"};

  QString _highlight_style{
      "QWidget#CombatantWidget {"
      " background-color: red; "
      "}"};

  QString _hover_style{
      "QWidget#CombatantWidget {"
      " background-color: ; "
      "}"};
};
#endif  // COMBATANTWIDGET_H
