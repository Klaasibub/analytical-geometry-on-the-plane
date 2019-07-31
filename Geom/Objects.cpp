#include <iostream>
#include <cmath>
#include <vector>
#include "Objects.hpp"
using namespace std; 

//distance Point
double distance(Point p1, Point p2){
   double x,y;
   x = p2.x - p1.x;
   y = p2.y - p1.y;
   return sqrt(x*x+y*y);
}
double distance(Point p, Segment l){
   double a = distance(p,Point(l.x1,l.y1));                     // расстояние до первого конца отрезка
   double b = distance(p,Point(l.x2,l.y2));                     // расстояние до второго конца отрезка
   double c = distance(Point(l.x1,l.y1),Point(l.x2,l.y2));   // длина отрезка
   
   if(a*a+c*c > b*b && b*b+c*c > a*a)                       //если можно провести перпендикуляр к отрезку
      return distance(p,Straight(l.x1,l.y1,l.x2,l.y2));      //возвращаем этот перпендикуляр
   //иначе наименьшее расстояние от точки до концов отрезка
   return min(a,b);
}
double distance(Point p, Straight l){
   double dy = l.y2-l.y1, dx = l.x2-l.x1;
   return fabs(dy*p.x-dx*p.y + l.x2*l.y1-l.x1*l.y2)/sqrt(dy*dy + dx*dx);
}
double distance(Point p, Polygon poly){
   double t,s,dy,dx;
   bool outside = false;
   dy = poly.m[0].y2-poly.m[0].y1;
   dx = poly.m[0].x2-poly.m[0].x1;
   s=(dy*p.x-dx*p.y+poly.m[0].x2*poly.m[0].y1-poly.m[0].x1*poly.m[0].y2)/sqrt(dy*dy + dx*dx);
   t =s/fabs(s);
   for(int i = 1; i < poly.m.size(); i++){
      dy = poly.m[i].y2-poly.m[i].y1;
      dx = poly.m[i].x2-poly.m[i].x1;
      s=(dy*p.x-dx*p.y + poly.m[i].x2*poly.m[i].y1-poly.m[i].x1*poly.m[i].y2)/sqrt(dy*dy + dx*dx);
      s/=fabs(s);
      if(s*t < 0){
         outside = true;
         break;
      }
      t = s;
   }
   if(!outside)
      return 0;
   double Min;
   Min = distance(p,poly.m[0]);
   for(int i = 1; i < poly.m.size(); i++)
      Min = min(Min,distance(p,poly.m[i]));
   return Min;
}
//distance Segment
double distance(Segment l1, Segment l2){
   //проверим пересечение отрезков
   double d,d1,d2,t,s;
   d = (l1.x2-l1.x1)*(l2.y1-l2.y2)-(l1.y2-l1.y1)*(l2.x1-l2.x2);
   d1= (l1.x2-l1.x1)*(l2.y1-l1.y1)-(l1.y2-l1.y1)*(l2.x1-l1.x1);
   d2= (l2.y1-l2.y2)*(l2.x1-l1.x1)-(l2.x1-l2.x2)*(l2.y1-l1.y1);
   if(d != 0){
      t=d1/d;
      s=d2/d;
      if(t>=0 && s>=0 && t<=1 && s<=1)
         return 0;
   }
   //если не пересекаются
   double Min;
   Min = distance(Point(l1.x1,l1.y1),l2);
   Min = min(Min,distance(Point(l1.x2,l1.y2),l2));
   Min = min(Min,distance(Point(l2.x1,l2.y1),l1));
   Min = min(Min,distance(Point(l2.x2,l2.y2),l1));
   return Min;
}
double distance(Segment l1, Straight l2){
   //подставим в уравнение прямой концы отрезка
   double n1 = l1.y1*(l2.x2-l2.x1)-l2.y1*(l2.x2-l2.x1) - l1.x1*(l2.y2-l2.y1) +l2.x1*(l2.y2-l2.y1);
   double n2 = l1.y2*(l2.x2-l2.x1)-l2.y1*(l2.x2-l2.x1) - l1.x2*(l2.y2-l2.y1) +l2.x1*(l2.y2-l2.y1);
   //если концы отрезка по разные стороны прямой
   if(n1 > 0 && n2 < 0 || n1 < 0 && n2 > 0)
      return 0;
   double Min;
   Min = distance(Point(l1.x1,l1.y1),l2);
   Min = min(Min,distance(Point(l1.x2,l1.y2),l2));
   return Min;
}
double distance(Segment l, Polygon poly){
   double Min;
   Min = distance(l,poly.m[0]);
   for(int i = 1; i < poly.m.size(); i++)
      Min = min(Min,distance(l,poly.m[i]));
   return Min;
}
double distance(Segment l, Point p){ return distance(p,l); }
//distance Straight
double distance(Straight l1, Straight l2){
   if((l1.y2-l1.y1)*(l2.x2-l2.x1) != (l2.y2-l2.y1)*(l1.x2-l1.x1))//если прямые не параллельны
      return 0;
   //иначе просто расстояние от любой точки на линии, до второй прямой
   return distance(Point(l1.x1,l1.y1),l2);
}
double distance(Straight l, Polygon poly){
   double Min;
   Min = distance(l,poly.m[0]);
   for(int i = 1; i < poly.m.size(); i++)
      Min = min(Min,distance(l,poly.m[i]));
   return Min;
}
double distance(Straight l, Point p){ return distance(p,l); }
double distance(Straight l2, Segment l1){ return distance(l1,l2); }
//distance Polygon
double distance(Polygon poly1, Polygon poly2){
   double Min;
   Min = distance(poly1.m[0],poly2);
   for(int i = 1; i < poly1.m.size(); i++)
      Min = min(Min,distance(poly1.m[i],poly2));
   return Min;
}
double distance(Polygon poly, Point p){ return distance(p,poly); }
double distance(Polygon poly, Segment l){ return distance(l,poly); }
double distance(Polygon poly, Straight l){ return distance(l,poly); }

//intersection = Point
Point intersection(Segment l1, Segment l2){ 
   if(distance(l1,l2) != 0)
      throw IntersectionError();
   return intersection(Straight(l1.x1,l1.y1,l1.x2,l1.y2),Straight(l2.x1,l2.y1,l2.x2,l2.y2));
}
Point intersection(Segment l1, Straight l2){
   if(distance(l1,l2) != 0)
      throw IntersectionError();
   return intersection(Straight(l1.x1,l1.y1,l1.x2,l1.y2),l2);
}
Point intersection(Straight l1, Straight l2){
   if(distance(l1,l2) != 0)
      throw IntersectionError();
   double a1,a2,b1,b2,c1,c2;
   a1 = l1.y1-l1.y2;
   b1 = l1.x2-l1.x1;
   c1 = l1.x1*(l1.y2-l1.y1)+l1.y1*(l1.x1-l1.x2);
   a2 = l2.y1-l2.y2;
   b2 = l2.x2-l2.x1;
   c2 = l2.x1*(l2.y2-l2.y1)+l2.y1*(l2.x1-l2.x2);
   double x,y;
   x = (b1*c2 - b2*c1)/(a1*b2 - a2*b1);
   y = (a2*c1 - a1*c2)/(a1*b2 - a2*b1);
   return Point(x,y);
}
Point intersection(Straight l2, Segment l1){ return intersection(l1,l2); }
//intersection = Segment
Segment intersection(Segment l, Polygon poly){ 
   if(distance(l,poly) != 0)
      throw IntersectionError();
   int points = 0;
   Point p[2];
   for(int i = 0; i < poly.m.size(); i++){
      if(distance(l,poly.m[i]) == 0){
         if(points == 2)
            throw IntersectionError();
         p[points++] = intersection(l,poly.m[i]);
      }
   }
   if(points == 0) //отрезок полностью в многоугольнике
      return l;
   if(points == 1){//отрезок пересек одну грань
      if(distance(Point(l.x1,l.y1),poly) != 0)
         return Segment(p[0],Point(l.x2,l.y2));
   }
   return Segment(p[0],p[1]);//иначе вернуть отрезок по двум точкам пересечения
}
Segment intersection(Straight l, Polygon poly){ 
   if(distance(l,poly) != 0)
      throw IntersectionError();
      
   int points = 0;
   Point p[2];
   for(int i = 0; i < poly.m.size(); i++){
      if(distance(l,poly.m[i]) == 0){
         if(points == 2)
            throw IntersectionError();
         p[points++] = intersection(l,poly.m[i]);
      }
   }
   return Segment(p[0],p[1]);//вернуть отрезок по двум точкам пересечения
}
Segment intersection(Polygon poly,Segment l){ return intersection(l,poly); }
Segment intersection(Polygon poly,Straight l){ return intersection(l,poly); }