#include "CommandsCreator.h"

namespace pf2e_manager {
CommandsCreator::CommandsCreator(MediatorInterface* mediator)
    : _mediator(mediator) {
  using namespace std::placeholders;
  _commands_dictionary.insert(std::pair(
      "command:harm", std::bind(&CommandsCreator::createHarm, this, _1, _2)));
  _commands_dictionary.insert(std::pair(
      "command:heal", std::bind(&CommandsCreator::createHeal, this, _1, _2)));
  _commands_dictionary.insert(
      std::pair("command:massharm",
                std::bind(&CommandsCreator::createMassHarm, this, _1, _2)));
  _commands_dictionary.insert(
      std::pair("command:massheal",
                std::bind(&CommandsCreator::createMassHeal, this, _1, _2)));
  _commands_dictionary.insert(
      std::pair("command:decreasemaxhp",
                std::bind(&CommandsCreator::createDecreaseMaxHp, this, _1, _2)));
}

CommandBase* CommandsCreator::createCommandByName(
    SubjectBase* sender, const std::string& name,
    std::vector<std::pair<pf2e_manager::SubjectBase*, int>>& info) {
  CommandBase* command = nullptr;

  if (_commands_dictionary.find(name) != _commands_dictionary.end()) {
    command = (_commands_dictionary[name])(sender, info);
  }

  return command;
}

CommandBase* CommandsCreator::createHarm(
    SubjectBase* sender,
    std::vector<std::pair<pf2e_manager::SubjectBase*, int>>& info) {
  return new HarmCommand(_mediator, sender, info[0].first, info[0].second);
}

CommandBase* CommandsCreator::createHeal(
    SubjectBase* sender,
    std::vector<std::pair<pf2e_manager::SubjectBase*, int>>& info) {
  return new HealCommand(_mediator, sender, info[0].first, info[0].second);
}

CommandBase* CommandsCreator::createMassHarm(
    SubjectBase* sender,
    std::vector<std::pair<pf2e_manager::SubjectBase*, int>>& info) {
  return new MassHarmCommand(_mediator, sender, info);
}

CommandBase* CommandsCreator::createMassHeal(
    SubjectBase* sender,
    std::vector<std::pair<pf2e_manager::SubjectBase*, int>>& info) {
  return new MassHealCommand(_mediator, sender, info);
}

    CommandBase* CommandsCreator::createDecreaseMaxHp(
        SubjectBase* sender,
        std::vector<std::pair<pf2e_manager::SubjectBase*, int>>& info) {
    return new DecreaseMaxHpCommand(_mediator, sender, info[0].first, info[0].second);
}


}  // namespace pf2e_manager
