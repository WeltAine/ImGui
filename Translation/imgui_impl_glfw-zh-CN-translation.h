// dear imgui: GLFW 平台后端
// 这需要与渲染器（如 OpenGL3、Vulkan、WebGPU 等）配合使用
// （信息：GLFW 是一个跨平台的通用库，用于处理窗口、输入、OpenGL/Vulkan 图形上下文创建等）
// （要求：GLFW 3.0+。为了获得完整的特性支持，建议使用 GLFW 3.3+/3.4+。）


// 已实现的功能：
// [X] 平台：剪贴板支持。
// [X] 平台：鼠标支持。可区分鼠标/触摸屏/笔（仅限 Windows）。
// [X] 平台：键盘支持。自 1.87 版本起，我们开始使用 io.AddKeyEvent() 函数。请向所有按键函数传递 ImGuiKey 值，例如 ImGui::IsKeyPressed(ImGuiKey_Space)。[旧有的 GLFW_KEY_* 值自 1.87 起已废弃，且自 1.91.5 起不再支持]
// [X] 平台：手柄支持。通过 'io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad' 启用。
// [X] 平台：鼠标光标形状及可见性 (ImGuiBackendFlags_HasMouseCursors)，需使用 GLFW 3.1+。调整光标大小功能需要 GLFW 3.4+！可通过 'io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange' 禁用。
// [X] 支持多个 Dear ImGui 上下文。
// 缺失的功能或问题：
// [ ] 平台：触摸事件仅在 Windows 上被正确识别为触摸。这会导致某些交互出现问题。由于 GLFW 未提供区分触摸输入与鼠标输入的方法，我们无法调用 io.AddMouseSourceEvent() 来识别来源。我们提供了一个针对 Windows 的特定变通方案。
// [ ] 平台：缺失 ImGuiMouseCursor_Wait 和 ImGuiMouseCursor_Progress 光标。


// 您可以在项目中使用未经修改的 imgui_impl_* 文件。请参阅 examples/ 文件夹了解相关使用示例。
// 建议将整个 imgui/ 仓库包含到您的项目中（作为副本或子模块），并仅构建您需要的后端。
// 了解 Dear ImGui：
// - 常见问题解答 https://dearimgui.com/faq
// - 入门指南 https://dearimgui.com/getting-started
// - 文档 https://dearimgui.com/docs（与本地 docs/ 文件夹内容相同）。
// - 简介、链接及更多信息见 imgui.cpp 顶部


#pragma once
#include "imgui.h" // IMGUI_IMPL_API
#ifndef IMGUI_DISABLE


struct GLFWwindow;
struct GLFWmonitor;


// 请参考“入门指南”链接并查看 examples/ 文件夹，以了解如何使用后端！
IMGUI_IMPL_API bool ImGui_ImplGlfw_InitForOpenGL(GLFWwindow* window, bool install_callbacks);
IMGUI_IMPL_API bool ImGui_ImplGlfw_InitForVulkan(GLFWwindow* window, bool install_callbacks);
IMGUI_IMPL_API bool ImGui_ImplGlfw_InitForOther(GLFWwindow* window, bool install_callbacks);
IMGUI_IMPL_API void ImGui_ImplGlfw_Shutdown();
IMGUI_IMPL_API void ImGui_ImplGlfw_NewFrame();


// Emscripten 相关初始化阶段方法（在 ImGui_ImplGlfw_InitForOpenGL 之后调用）
#ifdef __EMSCRIPTEN__
IMGUI_IMPL_API void ImGui_ImplGlfw_InstallEmscriptenCallbacks(GLFWwindow* window, const char* canvas_selector);
//static inline void ImGui_ImplGlfw_InstallEmscriptenCanvasResizeCallback(const char* canvas_selector) { ImGui_ImplGlfw_InstallEmscriptenCallbacks(nullptr, canvas_selector); } } // 在 1.91.0 版本中已重命名
#endif


// GLFW 回调安装
// - 当调用 Init 并设置 'install_callbacks=true' 时：将调用 ImGui_ImplGlfw_InstallCallbacks()。系统将为您安装 GLFW 回调。如果用户之前安装过回调，它们将链式调用这些回调。
// - 当调用 Init 并设置 'install_callbacks=false' 时：GLFW 回调将不会被安装。你需要从你自己的 GLFW 回调中手动调用各个对应的函数。
IMGUI_IMPL_API void ImGui_ImplGlfw_InstallCallbacks(GLFWwindow* window);
IMGUI_IMPL_API void ImGui_ImplGlfw_RestoreCallbacks(GLFWwindow* window);


// GFLW 回调选项：
// - 设置 'chain_for_all_windows=true' 以启用所有窗口的回调链（包括由后端或用户创建的次级视口）
IMGUI_IMPL_API void ImGui_ImplGlfw_SetCallbacksChainForAllWindows(bool chain_for_all_windows);


// GLFW 回调（如果您没有安装回调，可以自行调用的单个回调函数）
// 这些都是有实现的
IMGUI_IMPL_API void ImGui_ImplGlfw_WindowFocusCallback(GLFWwindow* window, int focused); // 自 1.84 版本起
IMGUI_IMPL_API void ImGui_ImplGlfw_CursorEnterCallback(GLFWwindow* window, int entered); // 自 1.84 版本起
IMGUI_IMPL_API void ImGui_ImplGlfw_CursorPosCallback(GLFWwindow* window, double x, double y); // 自 1.87 版本起
IMGUI_IMPL_API void ImGui_ImplGlfw_MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
IMGUI_IMPL_API void ImGui_ImplGlfw_ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
IMGUI_IMPL_API void ImGui_ImplGlfw_KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
IMGUI_IMPL_API void ImGui_ImplGlfw_CharCallback(GLFWwindow* window, unsigned int c);
IMGUI_IMPL_API void ImGui_ImplGlfw_MonitorCallback(GLFWmonitor* monitor, int event);


// GLFW 辅助函数
IMGUI_IMPL_API void ImGui_ImplGlfw_Sleep(int milliseconds);
IMGUI_IMPL_API float ImGui_ImplGlfw_GetContentScaleForWindow(GLFWwindow* window);
IMGUI_IMPL_API float ImGui_ImplGlfw_GetContentScaleForMonitor(GLFWmonitor* monitor);


#endif // #ifndef IMGUI_DISABLE