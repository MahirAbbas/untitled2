#include <iostream>
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "imgui/backends/imgui_impl_opengl3_loader.h"
#include <cmath>
//#include "glad.h"
#include <stdlib.h>
#include "GLFW/glfw3.h"
#include "src/gui_src/gui.h"
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
            static gui myGui;
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
            ImGui::TextWrapped(myGui.GetText().c_str());
            ImGui::EndChild();

            ImGui::Separator();
            ImVec2 uv_min = ImVec2(0.f, 0.f);
            ImVec2 uv_max = ImVec2(1.f, 1.f);
            ImVec4 tint_col = ImVec4(1.f, 1.f, 1.f, 1.f);
            ImVec4 border_col = ImVec4(1.f, 1.f, 1.f, .5f);

            ImVec2 imagesize(256, 256);

            if (true)
            {
//                myGui.bluePixel();
//                myGui.bluePixel();
//                ImGui::Image(reinterpret_cast<void *>(myGui.texture), imagesize);

                myGui.Update();

            }
//            glDeleteTextures(1, &testTexture);
            ImGui::PopItemWidth();
            ImGui::PopStyleColor();
            ImGui::End();
        }

        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
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