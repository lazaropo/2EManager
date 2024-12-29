#include "Combatant.h"

/**
 * @brief Template boost funtions definition. Allow to save/load into txt file.
 * Macro have to be defined in cmake file.
 *
 */
#ifdef _BOOST_SERIALIZATION_TXT_
template <class Archive>
void pf2e_manager::Combatant::save(Archive& ar,
                                   const unsigned int version) const {
  ar& ::boost::serialization::base_object<SubjectBase>(*this);

  ar & _hp_max;
  ar & _hp_tmp;
  ar & _hp_curr;
  ar & _initiative;
  ar & _level;

  ar& formattingSide(_side, false, false);
  ar& formattingVitality(_vitality, false, false);

  ar & _effects;
}

template <class Archive>
void pf2e_manager::Combatant::load(Archive& ar, const unsigned int version) {
  ar& ::boost::serialization::base_object<SubjectBase>(*this);

  ar & _hp_max;
  ar & _hp_tmp;
  ar & _hp_curr;
  ar & _initiative;
  ar & _level;

  std::string side, vitality;

  ar & side;
  ar & vitality;

  _side = formattingSide(side);
  _vitality = formattingVitality(vitality);

  ar & _effects;
}

BOOST_CLASS_EXPORT_IMPLEMENT(pf2e_manager::Combatant);
template void pf2e_manager::Combatant::save<boost::archive::text_oarchive>(
    boost::archive::text_oarchive& ar, const unsigned int version) const;
template void pf2e_manager::Combatant::load<boost::archive::text_iarchive>(
    boost::archive::text_iarchive& ar, const unsigned int version);
#endif
/**
 * @brief Template boost funtions definition. Allow to save/load into xml file.
 * Macro have to be defined in cmake file.
 *
 */
#ifdef _BOOST_SERIALIZATION_XML_

// template class
// ::boost::container::stable_vector<::pf2e_manager::EffectBase*>;

template <class Archive>
void pf2e_manager::Combatant::save(Archive& ar,
                                   const unsigned int version) const {
  if (_hp_max < 1 || _hp_curr < 1 || _hp_curr > _hp_max || _initiative < 1)
    return;
  // using namespace ::boost;
  // using namespace ::boost::serialization;
  // // using namespace ::boost::serialization::nvp;
  // using namespace ::boost::container;
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP(SubjectBase);

  ar& BOOST_SERIALIZATION_NVP(_hp_max);
  ar& BOOST_SERIALIZATION_NVP(_hp_tmp);
  ar& BOOST_SERIALIZATION_NVP(_hp_curr);
  ar& BOOST_SERIALIZATION_NVP(_initiative);
  ar& BOOST_SERIALIZATION_NVP(_level);

  std::string side = formattingSide(_side, false, false);
  std::string vitality = formattingVitality(_vitality, false, false);
  ar& ::boost::make_nvp("_side", side);
  ar& ::boost::make_nvp("_vitality", vitality);

  ar& boost::serialization::make_nvp("_effects", _effects);
  // ar& BOOST_SERIALIZATION_NVP(_effects);
}

template <class Archive>
void pf2e_manager::Combatant::load(Archive& ar, const unsigned int version) {
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP(SubjectBase);

  ar& BOOST_SERIALIZATION_NVP(_hp_max);
  ar& BOOST_SERIALIZATION_NVP(_hp_tmp);
  ar& BOOST_SERIALIZATION_NVP(_hp_curr);
  ar& BOOST_SERIALIZATION_NVP(_initiative);
  ar& BOOST_SERIALIZATION_NVP(_level);

  std::string side, vitality;

  ar& ::boost::make_nvp("_side", side);
  ar& ::boost::make_nvp("_vitality", vitality);

  _side = formattingSide(side);
  _vitality = formattingVitality(vitality);

  ar& BOOST_SERIALIZATION_NVP(_effects);

  if (_hp_max <= 0 || _hp_curr < 0 || _initiative < 1)
    throw std::logic_error(
        "Combatant::save(Archive& ar, const unsigned int version): Input is "
        "not "
        "correct. Name: " +
        _name + " HP max: " + std::to_string(_hp_max) +
        " HP curr: " + std::to_string(_hp_curr) +
        " Initiative: " + std::to_string(_initiative));
}

BOOST_CLASS_EXPORT_IMPLEMENT(pf2e_manager::Combatant);

// template void ::boost::serialization::access::serialize<
//     boost::archive::xml_oarchive,
//     boost::container::stable_vector<pf2e_manager::EffectBase*>>(
//     boost::archive::xml_oarchive& ar,
//     boost::container::stable_vector<pf2e_manager::EffectBase*>&,
//     const unsigned int version);

template void pf2e_manager::Combatant::save<boost::archive::xml_oarchive>(
    boost::archive::xml_oarchive& ar, const unsigned int version) const;
template void pf2e_manager::Combatant::load<boost::archive::xml_iarchive>(
    boost::archive::xml_iarchive& ar, const unsigned int version);

#endif

namespace pf2e_manager {

// void Combatant::setEffectDuration(t_pos_eff pos, int duration) {
//   if (duration < 0) return;

//  //  t_pos_eff it = _effects.begin();
//  //  t_pos_eff it_end = _effects.end();
//  //  while (it != it_end && it != pos) ++it;

//  //  if (it != pos && pos != it_end)
//  //    throw std::runtime_error(
//  //        "There are effect iterators from various Combatants");

//  //  (*pos)->removeEffect();
//  //  if (duration) {
//  //    _effects.insert(_effects.end(), *pos);
//  //    _effects.back()->_duration = duration;
//  //  }
//}

std::string Combatant::formattingSide(Side side, bool is_first_upper,
                                      bool with_colon) {
  std::string ret;
  if (side == Side::TEAM) {
    if (is_first_upper && with_colon)
      ret = "Team:";
    else if (is_first_upper && !with_colon)
      ret = "Team";
    else if (with_colon)
      ret = "team:";
    else
      ret = "team";
  } else if (side == Side::ENEAMY) {
    if (is_first_upper && with_colon)
      ret = "Eneamy:";
    else if (is_first_upper && !with_colon)
      ret = "Eneamy";
    else if (with_colon)
      ret = "eneamy:";
    else
      ret = "eneamy";
  } else if (side == Side::OTHER) {
    if (is_first_upper && with_colon)
      ret = "Other:";
    else if (is_first_upper && !with_colon)
      ret = "Other";
    else if (with_colon)
      ret = "other:";
    else
      ret = "other";
  }

  return ret;
}

Combatant::Side Combatant::formattingSide(const std::string& string) {
  Side ret;
  if (string == "Team:" || string == "Team" || string == "team:" ||
      string == "team")
    ret = Side::TEAM;
  else if (string == "Eneamy:" || string == "Eneamy" || string == "eneamy:" ||
           string == "eneamy")
    ret = Side::ENEAMY;
  else if (string == "Other:" || string == "Other" || string == "other:" ||
           string == "other")
    ret = Side::OTHER;
  else
    throw std::invalid_argument(
        "Incorrect string for Combatant::Size initialize.");

  return ret;
}

std::string Combatant::formattingVitality(Combatant::Vitality vitality,
                                          bool is_first_upper,
                                          bool with_colon) {
  std::string ret;
  if (vitality == Vitality::ALIVE) {
    if (is_first_upper && with_colon)
      ret = "Alive:";
    else if (is_first_upper && !with_colon)
      ret = "Alive";
    else if (with_colon)
      ret = "alive:";
    else
      ret = "alive";
  } else if (vitality == Vitality::DEAD) {
    if (is_first_upper && with_colon)
      ret = "Dead:";
    else if (is_first_upper && !with_colon)
      ret = "Dead";
    else if (with_colon)
      ret = "dead:";
    else
      ret = "dead";
  } else if (vitality == Vitality::CONSTRUCT) {
    if (is_first_upper && with_colon)
      ret = "Construct:";
    else if (is_first_upper && !with_colon)
      ret = "Construct";
    else if (with_colon)
      ret = "construct:";
    else
      ret = "construct";
  }
  return ret;
}

Combatant::Vitality Combatant::formattingVitality(const std::string& string) {
  Vitality ret;
  if (string == "Alive:" || string == "Alive" || string == "alive:" ||
      string == "alive")
    ret = Vitality::ALIVE;
  else if (string == "Dead:" || string == "Dead" || string == "dead:" ||
           string == "dead")
    ret = Vitality::DEAD;
  else if (string == "Construct:" || string == "Construct" ||
           string == "construct:" || string == "construct")
    ret = Vitality::CONSTRUCT;
  else
    throw std::invalid_argument(
        "Incorrect string for Combatant::Size initialize.");

  return ret;
}
}  // namespace pf2e_manager
