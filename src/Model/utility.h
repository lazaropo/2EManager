#ifndef UTILITY_H
#define UTILITY_H

#include <boost/container/stable_vector.hpp>
#include <boost/serialization/vector.hpp>

#include "Combatant.h"

#ifdef _BOOST_SERIALIZATION_TXT_
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/split_member.hpp>
#endif

#ifdef _BOOST_SERIALIZATION_XML_
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_member.hpp>
#endif

namespace pf2e_manager {
class Combatant;

namespace utility {
using t_cobatant_container =
    ::boost::container::stable_vector<pf2e_manager::Combatant*>;
}
}  // namespace pf2e_manager

namespace boost {
namespace serialization {
template <class Archive>
inline void save(Archive& ar, pf2e_manager::utility::t_cobatant_container& g,
                 const unsigned int version);

template <class Archive>
inline void load(Archive& ar, pf2e_manager::utility::t_cobatant_container& g,
                 const unsigned int version);
}  // namespace serialization
}  // namespace boost
// #ifdef _BOOST_SERIALIZATION_XML_
// BOOST_CLASS_EXPORT_KEY(pf2e_manager::utility::t_cobatant_container);
// #endif

#endif  // UTILITY_H
