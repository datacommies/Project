

class MobileUnit: public Unit{
public:
    MobileUnit(const int& teamID, const int& hp, const int& xPos, const int& yPos):
     Unit(teamID, hp, xPos, yPos){
        //init things???
    }
private:
    int moveSpeed_;
    int direction_;
    //any other attack related?
    int attackSpeed_;
    int attackDmg_;
}