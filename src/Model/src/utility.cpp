#include "utility.h"

#include "Combatant.h"

namespace pf2e_manager {
namespace utility {
void init_logger() {
  // Initialize sinks
  boost::filesystem::path dir("./log/exceptions/");
  if (!boost::filesystem::exists(dir)) boost::filesystem::create_directory(dir);

  logging::add_console_log()->set_filter(expr::attr<int>("Severity") >= 4);

  logging::formatter formatter =
      expr::stream << expr::attr<unsigned int>("LineID") << " : "
                   << expr::format_date_time<boost::posix_time::ptime>(
                          "TimeStamp", "%Y-%m-%d %H:%M:%S")
                   << " *" << expr::attr<int>("Severity") << "* "
                   << expr::message;

  // Create a text file sink
  using file_sink = sinks::synchronous_sink<sinks::text_file_backend>;
  boost::shared_ptr<file_sink> sink(new file_sink(
      keywords::file_name = "./log/exceptions/file.log",
      keywords::target_file_name = "./log/exceptions/file_%5N.log",
      keywords::rotation_size = 5 * 1024 * 1024,
      keywords::open_mode =
          std::ios_base::in | std::ios_base::out | std::ios_base::trunc));

  sink->locked_backend()->set_file_collector(sinks::file::make_collector(
      keywords::target = "log/exceptions/",
      keywords::max_size = 16 * 1024 * 1024,
      keywords::min_free_space = 100 * 1024 * 1024, keywords::max_files = 512));

  // Upon restart, scan the directory for files matching the file_name pattern
  sink->locked_backend()->scan_for_files();

  sink->set_formatter(formatter);

  logging::core::get()->add_sink(sink);

  logging::add_common_attributes();
}

void print_log(std::exception &ex) {
  src::logger_mt &lg = my_logger::get();
  BOOST_LOG(lg) << "Exception description: " << ex.what() << std::endl
                << "Stack Trace: " << boost::stacktrace::stacktrace()
                << std::endl;
}

void print_log(boost::exception &ex) {
  src::logger_mt &lg = my_logger::get();
  typedef boost::error_info<struct tag_my_info, int> my_info;
  // boost::error_info::value_type *info = boost::get_error_info<my_info>(ex);
  if (int const *mi = boost::get_error_info<my_info>(ex))
    BOOST_LOG(lg) << "Boost exception info: " << *mi << std::endl
                  << "Stack Trace: " << boost::stacktrace::stacktrace()
                  << std::endl;
}

void my_terminate_handler() {
  try {
    // logging::add_console_log()->set_filter(expr::attr<int>("Severity") >= 4);
    boost::filesystem::path dir("./log/signals/");
    if (!boost::filesystem::exists(dir))
      boost::filesystem::create_directory(dir);

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
}  // namespace utility
}  // namespace pf2e_manager
