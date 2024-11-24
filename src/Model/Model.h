#ifndef _MODEL_H_1841F277_9334_475B_B5F3_FEBED75CDCF8_
#define _MODEL_H_1841F277_9334_475B_B5F3_FEBED75CDCF8_

#include <algorithm>
#include <initializer_list>
#include <stdexcept>
#include <utility>  // std::pair, std::forward
#include <vector>

#include "Combatant.h"
#include "Mediator.h"

#if !defined(_BOOST_SERIALIZATION_TXT_) && !defined(_BOOST_SERIALIZATION_XML_)
#include "TXTReader.h"
#endif

#if defined(_BOOST_SERIALIZATION_TXT_) || defined(_BOOST_SERIALIZATION_XML_)

#include <cstdio>  // remove
#include <fstream>

#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std {
using ::remove;
}
#endif

#ifdef _BOOST_SERIALIZATION_TXT_
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#endif

#ifdef _BOOST_SERIALIZATION_XML_
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/nvp.hpp>
#endif

#include <boost/archive/tmpdir.hpp>
#include <boost/config.hpp>
#include <boost/exception/all.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/vector.hpp>
#include <boost\serialization\throw_exception.hpp>

#endif

namespace pf2e_manager {
class Model {
#if defined(_BOOST_SERIALIZATION_TXT_) || defined(_BOOST_SERIALIZATION_XML_)

  friend class ::boost::serialization::access;
  template <class Archive>
  void serialize(Archive& ar, const unsigned int version);

  Model() = default;
#endif
 public:
  using t_pos_comb = std::vector<Combatant*>::iterator;
  using t_pair_comb_with_effect = std::pair<t_pos_comb, Combatant::t_pos_eff>;

  Model(std::function<int(SubjectBase*, SubjectBase*, const std::string&)> fp);

  ~Model();

  void addCombatant(Combatant* new_body) {
    // if (_curr_pos == _combatants->end()) {
    //     _combatants->push_back(new_body);
    //     _curr_pos = _combatants->end();
    // } else
    _combatants->push_back(new_body);
    if (_combatants->size() == 1) _curr_pos = _combatants->begin();
  }

  void addCombatant(t_pos_comb pos, Combatant* new_body) {
    if (_curr_pos == _combatants->end()) {
      _combatants->insert(pos, new_body);
      _curr_pos = _combatants->end();
    } else
      _combatants->insert(pos, new_body);
  }

  void moveCombatant(t_pos_comb from, t_pos_comb before);

  CommandBase* makeCommand(
      SubjectBase* sender, const std::string& name,
      std::vector<std::pair<pf2e_manager::SubjectBase*, int>>& info);

  void removeCombatant(t_pos_comb it) { _combatants->erase(it); }
  void removeCombatant(Combatant* ptr) {
    _combatants->erase(
        std::find(_combatants->begin(), _combatants->end(), ptr));
  }

  void removeCommand(CommandBase* command) {
    _mediator->removeCommand(command);
  }

  void removeCombatantGroup(std::vector<t_pos_comb>& collection) {
    for (auto it : collection) removeCombatant(it);
  }

  void addEffect(SimpleEffectBuilder* builder, t_pos_comb pos) {
    builder->setReciever(*pos);
    addEffect(builder, *pos);
  }

  void addEffect(SimpleEffectBuilder* builder, Combatant* pos) {
    builder->setReciever(pos);
    if (pos)
      pos->addEffect(builder->getSimpleEffect());
    else
      builder->reset();
  }

  void makeEffect(SubjectBase* sender, SubjectBase* reciever,
                  const std::string& name, const int duration,
                  const int value) {
    _mediator->makeEffect(sender, reciever, name, duration, value);
  }

  void addEffectOnGroup(SimpleEffectBuilder* builder,
                        std::vector<t_pos_comb>& collection);

  void setEffectDuration(int duration, t_pair_comb_with_effect pair) {
    (*pair.first)->setEffectDuration(pair.second, duration);
  }

  void setEffectDurationOnGroup(
      int duration, std::vector<t_pair_comb_with_effect>& collection) {
    for (auto it : collection) setEffectDuration(duration, it);
  }

  void setCallbackFunctionUserInput(
      std::function<int(SubjectBase*, SubjectBase*, const std::string&)>
          callback) {
    _mediator->setCallbackFunctionUserInput(callback);
  }

  void sortByInit() {
    std::sort(_combatants->begin(), _combatants->end(),
              [](const Combatant* a, const Combatant* b) {
                // the std::greater-like definition. first combatant with
                // greater init and side::eneamy or side::other.
                bool ret = false;
                int init1 = a->getInitiative();
                int init2 = b->getInitiative();
                if (init1 > init2)
                  ret = true;
                else if (init1 == init2 && a->getSide() != b->getSide()) {
                  if (a->getSide() == Combatant::Side::TEAM)
                    ret = false;
                  else if (b->getSide() == Combatant::Side::TEAM)
                    ret = true;
                }
                return ret;
              });
    _curr_pos = _combatants->begin();
  }

  void startTurn();

  void nextTurn();

  const std::vector<Combatant*>* getCombatants() const { return _combatants; }

  std::vector<Combatant*>* getCombatants() { return _combatants; }

  const std::vector<CommandBase*>& getCommands() const {
    return _mediator->getCommands();
  }

  std::vector<CommandBase*>& getCommands() { return _mediator->getCommands(); }

  Combatant* getCurrent() {
    if (!_combatants || _combatants->empty() || _combatants->end() == _curr_pos)
      return nullptr;
    else
      return *_curr_pos;
  }

 private:
  std::vector<Combatant*>* _combatants = new std::vector<Combatant*>();
  MediatorInterface* _mediator = nullptr;

  t_pos_comb _curr_pos;

#ifndef _BOOST_SERIALIZATION_XML_
  FileReaderBase* _reader;
  const std::string _path = ("../Saved_info/info.txt");
#elif _BOOST_SERIALIZATION_XML_
  const std::string _path = (_BOOST_SERIALIZATION_XML_FILEPATH_);
#endif
};

}  // namespace pf2e_manager
#endif
