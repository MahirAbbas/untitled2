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
            Lv.normalise();
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

    double pixelValue = (material.ambientBlue* intensity);
    if (pixelValue > 255){
        return 255;
    }
    if (pixelValue < 0) return 0;
    return pixelValue;
}

double Sphere::ambientIlluminationRed(class Light light, Vector surfaceNormal)
{
    double pixelValue = (material.ambientRed* intensity);
    if (pixelValue > 255){
        return 255;
    }
    if (pixelValue < 0) return 0;
    return pixelValue;
}

double Sphere::ambientIlluminationGreen(class Light light, Vector surfaceNormal)
{
    double pixelValue = (material.ambientGreen* intensity);
    if (pixelValue > 255){
        return 255;
    }
    if (pixelValue < 0) return 0;
    return pixelValue;
}


double Sphere::diffuseIlluminationRed(class Light light, Vector surfaceNormal)
{
    double pixelValue;
    pixelValue = (material.diffuseRed*intensity*(surfaceNormal.dot(light.direction)));

    if (pixelValue > 255){
        return 255;
    }
    if (pixelValue < 0) return 0;
    return pixelValue;
}

double Sphere::diffuseIlluminationGreen(class Light light, Vector surfaceNormal)
{
    double pixelValue;
    pixelValue = (material.diffuseGreen*intensity*(surfaceNormal.dot(light.direction)));
    if (pixelValue > 255){
        return 255;
    }
    if (pixelValue < 0) return 0;
    return pixelValue;
}

double Sphere::diffuseIlluminationBlue(class Light light, Vector surfaceNormal)
{
    double pixelValue;
    pixelValue = (material.diffuseBlue*intensity*(surfaceNormal.dot(light.direction)));
    if (pixelValue > 255){
        return 255;
    }
    if (pixelValue < 0) return 0;
    return pixelValue;
}
double Sphere::specularIlluminationRed(class Light light,  Vector origin) {
    double pixelValue;
//    Vector normalisedLightVector = light.direction.returnNormalised();
//    Vector normalisedSurfaceNormal = sphereSurfaceNormal.returnNormalised();
    Vector sphereSurfaceNormal = normal;
    Vector eyeDirection = eye - p;
    Vector reflectedLight = light.direction - sphereSurfaceNormal * (sphereSurfaceNormal.dot(light.direction)) * 2.0 ;
    pixelValue = material.specularRed * light.red * pow((reflectedLight.returnNormalised().dot(eyeDirection.returnNormalised())),material.shininessCoefficient);
    return pixelValue;
}

double Sphere::specularIlluminationGreen(class Light light, Vector origin) {
    double pixelValue;
//    Vector normalisedLightVector = light.direction.returnNormalised();
//    Vector normalisedSurfaceNormal = sphereSurfaceNormal.returnNormalised();
    Vector sphereSurfaceNormal = normal;
    Vector eyeDirection = eye - p;
    Vector reflectedLight = light.direction - sphereSurfaceNormal * (sphereSurfaceNormal.dot(light.direction)) * 2.0 ;
    pixelValue = material.specularGreen* light.red * pow((reflectedLight.returnNormalised().dot(eyeDirection.returnNormalised())),material.shininessCoefficient);
    return pixelValue;
}
double Sphere::specularIlluminationBlue(class Light light, Vector origin) {
    double pixelValue;
//    Vector normalisedLightVector = light.direction.returnNormalised();
//    Vector normalisedSurfaceNormal = sphereSurfaceNormal.returnNormalised();
    Vector sphereSurfaceNormal = normal;
    Vector eyeDirection = eye - p;
    Vector reflectedLight = light.direction - sphereSurfaceNormal * (sphereSurfaceNormal.dot(light.direction)) * 2.0 ;
    pixelValue = material.specularBlue * light.red * pow((reflectedLight.returnNormalised().dot(eyeDirection.returnNormalised())),material.shininessCoefficient);
    return pixelValue;
}
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

