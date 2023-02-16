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
//        ImGui::Image(textureid, ImVec2(width, height));

//        glGenTextures(1, &texture);
//        glBindTexture(GL_TEXTURE_2D, texture);
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
    int GetTextureWidth() { return width; }
    int GetTextureHeight() { return height; }
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
private:
    void UpdateText() {
        text = "red:=" + std::to_string(r) + " green:=" + std::to_string(g) + " blue:=" + std::to_string(b);
    }
//    void UpdateTexture() {
//        int w = width, h = height;
//
//        double col = 0.0;
//        Vector o(0,0,0);
//        Vector d(0,0,1);
//        Vector cs(0,0,0);
//        double r = 100;
//        Vector p;
//        double t;
//        double a,b,c;
//        Vector v;
//
//        unsigned char* pixelData = new unsigned char [width * height * 4];
//        unsigned char B = (unsigned char)255 * b, R = (unsigned char)255 * r, G = (unsigned char)255 * g;
//        for (int y = 0; y < height; y++)
//            for (int x = 0; x < width; x++) {
//                int index = y * width * 4 + x * 4;
//                o.x = x-250;
//                o.y = y-250;
//                o.z = -200;
//                v= o - cs;
//
//                a=d.dot(d);
//                b=2*v.dot(d);
//                c=v.dot(v)-r*r;
//                double disc = (b*b)-4*a*c;
//                if (disc < 0) col = 0.0;
//                else
//                {
//                    col = 1.0f;
//                }
//                pixelData[index] = col;           // B
//                pixelData[index + 1] = col;       // G
//                pixelData[index + 2] = col;       // R
//                pixelData[index + 3] = 255;     // A
//            }
//        glGenTextures(1, &texture);
//        glBindTexture(GL_TEXTURE_2D, texture);
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE,pixelData);
//        glBindTexture(GL_TEXTURE_2D, 0);
//        ImGui::Image(reinterpret_cast<void *>(texture), imagesize);
//    }
    Vector Light= Vector(150,150,-250);
    Vector cs = Vector(0,0,0);
    void UpdateTexture() {
        const int w = width/2, h = height/2;

        double col;
        // Direction of line
        Vector d(0,0,1);
        // 3D Sphere = (p-Cs)^2=r^2
        // p is any point on the sphere surface
        // r = radius of sphere (scalar)
        // Cs - origin of the sphere
        double r = 100;
        Vector p(0,0,0);
        double t;
        double a,b,c;
        Vector v;

        float spherex= 0;
        if (ImGui::SliderFloat("sphere x", &cs.x, -height, height));
        if (ImGui::SliderFloat("light x", &Light.x, -width, width));
        if (ImGui::SliderFloat("light y", &Light.y, -height, height));
        if (ImGui::SliderFloat("light z", &Light.z, -height, height));

       unsigned char* pixelData = new unsigned char [width * height * 4];
        unsigned char B = (unsigned char)255 * b, R = (unsigned char)255 * r, G = (unsigned char)255 * g;
        for (int y = 0; y < height; y++)
            for (int x = 0; x < width; x++) {
                int index = y * width * 4 + x * 4;
                // Line Origin
                Vector o(x - w,y - h,0);
                v = o-cs;
                // a = d^2
                a=d.dot(d);
                // b = 2*vd
                b=2*v.dot(d);
                // c = v^2-r^2
                c=v.dot(v)-(r*r);
                double disc = (b*b)-4*a*c;
                if (disc < 0) {col = 0;}
                else{col = 255;}
                t = (-b- sqrt(disc))/2*a;
                p = o+d*t;
                Vector Lv= Light-p;
//                Lv.normalise();
                Vector n = p-cs;
                n.normalise();
                double dp = Lv.dot(n);
                if (dp < 0) col =0;
                else col = dp;
                if (col > 255) col = 255;
                pixelData[index] = col ;           // R
                pixelData[index + 1] = col;       // G
                pixelData[index + 2] = col;       // B
                pixelData[index + 3] = 255;     // A
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
