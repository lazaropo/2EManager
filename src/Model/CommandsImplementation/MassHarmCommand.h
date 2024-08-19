#ifndef _MASSHARMCOMMAND_H_F65E13E0_5E2B_11EF_A550_0800200C9A66_
#define _MASSHARMCOMMAND_H_F65E13E0_5E2B_11EF_A550_0800200C9A66_

#include <utility>

#include "HarmCommand.h"

namespace pf2e_manager {
class MassHarmCommand : public CommandBase {
 public:
  MassHarmCommand(MediatorInterface *mediator, SubjectBase *sender,
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

  const std::vector<HarmCommand *> &getInfo() const { return _info; }

 private:
  MediatorInterface *_mediator;
  std::vector<HarmCommand *> _info;
};
}  // namespace pf2e_manager

#endif  // MASSHARMCOMMAND_H
