#ifndef MYMENUWIDGET_H
#define MYMENUWIDGET_H

#include <QMenu>
#include <QMouseEvent>
#include <QTextBrowser>
#include <QWidget>
#include <QtWidgets>

#include "Controller.h"
#include "EffectListWidgetItem.h"

class MyMenuWidget : public QListWidget {
  Q_OBJECT
 public:
  explicit MyMenuWidget(QWidget* item = nullptr);
  ~MyMenuWidget();

  void setUI(std::function<void(QLayout*)> fp) { addTextBrowser = fp; }

  // void setFrame(QLayout* frame) { _frame = frame; }

  void setInitWidth(int width) { _init_width = width; }

  void setInitHeight(int height) { _init_height = height; }

  void setController(pf2e_manager::Controller* controller) {
    _controller = controller;
  }

 private slots:
  void keyPressEvent(QKeyEvent* event) override;

 protected:
  void contextMenuEvent(QContextMenuEvent* event) override;

  void setTextBrowser();

 protected:
  QTextBrowser* _item = nullptr;
  // QLayout* _frame = nullptr;
  std::function<void(QLayout*)> addTextBrowser;

  pf2e_manager::Controller* _controller = nullptr;

  int _init_height = 0;
  int _init_width = 0;

  const QString _item_base_style =
      "font: 14px;"
      "QTextBrowser{"
      "border-radius: 5px;"
      "background-color: rgb(138, 175, 189);"
      "}";
  const QString _text_browser_style =
      "QTextBrowser {"
      "background-color: rgb(194, 197, 170);"
      "font: 14px 'Arial';"
      "color: black;"
      "border-radius: 8px;"
      "}";
  const QString _menu_style =
      "QMenu {"
      "background-color: rgb(182, 173, 144);"
      "font: 16px 'Arial';"
      "color: black;"
      "}";
};

#endif  // MYMENUWIDGET_H
