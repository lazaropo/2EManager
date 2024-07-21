#ifndef _HEAL_COMMAND_H_BFB637A6_33DB_4A0F_A6B4_DBAF10B671A4_
#define _HEAL_COMMAND_H_BFB637A6_33DB_4A0F_A6B4_DBAF10B671A4_

#include "../CommandBase.h"

namespace pf2e_manager {
    class HealCommand : public CommandBase {
        public:
        void execute(int value) override {
            if(value < 0 || _is_active) return;

            if(_combatant->_hp_curr < _hp_max) {
                __hp_curr += value;
                if(_combatant->hp_curr > _hp_max)
                    _hp_curr = _hp_max;
            }

            _is_active = true;
        }

        void undo() override {
            if(!_is_active) return;

            if(_combatant)

            _is_active = false;
        }
    };
}

#endif