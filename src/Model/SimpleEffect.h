#ifndef _EFFECT_BASE_H_82A0C4AB_9EEF_4E15_9F9A_6535D003B2D3_
#define _EFFECT_BASE_H_82A0C4AB_9EEF_4E15_9F9A_6535D003B2D3_

#include <algorithm>  // std::swap

#include "Combatant.h"
#include "EffectBase.h"
#include "EffectExecutor.h"
#include "MediatorInterface.h"

#if defined(_BOOST_SERIALIZATION_TXT_) || defined(_BOOST_SERIALIZATION_XML_)

#ifdef _BOOST_SERIALIZATION_TXT_
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#endif

#ifdef _BOOST_SERIALIZATION_XML_
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#endif

#include <boost/archive/tmpdir.hpp>
#include <boost/config.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#endif

namespace pf2e_manager {
// class Combatant;
// class Mediator;
class SimpleEffect : public EffectBase {
#if defined(_BOOST_SERIALIZATION_TXT_) || defined(_BOOST_SERIALIZATION_XML_)
  friend class ::boost::serialization::access;
  template <class Archive>
  void serialize(Archive& ar, const unsigned int version);
#endif
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

  // const Trigger _trigger;

 protected:
  bool _is_associated_provided = false;

  std::vector<std::string> _associated_actions = std::vector<std::string>();
  std::vector<std::string> _execute_actions = std::vector<std::string>();

  EffectExecutor* _executor = nullptr;

  MediatorInterface* _mediator = nullptr;
};
}  // namespace pf2e_manager

#ifdef _BOOST_SERIALIZATION_XML_
BOOST_CLASS_EXPORT_KEY(pf2e_manager::SimpleEffect);
#endif
#endif
