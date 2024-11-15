#ifndef _HARM_COMMAND_H_B682292B_D042_4EEB_A771_67735725CE78_
#define _HARM_COMMAND_H_B682292B_D042_4EEB_A771_67735725CE78_

#include "../Combatant.h"
#include "../CommandBase.h"
#include "../MediatorInterface.h"

#ifdef _BOOST_SERIALIZATION_XML_
#include <boost/config.hpp>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/tmpdir.hpp>

#include <boost/serialization/base_object.hpp>

#include <boost/serialization/export.hpp>
#endif

namespace pf2e_manager {
class HarmCommand : public CommandBase {
#ifdef _BOOST_SERIALIZATION_XML_
    friend class ::boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        // serialize base class information
        ar& ::boost::serialization::base_object<CommandBase>(*this);
    }

    HarmCommand() {}
#endif
public:
    HarmCommand(MediatorInterface* mediator, SubjectBase* sender, SubjectBase* reciever, int value)
        : CommandBase(value, this)
        , _mediator(mediator)
    {
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

// BOOST_CLASS_EXPORT(pf2e_manager::HarmCommand);

#endif
