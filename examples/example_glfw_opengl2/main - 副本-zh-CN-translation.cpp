// Dear ImGui: GLFW + OpenGL2 的独立示例程序，使用传统固定流水线
// (GLFW 是一个跨平台的通用库，用于处理窗口、输入、OpenGL/Vulkan/Metal 图形上下文创建等)


// 了解 Dear ImGui：
// - 常见问题解答 https://dearimgui.com/faq
// - 入门指南 https://dearimgui.com/getting-started
// - 文档说明 https://dearimgui.com/docs（与本地 docs/ 文件夹内容相同）。
// - 简介、链接及更多信息请参见 imgui.cpp 顶部


// **如果您的代码/引擎使用的是现代 OPENGL（着色器、VBO、VAO 等），请勿使用此代码**
// **建议优先使用 example_glfw_opengl2/ 文件夹中的代码**
// 详情请参阅 imgui_impl_glfw.cpp。


#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl2.h"
#include <stdio.h>
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif
#include <GLFW/glfw3.h>


// [Win32] 我们的示例包含了一个用 VS2010 预编译的 glfw3.lib 副本，以最大限度地提高测试便利性以及与旧版 VS 编译器的兼容性。
// 为了与 VS2010 时代的库链接，VS2015+ 需要链接 legacy_stdio_definitions.lib，我们通过此 pragma 指令来实现。
// 您自己的项目应该不会受到影响，因为您可能会链接与您的 Visual Studio 版本相匹配的更现代的 GLFW 二进制文件。
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
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


    // 创建带有图形上下文的窗口
    float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor()); // 仅适用于 GLFW 3.3+
    GLFWwindow* window = glfwCreateWindow((int)(1280 * main_scale), (int)(800 * main_scale), "Dear ImGui GLFW+OpenGL2 example", nullptr, nullptr);
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
    style.ScaleAllSizes(main_scale); // 烘焙固定的样式缩放。（在有动态样式缩放方案之前，更改此项需要重置 Style 并再次调用此函数）
    style.FontScaleDpi = main_scale; // 设置初始字体缩放。（在 docking 分支中：使用 io.ConfigDpiScaleFonts=true 会根据当前显示器自动为每个窗口覆盖此设置）


    // 设置平台/渲染器后端
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL2_Init();


    // 加载字体
    // - 如果没有显式加载字体，Dear ImGui 将调用 AddFontDefault() 来选择一个嵌入字体：AddFontDefaultVector() 或 AddFontDefaultBitmap()。
    // 这一选择是基于 (style.FontSizeBase * style.FontScaleMain * style.FontScaleDpi) 是否达到一个较小的阈值。
    // - 您可以加载多个字体，并使用 ImGui::PushFont()/PopFont() 来选择它们。
    // - 如果文件无法加载，AddFont 函数将返回 nullptr。请在代码中处理这些错误（例如使用断言、显示错误并退出）。
    // - 阅读 'docs/FONTS.md' 以获取更多说明和详情。
    // - 在 imconfig 文件中使用 '#define IMGUI_ENABLE_FREETYPE' 以调用 FreeType 实现更高质量的字体渲染。
    // - 请记住，在 C/C++ 中，如果你想在字符串字面量中包含反斜杠 \，你需要写成双反斜杠 \\ ！
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
    while (!glfwWindowShouldClose(window))
    {
        // 轮询并处理事件（输入、窗口调整大小等）
        // 你可以读取 io.WantCaptureMouse 和 io.WantCaptureKeyboard 标志，以判断 dear imgui 是否想要使用你的输入。
        // - 当 io.WantCaptureMouse 为 true 时，请勿将鼠标输入数据分发给您的主应用程序，或清除/覆盖您备份的鼠标数据。
        // - 当 io.WantCaptureKeyboard 为 true 时，请勿将键盘输入数据分发给您的主应用程序，或清除/覆盖您备份的键盘数据。
        // 通常情况下，您可以始终将所有输入传递给 Dear ImGui，并根据这两个标志对您的应用程序隐藏这些输入。
        glfwPollEvents();
        if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0)
        {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }


        // 开启 Dear ImGui 帧
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        // 1. 显示大型演示窗口（大部分示例代码都在 ImGui::ShowDemoWindow() 中！您可以浏览其代码以了解更多关于 Dear ImGui 的信息！）。
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);


        // 2. 显示一个我们自己创建的简单窗口。我们使用 Begin/End 对来创建一个命名窗口。
        {
            static float f = 0.0f;
            static int counter = 0;


            ImGui::Begin("Hello, world!"); // 创建一个名为 "Hello, world!" 的窗口并开始绘制。


            ImGui::Text("This is some useful text."); // 显示一些文本（也可以使用格式化字符串）
            ImGui::Checkbox("Demo Window", &show_demo_window); // 编辑存储窗口打开/关闭状态的布尔值
            ImGui::Checkbox("Another Window", &show_another_window);


            ImGui::SliderFloat("float", &f, 0.0f, 1.0f); // 使用 0.0f 到 1.0f 的滑块编辑 1 个浮点数
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // 编辑代表颜色的 3 个浮点数


            if (ImGui::Button("Button")) // 按钮在被点击时返回 true（大多数控件在被编辑或激活时返回 true）
                counter++;
            ImGui::SameLine();
            ImGui::Text("计数器 = %d", counter);


            ImGui::Text("应用程序平均 %.3f 毫秒/帧 (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }


        // 3. 显示另一个简单的窗口。
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window); // 传入布尔变量的指针（窗口将包含一个关闭按钮，点击时会清除该布尔值）
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
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


        // 如果你在非传统 OpenGL 头文件/上下文中使用此代码（你不应该这样做，请优先使用 imgui_impl_opengl3.cpp！！），
        // 你可能需要备份/重置/恢复其他状态，例如使用下面注释掉的代码行来处理当前着色器。
        //GLint last_program;
        //glGetIntegerv(GL_CURRENT_PROGRAM, &last_program);
        //glUseProgram(0);
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
        //glUseProgram(last_program);


        glfwMakeContextCurrent(window);
        glfwSwapBuffers(window);
    }


    // 清理
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();


    glfwDestroyWindow(window);
    glfwTerminate();


    return 0;
}
