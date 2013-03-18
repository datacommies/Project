#ifndef BUILD_CONTROLLER_H
#define BUILD_CONTROLLER_H
/*--------------------------------------------------------------------------------------------------------------------
-- CLASS: BuildController
--
-- FUNCTIONS: 
--
-- DATE: 2013/03/14
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- NOTES: This class is extended from Controller and used for the purpose of getting coordinates when building a building
-- 
----------------------------------------------------------------------------------------------------------------------*/

#include "Controller.h"

class BuildController : public Controller
{
public:
	BuildController(int returnValue, sf::Keyboard::Key key, Button buttonRect, void (*move_fp)(void *));

protected:
	void RunCommand();
};

#endif