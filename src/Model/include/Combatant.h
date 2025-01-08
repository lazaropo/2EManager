#ifndef _COMBATANT_H_E1381FAB_5D83_4BD1_AFB3_CE0C044AF33E_
#define _COMBATANT_H_E1381FAB_5D83_4BD1_AFB3_CE0C044AF33E_

#include <algorithm>  //provides std::includes for effect instantiation in collection
// #include <boost/container/stable_vector.hpp>
#include <stdexcept>
#include <string>
// #include <vector>

#include "EffectBase.h"
#include "SubjectBase.h"
#include "Utility.h"

#if defined(_BOOST_SERIALIZATION_TXT_) || defined(_BOOST_SERIALIZATION_XML_)

#ifdef _BOOST_SERIALIZATION_TXT_
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#endif

#ifdef _BOOST_SERIALIZATION_XML_
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/nvp.hpp>
#endif

#include <boost/archive/tmpdir.hpp>
#include <boost/config.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/vector.hpp>
#endif

namespace pf2e_manager { /**
                          * @brief Combatant is entity with some properties like
                          * hp max, hp curr, initiative, etc. It is a child
                          * class of @class SubjectBase that means the ability
                          * to set combatant as effect/command initiator. That
                          * class holds the effects, so, the last one can be
                          * activated/disactivated/removed by according
                          * combatant methods. Boost.serialization is used for
                          * data save/load mechanic with txt or xml file
                          * creation (defined at project cmake file).
                          *
                          */
class DecreaseMaxHpCommand;
class Combatant : public SubjectBase {
 public:
  using t_eff_container = utility::t_effect_container;
#if defined(_BOOST_SERIALIZATION_TXT_) || defined(_BOOST_SERIALIZATION_XML_)
  friend class ::boost::serialization::access;
  /**
   * @brief Template boost functions declaration. They are requiring of
   * boost::serializatoin library.
   *
   * @tparam Archive
   * @param ar
   * @param version
   */
  template <class Archive>
  void save(Archive& ar, const unsigned int version) const;
  template <class Archive>
  void load(Archive& ar, const unsigned int version);

  BOOST_SERIALIZATION_SPLIT_MEMBER()
#endif

  using t_pos_eff = ::boost::container::stable_vector<EffectBase*>::iterator;

  enum class Vitality { ALIVE, DEAD, CONSTRUCT };
  enum class Side { TEAM, ENEAMY, OTHER };
  /**
   * @brief Construct a new Combatant object.
   * Default constructor is boost::serializatoin library requiring.
   */
  Combatant()
      : SubjectBase(this),
        _hp_max(-1),
        _hp_tmp(0),
        _hp_curr(-1),
        _initiative(-1),
        _side(Side::OTHER),
        // _name(name),
        _vitality(Vitality::CONSTRUCT) {}
  /**
   * @brief Construct a new Combatant object. Other model classes have to
   * initialize cobmatant by this constructor. Throws the exception with
   * incorrect data.
   *
   * @param hp
   * @param initiative
   * @param side
   * @param name
   * @param vit
   */
  Combatant(int hp, int initiative, Side side, std::string name,
            Vitality vit = Vitality::ALIVE)
      : SubjectBase(this),
        _hp_max(hp),
        _hp_tmp(0),
        _hp_curr(hp),
        _initiative(initiative),
        _side(side),
        _vitality(vit) {
    if (hp <= 0)
      throw std::logic_error(
          "Combatant(int, int, Side, std::string, Vitality): HP is not "
          "correct.");
    if (initiative <= 0)
      throw std::logic_error(
          "Combatant(int, int, Side, std::string, Vitality): Initiavite is not "
          "correct.");
    setName(name);
    //_effects.clear();
  }
  /**
   * @brief Destroy the effects at current Combatant instance.
   *
   */
  ~Combatant() {
    for (auto it : _effects) delete it;
  }
  /**
   * @brief Useful overload. Provides combatants comparing by their names in
   * @class SubjectBase.
   *
   * @param other
   * @return true Names equality.
   * @return false Names are differ from each other.
   */

  bool operator==(const Combatant& other) {
    return getName() == other.getName();
  }

  bool operator==(const std::string& name) { return getName() == name; }

  // /**
  //  * @brief Definition of less < overload
  //  * which is condition for std::sort in @class Model class.
  //  *
  //  * @param other
  //  * @return true
  //  * @return false
  //  */
  // //  friend bool operator<(const Combatant& fisrt, const Combatant& second);
  // //  bool operator==(const Combatant& other) {
  // //    return getName() == other.getName();
  // //  }
  /**
   * @brief Acception the effect by its pointer. Now combatant owns this effect
   * instance.
   *
   * @param effect
   */
  t_eff_container& getEffects() { return _effects; }

  void addEffect(EffectBase* effect) {
    _effects.push_back(effect);
    effect->executeAssociated();
  }
  /**
   * @brief Remove the effect at Combatant instance. Not disable, but remove.
   *
   * @param effect
   * @return int
   */
  int removeEffect(EffectBase* effect) {
    int ret_val = -1;
    auto it = std::find(_effects.begin(), _effects.end(), effect);
    if (it != _effects.end()) {
      ret_val = it - _effects.begin();
      (*it)->removeEffect();
      _effects.erase(it);
    }
    return ret_val;
  }

  // void setEffectDuration(t_pos_eff pos, int duration);
  /**
   * @brief Notify every effect by trigger. Effects may do something after this.
   *
   * @param trigger
   */
  void notifyTrigger(EffectBase::Trigger trigger) {
    for (auto it : _effects) it->notifyTrigger(trigger);
  }
  /**
   * @brief Static functoins provide side and vitality convetion to string and
   * revers operation.
   *
   * @param side
   * @param is_first_upper
   * @param with_colon
   * @return std::string
   */
  static std::string formattingSide(Side side, bool is_first_upper,
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

  friend class DecreaseMaxHpCommand;

 private:
  int _hp_max;
  int _hp_tmp;
  int _hp_curr;
  int _initiative;
  int _level = 0;
  Side _side;
  Vitality _vitality;

  t_eff_container _effects = {};
};

// inline bool operator<(const Combatant& fisrt, const Combatant& second) {
//   return fisrt._initiative < second._initiative;
// }

#ifdef _BOOST_SERIALIZATION_XML_

// inline std::ostream& operator<<(std::ostream& os,
//                                 const pf2e_manager::Combatant* instance) {
//   os << static_cast<const pf2e_manager::SubjectBase*>(instance);
//   os << "PEPPAA " << instance->_hp_max << ' ' << instance->_hp_tmp << ' '
//      << instance->_hp_curr << ' ' << instance->_initiative << ' '
//      << instance->_level << ' '
//      << Combatant::formattingSide(instance->_side, false, false) << ' '
//      << Combatant::formattingVitality(instance->_vitality, false, false);

//   for (auto it : instance->_effects) os << it << ' ';

//   return os;
// }
#endif
}  // namespace pf2e_manager

#if defined(_BOOST_SERIALIZATION_TXT_) || defined(_BOOST_SERIALIZATION_XML_)
namespace boost {
namespace serialization {
template <class Archive, class T>
void serialize(Archive& ar, boost::container::stable_vector<T>& vec,
               const unsigned int version);
}  // namespace serialization
}  // namespace boost
// BOOST_SERIALIZATION_SPLIT_FREE(pf2e_manager::Combatant::t_eff_container)

BOOST_CLASS_EXPORT_KEY(pf2e_manager::Combatant);
BOOST_CLASS_EXPORT_KEY(pf2e_manager::Combatant::t_eff_container);

#endif

#endif
