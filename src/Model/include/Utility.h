#ifndef _UTILITY_H
#define _UTILITY_H

#include <boost/container/stable_vector.hpp>
#include <boost/serialization/vector.hpp>

#ifdef _BOOST_SERIALIZATION_TXT_
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/split_member.hpp>
#endif

#ifdef _BOOST_SERIALIZATION_XML_
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/split_member.hpp>
#endif
// Libs providing ligging
#include <boost/exception/all.hpp>
#include <boost/exception/exception.hpp>
#include <boost/exception/get_error_info.hpp>
#include <boost/log/attributes/timer.hpp>
#include <boost/log/common.hpp>
#include <boost/log/core/core.hpp>
#include <boost/log/core/record.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/expressions/formatters/date_time.hpp>
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
#include <boost/log/support/date_time.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/exception_handler.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/from_stream.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/stacktrace/stacktrace.hpp>>
#include <boost/system.hpp>
#include <exception>
#include <fstream>
#include <iostream>

#include "boost/date_time/posix_time/posix_time.hpp"

#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp>

namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace attrs = boost::log::attributes;
namespace keywords = boost::log::keywords;
namespace sys = boost::system;

BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(my_logger, src::logger_mt)

namespace pf2e_manager {
class EffectBase;
class Combatant;

namespace utility {
// Container types for combatants and effects
using t_combatant_container =
    ::boost::container::stable_vector<pf2e_manager::Combatant *>;
using t_effect_container =
    ::boost::container::stable_vector<pf2e_manager::EffectBase *>;
// Logger functions
extern void init_logger();
extern void print_log(std::exception &ex);
extern void print_log(boost::exception &ex);
extern void my_terminate_handler();
}  // namespace utility
}  // namespace pf2e_manager

#endif  // UTILITY_H
