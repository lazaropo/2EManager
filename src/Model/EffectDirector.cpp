#include "EffectDirector.h"

namespace pf2e_manager {
EffectDirector::EffectDirector(SimpleEffectBuilder* builder)
    : _builder(builder) {
  // TODO: fill the constructor by all effect names and funcs pointers pairs
  using namespace std::placeholders;
  _effects_dictionary.insert(
      std::pair("effect:clumsy",
                std::bind(&EffectDirector::buildClumsyEffect, this, _1, _2)));
  _effects_dictionary.insert(std::pair(
      "effect:concealed",
      std::bind(&EffectDirector::buildConcealedEffect, this, _1, _2)));
  _effects_dictionary.insert(
      std::pair("effect:confused",
                std::bind(&EffectDirector::buildConfusedEffect, this, _1, _2)));
  _effects_dictionary.insert(std::pair(
      "effect:cotrolled",
      std::bind(&EffectDirector::buildControlledEffect, this, _1, _2)));
  _effects_dictionary.insert(
      std::pair("effect:dazzled",
                std::bind(&EffectDirector::buildDazzledEffect, this, _1, _2)));
  _effects_dictionary.insert(
      std::pair("effect:deafened",
                std::bind(&EffectDirector::buildDeafenedEffect, this, _1, _2)));
  _effects_dictionary.insert(
      std::pair("effect:doomed",
                std::bind(&EffectDirector::buildDoomedEffect, this, _1, _2)));
  _effects_dictionary.insert(
      std::pair("effect:drained",
                std::bind(&EffectDirector::buildDrainedEffect, this, _1, _2)));
  _effects_dictionary.insert(
      std::pair("effect:dying",
                std::bind(&EffectDirector::buildDyingEffect, this, _1, _2)));
  _effects_dictionary.insert(std::pair(
      "effect:encumbered",
      std::bind(&EffectDirector::buildEncumberedEffect, this, _1, _2)));
  _effects_dictionary.insert(std::pair(
      "effect:enfeebled",
      std::bind(&EffectDirector::buildEnfeebledEffect, this, _1, _2)));
  _effects_dictionary.insert(std::pair(
      "effect:fascinated",
      std::bind(&EffectDirector::buildFascinatedEffect, this, _1, _2)));
  _effects_dictionary.insert(
      std::pair("effect:fatigued",
                std::bind(&EffectDirector::buildFatiguedEffect, this, _1, _2)));
  _effects_dictionary.insert(
      std::pair("effect:fleeing",
                std::bind(&EffectDirector::buildFleeingEffect, this, _1, _2)));
  _effects_dictionary.insert(std::pair(
      "effect:frightened",
      std::bind(&EffectDirector::buildFrightenedEffect, this, _1, _2)));
}

void EffectDirector::buildClumsyEffect(int duration, int value) {
  _builder->reset();
  _builder->setName("effect:clumsy")
      ->setPenaltyType()
      ->setStatusType()
      ->setDexValue(value)
      ->setAcValue(value)
      ->setSkillsValue(value)
      ->setReflValue(value)
      ->setEndTrigger()
      ->setDuration(duration)
      ->setDescription(
          "Your movements become clumsy and inexact. Clumsy always includes "
          "a value. You take a status penalty equal to the condition value "
          "to Dexterity-based checks and DCs, including AC, Reflex saves, "
          "ranged attack rolls, and skill checks using Acrobatics, Stealth, "
          "and Thievery.");
}

void EffectDirector::buildConcealedEffect(int duration,
                                          __attribute__((unused)) int value) {
  _builder->reset();
  _builder->setName("effect:concealed")
      ->setNoType()
      ->setNoTrigger()
      ->setDuration(duration)
      ->setDescription(
          "You are difficult for one or more creatures to see due to thick "
          "fog or some other obscuring feature. You can be concealed to some "
          "creatures but not others. While concealed, you can still be "
          "observed, but you're tougher to target. A creature that you're "
          "concealed from must succeed at a DC 5 flat check when targeting "
          "you with an attack, spell, or other effect. If the check fails, "
          "you aren't affected. Area effects aren't subject to this flat "
          "check.");
}

void EffectDirector::buildConfusedEffect(int duration,
                                         __attribute__((unused)) int value) {
  _builder->reset();
  _builder->setName("effect:confused")
      ->setPenaltyType()
      ->setNoType()
      ->setEndTrigger()
      ->setDuration(duration)
      ->setAssociatedActions({{"effect:off-guard"}})
      ->setDescription(
          "You don't have your wits about you, and you attack wildly. You "
          "are off-guard, you don't treat anyone as your ally (though they "
          "might still treat you as theirs), and you can't Delay, Ready, or "
          "use reactions.\nYou use all your actions to Strike or cast "
          "offensive cantrips, though the GM can have you use other actions "
          "to facilitate attack, such as draw a weapon, move so target is in "
          "reach, and so forth. Your targets are determined randomly by the "
          "GM. If you have no other viable targets, you target yourself, "
          "automatically hitting but not scoring a critical hit. If it's "
          "impossible for you to attack or cast spells, you babble "
          "incoherently, wasting your actions.\nEach time you take damage "
          "from an attack or spell, you can attempt a DC 11 flat check to "
          "recover from your confusion and end the condition.");
}

void EffectDirector::buildControlledEffect(int duration,
                                           __attribute__((unused)) int value) {
  _builder->reset();
  _builder->setName("effect:cotrolled")
      ->setPenaltyType()
      ->setNoType()
      ->setEndTrigger()
      ->setDuration(duration)
      ->setDescription(
          "You have been commanded, magically dominated, or otherwise had "
          "your will subverted. The controller dictates how you act and can "
          "make you use any of your actions, including attacks, reactions, "
          "or even Delay. The controller usually doesn't have to spend their "
          "own actions when controlling you.");
}

void EffectDirector::buildDazzledEffect(int duration,
                                        __attribute__((unused)) int value) {
  _builder->reset();
  _builder->setName("effect:dazzled")
      ->setPenaltyType()
      ->setNoType()
      ->setEndTrigger()
      ->setDuration(duration)
      ->setDescription(
          "Your eyes are overstimulated or your vision is swimming. If "
          "vision is your only precise sense, all creatures and objects are "
          "concealed from you.");
}

void EffectDirector::buildDeafenedEffect(int duration,
                                         __attribute__((unused)) int value) {
  _builder->reset();
  _builder->setName("effect:deafened")
      ->setPenaltyType()
      ->setStatusType()
      ->setValueMagnitude(2)
      ->setInitiativeValue(2)
      ->setEndTrigger()
      ->setDuration(duration)
      ->setDescription(
          "You can't hear. You automatically critically fail Perception "
          "checks that require you to be able to hear. You take a –2 status "
          "penalty to Perception checks for initiative and checks that "
          "involve sound but also rely on other senses. If you perform an "
          "action that has the auditory trait, you must succeed at a DC 5 "
          "flat check or the action is lost; attempt the check after "
          "spending the action but before any effects are applied. You are "
          "immune to auditory effects while deafened.");
}

void EffectDirector::buildDoomedEffect(__attribute__((unused)) int duration,
                                       int value) {
  _builder->reset();
  _builder->setName("effect:doomed")
      ->setPenaltyType()
      ->setNoType()
      ->setValueMagnitude(value)
      ->setNoTrigger()
      ->setDescription(
          "Your soul has been gripped by a powerful force that calls you "
          "closer to death. Doomed always includes a value. The dying value "
          "at which you die is reduced by your doomed value. If your maximum "
          "dying value is reduced to 0, you instantly die. When you die, "
          "you're no longer doomed.\nYour doomed value decreases by 1 each "
          "time you get a full night's rest.");
}

void EffectDirector::buildDrainedEffect(__attribute__((unused)) int duration,
                                        int value) {
  _builder->reset();
  _builder->setName("effect:drained")
      ->setPenaltyType()
      ->setStatusType()
      ->setValueMagnitude(value)
      ->setConValue(value)
      ->setFortValue(value)
      ->setEndTrigger()
      ->setDuration(10 /*rounds per minute*/ * 60 /*minutes*/ * 24 /*hours*/ *
                    value)
      ->setAssociatedActions({{"command:harm\ncommand:decreasemaxhp"}})
      ->setDescription(
          "Your health and vitality have been depleted as you've lost blood, "
          "life force, or some other essence. Drained always includes a "
          "value. You take a status penalty equal to your drained value on "
          "Constitution-based checks, such as Fortitude saves. You also lose "
          "a number of Hit Points equal to your level (minimum 1) times the "
          "drained value, and your maximum Hit Points are reduced by the "
          "same amount. For example, if you become drained 3 and you're a "
          "3rd-level character, you lose 9 Hit Points and reduce your "
          "maximum Hit Points by 9. Losing these Hit Points doesn't count as "
          "taking damage.\nEach time you get a full night's rest, your "
          "drained value decreases by 1. This increases your maximum Hit "
          "Points, but you don't immediately recover the lost Hit Points.");
}

void EffectDirector::buildDyingEffect(__attribute__((unused)) int duration,
                                      int value) {
  _builder->reset();
  _builder->setName("effect:dying")
      ->setPenaltyType()
      ->setNoType()
      ->setValueMagnitude(value)
      ->setStartTrigger()
      ->setAssociatedActions({{"effect:unconscious"}})
      ->setDescription(
          "ou are bleeding out or otherwise at death's door. While you have "
          "this condition, you are unconscious. Dying always includes a "
          "value, and if it ever reaches dying 4, you die. When you're "
          "dying, you must attempt a recovery check at the start of your "
          "turn each round to determine whether you get better or worse. "
          "Your dying condition increases by 1 if you take damage while "
          "dying, or by 2 if you take damage from an enemy's critical hit or "
          "a critical failure on your save.\nIf you lose the dying condition "
          "by succeeding at a recovery check and are still at 0 Hit Points, "
          "you remain unconscious, but you can wake up as described in that "
          "condition. You lose the dying condition automatically and wake up "
          "if you ever have 1 Hit Point or more. Any time you lose the dying "
          "condition, you gain the wounded 1 condition, or increase your "
          "wounded condition value by 1 if you already have that condition.");
}

void EffectDirector::buildEncumberedEffect(int duration,
                                           __attribute__((unused)) int value) {
  _builder->reset();
  _builder->setName("effect:encumbered")
      ->setPenaltyType()
      ->setNoType()
      ->setNoTrigger()
      ->setAssociatedActions({{"effect:clumsy"}})
      ->setDescription(
          "You are carrying more weight than you can manage. While you're "
          "encumbered, you're clumsy 1 and take a 10-foot penalty to all "
          "your Speeds. As with all penalties to your Speed, this can't "
          "reduce your Speed below 5 feet.");
}

void EffectDirector::buildEnfeebledEffect(int duration, int value) {
  _builder->reset();
  _builder->setName("effect:enfeebled")
      ->setPenaltyType()
      ->setStatusType()
      ->setValueMagnitude(value)
      ->setStrValue(value)
      ->setSkillsValue(value)
      ->setEndTrigger()
      ->setDuration(duration)
      ->setDescription(
          "You're physically weakened. Enfeebled always includes a value. "
          "When you are enfeebled, you take a status penalty equal to the "
          "condition value to Strength-based rolls and DCs, including "
          "Strength-based melee attack rolls, Strength-based damage rolls, "
          "and Athletics checks.");
}

void EffectDirector::buildFascinatedEffect(int duration,
                                           __attribute__((unused)) int value) {
  _builder->reset();
  _builder->setName("effect:fascinated")
      ->setPenaltyType()
      ->setStatusType()
      ->setValueMagnitude(2)
      ->setPercValue(2)
      ->setSkillsValue(2)
      ->setEndTrigger()
      ->setDescription(
          "You're compelled to focus your attention on something, "
          "distracting you from whatever else is going on around you. You "
          "take a –2 status penalty to Perception and skill checks, and you "
          "can't use concentrate actions unless they (or their intended "
          "consequences) are related to the subject of your fascination, as "
          "determined by the GM. For instance, you might be able to Seek and "
          "Recall Knowledge about the subject, but you likely couldn't cast "
          "a spell targeting a different creature. This condition ends if a "
          "creature uses hostile actions against you or any of your allies.");
}

void EffectDirector::buildFatiguedEffect(int duration,
                                         __attribute__((unused)) int value) {
  _builder->reset();
  _builder->setName("effect:fatigue")
      ->setPenaltyType()
      ->setStatusType()
      ->setValueMagnitude(1)
      ->setAcValue(1)
      ->setFortValue(1)
      ->setReflValue(1)
      ->setWillValue(1)
      ->setDuration(duration)
      ->setDescription(
          "You're tired and can't summon much energy. You take a –1 status "
          "penalty to AC and saving throws. You can't use exploration "
          "activities performed while traveling, such as those on pages "
          "438–439.\nYou recover from fatigue after a full night's rest.");
}

void EffectDirector::buildFleeingEffect(int duration,
                                        __attribute__((unused)) int value) {
  _builder->reset();
  _builder->setName("effect:fleeing")
      ->setPenaltyType()
      ->setNoType()
      ->setEndTrigger()
      ->setDuration(duration)
      ->setDescription(
          "You're forced to run away due to fear or some other compulsion. "
          "On your turn, you must spend each of your actions trying to "
          "escape the source of the fleeing condition as expediently as "
          "possible (such as by using move actions to flee, or opening doors "
          "barring your escape). The source is usually the effect or "
          "creature that gave you the condition, though some effects might "
          "define something else as the source. You can't Delay or Ready "
          "while fleeing.");
}

void EffectDirector::buildFrightenedEffect(__attribute__((unused)) int duration,
                                           int value) {
  _builder->reset();
  _builder->setName("effect:frightened")
      ->setPenaltyType()
      ->setStatusType()
      ->setValueMagnitude(value)
      ->setEveryValue(value)
      ->setDuration(value)
      ->setEndTrigger()
      ->setDescription(
          "You're gripped by fear and struggle to control your nerves. The "
          "frightened condition always includes a value. You take a status "
          "penalty equal to this value to all your checks and DCs. Unless "
          "specified otherwise, at the end of each of your turns, the value "
          "of your frightened condition decreases by 1.");
}

}  // namespace pf2e_manager
