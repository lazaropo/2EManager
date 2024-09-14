#ifndef _SUBJECT_BASE_H_791C1EED_FB8B_499A_BA92_7A2D81BE58C0
#define _SUBJECT_BASE_H_791C1EED_FB8B_499A_BA92_7A2D81BE58C0

// #include <iostream>
#include <string>

#ifdef _USE_BOOST_SERIALIZE_
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/assume_abstract.hpp>
#endif

namespace pf2e_manager {
class SubjectBase {
 public:
    SubjectBase() {};
  SubjectBase(SubjectBase* subject, SubjectBase* reciever = nullptr)
      : _subject(subject), _reciever(reciever) {}

  virtual ~SubjectBase() = default;

  const std::string getName() const { return _name; }
  SubjectBase* getSubject() const { return _subject; }
  SubjectBase* getReciever() const { return _reciever; }
  SubjectBase* getInvoker() const { return _invoker; }

  void setName(const std::string name) { _name = name; }
  void setReciever(SubjectBase* reciever) { _reciever = reciever; }
  void setInvoker(SubjectBase* invoker) { _invoker = invoker; }

#ifdef _USE_BOOST_SERIALIZE_
  friend class boost::serialization::access;

  private:
  template <class Archive>
  void serialize(Archive & ar, const size_t version) {
      ar & BOOST_SERIALIZATION_NVP(_name);
      ar & BOOST_SERIALIZATION_NVP(_subject);
      ar & BOOST_SERIALIZATION_NVP(_reciever);
      ar & BOOST_SERIALIZATION_NVP(_invoker);
  }
#endif

 protected:
  std::string _name = "";
  SubjectBase* _subject = nullptr;   // this
  SubjectBase* _reciever = nullptr;  // direction of exertion
  SubjectBase* _invoker = nullptr;   // exertion from whom
};
}  // namespace pf2e_manager
#ifdef _USE_BOOST_SERIALIZE_
BOOST_SERIALIZATION_ASSUME_ABSTRACT(pf2e_manager::SubjectBase)
#endif
;
#endif
