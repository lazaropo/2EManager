#include "TXTReader.h"

namespace pf2e_manager {
std::vector<Combatant*>* TXTReader::readCombatants(const std::string& path)
{
#ifdef __APPLE__
  setlocale(LC_ALL, "en_US.UTF-8");
#else
  std::setlocale(LC_ALL, "en_US.UTF-8");
#endif

  if (!isCorrectName(path)) return nullptr;

  std::ifstream file(path);
  if (file.is_open()) {
      _ret_vector = new std::vector<Combatant*>();

      std::string buff;

      file >> std::ws; // multispace delete

      while (getline(file, buff))
          stringProcessing(buff);

      return _ret_vector;

  } else
    return nullptr;
}

void TXTReader::writeCombatants(const std::string& path, std::vector<Combatant*>* collection)
{
    if (!isCorrectName(path))
        return;

    std::fstream file(path, std::ios::in | std::ios::out | std::ios::trunc);

    if (!file.is_open())
        return;

    for (auto it : *collection) {
        file << "combatant:"
             << "name:" << it->getName() << '/' << "hpmax:" << std::to_string(it->getHPMax()) << '/'
             << "initiative:" << std::to_string(it->getInitiative()) << '/'
             << "side:" << Combatant::formattingSide(it->getSide(), false, false) << '/'
             << "vitality:" << Combatant::formattingVitality(it->getVitality(), false, false) << '/'
             << std::endl;
    }

    for (auto it : *collection) {
        for (auto eff : it->getEffects()) {
            if (eff && eff->isActive() && !(dynamic_cast<EffectBase*>(eff->getInvoker())))
                file << eff->getName() /*starts with "effect:"*/ << '/'
                     << "invoker:" << (eff->getInvoker() ? eff->getInvoker()->getName() : "<user>")
                     << '/' << "reciever:" << it->getName() << '/'
                     << "duration:" << eff->getDuration() << '/' << "value:" << eff->getValue()
                     << '/' << std::endl;
        }
    }
}

bool TXTReader::isCorrectName(const std::string& name) {
  std::string extention = ".txt";

  auto ind_first_match = name.find(extention);
  auto ind_last_match = name.rfind(extention);

  if (ind_first_match != ind_last_match || ind_last_match + 4 < name.size())
    return false;

  return true;
}

void TXTReader::setCombatant(const std::string& buff) {
  // 10 chars are "combatant:" without \0
  std::string name;
  int hp_max;
  int initiative;
  // side and vitality values haven't be used as default. In any case of
  // incorrect input the exception show up.
  Combatant::Side side = Combatant::Side::OTHER;
  Combatant::Vitality vitality = Combatant::Vitality::CONSTRUCT;

  std::string::size_type first, last, count = 0;

  first = buff.find("name:", 10);
  if (first != std::string::npos) last = buff.find('/', first);
  if (first != std::string::npos && last != std::string::npos)
    name = std::string(buff.begin() + first + 5 /*chars in name: string*/,
                       buff.begin() + last);
  if (name.empty()) return;

  first = buff.find("hpmax:", last + 1);
  if (first != std::string::npos) last = buff.find('/', first);
  if (first != std::string::npos && last != std::string::npos)
    hp_max = std::stoi(std::string(buff.begin() + first +
                                       6 /* count of chars in hpmax: string*/,
                                   buff.begin() + last),
                       &count);
  if (first + 6 + count != last) return;

  first = buff.find("initiative:", last + 1);
  if (first != std::string::npos) last = buff.find('/', first);
  if (first != std::string::npos && last != std::string::npos)
    initiative =
        std::stoi(std::string(buff.begin() + first +
                                  11 /*count of chars in initiative: string*/,
                              buff.begin() + last),
                  &count);
  if (first + 11 + count != last) return;

  first = buff.find("side:", last + 1);
  if (first != std::string::npos) last = buff.find('/', first);
  if (first != std::string::npos && last != std::string::npos)
    side = Combatant::formattingSide(
        std::string(buff.begin() + first + 5 /*count of chars in side: string*/,
                    buff.begin() + last /*substr without '/' char*/));

  first = buff.find("vitality:", last + 1);
  if (first != std::string::npos) last = buff.find('/', first);
  if (first != std::string::npos && last != std::string::npos)
    vitality = Combatant::formattingVitality(std::string(
        buff.begin() + first + 9 /*count of chars in vitality: string*/,
        buff.begin() + last /*substr without '/' char*/));

  _ret_vector->push_back(new Combatant(hp_max, initiative, side, name, vitality));
}

void TXTReader::setEffect(const std::string& buff) {
  size_t first = 0;
  size_t last = 0;
  size_t count = 0;

  std::string name;
  std::string invoker;
  std::string reciever;
  // int is_active = 0;
  int duration = 0;
  int value = 0;

  first = buff.find("effect:");
  if (first != std::string::npos) last = buff.find('/', first);
  if (first != std::string::npos && last != std::string::npos)
    name = std::string(buff.begin() + first, buff.begin() + last);

  first = buff.find("invoker:");
  if (first != std::string::npos) last = buff.find('/', first);
  if (first != std::string::npos && last != std::string::npos)
    invoker = std::string(buff.begin() + first + 8, buff.begin() + last);

  first = buff.find("reciever:");
  if (first != std::string::npos) last = buff.find('/', first);
  if (first != std::string::npos && last != std::string::npos)
    reciever = std::string(buff.begin() + first + 9, buff.begin() + last);

  //  first = buff.find("is_active:", last + 1);
  //  if (first != std::string::npos) last = buff.find('/', first);
  //  if (first != std::string::npos && last != std::string::npos)
  //    duration = std::stoi(std::string(buff.begin() + first, buff.begin() +
  //    last),
  //                         &count);

  first = buff.find("duration:", last + 1);
  if (first != std::string::npos) last = buff.find('/', first);
  if (first != std::string::npos && last != std::string::npos)
    duration = std::stoi(
        std::string(buff.begin() + first + 9, buff.begin() + last), &count);

  first = buff.find("value:", last + 1);
  if (first != std::string::npos) last = buff.find('/', first);
  if (first != std::string::npos && last != std::string::npos)
    value = std::stoi(
        std::string(buff.begin() + first + 6, buff.begin() + last), &count);

  _director->buildEffectByName(name, duration, value);

  auto from = std::find_if(_ret_vector->begin(), _ret_vector->end(), [&](Combatant* body) {
      return body->getName() == invoker;
  });
  if (from == _ret_vector->end())
      _builder->setInvoker(nullptr);
  else
    _builder->setInvoker(*from);

  auto to = std::find_if(_ret_vector->begin(), _ret_vector->end(), [&](Combatant* body) {
      return body->getName() == reciever;
  });
  if (to == _ret_vector->end())
      throw std::logic_error("TXTReader: setEffect(): reciever is not found.");
  else
    _builder->setReciever(*to);

  auto combatant = dynamic_cast<Combatant*>(*to);
  if (!*to)
    _builder->reset();
  else
    combatant->addEffect(_builder->getSimpleEffect());
}

void TXTReader::stringProcessing(const std::string& buff) {
  if (buff.find("combatant:") == 0)
    setCombatant(buff);
  else if (buff.find("effect:") == 0)
    setEffect(buff);
}
}  // namespace pf2e_manager
