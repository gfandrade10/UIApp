#ifndef UICLASS_H
#define UICLASS_H

#include <GLFW/glfw3.h>

class UIClass
{
    public:
    UIClass() = default;
    UIClass(UIClass&&) = delete;
    UIClass(const UIClass&) = delete;
    ~UIClass();
    
    UIClass& operator=(const UIClass&) = delete;
    void Init(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
    void Run();

    private:
    GLFWwindow* mWindow = nullptr;
};

#endif // !UICLASS_H
