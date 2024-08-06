#ifndef _SIMPLE_EFFECT_BUILDER_H_072812C7_047C_4E92_BEB5_1B9FF10FD818_
#define _SIMPLE_EFFECT_BUILDER_H_072812C7_047C_4E92_BEB5_1B9FF10FD818_

#include "SimpleEffect.h"
#include "SubjectBase.h"

namespace {}  // namespace

namespace pf2e_manager {
// class SimpleEffect;
class SimpleEffectBuilder {
 public:
  using ns_trigger = pf2e_manager::SimpleEffect::Trigger;
  using ns_type = pf2e_manager::SimpleEffect::Type;

  SimpleEffectBuilder() : _effect(new SimpleEffect()) {}

  ~SimpleEffectBuilder() { delete _effect; }

  SimpleEffectBuilder* setNoType() {
    int mask = 0;
    mask |= ns_type::PENALTY;
    mask |= ns_type::BONUS;
    _effect->_type &= mask;
    _effect->_type |= ns_type::NO_VALUE_TYPE;
    return this;
  }

  SimpleEffectBuilder* setCommonType() {
    setNoType();
    _effect->_type |= ns_type::COMMON_TYPE;
    return this;
  }

  SimpleEffectBuilder* setStatusType() {
    setNoType();
    _effect->_type |= ns_type::STATUS;
    return this;
  }

  SimpleEffectBuilder* setCircumstanceType() {
    setNoType();
    _effect->_type |= ns_type::CIRCUMSTANCE;
    return this;
  }

  SimpleEffectBuilder* setItemType() {
    setNoType();
    _effect->_type |= ns_type::ITEM;
    return this;
  }

  SimpleEffectBuilder* setLuckType() {
    setNoType();
    _effect->_type |= ns_type::LUCK;
    return this;
  }

  SimpleEffectBuilder* setPenaltyType() {
    int mask = 0;
    mask |= ns_type::PENALTY;
    mask |= ns_type::BONUS;
    mask = ~mask;
    _effect->_type &= mask;
    _effect->_type |= ns_type::PENALTY;
    return this;
  }

  SimpleEffectBuilder* setBonusType() {
    int mask = 0;
    mask |= ns_type::PENALTY;
    mask |= ns_type::BONUS;
    mask = ~mask;
    _effect->_type &= mask;
    _effect->_type |= ns_type::BONUS;
    return this;
  }

  SimpleEffectBuilder* setNoTrigger() {
    _effect->_trigger = ns_trigger::NO_TRIGGER;
    return this;
  }

  SimpleEffectBuilder* setStartTrigger() {
    _effect->_trigger = ns_trigger::START_TURN;
    return this;
  }

  SimpleEffectBuilder* setEndTrigger() {
    _effect->_trigger = ns_trigger::END_TURN;
    return this;
  }

  SimpleEffectBuilder* setConstantValue() {
    _effect->_value._is_constant = true;
    return this;
  }

  SimpleEffectBuilder* setNoConstantValue() {
    _effect->_value._is_constant = false;
    return this;
  }

  SimpleEffectBuilder* setValueMagnitude(int value) {
    _effect->_value._value = value;
    return this;
  }

  SimpleEffectBuilder* setStrValue(int value) {
    _effect->_value._str = value;
    return this;
  }

  SimpleEffectBuilder* setDexValue(int value) {
    _effect->_value._dex = value;
    return this;
  }

  SimpleEffectBuilder* setConValue(int value) {
    _effect->_value._con = value;
    return this;
  }

  SimpleEffectBuilder* setMindValue(int value) {
    _effect->_value._mind = value;
    return this;
  }

  SimpleEffectBuilder* setFortValue(int value) {
    _effect->_value._fort = value;
    return this;
  }

  SimpleEffectBuilder* setReflValue(int value) {
    _effect->_value._refl = value;
    return this;
  }

  SimpleEffectBuilder* setWillValue(int value) {
    _effect->_value._will = value;
    return this;
  }

  SimpleEffectBuilder* setSkillsValue(int value) {
    _effect->_value._skills = value;
    return this;
  }

  SimpleEffectBuilder* setPercValue(int value) {
    _effect->_value._perc = value;
    return this;
  }

  SimpleEffectBuilder* setAtkValue(int value) {
    _effect->_value._atk = value;
    return this;
  }

  SimpleEffectBuilder* setAcValue(int value) {
    _effect->_value._ac = value;
    return this;
  }

  SimpleEffectBuilder* setDcValue(int value) {
    _effect->_value._dc = value;
    return this;
  }

  SimpleEffectBuilder* setInitiativeValue(int value) {
    _effect->_value._init = value;
    return this;
  }

  SimpleEffectBuilder* setEveryValue(int value) {
    setStrValue(value)
        ->setDexValue(value)
        ->setConValue(value)
        ->setMindValue(value)
        ->setFortValue(value)
        ->setReflValue(value)
        ->setWillValue(value)
        ->setSkillsValue(value)
        ->setPercValue(value)
        ->setAtkValue(value)
        ->setAcValue(value)
        ->setDcValue(value)
        ->setInitiativeValue(value);
    return this;
  }

  SimpleEffectBuilder* setDuration(int value) {
    if (value < 0) return this;
    if (!value) _effect->_is_active = false;

    _effect->_duration = value;
    return this;
  }

  SimpleEffectBuilder* setDescription(const std::string& text) {
    _effect->_descprition = text;
    return this;
  }

  SimpleEffectBuilder* setName(const std::string& name) {
    _effect->setName(name);
    return this;
  }

  SimpleEffectBuilder* setAssociatedActions(
      const std::list<std::string>& actions) {
    _effect->_associated_actions = actions;
    return this;
  }

  SimpleEffectBuilder* setReciever(SubjectBase* reciever) {
    _effect->setReciever(reciever);
    return this;
  }

  SimpleEffectBuilder* setCreator(SubjectBase* creator) {
    _effect->setInvoker(creator);
    return this;
  }

  /* virtual */ void reset() {
    if (!_effect) {
      _effect = new SimpleEffect();
      _effect->_subject = _effect;
    }
  }

  /*virtual*/ void setSubject(SubjectBase* object) {
    if (_effect) {
      _effect->setReciever(object);
    }
  }

  /* virtual*/ SimpleEffect* getSimpleEffect() {
    SimpleEffect* ret = _effect;
    _effect = nullptr;
    reset();
    return ret;
  }

 private:
  SimpleEffect* _effect = nullptr;
};
}  // namespace pf2e_manager

#endif
