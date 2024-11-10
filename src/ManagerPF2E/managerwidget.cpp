#include "managerwidget.h"

#include "ui_managerwidget.h"

// BOOST_LOG_GLOBAL_LOGGER_INIT(my_logger, src::logger_mt)
// {
//     src::logger_mt lg;
//     lg.add_attribute("StopWatch", attrs::timer());
//     return lg;
// }

ManagerWidget::ManagerWidget(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::ManagerWidget),
      _controller(new pf2e_manager::Controller(std::bind(
          &ManagerWidget::getActionConfirmation, this, std::placeholders::_1,
          std::placeholders::_2, std::placeholders::_3))),
      _box_combatants(
          new DragNDropQWidget(_controller, &_combatant_list, this)),
      _box_commands(new DragNDropQWidgetCommands(_controller, this)) {
    make_logger_record();

    try {
        ui->setupUi(this);

        using namespace pf2e_manager;

        _box_combatants->setArea(ui->scrollArea_combatants);
        _box_commands->setArea(ui->scrollArea_commands);

        for (auto it : *_controller->getCombatants())
            _box_combatants->addWidget(it);

        ui->scrollArea_combatants->setWidget(_box_combatants);
        ui->scrollArea_commands->setWidget(_box_commands);

        ui->scrollArea_combatants->setAttribute(Qt::WA_StyledBackground);
        ui->scrollArea_combatants->setBackgroundRole(QPalette::Window);

        ui->scrollArea_commands->setAttribute(Qt::WA_StyledBackground);
        ui->scrollArea_commands->setBackgroundRole(QPalette::Window);

        _box_combatants->updateContent();

        _box_combatants->setModelCurrentComatant(_controller->getCurrent());
    } catch (std::exception &ex) {
    }
}

ManagerWidget::~ManagerWidget() {
  delete ui;
  delete _controller;
}

void ManagerWidget::on_pushButton_create_effect_clicked() {
  auto current_widget = _box_combatants->getCurrentWidget();
  // UNCOMMENT IT!!!
  // if (!current_widget) return;

  EffectDialog dialog =
      /*new */ EffectDialog(_controller, current_widget->getCombatant(), this);
  if (dialog.exec() == QDialog::Rejected) return;

  current_widget->updateContent();
}

void ManagerWidget::on_pushButton_create_combatant_clicked() {
  pf2e_manager::Combatant *body;
  CombatantDialog dialog(&body);
  if (dialog.exec() == QDialog::Accepted) {
    _controller->addCombatant(body);
    _box_combatants->addWidget(body);
  }
}

void ManagerWidget::on_pushButton_create_command_clicked() {
  pf2e_manager::CommandBase *command;
  CommandDialog dialog(&command, _controller);
  // command have to be set in collection from model
  if (dialog.exec() == QDialog::Rejected) return;
  _box_combatants->updateContent();

  _box_commands->addCommand(command);
}

void ManagerWidget::on_pushButton_create_order_clicked() {
  _controller->sortByInit();
  _box_combatants->setModelCurrentComatant(_controller->getCurrent());
  _box_combatants->updateContent();
}

void ManagerWidget::on_pushButton_turn_clicked() {
  //  if (_button_start_flag) {
  //    _controller->nextTurn();

  //    ui->pushButton_turn->setText("Start of Turn");
  //    ui->pushButton_turn->setStyleSheet(
  //        "QPushButton{"
  //        "font: bold 28px;"
  //        "color: black; "
  //        "background-color: rgb(246, 97, 81);"
  //        "}");
  //  } else {
  _controller->nextTurn();
  _box_combatants->setModelCurrentComatant(_controller->getCurrent());

  // ui->pushButton_turn->setText("Next Turn");
  //  ui->pushButton_turn->setStyleSheet(
  //      "QPushButton {"
  //      "font: bold 28px; "
  //      "color: black;"
  //      "background-color: rgb(143, 240, 164);"
  //      "}");
  // }

  _button_start_flag = !_button_start_flag;

  _box_combatants->updateContent();
  _box_commands->updateContent();
}

void make_logger_record()
{
    // Initialize sinks
    QDir dir("./log/exceptions/");
    if (!dir.exists())
        dir.mkpath(".");

    logging::add_console_log()->set_filter(expr::attr<int>("Severity") >= 4);

    logging::formatter formatter
        = expr::stream << expr::attr<unsigned int>("LineID") << " : "
                       << expr::format_date_time<boost::posix_time::ptime>("TimeStamp",
                                                                           "%Y-%m-%d %H:%M:%S")
                       << " *" << expr::attr<int>("Severity") << "* "
                       << expr::message; /*<< "Exception description: "
                       << boost::stacktrace::stacktrace::from_current_exception() << std::endl
                       << "Stack Trace: " << boost::stacktrace::stacktrace() << std::endl;*/

    //logging::add_file_log("./log/complete_%N.log")->set_formatter(formatter);

    // Create a text file sink
    using file_sink = sinks::synchronous_sink<sinks::text_file_backend>;
    boost::shared_ptr<file_sink> sink(
        new file_sink(keywords::file_name = "./log/exceptions/file.log",
                      keywords::target_file_name = "./log/exceptions/file_%5N.log",
                      keywords::rotation_size = 5 * 1024 * 1024,
                      keywords::open_mode = std::ios_base::in | std::ios_base::out
                                            | std::ios_base::trunc));

    sink->locked_backend()->set_file_collector(
        sinks::file::make_collector(keywords::target = "log/exceptions/",
                                    keywords::max_size = 16 * 1024 * 1024,
                                    keywords::min_free_space = 100 * 1024 * 1024,
                                    keywords::max_files = 512));

    // Upon restart, scan the directory for files matching the file_name pattern
    sink->locked_backend()->scan_for_files();

    sink->set_formatter(formatter);

    // logging::add_file_log(sink->locked_backend()->get_current_file_name())->set_formatter(formatter);
    //boost::filesystem::path filename = sink->locked_backend()->get_current_file_name();
    // sink->locked_backend()->add_file(boost::make_shared<std::ofstream>(filename));

    logging::core::get()->add_sink(sink);

    // core->add_sink(sink);

    logging::add_common_attributes();

    // // Here we go, we can write logs
    // src::logger lg;

    // BOOST_LOG(lg) << "Exception description: " << ex.what() << std::endl
    //               << "Stack Trace: " << boost::stacktrace::stacktrace() << std::endl;
}

void ManagerWidget::on_pushButton_create_remove_clicked() {
    try {
        auto widget = _combatant_list.extract(_box_combatants->getCurrentWidget()->getCombatant());
        if (widget.mapped() && widget.mapped()->getCombatant()) {
            _controller->removeCombatant(widget.mapped()->getCombatant());
            delete widget.mapped();
            _box_combatants->updateContent();
        }
    } catch (std::exception &ex) {
        // make_logger_record(ex);
        src::logger_mt &lg = my_logger::get();
        // auto record = lg.open_record(std::string() + "Exception description: " + ex.what() + '\n'
        //                              + "Stack Trace: " + to_string(boost::stacktrace::stacktrace())
        //                              + '\n');
        // if (record) {
        //     logging::record_ostream strm(record);
        //     strm << "Exception description: " << ex.what() << std::endl
        //          << "Stack Trace: " << boost::stacktrace::stacktrace() << std::endl;
        //     strm.flush();
        //     lg.push_record(boost::move(record));
        // }
        BOOST_LOG(lg) << "Exception description: " << ex.what() << std::endl
                      << "Stack Trace: " << boost::stacktrace::stacktrace() << std::endl;
    }
}

int ManagerWidget::getActionConfirmation(pf2e_manager::SubjectBase *sender,
                                         pf2e_manager::SubjectBase *reciever,
                                         const std::string &name) {
  int ret = 0;
  const std::string sender_name = sender ? sender->getName() : "User";
  if (!reciever)
    throw std::logic_error(
        "ManagerWidget: getActionConfirmation: Reciever is null.");
  ValueInputDialog dialog(&ret, sender_name, reciever->getName(), name);
  dialog.exec();

  // _box_commands->addCommand(_controller->getCommands().back());

  return ret;
}
