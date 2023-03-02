//
// Created by mahir on 27/02/23.
//

#ifndef UNTITLED2_LIGHT_H
#define UNTITLED2_LIGHT_H
#include "../Vector/Vector.h"


class Light {
        float r,g,b;
        Vector direction;


        void setLightColour(float r, float g, float b)
        {
            this-> r = r;
            this-> g = g;
            this-> b = b;
        }
};


#endif //UNTITLED2_LIGHT_H
