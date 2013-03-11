#ifndef CONTROL_MANAGER_H
#define CONTROL_MANAGER_H

/*--------------------------------------------------------------------------------------------------------------------
-- CLASS: ControlManager
--
-- FUNCTIONS: ControlManager()
--            void AddNewState(ControlState state)
--            int CheckState()
--            void SetNewActiveState(ControlState * state)
--         
-- DATE: 2013/03/11
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Luke Tao
--
-- PROGRAMMER: Luke Tao
--
-- NOTES: Class is loaded when the program starts. It holds a collection of ControlStates, which is filled on the
--        start of the program. This class will add, check or set a new active control state.
-- 
----------------------------------------------------------------------------------------------------------------------*/

#include "ControlState.h"
#include "resource.h"
#include <vector>

class ControlManager {

    public:    
        ControlManager();
        
        void AddNewState(ControlState state);
        int CheckState();
        void SetNewActiveState(ControlState * state);
        
    private:
        std::vector<ControlState> StateCollection;
        ControlState * activeState;
};

#endif

