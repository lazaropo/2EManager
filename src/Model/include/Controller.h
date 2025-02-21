#ifndef _CONTROLLER_H_27E6C796_B5D1_4569_9523_1218BA0AA3D7_
#define _CONTROLLER_H_27E6C796_B5D1_4569_9523_1218BA0AA3D7_

#include "Model.h"

namespace pf2e_manager {
class Controller {
 public:
  Controller(
      std::function<int(SubjectBase*, SubjectBase*, const std::string&)> fp)
      : _model(new Model(fp)) {}
  ~Controller() { delete _model; }

  void addCombatant(Combatant* new_body) { _model->addCombatant(new_body); }
  //  void addCombatantGroup(Model::t_pos_comb pos, std::vector<Combatant>&
  //  other) {
  //    for (auto it : other) _model->addCombatant(pos, it);
  //  }

  void moveCombatant(Model::t_pos_comb from, Model::t_pos_comb before) {
    _model->moveCombatant(from, before);
  }

  // void addCommand(CommandBase* cmd) { _model->addCommand(cmd); }
  // void addAndDoCommand(CommandBase* cmd) { _model->addAndDoCommand(cmd); }
  // void removeCommand(Mediator::t_pos_cmd pos) { _model->removeCommand(pos); }
  void removeCombatant(Model::t_pos_comb it) { _model->removeCombatant(it); }
  void removeCombatant(Combatant* ptr) { _model->removeCombatant(ptr); }
  void removeCombatantGroup(std::vector<Model::t_pos_comb>& collection) {
    _model->removeCombatantGroup(collection);
  }

  void addEffect(SimpleEffectBuilder* builder, Model::t_pos_comb pos) {
    _model->addEffect(builder, pos);
  }

  void addEffect(SimpleEffectBuilder* builder, Combatant* pos) {
    _model->addEffect(builder, pos);
  }

  void makeEffect(SubjectBase* sender, SubjectBase* reciever,
                  const std::string& name, const int duration,
                  const int value) {
    _model->makeEffect(sender, reciever, name, duration, value);
  }

  void addEffectOnGroup(SimpleEffectBuilder* builder,
                        std::vector<Model::t_pos_comb>& collection) {
    _model->addEffectOnGroup(builder, collection);
  }

  // void setEffectDuration(int duration, Model::t_pair_comb_with_effect pair) {
  //   _model->setEffectDuration(duration, pair);
  // }

  // void setEffectDurationOnGroup(
  //     int duration, std::vector<Model::t_pair_comb_with_effect>& collection)
  //     {
  //   _model->setEffectDurationOnGroup(duration, collection);
  // }

  void activateEffect(EffectBase* effect) { _model->activateEffect(effect); }

  void disactivateEffect(EffectBase* effect) {
    _model->disactivateEffect(effect);
  }

  void removeCommand(CommandBase* command) { _model->removeCommand(command); }

  void setCallbackFunctionUserInput(
      std::function<int(SubjectBase*, SubjectBase*, const std::string&)>
          callback) {
    _model->setCallbackFunctionUserInput(callback);
  }

  CommandBase* makeCommand(
      SubjectBase* sender, const std::string& name,
      std::vector<std::pair<pf2e_manager::SubjectBase*, int>>& info) {
    return _model->makeCommand(sender, name, info);
  }

  void sortByInit() { _model->sortByInit(); }

  void startTurn() { _model->startTurn(); }

  void nextTurn() { _model->nextTurn(); }

  const utility::t_combatant_container* getCombatants() const {
    return _model->getCombatants();
  }

  utility::t_combatant_container* getCombatants() {
    return _model->getCombatants();
  }

  const std::vector<CommandBase*>& getCommands() const {
    return _model->getCommands();
  }

  std::vector<CommandBase*>& getCommands() { return _model->getCommands(); }

  Combatant* getCurrent() { return _model->getCurrent(); }

  size_t addFromFile(const std::string& path) {
    return _model->addFromFile(path);
  }

 private:
  Model* _model;
};
}  // namespace pf2e_manager
#endif
