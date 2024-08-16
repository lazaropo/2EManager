#ifndef _TXT_READER_342C4570_5625_11EF_A550_0800200C9A66_
#define _TXT_READER_342C4570_5625_11EF_A550_0800200C9A66_

#include "EffectDirector.h"
#include "FileReaderBase.h"

namespace pf2e_manager {
class TXTReader : public FileReaderBase {
 public:
  TXTReader(MediatorInterface* mediator)
      : _builder(new SimpleEffectBuilder(mediator)),
        _director(new EffectDirector(_builder)) {}
  ~TXTReader() {
    delete _builder;
    delete _director;
  }

  std::list<Combatant*>* readCombatants(const std::string& path);
  void writeCombatants(const std::string& path,
                       std::list<Combatant*>* collection);

 private:
  bool isCorrectName(const std::string& name);
  void setCombatant(const std::string& buff);
  void setEffect(const std::string& buff);
  void stringProcessing(const std::string& buff);

 private:
  std::list<Combatant*>* _ret_list = nullptr;
  SimpleEffectBuilder* _builder;
  EffectDirector* _director;
};
}  // namespace pf2e_manager

#endif
