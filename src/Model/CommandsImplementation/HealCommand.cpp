#include "HealCommand.h"

namespace pf2e_manager {
void HealCommand::execute(int value) override {
  if (value <= 0 || _is_active) return;

  _value = value;

  Combatant* combatant = dynamic_cast<Combatant*>(this->getReciever());
  if (!combatant)
    throw std::runtime_error(
        "HealCommand - execute func: reciever is not Combatant class.");

  int curr_hp = combatant->getHPCurr();
  int max_hp = combatant->getHPMax();
  if (curr_hp <= 0) {
    combatant->setHPCurr(value);
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

void HealCommand::undo() override {
  if (!_is_active) return;

  Combatant* combatant = dynamic_cast<Combatant*>(getReciever());
  if (!combatant)
    throw std::runtime_error(
        "HealCommand - execute func: reciever is not Combatant class.");

  int curr_hp = combatant->getHPCurr();
  int max_hp = combatant->getHPMax();

  if (combatant->getHPCurr() > 0) {
    combatant->setHPCurr(combatant->getHPCurr() - _value);

    if (combatant->getHPCurr() < 0) combatant->setHPCurr(0);
  }
  _is_active = false;
}
}  // namespace pf2e_manager
