#ifndef _COMMAND_BASE_H_A9BAA2E5_D89F_4641_8058_A620720B6DA5
#define _COMMAND_BASE_H_A9BAA2E5_D89F_4641_8058_A620720B6DA5

#include "Combatant.h"
#include "EffectBase.h"

namespace pf2e_manager {
class CommandBase {
 public:
  virtual void execute() = 0;
  virtual void undo() = 0;

 private:
};
}  // namespace pf2e_manager
#endif