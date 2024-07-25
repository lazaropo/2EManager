#ifndef MYMENUWIDGET_H
#define MYMENUWIDGET_H

#include <QMenu>
#include <QTextBrowser>
#include <QtWidgets>
// #include <QApplication>

#include <QWidget>

namespace {

#include "EffectListWidgetItem.h"
#include "combatantwidget.h"
}  // namespace
// QT_BEGIN_NAMESPACE
// namespace Ui {
// class MyMenuWidget;

//}
// QT_END_NAMESPACE

class MyMenuWidget : public QListWidget {
  Q_OBJECT
 public:
  explicit MyMenuWidget(QWidget* item = nullptr) : QListWidget(item) {
    // setContextMenuPolicy(Qt::ActionsContextMenu);
  }

  void setUI(CombatantWidget* other_ui) { ui = other_ui; }

 protected:
  void contextMenuEvent(QContextMenuEvent* event) override {
    QMenu menu(this->parentWidget());
    QAction* show_description = menu.addAction("Get Discripttion");
    QAction* heal_command = menu.addAction("makeSomethingElse");

    // QAction* action = menu.exec(event->globalPos());

    QAbstractItemDelegate::connect(
        show_description, &QAction::triggered, [=]() {
          QTextBrowser* item = new QTextBrowser(this->parentWidget());
          item->setText(QString::fromStdString(
              (*(dynamic_cast<EffectListWidgetItem*>(currentItem())
                     ->getEffect()))
                  ->what()));
          ui->addTextBrowser(item);
        });

    QAbstractItemDelegate::connect(heal_command, &QAction::triggered, [=]() {
      QTextBrowser* item_command = new QTextBrowser(this->parentWidget());
      item_command->setText(QString::fromStdString("HEAL COMMAND"));
      ui->addTextBrowser(item);
    });
    // menu.show();
    menu.exec(event->globalPos());
  }

  CombatantWidget* ui;
};

#endif  // MYMENUWIDGET_H
