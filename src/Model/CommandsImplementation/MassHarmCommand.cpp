#include "MassHarmCommand.h"

#ifdef _BOOST_SERIALIZATION_TXT_
template<class Archive>
void pf2e_manager::MassHarmCommand::serialize(Archive &ar, const unsigned int version)
{
    // serialize base class information
    // ar.template register_type<::pf2e_manager::SubjectBase>();
    // ar.template register_type<::pf2e_manager::CommandBase>();
    // ar.template register_type<::pf2e_manager::HarmCommand>();

    // ar.template register_type<::pf2e_manager::SubjectBase*>();
    // ar.template register_type<::pf2e_manager::CommandBase*>();
    // ar.template register_type<::pf2e_manager::HarmCommand*>();

    ar & ::boost::serialization::base_object<CommandBase>(*this);
    // ar &boost::serialization::make_nvp("_info", _info);
    ar & _info;
}
template void pf2e_manager::MassHarmCommand::serialize<boost::archive::text_oarchive>(boost::archive::text_oarchive & ar, const unsigned int version);
template void pf2e_manager::MassHarmCommand::serialize<boost::archive::text_iarchive>(boost::archive::text_iarchive & ar, const unsigned int version);

BOOST_CLASS_EXPORT_IMPLEMENT(pf2e_manager::MassHarmCommand);
//BOOST_CLASS_EXPORT_IMPLEMENT(pf2e_manager::HarmCommand);
#endif

#ifdef _BOOST_SERIALIZATION_XML_
template<class Archive>
void pf2e_manager::MassHarmCommand::serialize(Archive& ar, const unsigned int version)
{
    // ar.template register_type<::pf2e_manager::SubjectBase>();
    // ar.template register_type<::pf2e_manager::SubjectBase*>();

    ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP(CommandBase);

    // ar& boost::serialization::make_nvp("_value", _value);
    // ar& boost::serialization::make_nvp("_is_active", _is_active);

     ar & BOOST_SERIALIZATION_NVP(_info);
    // ar & BOOST_SERIALIZATION_NVP(_is_active);
}
template void pf2e_manager::MassHarmCommand::serialize<boost::archive::xml_oarchive>(boost::archive::xml_oarchive & ar, const unsigned int version);
template void pf2e_manager::MassHarmCommand::serialize<boost::archive::xml_iarchive>(boost::archive::xml_iarchive & ar, const unsigned int version);

BOOST_CLASS_EXPORT_IMPLEMENT(pf2e_manager::MassHarmCommand);
#endif

namespace pf2e_manager {

MassHarmCommand::MassHarmCommand(
    MediatorInterface *mediator, SubjectBase *sender,
    const std::vector<std::pair<SubjectBase *, int> > &info)
    : CommandBase(info[0].second, this), _mediator(mediator) {
  setName("command:massharm");
  setInvoker(sender);
  setReciever(info[0].first);

  for (auto it : info)
    _info.push_back(new HarmCommand(_mediator, this, it.first, it.second));
}

void MassHarmCommand::execute() {
  if (_is_active) return;

  for (auto it : _info) it->execute();

  _is_active = true;
}

void MassHarmCommand::undo() {
  if (!_is_active) return;

  for (auto it : _info) it->undo();

  _is_active = false;
}
}  // namespace pf2e_manager
