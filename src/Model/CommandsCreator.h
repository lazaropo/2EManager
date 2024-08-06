#ifndef _COMMANDSCREATOR_H_15D57684_AB87_4A8A_94DD_B388CCABF02C_
#define _COMMANDSCREATOR_H_15D57684_AB87_4A8A_94DD_B388CCABF02C_

#include <functional>  // std::bind, std::function
#include <map>
#include <string>

#include "CommandBase.h"
#include "CommandsImplementation.h"
#include "MediatorInterface.h"
#include "SubjectBase.h"

namespace pf2e_manager {
class CommandsCreator {
 public:
  CommandsCreator(MediatorInterface* mediator) : _mediator(mediator) {}
  CommandBase* createCommandByName(SubjectBase* sender, SubjectBase* reciever,
                                   int value, const std::string name);

  CommandBase* createHarm(SubjectBase* sender, SubjectBase* reciever,
                          int value);
  CommandBase* createHeal(SubjectBase* sender, SubjectBase* reciever,
                          int value);

 private:
  std::map<const std::string,
           std::function<CommandBase*(SubjectBase*, SubjectBase*, int)>>
      _commands_dictionary;

  MediatorInterface* _mediator;
};
}  // namespace pf2e_manager

#endif  // COMMANDSCREATOR_H
