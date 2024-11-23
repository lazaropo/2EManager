#ifndef _HARM_COMMAND_H_B682292B_D042_4EEB_A771_67735725CE78_
#define _HARM_COMMAND_H_B682292B_D042_4EEB_A771_67735725CE78_

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
class HarmCommand : public CommandBase {
#if defined(_BOOST_SERIALIZATION_TXT_) || defined(_BOOST_SERIALIZATION_XML_)
  friend class ::boost::serialization::access;
  template <class Archive>
  void serialize(Archive& ar, const unsigned int version);

  HarmCommand() {}
#endif
 public:
  HarmCommand(MediatorInterface* mediator, SubjectBase* sender,
              SubjectBase* reciever, int value)
      : CommandBase(value, this), _mediator(mediator) {
    setName("command:harm");
    setInvoker(sender);
    setReciever(reciever);
  }
  /**
   * @brief Do from do/undo. _is_active == true accords currect exertion of this
   * effect. So, if it's true the damage is  caused. If not (command was undone)
   * the damage is saved, but doesn't caused rigth now.
   *
   * @param value damage value
   */
  void execute() override;

  void undo() override;

 private:
  MediatorInterface* _mediator;
};
}  // namespace pf2e_manager

#if defined(_BOOST_SERIALIZATION_TXT_) || defined(_BOOST_SERIALIZATION_XML_)
BOOST_CLASS_EXPORT_KEY(::pf2e_manager::HarmCommand);
#endif

#endif
