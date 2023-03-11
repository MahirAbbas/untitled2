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
#include "../Light/Light.h"

//TODO VECTOR D AS CONSTRUCTOR, AND Cs, Origin etc
    class Sphere {
    public:
        Sphere();
        Sphere(Vector cs, double radius);
        double intensity;
        Vector ambient_coefficient;
        Material material;

        // Direction of line
        Vector d = Vector(0, 0, 1);
        // Direction of line
        // 3D Sphere = (p-Cs)^2=radius^2
        // p is any point on the Sphere surface
        // radius = radius of Sphere (scalar)
        // Cs - origin of the Sphere
        Vector Cs, p;
        float radius ;
        double t = 0;
        Vector origin= Vector(0, 0, 0);
        Vector eye = Vector(0,0,0);
//        Vector v = origin-Cs;
//        Vector v;
        Vector Light = Vector(150, 150, -250);
        double a, b, c, disc;

        Vector normal;
        double dp;
        Vector Lv;
        bool intersected;


        void setOrigin(Vector screen)
        {
            origin = screen;
        }
        void calculations(Vector v, class Light light);


        bool intersects(Vector origin);

        void intersesectsAtT();

        void calculatePhongReflectuin();

        double ambientIlluminationBlue(class Light light, Vector surfaceNormal);
        double ambientIlluminationGreen(class Light light, Vector surfaceNormal);
        double ambientIlluminationRed(class Light light, Vector surfaceNormal);

        double diffuseIlluminationRed(class Light light, Vector surfaceNormal);
        double diffuseIlluminationGreen(class Light light, Vector surfaceNormal);
        double diffuseIlluminationBlue(class Light light, Vector surfaceNormal);

        double specularIlluminationRed(class Light light,  Vector origin);
        double specularIlluminationGreen(class Light light,  Vector origin);
        double specularIlluminationBlue(class Light light,  Vector origin);

//        void
    };

#endif //UNTITLED2_SPHERE_H
