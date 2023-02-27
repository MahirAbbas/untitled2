//
// Created by mahir on 27/02/23.
//

#ifndef UNTITLED2_SCENE_H
#define UNTITLED2_SCENE_H

#include "../Sphere/Sphere.h"
#include <vector>
#include "../Light/Light.h"
class Scene {
    std::vector<Sphere> Spheres;
    Sphere sphere;
    Light light;

};


#endif //UNTITLED2_SCENE_H
