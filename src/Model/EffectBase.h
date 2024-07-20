#ifndef _EFFECT_BASE_H_82A0C4AB_9EEF_4E15_9F9A_6535D003B2D3
#define _EFFECT_BASE_H_82A0C4AB_9EEF_4E15_9F9A_6535D003B2D3

#include <string>

// #include "Combatant.h"

namespace pf2e_manager {
class EffectBase {
 public:
  enum class Trigger { NO_TRIGGER, START_TURN, END_TURN };
  virtual void execute() = 0;
  virtual void undo() = 0;

  virtual void getTrigger() = 0;

  const std::string& what() const { return _descprition; }

  void removeEffect() {
    _duration = 0;
    _is_active = false;
  }

  friend class Combatant;

  const Trigger _trigger;

 private:
  int _duration;  // per round
  bool _is_active;
  const std::string _descprition;
};
}  // namespace pf2e_manager
#endif