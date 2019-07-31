#include <iostream>
#include <cmath>
#include <vector>
#include "Objects.hpp"
using namespace std; 
int main()
{
   double x[] = {1,1,3,3};
   double y[] = {1,3,3,1};
   Polygon poly(x,y,4);
   cout << Segment(2,2,3,2).length() << endl;
   cout << distance(Point(0,0),intersection(poly,Straight(1,2,2,4)));
}