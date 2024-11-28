#ifndef _MASSHARMCOMMAND_H_F65E13E0_5E2B_11EF_A550_0800200C9A66_
#define _MASSHARMCOMMAND_H_F65E13E0_5E2B_11EF_A550_0800200C9A66_

#include <utility>

#include "HarmCommand.h"

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
#include <boost/serialization/vector.hpp>
#endif

namespace pf2e_manager {
class MassHarmCommand : public CommandBase {
#if defined(_BOOST_SERIALIZATION_TXT_) || defined(_BOOST_SERIALIZATION_XML_)
  friend class ::boost::serialization::access;
  template <class Archive>
  void serialize(Archive &ar, const unsigned int version);

  MassHarmCommand() {}
#endif
 public:
  MassHarmCommand(MediatorInterface *mediator, SubjectBase *sender,
                  const std::vector<std::pair<SubjectBase *, int>> &info);

  /**
   * @brief Do from do/undo. _is_active == true accords currect exertion of
   * this effect. So, if it's true the damage is  caused. If not (command
   * was undone) the damage is saved, but doesn't caused rigth now.
   *
   * @param value damage value
   */
  void execute() override;

  void undo() override;

  const std::vector<HarmCommand *> &getInfo() const { return _info; }

 private:
  MediatorInterface *_mediator;
  std::vector<HarmCommand *> _info;
};
}  // namespace pf2e_manager

#if defined(_BOOST_SERIALIZATION_TXT_) || defined(_BOOST_SERIALIZATION_XML_)
BOOST_CLASS_EXPORT_KEY(::pf2e_manager::MassHarmCommand)
#endif

#endif  // MASSHARMCOMMAND_H
