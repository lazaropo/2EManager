#include "utility.h"

#ifdef _BOOST_SERIALIZATION_XML_
// template <class Archive>
// void pf2e_manager::serialize(Archive& ar, utility::t_cobatant_container& g,
//                              const unsigned int version) {
//   for (auto it : g) ar& BOOST_SERIALIZATION_NVP(it);
// }

// template <class Archive>
// void serialize(Archive& ar,
//                boost::container::stable_vector<::pf2e_manager::EffectBase*>&
//                g, const unsigned int version) {
//   for (auto it = g.begin(), it_end = g.end(); it != it_end; ++it)
//     ar& BOOST_SERIALIZATION_NVP(*it);
//   // for (auto it : g) ar& BOOST_SERIALIZATION_NVP(it);
// }
namespace boost {
namespace serialization {
template <class Archive>
void save(Archive& ar, pf2e_manager::utility::t_cobatant_container& g,
          const unsigned int version) {
  for (auto it = g.begin(), it_end = g.end(); it != it_end; ++it)
    ar& BOOST_SERIALIZATION_NVP(it);
}

template <class Archive>
void load(Archive& ar, pf2e_manager::utility::t_cobatant_container& g,
          const unsigned int version) {
  for (auto it = g.begin(), it_end = g.end(); it != it_end; ++it)
    ar& BOOST_SERIALIZATION_NVP(it);
  // for (auto it : g) ar& BOOST_SERIALIZATION_NVP(it);
}

template void save<boost::archive::xml_oarchive>(
    boost::archive::xml_oarchive& ar,
    pf2e_manager::utility::t_cobatant_container& g, const unsigned int version);
template void load<boost::archive::xml_iarchive>(
    boost::archive::xml_iarchive& ar,
    pf2e_manager::utility::t_cobatant_container& g, const unsigned int version);
}  // namespace serialization
}  // namespace boost
#endif
