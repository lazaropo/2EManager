#ifndef _INVOKER_H_FB1B5BB7_152F_4BF6_9845_8B4B026A68A9_
#define _INVOKER_H_FB1B5BB7_152F_4BF6_9845_8B4B026A68A9_

#include <list>

#include "CommandBase.h"
#include "CommandsImplementation/CommandsImplementation.h"
#include "EffectDirector.h"

namespace pf2e_manager {
class Mediator {
 public:
  using t_pos_cmd = std::list<CommandBase*>::iterator;

  explicit Mediator(std::list<Combatant>* combatant)
      : _combatants(combatant),
        _builder(new SimpleEffectBuilder()),
        _director(new EffectDirector(_builder)) {
    _builder->reset();
  }

  ~Mediator() {
    delete _director;
    delete _builder;
  }

  void makeEffect(SubjectBase* sender, SubjectBase* reciever,
                  const std::string& name, const int duration = 0,
                  const int value = 0) {
    Combatant* combatant = dynamic_cast<Combatant*>(reciever);
    if (!combatant)
      throw std::runtime_error(
          "Mediator - MakeEffect func: reciever is not Combatant class.");
    _director->buildEffectByName(name, duration, value);
    _builder->setSubject(sender);
    combatant->addEffect(_builder->getSimpleEffect());
  }

  void makeCommand(SubjectBase* sender, SubjectBase* reciever,
                   const std::string& name);

  void undoEffect(SubjectBase* sender, SubjectBase* reciever,
                  const std::string& name);

  void undoCommand(SubjectBase* sender, SubjectBase* reciever,
                   const std::string& name);

  const std::list<CommandBase*>& getCommands() const { return _commands; }

 private:
  std::list<Combatant>* _combatants;
  std::list<CommandBase*> _commands;

  SimpleEffectBuilder* _builder;
  EffectDirector* _director;
};
}  // namespace pf2e_manager

#endif