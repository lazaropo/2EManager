#ifndef _HEAL_COMMAND_H_BFB637A6_33DB_4A0F_A6B4_DBAF10B671A4_
#define _HEAL_COMMAND_H_BFB637A6_33DB_4A0F_A6B4_DBAF10B671A4_

#include "../CommandBase.h"
#include "../Combatant.h"

namespace pf2e_manager {
    class HealCommand : public CommandBase {
        public:
        HealCommand()
                : CommandBase(this) {}

        void execute(int value) override {
            if(value < 0 || _is_active) return;

            Combatant* combatant = dynamic_cast<Combatant*>(this->getObject());
            if (!combatant)
                throw std::runtime_error(
                    "HealCommand - execute func: reciever is not Combatant class.");

            if(combatant->getHPCurr() < combatant->getHPMax()) {
                combatant->setHPCurr(value + combatant->getHPCurr());

                if(combatant->getHPCurr() > combatant->getHPMax())
                    combatant->setHPCurr(combatant->getHPMax());
            }

            _is_active = true;
        }

        void undo() override {
            if(!_is_active) return;

            Combatant* combatant = dynamic_cast<Combatant*>(getObject());
            if (!combatant)
                throw std::runtime_error(
                    "HealCommand - execute func: reciever is not Combatant class.");

            if(combatant->getHPCurr() > 0) {
                combatant->setHPCurr(combatant->getHPCurr() - _value);
                
                if(combatant->getHPCurr() < 0)
                    combatant->setHPCurr(0);
            }
            _is_active = false;
        }
    };
}

#endif
