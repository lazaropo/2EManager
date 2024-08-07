#ifndef _COMBATANT_H_E1381FAB_5D83_4BD1_AFB3_CE0C044AF33E_
#define _COMBATANT_H_E1381FAB_5D83_4BD1_AFB3_CE0C044AF33E_

#include <algorithm>  //provides std::includes for effect instantiation in collection
#include <list>
#include <stdexcept>
#include <string>
#include <vector>

#include "SimpleEffect.h"
#include "SubjectBase.h"

namespace pf2e_manager {

class Combatant : public SubjectBase {
 public:
  using t_pos_eff = std::vector<SimpleEffect*>::iterator;

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
        // _name(name),
        _vitality(vit) {
    setName(name);
    //_effects.clear();
  }

  ~Combatant() {
    for (auto it : _effects) delete it;
  }

  bool operator==(const Combatant& other) {
    return getReciever() == other.getReciever();
  }

  /**
   * @brief Definition of less < overload
   * which is condition for std::sort in @class Model class.
   *
   * @param other
   * @return true
   * @return false
   */
  friend bool operator<(const Combatant& fisrt, const Combatant& second);

  std::vector<SimpleEffect*>& getEffects() { return _effects; }

  void addEffect(SimpleEffect* effect) { _effects.push_back(effect); }

  void setEffectDuration(t_pos_eff pos, int duration);

  int getHPCurr() const { return _hp_curr; }

  void setHPCurr(int value) { _hp_curr = value; }

  int getHPMax() const { return _hp_max; }

  void setHPTmp(int value) { _hp_tmp = value; }

  int getHPTmp() const { return _hp_tmp; }

  Side getSide() const { return _side; }

  Vitality getVitality() const { return _vitality; }

  // const std::string getName() const { return _name; }

  // void setName(const std::string& name) { _name = name; }

  int getInitiative() const { return _initiative; }

  friend class SimpleEffect;

 private:
  int _hp_max;
  int _hp_tmp;
  int _hp_curr;
  int _initiative;
  int _level;
  Side _side;
  // std::string _name = "";
  const Vitality _vitality;

  std::vector<SimpleEffect*> _effects = {};
};

inline bool operator<(const Combatant& fisrt, const Combatant& second) {
  return fisrt._initiative < second._initiative;
}
}  // namespace pf2e_manager

#endif
