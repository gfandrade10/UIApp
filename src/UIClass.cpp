#include <GLFW/glfw3.h>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "UIClass.h"
#include "SetClass.h"

#include <cstddef>
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

void UIClass::GetInputButtons() const
{   
    static std::string displayText; // Holds the output text
    static bool showTextWindow = false;

    size_t number = 6;
    float buttonLength = 50.0f;
    float buttonHeight = 50.0f;
    float verticalSpacing = 10.0f; 

    for (int row = 0; row < 2; ++row) // Two rows
    {
        for (int col = 0; col < 5; ++col) // Five buttons per row
        {
            if (ImGui::Button((std::to_string(number)).c_str(), ImVec2(buttonLength, buttonHeight)))
            {
                NumberSequence obj(number);
                obj.Run();
                displayText = obj.getString();
                showTextWindow = true;
            }   
            if (col < 4)
                ImGui::SameLine();
            ++number; // Increment the number for the next button
        }
    }

    if(showTextWindow)
    {
        float totalWidth = (5 * buttonLength + 4 * verticalSpacing) * 1.5f;
        ImVec2 ButtonWindowSize(totalWidth, 100.0f);
        // Set the position for the result window, below the buttons
        ImVec2 resultWindowPos = ImVec2(ImGui::GetCursorPosX(),
            ImGui::GetCursorPosY() + verticalSpacing
        );

        ImGui::SetNextWindowPos(resultWindowPos, ImGuiCond_Always);
        ImGui::SetNextWindowSize(ButtonWindowSize, ImGuiCond_Always);
        ImGui::Begin("Result", NULL, ImGuiWindowFlags_NoResize   | 
                                     ImGuiWindowFlags_NoCollapse |
                                     ImGuiWindowFlags_NoTitleBar |
                                     ImGuiWindowFlags_NoInputs   |
                                     ImGuiWindowFlags_NoMove);

        ImGui::TextUnformatted(displayText.c_str()); // Display the result
        ImGui::End();
    }
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
        ImGui::Begin("Hello, First C++ UI App", NULL, ImGuiWindowFlags_NoResize     | 
                                                      ImGuiWindowFlags_NoCollapse   |
                                                      ImGuiWindowFlags_NoBringToFrontOnFocus);
        ImGui::SetWindowSize(imguiWindowSize);

        // Ensure ImGui window stays within GLFW bounds
        ImVec2 imguiWindowPos = ImGui::GetWindowPos();
        if (imguiWindowPos.x < 0) imguiWindowPos.x = 0;
        if (imguiWindowPos.y < 0) imguiWindowPos.y = 0;
        if (imguiWindowPos.x + imguiWindowSize.x > windowWidth) imguiWindowPos.x = windowWidth - imguiWindowSize.x;
        if (imguiWindowPos.y + imguiWindowSize.y > windowHeight) imguiWindowPos.y = windowHeight - imguiWindowSize.y;

        ImGui::SetWindowPos(imguiWindowPos);

        ImGui::Text("Unique Numbers Generator");

        GetInputButtons();

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
