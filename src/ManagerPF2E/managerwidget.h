#ifndef MANAGERWIDGET_H
#define MANAGERWIDGET_H

#include <QListWidget>
#include <QWidget>
#include <list>

#include "../CombatantDialog/combatantdialog.h"
#include "../CombatantWidget/combatantwidget.h"
#include "../EffectDialog/EffectDialog.h"
#include "../Model/Controller.h"
#include "../ValueInputDialog/valueinputdialog.h"
#include "dragndropqwidget.h"
#include "dragndropqwidget_commands.h"

#include <boost/log/common.hpp>
#include <boost/log/core/core.hpp>
#include <boost/log/core/record.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/sources/basic_logger.hpp>
#include <boost/log/sources/exception_handler_feature.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/utility/exception_handler.hpp>
#include <boost/shared_ptr.hpp>

#include <exception>
#include <iostream>

// BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(my_logger, src::logger_mt)

struct my_handler
{
    typedef void result_type;

    void operator()(std::runtime_error const &e) const
    {
        std::cout << "std::runtime_error: " << e.what() << std::endl;
    }
    void operator()(std::logic_error const &e) const
    {
        std::cout << "std::logic_error: " << e.what() << std::endl;
        throw;
    }
    void operator()(std::exception const &e) const
    {
        std::cout << "std::exception-general: " << e.what() << std::endl;
        throw;
    }
};

inline void init_exception_handler()
{
    // Setup a global exception handler that will call my_handler::operator()
    // for the specified exception types
    using namespace boost::log;
    core::get()->set_exception_handler(
        make_exception_handler<std::runtime_error, std::logic_error>(my_handler()));
}

QT_BEGIN_NAMESPACE
namespace Ui {
class ManagerWidget;
using namespace pf2e_manager;
}  // namespace Ui
QT_END_NAMESPACE

class ManagerWidget : public QWidget {
  Q_OBJECT

 public:
  ManagerWidget(QWidget *parent = nullptr);
  ~ManagerWidget();

 private:
  int getActionConfirmation(pf2e_manager::SubjectBase *sender,
                            pf2e_manager::SubjectBase *reciever,
                            const std::string &name);

 private slots:
  void on_pushButton_create_effect_clicked();

  // void setCurrent(QMouseEvent *event);

  void on_pushButton_create_combatant_clicked();

  //   void mousePressEvent(QMouseEvent* event);
  // void mouseMoveEvent(QMouseEvent *event);
  //  void mouseReleaseEvent(QMouseEvent *event);

  //  void dragEnterEvent(QDragEnterEvent *event);
  //  void dragMoveEvent(QDragMoveEvent *event);
  // void dropEvent(QDropEvent *event) override;

  // void on_widget_drag(QMouseEvent *event);

  void on_pushButton_create_command_clicked();

  void on_pushButton_create_order_clicked();

  void on_pushButton_turn_clicked();

  void on_pushButton_create_remove_clicked();

 private:
  Ui::ManagerWidget *ui;
  pf2e_manager::Controller *_controller;

  // QStandardItemModel _combatant_model;
  std::map<pf2e_manager::Combatant *, CombatantWidget *> _combatant_list;

  DragNDropQWidget *_box_combatants;
  DragNDropQWidgetCommands *_box_commands;

  bool _button_start_flag = false;

  QPoint _mouseStartPosition;  // <------------- possibly dummy var
};
#endif  // MANAGERWIDGET_H
