#include "Mediator.h"

namespace pf2e_manager {
Mediator::Mediator(
    std::list<Combatant*>* combatant,
    std::function<int(SubjectBase*, SubjectBase*, const std::string&)> fp)
    : _combatants(combatant),
      _builder(new SimpleEffectBuilder(this)),
      _director(new EffectDirector(_builder)),
      _commands_creator(new CommandsCreator(this)),
      _callback(fp) {
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
  auto effects = &combatant->getEffects();
  Combatant::t_pos_eff it =
      std::find_if(effects->begin(), effects->end(), [&name](EffectBase* eff) {
        if (eff)
          return eff->getName() == name;
        else
          return false;
      });
  if (it != effects->end()) (*it)->removeEffect();

  _director->buildEffectByName(name, duration, value);
  _builder->setInvoker(sender);
  _builder->setReciever(combatant);
  combatant->addEffect(_builder->getSimpleEffect());
  if (!_combatants || _combatants->size()) return;
}

CommandBase* Mediator::makeCommand(SubjectBase* sender, SubjectBase* reciever,
                                   const std::string& name, int value) {
  CommandBase* command =
      _commands_creator->createCommandByName(sender, reciever, value, name);
  doCommand(command);
  return command;
}

}  // namespace pf2e_manager
