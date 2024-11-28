#ifndef _COMMANDSCREATOR_H_15D57684_AB87_4A8A_94DD_B388CCABF02C_
#define _COMMANDSCREATOR_H_15D57684_AB87_4A8A_94DD_B388CCABF02C_

#include <functional>  // std::bind, std::function
#include <map>
#include <string>
#include <utility>  // std::pair
#include <vector>

#include "CommandBase.h"
#include "CommandsImplementation.h"
#include "MediatorInterface.h"
#include "SubjectBase.h"

namespace pf2e_manager {
class CommandsCreator {
 public:
  CommandsCreator(MediatorInterface* mediator);

  CommandBase* createCommandByName(
      SubjectBase* sender, const std::string& name,
      std::vector<std::pair<SubjectBase*, int>>& info);

  CommandBase* createHarm(SubjectBase* sender,
                          std::vector<std::pair<SubjectBase*, int>>& info);
  CommandBase* createHeal(SubjectBase* sender,
                          std::vector<std::pair<SubjectBase*, int>>& info);
  CommandBase* createMassHarm(SubjectBase* sender,
                              std::vector<std::pair<SubjectBase*, int>>& info);
  CommandBase* createMassHeal(SubjectBase* sender,
                              std::vector<std::pair<SubjectBase*, int>>& info);
  CommandBase* createDecreaseMaxHp(SubjectBase* sender,
                              std::vector<std::pair<SubjectBase*, int>>& info);

 private:
  std::map<const std::string,
           std::function<CommandBase*(
               SubjectBase*, std::vector<std::pair<SubjectBase*, int>>& info)>>
      _commands_dictionary;

  MediatorInterface* _mediator;
};
}  // namespace pf2e_manager

#endif  // COMMANDSCREATOR_H
