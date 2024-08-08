#include "HealCommand.h"

namespace pf2e_manager {
void HealCommand::execute() {
  if (_value <= 0 || _is_active) return;

  Combatant* combatant = dynamic_cast<Combatant*>(this->getReciever());
  if (!combatant)
    throw std::runtime_error(
        "HealCommand - execute func: reciever is not Combatant class.");

  int curr_hp = combatant->getHPCurr();
  int max_hp = combatant->getHPMax();
  if (curr_hp <= 0) {
    combatant->setHPCurr(_value);
    // now sender is nullptr. but actually it must work without direction of
    // sender
    _mediator->undoEffect(nullptr, combatant, "effect:dying");
  } else if (curr_hp < max_hp) {
    int hp = curr_hp + _value;
    if (hp > max_hp) hp = max_hp;
    combatant->setHPCurr(hp);
  }

  _is_active = true;
}

void HealCommand::undo() {
  if (!_is_active) return;

  Combatant* combatant = dynamic_cast<Combatant*>(getReciever());
  if (!combatant)
    throw std::runtime_error(
        "HealCommand - execute func: reciever is not Combatant class.");

  int curr_hp = combatant->getHPCurr();
  if (curr_hp <= _value) {
    combatant->setHPCurr(0);
    _mediator->makeEffect(getSubject(), getReciever(), "effect:dying",
                          420000 /*very big duration*/, 1);
  } else {
    combatant->setHPCurr(curr_hp - _value);
  }

  _is_active = false;
}
}  // namespace pf2e_manager
