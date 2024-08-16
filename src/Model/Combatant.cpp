#include "Combatant.h"

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
