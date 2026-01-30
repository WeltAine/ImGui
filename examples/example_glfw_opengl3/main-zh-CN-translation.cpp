// Dear ImGui: 针对 GLFW + OpenGL 3 的独立示例程序，使用可编程渲染管线
// (GLFW 是一个跨平台的通用库，用于处理窗口、输入、OpenGL/Vulkan/Metal 图形上下文创建等)


// 了解 Dear ImGui：
// - 常见问题解答 https://dearimgui.com/faq
// - 入门指南 https://dearimgui.com/getting-started
// - 文档 https://dearimgui.com/docs（与本地 docs/ 文件夹内容相同）。
// - 简介、链接及更多信息见 imgui.cpp 顶部


#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // 将引入系统 OpenGL 头文件


// [Win32] 我们的示例包含了一个用 VS2010 预编译的 glfw3.lib 副本，以最大限度地提高测试便利性以及与旧版 VS 编译器的兼容性。
// 为了与 VS2010 时代的库链接，VS2015+ 版本需要链接 legacy_stdio_definitions.lib，我们通过此 pragma 指令来实现。
// 您自己的项目应该不会受到影响，因为您很可能会链接与您的 Visual Studio 版本相匹配的较新版本的 GLFW 二进制文件。
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif


// 此示例也可以通过 Emscripten 编译并运行！详见 'Makefile.emscripten'。
#ifdef __EMSCRIPTEN__
#include "../libs/emscripten/emscripten_mainloop_stub.h"
#endif


static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW 错误 %d: %s\n", error, description);
}


// 主代码
int main(int, char**)
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;


    // 确定 GL+GLSL 版本
#if defined(IMGUI_IMPL_OPENGL_ES2)
// GL ES 2.0 + GLSL 100 (WebGL 1.0)
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(IMGUI_IMPL_OPENGL_ES3)
// GL ES 3.0 + GLSL 300 es (WebGL 2.0)
    const char* glsl_version = "#version 300 es";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
// GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 仅适用于 3.2+
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Mac 系统必须设置
#else
// GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 仅适用于 3.2+ 版本
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // 仅适用于 3.0+ 版本
#endif


// 创建带有图形上下文的窗口
    float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor()); // 仅在 GLFW 3.3+ 版本有效
    GLFWwindow* window = glfwCreateWindow((int)(1280 * main_scale), (int)(800 * main_scale), "Dear ImGui GLFW+OpenGL3 example", nullptr, nullptr);
    if (window == nullptr)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // 启用垂直同步


    // 设置 Dear ImGui 上下文
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // 启用键盘控制
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // 启用手柄控制


    // 设置 Dear ImGui 样式
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();


    // 设置缩放
    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(main_scale); // 烘焙固定的样式缩放。（在有动态样式缩放的解决方案之前，更改此项需要重置 Style 并再次调用此函数）
    style.FontScaleDpi = main_scale; // 设置初始字体缩放。（在 docking 分支中：使用 io.ConfigDpiScaleFonts=true 会根据当前显示器自动为每个窗口覆盖此设置）


    // 设置平台/渲染器后端
    ImGui_ImplGlfw_InitForOpenGL(window, true);
#ifdef __EMSCRIPTEN__
    ImGui_ImplGlfw_InstallEmscriptenCallbacks(window, "#canvas");
#endif
    ImGui_ImplOpenGL3_Init(glsl_version);


    // 加载字体
    // - 如果没有显式加载字体，Dear ImGui 将调用 AddFontDefault() 来选择一个内置字体：AddFontDefaultVector() 或 AddFontDefaultBitmap()。
    // 这一选择基于 (style.FontSizeBase * style.FontScaleMain * style.FontScaleDpi) 是否达到一个较小的阈值。
    // - 您可以加载多个字体，并使用 ImGui::PushFont()/PopFont() 来选择它们。
    // - 如果文件无法加载，AddFont 函数将返回 nullptr。请在代码中处理这些错误（例如使用断言、显示错误并退出）。
    // - 阅读 'docs/FONTS.md' 以获取更多说明和详情。
    // - 在 imconfig 文件中使用 '#define IMGUI_ENABLE_FREETYPE' 以使用 FreeType 获得更高质量的字体渲染。
    // - 请记住，在 C/C++ 中，如果你想在字符串字面量中包含反斜杠 \，你需要写成双反斜杠 \\ ！
    // - 我们的 Emscripten 构建过程允许将字体嵌入，以便在运行时从 "fonts/" 文件夹访问。详情请参阅 Makefile.emscripten。
    //style.FontSizeBase = 20.0f;
    //io.Fonts->AddFontDefaultVector();
    //io.Fonts->AddFontDefaultBitmap();
    //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf");
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf");
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf");
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf");
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf");
    //IM_ASSERT(font != nullptr);


    // 我们的状态
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


    // 主循环
#ifdef __EMSCRIPTEN__
// 对于 Emscripten 构建，我们将禁用文件系统访问，因此不要尝试对 imgui.ini 文件执行 fopen()。
// 您可以手动调用 LoadIniSettingsFromMemory() 从您自己的存储中加载设置。
    io.IniFilename = nullptr;
    EMSCRIPTEN_MAINLOOP_BEGIN
#else
    while (!glfwWindowShouldClose(window))
#endif
    {
        // 轮询并处理事件（输入、窗口调整大小等）
        // 你可以读取 io.WantCaptureMouse 和 io.WantCaptureKeyboard 标志，以判断 dear imgui 是否想要使用你的输入。
        // - 当 io.WantCaptureMouse 为 true 时，请勿将鼠标输入数据发送给主程序，或清除/覆盖你备份的鼠标数据。
        // - 当 io.WantCaptureKeyboard 为 true 时，请勿将键盘输入数据发送给主程序，或清除/覆盖你备份的键盘数据。
        // 通常情况下，你可以始终将所有输入传递给 Dear ImGui，并根据这两个标志位对你的应用程序隐藏这些输入。
        glfwPollEvents();
        if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0)
        {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }


        // 开始 Dear ImGui 帧
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        // 1. 显示大型演示窗口（大部分示例代码都在 ImGui::ShowDemoWindow() 中！你可以浏览其代码以了解更多关于 Dear ImGui 的信息！）。
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);


        // 2. 显示一个我们自己创建的简单窗口。我们使用 Begin/End 对来创建一个命名窗口。
        {
            static float f = 0.0f;
            static int counter = 0;


            ImGui::Begin("Hello, world!"); // 创建一个名为 "Hello, world!" 的窗口并开始向其中添加内容。


            ImGui::Text("This is some useful text."); // 显示一些文本（也可以使用格式化字符串）
            ImGui::Checkbox("Demo Window", &show_demo_window); // 编辑用于存储窗口打开/关闭状态的布尔值
            ImGui::Checkbox("另一个窗口", &show_another_window);


            ImGui::SliderFloat("浮点数", &f, 0.0f, 1.0f); // 使用 0.0f 到 1.0f 的滑块编辑 1 个浮点数
            ImGui::ColorEdit3("背景颜色", (float*)&clear_color); // 编辑代表颜色的 3 个浮点数，关于参数看一下imgui.h中的对应函数（组件说明你就明白了）


            if (ImGui::Button("按钮")) // 按钮在被点击时返回 true（大多数控件在被编辑或激活时返回 true）
                counter++;
            ImGui::SameLine();
            ImGui::Text("计数器 = %d", counter);


            ImGui::Text("应用程序平均耗时 %.3f 毫秒/帧 (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }


        // 3. 显示另一个简单的窗口。
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window); // 传入布尔变量的指针（窗口将显示一个关闭按钮，点击后会清除该布尔值）
            ImGui::Text("来自另一个窗口的问候！");
            if (ImGui::Button("关闭我"))
                show_another_window = false;
            ImGui::End();
        }


        // 渲染
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


        glfwSwapBuffers(window);
    }
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_MAINLOOP_END;
#endif


    // 清理工作
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();


    glfwDestroyWindow(window);
    glfwTerminate();


    return 0;
}
