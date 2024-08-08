#ifndef _EFFECT_BASE_H_82A0C4AB_9EEF_4E15_9F9A_6535D003B2D3_
#define _EFFECT_BASE_H_82A0C4AB_9EEF_4E15_9F9A_6535D003B2D3_

#include <algorithm>  // std::swap
#include <list>
#include <string>

#include "EffectExecutor.h"
#include "MediatorInterface.h"
// #include "SubjectBase.h"

namespace pf2e_manager {
class Combatant;
class Mediator;
class SimpleEffect : public SubjectBase {
 public:
  enum class Trigger { NO_TRIGGER, START_TURN, END_TURN };
  enum Type {
    NO_VALUE_TYPE = 0,
    COMMON_TYPE = 1 << 0,
    STATUS = 1 << 1,
    CIRCUMSTANCE = 1 << 2,
    ITEM = 1 << 3,
    LUCK = 1 << 4,
    PENALTY = 1 << 5,
    BONUS = 1 << 6
  };
  struct Value {
    Value() = default;
    explicit Value(bool is_constant, int value)
        : _is_constant(is_constant), _value(value) {}

    operator bool() const { return _value; }

    bool _is_constant = true;
    int _value = 0;

    int _str = 0;
    int _dex = 0;
    int _con = 0;
    int _mind = 0;

    int _fort = 0;
    int _refl = 0;
    int _will = 0;

    int _skills = 0;
    int _perc = 0;  // perception

    int _atk = 0;
    int _ac = 0;
    int _dc = 0;  // class DC
    int _init = 0;
  };

  SimpleEffect() : SubjectBase(this) {}

  SimpleEffect(const SimpleEffect& other);

  SimpleEffect(SimpleEffect&& other) : SimpleEffect(other) {}

  SimpleEffect* copy() { return new SimpleEffect(*this); }

  void execute();

  void undo();

  void notifyTrigger(Trigger trigger);

  int getDuration() const { return _duration; }
  int getValue() const { return _value._value; }

  // const std::string getName() const { return _name; }
  const std::string& what() const { return _descprition; }

  void removeEffect() {
    _duration = 0;
    _is_active = false;
  }

  friend class Combatant;
  friend class SimpleEffectBuilder;

  // const Trigger _trigger;

 protected:
  int _type = 0;  // bit field
  Value _value = Value();
  Trigger _trigger = Trigger::NO_TRIGGER;
  int _duration = 0;  // per round
  bool _is_active = false;
  // std::string _name = "";
  std::string _descprition = "";

  std::list<std::string> _associated_actions = std::list<std::string>();

  EffectExecutor* _executor = nullptr;

  MediatorInterface* _mediator = nullptr;
};
}  // namespace pf2e_manager
#endif
