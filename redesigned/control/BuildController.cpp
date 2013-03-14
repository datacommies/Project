#include "BuildController.h"

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: RunCommand
--
-- DATE: 2013/03/14
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: 
--
-- INTERFACE: RunCommand()
--
-- RETURNS: N/A
--
-- NOTES: Polymorphic function used for giving coordinates to the event
----------------------------------------------------------------------------------------------------------------------*/
void 
Controller::RunCommand()
{
	int position[2];
	position[0] = 0; // X coordinate
	position[1] = 1; // Y coordinate
	
	eventFunction((void*)position);
}
