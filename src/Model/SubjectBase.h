#ifndef _SUBJECT_BASE_H_791C1EED_FB8B_499A_BA92_7A2D81BE58C0
#define _SUBJECT_BASE_H_791C1EED_FB8B_499A_BA92_7A2D81BE58C0

#include <iostream>
#include <string>

#if defined (_BOOST_SERIALIZATION_TXT_)  || defined (_BOOST_SERIALIZATION_XML_)

#ifdef _BOOST_SERIALIZATION_TXT_
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#endif

#ifdef _BOOST_SERIALIZATION_XML_
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#endif

#include <boost/config.hpp>
#include <boost/archive/tmpdir.hpp>

#include <boost/serialization/utility.hpp>

#include <boost/serialization/access.hpp>
#include <boost/serialization/export.hpp>

#include <boost/serialization/string.hpp>
#endif

namespace pf2e_manager {
class SubjectBase {
#if defined (_BOOST_SERIALIZATION_TXT_)  || defined (_BOOST_SERIALIZATION_XML_)
    friend std::ostream& operator<<(std::ostream& os, const SubjectBase* instance);

    friend class ::boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version);
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
#ifdef _BOOST_SERIALIZATION_XML_
inline std::ostream& operator<<(std::ostream& os, const pf2e_manager::SubjectBase* instance)
{
    if (!instance)
        return os;

    os << instance->_name << ' ' << instance->_reciever << ' ' << instance->_invoker << std::endl;

    return os;
}

#endif
} // namespace pf2e_manager

#if defined (_BOOST_SERIALIZATION_TXT_)  || defined (_BOOST_SERIALIZATION_XML_)
BOOST_CLASS_EXPORT_KEY(::pf2e_manager::SubjectBase);
#endif
#endif
