#include "ControlManager.h"
using namespace std;

ControlManager::ControlManager()
{
	
}

void ControlManager::AddNewState(ControlState state)
{
	StateCollection.push_back(state);
}

int ControlManager::CheckState()
{
	if(ControlState.CheckControllers() > 0)
	{
		for(vector<ControlState>::size_type i = 0; i < StateCollection.size(); i++)
		{
			if(ControlState.getIdentifier() == StateCollection[i].getIdentifier())
			{
				SetNewActiveState(StateCollection[i]);
			}
		}	
	}
	return 0;
}

void ControlManager::SetNewActiveState(ControlState * state)
{
	if(state.getOverride() || !activeState.getOverride())
	{
		activeState.UnloadGUIs();
	}
	
}
