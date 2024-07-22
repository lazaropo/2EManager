#ifndef _EFFECT_CLASSES_C61F8EA4_4104_405C_8865_237A7CE5BC26_
#define _EFFECT_CLASSES_C61F8EA4_4104_405C_8865_237A7CE5BC26_

#include <map>
#include <string>

#include "ComplexEffect.h"
#include "SimpleEffect.h"
// #include "SimpleEffectBuilder.h"
// #include "ComplexEffectBuilder.h"
namespace {
using ns_trigger = pf2e_manager::SimpleEffect::Trigger;
using ns_type = pf2e_manager::SimpleEffect::Type;
using ns_value = pf2e_manager::SimpleEffect::Value;
}  // namespace

namespace pf2e_manager {
struct EffectDictionaryValues {
  EffectDictionaryValues(std::string name, int type, SimpleEffect::Value value,
                         SimpleEffect::Trigger trigger,
                         std::string descprition = "",
                         std::list<std::string> command_and_effects_set)
      : _name(name),
        _type(type),
        _value(value),
        _trigger(trigger),
        _descprition(descprition),
        _command_and_effects_set(command_and_effects_set) {}

  std::string _name = "";  // KEY

  int _type;  // bit field
  SimpleEffect::Value _value;
  SimpleEffect::Trigger _trigger;

  std::string _descprition = "";

  std::list<std::string> _command_and_effects_set;
};
extern const std::map<std::string, EffectDictionaryValues>
    c_effects_dictionary = {
        {"effect:clumsy",
         EffectDictionaryValues(
             "effect:clumsy", ns_type::PENALTY | ns_type::STATUS,
             {ns_value, ns_value::_dex = 1, ns_value::_ac = 1,
              ns_value::_refl = 1, ns_value::_skills = 1},
             ns_trigger::END_TURN,
             "Your movements become clumsy and inexact. Clumsy always includes "
             "a "
             "value. You take a status penalty equal to the condition value to "
             "Dexterity-based checks and DCs, including AC, Reflex saves, "
             "ranged "
             "attack rolls, and skill checks using Acrobatics, Stealth, and "
             "Thievery.",
             {})},
        {"effect:concealed",
         {"effect:concealed",
          ns_type::NO_VALUE_TYPE,
          {},
          ns_trigger::NO_TRIGGER,
          "You are difficult for one or more creatures to see due to thick fog "
          "or some other obscuring feature. You can be concealed to some "
          "creatures but not others. While concealed, you can still be "
          "observed, but you're tougher to target. A creature that you're "
          "concealed from must succeed at a DC 5 flat check when targeting you "
          "with an attack, spell, or other effect. If the check fails, you "
          "aren't affected. Area effects aren't subject to this flat check.",
          {}}},
        {"effect:confused",
         {"effect:confused",
          ns_type::PENALTY | ns_type::NO_VALUE_TYPE,
          ns_trigger::NO_TRIGGER,
          "You don't have your wits about you, and you attack wildly. You are "
          "off-guard, you don't treat anyone as your ally (though they might "
          "still treat you as theirs), and you can't Delay, Ready, or use "
          "reactions.\nYou use all your actions to Strike or cast offensive "
          "cantrips, though the GM can have you use other actions to "
          "facilitate "
          "attack, such as draw a weapon, move so target is in reach, and so "
          "forth. Your targets are determined randomly by the GM. If you have "
          "no other viable targets, you target yourself, automatically hitting "
          "but not scoring a critical hit. If it's impossible for you to "
          "attack "
          "or cast spells, you babble incoherently, wasting your "
          "actions.\nEach "
          "time you take damage from an attack or spell, you can attempt a DC "
          "11 flat check to recover from your confusion and end the condition.",
          {{"effect:off-guard"}}}},
        {"effect:controlled",
         {"effect:controlled",
          ns_type::PENALTY | ns_type::NO_VALUE_TYPE,
          ns_trigger::NO_TRIGGER,
          "You have been commanded, magically dominated, or otherwise had your "
          "will subverted. The controller dictates how you act and can make "
          "you "
          "use any of your actions, including attacks, reactions, or even "
          "Delay. The controller usually doesn't have to spend their own "
          "actions when controlling you.",
          {}}},
        {"effect:dazzled",
         {"effect:dazzled",
          ns_type::PENALTY | ns_type::NO_VALUE_TYPE,
          ns_trigger::NO_TRIGGER,
          "Your eyes are overstimulated or your vision is swimming. If vision "
          "is your only precise sense, all creatures and objects are concealed "
          "from you.",
          {}}}};
}  // namespace pf2e_manager

#endif