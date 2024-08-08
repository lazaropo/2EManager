#ifndef _HEAL_COMMAND_H_BFB637A6_33DB_4A0F_A6B4_DBAF10B671A4_
#define _HEAL_COMMAND_H_BFB637A6_33DB_4A0F_A6B4_DBAF10B671A4_

#include "../Combatant.h"
#include "../CommandBase.h"

namespace pf2e_manager {
class HealCommand : public CommandBase {
 public:
  HealCommand(MediatorInterface* mediator, SubjectBase* sender,
              SubjectBase* reciever, int value)
      : CommandBase(value, this), _mediator(mediator) {
    setName("command:heal");
    setInvoker(sender);
    setReciever(reciever);
  }
  void execute() override;

  void undo() override;

 private:
  MediatorInterface* _mediator;
};
}  // namespace pf2e_manager

#endif
