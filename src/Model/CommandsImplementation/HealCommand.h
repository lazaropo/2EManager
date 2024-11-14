#ifndef _HEAL_COMMAND_H_BFB637A6_33DB_4A0F_A6B4_DBAF10B671A4_
#define _HEAL_COMMAND_H_BFB637A6_33DB_4A0F_A6B4_DBAF10B671A4_

#include "../Combatant.h"
#include "../CommandBase.h"
#include "../MediatorInterface.h"

#ifdef _BOOST_SERIALIZATION_XML_
#include <boost/config.hpp>

#include <boost/archive/tmpdir.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

#include <boost/serialization/base_object.hpp>
#endif

namespace pf2e_manager {
class HealCommand : public CommandBase {
#ifdef _BOOST_SERIALIZATION_XML_
    friend class ::boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        // serialize base class information
        ar& ::boost::serialization::base_object<CommandBase>(*this);
    }
#endif
public:
    HealCommand(MediatorInterface* mediator, SubjectBase* sender, SubjectBase* reciever, int value)
        : CommandBase(value, this)
        , _mediator(mediator)
    {
        setName("command:heal");
        setInvoker(sender);
        setReciever(reciever);
    }
    void execute() override;

    void undo() override;

private:
    MediatorInterface* _mediator;
};
}  // namespace pf2e_manager

#endif
