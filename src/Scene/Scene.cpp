#include "Scene.h"

//TODO
// spawn sphere
// light
// imgui/texture
// GUI/sliders
// render
Scene::Scene(int width, int height, Light light) {
    try {
        this->width = width;
        this->height = height;
        this->light = light;
    } catch (std::exception& e)
    {
        std::cerr << e.what() << "thrown here" << std::endl;
    }
}

void Scene::renderSphere() {
    Vector origin = Vector(0, 0, 0);
    Spheres.push_back(sphere);
    unsigned char *pixelData = new unsigned char[width * height * 4];

    const int w = width / 2, h = height / 2;
    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++){
            int index = y * width * 4 + x * 4;
            // origin of ray
            Sphere closestSphere = Spheres[0];
            origin = Vector(x - w, y - h, 0);
            for (auto& sphere: Spheres) {
                double t;
                if (sphere.intersects(origin)) {
//                    std::cout << " intersects" << "\n";
                    sphere.intersesectsAtT();
                    if (sphere.t < closestSphere.t) {
                        closestSphere = sphere;
                    }
                }
            }
            // point on sphere
            Vector point = origin + Vector(0,0,1) * closestSphere.t;
            Vector normal = point - closestSphere.Cs;
            normal.normalise();

            {
//                        set phong calculation
//                        for intersection with lowest t value, calculate reflection
//                        set
//                        t
//                        value
//                        of intersect
//
//                    use
//                    lowest
//                    t value
//                    intersect

// Line Origin
            }
            sphere.setOrigin(Vector(x - w, y - h, 0));
            Vector v = sphere.origin - sphere.Cs;
            sphere.calculations();
//            pixelData[index] = sphere.intensity * sphere.material.colourRed;           // R
            pixelData[index] = closestSphere.diffuseIlluminationRed(light, normal) + closestSphere.ambientIlluminationRed(light,normal); //R
//            pixelData[index + 1] = sphere.intensity * sphere.material.colourGreen;       // G
            pixelData[index + 1] = closestSphere.diffuseIlluminationGreen(light, normal) + closestSphere.ambientIlluminationGreen(light,normal); //G
//            pixelData[index + 2] = sphere.intensity * sphere.material.colourBlue;       // B
            pixelData[index + 2] = closestSphere.diffuseIlluminationBlue(light, normal) + closestSphere.ambientIlluminationBlue(light,normal); //B
//            pixelData[index + 3] = 255;     // A
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
}



