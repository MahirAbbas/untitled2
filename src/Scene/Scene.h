//
// Created by mahir on 27/02/23.
//

#ifndef UNTITLED2_SCENE_H
#define UNTITLED2_SCENE_H

#include "../../imgui/imgui.h"
#include "../../imgui/backends/imgui_impl_opengl3_loader.h"
#include "../../imgui/backends/imgui_impl_opengl3.h"
#include "../../imgui/backends/imgui_impl_glfw.h"
#include <GLFW/glfw3.h>
#include "../Sphere/Sphere.h"
#include <vector>
#include "../Light/Light.h"
#include "../Vector/Vector.h"

//TODO
// spawn sphere
// light
// imgui/texture
// GUI/sliders
// render
class Scene {
public:
    std::vector<Sphere> Spheres;
    Sphere sphere = Sphere(Vector(0,-100,0), 100);
    GLuint texture = NULL;
    ImVec2 imagesize = ImVec2(width, height);

    Light light;
    int width, height;
    unsigned char *pixelData = new unsigned char[width * height * 4];
    Scene();
    Scene(int width, int height, Light light);

    void renderSphere();

};


#endif //UNTITLED2_SCENE_H