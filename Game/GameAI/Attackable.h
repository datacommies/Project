#ifndef ATTACKABLE_H
#define ATTACKABLE_H

#include "Point.h"
#include "Elements.h"
#include <string>
#include <iostream>

class Attackable {
	public:
		Attackable() {}
		Attackable( const Attackable& a )
			: iHp(a.iHp), pCurrPoint( a.pCurrPoint ), iElement( a.iElement ), iTeam( a.iTeam ), name( a.name ) {}
		Point			getPos() { return pCurrPoint; }
		void			setTeam( int t ) { iTeam = t; }
		virtual void	Update() { }
		
		int		iHp;
		Point		pCurrPoint;
		int		iElement;
		int		iTeam;
		std::string	name;
};

class Castle : public Attackable {
	public:
		Castle() {
			iHp = 8000;
			iElement = ELEMENT_STONE;
			name = "Castle";
		}
};

#endif
