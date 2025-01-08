#ifndef _INVOKER_H_FB1B5BB7_152F_4BF6_9845_8B4B026A68A9_
#define _INVOKER_H_FB1B5BB7_152F_4BF6_9845_8B4B026A68A9_

#include <functional>  // std::function
#include <string>
#include <vector>

#include "CommandBase.h"
#include "CommandsCreator.h"
#include "EffectDirector.h"
#include "MediatorInterface.h"
#include "SubjectBase.h"
#include "utility.h"

#if defined(_BOOST_SERIALIZATION_TXT_) || defined(_BOOST_SERIALIZATION_XML_)

#ifdef _BOOST_SERIALIZATION_TXT_
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#endif

#ifdef _BOOST_SERIALIZATION_XML_
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#endif

#include <boost/archive/tmpdir.hpp>
#include <boost/config.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>

// using namespace ::pf2e_manager;

#endif

namespace pf2e_manager {
class Mediator : public MediatorInterface {
 public:
  using t_container_comb = utility::t_combatant_container;
  using t_pos_cmd = std::vector<CommandBase*>::iterator;

#if defined(_BOOST_SERIALIZATION_TXT_) || defined(_BOOST_SERIALIZATION_XML_)
  friend class ::boost::serialization::access;
  template <class Archive>
  void serialize(Archive& ar, const unsigned int version);

  template <class Archive>
  void serialize(Archive& ar, t_container_comb& g, const unsigned int version);
#endif
 public:
  Mediator() : MediatorInterface() {}

  explicit Mediator(
      t_container_comb* combatant,
      std::function<int(SubjectBase*, SubjectBase*, const std::string&)> fp);

  ~Mediator();

  int getConfirmation(SubjectBase* sender, SubjectBase* reciever,
                      const std::string& name) override {
    return _callback(sender, reciever, name);
  }

  void makeEffect(SubjectBase* sender, SubjectBase* reciever,
                  const std::string& name, const int duration = 0,
                  const int value = 0) override;

  CommandBase* makeCommand(
      SubjectBase* sender, const std::string& name,
      std::vector<std::pair<SubjectBase*, int>>& info) override;

  void doCommand(CommandBase* cmd) override {
    cmd->execute();
    _commands.push_back(cmd);
  }

  void doEffect(EffectBase* sender) override {}

  void undoEffect(EffectBase* sender) override;

  void undoCommand(CommandBase* command) override;

  void undoCommand(t_pos_cmd pos) { (*pos)->undo(); }

  const std::vector<CommandBase*>& getCommands() const override {
    return _commands;
  }

  void removeCommand(CommandBase* command) override {
    if (!command) return;
    if (command->isActive()) command->undo();
    auto it = std::find(_commands.begin(), _commands.end(), command);
    if (it != _commands.end()) _commands.erase(it);
  }

  std::vector<CommandBase*>& getCommands() override { return _commands; }

  void setCallbackFunctionUserInput(
      std::function<int(SubjectBase*, SubjectBase*, const std::string&)>
          callback) override {
    _callback = callback;
  }

 private:
  t_container_comb* _combatants;
  std::vector<CommandBase*> _commands;

  SimpleEffectBuilder* _builder = new SimpleEffectBuilder(this);
  EffectDirector* _director = new EffectDirector(_builder);

  CommandsCreator* _commands_creator = new CommandsCreator(this);

  std::function<int(SubjectBase*, SubjectBase*, const std::string&)> _callback;
};
}  // namespace pf2e_manager

#ifdef _BOOST_SERIALIZATION_XML_
namespace boost {
namespace serialization {
template <class Archive, class T>
void serialize(Archive& ar, boost::container::stable_vector<T>& vec,
               const unsigned int version);
// template <class Archive>
// inline void save(Archive& ar, pf2e_manager::Mediator::t_container_comb& g,
//                  const unsigned int version);

// template <class Archive>
// inline void load(Archive& ar, pf2e_manager::Mediator::t_container_comb& g,
//                  const unsigned int version);
}  // namespace serialization
}  // namespace boost

// BOOST_SERIALIZATION_SPLIT_FREE(pf2e_manager::Mediator::t_container_comb);

BOOST_CLASS_EXPORT_KEY(pf2e_manager::Mediator);
BOOST_CLASS_EXPORT_KEY(pf2e_manager::Mediator::t_container_comb);
#endif
// BOOST_CLASS_EXPORT(pf2e_manager::Mediator);

#endif
