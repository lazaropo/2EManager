#ifndef MANAGERWIDGET_H
#define MANAGERWIDGET_H

#include <QDir>
#include <QListWidget>
#include <QWidget>

#include "../CombatantDialog/combatantdialog.h"
#include "../CombatantWidget/combatantwidget.h"
#include "../EffectDialog/EffectDialog.h"
#include "../Model/Controller.h"
#include "../ValueInputDialog/valueinputdialog.h"
#include "dragndropqwidget.h"
#include "dragndropqwidget_commands.h"

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
//#include <boost/log/utility/init/common_attributes.hpp>
//#include <boost/log/utility/init/to_file.hpp>
#include "boost/date_time/posix_time/posix_time.hpp"
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

// #ifdef _WINDOWS
// #include <windows.h>

// // https://habr.com/ru/articles/332626/
// static LONG WINAPI vectoredExceptionHandler(struct _EXCEPTION_POINTERS *_exception_info)
// {
//     if (!execution_context
//         || _exception_info->ExceptionRecord->ExceptionCode == DBG_PRINTEXCEPTION_C
//         || _exception_info->ExceptionRecord->ExceptionCode == 0xE06D7363L /* C++ exception */
//     )
//         return EXCEPTION_CONTINUE_SEARCH;

//     reinterpret_cast<ExecutionContextStruct *>(static_cast<ExecutionContext *>(execution_context))
//         ->dirty
//         = true;
//     reinterpret_cast<ExecutionContextStruct *>(static_cast<ExecutionContext *>(execution_context))
//         ->exception_type
//         = _exception_info->ExceptionRecord->ExceptionCode;
//     longjmp(execution_context->environment, 0);
// }

// #define HW_TO_SW_CONVERTER_UNIQUE_NAME(NAME, LINE) NAME##LINE
// #define HW_TO_SW_CONVERTER_INTERNAL(NAME, LINE) \
//     ExecutionContext HW_TO_SW_CONVERTER_UNIQUE_NAME(NAME, LINE); \
//     if (setjmp(HW_TO_SW_CONVERTER_UNIQUE_NAME(NAME, LINE).environment)) \
//     throw HwException(HW_TO_SW_CONVERTER_UNIQUE_NAME(NAME, LINE))
// #define HW_TO_SW_CONVERTER() HW_TO_SW_CONVERTER_INTERNAL(execution_context, __LINE__)

// #endif

namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace attrs = boost::log::attributes;
namespace keywords = boost::log::keywords;
namespace sys = boost::system;

BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(my_logger, src::logger_mt)
// auto exception_handler_handle = AddVectoredExceptionHandler(1, vectoredExceptionHandler);
inline void make_logger_record(/*std::exception &ex*/);
inline void print_log(std::exception &ex);

inline void my_terminate_handler()
{
    try {
        //logging::add_console_log()->set_filter(expr::attr<int>("Severity") >= 4);
        QDir dir("./log/signals/");
        if (!dir.exists())
            dir.mkpath(".");

        std::fstream log("./log/signals/logger_signals_"
                             + to_iso_string(boost::posix_time::second_clock::local_time()) + ".log",
                         std::ios::in | std::ios::out | std::ios::trunc);
        if (log.is_open()) {
            log << "Stack Trace: " << std::endl << boost::stacktrace::stacktrace() << std::endl;
        } else
            // logging::formatter formatter
            //     = expr::stream << expr::attr<unsigned int>("LineID") << " : "
            //                    << expr::format_date_time<boost::posix_time::ptime>("TimeStamp",
            //                                                                        "%Y-%m-%d %H:%M:%S")
            //                    << " *" << expr::attr<int>("Severity") << "* " << expr::message;

            // logging::add_file_log("complete_signals_%N.log")->set_formatter(formatter);

            // auto sink = boost::make_shared<sinks::text_file_backend>(
            //     keywords::file_name = "file.log",
            //     keywords::target_file_name = "file_signals_%5N.log",
            //     keywords::rotation_size = 5 * 1024 * 1024,
            //     keywords::time_based_rotation = sinks::file::rotation_at_time_point(12, 0, 0));

            // boost::shared_ptr<logging::core> core = logging::core::get();

            // typedef sinks::synchronous_sink<sinks::text_file_backend> sink_t;
            // boost::shared_ptr<sink_t> p_sink(new sink_t(sink));

            // core->add_sink(p_sink);

            // Register common attributes
            //logging::add_common_attributes();

            // Here we go, we can write logs
            // src::logger lg;
            // lg.set_formatter();
            // BOOST_LOG(lg) // << "Description: " ex.what() << std::endl
            //     << std::endl
            //     << "Stack Trace: " << std::endl
            //     << boost::stacktrace::stacktrace() << std::endl;
            std::cerr << boost::stacktrace::stacktrace() << std::endl
                      << to_iso_string(boost::posix_time::second_clock::local_time());

    } catch (...) {
    }
    std::abort();
}
// BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(my_logger, src::logger_mt)
// BOOST_LOG_GLOBAL_LOGGER_DEFAULT(my_logger, src::logger_mt)
// ManagerPF2E_static.lib(managerwidget.cpp.obj):-1: error: LNK2019: ббл«Є  ­  ­Ґа §аҐиҐ­­л© ў­Ґи­Ё© бЁ¬ў®« "public: __cdecl CombatantDialog::CombatantDialog(class pf2e_manager::Combatant * *,class QWidget *)" (??0CombatantDialog@@QEAA@PEAPEAVCombatant@pf2e_manager@@PEAVQWidget@@@Z) ў дг­ЄжЁЁ "private: void __cdecl ManagerWidget::on_pushButton_create_combatant_clicked(void)" (?on_pushButton_create_combatant_clicked@ManagerWidget@@AEAAXXZ).
// ManagerPF2E_static.lib(managerwidget.cpp.obj):-1: error: LNK2019: ббл«Є  ­  ­Ґа §аҐиҐ­­л© ў­Ґи­Ё© бЁ¬ў®« "public: virtual __cdecl CombatantDialog::~CombatantDialog(void)" (??1CombatantDialog@@UEAA@XZ) ў дг­ЄжЁЁ "private: void __cdecl ManagerWidget::on_pushButton_create_combatant_clicked(void)" (?on_pushButton_create_combatant_clicked@ManagerWidget@@AEAAXXZ).
// ManagerPF2E_static.lib(managerwidget.cpp.obj):-1: error: LNK2019: ббл«Є  ­  ­Ґа §аҐиҐ­­л© ў­Ґи­Ё© бЁ¬ў®« "public: __cdecl pf2e_manager::Model::Model(class std::function<int __cdecl(class pf2e_manager::SubjectBase *,class pf2e_manager::SubjectBase *,class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const &)>)" (??0Model@pf2e_manager@@QEAA@V?$function@$$A6AHPEAVSubjectBase@pf2e_manager@@0AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z@std@@@Z) ў дг­ЄжЁЁ "public: __cdecl pf2e_manager::Controller::Controller(class std::function<int __cdecl(class pf2e_manager::SubjectBase *,class pf2e_manager::SubjectBase *,class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const &)>)" (??0Controller@pf2e_manager@@QEAA@V?$function@$$A6AHPEAVSubjectBase@pf2e_manager@@0AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z@std@@@Z).
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// enum severity_level { normal, notification, warning, error, critical };

// class my_logger_mt : public src::basic_composite_logger<
//                          char,
//                          my_logger_mt,
//                          src::multi_thread_model<boost::shared_mutex>,
//                          src::features<src::severity<severity_level>, src::exception_handler> >
// {
//     BOOST_LOG_FORWARD_LOGGER_MEMBERS(my_logger_mt)
// };

// BOOST_LOG_INLINE_GLOBAL_LOGGER_INIT(my_logger, my_logger_mt)
// {
//     my_logger_mt lg;

//     // Set up exception handler: all exceptions that occur while
//     // logging through this logger, will be suppressed
//     lg.set_exception_handler(logging::make_exception_suppressor());

//     return lg;
// }

// inline void logging_function()
// {
//     // This will not throw
//     BOOST_LOG_SEV(my_logger::get(), normal) << "Hello, world";
// }
//+++++++++++++++++++++++++++++++++++++++++++++++
// struct my_handler
// {
//     typedef void result_type;

//     void operator()(std::runtime_error const &e) const
//     {
//         src::logger_mt &lg = my_logger::get();
//         BOOST_LOG(lg) << "std::runtime_error: " << e.what() << std::endl;
//     }
//     void operator()(std::logic_error const &e) const
//     {
//         src::logger_mt &lg = my_logger::get();
//         BOOST_LOG(lg) << "std::logic_error: " << e.what() << std::endl;
//         throw;
//     }
//     void operator()(std::exception const &e) const
//     {
//         src::logger_mt &lg = my_logger::get();
//         BOOST_LOG(lg) << "std::exception-general: " << e.what() << std::endl;
//         throw;
//     }
// };

// inline void init_exception_handler()
// {
//     // Setup a global exception handler that will call my_handler::operator()
//     // for the specified exception types

//     logging::core::get()->set_exception_handler(
//         logging::make_exception_handler<std::runtime_error, std::logic_error>(my_handler()));
//     //  BOOST_LOG(my_logger::get()) << "std::exception-general: " << e.what() << std::endl;
// }

// inline void init()
// {
//     logging::add_file_log(keywords::file_name = "sample_%N.log",
//                           keywords::rotation_size = 10 * 1024 * 1024,
//                           keywords::time_based_rotation = sinks::file::rotation_at_time_point(0,
//                                                                                               0,
//                                                                                               0),
//                           keywords::format = "[%TimeStamp%]: %Message%");
//     // logging::add_file_log("sample.log");
//     logging::add_common_attributes();
//     logging::core::get()->set_filter(logging::trivial::severity >= logging::trivial::info);
// }

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

  QPoint _mouseStartPosition; // <------------- possibly dummy var
};
#endif  // MANAGERWIDGET_H
