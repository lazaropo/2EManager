#ifndef _HEAL_COMMAND_H_BFB637A6_33DB_4A0F_A6B4_DBAF10B671A4_
#define _HEAL_COMMAND_H_BFB637A6_33DB_4A0F_A6B4_DBAF10B671A4_

#include "../CommandBase.h"

namespace pf2e_manager {
    class HealCommand : public CommandBase {
        public:
        void execute(int value) override {
            if(value < 0 || _is_active) return;

            if(_combatant->getHPCurr() < _combatant->getHPMax()) {
                _combatant->setHPCurr(value + _combatant->getHPCurr());

                if(_combatant->getHPCurr() > _combatant->getHPMax())
                    _combatant->setHPCurr(_combatant->getHPMax());
            }

            _is_active = true;
        }

        void undo() override {
            if(!_is_active) return;

            if(_combatant->getHPCurr() > 0) {
                _combatant->setHPCurr(_combatant->getHPCurr() - _value);
                
                if(_combatant->getHPCurr() < 0)
                    _combatant->setHPCurr(0);
            }
            _is_active = false;
        }
    };
}

#endif