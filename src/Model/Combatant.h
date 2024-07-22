#ifndef _COMBATANT_H_E1381FAB_5D83_4BD1_AFB3_CE0C044AF33E_
#define _COMBATANT_H_E1381FAB_5D83_4BD1_AFB3_CE0C044AF33E_

#include <algorithm>  //provides std::includes for effect instantiation in collection
#include <list>
#include <stdexcept>
#include <string>

#include "SimpleEffect.h"
#include "SubjectBase.h"

namespace pf2e_manager {
class Combatant : public SubjectBase {
 public:
  using t_pos_eff = std::list<SimpleEffect*>::iterator;

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
        _name(name),
        _vitality(vit) {}

  ~Combatant() {
    for (auto it : _effects) delete it;
  }

  /**
   * @brief Definition of less < overload
   * which is condition for std::sort in @class Model class.
   *
   * @param other
   * @return true
   * @return false
   */
  bool operator<(const Combatant& other) {
    return this->_initiative < other._initiative;
  }

  std::list<SimpleEffect*>& getEffects() { return _effects; }

  const std::string& getName() const { return _name; }

  void addEffect(SimpleEffect* effect) { _effects.push_back(effect); }

  void setEffectDuration(t_pos_eff pos, int duration) {
    if (duration < 0) return;

    t_pos_eff it = _effects.begin();
    t_pos_eff it_end = _effects.end();
    while (it != it_end && it != pos) ++it;

    if (it != pos && pos != it_end)
      throw std::runtime_error(
          "There are effect iterators from various Combatants");

    (*pos)->removeEffect();
    if (duration) {
      _effects.insert(_effects.end(), *pos);
      _effects.back()->_duration = duration;
    }
  }

  int getHPCurr() const { return _hp_curr; }

  void setHPCurr(int value) { _hp_curr = value; }

  int getHPMax() const { return _hp_max; }

  int setHPTmp(int value) { _hp_tmp = value; }

  int getHPTmp() const { return _hp_tmp; }

  Side getSide() const { return _side; }

  Vitality getVitality() const { return _vitality; }

  const std::string& getName() const { return _name; }

  void setName(const std::string& name) { _name = name; }

  friend class SimpleEffect;

 private:
  int _hp_max;
  int _hp_tmp;
  int _hp_curr;
  int _initiative;
  Side _side;
  const Vitality _vitality;
  std::string _name;

  std::list<SimpleEffect*> _effects;
  // void(*f_eventDeath)(Combatant* object);
};
}  // namespace pf2e_manager

#endif