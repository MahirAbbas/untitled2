//
// Created by mahir on 27/02/23.
//

#ifndef UNTITLED2_LIGHT_H
#define UNTITLED2_LIGHT_H
#include "../Vector/Vector.h"


class Light {
public:
    float red,green,blue;
    Vector direction;
    Light();
    Light(float r, float g, float b, Vector direction);


        void setLightColour(float r, float g, float b)
        {
            this-> red = r;
            this-> green = g;
            this-> blue = b;
        }
};


#endif //UNTITLED2_LIGHT_H
