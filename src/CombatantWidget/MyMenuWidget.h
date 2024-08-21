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

  QString _item_base_style =
      "font: 14px;"
      "QTextBrowser{"
      "border-radius: 5px;"
      "background-color: rgb(250, 218, 221);"
      "}";
};

#endif  // MYMENUWIDGET_H
