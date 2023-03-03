//
// Created by mahir on 2/14/23.
//

#include "../../imgui/imgui.h"
#include "../../imgui/backends/imgui_impl_opengl3_loader.h"
#include "../../imgui/backends/imgui_impl_opengl3.h"
#include "../../imgui/backends/imgui_impl_glfw.h"
#include "Gui.h"
#include <GLFW/glfw3.h>
#include "../Sphere/Sphere.h"
#include "../Scene/Scene.h"

Gui::Gui(int width, int height) {

    this->width = 600;
    this->height = 400;
    r = g = b = 0.f;
    text = "";
    sphereScene = Scene(600, 400);

    UpdateTexture();
};

void Gui::UpdateTexture() {

    Sphere sphere = Sphere(Vector(0, -100, 0), 100);
    const int w = width / 2, h = height / 2;
    ImVec2 imagesize = ImVec2(width, height);

    float spherex = 0;
    if (ImGui::SliderFloat("Sphere x", &sphere.Cs.x, -height, height));
    if (ImGui::SliderFloat("Sphere y", &sphere.Cs.y, -height, height));
    if (ImGui::SliderFloat("Sphere z", &sphere.Cs.z, -height, height));
    if (ImGui::SliderFloat("light x", &sphere.Light.x, -width, width));
    if (ImGui::SliderFloat("light y", &sphere.Light.y, -height, height));
    if (ImGui::SliderFloat("light z", &sphere.Light.z, -height, height));


//    unsigned char *pixelData = new unsigned char[width * height * 4];

//        unsigned char* pixelData2 = new unsigned char [width * height * 4];
//        unsigned char* pixelData3 = pixelData + pixelData2;
//        unsigned char B = (unsigned char)255 * b, R = (unsigned char)255 * radius, G = (unsigned char)255 * g;

//    for (int y = 0; y < height; y++) {
//        for (int x = 0; x < width; x++) {
//            int index = y * width * 4 + x * 4;
//// Line Origin
//            sphere.setOrigin(Vector(x - w, y - h, 0));
//            sphere.v = sphere.o - sphere.Cs;
//            sphere.calculations();
//            pixelData[index] = sphere.intensity * sphere.material.colourRed;           // R
//            pixelData[index + 1] = sphere.intensity * sphere.material.colourGreen;       // G
//            pixelData[index + 2] = sphere.intensity * sphere.material.colourBlue;       // B
//            pixelData[index + 3] = 255;     // A
//
//        }
//    }
//    glGenTextures(1, &texture);
//    glBindTexture(GL_TEXTURE_2D, texture);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixelData);
//    glBindTexture(GL_TEXTURE_2D, 0);
//    ImGui::Image(reinterpret_cast<void *>(texture), imagesize);
}


