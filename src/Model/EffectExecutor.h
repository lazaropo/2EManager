#ifndef _EFFECT_EXECUTOR_H_5A2CD4D1_34D7_4D4E_9719_4366951EB28D_
#define _EFFECT_EXECUTOR_H_5A2CD4D1_34D7_4D4E_9719_4366951EB28D_

#include "MediatorInterface.h"

namespace pf2e_manager {
class EffectExecutor {
 public:
  EffectExecutor(MediatorInterface* mediator) : _mediator(mediator) {}

  ~EffectExecutor();

  void doNothing() const { ; }

  void createEffect(SubjectBase* sender, SubjectBase* reciever,
                    const std::string& name, const int duration = 0,
                    const int value = 0) {
    _mediator->makeEffect(sender, reciever, name, duration, value);
  }

  void createCommand() { ; }

 private:
  MediatorInterface* _mediator;
};
}  // namespace pf2e_manager

#endif
