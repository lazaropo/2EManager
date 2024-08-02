#include "SimpleEffect.h"

namespace pf2e_manager {
SimpleEffect::SimpleEffect(const SimpleEffect& other)
    : SubjectBase(this, other.getObject()),
      _type(other._type),
      _value(other._value),
      _trigger(other._trigger),
      _duration(other._duration),
      _is_active(other._is_active),
      _descprition(other._descprition) {}

void SimpleEffect::execute() {
  --_duration;
  if (_duration < 1) _is_active = false;
}

void SimpleEffect::undo() {
  ++_duration;
  _is_active = _is_active ? false : true;
}

void SimpleEffect::getTrigger(Trigger trigger) {
  if (trigger == _trigger && _is_active) {
    execute();
  }
}

}  // namespace pf2e_manager