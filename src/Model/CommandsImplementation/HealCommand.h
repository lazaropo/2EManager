#ifndef _HEAL_COMMAND_H_BFB637A6_33DB_4A0F_A6B4_DBAF10B671A4_
#define _HEAL_COMMAND_H_BFB637A6_33DB_4A0F_A6B4_DBAF10B671A4_

#include "../Combatant.h"
#include "../CommandBase.h"
#include "../MediatorInterface.h"

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
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#endif

namespace pf2e_manager {
class HealCommand : public CommandBase {
#if defined(_BOOST_SERIALIZATION_TXT_) || defined(_BOOST_SERIALIZATION_XML_)
  friend class ::boost::serialization::access;
  template <class Archive>
  void serialize(Archive& ar, const unsigned int version);
  HealCommand() = default;
#endif
 public:
  HealCommand(MediatorInterface* mediator, SubjectBase* sender,
              SubjectBase* reciever, int value)
      : CommandBase(value, this), _mediator(mediator) {
    setName("command:heal");
    setInvoker(sender);
    setReciever(reciever);
  }
  void execute() override;

  void undo() override;

 private:
  MediatorInterface* _mediator = nullptr;
};
}  // namespace pf2e_manager

#if defined(_BOOST_SERIALIZATION_TXT_) || defined(_BOOST_SERIALIZATION_XML_)
BOOST_CLASS_EXPORT_KEY(::pf2e_manager::HealCommand)
#endif

#endif
