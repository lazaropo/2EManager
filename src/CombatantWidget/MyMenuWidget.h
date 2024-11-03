#ifndef MYMENUWIDGET_H
#define MYMENUWIDGET_H

#include <QMenu>
#include <QMouseEvent>
#include <QTextBrowser>
#include <QWidget>
#include <QtWidgets>

#include "EffectListWidgetItem.h"

class MyMenuWidget : public QListWidget {
  Q_OBJECT
 public:
  explicit MyMenuWidget(QWidget* item = nullptr);
  ~MyMenuWidget();

  void setUI(std::function<void(QLayout*)> fp) { addTextBrowser = fp; }

  void setFrame(QLayout* frame) { _frame = frame; }

 private slots:
  void keyPressEvent(QKeyEvent* event) override;

 protected:
  void contextMenuEvent(QContextMenuEvent* event) override;

  void setTextBrowser();

 protected:
  QTextBrowser* _item = nullptr;
  QLayout* _frame = nullptr;
  std::function<void(QLayout*)> addTextBrowser;

  const QString _item_base_style = "font: 14px;"
                                   "QTextBrowser{"
                                   "border-radius: 5px;"
                                   "background-color: rgb(250, 218, 221);"
                                   "}";
  const QString _text_browser_style = "QTextBrowser {"
                                      "background-color: rgb(250, 238, 221);"
                                      "font: 14px 'Arial';"
                                      "color: black;"
                                      "border-radius: 8px;"
                                      "}";
  const QString _menu_style = "QMenu {"
                              "background-color: rgb(161,133,148);"
                              "font: 16px 'Arial';"
                              "color: black;"
                              //          "border-radius: 8px;"
                              "}";
};

#endif  // MYMENUWIDGET_H
