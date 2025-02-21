#include "CommandsImplementation/HealCommand.h"

#ifdef _BOOST_SERIALIZATION_TXT_
template <class Archive>
void pf2e_manager::HealCommand::serialize(Archive& ar,
                                          const unsigned int version) {
  // serialize base class information
  // ar.template register_type<::pf2e_manager::SubjectBase>();
  // ar.template register_type<::pf2e_manager::CommandBase>();

  // ar.template register_type<::pf2e_manager::SubjectBase*>();
  // ar.template register_type<::pf2e_manager::CommandBase*>();

  ar& ::boost::serialization::base_object<::pf2e_manager::CommandBase>(*this);
}
template void
pf2e_manager::HealCommand::serialize<boost::archive::text_oarchive>(
    boost::archive::text_oarchive& ar, const unsigned int version);
template void
pf2e_manager::HealCommand::serialize<boost::archive::text_iarchive>(
    boost::archive::text_iarchive& ar, const unsigned int version);

BOOST_CLASS_EXPORT_IMPLEMENT(::pf2e_manager::HealCommand);
#endif

#ifdef _BOOST_SERIALIZATION_XML_
template <class Archive>
void pf2e_manager::HealCommand::serialize(Archive& ar,
                                          const unsigned int version) {
  // ar.template register_type<::pf2e_manager::SubjectBase>();
  // ar.template register_type<::pf2e_manager::SubjectBase*>();

  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP(CommandBase);

  // ar& boost::serialization::make_nvp("_value", _value);
  // ar& boost::serialization::make_nvp("_is_active", _is_active);

  // ar & BOOST_SERIALIZATION_NVP(_value);
  // ar & BOOST_SERIALIZATION_NVP(_is_active);
}
template void
pf2e_manager::HealCommand::serialize<boost::archive::xml_oarchive>(
    boost::archive::xml_oarchive& ar, const unsigned int version);
template void
pf2e_manager::HealCommand::serialize<boost::archive::xml_iarchive>(
    boost::archive::xml_iarchive& ar, const unsigned int version);

BOOST_CLASS_EXPORT_IMPLEMENT(pf2e_manager::HealCommand);
#endif

namespace pf2e_manager {
void HealCommand::execute() {
  if (_value <= 0 || _is_active) return;

  Combatant* combatant = dynamic_cast<Combatant*>(this->getReciever());
  if (!combatant)
    throw std::runtime_error(
        "HealCommand - execute func: reciever is not Combatant class.");

  int curr_hp = combatant->getHPCurr();
  int max_hp = combatant->getHPMax();
  if (curr_hp <= 0) {
    combatant->setHPCurr(_value);
    // now sender is nullptr. but actually it must work without direction of
    // sender
    // _mediator->undoEffect(nullptr, combatant, "effect:dying");
  } else {
    int hp = curr_hp + _value;
    if (hp > max_hp) hp = max_hp;
    combatant->setHPCurr(hp);
  }

  _is_active = true;
}

void HealCommand::undo() {
  if (!_is_active) return;

  Combatant* combatant = dynamic_cast<Combatant*>(getReciever());
  if (!combatant)
    throw std::runtime_error(
        "HealCommand - execute func: reciever is not Combatant class.");

  int curr_hp = combatant->getHPCurr();
  if (curr_hp <= _value) {
    combatant->setHPCurr(0);
    _mediator->makeEffect(getSubject(), getReciever(), "effect:dying",
                          420000 /*very big duration*/, 1);
  } else {
    combatant->setHPCurr(curr_hp - _value);
  }

  _is_active = false;
}
}  // namespace pf2e_manager
