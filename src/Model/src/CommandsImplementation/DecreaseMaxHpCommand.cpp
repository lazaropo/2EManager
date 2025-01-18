#include "CommandsImplementation/DecreaseMaxHpCommand.h"

#ifdef _BOOST_SERIALIZATION_TXT_
template <class Archive>
void pf2e_manager::DecreaseMaxHpCommand::serialize(Archive& ar,
                                                   const unsigned int version) {
  // serialize base class information
  // ar.template register_type<::pf2e_manager::SubjectBase>();
  // ar.template register_type<::pf2e_manager::CommandBase>();

  // ar.template register_type<::pf2e_manager::CommandBase*>();

  ar& ::boost::serialization::base_object<CommandBase>(*this);
  ar& BOOST_SERIALIZATION_NVP(_prev_hp_max);
}
template void
pf2e_manager::DecreaseMaxHpCommand::serialize<boost::archive::text_oarchive>(
    boost::archive::text_oarchive& ar, const unsigned int version);
template void
pf2e_manager::DecreaseMaxHpCommand::serialize<boost::archive::text_iarchive>(
    boost::archive::text_iarchive& ar, const unsigned int version);

BOOST_CLASS_EXPORT_IMPLEMENT(pf2e_manager::DecreaseMaxHpCommand);
// BOOST_CLASS_EXPORT_IMPLEMENT(pf2e_manager::CommandBase);
#endif

#ifdef _BOOST_SERIALIZATION_XML_
template <class Archive>
void pf2e_manager::DecreaseMaxHpCommand::serialize(Archive& ar,
                                                   const unsigned int version) {
  // ar.template register_type<::pf2e_manager::SubjectBase>();
  // ar.template register_type<::pf2e_manager::SubjectBase*>();

  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP(CommandBase);

  // ar& boost::serialization::make_nvp("_value", _value);
  // ar& boost::serialization::make_nvp("_is_active", _is_active);

  ar& BOOST_SERIALIZATION_NVP(_prev_hp_max);
  // ar & BOOST_SERIALIZATION_NVP(_is_active);
}
template void
pf2e_manager::DecreaseMaxHpCommand::serialize<boost::archive::xml_oarchive>(
    boost::archive::xml_oarchive& ar, const unsigned int version);
template void
pf2e_manager::DecreaseMaxHpCommand::serialize<boost::archive::xml_iarchive>(
    boost::archive::xml_iarchive& ar, const unsigned int version);

BOOST_CLASS_EXPORT_IMPLEMENT(pf2e_manager::DecreaseMaxHpCommand);
#endif

namespace pf2e_manager {

void DecreaseMaxHpCommand::execute() {
  if (_value <= 0 || _is_active) return;

  Combatant* combatant = dynamic_cast<Combatant*>(this->getReciever());
  if (!combatant)
    throw std::runtime_error(
        "DecreaseMaxHpCommand - execute func: reciever is not Combatant "
        "class.");

  int curr_hp = combatant->getHPCurr();
  int max_hp = combatant->_hp_max;
  _prev_hp_max = max_hp;
  if (curr_hp <= _value || max_hp <= _value) {
    combatant->setHPCurr(1);
    combatant->_hp_max = 1;
    // _mediator->makeEffect(getSubject(), getReciever(), "effect:dying",
    //                       420000 /*very big duration*/, 1);
  } else {
    combatant->setHPCurr(curr_hp - _value);
    combatant->_hp_max = max_hp - _value;
  }

  _is_active = true;
}

void DecreaseMaxHpCommand::undo() {
  if (!_is_active) return;

  Combatant* combatant = dynamic_cast<Combatant*>(getReciever());
  if (!combatant)
    throw std::runtime_error(
        "DecreaseMaxHpCommand - execute func: reciever is not Combatant "
        "class.");

  int curr_hp = combatant->getHPCurr();
  int max_hp = combatant->getHPMax();
  if (curr_hp == 1 || max_hp == 1) {
    combatant->_hp_max = _prev_hp_max;
    combatant->setHPCurr(_value);
    // _mediator->undoEffect(getSubject(), getReciever(), "effect:dying");
  } else {
    combatant->_hp_max = _prev_hp_max;

    int hp = curr_hp + _value;
    if (hp > max_hp) hp = max_hp;
    combatant->setHPCurr(hp);
  }

  _is_active = false;
}
}  // namespace pf2e_manager
