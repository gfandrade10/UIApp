#include <GLFW/glfw3.h>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "UIClass.h"

#include <iostream>

void UIClass::Init(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
{
    glfwInit();
    mWindow = glfwCreateWindow(width, height, title, monitor, share);
    glfwMakeContextCurrent(mWindow);
    glfwSwapInterval(1); // Enable vsync

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(mWindow, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    ImGuiIO& io = ImGui::GetIO();
    ImFont* font = io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/Calibri.ttf", 16.0f);
    if (!font) 
        std::cerr << "Failed to load font!" << std::endl;
    else
        io.Fonts->Build();
}

void UIClass::Run()
{
    while (!glfwWindowShouldClose(mWindow)) 
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        int windowWidth, windowHeight;
        glfwGetWindowSize(mWindow, &windowWidth, &windowHeight);

        // Set up the UI
        ImVec2 imguiWindowSize(1200.0f, 700.0f); // Set desired ImGui window size
        ImGui::Begin("Hello, First C++ UI App", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        ImGui::SetWindowSize(imguiWindowSize);

        // Ensure ImGui window stays within GLFW bounds
        ImVec2 imguiWindowPos = ImGui::GetWindowPos();
        if (imguiWindowPos.x < 0) imguiWindowPos.x = 0;
        if (imguiWindowPos.y < 0) imguiWindowPos.y = 0;
        if (imguiWindowPos.x + imguiWindowSize.x > windowWidth) imguiWindowPos.x = windowWidth - imguiWindowSize.x;
        if (imguiWindowPos.y + imguiWindowSize.y > windowHeight) imguiWindowPos.y = windowHeight - imguiWindowSize.y;

        ImGui::SetWindowPos(imguiWindowPos);

        ImGui::Text("This is a cross-platform UI!");

        // Position the button within the bounds of the ImGui window
        ImVec2 buttonSize(150.0f, 50.0f);
        ImVec2 buttonPos(
            imguiWindowSize.x - buttonSize.x - 20.0f, // Align button with padding
            imguiWindowSize.y - buttonSize.y - 20.0f  // Align button with padding
        );
        ImGui::SetCursorPos(buttonPos);

        if (ImGui::Button("Exit", buttonSize))
            break;
        
        ImGui::End();

        if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            break;

        ImGui::Render();
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(mWindow);
    }
}

UIClass::~UIClass()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(mWindow);
    glfwTerminate();
}
