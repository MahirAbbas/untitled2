#include "Scene.h"
#include <thread>
//TODO
// spawn sphere
// light
// imgui/texture
// GUI/sliders
// render
Scene::Scene(int width, int height, Light light) {
        this->width = width;
        this->height = height;
//    std::cout << "thrown here" << std::endl;
        this->light = light;
}



void Scene::renderSphere() {
    Vector origin = Vector(0, 0, 0);
    Spheres.push_back(sphere);
    unsigned char* pixelData = new unsigned char[width * height * 4];
    const int w = width / 2, h = height / 2;

    double diffuseRed, ambientRed, specularRed = 0;
    double diffuseGreen, ambientGreen, specularGreen = 0;
    double diffuseBlue, ambientBlue, specularBlue= 0;
    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++) {
            int index = y * width * 4 + x * 4;
            // origin of ray
//            Sphere closestSphere = Spheres[0];
            Sphere closestSphere = sphere;
            origin = Vector(x - w, y - h, 0);
            if (false) {
                for (auto &sphere: Spheres) {
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
//            pixelData[index] = sphere.intensity * sphere.material.colourRed;           // R
//            pixelData[index + 1] = sphere.intensity * sphere.material.colourGreen;       // G
//            pixelData[index + 2] = sphere.intensity * sphere.material.colourBlue;       // B
            pixelData[index + 3] = 255;     // A
            diffuseRed = closestSphere.diffuseIlluminationRed(light, normal);
            ambientRed = closestSphere.ambientIlluminationRed();
            specularRed = closestSphere.specularIlluminationRed(light,origin); //R
            double red = diffuseRed
                        + ambientRed
                        + specularRed;
            if (red > 255) red = 255;
            pixelData[index] = red;
//            printf("diffuse %f, ambient = %f, specular = %f", closestSphere.diffuseIlluminationRed(light, normal),  closestSphere.ambientIlluminationRed(light, normal), closestSphere.specularIlluminationRed(light,origin));

            diffuseGreen = closestSphere.diffuseIlluminationGreen(light, normal);
            ambientGreen = closestSphere.ambientIlluminationGreen();
            specularGreen= closestSphere.specularIlluminationGreen(light,origin); //G
            double green = diffuseGreen
                         + ambientGreen
                         + specularGreen;
            if (green > 255) green = 255;
            pixelData[index + 1] = green ;

            diffuseBlue = closestSphere.diffuseIlluminationBlue(light, normal);
            ambientBlue = closestSphere.ambientIlluminationBlue();
            specularBlue = closestSphere.specularIlluminationBlue(light,origin); //B
            double blue = diffuseBlue
                           + ambientBlue
                           + specularBlue;
            if (blue > 255) blue = 255;
            pixelData[index + 2] = blue;
//            printf("r: %f, g: %f, b: %f \n", specularRed, specularGreen, specularBlue);
//            pixelData[index] = closestSphere.diffuseIlluminationRed(light, normal) +
//                               closestSphere.ambientIlluminationRed(light, normal); //R
//            pixelData[index + 1] = closestSphere.diffuseIlluminationGreen(light, normal) +
//                                   closestSphere.ambientIlluminationGreen(light, normal); //G
//            pixelData[index + 2] = closestSphere.diffuseIlluminationBlue(light, normal) +
//                                   closestSphere.ambientIlluminationBlue(light, normal); //B
//            pixelData[index + 3] = 255;     // A


        }
        }
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixelData);
    glBindTexture(GL_TEXTURE_2D, 0);

    ImGui::Image(reinterpret_cast<void *>(texture), imagesize);
}



