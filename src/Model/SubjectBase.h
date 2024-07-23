#ifndef _SUBJECT_BASE_H_791C1EED_FB8B_499A_BA92_7A2D81BE58C0
#define _SUBJECT_BASE_H_791C1EED_FB8B_499A_BA92_7A2D81BE58C0

namespace pf2e_manager {
class SubjectBase {
 public:
  SubjectBase(SubjectBase* subject, SubjectBase* object = nullptr)
      : _subject(subject), _object(object) {}

  SubjectBase* getSubject() const { return _subject; }
  SubjectBase* getObject() const { return _object; }
  void setObject(SubjectBase* object) { _object = object; }

 protected:
  SubjectBase* _subject;
  SubjectBase* _object;
};
}  // namespace pf2e_manager

#endif