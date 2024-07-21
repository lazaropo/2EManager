#ifndef _COMPLEX_EFFECT_H_A71E0A0B_E0BB_487B_AE85_D2C709BEDEF3_
#define _COMPLEX_EFFECT_H_A71E0A0B_E0BB_487B_AE85_D2C709BEDEF3_

#include "SimpleEffect.h"
// #include "Invoker.h"

namespace pf2e_manager {
class ComplexEffect : public SimpleEffect {
 public:
  void execute() override {
    --_duration;
    if (_duration < 1) _is_active = false;
    if (_value._is_constant)
      fp_execute(_value._value, _combatant);
    else
      fp_execute(fp_get_new_value(_name, _combatant), _combatant);
  }

  friend class ComplexEffectBuilder;

 private:
  // Invoker* _invoker;
  Combatant* _combatant;
  void (*fp_execute)(int, Combatant*);
  int (*fp_get_new_value)(const std::string&, const Combatant*);
};
}  // namespace pf2e_manager

#endif