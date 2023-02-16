//
// Created by mahir on 2/16/23.
//

#ifndef UNTITLED2_SHAPES_H
#define UNTITLED2_SHAPES_H
#include "Vector.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_opengl3_loader.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include <GLFW/glfw3.h>
#include <GL/gl.h>
namespace shapes {
    class sphere {

    public:
        sphere(){};
        double col = 100;
        // Direction of line
        Vector d = Vector(0, 0, 1);
        // 3D Sphere = (p-Cs)^2=r^2
        // p is any point on the sphere surface
        // r = radius of sphere (scalar)
        // Cs - origin of the sphere
        Vector cs = Vector(0, 0, 0);
        double r;
        Vector p;
        double t = 0;
        double a, b, c;
        Vector v;
        Vector Light = Vector(150, 150, -250);


    };
}
#endif //UNTITLED2_SHAPES_H
