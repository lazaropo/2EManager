#ifndef _INVOKER_H_FB1B5BB7_152F_4BF6_9845_8B4B026A68A9_
#define _INVOKER_H_FB1B5BB7_152F_4BF6_9845_8B4B026A68A9_

#include <functional> // std::function
#include <string>
#include <vector>

#include "CommandBase.h"
#include "CommandsCreator.h"
#include "EffectDirector.h"
#include "MediatorInterface.h"
#include "SubjectBase.h"

#ifdef _BOOST_SERIALIZATION_XML_
#include <boost/config.hpp>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/tmpdir.hpp>

#include <boost/serialization/base_object.hpp>

#include <boost/serialization/vector.hpp>

#include <boost/serialization/export.hpp>

// using namespace ::pf2e_manager;

#endif

namespace pf2e_manager {
class Mediator : public MediatorInterface {
#ifdef _BOOST_SERIALIZATION_XML_
    friend class ::boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& ::boost::serialization::base_object<MediatorInterface>(*this);
        ar & _commands;
    }
#endif
public:
    using t_pos_cmd = std::vector<CommandBase*>::iterator;

    Mediator()
        : MediatorInterface()
    {}

    explicit Mediator(std::vector<Combatant*>* combatant,
                      std::function<int(SubjectBase*, SubjectBase*, const std::string&)> fp);

    ~Mediator();

    int getConfirmation(SubjectBase* sender, SubjectBase* reciever, const std::string& name) override
    {
        return _callback(sender, reciever, name);
    }

    void makeEffect(SubjectBase* sender,
                    SubjectBase* reciever,
                    const std::string& name,
                    const int duration = 0,
                    const int value = 0) override;

    CommandBase* makeCommand(SubjectBase* sender,
                             const std::string& name,
                             std::vector<std::pair<SubjectBase*, int>>& info) override;

    void doCommand(CommandBase* cmd)
    {
        cmd->execute();
        _commands.push_back(cmd);
    }

    void undoEffect(
#ifdef __clang__ || __GNUC__ || __GNUG__
        __attribute__((unused))
#endif
        SubjectBase* sender,

#ifdef __clang__ || __GNUC__ || __GNUG__
        __attribute__((unused))
#endif
        SubjectBase* reciever,

#ifdef __clang__ || __GNUC__ || __GNUG__
        __attribute__((unused))
#endif
        const std::string& name) override
  {}

  void undoCommand(
#ifdef __clang__ || __GNUC__ || __GNUG__
      __attribute__((unused))
#endif
      SubjectBase* sender,

#ifdef __clang__ || __GNUC__ || __GNUG__
      __attribute__((unused))
#endif
      SubjectBase* reciever,

#ifdef __clang__ || __GNUC__ || __GNUG__
      __attribute__((unused))
#endif
      const std::string& name) override
  {}

  void undoCommand(t_pos_cmd pos) { (*pos)->undo(); }

  const std::vector<CommandBase*>& getCommands() const override {
    return _commands;
  }

  std::vector<CommandBase*>& getCommands() override { return _commands; }

 private:
     std::vector<Combatant*>* _combatants;
     std::vector<CommandBase*> _commands;

     SimpleEffectBuilder* _builder;
     EffectDirector* _director;

     CommandsCreator* _commands_creator;

     std::function<int(SubjectBase*, SubjectBase*, const std::string&)> _callback;
};
}  // namespace pf2e_manager

// BOOST_CLASS_EXPORT(pf2e_manager::Mediator);

#endif
