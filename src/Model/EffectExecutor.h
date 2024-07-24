#ifndef _EFFECT_EXECUTOR_H_5A2CD4D1_34D7_4D4E_9719_4366951EB28D_
#define _EFFECT_EXECUTOR_H_5A2CD4D1_34D7_4D4E_9719_4366951EB28D_

#include "EffectDirector.h"

namespace pf2e_manager {
class EffectExecutor {
 public:
  EffectExecutor(Mediator* mediator) : _mediator(mediator) {}

  ~EffectExecutor();

  void doNothing() const { ; }

  void createEffect(const std::string& name) { _mediator->makeEffect(name); }

  void createCommand() { ; }

 private:
  Mediator* _mediator;
};
}  // namespace pf2e_manager

#endif