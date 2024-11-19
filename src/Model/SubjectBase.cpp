#include "SubjectBase.h"

#ifdef _BOOST_SERIALIZATION_XML_

template<class Archive>
void pf2e_manager::SubjectBase::serialize(Archive& ar, const unsigned int version)
{
    // ar.template register_type<SubjectBase*>();
    ar& boost::serialization::make_nvp("_name", _name);
    ar& boost::serialization::make_nvp("_subject", _subject);
    ar& boost::serialization::make_nvp("_reciever", _reciever);
    ar& boost::serialization::make_nvp("_invoker", _invoker);

    ar & _name;
    ar & _subject;
    ar & _reciever;
    ar & _invoker;
}

template void pf2e_manager::SubjectBase::serialize<boost::archive::text_oarchive>(boost::archive::text_oarchive & ar, const unsigned int version);
template void pf2e_manager::SubjectBase::serialize<boost::archive::text_iarchive>(boost::archive::text_iarchive & ar, const unsigned int version);

BOOST_CLASS_EXPORT_IMPLEMENT(pf2e_manager::SubjectBase);
#endif
