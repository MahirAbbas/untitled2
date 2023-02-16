//
// Created by mahir on 2/14/23.
//

#ifndef UNTITLED2_GUI_H
#define UNTITLED2_GUI_H

#include "../imgui/imgui.h"
#include "../imgui/backends/imgui_impl_opengl3_loader.h"
#include "../imgui/backends/imgui_impl_opengl3.h"
#include "../imgui/backends/imgui_impl_glfw.h"
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <string>
#include "../Vector.h"
#include "../shapes.h"
class gui
{
private:

    float r, g, b;
    std::string text;
    int width = 600, height = 400;
//    GLuint texture = NULL;
public:
    ImVec2 imagesize = ImVec2(width, height);
    GLuint texture = NULL;
    unsigned char bluepixel[4] = {0,0,255,255};

    unsigned char getPixel() {return bluepixel[4];}
    gui()
    {
        r = g = b = 0.f;
        text = "";
        UpdateTexture();

    }
    void SetRed(const float rv)
    {
        r = rv;
//        Update();
//        std::cout << r <<"\n";
    }
    void SetGreen(const float gv)
    {
        g = gv;
//        Update();
    }
    void SetBlue(const float bv)
    {
        b = bv;
//        Update();
    }


    GLuint GetTexture() { return texture; }
//    ImTextureID GetTextureID() {return texture;}
    int Width() { return width; }
    int Height() { return height; }
//    int SetTexture() {this.texture}

    const std::string GetText() { return text; }

    void Update() {
        UpdateText();
        UpdateTexture();
    }

    void bluePixel()
    {
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE,bluepixel);
        glBindTexture(GL_TEXTURE_2D, 0);
        ImGui::Image(reinterpret_cast<void *>(texture), imagesize);
    }
    shapes::sphere sphere = shapes::sphere();

private:
    void UpdateText() {
        text = "red:=" + std::to_string(r) + " green:=" + std::to_string(g) + " blue:=" + std::to_string(b);
    }

//    Vector Light= Vector(150,150,-250);
//    Vector cs = Vector(0,0,0);
//    Vector d = Vector(0,0,1);
    void UpdateTexture() {
        const int w = width/2, h = height/2;

        // Direction of line
        // 3D Sphere = (p-Cs)^2=r^2
        // p is any point on the sphere surface
        // r = radius of sphere (scalar)
        // Cs - origin of the sphere

        sphere.r = 100;
        sphere.p = Vector(0,0,0);

        if (ImGui::SliderFloat("sphere x", &sphere.cs.x, -height, height));
        if (ImGui::SliderFloat("light x", &sphere.Light.x, -width, width));
        if (ImGui::SliderFloat("light y", &sphere.Light.y, -height, height));
        if (ImGui::SliderFloat("light z", &sphere.Light.z, -height, height));
//        if (ImGui::SliderFloat("Line z", &d.z, -10, 10));
//        if (ImGui::SliderFloat("Line x", &d.x, -10, 10));
//        if (ImGui::SliderFloat("Line y", &d.y, -10, 10));

       unsigned char* pixelData = new unsigned char [width * height * 4];
        unsigned char B = (unsigned char)255 * b, R = (unsigned char)255 * r, G = (unsigned char)255 * g;
        for (int y = 0; y < height; y++)
            for (int x = 0; x < width; x++) {
                int index = y * width * 4 + x * 4;
                // Line Origin
                Vector o(x - w,y - h,0);
                sphere.v = o-sphere.cs;
                // a = d^2
                sphere.a=sphere.d.dot(sphere.d);
                // b = 2*vd
                b=2*sphere.v.dot(sphere.d);
                // c = v^2-r^2
                sphere.c=sphere.v.dot(sphere.v)-(r*r);
                double disc = (b*b)-4*sphere.a*sphere.c;
                if (disc < 0) {sphere.col = 0;}
                else{sphere.col = 255;}
                sphere.t = (-b- sqrt(disc))/2*sphere.a;
                sphere.p = o+sphere.d*sphere.t;
                Vector Lv= sphere.Light-sphere.p;
//                Lv.normalise();
                Vector n = sphere.p-sphere.cs;
                n.normalise();
                double dp = Lv.dot(n);
                if (dp < 0) sphere.col =0;
                else sphere.col = dp;
                if (sphere.col > 255) sphere.col = 255;
                pixelData[index] = sphere.col ;           // R
                pixelData[index + 1] = sphere.col;       // G
                pixelData[index + 2] = sphere.col;       // B
                pixelData[index + 3] = 255;     // A
//                std::cout << sphere.col << "\n";
            }
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP, GLFW_REPEAT);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,pixelData);
        glBindTexture(GL_TEXTURE_2D, 0);
        ImGui::Image(reinterpret_cast<void *>(texture), imagesize);
    }


};

#endif //UNTITLED2_GUI_H
//void UpdateTexture() {
//    unsigned char* pixelData = new unsigned char [width * height * 4];
//    unsigned char B = (unsigned char)255 * b, R = (unsigned char)255 * r, G = (unsigned char)255 * g;
//    for (int y = 0; y < height; y++)
//        for (int x = 0; x < width; x++) {
//            int index = y * width * 4 + x * 4;
//            pixelData[index] = B;           // B
//            pixelData[index + 1] = G;       // G
//            pixelData[index + 2] = R;       // R
//            pixelData[index + 3] = 255;     // A
//        }
//    glGenTextures(1, &texture);
//    glBindTexture(GL_TEXTURE_2D, texture);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE,pixelData);
//    glBindTexture(GL_TEXTURE_2D, 0);
//    ImGui::Image(reinterpret_cast<void *>(texture), imagesize);
//}
