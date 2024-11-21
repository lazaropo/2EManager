#include "EffectDirector.h"

namespace pf2e_manager {
EffectDirector::EffectDirector(SimpleEffectBuilder* builder)
    : _builder(builder) {
  using namespace std::placeholders;
  using std::bind;
  using std::pair;

  _effects_dictionary.insert(
      std::pair("effect:blinded", std::bind(&EffectDirector::buildBlindedEffect, this, _1, _2)));
  _effects_dictionary.insert(
      std::pair("effect:clumsy", std::bind(&EffectDirector::buildClumsyEffect, this, _1, _2)));
  _effects_dictionary.insert(
      std::pair("effect:concealed", std::bind(&EffectDirector::buildConcealedEffect, this, _1, _2)));
  _effects_dictionary.insert(
      std::pair("effect:confused", std::bind(&EffectDirector::buildConfusedEffect, this, _1, _2)));
  _effects_dictionary.insert(
      std::pair("effect:cotrolled",
                std::bind(&EffectDirector::buildControlledEffect, this, _1, _2)));
  _effects_dictionary.insert(
      std::pair("effect:dazzled", std::bind(&EffectDirector::buildDazzledEffect, this, _1, _2)));
  _effects_dictionary.insert(
      std::pair("effect:deafened", std::bind(&EffectDirector::buildDeafenedEffect, this, _1, _2)));
  _effects_dictionary.insert(
      std::pair("effect:doomed", std::bind(&EffectDirector::buildDoomedEffect, this, _1, _2)));
  _effects_dictionary.insert(
      std::pair("effect:drained", std::bind(&EffectDirector::buildDrainedEffect, this, _1, _2)));
  _effects_dictionary.insert(
      std::pair("effect:dying", std::bind(&EffectDirector::buildDyingEffect, this, _1, _2)));
  _effects_dictionary.insert(
      std::pair("effect:encumbered",
                std::bind(&EffectDirector::buildEncumberedEffect, this, _1, _2)));
  _effects_dictionary.insert(
      std::pair("effect:enfeebled", std::bind(&EffectDirector::buildEnfeebledEffect, this, _1, _2)));
  _effects_dictionary.insert(
      std::pair("effect:fascinated",
                std::bind(&EffectDirector::buildFascinatedEffect, this, _1, _2)));
  _effects_dictionary.insert(
      std::pair("effect:fatigued", std::bind(&EffectDirector::buildFatiguedEffect, this, _1, _2)));
  _effects_dictionary.insert(
      std::pair("effect:fleeing", std::bind(&EffectDirector::buildFleeingEffect, this, _1, _2)));
  _effects_dictionary.insert(
      std::pair("effect:frightened",
                std::bind(&EffectDirector::buildFrightenedEffect, this, _1, _2)));
  _effects_dictionary.insert(
      std::pair("effect:grabbed", std::bind(&EffectDirector::buildGrabbedEffect, this, _1, _2)));
  _effects_dictionary.insert(
      std::pair("effect:hidden", std::bind(&EffectDirector::buildHiddenEffect, this, _1, _2)));
  _effects_dictionary.insert(
      std::pair("effect:immobilized",
                std::bind(&EffectDirector::buildImmobilizedEffect, this, _1, _2)));
  _effects_dictionary.insert(
      std::pair("effect:indifferent",
                std::bind(&EffectDirector::buildIndifferentEffect, this, _1, _2)));
  _effects_dictionary.insert(
      std::pair("effect:invisible", std::bind(&EffectDirector::buildInvisibleEffect, this, _1, _2)));
  _effects_dictionary.insert(
      std::pair("effect:observed", std::bind(&EffectDirector::buildObservedEffect, this, _1, _2)));
  _effects_dictionary.insert(
      std::pair("effect:off-guard", std::bind(&EffectDirector::buildOffGuardEffect, this, _1, _2)));
  _effects_dictionary.insert(
      std::pair("effect:paralyzed", std::bind(&EffectDirector::buildParalyzedEffect, this, _1, _2)));
  _effects_dictionary.insert(
      std::pair("effect:persistentdamage",
                std::bind(&EffectDirector::buildPersistentDamageEffect, this, _1, _2)));
  _effects_dictionary.insert(
      std::pair("effect:petrified", std::bind(&EffectDirector::buildPetrifiedEffect, this, _1, _2)));
  _effects_dictionary.insert(
      std::pair("effect:prone", std::bind(&EffectDirector::buildProneEffect, this, _1, _2)));
  _effects_dictionary.insert(
      std::pair("effect:quickened", std::bind(&EffectDirector::buildQuickenedEffect, this, _1, _2)));
  _effects_dictionary.insert(
      std::pair("effect:restrained",
                std::bind(&EffectDirector::buildRestrainedEffect, this, _1, _2)));
  _effects_dictionary.insert(
      std::pair("effect:sickened", std::bind(&EffectDirector::buildSickenedEffect, this, _1, _2)));
  _effects_dictionary.insert(
      std::pair("effect:slowed", std::bind(&EffectDirector::buildSlowedEffect, this, _1, _2)));
  _effects_dictionary.insert(
      std::pair("effect:stunned", std::bind(&EffectDirector::buildStunnedEffect, this, _1, _2)));
  _effects_dictionary.insert(
      std::pair("effect:stupified", std::bind(&EffectDirector::buildStupefiedEffect, this, _1, _2)));
  _effects_dictionary.insert(
      std::pair("effect:unconscious",
                std::bind(&EffectDirector::buildUnconsciousEffect, this, _1, _2)));
  _effects_dictionary.insert(
      std::pair("effect:undetected",
                std::bind(&EffectDirector::buildUndetectedEffect, this, _1, _2)));
  _effects_dictionary.insert(
      std::pair("effect:unnoticed", std::bind(&EffectDirector::buildUnnoticedEffect, this, _1, _2)));
  _effects_dictionary.insert(
      std::pair("effect:wounded", std::bind(&EffectDirector::buildWoundedEffect, this, _1, _2)));

  _effects_dictionary.insert(
      std::pair("effect:malevolence",
                std::bind(&EffectDirector::buildMalevolenceEffect, this, _1, _2)));
}

void EffectDirector::buildEffectByName(const std::string& name, int duration,
                                       int value) {
  // try{
  if (_effects_dictionary.find(name) != _effects_dictionary.end())
    (_effects_dictionary[name])(duration, value);
  else
    return;
  // }
  // catch (const std::bad_any_cast& ex){
  //   throw std:: << "Bad Any Cast: EffectDirector"
  // }
}

void EffectDirector::buildBlindedEffect(int duration,


#if defined (__clang__)  || defined (__GNUC__) || defined (__GNUG__)
                                        __attribute__((unused))
#endif
                                        int value)
{
    _builder->reset();
    _builder->setName("effect:blinded")
        ->setPenaltyType()
        ->setStatusType()
        ->setValueMagnitude(4)
        ->setPercValue(value)
        ->setEndTrigger()
        ->setDuration(duration)
        ->setDescription("You can't see. All normal terrain is difficult terrain to you. You "
                         "can't detect anything using vision. You automatically critically "
                         "fail Perception checks that require you to be able to see, and if "
                         "vision is your only precise sense, you take a –4 status penalty to "
                         "Perception checks. You are immune to visual effects. Blinded "
                         "overrides dazzled.");
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


#if defined (__clang__)  || defined (__GNUC__) || defined (__GNUG__)
                                          __attribute__((unused))
#endif
                                          int value)
{
    _builder->reset();
    _builder->setName("effect:concealed")
        ->setNoType()
        ->setNoTrigger()
        ->setDuration(duration)
        ->setDescription("You are difficult for one or more creatures to see due to thick "
                         "fog or some other obscuring feature. You can be concealed to some "
                         "creatures but not others. While concealed, you can still be "
                         "observed, but you're tougher to target. A creature that you're "
                         "concealed from must succeed at a DC 5 flat check when targeting "
                         "you with an attack, spell, or other effect. If the check fails, "
                         "you aren't affected. Area effects aren't subject to this flat "
                         "check.");
}

void EffectDirector::buildConfusedEffect(int duration,

#if defined (__clang__)  || defined (__GNUC__) || defined (__GNUG__)
                                         __attribute__((unused))
#endif
                                         int value)
{
    _builder->reset();
    _builder->setName("effect:confused")
        ->setPenaltyType()
        ->setNoType()
        ->setEndTrigger()
        ->setDuration(duration)
        ->setAssociatedActions({{"effect:off-guard"}})
        ->setDescription("You don't have your wits about you, and you attack wildly. You "
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

#if defined (__clang__)  || defined (__GNUC__) || defined (__GNUG__)
                                           __attribute__((unused))
#endif
                                           int value)
{
    _builder->reset();
    _builder->setName("effect:cotrolled")
        ->setPenaltyType()
        ->setNoType()
        ->setEndTrigger()
        ->setDuration(duration)
        ->setDescription("You have been commanded, magically dominated, or otherwise had "
                         "your will subverted. The controller dictates how you act and can "
                         "make you use any of your actions, including attacks, reactions, "
                         "or even Delay. The controller usually doesn't have to spend their "
                         "own actions when controlling you.");
}

void EffectDirector::buildDazzledEffect(int duration,

#if defined (__clang__)  || defined (__GNUC__) || defined (__GNUG__)
                                        __attribute__((unused))
#endif
                                        int value)
{
    _builder->reset();
    _builder->setName("effect:dazzled")
        ->setPenaltyType()
        ->setNoType()
        ->setEndTrigger()
        ->setDuration(duration)
        ->setDescription("Your eyes are overstimulated or your vision is swimming. If "
                         "vision is your only precise sense, all creatures and objects are "
                         "concealed from you.");
}

void EffectDirector::buildDeafenedEffect(int duration,

#if defined (__clang__)  || defined (__GNUC__) || defined (__GNUG__)
                                         __attribute__((unused))
#endif
                                         int value)
{
    _builder->reset();
    _builder->setName("effect:deafened")
        ->setPenaltyType()
        ->setStatusType()
        ->setValueMagnitude(2)
        ->setInitiativeValue(2)
        ->setEndTrigger()
        ->setDuration(duration)
        ->setDescription("You can't hear. You automatically critically fail Perception "
                         "checks that require you to be able to hear. You take a –2 status "
                         "penalty to Perception checks for initiative and checks that "
                         "involve sound but also rely on other senses. If you perform an "
                         "action that has the auditory trait, you must succeed at a DC 5 "
                         "flat check or the action is lost; attempt the check after "
                         "spending the action but before any effects are applied. You are "
                         "immune to auditory effects while deafened.");
}

void EffectDirector::buildDoomedEffect(

#if defined (__clang__)  || defined (__GNUC__) || defined (__GNUG__)
    __attribute__((unused))
#endif
    int duration,
    int value)
{
    _builder->reset();
    _builder->setName("effect:doomed")
        ->setPenaltyType()
        ->setNoType()
        ->setValueMagnitude(value)
        ->setNoTrigger()
        ->setDescription("Your soul has been gripped by a powerful force that calls you "
                         "closer to death. Doomed always includes a value. The dying value "
                         "at which you die is reduced by your doomed value. If your maximum "
                         "dying value is reduced to 0, you instantly die. When you die, "
                         "you're no longer doomed.\nYour doomed value decreases by 1 each "
                         "time you get a full night's rest.");
}

void EffectDirector::buildDrainedEffect(

#if defined (__clang__)  || defined (__GNUC__) || defined (__GNUG__)
    __attribute__((unused))
#endif
    int duration,
    int value)
{
    _builder->reset();
    _builder->setName("effect:drained")
        ->setPenaltyType()
        ->setStatusType()
        ->setValueMagnitude(value)
        ->setConValue(value)
        ->setFortValue(value)
        ->setEndTrigger()
        ->setDuration(10 /*rounds per minute*/ * 60 /*minutes*/ * 24 /*hours*/ * value)
        ->setAssociatedActions({{"command:harm\ncommand:decreasemaxhp"}})
        ->setDescription("Your health and vitality have been depleted as you've lost blood, "
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

void EffectDirector::buildDyingEffect(

#if defined (__clang__)  || defined (__GNUC__) || defined (__GNUG__)
    __attribute__((unused))
#endif
    int duration,
    int value)
{
    _builder->reset();
    _builder->setName("effect:dying")
        ->setPenaltyType()
        ->setNoType()
        ->setValueMagnitude(value ? value : 1)
        ->setStartTrigger()
        ->setDuration(420000 /*just big number*/)
        ->setAssociatedActions({{"effect:unconscious"}})
        ->setExecuteActions({{"effect:dying"}})
        ->setDescription("You are bleeding out or otherwise at death's door. While you have "
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

void EffectDirector::buildEncumberedEffect(

#if defined (__clang__)  || defined (__GNUC__) || defined (__GNUG__)
    __attribute__((unused))
#endif
    int duration,


#if defined (__clang__)  || defined (__GNUC__) || defined (__GNUG__)
    __attribute__((unused))
#endif
    int value)
{
    _builder->reset();
    _builder->setName("effect:encumbered")
        ->setPenaltyType()
        ->setNoType()
        ->setNoTrigger()
        ->setAssociatedActions({{"effect:clumsy"}})
        ->setDescription("You are carrying more weight than you can manage. While you're "
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


#if defined (__clang__)  || defined (__GNUC__) || defined (__GNUG__)
                                           __attribute__((unused))
#endif
                                           int value)
{
    _builder->reset();
    _builder->setName("effect:fascinated")
        ->setPenaltyType()
        ->setStatusType()
        ->setValueMagnitude(2)
        ->setPercValue(2)
        ->setSkillsValue(2)
        ->setEndTrigger()
        ->setDuration(duration)
        ->setDescription("You're compelled to focus your attention on something, "
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


#if defined (__clang__)  || defined (__GNUC__) || defined (__GNUG__)
                                         __attribute__((unused))
#endif
                                         int value)
{
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
        ->setDescription("You're tired and can't summon much energy. You take a –1 status "
                         "penalty to AC and saving throws. You can't use exploration "
                         "activities performed while traveling, such as those on pages "
                         "438–439.\nYou recover from fatigue after a full night's rest.");
}

void EffectDirector::buildFleeingEffect(int duration,

#if defined (__clang__)  || defined (__GNUC__) || defined (__GNUG__)
                                        __attribute__((unused))
#endif
                                        int value)
{
    _builder->reset();
    _builder->setName("effect:fleeing")
        ->setPenaltyType()
        ->setNoType()
        ->setEndTrigger()
        ->setDuration(duration)
        ->setDescription("You're forced to run away due to fear or some other compulsion. "
                         "On your turn, you must spend each of your actions trying to "
                         "escape the source of the fleeing condition as expediently as "
                         "possible (such as by using move actions to flee, or opening doors "
                         "barring your escape). The source is usually the effect or "
                         "creature that gave you the condition, though some effects might "
                         "define something else as the source. You can't Delay or Ready "
                         "while fleeing.");
}

void EffectDirector::buildFrightenedEffect(

#if defined (__clang__)  || defined (__GNUC__) || defined (__GNUG__)
    __attribute__((unused))
#endif
    int duration,
    int value)
{
    _builder->reset();
    _builder->setName("effect:frightened")
        ->setPenaltyType()
        ->setStatusType()
        ->setValueMagnitude(value)
        ->setEveryValue(value)
        ->setDuration(value)
        ->setEndTrigger()
        ->setDescription("You're gripped by fear and struggle to control your nerves. The "
                         "frightened condition always includes a value. You take a status "
                         "penalty equal to this value to all your checks and DCs. Unless "
                         "specified otherwise, at the end of each of your turns, the value "
                         "of your frightened condition decreases by 1.");
}

void EffectDirector::buildGrabbedEffect(int duration,

#if defined (__clang__)  || defined (__GNUC__) || defined (__GNUG__)
                                        __attribute__((unused))
#endif
                                        int value)
{
    _builder->reset();
    _builder->setName("effect:grabbed")
        ->setPenaltyType()
        ->setNoType()
        ->setNoTrigger()
        ->setDuration(duration /*just big number*/)
        ->setAssociatedActions({{"effect:off-guard"}, {"effect:immobilized"}})
        ->setDescription("You're held in place by another creature, giving you the off-guard "
                         "and immobilized conditions. If you attempt a manipulate action "
                         "while grabbed, you must succeed at a DC 5 flat check or it is lost; "
                         "roll the check after spending the action, but before any effects "
                         "are applied.");
}
// TODO: implement this func and further

void EffectDirector::buildHiddenEffect(int duration,

#if defined (__clang__)  || defined (__GNUC__) || defined (__GNUG__)
                                       __attribute__((unused))
#endif
                                       int value)
{
    _builder->reset();
    _builder->setName("effect:fatigue")
        ->setBonusType()
        ->setNoType()
        ->setDuration(duration)
        ->setDescription("While you're hidden from a creature, that creature knows the space "
                         "you're in but can't tell precisely where you are. You typically "
                         "become hidden by using Stealth to Hide. When Seeking a creature "
                         "using only imprecise senses, it remains hidden, rather than "
                         "observed. A creature you're hidden from is off-guard to you, and it "
                         "must succeed at a DC 11 flat check when targeting you with an "
                         "attack, spell, or other effect or it fails to affect you. Area "
                         "effects aren't subject to this flat check. A creature might be able "
                         "to use the Seek action to try to observe you.");
}
void EffectDirector::buildImmobilizedEffect(int duration,

#if defined (__clang__)  || defined (__GNUC__) || defined (__GNUG__)
                                            __attribute__((unused))
#endif
                                            int value)
{
    _builder->reset();
    _builder->setName("effect:immobilized")
        ->setPenaltyType()
        ->setNoType()
        ->setDuration(duration)
        ->setDescription("You are incapable of movement. You can't use any actions that have "
                         "the move trait. If you're immobilized by something holding you in "
                         "place and an external force would move you out of your space, the "
                         "force must succeed at a check against either the DC of the effect "
                         "holding you in place or the relevant defense (usually Fortitude DC) "
                         "of the monster holding you in place.");
}
void EffectDirector::buildIndifferentEffect(int duration,

#if defined (__clang__)  || defined (__GNUC__) || defined (__GNUG__)
                                            __attribute__((unused))
#endif
                                            int value)
{
    _builder->reset();
    _builder->setName("effect:indifferent")
        ->setNoType()
        ->setDuration(duration)
        ->setDescription("This condition reflects a creature's disposition toward a "
                         "particular character, and only supernatural effects (like a spell) "
                         "can impose this condition on a PC. A creature that is indifferent "
                         "to a character doesn't really care one way or the other about that "
                         "character. Assume a creature's attitude to a given character is "
                         "indifferent unless specified otherwise.");
}
void EffectDirector::buildInvisibleEffect(int duration,

#if defined (__clang__)  || defined (__GNUC__) || defined (__GNUG__)
                                          __attribute__((unused))
#endif
                                          int value)
{
    _builder->reset();
    _builder->setName("effect:invisible")
        ->setBonusType()
        ->setDuration(duration)
        ->setDescription("You can't be seen. You're undetected to everyone. Creatures can "
                         "Seek to detect you; if a creature succeeds at its Perception check "
                         "against your Stealth DC, you become hidden to that creature until "
                         "you Sneak to become undetected again. If you become invisible while "
                         "someone can already see you, you start out hidden to them (instead "
                         "of undetected) until you successfully Sneak. You can't become "
                         "observed while invisible except via special abilities or magic.");
}
void EffectDirector::buildObservedEffect(int duration,


#if defined (__clang__)  || defined (__GNUC__) || defined (__GNUG__)
                                         __attribute__((unused))
#endif
                                         int value)
{
    _builder->reset();
    _builder->setName("effect:observed")
        ->setNoType()
        ->setDuration(duration)
        ->setDescription("Anything in plain view is observed by you. If a creature takes "
                         "measures to avoid detection, such as by using Stealth to Hide, it "
                         "can become hidden or undetected instead of observed. If you have "
                         "another precise sense besides sight, you might be able to observe a "
                         "creature or object using that sense instead. You can observe a "
                         "creature with only your precise senses. When Seeking a creature "
                         "using only imprecise senses, it remains hidden, rather than "
                         "observed.");
}
void EffectDirector::buildOffGuardEffect(int duration,


#if defined (__clang__)  || defined (__GNUC__) || defined (__GNUG__)
                                         __attribute__((unused))
#endif
                                         int value)
{
    _builder->reset();
    _builder->setName("effect:off-guard")
        ->setPenaltyType()
        ->setCircumstanceType()
        ->setValueMagnitude(2)
        ->setAcValue(2)
        ->setDuration(duration)
        ->setEndTrigger()
        ->setDescription("You're distracted or otherwise unable to focus your full attention "
                         "on defense. You take a –2 circumstance penalty to AC. Some effects "
                         "give you the off-guard condition only to certain creatures or "
                         "against certain attacks. Others—especially conditions—can make you "
                         "off-guard against everything. If a rule doesn't specify that the "
                         "condition applies only to certain circumstances, it applies to all "
                         "of them, such as “The target is off-guard.”");
}
void EffectDirector::buildParalyzedEffect(int duration,

#if defined (__clang__)  || defined (__GNUC__) || defined (__GNUG__)
                                          __attribute__((unused))
#endif
                                          int value)
{
    _builder->reset();
    _builder->setName("effect:paralyzed")
        ->setPenaltyType()
        ->setNoType()
        ->setDuration(duration)
        ->setEndTrigger()
        ->setAssociatedActions({{"effect:off-guard"}})
        ->setDescription("You're frozen in place. You have the off-guard condition and can't "
                         "act except to Recall Knowledge and use actions that require only "
                         "your mind (as determined by the GM). Your senses still function, "
                         "but only in the areas you can perceive without moving, so you can't "
                         "Seek.");
}
void EffectDirector::buildPersistentDamageEffect(int duration, int value) {
  _builder->reset();
  if (value)
    _builder->setValueMagnitude(value)->setConstantValue();
  else
    _builder->setNoConstantValue();

  _builder->setName("effect:persistentdamage")
      ->setPenaltyType()
      ->setNoType()
      ->setDuration(duration)
      ->setEndTrigger()
      ->setExecuteActions({{"command:harm"}})
      ->setDescription(
          "You are taking damage from an ongoing effect, such as from being "
          "lit on fire. This appears as “X persistent [type] damage,” where "
          "“X” is the amount of damage dealt and “[type]” is the damage type. "
          "Like normal damage, it can be doubled or halved based on the "
          "results of an attack roll or saving throw. Instead of taking "
          "persistent damage immediately, you take it at the end of each of "
          "your turns as long as you have the condition, rolling any damage "
          "dice anew each time. After you take persistent damage, roll a DC 15 "
          "flat check to see if you recover from the persistent damage. If you "
          "succeed, the condition ends.");
}
void EffectDirector::buildPetrifiedEffect(int duration,

#if defined (__clang__)  || defined (__GNUC__) || defined (__GNUG__)
                                          __attribute__((unused))
#endif
                                          int value)
{
    _builder->reset();
    _builder->setName("effect:petrified")
        ->setPenaltyType()
        ->setNoType()
        ->setDuration(duration)
        ->setEndTrigger()
        ->setDescription("You have been turned to stone. You can't act, nor can you sense "
                         "anything. You become an object with a Bulk double your normal Bulk "
                         "(typically 12 for a petrified Medium creature or 6 for a petrified "
                         "Small creature), AC 9, Hardness 8, and the same current Hit Points "
                         "you had when alive. You don't have a Broken Threshold. When the "
                         "petrified condition ends, you have the same number of Hit Points "
                         "you had as a statue. If the statue is destroyed, you immediately "
                         "die. While petrified, your mind and body are in stasis, so you "
                         "don't age or notice the passing of time.");
}
void EffectDirector::buildProneEffect(int duration,

#if defined (__clang__)  || defined (__GNUC__) || defined (__GNUG__)
                                      __attribute__((unused))
#endif
                                      int value)
{
    _builder->reset();
    _builder->setName("effect:prone")
        ->setPenaltyType()
        ->setCircumstanceType()
        ->setValueMagnitude(2)
        ->setAtkValue(2)
        ->setDuration(duration)
        ->setEndTrigger()
        ->setDescription("You're lying on the ground. You are off-guard and take a –2 "
                         "circumstance penalty to attack rolls. The only move actions you can "
                         "use while you're prone are Crawl and Stand. Standing up ends the "
                         "prone condition. You can Take Cover while prone to hunker down and "
                         "gain greater cover against ranged attacks, even if you don't have "
                         "an object to get behind, which grants you a +4 circumstance bonus "
                         "to AC against ranged attacks (but you remain off-guard). If you "
                         "would be knocked prone while you're Climbing or Flying, you fall. "
                         "You can't be knocked prone when Swimming.");
}
void EffectDirector::buildQuickenedEffect(int duration,

#if defined (__clang__)  || defined (__GNUC__) || defined (__GNUG__)
                                          __attribute__((unused))
#endif
                                          int value)
{
    _builder->reset();
    _builder->setName("effect:quickened")
        ->setBonusType()
        ->setDuration(duration)
        ->setStartTrigger()
        ->setDescription("You're able to act more quickly. You gain 1 additional action at "
                         "the start of your turn each round. Many effects that make you "
                         "quickened require you use this extra action only in certain ways. "
                         "If you become quickened from multiple sources, you can use the "
                         "extra action you've been granted for any single action allowed by "
                         "any of the effects that made you quickened. Because quickened has "
                         "its effect at the start of your turn, you don't immediately gain "
                         "actions if you become quickened during your turn.");
}
void EffectDirector::buildRestrainedEffect(int duration,

#if defined (__clang__)  || defined (__GNUC__) || defined (__GNUG__)
                                           __attribute__((unused))
#endif
                                           int value)
{
    _builder->reset();
    _builder->setName("effect:restrained")
        ->setPenaltyType()
        ->setNoType()
        ->setDuration(duration)
        ->setEndTrigger()
        ->setAssociatedActions({{"effect:off-guard"}, {"effect:immobilized"}})
        ->setDescription("You're tied up and can barely move, or a creature has you pinned. "
                         "You have the off-guard and immobilized conditions, and you can't "
                         "use any attack or manipulate actions except to attempt to Escape or "
                         "Force Open your bonds. Restrained overrides grabbed.");
}

void EffectDirector::buildSickenedEffect(int duration, int value) {
  _builder->reset();
  _builder->setName("effect:sickned")
      ->setPenaltyType()
      ->setStatusType()
      ->setValueMagnitude(value)
      ->setEveryValue(value)
      ->setDuration(duration)
      ->setEndTrigger()
      ->setDescription(
          "You feel ill. Sickened always includes a value. You take a status "
          "penalty equal to this value on all your checks and DCs. You can't "
          "willingly ingest anything—including elixirs and potions—while "
          "sickened.You can spend a single action retching in an attempt to "
          "recover, which lets you immediately attempt a Fortitude save "
          "against the DC of the effect that made you sickened. On a success, "
          "you reduce your sickened value by 1 (or by 2 on a critical "
          "success).");
  ;
}
void EffectDirector::buildSlowedEffect(int duration, int value) {
  _builder->reset();
  _builder->setName("effect:slowed")
      ->setPenaltyType()
      ->setNoType()
      ->setValueMagnitude(value)
      ->setDuration(duration)
      ->setStartTrigger()
      ->setDescription(
          "You have fewer actions. Slowed always includes a value. When you "
          "regain your actions, reduce the number of actions regained by your "
          "slowed value. Because you regain actions at the start of your turn, "
          "you don't immediately lose actions if you become slowed during your "
          "turn.");
}
void EffectDirector::buildStunnedEffect(int duration, int value) {
  _builder->reset();
  _builder->setName("effect:stunnded")
      ->setPenaltyType()
      ->setNoType()
      ->setValueMagnitude(value)
      ->setDuration(duration)
      ->setStartTrigger()
      ->setDescription(
          "You've become senseless. You can't act. Stunned usually includes a "
          "value, which indicates how many total actions you lose, possibly "
          "over multiple turns, from being stunned. Each time you regain "
          "actions, reduce the number you regain by your stunned value, then "
          "reduce your stunned value by the number of actions you lost. For "
          "example, if you were stunned 4, you would lose all 3 of your "
          "actions on your turn, reducing you to stunned 1; on your next turn, "
          "you would lose 1 more action, and then be able to use your "
          "remaining 2 actions normally. Stunned might also have a duration "
          "instead, such as “stunned for 1 minute,” causing you to lose all "
          "your actions for the duration.\nStunned overrides slowed. If the "
          "duration of your stunned condition ends while you are slowed, you "
          "count the actions lost to the stunned condition toward those lost "
          "to being slowed. So, if you were stunned 1 and slowed 2 at the "
          "beginning of your turn, you would lose 1 action from stunned, and "
          "then lose only 1 additional action by being slowed, so you would "
          "still have 1 action remaining to use that turn.");
}
void EffectDirector::buildStupefiedEffect(int duration, int value) {
  _builder->reset();
  _builder->setName("effect:stupefied")
      ->setPenaltyType()
      ->setNoType()
      ->setValueMagnitude(value)
      ->setDuration(duration)
      ->setEndTrigger()
      ->setDescription(
          "Your thoughts and instincts are clouded. Stupefied always includes "
          "a value. You take a status penalty equal to this value on "
          "Intelligence-, Wisdom-, and Charisma-based checks and DCs, "
          "including Will saving throws, spell attack modifiers, spell DCs, "
          "and skill checks that use these attribute modifiers. Any time you "
          "attempt to Cast a Spell while stupefied, the spell is disrupted "
          "unless you succeed at a flat check with a DC equal to 5 + your "
          "stupefied value.");
}

void EffectDirector::buildUnconsciousEffect(int duration,

#if defined (__clang__)  || defined (__GNUC__) || defined (__GNUG__)
                                            __attribute__((unused))
#endif
                                            int value)
{
    _builder->reset();
    _builder->setName("effect:unconscious")
        ->setPenaltyType()
        ->setStatusType()
        ->setValueMagnitude(4)
        ->setAcValue(4)
        ->setPercValue(4)
        ->setReflValue(4)
        ->setDuration(duration)
        ->setStartTrigger()
        ->setAssociatedActions({{"effect:blinded"}, {"effect:off-guard"}})
        ->setDescription("You're sleeping or have been knocked out. You can't act. You take a "
                         "–4 status penalty to AC, Perception, and Reflex saves, and you have "
                         "the blinded and off-guard conditions. When you gain this condition, "
                         "you fall prone and drop items you're holding unless the effect "
                         "states otherwise or the GM determines you're positioned so you "
                         "wouldn't.\nIf you're unconscious because you're dying, you can't "
                         "wake up while you have 0 Hit Points. If you are restored to 1 Hit "
                         "Point or more, you lose the dying and unconscious conditions and "
                         "can act normally on your next turn.\nIf you are unconscious and at "
                         "0 Hit Points, but not dying, you return to 1 Hit Point and awaken "
                         "after sufficient time passes. The GM determines how long you remain "
                         "unconscious, from a minimum of 10 minutes to several hours. If you "
                         "are healed, you lose the unconscious condition and can act normally "
                         "on your next turn.\nIf you're unconscious and have more than 1 Hit "
                         "Point (typically because you are asleep or unconscious due to an "
                         "effect), you wake up in one of the following ways.\nYou take "
                         "damage, though if the damage reduces you to 0 Hit Points, you "
                         "remain unconscious and gain the dying condition as normal.\nYou "
                         "receive healing, other than the natural healing you get from "
                         "resting.\nSomeone shakes you awake with an Interact action.\nLoud "
                         "noise around you might wake you. At the start of your turn, you "
                         "automatically attempt a Perception check against the noise's DC (or "
                         "the lowest DC if there is more than one noise), waking up if you "
                         "succeed. If creatures are attempting to stay quiet around you, this "
                         "Perception check uses their Stealth DCs. Some effects make you "
                         "sleep so deeply that they don't allow you this Perception "
                         "check.\nIf you are simply asleep, the GM decides you wake up either "
                         "because you have had a restful night's sleep or something disrupted "
                         "that rest.");
}
void EffectDirector::buildUndetectedEffect(int duration,

#if defined (__clang__)  || defined (__GNUC__) || defined (__GNUG__)
                                           __attribute__((unused))
#endif
                                           int value)
{
    _builder->reset();
    _builder->setName("effect:undetected")
        ->setBonusType()
        ->setNoType()
        ->setDuration(duration)
        ->setEndTrigger()
        ->setDescription("When you are undetected by a creature, that creature can't see you "
                         "at all, has no idea what space you occupy, and can't target you, "
                         "though you still can be affected by abilities that target an area. "
                         "When you're undetected by a creature, that creature is off-guard to "
                         "you.\nA creature you're undetected by can guess which square you're "
                         "in to try targeting you. It must pick a square and attempt an "
                         "attack. This works like targeting a hidden creature (requiring a DC "
                         "11 flat check, as described under Detecting Creatures), but the "
                         "flat check and attack roll are rolled in secret by the GM, who "
                         "doesn't reveal whether the attack missed due to failing the flat "
                         "check, failing the attack roll, or choosing the wrong square. They "
                         "can Seek to try to find you.");
}
void EffectDirector::buildUnnoticedEffect(int duration,

#if defined (__clang__)  || defined (__GNUC__) || defined (__GNUG__)
                                          __attribute__((unused))
#endif
                                          int value)
{
    _builder->reset();
    _builder->setName("effect:unnoticed")
        ->setBonusType()
        ->setNoType()
        ->setDuration(duration)
        ->setEndTrigger()
        ->setAssociatedActions({"effect:undetected"})
        ->setDescription("If you're unnoticed by a creature, that creature has no idea you're "
                         "present. When you're unnoticed, you're also undetected. This "
                         "matters for abilities that can be used only against targets totally "
                         "unaware of your presence.");
}
void EffectDirector::buildWoundedEffect(int duration, int value) {
  _builder->reset();
  _builder->setName("effect:wounded")
      ->setPenaltyType()
      ->setNoType()
      ->setValueMagnitude(value)
      ->setDuration(duration)
      ->setEndTrigger()
      ->setDescription(
          "You have been seriously injured. If you lose the dying condition "
          "and do not already have the wounded condition, you become wounded "
          "1. If you already have the wounded condition when you lose the "
          "dying condition, your wounded condition value increases by 1. If "
          "you gain the dying condition while wounded, increase your dying "
          "condition value by your wounded value.\nThe wounded condition ends "
          "if someone successfully restores Hit Points to you using Treat "
          "Wounds, or if you are restored to full Hit Points by any means and "
          "rest for 10 minutes. ");
}

void EffectDirector::buildMalevolenceEffect(int duration, int value) {
  _builder->reset();
  _builder->setName("effect:malevolence")
      ->setPenaltyType()
      ->setStatusType()
      ->setValueMagnitude(value)
      ->setDuration(duration)
      ->setEndTrigger()
      ->setDescription("As the malevolence begins to take its hold on creatures, their "
                       "body, minds, and souls become increasingly haunted by the "
                       "supernatural force infesting Xarwin Manor. Malevolence is a special "
                       "condition that can affect PCs who play in this adventure. The "
                       "malevolence condition always includes a value. You take a status "
                       "penalty equal to this value to all saving throws against effects "
                       "generated by haunts and against all curse and possession effects. "
                       "The malevolence condition can be reduced by restoration.\nThe "
                       "malevolence can never increase above a value of 4. If an effect "
                       "would increase a creature's malevolence value higher than 4, the "
                       "creature is instead stupefied 1 for 24 hours as the malevolence "
                       "consumes a few of their random, short-term memories. A creature "
                       "that has a malevolence 4 won't voluntarily leave the Xarwin Manor "
                       "grounds.\nEach time you get a full night's rest in a region not "
                       "influenced by the malevolence condition, the value of your "
                       "malevolence decreases by 1.");
}

}  // namespace pf2e_manager
