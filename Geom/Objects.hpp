#ifndef OBJECTS_HPP
#define OBJECTS_HPP
#include <iostream>
#include <cmath>
#include <vector>
using namespace std; 
class Point;            //Точка
class Segment;       //Отрезок   
class Straight;        //Прямая
class Polygon;        //Многоугольник

class Object{
public:
   virtual void move(double dx,double dy)=0;
   virtual void rotate(double angle)=0;
};
class Point : public Object{
   double x,y;
   friend Polygon;
   friend Segment;
   friend double distance(Point p1, Point p2);
   friend double distance(Point p, Segment l);
   friend double distance(Point p, Straight l);
   friend double distance(Point p, Polygon poly);
public:
   Point(){}
   Point(double x, double y) : x(x),y(y) {}
   void move(double dx, double dy){ x+=dx; y+=dy; }
   void rotate(double angle){
      double r = sqrt(x*x+y*y);
      x = r*cos(angle*acos(-1)/180);
      y = r*sin(angle*acos(-1)/180);
   }
};
class Straight : public Object{
protected:
   int x1,y1,x2,y2;
   friend double distance(Straight l1, Straight l2);
   friend double distance(Straight l, Polygon poly);
   friend double distance(Point p, Straight l);
   friend double distance(Segment l1, Straight l2);
   
   friend Point intersection(Segment l1, Straight l2);
   friend Point intersection(Straight l1, Straight l2);
public:
   Straight(){}
   Straight(double x1, double y1, double x2, double y2):x1(x1),y1(y1),x2(x2),y2(y2) { }
   void move(double dx, double dy){ x1+=dx; x2+=dx; y1+=dy; y2+=dy; }
   void rotate(double angle){
      double r;
      r = sqrt(x1*x1+y1*y1);
      x1 = r*cos(angle*acos(-1)/180);
      y1 = r*sin(angle*acos(-1)/180);
      
      r = sqrt(x2*x2+y2*y2);
      x2 = r*cos(angle*acos(-1)/180);
      y2 = r*sin(angle*acos(-1)/180);
   }
   
};
class Segment : public Straight{
   friend Polygon;
   friend double distance(Segment l1, Segment l2);
   friend double distance(Segment l, Polygon poly);
   friend double distance(Point p, Segment l);
   friend double distance(Point p, Polygon poly);
   friend double distance(Segment l1, Straight l2);
   
   friend Point intersection(Segment l1, Segment l2);
   friend Point intersection(Segment l1, Straight l2);
   friend Segment intersection(Segment l, Polygon poly);
public:
   Segment(){}
   Segment(Point p1, Point p2) : Straight(p1.x,p1.y,p2.x,p2.y){}
   Segment(double x1, double y1, double x2, double y2) : Straight(x1,y1,x2,y2){ }
   double length() {
      return distance(Point(x1,y1),Point(x2,y2));
   }
   
};

class Polygon : public Object{
   vector<Segment> m;
   friend double distance(Point p, Polygon poly);
   friend double distance(Segment l, Polygon poly);
   friend double distance(Straight l, Polygon poly);
   friend double distance(Polygon poly1, Polygon poly2);
   
   friend Segment intersection(Segment l, Polygon poly);
   friend Segment intersection(Straight l, Polygon poly);
public:
   Polygon(){}
   Polygon(double *x, double *y,int num){
      for(int i = 0; i < num; i++)
         m.push_back(Segment(x[i],y[i],x[(i+1)%num],y[(i+1)%num]));
   }
   Polygon(vector<Segment> _m){
      m.clear();
      m = _m;
   }
   void move(double dx, double dy) {
      for(int i = 0; i < m.size(); i++)
         m[i].move(dx,dy);
   }
   void rotate(double angle) {
      double r;
      for(int i = 0; i < m.size(); i++)
         m[i].rotate(angle);
   }
   double area() {
      double sum = 0, x1,y1,x2,y2;
      x1 = m[m.size()-1].x1;
      y1 = m[m.size()-1].y1;
      for(int i = 0; i < m.size(); i++) { 
         x2 = m[i].x1;
         y2 = m[i].y1;
         sum+=(x1+x2)*(y2-y1); 
         x1=x2; 
         y1=y2; 
      } 
      return fabs(sum)/2;
   }
   double perimeter() {
      double p = 0;
      for(int i = 0; i < m.size(); i++)
         p+=m[i].length();
      return p;
   }
}; 
class IntersectionError{};

//distance Point
double distance(Point p1, Point p2);
double distance(Point p, Segment l);
double distance(Point p, Straight l);
double distance(Point p, Polygon poly);
//distance Segment
double distance(Segment l1, Segment l2);
double distance(Segment l1, Straight l2);
double distance(Segment l, Polygon poly);
double distance(Segment l, Point p);
//distance Straight
double distance(Straight l1, Straight l2);
double distance(Straight l, Polygon poly);
double distance(Straight l, Point p);
double distance(Straight l2, Segment l1);
//distance Polygon
double distance(Polygon poly1, Polygon poly2);
double distance(Polygon poly, Point p);
double distance(Polygon poly, Segment l);
double distance(Polygon poly, Straight l);

//intersection = Point
Point intersection(Segment l1, Segment l2);
Point intersection(Segment l1, Straight l2);
Point intersection(Straight l2, Segment l1);
//intersection = Segment
Segment intersection(Segment l, Polygon poly);
Segment intersection(Straight l, Polygon poly);
Segment intersection(Polygon poly,Segment l);
Segment intersection(Polygon poly,Straight l);
#endif