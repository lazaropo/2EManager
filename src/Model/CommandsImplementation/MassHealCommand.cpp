#include "MassHealCommand.h"

#ifdef _BOOST_SERIALIZATION_XML_
template<class Archive>
void pf2e_manager::MassHealCommand::serialize(Archive &ar, const unsigned int version)
{
    // serialize base class information
    // ar.template register_type<::pf2e_manager::SubjectBase>();
    // ar.template register_type<::pf2e_manager::CommandBase>();
    // ar.template register_type<::pf2e_manager::HealCommand>();

    // ar.template register_type<::pf2e_manager::SubjectBase*>();
    // ar.template register_type<::pf2e_manager::CommandBase*>();
    // ar.template register_type<::pf2e_manager::HealCommand*>();

    ar & ::boost::serialization::base_object<CommandBase>(*this);
    ar &boost::serialization::make_nvp("_info", _info);
    ar & _info;
}
template void pf2e_manager::MassHealCommand::serialize<boost::archive::text_oarchive>(boost::archive::text_oarchive & ar, const unsigned int version);
template void pf2e_manager::MassHealCommand::serialize<boost::archive::text_iarchive>(boost::archive::text_iarchive & ar, const unsigned int version);

BOOST_CLASS_EXPORT_IMPLEMENT(pf2e_manager::MassHealCommand);
#endif

namespace pf2e_manager {
MassHealCommand::MassHealCommand(
    MediatorInterface *mediator, SubjectBase *sender,
    const std::vector<std::pair<SubjectBase *, int> > &info)
    : CommandBase(info[0].second, this), _mediator(mediator) {
  setName("command:massheal");
  setInvoker(sender);
  setReciever(info[0].first);

  for (auto it : info)
    _info.push_back(new HealCommand(_mediator, this, it.first, it.second));
}

void MassHealCommand::execute() {
  if (_is_active) return;

  for (auto it : _info) it->execute();

  _is_active = true;
}

void MassHealCommand::undo() {
  if (!_is_active) return;

  for (auto it : _info) it->undo();

  _is_active = false;
}
}  // namespace pf2e_manager
