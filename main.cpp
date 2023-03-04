#include <iostream>
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "imgui/backends/imgui_impl_opengl3_loader.h"
#include <cmath>
//#include "glad.h"
#include <stdlib.h>
#include "GLFW/glfw3.h"
#include "src/Gui_src/Gui.h"
#include "src/Scene/Scene.h"
void framebuffer_size_callback(GLFWwindow*, int, int);
void processInput(GLFWwindow *window);



int main() {

    if (!glfwInit())
        return -1;
    GLFWwindow* window = glfwCreateWindow(1920, 1080, "Test Window", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);


    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    bool show_demo_window = true;
    bool show_another_window = false;

    while (!glfwWindowShouldClose(window))
    {
//        using namespace ImGui;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            Gui newGui = Gui(600, 400, Scene(600, 400, Light(1, 1, 1, Vector(100, 100, 100))));

//            static Gui myGui = Gui(600,400);
            static float red,green, blue;
            ImGui::Begin("Test2", NULL, ImGuiWindowFlags_AlwaysAutoResize);
            ImGui::PushItemWidth(200) ;

//            (ImGui::SliderFloat("green", &myGui.sphere.material.colourGreen, 0.f, 1.f));
//            (ImGui::SliderFloat("red", &myGui.sphere.material.colourRed, 0.f, 1.f));
//            (ImGui::SliderFloat("blue", &myGui.sphere.material.colourBlue, 0.f, 1.f));
//            ImGui::Separator();

            ImGui::TextWrapped("Debug Window");
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
//            ImGui::Text("col: %.1f", myGui.Sphere.col);
            ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(127, 127, 127, 100));
            ImGui::BeginChild("Debug_win", ImVec2(400,200), true, ImGuiWindowFlags_None);
            ImGui::TextWrapped(newGui.GetText().c_str());
            ImGui::EndChild();

            ImGui::Separator();



                newGui.Update();


//            glDeleteTextures(1, &testTexture);
            ImGui::PopItemWidth();
            ImGui::PopStyleColor();
            ImGui::End();
        }

        ImGui::Render();
        int display_width, display_height;
        glfwGetFramebufferSize(window, &display_width, &display_height);
        glViewport(0,0,display_width,display_height);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        processInput(window);

        glfwSwapBuffers(window);
        glfwPollEvents();
//        std::vector<int> ints;
//        ints.push_back(2);

    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}

// calls glfw and gives argument when resizing window
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0,0,width, height);
}
// closes window if ESCAPE key is pressed
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}