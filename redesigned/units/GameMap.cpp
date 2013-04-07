#include "../resource.h"
#include "Point.h"

class GameMap{
public:
    Point castle1; //position for team 0's castle
    Point castle2; //position for team 0's castle
    PATH topOne, midOne, botOne; //paths for team 0's creeps
    PATH topTwo, midTwo, botTwo; //paths for team 1's creeps
    Point team0start[4]; //starting positions for team 0's players
    Point team1start[4]; //starting positions for team 1's players
    //add the 2d array
    

    //initializes castle positions and paths for each team
    //these still need to be assigned to a team object somehow
    //should probably be changed to use the MAPWIDTH/MAPHEIGHT defines
    //do we want default player spawn positions?
    void initMap(){
        //team 1 castle position, top left corner
        castle1.x = 0;
        castle1.y = 0;

        //team 2 castle position, bottom right corner
        castle2.x = 500;
        castle2.y = 500;

        //*** team 1 paths ***
        Point a;

        a.x = 30; //castle icon is 25x25
        a.y = 0;
        topOne.push_back(a);
        a.x = 500;
        a.y = 0;
        topOne.push_back(a);
        a.x = 500;
        a.y = 470;
        topOne.push_back(a);

        a.x = 0;
        a.y = 30;
        botOne.push_back(a);
        a.x = 0;
        a.y = 500;
        botOne.push_back(a);
        a.x = 470;
        a.y = 500;
        botOne.push_back(a);

        a.x = 30;
        a.y = 30;
        midOne.push_back(a);
        a.x = 250;
        a.y = 250;
        midOne.push_back(a);
        a.x = 470;
        a.y = 470; 
        midOne.push_back(a);
        //*** end of team 1 paths ***


        //*** team 2 paths ***
        Point b;

        b.x = 500;
        b.y = 470;
        topTwo.push_back(b);
        b.x = 500;
        b.y = 0;
        topTwo.push_back(b);
        b.x = 30;
        b.y = 0;
        topTwo.push_back(b);

        b.x = 470;
        b.y = 500;
        botTwo.push_back(b);
        b.x = 0;
        b.y = 500;
        botTwo.push_back(b);
        b.x = 0;
        b.y = 30;
        botTwo.push_back(b);

        b.x = 470;
        b.y = 470;
        midTwo.push_back(b);
        b.x = 250;
        b.y = 250;
        midTwo.push_back(b);
        b.x = 30;
        b.y = 30;
        midTwo.push_back(b);
        //*** end of team 2 paths ***

        //*** team 1 player starting positions ***
        Point c;
        c.x = 10;
        c.y = 10;

        team0start[0] = c;

        c.x = 12;
        c.y = 10;

        team0start[1] = c;

        c.x = 14;
        c.y = 8;

        team0start[2] = c;

        c.x = 16;
        c.y = 8;

        team0start[3] = c;
        //*** end of team 1 starting positions ***

        //*** team 2 player starting positions ***
        c.x = 490;
        c.y = 490;

        team1start[0] = c;

        c.x = 480;
        c.y = 480;

        team1start[1] = c;

        c.x = 480;
        c.y = 490;

        team1start[2] = c;

        c.x = 490;
        c.y = 480;

        team1start[3] = c;
        //*** end of team 2 starting positions ***
    }   
private:
};
