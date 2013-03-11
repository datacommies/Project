#ifndef CREEP_H
#define CREEP_H

#include "../resource.h"
#include "../types.h"
//#include "unit.h"
#include "mobile_unit.h"

class Creep : public MobileUnit
{
public: 
<<<<<<< HEAD
   void spawn(const int& num);  //also creep type? when we have a type
   std::string serializeCreep(const Creep& creep);

	virtual UnitTypes getType() const { return TYPE_CREEP; }
	virtual size_t getSize() const { return sizeof(Creep); }
=======
   	void spawn(const int& num);  //also creep type? when we have a type
   	void serializeCreep(const Creep& creep);
   
	Creep(): pPath( 0 ), pSaved( 0 ), moveSpeed( 0 ){}

	Creep( const Creep& );
	void	Update( void );
	void	setSpeed( int newSpeed) { moveSpeed = newSpeed; }
	void	setPath( Point *pt )	{ pPath = pt; }
	void	nextPoint( void )	{ pPath++; }
	void	savePoint( Point &pt )	{ pSaved = &pt; }
	void	Move( Point );
	int	getDirection( int, int );

	Point	*	pPath;
	Point	*	pSaved;
	int      	moveSpeed;   //the speed which a unit can move. ex. (it can move 1 square per 30 frames)
>>>>>>> 932982e50d58aea124570f9f5ed67c2de6f9db03

private:
};

#endif
