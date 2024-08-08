#include "CommandsCreator.h"

namespace pf2e_manager {
CommandsCreator::CommandsCreator(MediatorInterface* mediator)
    : _mediator(mediator) {
  using namespace std::placeholders;
  _commands_dictionary.insert(
      std::pair("command:harm",
                std::bind(&CommandsCreator::createHarm, this, _1, _2, _3)));
  _commands_dictionary.insert(
      std::pair("command:heal",
                std::bind(&CommandsCreator::createHeal, this, _1, _2, _3)));
}

CommandBase* CommandsCreator::createCommandByName(SubjectBase* sender,
                                                  SubjectBase* reciever,
                                                  int value,
                                                  const std::string name) {
  CommandBase* command = nullptr;
  if (_commands_dictionary.find(name) != _commands_dictionary.end())
    command = (_commands_dictionary[name])(sender, reciever, value);

  return command;
}

CommandBase* CommandsCreator::createHarm(SubjectBase* sender,
                                         SubjectBase* reciever, int value) {
  return new HarmCommand(_mediator, sender, reciever, value);
}

CommandBase* CommandsCreator::createHeal(SubjectBase* sender,
                                         SubjectBase* reciever, int value) {
  return new HealCommand(_mediator, sender, reciever, value);
}

}  // namespace pf2e_manager
