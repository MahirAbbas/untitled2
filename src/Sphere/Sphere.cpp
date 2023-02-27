//
// Created by mahir on 27/02/23.
//

#include "Sphere.h"
void Sphere::calculations()
{
    a = d.dot(d);
    b = 2*v.dot(d);
    c = v.dot(v)-(r*r);
    disc = (b*b)-4*a*c;
    if (disc < 0) intensity = 0;
    else
    {
        intensity = 1;
    }
    t = (-b- sqrt(disc))/2*a;
    p = o+d*t;
    Lv = Light-p;
//            Lv.normalise();
//            Why doesn't normalise work?
    n = p - Cs;
    n.normalise();

//            dp = (Light * Lv.dot(n)).dot(Vector(2,2,2));
    //including ambient illumination
    // dp += AmbientIlluminationCoefficent * Light Source RGB

    dp = Lv.dot(n);


    if (dp < 0)
    {
        intensity =0;
    }
    else
    {
        intensity = dp;
    }
    if (intensity > 255) intensity = 255;
}