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
    Scene(int width, int height);

    void Render() {

        const int w = width / 2, h = height / 2;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                for (Sphere sphere: Spheres) {
//                    if (sphere.intersects()) {
//                        set
//                        t
//                        value
//                        of intersect
//                    }
//                    use
//                    lowest
//                    t value
//                    intersect
                }
                int index = y * width * 4 + x * 4;
// Line Origin
                sphere.setOrigin(Vector(x - w, y - h, 0));
                sphere.v = sphere.o - sphere.Cs;
                sphere.calculations();
                pixelData[index] = sphere.intensity * sphere.material.colourRed;           // R
                pixelData[index + 1] = sphere.intensity * sphere.material.colourGreen;       // G
                pixelData[index + 2] = sphere.intensity * sphere.material.colourBlue;       // B
                pixelData[index + 3] = 255;     // A

            }
        }
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixelData);
        glBindTexture(GL_TEXTURE_2D, 0);
        ImGui::Image(reinterpret_cast<void *>(texture), imagesize);
    };
};


#endif //UNTITLED2_SCENE_H
