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
//TODO VECTOR D AS CONSTRUCTOR, AND Cs, Origin etc
namespace shapes {
    class sphere {
    public:
        sphere(Vector cs){
            this->cs = cs;
        }
        double intensity;
        float red = 1;
        float green = 1;
        float blue = 1;
        // Direction of line
        Vector d = Vector(0, 0, 1);
        // Direction of line
        // 3D Sphere = (p-Cs)^2=r^2
        // p is any point on the sphere surface
        // r = radius of sphere (scalar)
        // Cs - origin of the sphere
        Vector cs;
        double r = 100;
        Vector p;
        double t = 0;
        Vector o= Vector(0,0,0);
//        Vector v = o-cs;
        Vector v;
        Vector Light = Vector(150, 150, -250);
        double a;
        double b;
        double c;
        double disc;

        Vector n;
        double dp;
        Vector Lv;
        double setOrigin(Vector screen)
        {
            o = screen;
        }


        void calculations()
        {

            a = d.dot(d);
            b = 2*v.dot(d);
            c = v.dot(v)-(r*r);
            disc = (b*b)-4*a*c;
            t = (-b- sqrt(disc))/2*a;
            n = p-cs;
            n.normalise();
            p = o+d*t;
            Lv = Light-p;
//            Lv.normalise();
//            Why doesn't normalise work?
            dp = Lv.dot(n);
            if (dp < 0)
            {
                intensity =0;

            }
            else
            {
                intensity = dp;
            }
            if (intensity > 255) intensity = 255;

        }

        int* renderSphere(int width, int height, int* ptr)
        {
            int* arr = new int[width * height * 4];

            for (int y = 0; y < height; y++)
            {
                for (int x = 0; x < width; x++)
                {
                    int index = y * width * 4 * + x * 4;
                    this->o = Vector(x-(width/2), y-(height/2),0);
                    this->v = o-cs;
                    calculations();
                    arr[index] = intensity * red;           // R
                    arr[index + 1] = intensity * green;       // G
                    arr[index + 2] = intensity * blue;       // B
                    arr[index + 3] = 255;     // A
                }
            }
            return arr;
        }
    };
}

#endif //UNTITLED2_SHAPES_H
