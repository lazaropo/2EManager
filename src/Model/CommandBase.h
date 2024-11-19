#ifndef _COMMAND_BASE_H_A9BAA2E5_D89F_4641_8058_A620720B6DA5
#define _COMMAND_BASE_H_A9BAA2E5_D89F_4641_8058_A620720B6DA5

#include <string>

#include "SubjectBase.h"

#ifdef _BOOST_SERIALIZATION_XML_
#include <boost/config.hpp>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/tmpdir.hpp>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/assume_abstract.hpp>
#endif

namespace pf2e_manager {
class CommandBase : public SubjectBase {
 public:
#ifdef _BOOST_SERIALIZATION_XML_
     friend std::ostream& operator<<(std::ostream& os, const pf2e_manager::SubjectBase* instance);

     friend class ::boost::serialization::access;
     template<class Archive>
     void serialize(Archive& ar, const unsigned int version);
     CommandBase() = default;
     //     : SubjectBase(this)
     // {}
#endif

     CommandBase(int value, CommandBase* p);
     virtual void execute() = 0;
     virtual void undo() = 0;
     int value() const { return _value; }

 protected:
  int _value = 0;
  bool _is_active = false;
};
}  // namespace pf2e_manager

#ifdef _BOOST_SERIALIZATION_XML_

BOOST_SERIALIZATION_ASSUME_ABSTRACT(pf2e_manager::CommandBase);

BOOST_CLASS_EXPORT_KEY(pf2e_manager::CommandBase);
#endif

#endif
