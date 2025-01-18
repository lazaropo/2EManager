#ifndef _FILE_READER_BASE_H_716FC850_5623_11EF_A550_0800200C9A66_
#define _FILE_READER_BASE_H_716FC850_5623_11EF_A550_0800200C9A66_

#include <fstream>
#include <string>

#include "Combatant.h"
#include "Mediator.h"

namespace pf2e_manager {
class FileReaderBase {
 public:
  virtual ~FileReaderBase() = default;
  virtual std::vector<Combatant*>* readCombatants(const std::string& path) = 0;
  virtual void writeCombatants(const std::string& path,
                               std::vector<Combatant*>* list) = 0;
};
}  // namespace pf2e_manager

#endif
