#ifndef _EFFECT_EXECUTOR_H_5A2CD4D1_34D7_4D4E_9719_4366951EB28D_
#define _EFFECT_EXECUTOR_H_5A2CD4D1_34D7_4D4E_9719_4366951EB28D_

#include <functional>

#include "EffectBase.h"
#include "MediatorInterface.h"

#if defined(_BOOST_SERIALIZATION_TXT_) || defined(_BOOST_SERIALIZATION_XML_)

#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std {
using ::remove;
}
#endif

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
#include <boost/exception/all.hpp>
#include <boost/serialization/access.hpp>
#include <cstdio>  // remove
#include <fstream>
// #include <boost/serialization/nvp.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/throw_exception.hpp>
#include <boost/serialization/utility.hpp>
#endif

namespace pf2e_manager {
class EffectExecutor {
 public:
#if defined(_BOOST_SERIALIZATION_TXT_) || defined(_BOOST_SERIALIZATION_XML_)
  friend std::ostream& operator<<(std::ostream& os,
                                  const pf2e_manager::EffectBase* instance);

  friend class ::boost::serialization::access;
  template <class Archive>
  void serialize(Archive& ar, const unsigned int version);

#endif
  EffectExecutor() = default;
  EffectExecutor(MediatorInterface* mediator) : _mediator(mediator) {}

  ~EffectExecutor() = default;

  void doNothing() const { ; }

  void execute(SubjectBase* sender, SubjectBase* reciever,
               const std::vector<std::string>& name);

  void createEffect(SubjectBase* sender, SubjectBase* reciever,
                    const std::string& name, const int duration = 0,
                    const int value = 0) {
    _mediator->makeEffect(sender, reciever, name, duration, value);
  }

  void createCommand() { ; }

 private:
  MediatorInterface* _mediator;
};
}  // namespace pf2e_manager

#endif
