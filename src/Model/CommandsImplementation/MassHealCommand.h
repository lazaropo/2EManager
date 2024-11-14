#ifndef _MASSHEALCOMMAND_H_21A81540_5E46_11EF_A550_0800200C9A66_
#define _MASSHEALCOMMAND_H_21A81540_5E46_11EF_A550_0800200C9A66_

#include <utility>

#include "HealCommand.h"

#ifdef _BOOST_SERIALIZATION_XML_
#include <boost/config.hpp>

#include <boost/archive/tmpdir.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

#include <boost/serialization/base_object.hpp>

#include <boost/serialization/vector.hpp>
#endif

namespace pf2e_manager {
class MassHealCommand : public CommandBase {
#ifdef _BOOST_SERIALIZATION_XML_
    friend class ::boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        // serialize base class information
        ar & ::boost::serialization::base_object<CommandBase>(*this);

        ar & _info;
    }
#endif
public:
    MassHealCommand(MediatorInterface *mediator,
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

    const std::vector<HealCommand *> &getInfo() const { return _info; }

private:
    MediatorInterface *_mediator;
    std::vector<HealCommand *> _info;
};
}  // namespace pf2e_manager

#endif  // MASSHEALCOMMAND_H
