#ifndef _EFFECTBASE_H_73406A90_5BBE_11EF_A550_0800200C9A66_
#define _EFFECTBASE_H_73406A90_5BBE_11EF_A550_0800200C9A66_

#include <string>
#include <vector>

#include "SubjectBase.h"

#ifdef _BOOST_SERIALIZATION_XML_
#include <boost/config.hpp>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/tmpdir.hpp>
#include <boost/serialization/access.hpp>

#include <boost/serialization/split_member.hpp>

#include <boost/serialization/base_object.hpp>

#include <boost/serialization/string.hpp>
#endif

namespace pf2e_manager {
class EffectBase : public SubjectBase {
#ifdef _BOOST_SERIALIZATION_XML_
    friend std::ostream &operator<<(std::ostream &os, const pf2e_manager::EffectBase *instance);

    friend class ::boost::serialization::access;
    // template<class Archive>
    // void serialize(Archive &ar, const unsigned int version)
    // {
    //     // serialize base class information
    //     ar &boost::serialization::base_object<SubjectBase>(*this);

    //     ar & _duration; // per round
    //     ar & _is_active;
    //     ar & _type; // bit field
    //     ar & _value;
    //     ar & _trigger;

    //     ar & _description;
    // }

    template<class Archive>
    void save(Archive &ar, const unsigned int version) const
    {
        ar &boost::serialization::base_object<SubjectBase>(*this);

        ar & _duration; // per round
        ar & _is_active;
        ar & _type; // bit field
        ar & _value;
        ar & _trigger;

        ar & _description;
    }
    template<class Archive>
    void load(Archive &ar, const unsigned int version)
    {
        ar &boost::serialization::base_object<SubjectBase>(*this);

        ar & _duration; // per round
        ar & _is_active;
        ar & _type; // bit field
        ar & _value;
        ar & _trigger;

        ar & _description;
    }
    BOOST_SERIALIZATION_SPLIT_MEMBER()
#endif
public:
    enum class Trigger { NO_TRIGGER, START_TURN, END_TURN };
    enum Type {
        NO_VALUE_TYPE = 0,
        COMMON_TYPE = 1 << 0,
        STATUS = 1 << 1,
        CIRCUMSTANCE = 1 << 2,
        ITEM = 1 << 3,
        LUCK = 1 << 4,
        PENALTY = 1 << 5,
        BONUS = 1 << 6
    };
    struct Value
    {
#ifdef _BOOST_SERIALIZATION_XML_
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive &ar, const unsigned int version)
        { // per round
            ar &_is_constant = true;
            ar &_value = 0;
            ar &_str = 0;
            ar &_dex = 0;
            ar &_con = 0;
            ar &_mind = 0;
            ar &_fort = 0;
            ar &_refl = 0;
            ar &_will = 0;
            ar &_skills = 0;
            ar &_perc = 0; // perception
            ar &_atk = 0;
            ar &_ac = 0;
            ar &_dc = 0; // class DC
            ar &_init = 0;
        }
#endif
        Value() = default;
        explicit Value(bool is_constant, int value)
            : _is_constant(is_constant)
            , _value(value)
        {}

        operator bool() const { return _value; }

        bool _is_constant = true;
        int _value = 0;

        int _str = 0;
        int _dex = 0;
        int _con = 0;
        int _mind = 0;

        int _fort = 0;
        int _refl = 0;
        int _will = 0;

        int _skills = 0;
        int _perc = 0; // perception

        int _atk = 0;
        int _ac = 0;
        int _dc = 0; // class DC
        int _init = 0;
    };

    EffectBase()
        : SubjectBase(this)
    {}
    EffectBase(EffectBase *child)
        : SubjectBase(child)
    {}
    EffectBase(EffectBase *child, SubjectBase *reciever)
        : SubjectBase(child, reciever)
    {}

    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual void activateEffect() = 0;
    virtual void removeEffect() = 0;
    virtual void executeAssociated() = 0;

    void notifyTrigger(Trigger trigger)
    {
        if (trigger == _trigger)
            execute();
    }

    int getValue() const { return _value._value; }
    int getDuration() const { return _duration; }
    int isActive() const { return _is_active; }
    const std::string &getDescription() const { return _description; }

    static std::string formattingValue(Value side);
    static Value formattingValue(const std::string &string);

    static std::string formattingTrigger(Trigger side);
    static Trigger formattingTrigger(const std::string &string);

    static std::string formattingType(Type side);
    static Type formattingType(const std::string &string);

protected:
    int _duration = 0; // per round
    bool _is_active = false;
    int _type = 0; // bit field
    Value _value = Value();
    Trigger _trigger = Trigger::NO_TRIGGER;

    std::string _description = "";
};

#ifdef _BOOST_SERIALIZATION_XML_
inline std::ostream &operator<<(std::ostream &os, const pf2e_manager::EffectBase *instance)
{
    os << static_cast<const pf2e_manager::SubjectBase *>(instance);
    os << instance->_duration << ' ' << instance->_is_active << ' ' << instance->_type << ' '
       << instance->_value._value << ' ' << EffectBase::formattingTrigger(instance->_trigger) << ' '
       << instance->_description;

    return os;
}
#endif
}  // namespace pf2e_manager

#endif  // EFFECTBASE_H
