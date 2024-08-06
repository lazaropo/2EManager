#ifndef _INVOKER_H_FB1B5BB7_152F_4BF6_9845_8B4B026A68A9_
#define _INVOKER_H_FB1B5BB7_152F_4BF6_9845_8B4B026A68A9_

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

  explicit Mediator(std::list<Combatant>* combatant);

  ~Mediator() {
    delete _builder;
    delete _director;
  }

  void makeEffect(SubjectBase* sender, SubjectBase* reciever,
                  const std::string& name, const int duration = 0,
                  const int value = 0) override;

  void makeCommand(SubjectBase* sender, SubjectBase* reciever,
                   const std::string& name, int value) override {
    CommandBase* command =
        _commands_creator->createCommandByName(sender, reciever, value, name);
    makeCommand(command);
  }

  void makeCommand(CommandBase* cmd) { _commands.push_back(cmd); }

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
  std::list<Combatant>* _combatants;
  std::vector<CommandBase*> _commands;

  SimpleEffectBuilder* _builder;
  EffectDirector* _director;

  CommandsCreator* _commands_creator;
};
}  // namespace pf2e_manager

#endif
