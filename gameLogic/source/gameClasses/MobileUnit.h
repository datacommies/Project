#include "Unit.h"

class MobileUnit: public Unit{
public:
    MobileUnit(const int& teamID, const int& hp, const int& xPos, const int& yPos):
     Unit(teamID, hp, xPos, yPos){
        //init things???
    }

    /**
     * getters and setters
     */
    int getMvSpeed(){
        return moveSpeed_;
    }

    int getDirect(){
        return direction_;
    }

    int getAtkSpeed(){
        return attackSpeed_;
    }

    int getAtkDmg(){
        return attackDmg_;
    }

    void setMvSpeed(const int& speed){
        moveSpeed_ = speed;
    }

    void setDirect(const int& direction){
        direction_ = direction;
    }

    void setAtkSpeed(const int& atkSpeed){
        attackSpeed_ = atkSpeed;
    }

    void setAtkDmg(const int& atkDmg){
        attackDmg_ = atkDmg;
    }


    //other functions
    virtual void Move(){
        //check move speed and direction
        //move in direction at move speed amount for the 
        //current loop iteration
    }

    virtual void Attack(){
        //FOR A CREEP
        //call AI function

        //FOR A PLAYER
        //attacks only happen when your unit collides with an enemy unit
        //ie: you walk into that unit, and keeps pressing the move button in that direction
        //check direction and attack dmg
        //damage the unit you've collided with base on attack dmg
    }


private:
    int moveSpeed_;
    int direction_;
    //any other attack related?
    int attackSpeed_;
    int attackDmg_;
    //int aggroRadius_;
    //int defense_;
};