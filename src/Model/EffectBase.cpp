#include "EffectBase.h"

namespace pf2e_manager {
// std::string EffectBase::formattingValue(EffectBase::Value side, bool is_first_upper, bool with_colon)
// {
//     std::string ret;
//     if (side == Value::TEAM) {
//         if (is_first_upper && with_colon)
//             ret = "Team:";
//         else if (is_first_upper && !with_colon)
//             ret = "Team";
//         else if (with_colon)
//             ret = "team:";
//         else
//             ret = "team";
//     } else if (side == Value::ENEAMY) {
//         if (is_first_upper && with_colon)
//             ret = "Eneamy:";
//         else if (is_first_upper && !with_colon)
//             ret = "Eneamy";
//         else if (with_colon)
//             ret = "eneamy:";
//         else
//             ret = "eneamy";
//     } else if (side == Value::OTHER) {
//         if (is_first_upper && with_colon)
//             ret = "Other:";
//         else if (is_first_upper && !with_colon)
//             ret = "Other";
//         else if (with_colon)
//             ret = "other:";
//         else
//             ret = "other";
//     }

//     return ret;
// }

// EffectBase::Value EffectBase::formattingValue(const std::string &string)
// {
//     Value ret;
//     if (string == "Team:" || string == "Team" || string == "team:" || string == "team")
//         ret = Value::TEAM;
//     else if (string == "Eneamy:" || string == "Eneamy" || string == "eneamy:" || string == "eneamy")
//         ret = Value::ENEAMY;
//     else if (string == "Other:" || string == "Other" || string == "other:" || string == "other")
//         ret = Value::OTHER;
//     else
//         throw std::invalid_argument("Incorrect string for Combatant::Size initialize.");

//     return ret;
// }

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
