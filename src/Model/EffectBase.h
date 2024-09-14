#ifndef _EFFECTBASE_H_73406A90_5BBE_11EF_A550_0800200C9A66_
#define _EFFECTBASE_H_73406A90_5BBE_11EF_A550_0800200C9A66_

#include <string>
#include <vector>

#ifdef _USE_BOOST_SERIALIZE_
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/assume_abstract.hpp>
#endif

#include "SubjectBase.h"

namespace pf2e_manager {
class EffectBase : public SubjectBase {
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
  struct Value {
    Value() = default;
    explicit Value(bool is_constant, int value)
        : _is_constant(is_constant), _value(value) {}

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
    int _perc = 0;  // perception

    int _atk = 0;
    int _ac = 0;
    int _dc = 0;  // class DC
    int _init = 0;

#ifdef _USE_BOOST_SERIALIZE_
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive & ar, const size_t version) {
            ar & BOOST_SERIALIZATION_NVP(_str);
            ar & BOOST_SERIALIZATION_NVP(_dex);
            ar & BOOST_SERIALIZATION_NVP(_con );
            ar & BOOST_SERIALIZATION_NVP(_mind);
            ar & BOOST_SERIALIZATION_NVP(_fort);
            ar & BOOST_SERIALIZATION_NVP(_refl);
ar & BOOST_SERIALIZATION_NVP(_will);
ar & BOOST_SERIALIZATION_NVP(_skills);
ar & BOOST_SERIALIZATION_NVP(_perc);
ar & BOOST_SERIALIZATION_NVP(_atk );
ar & BOOST_SERIALIZATION_NVP(_ac );
ar & BOOST_SERIALIZATION_NVP(_dc );
ar & BOOST_SERIALIZATION_NVP(_init);

    }
    friend inline std::ostream &operator<<(std::ostream &os, const Value &value);

#endif

  };
  EffectBase() {}
  EffectBase(EffectBase *child) : SubjectBase(child) {}
  EffectBase(EffectBase *child, SubjectBase *reciever)
      : SubjectBase(child, reciever) {}

  virtual void execute() = 0;
  virtual void undo() = 0;
  virtual void activateEffect() = 0;
  virtual void removeEffect() = 0;
  virtual void executeAssociated() = 0;

  void notifyTrigger(Trigger trigger) {
    if (trigger == _trigger) execute();
  }

  int getValue() const { return _value._value; }
  int getDuration() const { return _duration; }
  int isActive() const { return _is_active; }
  const std::string &getDescription() const { return _description; }

#ifdef _USE_BOOST_SERIALIZE_
  friend class boost::serialization::access;
  template <class Archive>
  void serialize(Archive & ar, const size_t version) {
    if(_is_active) {
        ar &BOOST_SERIALIZATION_BASE_OBJECT_NVP(SubjectBase);
    ar & BOOST_SERIALIZATION_NVP(_duration);
    ar & BOOST_SERIALIZATION_NVP(_is_active);
    ar & BOOST_SERIALIZATION_NVP(_type);
    ar & BOOST_SERIALIZATION_NVP(_value);
    ar & BOOST_SERIALIZATION_NVP(_trigger);
    ar & BOOST_SERIALIZATION_NVP(_description);
    }
  }
  friend inline std::ostream &operator<<(std::ostream &os, const EffectBase &effect);

#endif

  protected:
  int _duration = 0;  // per round
  bool _is_active = false;
  int _type = 0;  // bit field
  Value _value = Value();
  Trigger _trigger = Trigger::NO_TRIGGER;

  std::string _description = "";
};


#ifdef _USE_BOOST_SERIALIZE_
inline std::ostream &operator<<(std::ostream &os, const EffectBase::Trigger &trigger)
{
  os << ' ' << trigger;
  return os;
}

inline std::ostream &operator<<(std::ostream &os, const EffectBase &effect)
{
  os << ' ' << effect._duration << ' ' << effect._is_active << ' ' << effect._type << ' '
     << effect._value << ' ' << effect._trigger << ' ' << effect._description << '\n';
  return os;
}
#endif
}  // namespace pf2e_manager
#ifdef _USE_BOOST_SERIALIZE_
BOOST_SERIALIZATION_ASSUME_ABSTRACT(pf2e_manager::EffectBase)
#endif

#endif  // EFFECTBASE_H
