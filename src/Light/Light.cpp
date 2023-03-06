//
// Created by mahir on 27/02/23.
//

#include "Light.h"

Light::Light() {};
Light::Light(float r, float g, float b, Vector direction) {
try {
    this->red = r;
    this->green = g;
    this->blue = b;
    this->direction = direction;

} catch (std::exception& e)
{
    std::cerr << e.what() << "thrown here" << std::endl;
}
}