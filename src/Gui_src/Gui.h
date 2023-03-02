//
// Created by mahir on 2/14/23.
//

#ifndef UNTITLED2_GUI_H
#define UNTITLED2_GUI_H

#include <vector>
#include "../../imgui/imgui.h"
#include "../../imgui/backends/imgui_impl_opengl3_loader.h"
#include "../../imgui/backends/imgui_impl_opengl3.h"
#include "../../imgui/backends/imgui_impl_glfw.h"
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <string>
#include "../Vector/Vector.h"
#include "../Sphere/Sphere.h"
#include <stdlib.h>
#include "../Scene/Scene.h"

//#include ""
    class Gui {
    public:
        Gui();

        float r, g, b;
        std::string text;
        int width, height;
//        ImVec2 imagesize = ImVec2(width, height);
        GLuint texture = NULL;

        Gui(int width, int height) {
            this->width = 600;
            this->height = 400;
            r = g = b = 0.f;
            text = "";

            UpdateTexture();
        }

        void SetRed(const float rv) {
            r = rv;
        }

        void SetGreen(const float gv) {
            g = gv;
        }

        void SetBlue(const float bv) {
            b = bv;
        }

        const std::string GetText() { return text; }

        void Update() {
            UpdateText();
            UpdateTexture();
        }

        std::vector<Sphere> spheres;

        void UpdateText() {
            text = "red:=" + std::to_string(r) + " green:=" + std::to_string(g) + " blue:=" + std::to_string(b);
        }

        void UpdateTexture();

    };

#endif //UNTITLED2_GUI_H