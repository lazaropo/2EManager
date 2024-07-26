#ifndef MYMENUWIDGET_H
#define MYMENUWIDGET_H

#include <QMenu>
#include <QMouseEvent>
#include <QTextBrowser>
#include <QWidget>
#include <QtWidgets>

#include "EffectListWidgetItem.h"

class MyMenuWidget : public QListWidget {
 public:
  explicit MyMenuWidget(QWidget* item = nullptr) : QListWidget(item) {
    // setContextMenuPolicy(Qt::ActionsContextMenu);
  }

  void setUI(std::function<void(QLayout*)> fp) { addTextBrowser = fp; }

  void setFrame(QLayout* frame) { _frame = frame; }

 private slots:
  void keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Escape) {
      if (_item)
        delete _item;
      else
        return;
      // if (_layout)
      //   delete _layout;
      // else
      //   return;
      _item = nullptr;
      //_layout = nullptr;
    }
  };

 protected:
  void contextMenuEvent(QContextMenuEvent* event) override {
    QMenu menu(this->parentWidget());
    QAction* show_description = menu.addAction("Get Discripttion");
    QAction* heal_command = menu.addAction("makeSomethingElse");

    QAbstractItemDelegate::connect(
        show_description, &QAction::triggered, [=]() {
          if (!_item) setTextBrowser();
          _item->setText(QString::fromStdString(
              (*(dynamic_cast<EffectListWidgetItem*>(currentItem())
                     ->getEffect()))
                  ->what()));
          _frame->addWidget(_item);
          // this->parentWidget()->setLayout(_frame->layout());
        });

    QAbstractItemDelegate::connect(heal_command, &QAction::triggered, [=]() {
      if (!_item) setTextBrowser();
      _item->setText(QString::fromStdString("HEAL COMMAND"));
      _frame->addWidget(_item);
      // this->parentWidget()->setLayout(_frame->layout());
    });

    menu.exec(event->globalPos());
  }

  void setTextBrowser() {
    if (_item /*|| _layout*/) return;

    //_layout = new QVBoxLayout(_frame);
    // _layout->setGeometry(_frame->geometry());
    // _layout->setContentsMargins(_frame->contentsMargins());
    _item = new QTextBrowser(this->parentWidget());
    // _item->setGeometry(QRect(_frame->x(),
    //                          _frame->y(),
    //                              _frame->x()+_frame->width(),
    //                           _frame->y() + _frame->height()));
    // _item->setGeometry(_frame->geometry());
    // _item->setContentsMargins(_frame->contentsMargins());
    //_layout->addWidget(_item);
    QObject::connect(_item, SIGNAL(keyPressed()), _item, SLOT(onKeyPressed()));
  }

  // QVBoxLayout* _layout = nullptr;
  QTextBrowser* _item = nullptr;
  QLayout* _frame = nullptr;
  std::function<void(QLayout*)> addTextBrowser;
};

#endif  // MYMENUWIDGET_H
