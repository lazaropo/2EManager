#ifndef _MY_MENU_WIDGET_CPP_
#define _MY_MENU_WIDGET_CPP_

#include "MyMenuWidget.h"

MyMenuWidget::MyMenuWidget(QWidget* item) : QListWidget(item) {}

MyMenuWidget::~MyMenuWidget() {
  if (_item) delete _item;
  if (_frame) delete _frame;
}

void MyMenuWidget::keyPressEvent(QKeyEvent* event) {
  if (event->key() == Qt::Key_Escape) {
    if (_item)
      delete _item;
    else
      return;

    _item = nullptr;
    delete _frame;
    _frame = nullptr;
  }
}

void MyMenuWidget::contextMenuEvent(QContextMenuEvent* event) {
  QMenu menu(this->parentWidget());
  QAction* show_description = menu.addAction("Get Discripttion");
  auto eff = dynamic_cast<EffectListWidgetItem*>(currentItem())->getEffect();

  bool is_active = false;
  if (eff)
    is_active = eff->isActive();
  else
    return;

  QAction* do_undo_effect =
      menu.addAction(is_active ? "Remove Effect" : "Activate Effect");

  QAbstractItemDelegate::connect(show_description, &QAction::triggered, [=]() {
    if (!_item) setTextBrowser();
    _item->setText(QString::fromStdString((eff->getDescription())));
  });
  QAbstractItemDelegate::connect(do_undo_effect, &QAction::triggered, [=]() {
    if (is_active)
      eff->removeEffect();
    else
      eff->activateEffect();
    emit itemChanged(currentItem());
  });

  menu.exec(event->globalPos());
}

void MyMenuWidget::setTextBrowser() {
  if (_item) return;

  _item = new QTextBrowser(this->parentWidget());
  _item->setGeometry(QRect(600, 10, 400, 140));
  _item->setStyleSheet(_item_base_style);
  _item->show();
}

#endif
