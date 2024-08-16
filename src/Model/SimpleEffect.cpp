#include "SimpleEffect.h"

namespace pf2e_manager {
SimpleEffect::SimpleEffect(const SimpleEffect &other)
    : EffectBase(this, other.getReciever())

{
  _type = other._type;
  _value = other._value;
  _trigger = other._trigger;
  _duration = other._duration;
  _is_active = other._is_active;
  _description = other._description;
}

void SimpleEffect::execute() {
  --_duration;
  if (_execute_actions.size())
    _executor->execute(getSubject(), getReciever(), _execute_actions);
  if (_duration < 1) _is_active = false;
}

void SimpleEffect::undo() {
  ++_duration;
  _is_active = _is_active ? false : true;
}

}  // namespace pf2e_manager
