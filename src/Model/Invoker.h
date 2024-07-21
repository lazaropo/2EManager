#ifndef _INVOKER_H_FB1B5BB7_152F_4BF6_9845_8B4B026A68A9_
#define _INVOKER_H_FB1B5BB7_152F_4BF6_9845_8B4B026A68A9_

#include <list>

#include "CommandBase.h"

namespace pf2e_manager {
class Invoker {
 public:
  using t_pos_cmd = std::list<CommandBase*>::iterator;

  void addCommand(CommandBase* cmd) { _commands.push_back(cmd); }

  void addAndDoCommand(CommandBase* cmd) {
    addCommand(cmd);
    _commands.back()->execute();
  }

  void undoCommand(t_pos_cmd pos) { (*pos)->undo(); }

  void heal(int value, Combatant* comb) {
    // HealCommand* hcmd = new HealCommand()
  }

  void harm(int value, Combatant* comb) {}

  const std::list<CommandBase*>& getCommands() const { return _commands; }

 private:
  std::list<CommandBase*> _commands;
};
}  // namespace pf2e_manager

#endif