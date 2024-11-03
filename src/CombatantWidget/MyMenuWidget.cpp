#ifndef _MY_MENU_WIDGET_CPP_
#define _MY_MENU_WIDGET_CPP_

#include "MyMenuWidget.h"

MyMenuWidget::MyMenuWidget(QWidget* item) : QListWidget(item) { setSpacing(1); }

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
  menu.setStyleSheet(_menu_style);
  QAction* show_description = menu.addAction("Get Discription");
  QListWidgetItem* instance = currentItem();
  pf2e_manager::EffectBase* picked_effect = nullptr;
  if(instance)
      picked_effect = dynamic_cast<EffectListWidgetItem*>(instance)->getEffect();
  else return;

  bool is_active = picked_effect->isActive();
  //if (picked_effect)
  //  is_active = picked_effect->isActive();
  // else
  //   return;

  QAction* do_undo_effect =
      menu.addAction(is_active ? "Remove Effect" : "Activate Effect");

  QAbstractItemDelegate::connect(show_description, &QAction::triggered, [=]() {
    if (!_item) setTextBrowser();
    _item->setText(QString::fromStdString((picked_effect->getDescription())));
  });
  QAbstractItemDelegate::connect(do_undo_effect, &QAction::triggered, [=]() {
    if (is_active)
      picked_effect->removeEffect();
    else
      picked_effect->activateEffect();
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
  _item->setStyleSheet(_text_browser_style);
}

#endif
