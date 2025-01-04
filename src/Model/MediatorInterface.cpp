#include "MediatorInterface.h"

#if defined(_BOOST_SERIALIZATION_TXT_) || defined(_BOOST_SERIALIZATION_XML_)
template <class Archive>
void pf2e_manager::MediatorInterface::serialize(Archive& ar,
                                                const unsigned int version) {}

template void
pf2e_manager::MediatorInterface::serialize<boost::archive::xml_oarchive>(
    boost::archive::xml_oarchive& ar, const unsigned int version);
template void
pf2e_manager::MediatorInterface::serialize<boost::archive::xml_iarchive>(
    boost::archive::xml_iarchive& ar, const unsigned int version);

BOOST_CLASS_EXPORT_IMPLEMENT(pf2e_manager::MediatorInterface);
#endif
