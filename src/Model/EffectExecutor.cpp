#include "EffectExecutor.h"

#ifdef _BOOST_SERIALIZATION_XML_
template<class Archive>
void pf2e_manager::EffectExecutor::serialize(Archive &ar, const unsigned int version)
{
    ar& boost::serialization::make_nvp("_mediator", _mediator);

    ar & _mediator;
}

template void pf2e_manager::EffectExecutor::serialize<boost::archive::text_oarchive>(boost::archive::text_oarchive & ar, const unsigned int version);
template void pf2e_manager::EffectExecutor::serialize<boost::archive::text_iarchive>(boost::archive::text_iarchive & ar, const unsigned int version);

BOOST_CLASS_EXPORT_IMPLEMENT(pf2e_manager::EffectExecutor);
#endif

namespace pf2e_manager{
void EffectExecutor::execute(SubjectBase* sender, SubjectBase* reciever,
             const std::vector<std::string>& name/*, const int duration = 0,
               const int value = 0*/) {
    for (auto it : name) {
        if (it.find("effect:") == 0) {
            int value = _mediator->getConfirmation(sender, reciever, it);
            int duration = 420000; /* just big number*/
            if (auto effect = static_cast<EffectBase*>(sender))
                duration = effect->getDuration();
            if (value >= 0)
                _mediator->makeEffect(sender, reciever, it, duration, value);
            else {
                auto effect = dynamic_cast<EffectBase*>(sender);
                if (effect) effect->removeEffect();
            }
        } else if (it.find("command:") == 0) {
            int value = _mediator->getConfirmation(sender, reciever, it);
            auto info = std::vector{std::make_pair(reciever, value)};
            if (value >= 0)
                _mediator->makeCommand(sender, it, info);
            else {
                auto effect = dynamic_cast<EffectBase*>(sender);
                if (effect) effect->removeEffect();
            }
        }
    }
}
}
