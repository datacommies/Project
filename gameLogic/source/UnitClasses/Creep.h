class Creep: public MobileUnit{
public:
    Creep(const int& teamID, const int& hp, const int& xPos, const int& yPos, const int& lane, const int& type);

    int getLane();

    int getType();

    void setLane(const int& lane);
    
    void setType(const int& type);

    virtual void Run();
private:
    int lane_;
    int type_;
    //others?
}