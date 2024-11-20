#include "SubjectBase.h"

#ifdef _BOOST_SERIALIZATION_TXT_

template<class Archive>
void pf2e_manager::SubjectBase::serialize(Archive& ar, const unsigned int version)
{
    // ar.template register_type<SubjectBase*>();
    // ar& boost::serialization::make_nvp("_name", _name);
    // ar& boost::serialization::make_nvp("_subject", _subject);
    // ar& boost::serialization::make_nvp("_reciever", _reciever);
    // ar& boost::serialization::make_nvp("_invoker", _invoker);

    ar & _name;
    ar & _subject;
    ar & _reciever;
    ar & _invoker;
}

template void pf2e_manager::SubjectBase::serialize<boost::archive::text_oarchive>(boost::archive::text_oarchive & ar, const unsigned int version);
template void pf2e_manager::SubjectBase::serialize<boost::archive::text_iarchive>(boost::archive::text_iarchive & ar, const unsigned int version);

BOOST_CLASS_EXPORT_IMPLEMENT(pf2e_manager::SubjectBase);
#endif

#ifdef _BOOST_SERIALIZATION_XML_
template<class Archive>
void pf2e_manager::SubjectBase::serialize(Archive& ar, const unsigned int version)
{
    // ar.template register_type<SubjectBase*>();
    // ar& boost::serialization::make_nvp("_name", _name);
    // ar& boost::serialization::make_nvp("_subject", _subject);
    // ar& boost::serialization::make_nvp("_reciever", _reciever);
    // ar& boost::serialization::make_nvp("_invoker", _invoker);

    ar & BOOST_SERIALIZATION_NVP(_name);
    ar & BOOST_SERIALIZATION_NVP(_subject);
    ar & BOOST_SERIALIZATION_NVP(_reciever);
    ar & BOOST_SERIALIZATION_NVP(_invoker);
}

template void pf2e_manager::SubjectBase::serialize<boost::archive::xml_oarchive>(boost::archive::xml_oarchive & ar, const unsigned int version);
template void pf2e_manager::SubjectBase::serialize<boost::archive::xml_iarchive>(boost::archive::xml_iarchive & ar, const unsigned int version);

BOOST_CLASS_EXPORT_IMPLEMENT(pf2e_manager::SubjectBase);

#endif
