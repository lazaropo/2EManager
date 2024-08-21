#ifndef _EFFECT_DIRECTOR_C61F8EA4_4104_405C_8865_237A7CE5BC26_
#define _EFFECT_DIRECTOR_C61F8EA4_4104_405C_8865_237A7CE5BC26_

#include <functional>
#include <map>
#include <string>

// #include "ComplexEffect.h"
// #include "ComplexEffectBuilder.h"

// #include "SimpleEffect.h"
#include "SimpleEffectBuilder.h"
namespace {
using ns_trigger = pf2e_manager::SimpleEffect::Trigger;
using ns_type = pf2e_manager::SimpleEffect::Type;
using ns_value = pf2e_manager::SimpleEffect::Value;
}  // namespace

namespace pf2e_manager {
class EffectDirector {
 public:
  EffectDirector(SimpleEffectBuilder* builder);

  void buildEffectByName(const std::string& name, int duration, int value);

  void buildBlindedEffect(int duration, __attribute__((unused)) int value = 0);

  void buildClumsyEffect(int duration, int value);

  void buildConcealedEffect(int duration,
                            __attribute__((unused)) int value = 0);

  void buildConfusedEffect(int duration, __attribute__((unused)) int value = 0);

  void buildControlledEffect(int duration,
                             __attribute__((unused)) int value = 0);

  void buildDazzledEffect(int duration, __attribute__((unused)) int value = 0);

  void buildDeafenedEffect(int duration, __attribute__((unused)) int value = 0);

  void buildDoomedEffect(__attribute__((unused)) int duration, int value);

  void buildDrainedEffect(__attribute__((unused)) int duration, int value);

  void buildDyingEffect(__attribute__((unused)) int duration, int value);

  void buildEncumberedEffect(int duration,
                             __attribute__((unused)) int value = 0);

  void buildEnfeebledEffect(int duration, int value);

  void buildFascinatedEffect(int duration,
                             __attribute__((unused)) int value = 0);

  void buildFatiguedEffect(int duration, __attribute__((unused)) int value = 0);

  void buildFleeingEffect(int duration, __attribute__((unused)) int value = 0);

  void buildFrightenedEffect(__attribute__((unused)) int duration, int value);

  void buildGrabbedEffect(int duration, __attribute__((unused)) int value = 0);
  // TODO: implement this func and further

  void buildHiddenEffect(int duration, int value);
  void buildImmobilizedEffect(int duration, int value);
  void buildIndifferentEffect(int duration, int value);
  void buildInvisibleEffect(int duration, int value);
  void buildObservedEffect(int duration, int value);
  void buildOffGuardEffect(int duration, int value);
  void buildParalyzedEffect(int duration, int value);
  void buildPersistentDamageEffect(int duration, int value);
  void buildPetrifiedEffect(int duration, int value);
  void buildProneEffect(int duration, int value);
  void buildQuickenedEffect(int duration, int value);
  void buildRestrainedEffect(int duration, int value);

  void buildSickenedEffect(int duration, int value);
  void buildSlowedEffect(int duration, int value);
  void buildStunnedEffect(int duration, int value);
  void buildStupefiedEffect(int duration, int value);
  void buildUnconsciousEffect(int duration, int value);
  void buildUndetectedEffect(int duration, int value);
  void buildUnnoticedEffect(int duration, int value);
  void buildWoundedEffect(int duration, int value);

  void buildMalevolenceEffect(int duration, int value);

 private:
  SimpleEffectBuilder* _builder;
  // std::any is purposed only to void(int, int)
  std::map<const std::string, std::function<void(int, int)>>
      _effects_dictionary;
};
}  // namespace pf2e_manager

#endif
