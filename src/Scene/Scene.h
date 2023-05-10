//
// Created by mahir on 27/02/23.
//

#ifndef UNTITLED2_SCENE_H
#define UNTITLED2_SCENE_H

#include "../../imgui/backends/imgui_impl_glfw.h"
#include "../../imgui/backends/imgui_impl_opengl3.h"
#include "../../imgui/backends/imgui_impl_opengl3_loader.h"
#include "../../imgui/imgui.h"
#include "../Light/Light.h"
#include "../Sphere/Sphere.h"
#include "../Vector/Vector.h"
#include <GLFW/glfw3.h>
#include <future>
#include <iostream>
#include <thread>
#include <vector>

// TODO
//  spawn sphere
//  light
//  imgui/texture
//  GUI/sliders
//  render
class Scene {
public:
  int width, height;
  Scene(int width, int height, Light light);
  std::vector<Sphere> Spheres;
  Sphere sphere = Sphere(Vector(0, 0, 1200), 200);

  GLuint texture = NULL;
  ImVec2 imagesize = ImVec2(600, 400);

  Light light;

  void renderSphere();

  void threadRenderRed(std::promise<int> &&prom, Sphere closestsphere);
  void threadRenderGreen(std::promise<int> &&prom, Sphere closestsphere);
  void threadRenderBlue(std::promise<int> &&prom, Sphere closestsphere);
};

#endif // UNTITLED2_SCENE_H
