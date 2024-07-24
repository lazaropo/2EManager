#ifndef _MODEL_H_1841F277_9334_475B_B5F3_FEBED75CDCF8_
#define _MODEL_H_1841F277_9334_475B_B5F3_FEBED75CDCF8_

#include <algorithm>
#include <initializer_list>
#include <list>
#include <stdexcept>
#include <utility>  // std::pair, std::forward
#include <vector>

#include "Mediator.h"
// #include "SimpleEffectBuilder.h"

namespace pf2e_manager {
class Model {
 public:
  using t_pos_comb = std::list<Combatant>::iterator;
  using t_pair_comb_with_effect = std::pair<t_pos_comb, Combatant::t_pos_eff>;

  void addCombatant(t_pos_comb it, Combatant&& new_body) {
    _combatants.insert(it, std::forward<Combatant>(new_body));
  }
  void addCombatantGroup(std::vector<Combatant&&>& other) {
    for (auto it : other) addCombatant(it, std::forward<Combatant>(it));
  }

  void moveCombatant(t_pos_comb from, t_pos_comb before) {
    if (++before == from)
      throw std::range_error(
          "Attempt to move Combatant to its current position.");
    if (_curr_pos == from) {
      startTurn();
      nextTurn();
    }
    _combatants.splice(--before, _combatants, from);
  }

  void addCommand(CommandBase* cmd) { _mediator.addCommand(cmd) }
  void addAndDoCommand(CommandBase* cmd) { _mediator.addAndDoCommand(cmd); }
  void removeCommand(Invoker::t_pos_cmd pos) { _mediator.undoCommand(pos); }
  void removeCombatant(t_pos_comb it) { _combatants.erase(it); }
  void removeCombatantGroup(std::vector<t_pos_comb>& collection) {
    for (auto it : collection) removeCombatant(it);
  }

  void addEffect(SimpleEffectBuilder* builder, t_pos_comb pos) {
    pos->addEffect(builder->getSimpleEffect());
  }

  void addEffectOnGroup(SimpleEffectBuilder* builder,
                        std::vector<t_pos_comb>& collection) {
    SimpleEffect* effect = builder->getSimpleEffect();
    for (auto it : collection) addEffect(effect->copy(), it);
    delete[] effect;
  }

  void setEffectDuration(int duration, t_pair_comb_with_effect pair) {
    pair.first->setEffectDuration(pair.second, duration);
  }

  void setEffectDurationOnGroup(
      int duration, std::vector<t_pair_comb_with_effect>& collection) {
    for (auto it : collection) setEffectDuration(duration, it);
  }

  void sortByInit() { std::sort(_combatants.rbegin(), _combatants.rend()); }

  void startTurn() {
    if (_combatants.empty())
      throw std::runtime_error("There are not any combatants!");

    if (++_curr_pos == _combatants.end()) _curr_pos = _combatants.begin();

    for (auto it : _combatants)
      for (auto it_eff : it.getEffects())
        it_eff->getTrigger(SimpleEffect::Trigger::START_TURN);
  }

  void nextTurn() {
    if (_combatants.empty())
      throw std::runtime_error("There are not any combatants!");

    for (auto it : _combatants)
      for (auto it_eff : it.getEffects())
        it_eff->getTrigger(SimpleEffect::Trigger::END_TURN);
  }

  const std::list<Combatant>& getCombatants() const { return _combatants; }

  const std::list<CommandBase*>& getCommands() const {
    return _mediator.getCommands();
  }

 private:
  std::list<Combatant> _combatants;
  Mediator* _;

  t_pos_comb _curr_pos;
};
}  // namespace pf2e_manager
#endif
