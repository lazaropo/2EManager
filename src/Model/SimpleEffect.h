#ifndef _EFFECT_BASE_H_82A0C4AB_9EEF_4E15_9F9A_6535D003B2D3_
#define _EFFECT_BASE_H_82A0C4AB_9EEF_4E15_9F9A_6535D003B2D3_

#include <algorithm>  // std::swap

#include "Combatant.h"
#include "EffectBase.h"
#include "EffectExecutor.h"
#include "MediatorInterface.h"
// #include "SubjectBase.h"

#ifdef _USE_BOOST_SERIALIZE_
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/base_object.hpp>
#endif



namespace pf2e_manager {
// class Combatant;
// class Mediator;
class SimpleEffect : public EffectBase {
 public:
  SimpleEffect() : EffectBase(this) {}

  SimpleEffect(const SimpleEffect& other);

  SimpleEffect(SimpleEffect&& other) : SimpleEffect(other) {}

  SimpleEffect* copy() { return new SimpleEffect(*this); }

  void execute() override;

  void undo() override;

  void removeEffect() override {
    _is_active = false;
    Combatant* combatant = dynamic_cast<Combatant*>(getReciever());
    if (combatant) {
      auto eff_container = &combatant->getEffects();
      for (auto it : *eff_container)
        if (getSubject() == it->getInvoker()) it->removeEffect();
    }
  }

  void activateEffect() override {
    if (_duration) _is_active = true;
    Combatant* combatant = dynamic_cast<Combatant*>(getReciever());
    if (combatant) {
      auto eff_container = &combatant->getEffects();
      for (auto it : *eff_container)
        if (getSubject() == it->getInvoker()) it->activateEffect();
    }
  }

  void executeAssociated() override {
    if (!_is_associated_provided) {
      _executor->execute(this, getReciever(), _associated_actions);
      _is_associated_provided = true;
    }
  }

  friend class Combatant;
  friend class SimpleEffectBuilder;

#ifdef _USE_BOOST_SERIALIZE_
  friend class boost::serialization::access;
  template <class Archive>
  void serialize(Archive & ar, const size_t version) {
      ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(EffectBase);
      ar & BOOST_SERIALIZATION_NVP(_is_associated_provided);
      ar & BOOST_SERIALIZATION_NVP(_associated_actions);
      ar & BOOST_SERIALIZATION_NVP(_execute_actions);

  }

  friend inline std::ostream &operator<<(std::ostream &os, const SimpleEffect &effect);

#endif
 protected:
  bool _is_associated_provided = false;

  std::vector<std::string> _associated_actions = std::vector<std::string>();
  std::vector<std::string> _execute_actions = std::vector<std::string>();

  EffectExecutor* _executor = nullptr;

  MediatorInterface* _mediator = nullptr;
};

#ifdef _USE_BOOST_SERIALIZE_


inline std::ostream &operator<<(std::ostream &os, const SimpleEffect &effect)
{
    os << ' ' << effect._is_associated_provided;
    for(auto it : effect._associated_actions)
        os << ' ' << it;
    os  << ' ' << effect._type;
    for(auto it : effect._execute_actions)
        os << ' ' << it;
       os << '\n';
    return os;
}
#endif
}  // namespace pf2e_manager
#endif
