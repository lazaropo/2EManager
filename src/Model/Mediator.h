#ifndef _INVOKER_H_FB1B5BB7_152F_4BF6_9845_8B4B026A68A9_
#define _INVOKER_H_FB1B5BB7_152F_4BF6_9845_8B4B026A68A9_

#include <functional>  // std::function
#include <list>
#include <string>

#include "CommandBase.h"
#include "CommandsCreator.h"
#include "EffectDirector.h"
#include "MediatorInterface.h"
#include "SubjectBase.h"

namespace pf2e_manager {
class Mediator : public MediatorInterface {
 public:
  using t_pos_cmd = std::vector<CommandBase*>::iterator;

  explicit Mediator(
      std::list<Combatant*>* combatant,
      std::function<int(SubjectBase*, SubjectBase*, const std::string&)> fp);

  ~Mediator();

  int getConfirmation(SubjectBase* sender, SubjectBase* reciever,
                      const std::string& name) override {
    return _callback(sender, reciever, name);
  }

  void makeEffect(SubjectBase* sender, SubjectBase* reciever,
                  const std::string& name, const int duration = 0,
                  const int value = 0) override;

  CommandBase* makeCommand(SubjectBase* sender, SubjectBase* reciever,
                           const std::string& name, int value) override;

  void doCommand(CommandBase* cmd) {
    cmd->execute();
    _commands.push_back(cmd);
  }

  void undoEffect(__attribute__((unused)) SubjectBase* sender,
                  __attribute__((unused)) SubjectBase* reciever,
                  __attribute__((unused)) const std::string& name) override {}

  void undoCommand(__attribute__((unused)) SubjectBase* sender,
                   __attribute__((unused)) SubjectBase* reciever,
                   __attribute__((unused)) const std::string& name) override {}

  void undoCommand(t_pos_cmd pos) { (*pos)->undo(); }

  const std::vector<CommandBase*>& getCommands() const override {
    return _commands;
  }

  std::vector<CommandBase*>& getCommands() override { return _commands; }

 private:
  std::list<Combatant*>* _combatants;
  std::vector<CommandBase*> _commands;

  SimpleEffectBuilder* _builder;
  EffectDirector* _director;

  CommandsCreator* _commands_creator;

  std::function<int(SubjectBase*, SubjectBase*, const std::string&)> _callback;
};
}  // namespace pf2e_manager

#endif
