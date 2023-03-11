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
    float shininessCoefficient;
    Material()
    {
        colourRed = 1;
        colourGreen = 1;
        ambientBlue = ambientGreen = ambientRed = 1;
        diffuseBlue = diffuseGreen = diffuseRed = 1;
        specularRed = specularGreen = specularBlue =1;
        shininessCoefficient = 1;
    }
};


#endif //UNTITLED2_MATERIAL_H
