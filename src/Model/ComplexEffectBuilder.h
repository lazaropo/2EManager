#ifndef _COMPLEX_EFFECT_BUILDER_H_5688AAED_2A4A_4E65_B8C3_F7A75F625177_
#define _COMPLEX_EFFECT_BUILDER_H_5688AAED_2A4A_4E65_B8C3_F7A75F625177_

#include <stdexcept>

#include "ComplexEffect.h"
#include "SimpleEffectBuilder.h"

namespace pf2e_manager {
class ComplexEffectBuilder : public SimpleEffectBuilder {
 public:
  ComplexEffectBuilder() { reset(); }
  ~ComplexEffectBuilder() { delete[] _effect; }

  void reset() override {
    if (!_effect) _effect = new ComplexEffect();
  }

  ComplexEffect* getComplexEffect() {
    ComplexEffect* ret = _effect;
    _effect = nullptr;
    reset();
    return ret;
  }

  SimpleEffect* getSimpleEffect() final {
    throw std::runtime_error(
        "Attempt to get SimpleEffect base-class from Complex Effect class "
        "builder.");
  }

  ComplexEffectBuilder& setCombatant(Combatant* combatant) {
    _effect->_combatant = combatant;
  }

  ComplexEffectBuilder& setCallbackExecution(void (*fp)(int, Combatant*)) {
    _effect->fp_execute = fp;
  }

  ComplexEffectBuilder& setCallbackNewValueSetter(int (*fp)(const std::string&,
                                                            const Combatant*)) {
    _effect->fp_get_new_value = fp;
  }

 private:
  ComplexEffect* _effect = nullptr;
};
}  // namespace pf2e_manager

#endif