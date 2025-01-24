# Ctrlengine
### 使用C++编写的游戏引擎
使用库：
1. Vulkan (https://www.vulkan.org)

2. GLFW (https://glfw.org)

3. bass (https://www.un4seen.com/))

4. assimp (https://github.com/assimp/assimp)

5. spdlog (https://github.com/gabime/spdlog)

6. nlohmann-json (https://github.com/nlohmann/json)

7. stb image (https://github.com/nothings/stb)

  **我也不知道这算不算一个游戏引擎 反正写出来了 awa**

如何使用：
首先安装上面列出来的库，要不然运行都运行不了 qwq
	如果你成功安装了这些库，把“Ctrlengine”文件夹放到你的C++项目的目录下，确保在Visual Studio或者Visual Studio Code的“资源管理器”视图中可以看到这个文件夹
	这个文件夹应该包括以下文件：
Ctrlengine
	├─logs
	├─main
	├─model
	│  └─obj
	├─verify
	├─versions
	│  ├─core
	│  │  ├─2D
	│  │  │  └─role
	│  │  └─3D
	│  │      └─role
	│  ├─error
	│  ├─file management
	│  │  └─file
	│  │      ├─file
	│  │      ├─model
	│  │      ├─music
	│  │      └─texture
	│  ├─log
	│  ├─performance
	│  ├─readfile
	│  ├─register
	│  ├─settings
	│  ├─sound
	│  └─window
	└─Vulkan
	    └─shaders
	运行代码，你会看见一个彩色三角形（前提是你的显卡支持Vulkan）
	打开"main"文件夹下的"main.cpp",你应该看到如下内容:

```cpp
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
```

​	让我们一步步理解这段代码！

# 游戏程序样例
## 初步认识Ctrlengine

​	main函数是整个C++程序的入口，代码"cte::CteWindow Window"指的是为在命名空间"cte"下的"CteWindow"类创建一个名为"Window"的对象，顾名思义，"CteWindow"是掌管"Window"的，为什么不使用"window"做为对象名呢？因为为了更方便的调用GLFW的函数，指向GLFWwindow的指针，名为"window"，为了防止重名报错，使用"Window"作为对象名
​	接下来是一个"try"的代码块，用来捕捉错误。
​	"Window.initWindow(800, 600, "Ctrlengine")"这段代码的作用是，调用”Window“对象下的”initWindow“函数，创建一个长800，宽600，标题为"Ctrlengine"的窗口
​	接下来的代码，是为"CteVulkan"类，创建了一个名为"vulkan"的对象。"initVulkan()"函数返回一个bool的值，代表Vulkan是否被成功初始化，如果没有初始化完成。则直接退出，返回值为-1
​	接下来的一个while循环，只要窗口没有关闭，就一直进行渲染。"vulkan.drawFrame()"是调用vulkan对象下的"drawFrame()"函数，这个函数是用于渲染一帧，你可能需要根据你的游戏需要进行修改。"Window.updateWindow()"是用于更新窗口。以显示新渲染的一帧。"vulkan.closeVulkan()"和"Window.closeWindow()"是用于关闭窗口和对Vulkan进行运行时使用的资源进行清理

awa
