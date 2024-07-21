#ifndef _COMMAND_BASE_H_A9BAA2E5_D89F_4641_8058_A620720B6DA5
#define _COMMAND_BASE_H_A9BAA2E5_D89F_4641_8058_A620720B6DA5

#include <string>

#include "Combatant.h"

namespace pf2e_manager {
class CommandBase {
 public:
  virtual void execute(int value) = 0;
  virtual void undo() = 0;

 protected:
  Combatant* _combatant;
  int _value = 0;
  bool _is_active = true;
  std::string _invoker = "";
  std::string _receiver = "";
};
}  // namespace pf2e_manager
#endif