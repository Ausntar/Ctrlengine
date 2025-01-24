#include "../model/model.hpp"
#include "../Vulkan/CteVulkan.hpp"

int main() {
    cte::CteWindow Window;

    try {
        Window.initWindow(800, 600, "Ctrlengine");
        
        cte::CteVulkan vulkan;
        if (!vulkan.initVulkan()) {
            return -1;
        }
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
            vulkan.drawFrame();
            Window.updateWindow();
        }
        vkDeviceWaitIdle(device);
        vulkan.closeVulkan();
        Window.closeWindow();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        Sleep(5000);
    }
    return 0;
}