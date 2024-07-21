#ifndef _SIMPLE_EFFECT_BUILDER_H_072812C7_047C_4E92_BEB5_1B9FF10FD818_
#define _SIMPLE_EFFECT_BUILDER_H_072812C7_047C_4E92_BEB5_1B9FF10FD818_

#include "SimpleEffect.h"

namespace {
using ns_trigger = pf2e_manager::SimpleEffect::Trigger;
using ns_type = pf2e_manager::SimpleEffect::Type;
}  // namespace

namespace pf2e_manager {
class SimpleEffectBuilder {
 public:
  SimpleEffectBuilder() { reset(); }
  ~SimpleEffectBuilder() { delete[] _effect; }

  SimpleEffectBuilder& setNoType() {
    int mask = 0;
    mask |= ns_type::PENALTY;
    mask |= ns_type::BONUS;
    _effect->_type &= mask;
    _effect->_type |= ns_type::NO_VALUE_TYPE;
  }

  SimpleEffectBuilder& setCommonType() {
    setNoType();
    _effect->_type |= ns_type::COMMON_TYPE;
  }

  SimpleEffectBuilder& setStatusType() {
    setNoType();
    _effect->_type |= ns_type::STATUS;
  }

  SimpleEffectBuilder& setCircumstanceType() {
    setNoType();
    _effect->_type |= ns_type::CIRCUMSTANCE;
  }

  SimpleEffectBuilder& setItemType() {
    setNoType();
    _effect->_type |= ns_type::ITEM;
  }

  SimpleEffectBuilder& setLuckType() {
    setNoType();
    _effect->_type |= ns_type::LUCK;
  }

  SimpleEffectBuilder& setPenaltyType() {
    int mask = 0;
    mask |= ns_type::PENALTY;
    mask |= ns_type::BONUS;
    mask = ~mask;
    _effect->_type &= mask;
    _effect->_type |= ns_type::PENALTY;
  }

  SimpleEffectBuilder& setBonusType() {
    int mask = 0;
    mask |= ns_type::PENALTY;
    mask |= ns_type::BONUS;
    mask = ~mask;
    _effect->_type &= mask;
    _effect->_type |= ns_type::BONUS;
  }

  SimpleEffectBuilder& setNoTrigger() {
    _effect->_trigger = ns_trigger::NO_TRIGGER;
  }

  SimpleEffectBuilder& setStartTrigger() {
    _effect->_trigger = ns_trigger::START_TURN;
  }

  SimpleEffectBuilder& setEndTrigger() {
    _effect->_trigger = ns_trigger::END_TURN;
  }

  SimpleEffectBuilder& setConstantValue() {
    _effect->_value._is_constant = true;
  }

  SimpleEffectBuilder& setNoConstantValue() {
    _effect->_value._is_constant = false;
  }

  SimpleEffectBuilder& setValueMagnitude(int value) {
    _effect->_value._value = value;
  }

  SimpleEffectBuilder& setStrValue(int value) { _effect->_value._str = value; }

  SimpleEffectBuilder& setDexValue(int value) { _effect->_value._dex = value; }

  SimpleEffectBuilder& setConValue(int value) { _effect->_value._con = value; }

  SimpleEffectBuilder& setMindValue(int value) {
    _effect->_value._mind = value;
  }

  SimpleEffectBuilder& setFortValue(int value) {
    _effect->_value._fort = value;
  }

  SimpleEffectBuilder& setReflValue(int value) {
    _effect->_value._refl = value;
  }

  SimpleEffectBuilder& setWillValue(int value) {
    _effect->_value._will = value;
  }

  SimpleEffectBuilder& setSkillsValue(int value) {
    _effect->_value._skills = value;
  }

  SimpleEffectBuilder& setPercValue(int value) {
    _effect->_value._perc = value;
  }

  SimpleEffectBuilder& setAtkValue(int value) { _effect->_value._atk = value; }

  SimpleEffectBuilder& setAcValue(int value) { _effect->_value._ac = value; }

  SimpleEffectBuilder& setDcValue(int value) { _effect->_value._dc = value; }

  SimpleEffectBuilder& setDuration(int value) {
    if (value < 0) return;
    if (!value) _effect->_is_active = false;

    _effect->_duration = value;
  }

  SimpleEffectBuilder& setDescription(const std::string& text) {
    _effect->_descprition = text;
  }

  SimpleEffectBuilder& setName(const std::string& name) {
    _effect->_name = name;
  }

  virtual void reset() {
    if (!_effect) _effect = new SimpleEffect();
  }

  virtual SimpleEffect* getSimpleEffect() {
    SimpleEffect* ret = _effect;
    _effect = nullptr;
    reset();
    return ret;
  }

 private:
  SimpleEffect* _effect = nullptr;
}
}  // namespace pf2e_manager

#endif