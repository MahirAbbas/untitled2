//
// Created by mahir on 27/02/23.
//

#ifndef UNTITLED2_MATERIAL_H
#define UNTITLED2_MATERIAL_H


class Material {
public:
    float colourRed, colourGreen, colourBlue;

    float ambientRed, ambientGreen, ambientBlue;
    float diffuseRed, diffuseGreen, diffuseBlue;
    float specularRed, specularGreen, specularBlue;
    Material()
    {
        colourRed = 1;
        colourGreen = 1;
        colourBlue = 1;
    }
};


#endif //UNTITLED2_MATERIAL_H
