#ifndef _SUBJECT_BASE_H_791C1EED_FB8B_499A_BA92_7A2D81BE58C0
#define _SUBJECT_BASE_H_791C1EED_FB8B_499A_BA92_7A2D81BE58C0

#include <iostream>
#include <string>

namespace pf2e_manager {
class SubjectBase {
 public:
  SubjectBase() = delete;
  SubjectBase(SubjectBase* subject, SubjectBase* object = nullptr)
      : _subject(subject), _object(object) {}

  virtual ~SubjectBase() = default;

  const std::string getName() const {
    std::cout << _name << std::endl;
    return _name;
  }
  SubjectBase* getSubject() const { return _subject; }
  SubjectBase* getObject() const { return _object; }
  SubjectBase* getCreator() const { return _creator; }

  void setName(const std::string name) { _name = name; }
  void setObject(SubjectBase* object) { _object = object; }
  void setCreator(SubjectBase* creator) { _creator = creator; }

 protected:
  std::string _name = "";
  SubjectBase* _subject = nullptr;  // this
  SubjectBase* _object = nullptr;   // direction of exertion
  SubjectBase* _creator = nullptr;  // exertion from whom
};
}  // namespace pf2e_manager

#endif
