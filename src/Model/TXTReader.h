#ifndef _TXT_READER_342C4570_5625_11EF_A550_0800200C9A66_
#define _TXT_READER_342C4570_5625_11EF_A550_0800200C9A66_

#include "EffectDirector.h"
#include "FileReaderBase.h"

namespace pf2e_manager {
class TXTReader : public FileReaderBase {
 public:
  TXTReader() = default;
  ~TXTReader() {
    delete _builder;
    delete _director;
  }

  std::vector<Combatant*>* readCombatants(const std::string& path);
  void writeCombatants(const std::string& path,
                       std::vector<Combatant*>* collection);

 private:
  bool isCorrectName(const std::string& name);
  void setCombatant(const std::string& buff);
  void setEffect(const std::string& buff);
  void stringProcessing(const std::string& buff);

 private:
  std::vector<Combatant*>* _ret_list = nullptr;
  SimpleEffectBuilder* _builder = new SimpleEffectBuilder();
  EffectDirector* _director = new EffectDirector(_builder);
};
}  // namespace pf2e_manager

#endif
