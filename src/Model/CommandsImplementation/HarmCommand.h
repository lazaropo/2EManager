#ifndef _HARM_COMMAND_H_B682292B_D042_4EEB_A771_67735725CE78_
#define _HARM_COMMAND_H_B682292B_D042_4EEB_A771_67735725CE78_

#include "../Combatant.h"
#include "../CommandBase.h"
#include "../MediatorInterface.h"

namespace pf2e_manager {
class HarmCommand : public CommandBase {
 public:
  HarmCommand(MediatorInterface* mediator, SubjectBase* sender,
              SubjectBase* reciever, int value)
      : CommandBase(value, this), _mediator(mediator) {
    setName("command:harm");
    setInvoker(sender);
    setReciever(reciever);
  }
  /**
   * @brief Do from do/undo. _is_active == true accords currect exertion of this
   * effect. So, if it's true the damage is  caused. If not (command was undone)
   * the damage is saved, but doesn't caused rigth now.
   *
   * @param value damage value
   */
  void execute(int value) override;

  void undo() override;

 private:
  MediatorInterface* _mediator;
};
}  // namespace pf2e_manager

#endif
