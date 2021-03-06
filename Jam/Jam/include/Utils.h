#pragma once
#include <sys/stat.h>
#ifdef __CYGWIN__
#include <dirent.h>
#endif
#include <sys/types.h>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
extern bool CheckExistedFile(const std::string& filepath);

namespace MMath
{
    class Line;

    class Point
    {
    public:
        double x,y;
        Point(double _x, double _y):x(_x),y(_y){};
        Point():x(0),y(0){};
        double distance(const Point& other) const
        {
            return sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
        }


    };

    class Line
    {
    public:
        double a,b;//y = ax + b;
        Point A,B;
        Line(const Point& AA, const Point& BB):A(AA),B(BB)
        {
            double d = AA.x - BB.x;
            if(d == 0.0) d = 0.00001;
            a = (AA.y - BB.y)/d;
            b = AA.y  - a * AA.x;
        }

        bool isBelongLine(const Point& p) const
        {
            double dis1 =  p.distance(A);
            double dis2 = p.distance(B);
            double sum = A.distance(B);
            double detal = sum - dis1 - dis2;
            if(abs(detal) < 0.0001) return true;
            return false;
        }

        bool  Intersect(const Line& other) const
        {
            double x,y;
            double d = a - other.a;
            if(d == 0.0) d = 0.00001;
            x = (other.b - b)/d;
            y = a * x + b;
            printf("giao %f %f\n",x,y);
            Point p = Point(x,y);
            if( isBelongLine(p) && other.isBelongLine(p)) return true;
            return false;
        }
    };
};
