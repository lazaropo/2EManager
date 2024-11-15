#include "MassHarmCommand.h"

// #ifdef _BOOST_SERIALIZATION_XML_
// BOOST_CLASS_EXPORT(pf2e_manager::HarmCommand);
// BOOST_CLASS_EXPORT(pf2e_manager::MassHarmCommand);
// #endif

namespace pf2e_manager {

MassHarmCommand::MassHarmCommand(
    MediatorInterface *mediator, SubjectBase *sender,
    const std::vector<std::pair<SubjectBase *, int> > &info)
    : CommandBase(info[0].second, this), _mediator(mediator) {
  setName("command:massharm");
  setInvoker(sender);
  setReciever(info[0].first);

  for (auto it : info)
    _info.push_back(new HarmCommand(_mediator, this, it.first, it.second));
}

void MassHarmCommand::execute() {
  if (_is_active) return;

  for (auto it : _info) it->execute();

  _is_active = true;
}

void MassHarmCommand::undo() {
  if (!_is_active) return;

  for (auto it : _info) it->undo();

  _is_active = false;
}
}  // namespace pf2e_manager
