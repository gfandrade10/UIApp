#include <GLFW/glfw3.h>
#include <memory>
#include "UIClass.h"

int main() 
{
    std::unique_ptr<UIClass> Application = std::make_unique<UIClass>();
    Application->Init(1280, 720, "UI App", nullptr, nullptr);
    Application->Run();
    return 0;
}
