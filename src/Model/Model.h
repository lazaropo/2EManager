#ifndef _MODEL_H_1841F277_9334_475B_B5F3_FEBED75CDCF8_
#define _MODEL_H_1841F277_9334_475B_B5F3_FEBED75CDCF8_

#include <algorithm>
#include <initializer_list>
#include <list>
#include <stdexcept>
#include <utility>  // std::pair, std::forward
#include <vector>

#include "Combatant.h"
#include "Mediator.h"
// #include "SimpleEffectBuilder.h"

namespace pf2e_manager {
class Model {
 public:
  using t_pos_comb = std::list<Combatant>::iterator;
  using t_pair_comb_with_effect = std::pair<t_pos_comb, Combatant::t_pos_eff>;

  // void addCombatant(t_pos_comb pos, Combatant new_body) {
  //   _combatants.insert(pos, std::move(new_body));
  // }

  void addCombatant(/*t_pos_comb pos, */ Combatant&& new_body) {
    _combatants.push_back(/*pos, */ std::forward<Combatant>(new_body));
  }

  void addCombatant(t_pos_comb pos, Combatant&& new_body) {
    _combatants.insert(pos, std::forward<Combatant>(new_body));
  }

  void addCombatantGroup(t_pos_comb pos, std::vector<Combatant>& other) {
    for (auto it : other) addCombatant(pos, std::move(it));
  }

  void moveCombatant(t_pos_comb from, t_pos_comb before);

  void addCommand(CommandBase* cmd) { _mediator->makeCommand(cmd); }
  // void addAndDoCommand(CommandBase* cmd) { _mediator->addAndDoCommand(cmd); }
  void removeCommand(Mediator::t_pos_cmd pos) { _mediator->undoCommand(pos); }
  void removeCombatant(t_pos_comb it) { _combatants.erase(it); }
  void removeCombatantGroup(std::vector<t_pos_comb>& collection) {
    for (auto it : collection) removeCombatant(it);
  }

  void addEffect(SimpleEffectBuilder* builder, t_pos_comb pos) {
    builder->setReciever(&(*pos));
    addEffect(builder, &(*pos));
  }

  void addEffect(SimpleEffectBuilder* builder, Combatant* pos) {
    builder->setReciever(pos);
    pos->addEffect(builder->getSimpleEffect());
  }

  void addEffectOnGroup(SimpleEffectBuilder* builder,
                        std::vector<t_pos_comb>& collection);

  void setEffectDuration(int duration, t_pair_comb_with_effect pair) {
    pair.first->setEffectDuration(pair.second, duration);
  }

  void setEffectDurationOnGroup(
      int duration, std::vector<t_pair_comb_with_effect>& collection) {
    for (auto it : collection) setEffectDuration(duration, it);
  }

  void sortByInit() {
    _combatants.sort([](const Combatant& a, const Combatant& b) {
      return a.getInitiative() < b.getInitiative();
    });
  }

  void startTurn();

  void nextTurn();

  const std::list<Combatant>& getCombatants() const { return _combatants; }

  std::list<Combatant>& getCombatants() { return _combatants; }

  const std::list<CommandBase*>& getCommands() const {
    return _mediator->getCommands();
  }

 private:
  std::list<Combatant> _combatants;
  Mediator* _mediator;

  t_pos_comb _curr_pos;
};
}  // namespace pf2e_manager
#endif
