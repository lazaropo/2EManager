#include "Mediator.h"

namespace pf2e_manager {
Mediator::Mediator(std::list<Combatant>* combatant)
    : _combatants(combatant),
      _builder(new SimpleEffectBuilder()),
      _director(new EffectDirector(_builder)),
      _commands_creator(new CommandsCreator(this)) {
  _builder->reset();
}

Mediator::~Mediator() {
  for (auto it : _commands) delete it;
  delete _builder;
  delete _director;
}

void Mediator::makeEffect(SubjectBase* sender, SubjectBase* reciever,
                          const std::string& name, const int duration,
                          const int value) {
  Combatant* combatant = dynamic_cast<Combatant*>(reciever);
  if (!combatant)
    throw std::runtime_error(
        "Mediator - MakeEffect func: reciever is not Combatant class.");
  _director->buildEffectByName(name, duration, value);
  _builder->setSubject(sender);
  combatant->addEffect(_builder->getSimpleEffect());
  if (_combatants->size()) return;
}

CommandBase* Mediator::makeCommand(SubjectBase* sender, SubjectBase* reciever,
                                   const std::string& name, int value) {
  CommandBase* command =
      _commands_creator->createCommandByName(sender, reciever, value, name);
  makeCommand(command);
  return command;
}

}  // namespace pf2e_manager
