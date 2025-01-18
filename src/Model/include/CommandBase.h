#ifndef _COMMAND_BASE_H_A9BAA2E5_D89F_4641_8058_A620720B6DA5
#define _COMMAND_BASE_H_A9BAA2E5_D89F_4641_8058_A620720B6DA5

#include <string>

#include "SubjectBase.h"

#if defined(_BOOST_SERIALIZATION_TXT_) || defined(_BOOST_SERIALIZATION_XML_)

#ifdef _BOOST_SERIALIZATION_TXT_
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#endif

#ifdef _BOOST_SERIALIZATION_XML_
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#endif

#include <boost/archive/tmpdir.hpp>
#include <boost/config.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#endif

namespace pf2e_manager {
/**
 * @brief CommandBase is derived from @class SubjectBase that allow to define
 * the source and direction of command. Also its an abstract class with some
 * children: HealCommand, HarmCommand, MassHealCommand, MassHarmCommand. There
 * are do/undo mechanic implemented (command pattern). Save/load implemented by
 * boost::serialize template function.
 */
class CommandBase : public SubjectBase {
#if defined(_BOOST_SERIALIZATION_TXT_) || defined(_BOOST_SERIALIZATION_XML_)
  friend std::ostream& operator<<(std::ostream& os,
                                  const pf2e_manager::SubjectBase* instance);

  friend class ::boost::serialization::access;
  template <class Archive>
  void serialize(Archive& ar, const unsigned int version);

  //     : SubjectBase(this)
  // {}
#endif
 public:
  CommandBase() = default;
  CommandBase(int value, CommandBase* p);
  virtual void execute() = 0;
  virtual void undo() = 0;
  int value() const { return _value; }
  bool isActive() const { return _is_active; }

 protected:
  int _value = 0;
  bool _is_active = false;
};
}  // namespace pf2e_manager

#if defined(_BOOST_SERIALIZATION_TXT_) || defined(_BOOST_SERIALIZATION_XML_)

BOOST_SERIALIZATION_ASSUME_ABSTRACT(pf2e_manager::CommandBase);

BOOST_CLASS_EXPORT_KEY(pf2e_manager::CommandBase);
#endif

#endif
