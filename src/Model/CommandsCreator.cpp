#include "CommandsCreator.h"

namespace pf2e_manager {
CommandsCreator::CommandsCreator() {
  using namespace std::placeholders;
  _commands_dictionary.insert(
      std::pair("command:harm",
                std::bind(&CommandsCreator::createHarm, this, _1, _2, _3)));
  _commands_dictionary.insert(
      std::pair("command:heal",
                std::bind(&CommandsCreator::createHeal, this, _1, _2, _3)));
}

CommandBase* CommandsCreator::createHarm(SubjectBase* sender,
                                         SubjectBase* reciever, int value) {
  CommandBase* ret = new HarmCommand()
}
}  // namespace pf2e_manager
