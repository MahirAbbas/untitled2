#include "Scene.h"
#include <future>
#include <iostream>
#include <thread>
// TODO
//  spawn sphere
//  light
//  imgui/texture
//  GUI/sliders
//  render
Scene::Scene(int width, int height, Light light) {
  this->width = width;
  this->height = height;
  //    std::cout << "thrown here" << std::endl;
  this->light = light;
}
void Scene::threadRenderRed(std::promise<int> &&prom, Sphere closestSphere,
                            Vector normal, Vector origin) {

  double diffuseRed =
      closestSphere.diffuseIlluminationRed(Scene::light, normal);
  double ambientRed = closestSphere.ambientIlluminationRed();
  double specularRed =
      closestSphere.specularIlluminationRed(light, origin); // R
  double red = diffuseRed + ambientRed + specularRed;
  if (red > 255)
    red = 255;
  prom.set_value(red);
}

void Scene::threadRenderGreen(std::promise<int> &&prom, Sphere closestSphere,
                              Vector normal, Vector origin) {

  double diffuseGreen = closestSphere.diffuseIlluminationGreen(light, normal);
  double ambientGreen = closestSphere.ambientIlluminationGreen();
  double specularGreen =
      closestSphere.specularIlluminationGreen(light, origin); // G
  double green = diffuseGreen + ambientGreen + specularGreen;
  if (green > 255)
    green = 255;
  prom.set_value(green);
}

void Scene::threadRenderBlue(std::promise<int> &&prom, Sphere closestSphere,
                             Vector normal, Vector origin) {

  double diffuseBlue = closestSphere.diffuseIlluminationBlue(light, normal);
  double ambientBlue = closestSphere.ambientIlluminationBlue();
  double specularBlue =
      closestSphere.specularIlluminationBlue(light, origin); // B
  double blue = diffuseBlue + ambientBlue + specularBlue;
  if (blue > 255)
    blue = 255;
  prom.set_value(blue);
}
void Scene::renderSphere() {
  Vector origin = Vector(0, 0, 0);
  Spheres.push_back(sphere);
  unsigned char *pixelData = new unsigned char[width * height * 4];
  const int w = width / 2, h = height / 2;

  // doghtuble diffuseRed, ambientRed, specularRed = 0;
  // double diffuseGreen, ambientGreen, specularGreen = 0;
  // double diffuseBlue, ambientBlue, specularBlue = 0;
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      int index = y * width * 4 + x * 4;
      // origin of ray
      //            Sphere closestSphere = Spheres[0];
      Sphere closestSphere = sphere;
      origin = Vector(x - w, y - h, 0);
      if (false) {
        for (auto &sphere : Spheres) {
          double t;
          if (sphere.intersects(origin)) {
            //                    std::cout << " intersects" << "\n";
            sphere.intersesectsAtT();
            if (sphere.t < closestSphere.t) {
              closestSphere = sphere;
            }
          }
        }
      }
      // point on sphere
      Vector point = origin + Vector(0, 0, 1) * closestSphere.t;
      Vector normal = point - closestSphere.Cs;
      normal.normalise();

      sphere.setOrigin(Vector(x - w, y - h, 0));
      Vector v = sphere.origin - sphere.Cs;
      sphere.calculations(v, light);
      //            pixelData[index] = sphere.intensity *
      //            sphere.material.colourRed;           // R pixelData[index +
      //            1] = sphere.intensity * sphere.material.colourGreen; // G
      //            pixelData[index + 2] = sphere.intensity *
      //            sphere.material.colourBlue;       // B
      pixelData[index + 3] = 255; // A

      std::promise<int> promiseRed;
      std::future<int> futureRed = promiseRed.get_future();

      std::promise<int> promiseGreen;
      std::future<int> futureGreen = promiseGreen.get_future();

      std::promise<int> promiseBlue;
      std::future<int> futureBlue = promiseBlue.get_future();

      std::thread t1(&Scene::threadRenderRed, this, std::move(promiseRed),
                     closestSphere, normal, origin);
      std::thread t2(&Scene::threadRenderGreen, this, std::move(promiseGreen),
                     closestSphere, normal, origin);
      std::thread t3(&Scene::threadRenderBlue, this, std::move(promiseBlue),
                     closestSphere, normal, origin);

      t1.join();
      t2.join();
      t3.join();

      int result1 = futureRed.get();
      pixelData[index] = result1;
      int result2 = futureGreen.get();
      pixelData[index + 1] = result2;
      int result3 = futureBlue.get();
      pixelData[index + 2] = result3;

      // diffuseRed = closestSphere.diffuseIlluminationRed(light, normal);
      // ambientRed = closestSphere.ambientIlluminationRed();
      // specularRed = closestSphere.specularIlluminationRed(light, origin); //
      // R double red = diffuseRed + ambientRed + specularRed; if (red > 255)
      //   red = 255;
      // pixelData[index] = red;
      //            printf("diffuse %f, ambient = %f, specular = %f",
      //            closestSphere.diffuseIlluminationRed(light, normal),
      //            closestSphere.ambientIlluminationRed(light, normal),
      //            closestSphere.specularIlluminationRed(light,origin));

      // diffuseGreen = closestSphere.diffuseIlluminationGreen(light, normal);
      // ambientGreen = closestSphere.ambientIlluminationGreen();
      // specularGreen =
      //     closestSphere.specularIlluminationGreen(light, origin); // G
      // double green = diffuseGreen + ambientGreen + specularGreen;
      // if (green > 255)
      //   green = 255;
      // pixelData[index + 1] = green;

      // diffuseBlue = closestSphere.diffuseIlluminationBlue(light, normal);
      // ambientBlue = closestSphere.ambientIlluminationBlue();
      // specularBlue = closestSphere.specularIlluminationBlue(light, origin);
      // // B double blue = diffuseBlue + ambientBlue + specularBlue; if (blue >
      // 255)
      //   blue = 255;
      // pixelData[index + 2] = blue;
      //            printf("r: %f, g: %f, b: %f \n", specularRed, specularGreen,
      //            specularBlue); pixelData[index] =
      //            closestSphere.diffuseIlluminationRed(light, normal) +
      //                               closestSphere.ambientIlluminationRed(light,
      //                               normal); //R
      //            pixelData[index + 1] =
      //            closestSphere.diffuseIlluminationGreen(light, normal) +
      //                                   closestSphere.ambientIlluminationGreen(light,
      //                                   normal); //G
      //            pixelData[index + 2] =
      //            closestSphere.diffuseIlluminationBlue(light, normal) +
      //                                   closestSphere.ambientIlluminationBlue(light,
      //                                   normal); //B
      //            pixelData[index + 3] = 255;     // A
    }
  }
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, pixelData);
  glBindTexture(GL_TEXTURE_2D, 0);

  ImGui::Image(reinterpret_cast<void *>(texture), imagesize);
}
