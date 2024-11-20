#include "Mediator.h"

#ifdef _BOOST_SERIALIZATION_TXT_
template<class Archive>
void pf2e_manager::Mediator::serialize(Archive& ar, const unsigned int version)
{
    // ar& ::boost::serialization::base_object<MediatorInterface>(*this);
    // ar& boost::serialization::make_nvp("_commands", _commands);
    // ar& boost::serialization::make_nvp("_combatants", _combatants);

    ar & _combatants;
    ar & _commands;
}
template void pf2e_manager::Mediator::serialize<boost::archive::text_oarchive>(boost::archive::text_oarchive & ar, const unsigned int version);
template void  pf2e_manager::Mediator::serialize<boost::archive::text_iarchive>(boost::archive::text_iarchive & ar, const unsigned int version);

BOOST_CLASS_EXPORT_IMPLEMENT(pf2e_manager::Mediator);
// BOOST_CLASS_EXPORT_IMPLEMENT(pf2e_manager::Combatant);
#endif

#ifdef _BOOST_SERIALIZATION_XML_
template<class Archive>
void pf2e_manager::Mediator::serialize(Archive& ar, const unsigned int version)
{
    ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP(MediatorInterface);
    // ar& boost::serialization::make_nvp("_commands", _commands);
    // ar& boost::serialization::make_nvp("_combatants", _combatants);

    ar & BOOST_SERIALIZATION_NVP(_combatants);
    ar & BOOST_SERIALIZATION_NVP(_commands);
}
template void pf2e_manager::Mediator::serialize<boost::archive::xml_oarchive>(boost::archive::xml_oarchive & ar, const unsigned int version);
template void  pf2e_manager::Mediator::serialize<boost::archive::xml_iarchive>(boost::archive::xml_iarchive & ar, const unsigned int version);

BOOST_CLASS_EXPORT_IMPLEMENT(pf2e_manager::Mediator);
#endif

namespace pf2e_manager {
Mediator::Mediator(std::vector<Combatant*>* combatant,
                   std::function<int(SubjectBase*, SubjectBase*, const std::string&)> fp)
    : _combatants(combatant)
    , _builder(new SimpleEffectBuilder(this))
    , _director(new EffectDirector(_builder))
    , _commands_creator(new CommandsCreator(this))
    , _callback(fp)
{
    _builder->reset();
}

Mediator::~Mediator() {
  for (auto it : _commands) delete it;

  delete _builder;
  delete _director;
  delete _commands_creator;
}

void Mediator::makeEffect(SubjectBase* sender, SubjectBase* reciever,
                          const std::string& name, const int duration,
                          const int value) {
  Combatant* combatant = dynamic_cast<Combatant*>(reciever);
  if (!combatant)
    throw std::runtime_error(
        "Mediator - MakeEffect func: reciever is not Combatant class.");
  auto effects = &combatant->getEffects();
  Combatant::t_pos_eff it =
      std::find_if(effects->begin(), effects->end(), [&name](EffectBase* eff) {
        if (eff)
          return eff->getName() == name;
        else
          return false;
      });
  if (it != effects->end()) (*it)->removeEffect();

  _director->buildEffectByName(name, duration, value);
  _builder->setInvoker(sender);
  _builder->setReciever(combatant);
  combatant->addEffect(_builder->getSimpleEffect());
  if (!_combatants || _combatants->size()) return;
}

CommandBase* Mediator::makeCommand(
    SubjectBase* sender, const std::string& name,
    std::vector<std::pair<pf2e_manager::SubjectBase*, int>>& info) {
  CommandBase* command =
      _commands_creator->createCommandByName(sender, name, info);
  doCommand(command);
  return command;
}

}  // namespace pf2e_manager
