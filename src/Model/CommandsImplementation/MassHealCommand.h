#ifndef _MASSHEALCOMMAND_H_21A81540_5E46_11EF_A550_0800200C9A66_
#define _MASSHEALCOMMAND_H_21A81540_5E46_11EF_A550_0800200C9A66_

#include <utility>

#include "HealCommand.h"

namespace pf2e_manager {
class MassHealCommand : public CommandBase {
 public:
  MassHealCommand(MediatorInterface *mediator, SubjectBase *sender,
                  const std::vector<std::pair<SubjectBase *, int>> &info);

  /**
   * @brief Do from do/undo. _is_active == true accords currect exertion of
   * this effect. So, if it's true the damage is  caused. If not (command
   * was undone) the damage is saved, but doesn't caused rigth now.
   *
   * @param value damage value
   */
  void execute() override;

  void undo() override;

  const std::vector<HealCommand *> &getInfo() const { return _info; }

 private:
  MediatorInterface *_mediator;
  std::vector<HealCommand *> _info;
};
}  // namespace pf2e_manager

#endif  // MASSHEALCOMMAND_H
