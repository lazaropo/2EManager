#ifndef _COMBATANT_H_E1381FAB_5D83_4BD1_AFB3_CE0C044AF33E
#define _COMBATANT_H_E1381FAB_5D83_4BD1_AFB3_CE0C044AF33E

#include <algorithm>  //provides std::includes for effect instantiation in collection
#include <list>
#include <stdexcept>
#include <string>

#include "EffectBase.h"

namespace pf2e_manager {
class Combatant {
 public:
  using t_pos_eff = std::list<EffectBase*>::iterator;
  enum class Vitality { ALIVE, DEAD, CONSTRUCT };
  enum class Side { TEAM, ENEAMY, OTHER };

  Combatant(/*void (*eventDeath) (Combatant* obj),*/ int hp, int initiative,
            Side side, std::string name, Vitality vit = Vitality::ALIVE)
      : /*f_eventDeath(eventDeath), */ _hp_max(hp),
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

  std::list<EffectBase*>& getEffects() { return _effects; }

  void addEffect(EffectBase* effect) { _effects.push_back(effect); }

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

  // void changeHP(int value) {
  //     if(value > 0 && _hp_curr < _hp_max) {
  //         _hp_curr += value;
  //         if(_hp_curr > _hp_max)
  //             _hp_curr = _hp_max;
  //     } else if(value < 0) {
  //         _hp_curr += value;
  //         if(_hp_curr < 0) {
  //             _hp_curr = 0;
  //             f_eventDeath(this);
  //         }
  //     }
  // }

  friend class CommandBase;
  friend class EffectBase;

 private:
  int _hp_max;
  int _hp_tmp;
  int _hp_curr;
  int _initiative;
  Side _side;
  const Vitality _vitality;
  std::string _name;

  std::list<EffectBase*> _effects;
  // void(*f_eventDeath)(Combatant* object);
};
}  // namespace pf2e_manager

#endif