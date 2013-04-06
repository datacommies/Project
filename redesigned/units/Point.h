#ifndef POINT_H
#define POINT_H

class Point {
  public:
    Point()
    {
	x = 0;
	y = 0;
    }

    Point(int xLoc, int yLoc)
    {
	x = xLoc;
	y = yLoc;
    }

    Point& operator=(const Point& rhs)
    {
	x = rhs.x;
	y = rhs.y;

	return *this;
    }

    int x;
    int y;

  /*Point(double xp = 0, double yp = 0){
    x = xp; 
    y = yp;
  }

  double getX()const;

  double getY()const;

  void setX(const double& xp);

  void setY(const double& yp);

  double distance(Point otherP){
    double xdis = (double)x - otherP.x;
    double ydis = (double)y - otherP.y;
    return sqrt(xdis*xdis + ydis*ydis);
  }

  void move(double a, double b){
    (double)x += a;
    (double)y += b;
  }*/

  		
};

#endif
