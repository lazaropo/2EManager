#ifndef _INVOKER_H_FB1B5BB7_152F_4BF6_9845_8B4B026A68A9_
#define _INVOKER_H_FB1B5BB7_152F_4BF6_9845_8B4B026A68A9_

#include <list>
#include <string>

#include "CommandBase.h"
#include "CommandsImplementation.h"
#include "EffectDirector.h"
#include "MediatorInterface.h"
#include "SubjectBase.h"

namespace pf2e_manager {
class Mediator : public MediatorInterface {
 public:
  using t_pos_cmd = std::list<CommandBase*>::iterator;

  explicit Mediator(std::list<Combatant>* combatant);

  ~Mediator() {
    delete _builder;
    delete _director;
  }

  void makeEffect(SubjectBase* sender, SubjectBase* reciever,
                  const std::string& name, const int duration = 0,
                  const int value = 0) override;

  // void makeCommand(SubjectBase* sender, SubjectBase* reciever,
  //                  const std::string& name) override;

  void makeCommand(CommandBase* cmd) { _commands.push_back(cmd); };

  // void undoEffect(SubjectBase* sender, SubjectBase* reciever,
  //                 const std::string& name) override;

  // void undoCommand(SubjectBase* sender, SubjectBase* reciever,
  //                  const std::string& name) override;

  void undoCommand(t_pos_cmd pos) { _commands.erase(pos); };

  const std::list<CommandBase*>& getCommands() const override {
    return _commands;
  }

 private:
  std::list<Combatant>* _combatants;
  std::list<CommandBase*> _commands;

  SimpleEffectBuilder* _builder;
  EffectDirector* _director;
};
}  // namespace pf2e_manager

#endif
