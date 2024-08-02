#include "Combatant.h"

namespace pf2e_manager {
void Combatant::setEffectDuration(t_pos_eff pos, int duration) {
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
}  // namespace pf2e_manager
