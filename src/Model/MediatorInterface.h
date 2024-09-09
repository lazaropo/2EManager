#ifndef _MEDIATOR_INTERFACE_H_250D0D9E_9EBB_482B_B709_09EEB6A3AD7D_
#define _MEDIATOR_INTERFACE_H_250D0D9E_9EBB_482B_B709_09EEB6A3AD7D_

#include <vector>

#include "CommandBase.h"
#include "SubjectBase.h"


namespace pf2e_manager {
class MediatorInterface {
 public:
  virtual ~MediatorInterface() = default;

  virtual int getConfirmation(SubjectBase* sender, SubjectBase* reciever,
                              const std::string& name) = 0;

  virtual void makeEffect(SubjectBase* sender, SubjectBase* reciever,
                          const std::string& name, const int duration = 0,
                          const int value = 0) = 0;

  virtual CommandBase* makeCommand(
      SubjectBase* sender, const std::string& name,
      std::vector<std::pair<pf2e_manager::SubjectBase*, int>>& info) = 0;

  virtual void undoEffect(SubjectBase* sender, SubjectBase* reciever,
                          const std::string& name) = 0;

  virtual void undoCommand(SubjectBase* sender, SubjectBase* reciever,
                           const std::string& name) = 0;

  virtual const std::vector<CommandBase*>& getCommands() const = 0;
  virtual std::vector<CommandBase*>& getCommands() = 0;
};
}  // namespace pf2e_manager

#endif
