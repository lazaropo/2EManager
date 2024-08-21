#ifndef _SUBJECT_BASE_H_791C1EED_FB8B_499A_BA92_7A2D81BE58C0
#define _SUBJECT_BASE_H_791C1EED_FB8B_499A_BA92_7A2D81BE58C0

#include <iostream>
#include <string>

namespace pf2e_manager {
class SubjectBase {
 public:
  SubjectBase() = delete;
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

 protected:
  std::string _name = "";
  SubjectBase* _subject = nullptr;   // this
  SubjectBase* _reciever = nullptr;  // direction of exertion
  SubjectBase* _invoker = nullptr;   // exertion from whom
};
}  // namespace pf2e_manager

#endif
