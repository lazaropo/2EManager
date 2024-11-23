#ifndef MANAGERWIDGET_H
#define MANAGERWIDGET_H

#include <QDir>
#include <QListWidget>
#include <QSizePolicy>
#include <QWidget>
#include <boost/log/attributes/timer.hpp>
#include <boost/log/common.hpp>
#include <boost/log/core/core.hpp>
#include <boost/log/core/record.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sources/basic_logger.hpp>
#include <boost/log/sources/exception_handler_feature.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_feature.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/exception_handler.hpp>
#include <boost/log/utility/setup/from_stream.hpp>
#include <boost/stacktrace/stacktrace.hpp>>

#include "../CombatantDialog/combatantdialog.h"
#include "../CombatantWidget/combatantwidget.h"
#include "../EffectDialog/EffectDialog.h"
#include "../Model/Controller.h"
#include "../ValueInputDialog/valueinputdialog.h"
#include "dragndropqwidget.h"
#include "dragndropqwidget_commands.h"
// #include <boost/log/utility/init/common_attributes.hpp>
// #include <boost/log/utility/init/to_file.hpp>
#include <boost/exception/all.hpp>
#include <boost/exception/exception.hpp>
#include <boost/exception/get_error_info.hpp>
#include <boost/log/expressions/formatters/date_time.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/system.hpp>
#include <exception>
#include <fstream>
#include <iostream>
#include <list>

#include "boost/date_time/posix_time/posix_time.hpp"

namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace attrs = boost::log::attributes;
namespace keywords = boost::log::keywords;
namespace sys = boost::system;

BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(my_logger, src::logger_mt)
// auto exception_handler_handle = AddVectoredExceptionHandler(1,
// vectoredExceptionHandler);
inline void init_logger(/*std::exception &ex*/);
inline void print_log(std::exception &ex);
inline void print_log(boost::exception &ex);

inline void my_terminate_handler() {
  try {
    // logging::add_console_log()->set_filter(expr::attr<int>("Severity") >= 4);
    QDir dir("./log/signals/");
    if (!dir.exists()) dir.mkpath(".");

    std::fstream log(
        "./log/signals/logger_signals_" +
            to_iso_string(boost::posix_time::second_clock::local_time()) +
            ".log",
        std::ios::in | std::ios::out | std::ios::trunc);
    if (log.is_open()) {
      log << "Stack Trace: " << std::endl
          << boost::stacktrace::stacktrace() << std::endl;
    } else
      std::cerr << boost::stacktrace::stacktrace() << std::endl
                << to_iso_string(boost::posix_time::second_clock::local_time());

  } catch (...) {
  }
  std::abort();
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

  // void resizeEvent(QResizeEvent* event) override;

  static void resizeLayout(QResizeEvent *event, QLayout *layout);

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
