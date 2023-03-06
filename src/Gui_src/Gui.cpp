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

Gui::Gui(int width, int height, Scene sphereScene) : sphereScene(sphereScene) {

    this->width = width;
    this->height = height;
    r = g = b = 0.f;
    text = "";
    this->sphereScene = sphereScene;

//    UpdateTexture();
};

void Gui::UpdateTexture() { //
    Sphere sphere = Sphere(Vector(0, -100, 0), 100);
    const int w = width / 2, h = height / 2;
    ImVec2 imagesize = ImVec2(width, height);

    float spherex = 0;
//    if (ImGui::SliderFloat("Sphere x", &sphere.Cs.x, -height, height));
//    if (ImGui::SliderFloat("Sphere y", &sphere.Cs.y, -height, height));
//    if (ImGui::SliderFloat("Sphere z", &sphere.Cs.z, -height, height));
//    if (ImGui::SliderFloat("light x", &sphere.Light.x, -width, width));
//    if (ImGui::SliderFloat("light y", &sphere.Light.y, -height, height));
//    if (ImGui::SliderFloat("light z", &sphere.Light.z, -height, height));

    sphereScene.renderSphere();
}


