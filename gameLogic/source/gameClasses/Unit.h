

//base unit classes, all concrete unit types will inherit from this in some way
class Unit{
public:
    Unit(const int& teamID, const int& hp, const int& xPos, const int& yPos):
     teamID_(teamID), healthPoints_(hp), xPos_(xPos), yPos_(yPos) {
        //call function to generate unit id
        //unitID_ = generated id
        //need a mutex??

        //set HP based on unit type, or maybe not
        //should hp stuff even be in here?
        //hp = unit hp type
        
        //validation

        //check that unit id is unique
        //check that teamID is correct(1 of the 2 teams)
        //check that hp is > 0
        //x/y?

    }

    /*********************
     * getters and setters
     *********************/
    int getID(){
        return unitID_;
    }

    int getTeam(){
        return teamID_;
    }

    int getHP(){
        return healthPoints_;
    }

    int getX(){
        return xPos_;
    }

    int getY(){
        return yPos_;
    }

    //some setters may not be needed, some may require validation
    void setID(const int& id){
        unitID_ = id;
    }

    void setTeam(const int& team){
        teamID_ = team;
    }

    void setHP(const int& hp){
        healthPoints_ = hp;
    }

    void setX(const int& x){
        xPos_ = x;
    }

    void setY(const int& y){
        yPos_ = y;
    }

    //other useful functions
    void setPos(int x, int y){
        xPos_ = x;
        yPos_ = y;
    }

    bool isDead(){
        if(healthPoints_ == 0){
            return true;
        }
        return false;
    }

    void addHP(const int& add){
        healthPoints_ += add;
    }

    //virtual because attacks might be mitigated by armour in other classes?
    virtual void subHP(const int& sub){
        healthPoints_ -= sub;
    }

    virtual void Run(){
        //every 1/30 of a second, use a timer to sync all units
        //check things like if there enemies to attack, am I moving?, etc.
        //overridden in concrete each class
    }

    //pure virtual function for displaying info about the class
    //makes the class abstract
    virtual void display() const = 0;
private:
    int unitID_;//unique ID for the unit
    int teamID_;//ID of the team that the unit is associated with
    int healthPoints_;//health points of the unit
    int xPos_;//x position of the unit
    int yPos_;//y position of the unit
};