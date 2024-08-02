#ifndef _CONTROLLER_H_27E6C796_B5D1_4569_9523_1218BA0AA3D7_
#define _CONTROLLER_H_27E6C796_B5D1_4569_9523_1218BA0AA3D7_

#include "Model.h"

namespace pf2e_manager {
class Controller {
 public:
  Controller() : _model(new Model()) {}
  ~Controller() { delete _model; }

  void addCombatant(/*Model::t_pos_comb pos, */ Combatant&& new_body) {
    _model->addCombatant(/*pos, */ std::forward<Combatant>(new_body));
  }
  void addCombatantGroup(Model::t_pos_comb pos, std::vector<Combatant>& other) {
    for (auto it : other) _model->addCombatant(pos, std::move(it));
  }

  void moveCombatant(Model::t_pos_comb from, Model::t_pos_comb before) {
    _model->moveCombatant(from, before);
  }

  void addCommand(CommandBase* cmd) { _model->addCommand(cmd); }
  // void addAndDoCommand(CommandBase* cmd) { _model->addAndDoCommand(cmd); }
  void removeCommand(Mediator::t_pos_cmd pos) { _model->removeCommand(pos); }
  void removeCombatant(Model::t_pos_comb it) { _model->removeCombatant(it); }
  void removeCombatantGroup(std::vector<Model::t_pos_comb>& collection) {
    _model->removeCombatantGroup(collection);
  }

  void addEffect(SimpleEffectBuilder* builder, Model::t_pos_comb pos) {
    _model->addEffect(builder, pos);
  }

  void addEffect(SimpleEffectBuilder* builder, Combatant* pos) {
    _model->addEffect(builder, pos);
  }

  void addEffectOnGroup(SimpleEffectBuilder* builder,
                        std::vector<Model::t_pos_comb>& collection) {
    _model->addEffectOnGroup(builder, collection);
  }

  void setEffectDuration(int duration, Model::t_pair_comb_with_effect pair) {
    _model->setEffectDuration(duration, pair);
  }

  void setEffectDurationOnGroup(
      int duration, std::vector<Model::t_pair_comb_with_effect>& collection) {
    _model->setEffectDurationOnGroup(duration, collection);
  }

  void sortByInit() { _model->sortByInit(); }

  void startTurn() { _model->startTurn(); }

  void nextTurn() { _model->nextTurn(); }

  const std::list<Combatant>& getCombatants() const {
    return _model->getCombatants();
  }

  std::list<Combatant>& getCombatants() { return _model->getCombatants(); }

  const std::list<CommandBase*>& getCommands() const {
    return _model->getCommands();
  }

 private:
  Model* _model;
};
}  // namespace pf2e_manager
#endif
