#ifndef COMBATANTWIDGET_H
#define COMBATANTWIDGET_H

#include <QDrag>
#include <QListWidget>
#include <QToolTip>
#include <QWidget>
#include <QtWidgets>

// #include "EffectListWidgetItem.h"
#include <boost/log/trivial.hpp>

#include "../CombatantWidget/MyMenuWidget.h"
#include "../Model/CommandsImplementation.h"
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

  pf2e_manager::Combatant *getCombatant() {
    // if (!this)
    //     throw std::logic_error("CombatantWidget doent exists");
    return _combatant;
  }
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

  MyMenuWidget *_listWidget_effect = nullptr;
  pf2e_manager::Combatant *_combatant = nullptr;

  static constexpr int _init_width = 1150;
  static constexpr int _init_height = 155;

  QString _base_style{
      "QWidget#CombatantWidget {"
      "border-radius: 30px;"
      "background-color: rgb(242, 204, 143);"
      "}"
      "QLabel{"
      "font: bold 20px;"
      "color: black;"
      "}"
      "QLineEdit{"
      "border-radius: 10px;"
      "color: black;"
      "font: bold 16px;"
      "background-color: rgb(166, 138, 100);"
      "}"};

  QString _highlight_style{
      "QWidget#CombatantWidget {"
      "border-radius: 30px;"
      " background-color: rgb(65, 72, 51); "
      "}"
      "QLabel{"
      "font: bold 20px;"
      "color: black;"
      "}"
      "QLineEdit{"
      "border-radius: 10px;"
      "font: bold 16px;"
      "color: black;"
      "background-color: rgb(164, 172, 134);"
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
      //  "background-color: rgb(8,36,0);"
      " background-color: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
      "stop:0 rgba(242, 204, 143, 1),"
      "stop:1 rgba(65, 72, 51, 1));"  // linear-gradient(90deg, rgba(8,36,0,1),
                                      // rgba(7,91,25,1), rgba(68,24,14,1));"
      "}"
      "QLabel{"
      "font: bold 20px;"
      "color: black;"
      "}"
      "QLineEdit{"
      "border-radius: 10px;"
      "font: bold 16px;"
      "color: black;"
      "background-color: rgb(242, 204, 143);"
      "}"};

  QString _list_widget_style{
      "QListWidget{"
      "font: 16px;"
      "color: black;"
      "border-radius: 5px;"
      "background-color: rgb(182, 173, 144);"
      "}"};

  QString _label_active_style{
      "QLabel{"
      "border-radius: 6px;"
      "font: 16px black;"
      "background-color: rgb(147, 102, 57);"
      "}"};
  QString _label_disable_style{
      "QLabel{"
      "border-radius: 6px;"
      "font: 16px black;"
      "background-color: rgb(164, 172, 134);"
      "}"};
};
#endif  // COMBATANTWIDGET_H
