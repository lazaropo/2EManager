#include "CommandBase.h"


#ifdef _BOOST_SERIALIZATION_TXT_
template<class Archive>
void pf2e_manager::CommandBase::serialize(Archive& ar, const unsigned int version)
{
    // ar.template register_type<::pf2e_manager::SubjectBase>();
    // ar.template register_type<::pf2e_manager::SubjectBase*>();

    ar& ::boost::serialization::base_object<pf2e_manager::SubjectBase>(*this);

    ar& boost::serialization::make_nvp("_value", _value);
    ar& boost::serialization::make_nvp("_is_active", _is_active);

    ar & _value;
    ar & _is_active;
}
template void pf2e_manager::CommandBase::serialize<boost::archive::text_oarchive>(boost::archive::text_oarchive & ar, const unsigned int version);
template void pf2e_manager::CommandBase::serialize<boost::archive::text_iarchive>(boost::archive::text_iarchive & ar, const unsigned int version);

BOOST_CLASS_EXPORT_IMPLEMENT(pf2e_manager::CommandBase);
#endif

#ifdef _BOOST_SERIALIZATION_XML_
template<class Archive>
void pf2e_manager::CommandBase::serialize(Archive& ar, const unsigned int version)
{
    // ar.template register_type<::pf2e_manager::SubjectBase>();
    // ar.template register_type<::pf2e_manager::SubjectBase*>();

    ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP(SubjectBase);

    // ar& boost::serialization::make_nvp("_value", _value);
    // ar& boost::serialization::make_nvp("_is_active", _is_active);

    ar & BOOST_SERIALIZATION_NVP(_value);
    ar & BOOST_SERIALIZATION_NVP(_is_active);
}
template void pf2e_manager::CommandBase::serialize<boost::archive::xml_oarchive>(boost::archive::xml_oarchive & ar, const unsigned int version);
template void pf2e_manager::CommandBase::serialize<boost::archive::xml_iarchive>(boost::archive::xml_iarchive & ar, const unsigned int version);

BOOST_CLASS_EXPORT_IMPLEMENT(pf2e_manager::CommandBase);
#endif


namespace pf2e_manager {
CommandBase::CommandBase(int value, CommandBase* p)
    : SubjectBase(p)
    , _value(value)
{}
}
