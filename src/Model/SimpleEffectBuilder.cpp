#include "SimpleEffectBuilder.h"

#ifdef _BOOST_SERIALIZATION_XML_
// BOOST_CLASS_EXPORT_IMPLEMENT(pf2e_manager::Combatant);
template<class Archive>
void pf2e_manager::SimpleEffectBuilder::serialize(Archive& ar, const unsigned int version)
{
    // ar& boost::serialization::make_nvp("_combatants", _combatants);
    // ar& boost::serialization::make_nvp("_mediator", _mediator);
    ar& boost::serialization::make_nvp("_executor", _executor);

    // ar.register_type<std::vector<Combatant*>();

    ar & _executor;
}
BOOST_CLASS_EXPORT_IMPLEMENT(pf2e_manager::SimpleEffectBuilder);

template void pf2e_manager::SimpleEffectBuilder::serialize<boost::archive::text_oarchive>(boost::archive::text_oarchive & ar, const unsigned int version);
template void  pf2e_manager::SimpleEffectBuilder::serialize<boost::archive::text_iarchive>(boost::archive::text_iarchive & ar, const unsigned int version);
#endif
