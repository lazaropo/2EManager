#include "Model.h"

namespace pf2e_manager {

Model::Model(
    std::function<int(SubjectBase*, SubjectBase*, const std::string&)> fp)
    : _mediator(new Mediator(_combatants, fp))
#ifdef _USE_TXT_READER_
      , _reader(new TXTReader(_mediator))
#endif
{
#ifdef _USE_TXT_READER_
  _combatants = _reader->readCombatants(_path);
#endif
  if (!_combatants) _combatants = new std::list<Combatant*>();
  _curr_pos = _combatants->end();
}

Model::~Model() {
#ifdef _USE_TXT_READER_
  _reader->writeCombatants(_path, _combatants);
  delete _reader;
#endif
  for (auto it : *_combatants) delete it;
  delete _combatants;
  delete _mediator;
}

void Model::moveCombatant(t_pos_comb from, t_pos_comb before) {
  if (--before == from) return;
  if (_curr_pos == from)
    ++_curr_pos;

  _combatants->splice(++before, *_combatants, from);
}

void Model::addEffectOnGroup(SimpleEffectBuilder* builder,
                             std::vector<t_pos_comb>& collection) {
  SimpleEffect* effect = builder->getSimpleEffect();
  for (auto it : collection) addEffect(builder, it);
  delete[] effect;
}

CommandBase* Model::makeCommand(
    SubjectBase* sender, const std::string& name,
    std::vector<std::pair<pf2e_manager::SubjectBase*, int>>& info) {
  return _mediator->makeCommand(sender, name, info);
}

void Model::startTurn() {
  if (!_combatants || _combatants->empty())
    throw std::runtime_error("There are not any combatants!");
}

void Model::nextTurn() {
  if (!_combatants || _combatants->empty())
    throw std::runtime_error("There are not any combatants!");

  if (_curr_pos == _combatants->end())
    _curr_pos = _combatants->begin();
  else
    (*_curr_pos++)->notifyTrigger(SimpleEffect::Trigger::END_TURN);

  // if (++_curr_pos == _combatants->end()) _curr_pos = _combatants->begin();
  if (_curr_pos == _combatants->end()) _curr_pos = _combatants->begin();
  (*_curr_pos)->notifyTrigger(SimpleEffect::Trigger::START_TURN);
}

}  // namespace pf2e_manager
