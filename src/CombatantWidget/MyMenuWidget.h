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
      this->parentWidget()->layout()->removeWidget(_item);
      if (_item)
        delete _item;
      else
        return;
      // if (_layout)
      //   delete _layout;
      // else
      //   return;
      _item = nullptr;
      delete _frame;
      _frame = nullptr;
      // _frame->setEnabled(false);
      //_layout = nullptr;
    }
  };

 protected:
  void contextMenuEvent(QContextMenuEvent* event) override {
    QMenu menu(this->parentWidget());
    QAction* show_description = menu.addAction("Get Discripttion");
    QAction* heal_command = menu.addAction("makeSomethingElse");
    QMenu* make_effect = menu.addMenu("Make Effect...");

    QAction* make_clumsy = menu.addAction("Make Clumsy");

    QAbstractItemDelegate::connect(
        show_description, &QAction::triggered, [=]() {
          if (!_item) setTextBrowser();
          _item->setText(QString::fromStdString(
              (*(dynamic_cast<EffectListWidgetItem*>(currentItem())
                     ->getEffect()))
                  ->what()));
          this->parentWidget()->layout()->addWidget(_item);
          // this->parentWidget()->setLayout(_frame->layout());
        });

    QAbstractItemDelegate::connect(heal_command, &QAction::triggered, [=]() {
      if (!_item) setTextBrowser();
      _item->setText(QString::fromStdString("HEAL COMMAND"));
      this->parentWidget()->layout()->addWidget(_item);
    });

    QAbstractItemDelegate::connect(make_clumsy, &QAction::triggered, [=]() {
      if (!_item) setTextBrowser();

      // _item->setText(QString::fromStdString(
      //     (*(dynamic_cast<EffectListWidgetItem*>(currentItem())
      //            ->getEffect()))
      //         ->what()));
      // this->parentWidget()->layout()->addWidget(_item);
    });

    menu.exec(event->globalPos());
  }

  void setTextBrowser() {
    if (_item /*|| _layout*/) return;

    _frame = new QVBoxLayout(this->parentWidget());
    // _layout->setGeometry(_frame->geometry());
    // _layout->setContentsMargins(_frame->contentsMargins());
    _item = new QTextBrowser(this->parentWidget());
    // _item->setGeometry(QRect(600,
    //                           10,
    //                               600+370,
    //                            10 + 140));
    _item->setFixedSize(370, 140);
    _frame->setSizeConstraint(QLayout::SetFixedSize);
    // _frame->setContentsMargins(600,
    //                            10,
    //                            600+370,
    //                            10 + 140);
    _frame->setContentsMargins(600, 10, 30, 30);

    _frame->addWidget(_item);
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
