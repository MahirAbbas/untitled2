//
// Created by mahir on 2/16/23.
//

#ifndef UNTITLED2_SPHERE_H
#define UNTITLED2_SPHERE_H
#include "../Vector/Vector.h"
#include "../../imgui/imgui.h"
#include "../../imgui/backends/imgui_impl_opengl3_loader.h"
#include "../../imgui/backends/imgui_impl_opengl3.h"
#include "../../imgui/backends/imgui_impl_glfw.h"
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include "../Material/Material.h"

//TODO VECTOR D AS CONSTRUCTOR, AND Cs, Origin etc
    class Sphere {
    public:
        Sphere(Vector cs){
            this->Cs = cs;
        }
        double intensity;
        Vector ambient_coefficient;
        Material material;

        // Direction of line
        Vector d = Vector(0, 0, 1);
        // Direction of line
        // 3D Sphere = (p-Cs)^2=r^2
        // p is any point on the Sphere surface
        // r = radius of Sphere (scalar)
        // Cs - origin of the Sphere
        Vector Cs, p;
        double r = 100;
        double t = 0;
        Vector o= Vector(0,0,0);
//        Vector v = o-Cs;
        Vector v;
        Vector Light = Vector(150, 150, -250);
        double a, b, c, disc;

        Vector n;
        double dp;
        Vector Lv;
        void setOrigin(Vector screen)
        {
            o = screen;
        }
        void calculations();


        void intersects();

//        void
    };

#endif //UNTITLED2_SPHERE_H
