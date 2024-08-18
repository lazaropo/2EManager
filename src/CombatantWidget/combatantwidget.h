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

  void setBaseStyle() {
    if (!_fixe_style) setStyleSheet(_base_style);
  }

  void setHighlightStyle() {
    if (!_fixe_style) setStyleSheet(_highlight_style);
  }

  void setHoverStyle() { setStyleSheet(_hover_style); }

  void setModelCurrentStyle() { setStyleSheet(_model_style); }

  void updateContent();

  bool _fixe_style = false;

 signals:
  void mousePressed(QMouseEvent *event = nullptr);
  void mouseMoved(QMouseEvent *event = nullptr);
  void dragEntered(QDragEnterEvent *event = nullptr);
  void dragLeaved(QDragLeaveEvent *event = nullptr);
  void dragMoved(QDragMoveEvent *event = nullptr);
  void droped(QDropEvent *event = nullptr);

 protected slots:
  void mousePressEvent(QMouseEvent *event = nullptr) override {
    emit mousePressed(event);
  }
  void mouseMoveEvent(QMouseEvent *event = nullptr) override {
    emit mouseMoved(event);
  }
  void dragEnterEvent(QDragEnterEvent *event = nullptr) override {
    emit dragEntered(event);
  }
  void dragLeaveEvent(QDragLeaveEvent *event = nullptr) override {
    emit dragLeaved(event);
  }
  void dragMoveEvent(QDragMoveEvent *event = nullptr) override {
    emit dragMoved(event);
  }
  void dropEvent(QDropEvent *event = nullptr) override { emit droped(event); }

  void itemChanged(QListWidgetItem *item) {
    Q_UNUSED(item);
    updateContent();
  }

  //  void enterEvent(QEnterEvent *event) override;
  //  void leaveEvent(QEvent *event) override;

 private slots:
  // void lineEditCurrHPFinished();

  // void mouseMoved(QMouseEvent *event = nullptr);

 private:
  Ui::CombatantWidget *ui;

  MyMenuWidget *_listWidget_effect = new MyMenuWidget(this);
  pf2e_manager::Combatant *_combatant = nullptr;

  QString _base_style{
      "QWidget#CombatantWidget {"
      "border-radius: 30px;"
      "background-color: rgb(0,0,0);"
      "}"
      "QLabel{"
      "font: bold 20px;"
      "color: white;"
      "}"};

  QString _highlight_style{
      "QWidget#CombatantWidget {"
      "border-radius: 30px;"
      " background-color: red; "
      "}"
      "QLabel{"
      "font: bold 20px;"
      "color: white;"
      "}"};

  QString _hover_style{
      "QWidget#CombatantWidget {"
      " background-color: ; "
      "}"
      "QLabel{"
      "font: bold 20px;"
      "color: white;"
      "}"};

  QString _model_style{
      "QWidget#CombatantWidget {"
      "border-radius: 30px;"
      " background-color: qconicalgradient(cx:0, cy:0, angle:135, stop:0 "
      "rgba(255, 255, 0, 69), stop:0.375 rgba(255, 255, 0, 69), stop:0.423533 "
      "rgba(251, 255, 0, 145), stop:0.45 rgba(247, 255, 0, 208), stop:0.477581 "
      "rgba(255, 244, 71, 130), stop:0.518717 rgba(255, 218, 71, 130), "
      "stop:0.55 rgba(255, 255, 0, 255), stop:0.57754 rgba(255, 203, 0, 130), "
      "stop:0.625 rgba(255, 255, 0, 69), stop:1 rgba(255, 255, 0, 69));"
      "}"
      "QLabel{"
      "font: bold 20px;"
      "color: black;"
      "}"};

  QString _label_active_style{
      "QLabel{"
      // "font: bold;"
      "background-color: rgba(113, 237, 255, 1);"
      "}"};
  QString _label_disable_style{
      "QLabel{"
      "background-color: rgba(3, 70, 128, 0.4);"
      "}"};
};
#endif  // COMBATANTWIDGET_H
