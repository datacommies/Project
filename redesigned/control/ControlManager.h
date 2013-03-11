#ifndef CONTROL_MANAGER_H
#define CONTROL_MANAGER_H

#include "ControlPlaceHolder.h"
#include "ControlState.h"
#include "resource.h"
#include <vector>

class ControlManager {

    public:    
        ControlManager();
        
        void AddNewState(ControlState state);
        int CheckState();
        void SetNewActiveState(ControlState state);
        
    private:
        std::vector<ControlState> StateCollection;
        ControlState * activeState;
};

#endif

