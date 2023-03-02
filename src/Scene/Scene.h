//
// Created by mahir on 27/02/23.
//

#ifndef UNTITLED2_SCENE_H
#define UNTITLED2_SCENE_H

#include "../Sphere/Sphere.h"
#include <vector>
#include "../Light/Light.h"

//TODO
// spawn sphere
// light
// imgui/texture
// GUI/sliders
// render

class Scene {

    std::vector<Sphere> Spheres;
    Sphere sphere();
    Light light;
    int width, height;
    unsigned char *pixelData = new unsigned char[width * height * 4];

public:
    Scene(int width, int height){
        this->width = width;
        this->height = height;
    };
    void Render() {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                for (Sphere sphere : Spheres)
                {
                    if (sphere.intersects())
                    {
                        set t value of intersect
                    }
                    use lowest t value
                    intersect
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
    };
};


#endif //UNTITLED2_SCENE_H
