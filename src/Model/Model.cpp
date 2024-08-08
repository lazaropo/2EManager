#include "Model.h"

namespace pf2e_manager {
void Model::moveCombatant(t_pos_comb from, t_pos_comb before) {
  if (--before == from)
    throw std::range_error(
        "Attempt to move Combatant to its current position.");
  if (_curr_pos == from) {
    startTurn();
    nextTurn();
  }
  _combatants.splice(++before, _combatants, from);
}

void Model::addEffectOnGroup(SimpleEffectBuilder* builder,
                             std::vector<t_pos_comb>& collection) {
  SimpleEffect* effect = builder->getSimpleEffect();
  for (auto it : collection) addEffect(builder, it);
  delete[] effect;
}

CommandBase* Model::makeCommand(SubjectBase* sender, SubjectBase* reciever,
                                const std::string& name, int value) {
  return _mediator->makeCommand(sender, reciever, name, value);
}

void Model::startTurn() {
  if (_combatants.empty())
    throw std::runtime_error("There are not any combatants!");

  if (++_curr_pos == _combatants.end()) _curr_pos = _combatants.begin();

  for (auto it : _combatants)
    for (auto it_eff : it->getEffects())
      it_eff->getTrigger(SimpleEffect::Trigger::START_TURN);
}

void Model::nextTurn() {
  if (_combatants.empty())
    throw std::runtime_error("There are not any combatants!");

  for (auto it : _combatants)
    for (auto it_eff : it->getEffects())
      it_eff->getTrigger(SimpleEffect::Trigger::END_TURN);
}

}  // namespace pf2e_manager
