#ifndef _COMBATANT_H_E1381FAB_5D83_4BD1_AFB3_CE0C044AF33E_
#define _COMBATANT_H_E1381FAB_5D83_4BD1_AFB3_CE0C044AF33E_

#include <algorithm>  //provides std::includes for effect instantiation in collection
// #include <list>
#include <stdexcept>
#include <string>
#include <vector>

#ifdef _USE_BOOST_SERIALIZE_
#include <boost/serialization/vector.hpp>

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/base_object.hpp>

#endif


#include "SubjectBase.h"
#include "EffectBase.h"



namespace pf2e_manager {

class Combatant : public SubjectBase {
 public:
  using t_pos_eff = std::vector<EffectBase*>::iterator;

  enum class Vitality { ALIVE, DEAD, CONSTRUCT };
  enum class Side { TEAM, ENEAMY, OTHER };

  Combatant() {}

  Combatant(int hp, int initiative, Side side, std::string name,
            Vitality vit = Vitality::ALIVE)
      : SubjectBase(this),
        _hp_max(hp),
        _hp_tmp(0),
        _hp_curr(hp),
        _initiative(initiative),
        _side(side),
        _vitality(vit) {
    setName(name);
  }

  ~Combatant() {
    for (auto it : _effects) delete it;
  }

  bool operator==(const Combatant& other) {
    return getName() == other.getName();
  }

  bool operator==(const std::string& name) { return getName() == name; }

  /**
   * @brief Definition of less < overload
   * which is condition for std::sort in @class Model class.
   *
   * @param other
   * @return true
   * @return false
   */
  //  friend bool operator<(const Combatant& fisrt, const Combatant& second);
  //  bool operator==(const Combatant& other) {
  //    return getName() == other.getName();
  //  }

  std::vector<EffectBase*>& getEffects() { return _effects; }

  void addEffect(EffectBase* effect) {
    _effects.push_back(effect);
    effect->executeAssociated();
  }

  void setEffectDuration(t_pos_eff pos, int duration);

  void notifyTrigger(EffectBase::Trigger trigger) {
    for (auto it : _effects) it->notifyTrigger(trigger);
  }

   static  std::string formattingSide(Side side, bool is_first_upper,
                                    bool with_colon);
  static Side formattingSide(const std::string& string);

  static std::string formattingVitality(Vitality side, bool is_first_upper,
                                        bool with_colon);
  static Vitality formattingVitality(const std::string& string);

  int getHPCurr() const { return _hp_curr; }

  void setHPCurr(int value) { _hp_curr = value; }

  int getHPMax() const { return _hp_max; }

  void setHPTmp(int value) { _hp_tmp = value; }

  int getHPTmp() const { return _hp_tmp; }

  Side getSide() const { return _side; }

  Vitality getVitality() const { return _vitality; }

  int getInitiative() const { return _initiative; }

  void setInitiative(int initiavite) { _initiative = initiavite; }

#ifdef _USE_BOOST_SERIALIZE_
  friend class boost::serialization::access;
  friend std::ostream &operator<<(std::ostream &os, const Combatant &combatant);

  template<class Archive>
  void serialize(Archive & ar, const size_t version) {
    // ar & boost::serialization::base_object<SubjectBase>(*this);
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(SubjectBase);
    ar & BOOST_SERIALIZATION_NVP(_hp_max);
    ar & BOOST_SERIALIZATION_NVP(_hp_tmp);
    ar & BOOST_SERIALIZATION_NVP(_hp_curr);
    ar & BOOST_SERIALIZATION_NVP(_initiative);
    ar & BOOST_SERIALIZATION_NVP(_level);
    ar & BOOST_SERIALIZATION_NVP(_side);
    ar & BOOST_SERIALIZATION_NVP(_vitality);
    ar & BOOST_SERIALIZATION_NVP(_effects);
  }

  template<class Archive>
  void save(Archive & ar, const unsigned int version) const
  {
      ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(SubjectBase);
      ar & BOOST_SERIALIZATION_NVP(_hp_max);
      ar & BOOST_SERIALIZATION_NVP(_hp_tmp);
      ar & BOOST_SERIALIZATION_NVP(_hp_curr);
      ar & BOOST_SERIALIZATION_NVP(_initiative);
      ar & BOOST_SERIALIZATION_NVP(_level);
      const std::string side = formattingSide(_side, false, false);
      ar & BOOST_SERIALIZATION_NVP(side);
      const std::string vitality = formattingVitality(_vitality, false, false);
      ar & BOOST_SERIALIZATION_NVP(vitality);
      ar & BOOST_SERIALIZATION_NVP(_effects);
      //  = labels[static_cast<int>(a_)];
      // ar & boost::serialization::make_nvp("label", label);
  }
  template<class Archive>
  void load(Archive & ar, const unsigned int version)
  {
      ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(SubjectBase);
      ar & BOOST_SERIALIZATION_NVP(_hp_max);
      ar & BOOST_SERIALIZATION_NVP(_hp_tmp);
      ar & BOOST_SERIALIZATION_NVP(_hp_curr);
      ar & BOOST_SERIALIZATION_NVP(_initiative);
      ar & BOOST_SERIALIZATION_NVP(_level);
      std::string side;
      ar & BOOST_SERIALIZATION_NVP(side);
      _side = formattingSide(side);
      std::string vitality;
      ar & BOOST_SERIALIZATION_NVP(vitality);
      _vitality = formattingVitality(vitality);
      ar & BOOST_SERIALIZATION_NVP(_effects);
      //  = labels[static_cast<int>(a_)];
      // ar & boost::serialization::make_nvp("label", label);
  }
  BOOST_SERIALIZATION_SPLIT_MEMBER();
#endif

 private:
  int _hp_max;
  int _hp_tmp = 0;
  int _hp_curr;
  int _initiative;
  int _level;
  Side _side = Side::OTHER;
  // std::string _name = "";
  Vitality _vitality = Vitality::CONSTRUCT;

  std::vector<EffectBase*> _effects = {};
};
#ifdef _USE_BOOST_SERIALIZE_
inline std::ostream &operator<<(std::ostream &os, const Combatant::Side &side)
{
  os << ' ' << side;
  return os;
}

inline std::ostream &operator<<(std::ostream &os, const Combatant::Vitality &vitality)
{
  os << ' ' << vitality;
  return os;
}

inline std::ostream &operator<<(std::ostream &os, const Combatant &combatant)
{
  os << ' ' << combatant._hp_max << ' ' << combatant._hp_tmp << ' ' << combatant._hp_curr << ' '
     << combatant._initiative << ' ' << combatant._level << ' ' << combatant._side << ' '
     << combatant._vitality;

  for (std::vector<EffectBase *>::const_iterator it = combatant._effects.begin(),
                                                 it_end = combatant._effects.end();
       it != it_end;
       ++it)
    os << ' ' << std::hex << "0x" << *it << std::dec << ' ' << **it;
  return os;
}
#endif
// inline bool operator<(const Combatant& fisrt, const Combatant& second) {
//   return fisrt._initiative < second._initiative;
// }
}  // namespace pf2e_manager

#endif
