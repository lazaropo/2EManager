#ifndef _MEDIATOR_INTERFACE_H_250D0D9E_9EBB_482B_B709_09EEB6A3AD7D_
#define _MEDIATOR_INTERFACE_H_250D0D9E_9EBB_482B_B709_09EEB6A3AD7D_

#include <vector>

#include "CommandBase.h"
#include "SubjectBase.h"

#ifdef _BOOST_SERIALIZATION_XML_
#include <boost/config.hpp>

#include <boost/archive/tmpdir.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

#include <boost/serialization/access.hpp>
#endif

namespace pf2e_manager {
class MediatorInterface {
#ifdef _BOOST_SERIALIZATION_XML_
    friend class ::boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {}
#endif
public:
    MediatorInterface() = default;
    virtual ~MediatorInterface() = default;

    virtual int getConfirmation(SubjectBase* sender, SubjectBase* reciever, const std::string& name)
        = 0;

    virtual void makeEffect(SubjectBase* sender,
                            SubjectBase* reciever,
                            const std::string& name,
                            const int duration = 0,
                            const int value = 0)
        = 0;

    virtual CommandBase* makeCommand(SubjectBase* sender,
                                     const std::string& name,
                                     std::vector<std::pair<SubjectBase*, int>>& info)
        = 0;

    virtual void undoEffect(SubjectBase* sender, SubjectBase* reciever, const std::string& name) = 0;

    virtual void undoCommand(SubjectBase* sender, SubjectBase* reciever, const std::string& name) = 0;

    virtual const std::vector<CommandBase*>& getCommands() const = 0;
    virtual std::vector<CommandBase*>& getCommands() = 0;
};
}  // namespace pf2e_manager

#endif
