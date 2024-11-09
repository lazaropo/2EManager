#ifndef _MODEL_H_1841F277_9334_475B_B5F3_FEBED75CDCF8_
#define _MODEL_H_1841F277_9334_475B_B5F3_FEBED75CDCF8_

#include <algorithm>
#include <initializer_list>
#include <list>
#include <stdexcept>
#include <utility>  // std::pair, std::forward
#include <vector>

#include "Combatant.h"
#include "Mediator.h"
#include "TXTReader.h"
// #include "SimpleEffectBuilder.h"

namespace pf2e_manager {
class Model {
 public:
  using t_pos_comb = std::list<Combatant*>::iterator;
  using t_pair_comb_with_effect = std::pair<t_pos_comb, Combatant::t_pos_eff>;

  Model(std::function<int(SubjectBase*, SubjectBase*, const std::string&)> fp);

  ~Model();

  void addCombatant(Combatant* new_body) { _combatants->push_back(new_body); }

  void addCombatant(t_pos_comb pos, Combatant* new_body) {
    _combatants->insert(pos, new_body);
  }

  void moveCombatant(t_pos_comb from, t_pos_comb before);

  CommandBase* makeCommand(
      SubjectBase* sender, const std::string& name,
      std::vector<std::pair<pf2e_manager::SubjectBase*, int>>& info);

  void removeCombatant(t_pos_comb it) { _combatants->erase(it); }
  void removeCombatant(Combatant* ptr) { _combatants->remove(ptr); }

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

  void sortByInit() {
    _combatants->sort([](const Combatant* a, const Combatant* b) {
      // the std::greater-like definition. first combatant with greater init and
      // side::eneamy or side::other.
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

  const std::list<Combatant*>* getCombatants() const { return _combatants; }

  std::list<Combatant*>* getCombatants() { return _combatants; }

  const std::vector<CommandBase*>& getCommands() const {
    return _mediator->getCommands();
  }

  std::vector<CommandBase*>& getCommands() { return _mediator->getCommands(); }

  Combatant* getCurrent()
  {
      if (_curr_pos == _combatants->end())
          return nullptr;
      else
          return *_curr_pos;
  }

  private:
  std::list<Combatant*>* _combatants = nullptr;
  MediatorInterface* _mediator;

  t_pos_comb _curr_pos;

  FileReaderBase* _reader;
#ifdef __CMAKE_IS_USED__
  const std::string _path = (__CMAKE_IS_USED__);
#else
  const std::string _path = ("../Saved_info/info.txt");
#endif
};
}  // namespace pf2e_manager
#endif
