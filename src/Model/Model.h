#ifndef _MODEL_H_1841F277_9334_475B_B5F3_FEBED75CDCF8_
#define _MODEL_H_1841F277_9334_475B_B5F3_FEBED75CDCF8_

#include <algorithm>
#include <initializer_list>
#include <list>
#include <stdexcept>
#include <utility>

#include "Invoker.h"

namespace pf2e_manager {
class Model {
 public:
  using t_pos_comb = std::list<Combatant>::iterator;

  void addCombatant(t_pos_comb it, Combatant&& new_body) {
    _combatants.insert(it, std::forward(new_body));
  }
  void addCombatantGroup(t_pos_comb it, Combatant&&... other) {
    addCombatant(it, std::forward(other))...;
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

  void addCommand(CommandBase* cmd) { involer.addCommand(cmd) }
  void addAndDoCommand(CommandBase* cmd) { involer.addAndDoCommand(cmd); }
  void removeCommand(Invoker::t_pos_cmd pos) { invoker.undoCommand(pos); }
  void removeCombotant(t_pos_comb it) { _combatants.erase(it); }
  void removeCombatantGroup(t_pos_comb... it) { removeCombotant(it)...; }

  // void addEffect(t_pos_comb pos, EffectBase* effect) {
  //     pos.
  // }
  // setEffectDuration(t_pos_eff pos, int duration) {

  // }

  void sortByInit() { std::sort(_combatants.rbegin(), _combatants.rend()); }

  void startTurn() {
    if (_combatants.empty())
      throw std::runtime_error("There are not any combatants!");

    if (++_curr_pos == _combatants.end()) _curr_pos = _combatants.begin();

    for (auto it : _combatants.getEffects())
      it.getTrigger(EffectBase::Trigger::START_TURN);
  }

  void nextTurn() {
    if (_combatants.empty())
      throw std::runtime_error("There are not any combatants!");

    for (auto it : _combatants.getEffects())
      it.getTrigger(EffectBase::Trigger::END_TURN);
  }

  const std::list<Combatant>& getCombatants() const { return _combatants; }

  const std::list<CommandBase*>& getCommands() const { return _commands; }

 private:
  std::list<Combatant> _combatants;
  std::list<CommandBase*> _commands;
  Invoker _invoker;

  t_pos_comb _curr_pos;
};
}  // namespace pf2e_manager
#endif