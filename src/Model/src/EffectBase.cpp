#include "EffectBase.h"

#ifdef _BOOST_SERIALIZATION_TXT_
template <class Archive>
void pf2e_manager::EffectBase::serialize(Archive &ar,
                                         const unsigned int version) {
  // serialize base class information
  ar &boost::serialization::base_object<SubjectBase>(*this);

  // ar& boost::serialization::make_nvp("_duration", _duration);
  // ar& boost::serialization::make_nvp("_is_active", _is_active);
  // ar& boost::serialization::make_nvp("_value", _value);
  // ar& boost::serialization::make_nvp("_trigger", _trigger);
  // ar& boost::serialization::make_nvp("_description", _description);

  ar & _duration;  // per round
  ar & _is_active;
  ar & _type;  // bit field
  ar & _value;
  ar & _trigger;

  ar & _description;
}

template void
pf2e_manager::EffectBase::serialize<boost::archive::text_oarchive>(
    boost::archive::text_oarchive &ar, const unsigned int version);
template void
pf2e_manager::EffectBase::serialize<boost::archive::text_iarchive>(
    boost::archive::text_iarchive &ar, const unsigned int version);

BOOST_CLASS_EXPORT_IMPLEMENT(pf2e_manager::EffectBase);
#endif

#ifdef _BOOST_SERIALIZATION_XML_
template <class Archive>
void pf2e_manager::EffectBase::serialize(Archive &ar,
                                         const unsigned int version) {
  // serialize base class information
  ar &BOOST_SERIALIZATION_BASE_OBJECT_NVP(SubjectBase);

  ar &BOOST_SERIALIZATION_NVP(_duration);  // per round
  ar &BOOST_SERIALIZATION_NVP(_is_active);
  ar &BOOST_SERIALIZATION_NVP(_type);  // bit field
  ar &BOOST_SERIALIZATION_NVP(_value);
  ar &BOOST_SERIALIZATION_NVP(_trigger);

  ar &BOOST_SERIALIZATION_NVP(_description);
}

template void pf2e_manager::EffectBase::serialize<boost::archive::xml_oarchive>(
    boost::archive::xml_oarchive &ar, const unsigned int version);
template void pf2e_manager::EffectBase::serialize<boost::archive::xml_iarchive>(
    boost::archive::xml_iarchive &ar, const unsigned int version);

BOOST_CLASS_EXPORT_IMPLEMENT(pf2e_manager::EffectBase)

template <class Archive>
void pf2e_manager::EffectBase::Value::serialize(
    Archive &ar, const unsigned int version) {  // per round
  ar &BOOST_SERIALIZATION_NVP(_is_constant);
  ar &BOOST_SERIALIZATION_NVP(_value);
  ar &BOOST_SERIALIZATION_NVP(_str);
  ar &BOOST_SERIALIZATION_NVP(_dex);
  ar &BOOST_SERIALIZATION_NVP(_con);
  ar &BOOST_SERIALIZATION_NVP(_mind);
  ar &BOOST_SERIALIZATION_NVP(_fort);
  ar &BOOST_SERIALIZATION_NVP(_refl);
  ar &BOOST_SERIALIZATION_NVP(_will);
  ar &BOOST_SERIALIZATION_NVP(_skills);
  ar &BOOST_SERIALIZATION_NVP(_perc);  // perception
  ar &BOOST_SERIALIZATION_NVP(_atk);
  ar &BOOST_SERIALIZATION_NVP(_ac);
  ar &BOOST_SERIALIZATION_NVP(_dc);  // class DC
  ar &BOOST_SERIALIZATION_NVP(_init);
}

template void
pf2e_manager::EffectBase::Value::serialize<boost::archive::xml_oarchive>(
    boost::archive::xml_oarchive &ar, const unsigned int version);
template void
pf2e_manager::EffectBase::Value::serialize<boost::archive::xml_iarchive>(
    boost::archive::xml_iarchive &ar, const unsigned int version);

BOOST_CLASS_EXPORT_IMPLEMENT(pf2e_manager::EffectBase::Value);
#endif

namespace pf2e_manager {
std::string EffectBase::formattingTrigger(EffectBase::Trigger trigger) {
  std::string ret;

  if (trigger == Trigger::NO_TRIGGER)
    ret = "No trigger";
  else if(trigger == Trigger::AT_CREATION)
      ret = "At creation";
  else if (trigger == Trigger::START_TURN)
    ret = "Start turn";
  else if (trigger == Trigger::END_TURN)
    ret = "End of turn";

  return ret;
}

EffectBase::Trigger EffectBase::formattingTrigger(const std::string &string) {
  Trigger ret;
  if (string == "No trigger:" || string == "No trigger" ||
      string == "no trigger:" || string == "no trigger")
    ret = Trigger::NO_TRIGGER;
  else if(string == "At creation:" || string == "At creation" ||
           string == "at creation:" || string == "at creation")
      ret = Trigger::AT_CREATION;
  else if (string == "Start turn:" || string == "Start turn" ||
           string == "start turn:" || string == "start turn")
    ret = Trigger::START_TURN;
  else if (string == "End of turn:" || string == "End of turn" ||
           string == "end of turn:" || string == "end of turn")
    ret = Trigger::END_TURN;
  else
    throw std::invalid_argument(
        "Incorrect string for EffectBase::Trigger initialize.");

  return ret;
}

std::string EffectBase::formattingType(Type type) {
  std::string ret;

  if (type == Type::NO_VALUE_TYPE)
    ret = "No value type.";
  else if (type == Type::COMMON_TYPE)
    ret = "Common type.";
  else if (type == Type::STATUS)
    ret = "Status typr.";
  else if (type == Type::CIRCUMSTANCE)
    ret = "Circumstance type.";
  else if (type == Type::ITEM)
    ret = "Item type.";
  else if (type == Type::LUCK)
    ret = "Luck type.";
  else if (type == Type::PENALTY)
    ret = "Penalty type.";
  else if (type == Type::BONUS)
    ret = "Bonus type.";

  return ret;
}

EffectBase::Type EffectBase::formattingType(const std::string &string) {
  Type ret;

  if (string == "No value type.")
    ret = Type::NO_VALUE_TYPE;
  else if (string == "Common type.")
    ret = Type::COMMON_TYPE;
  else if (string == "Status typr.")
    ret = Type::STATUS;
  else if (string == "Circumstance type.")
    ret = Type::CIRCUMSTANCE;
  else if (string == "Item type.")
    ret = Type::ITEM;
  else if (string == "Luck type.")
    ret = Type::LUCK;
  else if (string == "Penalty type.")
    ret = Type::PENALTY;
  else if (string == "Bonus type.")
    ret = Type::BONUS;

  return ret;
}
}  // namespace pf2e_manager
