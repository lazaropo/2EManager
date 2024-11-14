#ifndef _COMMAND_BASE_H_A9BAA2E5_D89F_4641_8058_A620720B6DA5
#define _COMMAND_BASE_H_A9BAA2E5_D89F_4641_8058_A620720B6DA5

#include <string>

#include "SubjectBase.h"

#ifdef _BOOST_SERIALIZATION_XML_
#include <boost/config.hpp>

#include <boost/archive/tmpdir.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

#include <boost/serialization/base_object.hpp>
#endif

namespace pf2e_manager {
class CommandBase : public SubjectBase {
 public:
#ifdef _BOOST_SERIALIZATION_XML_
     friend std::ostream& operator<<(std::ostream& os, const pf2e_manager::SubjectBase* instance);

     friend class ::boost::serialization::access;
     template<class Archive>
     void serialize(Archive& ar, const unsigned int version)
     {
         ar& ::boost::serialization::base_object<SubjectBase>(*this);
         ar & _value;
         ar & _is_active;
     }
#endif

     CommandBase(int value, CommandBase* p)
         : SubjectBase(p)
         , _value(value)
     {}
     virtual void execute() = 0;
     virtual void undo() = 0;
     int value() const { return _value; }

 protected:
  int _value = 0;
  bool _is_active = false;
};
}  // namespace pf2e_manager
#endif
