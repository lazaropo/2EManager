#include "Model.h"

namespace pf2e_manager {
#ifdef _BOOST_SERIALIZATION_XML_
Model::Model(std::function<int(SubjectBase*, SubjectBase*, const std::string&)> fp)
    : _mediator(new Mediator(_combatants, fp))
{
    // open the archive
    std::ifstream ifs(_path);
    assert(ifs.good());
    boost::archive::xml_iarchive ia(ifs);

    // restore the schedule from the archive
    ia >> BOOST_SERIALIZATION_NVP(_combatants);
    ia >> BOOST_SERIALIZATION_NVP(_mediator);

    if (!_combatants)
        _combatants = new std::vector<Combatant*>();
    _curr_pos = _combatants->end();
}
#elif
Model::Model(std::function<int(SubjectBase*, SubjectBase*, const std::string&)> fp)
    : _mediator(new Mediator(_combatants, fp))
    , _reader(new TXTReader(_mediator))
{
    _combatants = _reader->readCombatants(_path);
    if (!_combatants)
        _combatants = new std::vector<Combatant*>();
    _curr_pos = _combatants->end();
}
#endif

#ifdef _BOOST_SERIALIZATION_XML_
Model::~Model()
{
    // make an archive
    std::ofstream ofs(_path);
    assert(ofs.good());
    boost::archive::xml_oarchive oa(ofs);
    oa << BOOST_SERIALIZATION_NVP(_combatants);
    oa << BOOST_SERIALIZATION_NVP(_mediator);

    for (auto it : *_combatants)
        delete it;
    delete _combatants;
    delete _mediator;
}
#elif
Model::~Model()
{
    _reader->writeCombatants(_path, _combatants);
    delete _reader;
    for (auto it : *_combatants)
        delete it;
    delete _combatants;
    delete _mediator;
}
#endif

void Model::moveCombatant(t_pos_comb from, t_pos_comb before) {
  if (--before == from) return;
// if (_curr_pos == from) {
//   //    (*from)->notifyTrigger(SimpleEffect::Trigger::START_TURN);
//   //    (*from)->notifyTrigger(SimpleEffect::Trigger::END_TURN);
//   ++_curr_pos;
// }
// _combatants->splice(++before, *_combatants, from);
std:
    swap(from, before);
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
