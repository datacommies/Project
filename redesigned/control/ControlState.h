#ifndef CONTROL_STATE_H
#define CONTROL_STATE_H

/*--------------------------------------------------------------------------------------------------------------------
-- CLASS: ControlState
--
-- FUNCTIONS: ControlState()
--            void LoadGUIs()
--            void UnloadGUIs()
--            void AddController()
--            int CheckControllers()
--            bool getOverride()
--            int getIndentifier()
--
--
-- DATE: 2013/03/11
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- NOTES: Class is intended to represent a control state. It holds a collection of Controllers, checks if they hace been
--        activated, and is held by a ControlManager.
-- 
----------------------------------------------------------------------------------------------------------------------*/

#include "ControlPlaceHolder.h"
#include "Controller.h"
#include <vector>

class ControlState
{
public:
	ControlState(bool override, int identifier);
	
	void LoadGUIs();
	void UnloadGUIs();

	void AddController(Controller control);
	
	int CheckControllers();

	bool getOverride();
	bool getIdentifier();

private:
	bool _Override;
	int _Identifier;

	std::vector<Controller> Controllers;
};

#endif

