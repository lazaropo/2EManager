#ifndef _COMBATANT_H_E1381FAB_5D83_4BD1_AFB3_CE0C044AF33E_
#define _COMBATANT_H_E1381FAB_5D83_4BD1_AFB3_CE0C044AF33E_

#include <algorithm>  //provides std::includes for effect instantiation in collection
#include <stdexcept>
#include <string>
#include <vector>

#include "EffectBase.h"
#include "SubjectBase.h"

#if defined(_BOOST_SERIALIZATION_TXT_) || defined(_BOOST_SERIALIZATION_XML_)

#ifdef _BOOST_SERIALIZATION_TXT_
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#endif

#ifdef _BOOST_SERIALIZATION_XML_
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/nvp.hpp>
#endif

#include <boost/archive/tmpdir.hpp>
#include <boost/config.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/vector.hpp>
#endif

namespace pf2e_manager {

class Combatant : public SubjectBase {
 public:
#if defined(_BOOST_SERIALIZATION_TXT_) || defined(_BOOST_SERIALIZATION_XML_)

  friend std::ostream& operator<<(std::ostream& os, const Combatant* gp);

  friend class ::boost::serialization::access;

  template <class Archive>
  void save(Archive& ar, const unsigned int version) const;
  template <class Archive>
  void load(Archive& ar, const unsigned int version);

  BOOST_SERIALIZATION_SPLIT_MEMBER()
#endif

  using t_pos_eff = std::vector<EffectBase*>::iterator;

  enum class Vitality { ALIVE, DEAD, CONSTRUCT };
  enum class Side { TEAM, ENEAMY, OTHER };

  Combatant()
      : SubjectBase(this),
        _hp_max(-1),
        _hp_tmp(0),
        _hp_curr(-1),
        _initiative(-1),
        _side(Side::OTHER),
        // _name(name),
        _vitality(Vitality::CONSTRUCT) {}

  Combatant(int hp, int initiative, Side side, std::string name,
            Vitality vit = Vitality::ALIVE)
      : SubjectBase(this),
        _hp_max(hp),
        _hp_tmp(0),
        _hp_curr(hp),
        _initiative(initiative),
        _side(side),
        _vitality(vit) {
    if (hp <= 0)
      throw std::logic_error(
          "Combatant(int, int, Side, std::string, Vitality): HP is not "
          "correct.");
    if (initiative <= 0)
      throw std::logic_error(
          "Combatant(int, int, Side, std::string, Vitality): HP is not "
          "correct.");
    setName(name);
    //_effects.clear();
  }

  ~Combatant() {
    for (auto it : _effects) delete it;
  }

  bool operator==(const Combatant& other) {
    return getName() == other.getName();
  }

  bool operator==(const std::string& name) { return getName() == name; }

  /**
   * @brief Definition of less < overload
   * which is condition for std::sort in @class Model class.
   *
   * @param other
   * @return true
   * @return false
   */
  //  friend bool operator<(const Combatant& fisrt, const Combatant& second);
  //  bool operator==(const Combatant& other) {
  //    return getName() == other.getName();
  //  }

  std::vector<EffectBase*>& getEffects() { return _effects; }

  void addEffect(EffectBase* effect) {
    _effects.push_back(effect);
    effect->executeAssociated();
  }

  int removeEffect(EffectBase* effect) {
    int ret_val = -1;
    auto it = std::find(_effects.begin(), _effects.end(), effect);
    if (it != _effects.end()) {
      ret_val = it - _effects.begin();
      _effects.erase(it);
    }
    return ret_val;
  }

  void setEffectDuration(t_pos_eff pos, int duration);

  void notifyTrigger(EffectBase::Trigger trigger) {
    for (auto it : _effects) it->notifyTrigger(trigger);
  }

  static std::string formattingSide(Side side, bool is_first_upper,
                                    bool with_colon);
  static Side formattingSide(const std::string& string);

  static std::string formattingVitality(Vitality side, bool is_first_upper,
                                        bool with_colon);
  static Vitality formattingVitality(const std::string& string);

  int getHPCurr() const { return _hp_curr; }

  void setHPCurr(int value) { _hp_curr = value; }

  int getHPMax() const { return _hp_max; }

  void setHPTmp(int value) { _hp_tmp = value; }

  int getHPTmp() const { return _hp_tmp; }

  Side getSide() const { return _side; }

  Vitality getVitality() const { return _vitality; }

  int getInitiative() const { return _initiative; }

  void setInitiative(int initiavite) { _initiative = initiavite; }

  // friend class SimpleEffect;

 private:
  int _hp_max;
  int _hp_tmp;
  int _hp_curr;
  int _initiative;
  int _level = 0;
  Side _side;
  // std::string _name = "";
  Vitality _vitality;

  std::vector<EffectBase*> _effects = {};
};

// inline bool operator<(const Combatant& fisrt, const Combatant& second) {
//   return fisrt._initiative < second._initiative;
// }

#ifdef _BOOST_SERIALIZATION_XML_

inline std::ostream& operator<<(std::ostream& os,
                                const pf2e_manager::Combatant* instance) {
  os << static_cast<const pf2e_manager::SubjectBase*>(instance);
  os << "PEPPAA " << instance->_hp_max << ' ' << instance->_hp_tmp << ' '
     << instance->_hp_curr << ' ' << instance->_initiative << ' '
     << instance->_level << ' '
     << Combatant::formattingSide(instance->_side, false, false) << ' '
     << Combatant::formattingVitality(instance->_vitality, false, false);

  for (auto it : instance->_effects) os << it << ' ';

  return os;
}
#endif
}  // namespace pf2e_manager

#if defined(_BOOST_SERIALIZATION_TXT_) || defined(_BOOST_SERIALIZATION_XML_)
BOOST_CLASS_EXPORT_KEY(pf2e_manager::Combatant);
#endif

#endif
