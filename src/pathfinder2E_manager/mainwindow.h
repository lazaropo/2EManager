#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "../Model/Controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
using logic = pf2e_manager;
}  // namespace Ui
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  pf2e_manager::Controller *_controller;
};
#endif  // MAINWINDOW_H
