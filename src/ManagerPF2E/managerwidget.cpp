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
    init_logger();

    try {
        ui->setupUi(this);

        using namespace pf2e_manager;

        QSizePolicy policy_combatants(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
QSizePolicy policy_commands(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);
        _box_combatants->setSizePolicy(policy_combatants);
        _box_commands->setSizePolicy(policy_commands);

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
        print_log(ex);
    } catch (boost::exception &ex) {
        print_log(ex);
    }
}

ManagerWidget::~ManagerWidget() {
  delete ui;
  delete _controller;
}

void ManagerWidget::on_pushButton_create_effect_clicked() {
    try {
        auto current_widget = _box_combatants->getCurrentWidget();
        // UNCOMMENT IT!!!
        // if (!current_widget) return;

        EffectDialog dialog =
            /*new */ EffectDialog(_controller, current_widget->getCombatant(), this);
        if (dialog.exec() == QDialog::Rejected)
            return;

        current_widget->updateContent();
    } catch (std::exception &ex) {
        print_log(ex);
    } catch (boost::exception &ex) {
        print_log(ex);
    }
}

void ManagerWidget::on_pushButton_create_combatant_clicked() {
    try {
        pf2e_manager::Combatant *body;
        CombatantDialog dialog(&body);
        if (dialog.exec() == QDialog::Accepted) {
            _controller->addCombatant(body);
            _box_combatants->addWidget(body);
        }
    } catch (std::exception &ex) {
        print_log(ex);
    } catch (boost::exception &ex) {
        print_log(ex);
    }
}

void ManagerWidget::on_pushButton_create_command_clicked() {
    if (_controller->getCombatants()->empty())
        return;
    try {
        pf2e_manager::CommandBase *command;

        CommandDialog dialog(&command, _controller);
        // command have to be set in collection from model
        if (dialog.exec() == QDialog::Rejected)
            return;
        _box_combatants->updateContent();

        _box_commands->addCommand(command);
    } catch (std::exception &ex) {
        print_log(ex);
    } catch (boost::exception &ex) {
        print_log(ex);
    }
}

void ManagerWidget::on_pushButton_create_order_clicked() {
    try {
        _controller->sortByInit();
        _box_combatants->setModelCurrentComatant(_controller->getCurrent());
        _box_combatants->updateContent();
    } catch (std::exception &ex) {
        print_log(ex);
    } catch (boost::exception &ex) {
        print_log(ex);
    }
}

void ManagerWidget::on_pushButton_turn_clicked() {
    try {
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
    } catch (std::exception &ex) {
        print_log(ex);
    } catch (boost::exception &ex) {
        print_log(ex);
    }
}

void init_logger()
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

void print_log(std::exception &ex)
{
    src::logger_mt &lg = my_logger::get();
    BOOST_LOG(lg) << "Exception description: " << ex.what() << std::endl
                  << "Stack Trace: " << boost::stacktrace::stacktrace() << std::endl;
}

void print_log(boost::exception &ex)
{
    src::logger_mt &lg = my_logger::get();
    typedef boost::error_info<struct tag_my_info, int> my_info;
    // boost::error_info::value_type *info = boost::get_error_info<my_info>(ex);
    if (int const *mi = boost::get_error_info<my_info>(ex))
        BOOST_LOG(lg) << "Boost exception info: " << *mi << std::endl
                      << "Stack Trace: " << boost::stacktrace::stacktrace() << std::endl;
}

void ManagerWidget::on_pushButton_create_remove_clicked() {
    try {
        auto widget = _combatant_list.extract(_box_combatants->getCurrentWidget()->getCombatant());
        if (!widget)
            return;
        CombatantWidget* node = widget.mapped();
        if (node && node->getCombatant()) {
            _controller->removeCombatant(node->getCombatant());
            delete node;
            _box_combatants->updateContent();
        }
    } catch (std::exception &ex) {
        print_log(ex);
    } catch (boost::exception &ex) {
        print_log(ex);
    }
}

int ManagerWidget::getActionConfirmation(pf2e_manager::SubjectBase *sender,
                                         pf2e_manager::SubjectBase *reciever,
                                         const std::string &name) {
  int ret = 0;
  try {
      const std::string sender_name = sender ? sender->getName() : "User";
      if (!reciever)
          throw std::logic_error("ManagerWidget: getActionConfirmation: Reciever is null.");
      ValueInputDialog dialog(&ret, sender_name, reciever->getName(), name);
      dialog.exec();
  } catch (std::exception &ex) {
      print_log(ex);
  } catch (boost::exception &ex) {
      print_log(ex);
  }

  // _box_commands->addCommand(_controller->getCommands().back());

  return ret;
}

void ManagerWidget::resizeLayout(QResizeEvent* event, QLayout* layout){
    QRect layout_rect = layout->geometry();
    // QSize buttons_layout_size = ui->buttons_layout->size();
    double width_coeff = static_cast<double>(event->size().width()) / qMax(event->oldSize().width(), 1);
    double height_coeff =static_cast<double>(event->size().height()) / qMax(event->oldSize().height(), 1);
    if(width_coeff > 1.03 || width_coeff < 0.97 || height_coeff > 1.03 || height_coeff < 0.97){

        int width =  width_coeff * layout_rect.width();
        int height = height_coeff * layout_rect.height();


        int x = layout_rect.x();
        int y = layout_rect.y();;
        if(x + width > event->size().width())
            width = event->size().width() - x;
        if(y + height> event->size().height())
            height = event->size().height() - y;

        QRect new_rect(x, y, width, height);

        layout->setGeometry(new_rect);
        layout->update();
    }
}

// void ManagerWidget::resizeEvent(QResizeEvent *event)
// {
//     //if(hasHeightForWidth()){
//     // setFixedHeight(heightForWidth(event->()));
//     // setFixedSize(event->size());
//     resizeLayout(event, ui->buttons_layout);
//     // resizeLayout(event, ui->verticalLayout);



//     QRect new_combatants_rect = ui->scrollArea_combatants->geometry();
//     QRect new_commmands_rect = ui->scrollArea_commands->geometry();
//     double width_coeff = static_cast<double>(event->size().width())
//                          / qMax(event->oldSize().width(), 1);
//     int height_coeff = static_cast<double>(event->size().height())
//                        / qMax(event->oldSize().height(), 1);

//     if (width_coeff > 1.03 || width_coeff < 0.97 || height_coeff > 1.03 || height_coeff < 0.97) {
//         new_combatants_rect.setWidth(width_coeff * new_combatants_rect.width());
//         new_combatants_rect.setHeight(height_coeff * new_combatants_rect.height());

//         ui->scrollArea_combatants->setGeometry(new_combatants_rect);
//         // _box_commands->setMaximumHeight(120);

//         // int height_box_commmands = ui->scrollArea_commands->rect()
//         //                                .height(); // - _box_commands->rect().y();
//         // int heigth_button = ui->pushButton_create_combatant->geometry().height();

//         // ui->scrollArea_commands->setFixedSize(
//         //     event->size() - QSize(0, 10 + heigth_button + height_box_commmands));
//     }
//     if (width_coeff > 1.03 || width_coeff < 0.97 || height_coeff > 1.03 || height_coeff < 0.97) {
//         new_commmands_rect.setWidth(width_coeff * new_commmands_rect.width() - 10);
//         new_commmands_rect.setHeight(height_coeff * new_commmands_rect.height() - 10);

//         ui->scrollArea_commands->setGeometry(new_commmands_rect);
//     }
//     _box_combatants->updateGeometry();
//     _box_commands->updateGeometry();
//     //}
//      QWidget::resizeEvent(event);

// }
