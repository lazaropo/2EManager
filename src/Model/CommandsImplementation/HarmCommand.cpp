#include "HarmCommand.h"

namespace pf2e_manager {

void HarmCommand::execute(int value) {
  if (value <= 0 || _is_active) return;

  _value = value;

  Combatant* combatant = dynamic_cast<Combatant*>(this->getReciever());
  if (!combatant)
    throw std::runtime_error(
        "HarmCommand - execute func: reciever is not Combatant class.");

  int curr_hp = combatant->getHPCurr();
  if (curr_hp <= _value) {
    combatant->setHPCurr(0);
    _mediator->makeEffect(getSubject(), getReciever(), "effect:dying",
                          420000 /*very big duration*/, 1);
  } else {
    combatant->setHPCurr(curr_hp - _value);
  }

  _is_active = true;
}

void HarmCommand::undo() {
  if (!_is_active) return;

  Combatant* combatant = dynamic_cast<Combatant*>(getReciever());
  if (!combatant)
    throw std::runtime_error(
        "HarmCommand - execute func: reciever is not Combatant class.");

  int curr_hp = combatant->getHPCurr();
  if (curr_hp <= 0) {
    combatant->setHPCurr(_value);
    _mediator->undoEffect(getSubject(), getReciever(), "effect:dying");
  } else {
    combatant->setHPCurr(curr_hp + _value);
  }

  _is_active = false;
}
}  // namespace pf2e_manager
