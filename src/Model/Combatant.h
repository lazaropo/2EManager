#ifndef _COMBATANT_H_E1381FAB_5D83_4BD1_AFB3_CE0C044AF33E_
#define _COMBATANT_H_E1381FAB_5D83_4BD1_AFB3_CE0C044AF33E_

#include <algorithm>  //provides std::includes for effect instantiation in collection
#include <list>
#include <stdexcept>
#include <string>
#include <vector>

#ifdef _USE_BOOST_SERIALIZE_
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#endif

#include "EffectBase.h"
#include "SubjectBase.h"

namespace pf2e_manager {

class Combatant : public SubjectBase {
 public:
  using t_pos_eff = std::vector<EffectBase*>::iterator;

  enum class Vitality { ALIVE, DEAD, CONSTRUCT };
  enum class Side { TEAM, ENEAMY, OTHER };

  Combatant(int hp, int initiative, Side side, std::string name,
            Vitality vit = Vitality::ALIVE)
      : SubjectBase(this),
        _hp_max(hp),
        _hp_tmp(0),
        _hp_curr(hp),
        _initiative(initiative),
        _side(side),
        _vitality(vit) {
    setName(name);
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

#ifdef _USE_BOOST_SERIALIZE_
  friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive & ar, const size_t version) {
    ar & boost::serialization::base_object<SubjectBase>(*this);
    ar & _hp_max;
    ar & _hp_tmp;
    ar & _hp_curr;
    ar & _initiative;
    ar & _level;
    ar & _side;
    ar & _vitality;
    ar & _effects;
  }
#endif

 private:
  int _hp_max;
  int _hp_tmp;
  int _hp_curr;
  int _initiative;
  int _level;
  Side _side;
  // std::string _name = "";
  const Vitality _vitality;

  std::vector<EffectBase*> _effects = {};
};

// inline bool operator<(const Combatant& fisrt, const Combatant& second) {
//   return fisrt._initiative < second._initiative;
// }
}  // namespace pf2e_manager

#endif
