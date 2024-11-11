#ifndef _SUBJECT_BASE_H_791C1EED_FB8B_499A_BA92_7A2D81BE58C0
#define _SUBJECT_BASE_H_791C1EED_FB8B_499A_BA92_7A2D81BE58C0

#include <iostream>
#include <string>

#ifdef _BOOST_SERIALIZATION_XML_
#include <boost/config.hpp>

#include <boost/archive/tmpdir.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

#include <boost/serialization/string.hpp>
#endif

namespace pf2e_manager {
class SubjectBase {
#ifdef _BOOST_SERIALIZATION_XML_
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar & _name;
        ar & _subject;
        ar & _reciever;
        ar & _invoker;
    }
#endif
public:
    SubjectBase() {}
    SubjectBase(SubjectBase* subject, SubjectBase* reciever = nullptr)
        : _subject(subject)
        , _reciever(reciever)
    {}

    virtual ~SubjectBase() = default;

    const std::string getName() const { return _name; }
    SubjectBase* getSubject() const { return _subject; }
    SubjectBase* getReciever() const { return _reciever; }
    SubjectBase* getInvoker() const { return _invoker; }

    void setName(const std::string name) { _name = name; }
    void setReciever(SubjectBase* reciever) { _reciever = reciever; }
    void setInvoker(SubjectBase* invoker) { _invoker = invoker; }

protected:
    std::string _name = "";
    SubjectBase* _subject = nullptr;  // this
    SubjectBase* _reciever = nullptr; // direction of exertion
    SubjectBase* _invoker = nullptr;  // exertion from whom
};
}  // namespace pf2e_manager

#endif
