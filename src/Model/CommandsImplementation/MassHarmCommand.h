#ifndef _MASSHARMCOMMAND_H_F65E13E0_5E2B_11EF_A550_0800200C9A66_
#define _MASSHARMCOMMAND_H_F65E13E0_5E2B_11EF_A550_0800200C9A66_

#include <utility>

#include "HarmCommand.h"

#ifdef _BOOST_SERIALIZATION_XML_
#include <boost/config.hpp>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/tmpdir.hpp>

#include <boost/serialization/base_object.hpp>

#include <boost/serialization/export.hpp>
#include <boost/serialization/vector.hpp>

// using namespace ::pf2e_manager;

#endif

namespace pf2e_manager {
class MassHarmCommand : public CommandBase {
#ifdef _BOOST_SERIALIZATION_XML_
    friend class ::boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        // serialize base class information
        ar & ::boost::serialization::base_object<CommandBase>(*this);
        ar & _info;
    }

    MassHarmCommand() {}
#endif
public:
    MassHarmCommand(MediatorInterface *mediator,
                    SubjectBase *sender,
                    const std::vector<std::pair<SubjectBase *, int>> &info);

    /**
   * @brief Do from do/undo. _is_active == true accords currect exertion of
   * this effect. So, if it's true the damage is  caused. If not (command
   * was undone) the damage is saved, but doesn't caused rigth now.
   *
   * @param value damage value
   */
    void execute() override;

    void undo() override;

    const std::vector<HarmCommand *> &getInfo() const { return _info; }

private:
    MediatorInterface *_mediator;
    std::vector<HarmCommand *> _info;
};
}  // namespace pf2e_manager
// BOOST_CLASS_EXPORT(pf2e_manager::MassHarmCommand);
#endif  // MASSHARMCOMMAND_H
