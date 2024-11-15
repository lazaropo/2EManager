#ifndef _COMPLEX_EFFECT_H_A71E0A0B_E0BB_487B_AE85_D2C709BEDEF3_
#define _COMPLEX_EFFECT_H_A71E0A0B_E0BB_487B_AE85_D2C709BEDEF3_

#include <list>

#include "SimpleEffect.h"

namespace pf2e_manager {
class ComplexEffect : public SimpleEffect {
 public:
  void execute() override {
    // --_duration;
    if (_duration-- < 1) _is_active = false;

    for (auto it : _commands_and_effects) {
      if (it.find("effect:") == 0)
          _mediator->makeEffect(this, getReciever(), it /*num of sym in "effect:"*/);
      else if (it.find("command:") == 0)
          _mediator->makeCommand(this, getReciever(), it /*num of sym in "command:"*/);
    }
  }

  void undo() override {
    ++_duration;

    for (auto it : _commands_and_effects) {
      if (it.find("effect:") == 0)
          _mediator->undoEffect(this, getReciever(), it /*8 - num of sym in "effect:"*/);
      else if (it.find("command:") == 0)
          _mediator->undoCommand(this, getReciever(), it /*9 - num of sym in "command:"*/);
    }

    _is_active = _is_active ? false : true;
  }

  friend class ComplexEffectBuilder;

 private:
  std::list<std::string> _commands_and_effects;
  // Combatant* _combatant;
  // void (*fp_execute)(int, Combatant*);
  // int (*fp_get_new_value)(const std::string&, const Combatant*);
};
}  // namespace pf2e_manager

#endif
