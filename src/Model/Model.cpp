#include "Model.h"

#ifdef _BOOST_SERIALIZATION_TXT_
template <class Archive>
void pf2e_manager::Model::serialize(Archive& ar, const unsigned int version) {
  ar & _combatants;
  ar & _mediator;

  // ar & _curr_pos;
}
BOOST_CLASS_EXPORT_IMPLEMENT(pf2e_manager::Model);

template void pf2e_manager::Model::serialize<boost::archive::text_oarchive>(
    boost::archive::text_oarchive& ar, const unsigned int version);
template void pf2e_manager::Model::serialize<boost::archive::text_iarchive>(
    boost::archive::text_iarchive& ar, const unsigned int version);
#endif

#ifdef _BOOST_SERIALIZATION_XML_
template <class Archive>
void pf2e_manager::Model::serialize(Archive& ar, const unsigned int version) {
  ar& BOOST_SERIALIZATION_NVP(_combatants);
  ar& BOOST_SERIALIZATION_NVP(_mediator);
}
BOOST_CLASS_EXPORT_IMPLEMENT(pf2e_manager::Model);

template void pf2e_manager::Model::serialize<boost::archive::xml_oarchive>(
    boost::archive::xml_oarchive& ar, const unsigned int version);
template void pf2e_manager::Model::serialize<boost::archive::xml_iarchive>(
    boost::archive::xml_iarchive& ar, const unsigned int version);
#endif

namespace pf2e_manager {
#if defined(_BOOST_SERIALIZATION_TXT_) || defined(_BOOST_SERIALIZATION_XML_)

Model::Model(
    std::function<int(SubjectBase*, SubjectBase*, const std::string&)> fp)
    : _mediator(new Mediator(_combatants, fp)) {
  {
    try {
      // open the archive
      std::ifstream ifs(_BOOST_SERIALIZATION_XML_FILEPATH_);
      // std::ifstream ifs0(_BOOST_SERIALIZATION_XML_FILEPATH_);
      int ret_good = ifs.good();
      int ret_in_avail = !ifs.eof();
      // ifs.rdbuf()->in_avail();

      // while (ifs0.good() && !ifs0.eof())
      //     std::cout << static_cast<char>(ifs0.get());

      if (ret_good && ret_in_avail > 0) {
        // boost::archive::xml_iarchive ia(ifs);
        using namespace pf2e_manager;
        using namespace ::boost;
        // ::boost::archive::text_iarchive ia(ifs);
        ::boost::archive::xml_iarchive ia(ifs);
        this->serialize(ia, 0);
      }
    } catch (::boost::exception& ex) {
      typedef ::boost::error_info<struct tag_my_info, int> my_info;
      if (int const* mi = ::boost::get_error_info<my_info>(ex))
        std::cerr << *mi;
    }
  }

  if (!_combatants) _combatants = new std::vector<Combatant*>();
  _curr_pos = _combatants->end();
}
#else
Model::Model(
    std::function<int(SubjectBase*, SubjectBase*, const std::string&)> fp)
    : _mediator(new Mediator(_combatants, fp)),
      _reader(new TXTReader(_mediator)) {
  _combatants = _reader->readCombatants(_path);
  if (!_combatants) _combatants = new std::vector<Combatant*>();
  _curr_pos = _combatants->end();
}
#endif

#if defined(_BOOST_SERIALIZATION_TXT_) || defined(_BOOST_SERIALIZATION_XML_)
Model::~Model() {
  // make an archive
  std::ofstream ofs(_BOOST_SERIALIZATION_XML_FILEPATH_,
                    std::ios_base::out | std::ios_base::trunc);
  if (ofs.good()) {
    // boost::archive::xml_oarchive oa(ofs);
    // ::boost::archive::text_oarchive oa(ofs);
    ::boost::archive::xml_oarchive oa(ofs);

    this->serialize(oa, 0);
  }

  for (auto it : *_combatants) delete it;
  delete _combatants;
  delete _mediator;
}
#else
Model::~Model() {
  _reader->writeCombatants(_path, _combatants);
  delete _reader;
  for (auto it : *_combatants) delete it;
  delete _combatants;
  delete _mediator;
}
#endif

void Model::moveCombatant(t_pos_comb from, t_pos_comb before) {
  // if (before == _combatants->begin()) {
  //     _combatants->insert(before, *from);
  //     _combatants->erase(from);
  if (before == from + 1) return;
  // if (_curr_pos == from) {
  //   //    (*from)->notifyTrigger(SimpleEffect::Trigger::START_TURN);
  //   //    (*from)->notifyTrigger(SimpleEffect::Trigger::END_TURN);
  //   ++_curr_pos;
  // }
  // _combatants->splice(++before, *_combatants, from);
  std::swap(from, before);
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
  else {
    (*_curr_pos)->notifyTrigger(SimpleEffect::Trigger::END_TURN);
    (*_curr_pos++)->notifyTrigger(SimpleEffect::Trigger::START_TURN);
  }

  // if (++_curr_pos == _combatants->end()) _curr_pos = _combatants->begin();
  if (_curr_pos == _combatants->end()) _curr_pos = _combatants->begin();
}

}  // namespace pf2e_manager
