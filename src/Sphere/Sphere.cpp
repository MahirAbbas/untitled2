//
// Created by mahir on 27/02/23.
//

#include "Sphere.h"
#include "../Light/Light.h"
#include <cmath>

Sphere::Sphere(Vector cs, double radius){

    this->Cs = cs;
    this->radius = radius;
    material.diffuseRed = 1;
    material.diffuseBlue= 1;
    material.diffuseGreen = 1;
};
void Sphere::calculations(Vector v, class Light light)
{
    a = d.dot(d);
    b = 2*v.dot(d);
    c = v.dot(v)-(radius * radius);
//    printf("(%d,%d,%d)", d.x,d.y,d.z);
//    printf("a: %d \n B: %d \n C:%d", a,b,c);
    disc = (b*b)-4*a*c;
    if (disc < 0)
    {
//        std::cout << "intersects" << "\n";
        intensity = 0;
    }
    else
    {
        intensity = 1;
//        std::cout << "intersects" << "\n";
    }

    t = (-b- sqrt(disc))/2*a;
    if (t > 0)
    {
//        std::cout << "intersects" << "\n";
    }
//    std::cout << t << "\n";
    p = origin + d * t;
//    std::cout << "("<<p.x << "," << p.y << p.??z <<")" << "\n";
//    printf("(%d,%d,%d)", p.x,p.y,p.z);
    Lv = Light-p;
//            Lv.normalise();
//            Why doesn't normalise work?
    normal = p - Cs;
    normal.normalise();

//            dp = (Light * Lv.dot(normal)).dot(Vector(2,2,2));
    //including ambient illumination
    // dp += AmbientIlluminationCoefficent * Light Source RGB

    dp = Lv.dot(normal);


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

double Sphere::ambientIlluminationBlue(class Light light, Vector surfaceNormal)
{
    return (material.ambientBlue * light.blue);
}

double Sphere::ambientIlluminationRed(class Light light, Vector surfaceNormal)
{
    double pixelValue = (material.ambientRed* intensity);
    if (pixelValue > 255){
        return 255;
    }
    return pixelValue;
}

double Sphere::ambientIlluminationGreen(class Light light, Vector surfaceNormal)
{
    return (material.ambientGreen* light.green);
}


double Sphere::diffuseIlluminationRed(class Light light, Vector surfaceNormal)
{
    double pixelValue;
    pixelValue = (material.diffuseRed*light.red*(surfaceNormal.dot(light.direction)));

    if (pixelValue > 255){
        return 255;
    }
    return pixelValue;
}

double Sphere::diffuseIlluminationGreen(class Light light, Vector surfaceNormal)
{
    double pixelValue;
    pixelValue = (material.diffuseGreen*light.green*(surfaceNormal.dot(light.direction)));
    if (pixelValue > 255){
        return 255;
    }
    return pixelValue;
}

double Sphere::diffuseIlluminationBlue(class Light light, Vector surfaceNormal)
{
    return (material.diffuseBlue*light.blue*(surfaceNormal.dot(light.direction)));
}
//void Sphere::calculatePhongReflection(class Light light, Vector sphereSurfaceNormal) {
// page 17 for diffuse illumination
//    Vector reflectedRay = light.direction - sphereSurfaceNormal * (2 * (sphereSurfaceNormal.dot(light.direction))) ;
//     (material.specularBlue * light.blue*(reflectedRay.normalise()*directionFrompointToPixel.normalise)^shinienessCoefficient);
//    (material.ambientRed* light.red)+(material.diffuseRed*light.red*(sphereSurfaceNormal * lightDirection))+(material.specularRed* light.red*(reflectedray.normailise()*directionFrompointToPixel.normalise)^shinienessCoefficient);
//    (material.ambientGreen* light.green)+(material.diffuseGreen*light.green*(sphereSurfaceNormal * lightDirection))+(material.specularGreen* light.Green*(reflectedray.normailise()*directionFrompointToPixel.normalise)^shinienessCoefficient);
//}

bool Sphere::intersects(Vector origin) {
    Vector v = origin - Cs;
    a = d.dot(d);
    b = 2*v.dot(d);
    c = v.dot(v)-(radius * radius);
    disc = (b*b)-4*a*c;
    if (false){
        const double b2 = b* b;
        const double ac4 = 4 * a * c;
        const double d = std::fma(-ac4, b2, b2);
    }
    if (disc < 0) return false;
    else
    {
        return true;
    }

}
void Sphere::intersesectsAtT() {

    t = (-b- sqrt(disc))/2*a;
}

