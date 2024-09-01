#ifndef _EFFECT_EXECUTOR_H_5A2CD4D1_34D7_4D4E_9719_4366951EB28D_
#define _EFFECT_EXECUTOR_H_5A2CD4D1_34D7_4D4E_9719_4366951EB28D_

#include <functional>

#include "EffectBase.h"
#include "MediatorInterface.h"

namespace pf2e_manager {
class EffectExecutor {
 public:
  EffectExecutor(MediatorInterface* mediator) : _mediator(mediator) {}

  ~EffectExecutor();

  void doNothing() const { ; }

  void execute(SubjectBase* sender, SubjectBase* reciever,
               const std::vector<std::string>& name/*, const int duration = 0,
               const int value = 0*/) {
    for (auto it : name) {
      if (it.find("effect:") == 0) {
        int value = _mediator->getConfirmation(sender, reciever, it);
        if (value >= 0)
          _mediator->makeEffect(sender, reciever, it,
                                420000 /*just big number*/, value);
        else {
          auto effect = dynamic_cast<EffectBase*>(sender);
          if (effect) effect->removeEffect();
        }
      } else if (it.find("command:") == 0) {
        int value = _mediator->getConfirmation(sender, reciever, it);
        auto info = std::vector{std::make_pair(reciever, value)};
        if (value >= 0)
          _mediator->makeCommand(sender, it, info);
        else {
          auto effect = dynamic_cast<EffectBase*>(sender);
          if (effect) effect->removeEffect();
        }
      }
    }
  }

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
