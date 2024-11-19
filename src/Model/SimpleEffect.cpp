#include "SimpleEffect.h"

#ifdef _BOOST_SERIALIZATION_XML_
template<class Archive>
void pf2e_manager::SimpleEffect::serialize(Archive& ar, const unsigned int version)
{
    // serialize base class information
    // ar.template register_type<::pf2e_manager::SubjectBase>();
    // ar.template register_type<::pf2e_manager::SubjectBase*>();
    // ar.template register_type<::pf2e_manager::EffectBase>();
    // ar.template register_type<::pf2e_manager::EffectBase*>();

    ar& ::boost::serialization::base_object<EffectBase>(*this);

    ar& boost::serialization::make_nvp("_is_associated_provided", _is_associated_provided);
    ar& boost::serialization::make_nvp("_associated_actions", _associated_actions);
    ar& boost::serialization::make_nvp("_execute_actions", _execute_actions);

    ar & _is_associated_provided;

    ar & _associated_actions;
    ar & _execute_actions;
}
template void pf2e_manager::SimpleEffect::serialize<boost::archive::text_oarchive>(boost::archive::text_oarchive & ar, const unsigned int version);
template void  pf2e_manager::SimpleEffect::serialize<boost::archive::text_iarchive>(boost::archive::text_iarchive & ar, const unsigned int version);

BOOST_CLASS_EXPORT_IMPLEMENT(pf2e_manager::SimpleEffect);
#endif

namespace pf2e_manager {
SimpleEffect::SimpleEffect(const SimpleEffect &other)
    : EffectBase(this, other.getReciever())

{
  _type = other._type;
  _value = other._value;
  _trigger = other._trigger;
  _duration = other._duration;
  _is_active = other._is_active;
  _description = other._description;
}

void SimpleEffect::execute() {
  if (!_is_active) return;
  --_duration;
  if (_execute_actions.size())
    _executor->execute(getSubject(), getReciever(), _execute_actions);
  if (_duration < 1) _is_active = false;
}

void SimpleEffect::undo() {
  ++_duration;
  _is_active = _is_active ? false : true;
}

}  // namespace pf2e_manager
