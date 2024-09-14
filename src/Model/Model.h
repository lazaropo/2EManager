#ifndef _MODEL_H_1841F277_9334_475B_B5F3_FEBED75CDCF8_
#define _MODEL_H_1841F277_9334_475B_B5F3_FEBED75CDCF8_

#include <algorithm>
#include <initializer_list>
#include <list>
#include <stdexcept>
#include <utility>  // std::pair, std::forward
#include <vector>

#include "Combatant.h"
#include "Mediator.h"
#ifdef _USE_TXT_READER_
#include "TXTReader.h"
#endif
// #include "SimpleEffectBuilder.h"

#ifdef _USE_BOOST_SERIALIZE_
#include <boost/config.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/string.hpp>
#include <boost/archive/tmpdir.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

#include <boost/serialization/version.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/nvp.hpp>


#include <fstream> // ostream for boost::serialize

#if defined(BOOST_NO_STD_NAMESPACE)
namespace std {
using ::remove;
}
#endif

#endif
#ifdef _USE_BOOST_SERIALIZE_
namespace pf2e_manager {
class Model;
}
BOOST_CLASS_IMPLEMENTATION(pf2e_manager::Model,boost::serialization::object_class_info )
BOOST_CLASS_IMPLEMENTATION(pf2e_manager::Combatant,boost::serialization::object_class_info )
//BOOST_CLASS_IMPLEMENTATION(pf2e_manager::EffectBase,boost::serialization::object_class_info )
BOOST_CLASS_IMPLEMENTATION(pf2e_manager::SimpleEffect, boost::serialization::object_class_info )

BOOST_CLASS_TRACKING(pf2e_manager::Model, boost::serialization::track_selectively )
BOOST_CLASS_TRACKING(pf2e_manager::Combatant, boost::serialization::track_selectively )
//BOOST_CLASS_TRACKING(pf2e_manager::EffectBase, boost::serialization::track_selectively )
BOOST_CLASS_TRACKING(pf2e_manager::SimpleEffect, boost::serialization::track_selectively )

BOOST_CLASS_VERSION(pf2e_manager::Model, 1)
#endif

namespace pf2e_manager {
class Model {
 public:
  using t_pos_comb = std::list<Combatant*>::iterator;
  using t_pair_comb_with_effect = std::pair<t_pos_comb, Combatant::t_pos_eff>;

  Model() {
      if(!_combatants)
          _combatants = new std::list<Combatant*>;
  }

  Model(std::function<int(SubjectBase*, SubjectBase*, const std::string&)> fp);

  ~Model();

  // void addCombatant(t_pos_comb pos, Combatant new_body) {
  //   _combatants.insert(pos, std::move(new_body));
  // }

  void addCombatant(Combatant* new_body) { _combatants->push_back(new_body); }

  void addCombatant(t_pos_comb pos, Combatant* new_body) {
    _combatants->insert(pos, new_body);
  }

  //  void addCombatantGroup(t_pos_comb pos, std::vector<Combatant>& other) {
  //    for (auto it : other) addCombatant(pos, std::move(it));
  //  }

  void moveCombatant(t_pos_comb from, t_pos_comb before);

  // void addCommand(CommandBase* cmd) { _mediator->makeCommand(cmd); }
  // void addAndDoCommand(CommandBase* cmd) { _mediator->addAndDoCommand(cmd); }
  CommandBase* makeCommand(
      SubjectBase* sender, const std::string& name,
      std::vector<std::pair<pf2e_manager::SubjectBase*, int>>& info);
  // void removeCommand(Mediator::t_pos_cmd pos) { _mediator->undoCommand(pos);
  // }
  void removeCombatant(t_pos_comb it) { _combatants->erase(it); }
  void removeCombatant(Combatant* ptr) { _combatants->remove(ptr); }
  void removeCombatantGroup(std::vector<t_pos_comb>& collection) {
    for (auto it : collection) removeCombatant(it);
  }

  void addEffect(SimpleEffectBuilder* builder, t_pos_comb pos) {
    builder->setReciever(*pos);
    addEffect(builder, *pos);
  }

  void addEffect(SimpleEffectBuilder* builder, Combatant* pos) {
    builder->setReciever(pos);
    if (pos)
      pos->addEffect(builder->getSimpleEffect());
    else
      builder->reset();
  }

  void makeEffect(SubjectBase* sender, SubjectBase* reciever,
                  const std::string& name, const int duration,
                  const int value) {
    _mediator->makeEffect(sender, reciever, name, duration, value);
  }

  void addEffectOnGroup(SimpleEffectBuilder* builder,
                        std::vector<t_pos_comb>& collection);

  void setEffectDuration(int duration, t_pair_comb_with_effect pair) {
    (*pair.first)->setEffectDuration(pair.second, duration);
  }

  void setEffectDurationOnGroup(
      int duration, std::vector<t_pair_comb_with_effect>& collection) {
    for (auto it : collection) setEffectDuration(duration, it);
  }

  void sortByInit() {
    _combatants->sort([](const Combatant* a, const Combatant* b) {
      // the std::greater-like definition. first combatant with greater init and
      // side::eneamy or side::other.
      bool ret = false;
      int init1 = a->getInitiative();
      int init2 = b->getInitiative();
      if (init1 > init2)
        ret = true;
      else if (init1 == init2 && a->getSide() != b->getSide()) {
        if (a->getSide() == Combatant::Side::TEAM)
          ret = false;
        else if (b->getSide() == Combatant::Side::TEAM)
          ret = true;
      }
      return ret;
    });
    _curr_pos = _combatants->begin();
  }

  void startTurn();

  void nextTurn();

  const std::list<Combatant*>* getCombatants() const { return _combatants; }

  std::list<Combatant*>* getCombatants() { return _combatants; }

  const std::vector<CommandBase*>& getCommands() const {
    return _mediator->getCommands();
  }

  std::vector<CommandBase*>& getCommands() { return _mediator->getCommands(); }

  Combatant* getCurrent() { return *_curr_pos; }
#ifdef _USE_BOOST_SERIALIZE_

  friend class boost::serialization::access;
  friend inline std::ostream& operator<<(std::ostream &os, const Model &object);

  // template<class Archive>
  // friend inline void ::boost::serialization::save_construct_data(Archive &ar, const pf2e_manager::Model *d, const unsigned int file_version);
  // template<class Archive>
  // friend inline void ::boost::serialization::load_construct_data(Archive &ar, pf2e_manager::Model *d, const unsigned int file_version);

  private:
  template<class Archive>
  void serialize(Archive &ar, const size_t version)
  {

      ar.register_type(static_cast<Combatant *>(nullptr));
      // ar.register_type(static_cast<EffectBase *>(nullptr));
      ar.register_type(static_cast<SimpleEffect *>(nullptr));
    //if(version>0) {
      ar & BOOST_SERIALIZATION_NVP(*_combatants);
      // ar & _mediator;
      //  & BOOST_SERIALIZATION_NVP(_curr_pos);
      //}
  }

  template<class Archive>
  void save(Archive & ar, const unsigned int version) const
  {
      // note, version is always the latest when saving
      ar & _combatants;
      ar &_curr_pos;
  }
  template<class Archive>
  void load(Archive & ar, const unsigned int version)
  {
      if(version > 0) {
          ar & _combatants;
      ar &_curr_pos;
      }
      if(!_combatants)
          _combatants = new std::list<Combatant*>;
  }
  // BOOST_SERIALIZATION_SPLIT_MEMBER()

  private:
  void setCombatants(std::list<Combatant *> *list)
  {
      delete _combatants;
      _combatants = list;
  }

  void setCurrentPosition(t_pos_comb pos) { _curr_pos = pos; }

#endif

 private:
  std::list<Combatant*>* _combatants = nullptr;
  MediatorInterface* _mediator;

  t_pos_comb _curr_pos;
#ifdef _USE_TXT_READER_
  FileReaderBase* _reader;
  const std::string _path = ("../Saved_info/info.txt");
#endif


};



} // namespace pf2e_manager
// using namespace pf2e_manager;


#endif
//inline void boost::serialization::save_construct_data(Archive & ar, const Model * t, const unsigned int file_version) {
//  ar << t->_combatants;
//  ar << t->_curr_pos;
//}
#ifdef _USE_BOOST_SERIALIZE_
namespace pf2e_manager {

inline std::ostream &operator<<(std::ostream &os, const pf2e_manager::Model &object)
{
  for (auto it : *object._combatants)
      os << ' ' << std::hex << it << std::dec << ' ' << *it;
  os << *object._curr_pos;
  return os;
}

inline void save_model(const Model &object, const char *filename)
{
    //using namespace ::pf2e_manager;
    using namespace ::boost;

    std::ofstream os(filename);
    assert(os.good());
    ::boost::archive::xml_oarchive oa(os);
    //oa << object;
    oa << BOOST_SERIALIZATION_NVP(object);
}

inline void restore_model(Model &object, const char *filename)
{
    //using namespace ::pf2e_manager;
    using namespace ::boost;

    std::ifstream is(filename);
    assert(is.good());
    ::boost::archive::xml_iarchive ia(is);
    ia >> BOOST_SERIALIZATION_NVP(object);
}

}
#endif

/*
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <boost/serialization/export.hpp>
#include <iostream>
#include <fstream>

//base class
struct base
{
  base(double d) : m_d(d) {}
  virtual double run() = 0;
private:

  friend class boost::serialization::access;
  double m_d;
  template <class Archive>
  void serialize(Archive& ar, const unsigned int version)
  {
    ar & m_d;
  }
};

//forward declare the save construct data before friending it
// (something about friend being in a different namespace)
class derived;
namespace boost { namespace serialization {
template<class Archive>
inline void save_construct_data(Archive & ar, const derived * t, const unsigned int file_version);
}}


//derived class with non-default constructor
struct derived : public base
{
  derived(double a , double b) :
    base(a+b),
    m_a(a),m_b(b),m_c(a*b)
  {}
  //some checks
  double get_a() const {return m_a;}
  double get_b() const {return m_b;}
  double get_c() const {return m_c;}

  double run(){return 1.0;}
private:

  friend class boost::serialization::access;
  template<class Archive>
  friend void boost::serialization::save_construct_data(Archive & ar, const derived * t, const unsigned int file_version);

  template <class Archive>
  void serialize(Archive& ar, const unsigned int version)
  {
    ar & boost::serialization::base_object<base>(*this);
    //only need to return c, a and b already done for constructor
    ar & m_c;
  }
  double m_a, m_b, m_c;
 };

//Save and load the data required for the constructor.
namespace boost { namespace serialization {
  template <class Archive>
    inline void save_construct_data(
                    Archive & ar,const derived* d,const unsigned int file_version
                    )
    {
      // save data required to construct instance
      ar << d->m_a;
      ar << d->m_b;
    }
    template <class Archive>
    inline void load_construct_data(
                        Archive & ar, derived* d,const unsigned int file_version
                        )
    {
      double a,b;
      ar >> a;
      ar >> b;
    // invoke inplace constructor to initialize instance of my_class
      ::new(d) derived(a,b);
    }

  }
}

//register the derived class with boost.
BOOST_CLASS_EXPORT_GUID(derived, "derived")

int main  (int ac, char **av)
{
  std::ofstream ofs("filename");
  base* p = new derived(2,3);

  // save data to archive
  {
    boost::archive::text_oarchive oa(ofs);
    oa << p;
  }

  // ... some time later restore the class instance to its orginal state
  base* p2;
  {
     std::ifstream ifs("filename");
     boost::archive::text_iarchive ia(ifs);
     ia >> p2;
  }

  derived* d = static_cast<derived*>(p2);
  std::cout<<"p2 vals are: "<<d->get_a()<<" "<<d->get_b()<<" "<<d->get_c()<<std::endl;

}*/
