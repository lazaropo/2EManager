#ifndef _INVOKER_H_FB1B5BB7_152F_4BF6_9845_8B4B026A68A9_
#define _INVOKER_H_FB1B5BB7_152F_4BF6_9845_8B4B026A68A9_

#include <list>

#include "CommandBase.h"
#include "CommandsImplementation/CommandsImplementation.h"
#include "ComplexEffect.h"
#include "SimpleEffect.h"

namespace pf2e_manager {
class Mediator {
 public:
  using t_pos_cmd = std::list<CommandBase*>::iterator;

  // void addCommand(CommandBase* cmd) { _commands.push_back(cmd); }

  // void addAndDoCommand(CommandBase* cmd) {
  //   addCommand(cmd);
  //   _commands.back()->execute();
  // }

  // void undoCommand(t_pos_cmd pos) { (*pos)->undo(); }

  // void heal(int value, Combatant* comb) {
  //   // HealCommand* hcmd = new HealCommand()
  // }

  // void harm(int value, Combatant* comb) {}

  void makeEffect(SubjectBase* sender, SubjectBase* reciever,
                  const std::string& name);

  void makeCommand(SubjectBase* sender, SubjectBase* reciever,
                   const std::string& name);

  void undoEffect(SubjectBase* sender, SubjectBase* reciever,
                  const std::string& name);

  void undoCommand(SubjectBase* sender, SubjectBase* reciever,
                   const std::string& name);

  const std::list<CommandBase*>& getCommands() const { return _commands; }

 private:
  std::list<Combatant>* _combatants;
  std::list<CommandBase*> _commands;
};
}  // namespace pf2e_manager

#endif