#ifndef _MY_MENU_WIDGET_CPP_
#define _MY_MENU_WIDGET_CPP_

#include "MyMenuWidget.h"

MyMenuWidget::MyMenuWidget(QWidget* item) : QListWidget(item) {
  setSpacing(1);
  _init_width = width();
  _init_height = height();
}

MyMenuWidget::~MyMenuWidget() {
  if (_item) delete _item;
  // if (_frame) delete _frame;
}

void MyMenuWidget::keyPressEvent(QKeyEvent* event) {
  if (event->key() == Qt::Key_Escape) {
    if (_item)
      delete _item;
    else
      return;

    _item = nullptr;
  }
}

void MyMenuWidget::contextMenuEvent(QContextMenuEvent* event) {
  QMenu menu(this->parentWidget());
  menu.setStyleSheet(_menu_style);
  QAction* show_description = menu.addAction("Get Discription");
  QListWidgetItem* instance = currentItem();
  pf2e_manager::EffectBase* picked_effect = nullptr;
  if (instance)
    picked_effect = dynamic_cast<EffectListWidgetItem*>(instance)->getEffect();
  else
    return;

  pf2e_manager::Combatant* combatant =
      dynamic_cast<pf2e_manager::Combatant*>(picked_effect->getReciever());
  bool is_active = picked_effect->isActive();
  // if (picked_effect)
  //   is_active = picked_effect->isActive();
  //  else
  //    return;

  QAction* do_undo_effect =
      menu.addAction(is_active ? "Disactivate Effect" : "Activate Effect");
  QAction* remove_effect = menu.addAction("Remove Effect");

  QAbstractItemDelegate::connect(show_description, &QAction::triggered, [=]() {
    if (!_item) setTextBrowser();
    _item->setText(QString::fromStdString((picked_effect->getDescription())));
  });
  QAbstractItemDelegate::connect(do_undo_effect, &QAction::triggered, [=]() {
    if (is_active)
      _controller->disableEffect(picked_effect, combatant);
    else
       _controller->activateEffect(picked_effect, combatant);
    emit itemChanged(currentItem());
  });
  QAbstractItemDelegate::connect(remove_effect, &QAction::triggered, [=]() {
    if (!combatant) return;

    int count = combatant->removeEffect(picked_effect);
    if (count == -1) return;
    removeItemWidget(item(count));
    emit itemChanged(nullptr);
  });

  menu.exec(event->globalPos());
}

void MyMenuWidget::setTextBrowser() {
  if (_item) return;

  QWidget* parent = this->parentWidget();
  _item = new QTextBrowser(parent);
  _item->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
  _item->setFocus();

  QRect my_rect = geometry();

  _item->setGeometry(
      QRect(my_rect.x() + 10, my_rect.y() + 10,
            my_rect.width() - 20 /*+ parent->width() - _init_width*/,
            my_rect.height() - 20 /*+ parent->height() - _init_height*/));
  // _item->setStyleSheet(_item_base_style);

  _item->setStyleSheet(_text_browser_style);

  _item->setWindowState(Qt::WindowState::WindowActive);

  // QObject::connect(_item, &QWidget::mouseDoubleClickEvent, [=](QKeyEvent
  // *event) {
  //     if(event && event->key() == Qt::Key_Escape )
  //       close();
  // });
  // hide();
  // if (parent)
  //     parent->layout()->addWidget(_item);
  // // layout()->addWidget(_item);
  _item->show();
}

#endif
