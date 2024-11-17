#include "EffectBase.h"

namespace pf2e_manager {
std::string EffectBase::formattingTrigger(EffectBase::Trigger trigger)
{
    std::string ret;

    if (trigger == Trigger::NO_TRIGGER)
        ret = "No trigger.";
    else if (trigger == Trigger::START_TURN)
        ret = "Start turn.";
    else if (trigger == Trigger::END_TURN)
        ret = "End of turn.";

    return ret;
}

EffectBase::Trigger EffectBase::formattingTrigger(const std::string &string)
{
    Trigger ret;
    if (string == "No trigge:" || string == "No trigge" || string == "no trigge:"
        || string == "no trigge")
        ret = Trigger::NO_TRIGGER;
    else if (string == "Start turn:" || string == "Start turn" || string == "start turn:"
             || string == "start turn")
        ret = Trigger::START_TURN;
    else if (string == "End of turn:" || string == "End of turn" || string == "end of turn:"
             || string == "end of turn")
        ret = Trigger::END_TURN;
    else
        throw std::invalid_argument("Incorrect string for EffectBase::Trigger initialize.");

    return ret;
}

std::string EffectBase::formattingType(Type type)
{
    std::string ret;

    if (type == Type::NO_VALUE_TYPE)
        ret = "No value type.";
    else if (type == Type::COMMON_TYPE)
        ret = "Common type.";
    else if (type == Type::STATUS)
        ret = "Status typr.";
    else if (type == Type::CIRCUMSTANCE)
        ret = "Circumstance type.";
    else if (type == Type::ITEM)
        ret = "Item type.";
    else if (type == Type::LUCK)
        ret = "Luck type.";
    else if (type == Type::PENALTY)
        ret = "Penalty type.";
    else if (type == Type::BONUS)
        ret = "Bonus type.";

    return ret;
}

EffectBase::Type EffectBase::formattingType(const std::string &string)
{
    Type ret;

    if (string == "No value type.")
        ret = Type::NO_VALUE_TYPE;
    else if (string == "Common type.")
        ret = Type::COMMON_TYPE;
    else if (string == "Status typr.")
        ret = Type::STATUS;
    else if (string == "Circumstance type.")
        ret = Type::CIRCUMSTANCE;
    else if (string == "Item type.")
        ret = Type::ITEM;
    else if (string == "Luck type.")
        ret = Type::LUCK;
    else if (string == "Penalty type.")
        ret = Type::PENALTY;
    else if (string == "Bonus type.")
        ret = Type::BONUS;

    return ret;
}
} // namespace pf2e_manager
