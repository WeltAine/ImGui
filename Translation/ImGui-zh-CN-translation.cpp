// dear imgui, v1.92.6 WIP
// (主要代码和文档)


// 帮助：
// - 调用并阅读 imgui_demo.cpp 中的 ImGui::ShowDemoWindow()。examples/ 目录下的所有应用程序都在这样做。
// - 更多详情、链接和注释请阅读 imgui.cpp 顶部内容。
// - 在包含 imgui.h 之前（或在 imconfig.h 中）添加 '#define IMGUI_DEFINE_MATH_OPERATORS'，即可使用为 ImVec2 和 ImVec4 提供的便利数学运算符。


// 资源：
// - 常见问题解答 (FAQ) ........... https://dearimgui.com/faq（在仓库中路径为 docs/FAQ.md）
// - 主页 ....................... https://github.com/ocornut/imgui
// - 发布说明与更新日志 ........... https://github.com/ocornut/imgui/releases
// - 展示厅 ..................... https://github.com/ocornut/imgui/issues?q=label%3Agallery (请在那里发布您的截图/视频！)
// - Wiki ....................... https://github.com/ocornut/imgui/wiki (这里有很多干货)
// - 入门指南 https://github.com/ocornut/imgui/wiki/Getting-Started (如何通过添加约 25 行代码集成到现有应用中)
// - 第三方扩展 https://github.com/ocornut/imgui/wiki/Useful-Extensions (ImPlot 及更多扩展)
// - 绑定/后端 https://github.com/ocornut/imgui/wiki/Bindings (语言绑定 + 适用于各种技术/引擎的后端)
// - 调试工具 https://github.com/ocornut/imgui/wiki/Debug-Tools
// - 术语表 https://github.com/ocornut/imgui/wiki/Glossary
// - 使用 Dear ImGui 的软件 https://github.com/ocornut/imgui/wiki/Software-using-dear-imgui
// - 问题反馈与支持 ........... https://github.com/ocornut/imgui/issues
// - 测试引擎与自动化 ... https://github.com/ocornut/imgui_test_engine (测试套件，用于实现应用自动化的测试引擎)
// Demo 的网页版 .... https://pthom.github.io/imgui_manual_online/manual/imgui_manual.html（附带源码浏览器）


// 针对初次使用时遇到编译/链接/运行问题的用户：
// 如果在上述资源中找不到解决方案，请在 https://github.com/ocornut/imgui/discussions 中发帖。
// 其他所有问题都应在“Issues”中提问！我们正在那里建立一个交叉引用的知识库。
// 自 1.92 版本起，我们鼓励将字体加载相关问题也发布在“Issues”中。


// 版权所有 (c) 2014-2026 Omar Cornut
// 由 Omar Cornut 以及 GitHub 上的所有直接或间接贡献者开发。
// 有关版权和许可详情，请参阅 LICENSE.txt（标准 MIT 许可证）。
// 本库免费，但需要您的支持以维持开发和维护。
// 企业用户：您可以通过 B2B 开票技术支持、维护和赞助合同来支持持续开发。
// 请通过 omar AT dearimgui DOT com 与我联系。详见 https://github.com/ocornut/imgui/wiki/Funding
// 企业用户：您还可以购买 Dear ImGui Automation/Test Engine 的许可证。


// 建议不要修改 imgui.cpp！否则后续更新库文件会变得非常困难。
// 请注意，由于 'ImGui::' 是一个命名空间，你可以在自己的源文件中向该命名空间添加函数，而无需
// 修改 imgui.h 或 imgui.cpp。你可以包含 imgui_internal.h 来访问内部数据结构，但这
// 并不保证向后兼容性。在 GitHub Issue Tracker 上讨论你的更改可能会让你
// 以寻求更好的解决方案或官方支持。


/*


本文档索引：


文档说明


- 使命宣言
- 控制指南
- 程序员指南
- 必读说明
- 如何更新至新版本的 Dear ImGui
- 如何开始在你的代码/引擎中集成 Dear ImGui
- 一个简单的应用程序示例
- 使用自定义后端 / 自定义引擎
- API 重大变更（更新时请阅读！）
- 常见问题解答 (FAQ)
- 在线阅读所有答案：https://www.dearimgui.com/faq，或查看 docs/FAQ.md（使用 Markdown 查看器）


代码
（在代码中搜索 "[SECTION]" 以查找相关内容）


// [SECTION] 包含文件 (INCLUDES)
// [SECTION] 前向声明 (FORWARD DECLARATIONS)
// [SECTION] 上下文与内存分配器 (CONTEXT AND MEMORY ALLOCATORS)
// [SECTION] 面向用户的结构体 (ImGuiStyle, ImGuiIO, ImGuiPlatformIO)
// [章节] 杂项辅助/工具函数 (几何函数)
// [章节] 杂项辅助/工具函数 (字符串、格式化、哈希函数)
// [章节] 杂项辅助/工具函数 (文件函数)
// [章节] 杂项辅助/工具函数 (ImText* 函数)
// [SECTION] 杂项辅助/实用工具 (颜色函数)
// [SECTION] ImGuiStorage
// [SECTION] ImGuiTextFilter
// [SECTION] ImGuiTextBuffer, ImGuiTextIndex
// [SECTION] ImGuiListClipper
// [SECTION] STYLING (样式)
// [SECTION] RENDER HELPERS (渲染辅助函数)
// [SECTION] INITIALIZATION, SHUTDOWN (初始化、销毁)
// [SECTION] 核心代码 (大部分代码！内容繁多，需要整理！)
// [SECTION] 字体、纹理
// [SECTION] ID 栈
// [SECTION] 输入
// [SECTION] 错误检查、状态恢复
// [SECTION] 项目提交
// [SECTION] 布局
// [SECTION] 滚动
// [SECTION] 工具提示 (TOOLTIPS)
// [SECTION] 弹出窗口 (POPUPS)
// [SECTION] 窗口焦点 (WINDOW FOCUS)
// [SECTION] 键盘/手柄导航 (KEYBOARD/GAMEPAD NAVIGATION)
// [SECTION] 拖放 (DRAG AND DROP)
// [SECTION] 日志记录/捕获 (LOGGING/CAPTURING)
// [SECTION] 设置 (SETTINGS)
// [SECTION] 本地化 (LOCALIZATION)
// [章节] 视口, 平台窗口
// [章节] 平台相关辅助函数
// [章节] 指标/调试器窗口
// [章节] 调试日志窗口
// [SECTION] 其他调试工具 (物品选择器, ID 堆栈工具)


*/


//-----------------------------------------------------------------------------
// 文档
//-----------------------------------------------------------------------------


/*


使命宣言
=================


- 易于使用，可用于创建代码驱动和数据驱动的工具。
- 易于使用，既能创建即用的临时短期工具，也能构建更复杂的长期工具。
- 易于修改和改进。
- 最大程度减少设置和维护工作。
- 最大程度减少用户侧的状态存储。
- 最小化状态同步。
- 便携、最小化依赖，可在目标设备（控制台、手机等）上运行。
- 高效的运行时性能和内存消耗。


主要为开发者和内容创作者设计，而非针对普通终端用户！
目前的一些不足之处（我们计划在未来解决）包括：


- 默认外观不够华丽。
- 布局功能有限，复杂的布局通常需要在代码中精心构建。


控件指南
==============


- 鼠标控制
- 鼠标滚轮：垂直滚动。
- Shift+鼠标滚轮：水平滚动。
- 点击 [X]：关闭窗口，当向 ImGui::Begin() 传递 'bool* p_open' 参数时可用。
- 点击 ^，双击标题栏：折叠窗口。
- 拖动角落/边缘：调整窗口大小（双击可使窗口自动适应其内容）。
- 拖动任意空白区域：移动窗口（除非 io.ConfigWindowsMoveFromTitleBarOnly = true）。
- 在弹窗外点击左键：关闭弹窗栈（在底层弹窗上点击右键：部分关闭弹窗栈）。


- 文本编辑器
- 按住 Shift 或拖动鼠标：选择文本。
- Ctrl+左/右方向键：单词跳转。
- Ctrl+Shift+左/右方向键：选择单词。
- Ctrl+A 或双击：全选。
- Ctrl+X, Ctrl+C, Ctrl+V：使用系统剪贴板。
- Ctrl+Z：撤销。
- Ctrl+Y 或 Ctrl+Shift+Z：重做。
- ESCAPE：将文本还原为原始值。
- 在 macOS 上，控件会自动调整以符合标准的 macOS 文本编辑和行为习惯。
（对于 99% 的快捷键，macOS 上的 Ctrl 键会被替换为 Cmd 键）。


- 键盘控制
- 基础：
- Tab, Shift+Tab：在可编辑文本字段间循环切换。
- Ctrl+Tab, Ctrl+Shift+Tab：在窗口间循环切换。
- Ctrl+左键点击：在滑块（Slider）或拖动（Drag）控件中输入文本。
- 通过 `io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard` 开启扩展功能：
- Tab, Shift+Tab：循环切换所有控件。
- 方向键：使用方向导航移动控件。调整数值。
- 方向键 + Alt, Shift：更慢或更快地调整数值（使用方向键时）。
- Enter 激活项目（尽可能优先进行文本输入）。
- Space 激活项目（尽可能优先使用方向键调整）。
- Escape 取消激活项目、退出子窗口、关闭弹窗。
- Page Up, Page Down 上一页，下一页。
- Home, End 滚动至顶部，滚动至底部。
- Alt 在滚动层和菜单层之间切换。
- Ctrl+Tab 后按 Ctrl+方向键 移动窗口。按住 Shift 可调整大小而非移动。
- 当设置了 ImGuiConfigFlags_NavEnableKeyboard 时的输出，
- 当键盘被占用时，会设置 io.WantCaptureKeyboard 标志。
- io.NavActive：当一个窗口获得焦点且未设置 ImGuiWindowFlags_NoNavInputs 标志时为 true。
- io.NavVisible：当导航光标可见时为 true（通常在使用鼠标时会恢复为 false）。


- 游戏手柄控制
- 通过 `io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad` 启用。
- 特别适用于在没有鼠标的游戏机系统（如 PlayStation、Switch、Xbox）上使用 Dear ImGui！
- 请访问 http://dearimgui.com/controls_sheets 下载控制器映射的 PNG/PSD 文件。
- 后端支持：后端需要：
- 设置 `io.BackendFlags |= ImGuiBackendFlags_HasGamepad`，并使用 ImGuiKey_Gamepad_XXX 键位调用 `io.AddKeyEvent/AddKeyAnalogEvent()`。
- 对于模拟量数值（0.0f 到 1.0f），后端负责处理死区并相应地重新缩放输入。
后端代码可能需要转换您的原始输入（例如，将 0.2..0.9 的原始输入范围重新映射到 0.0..1.0 的 imgui 范围等）。
- 如果您需要在游戏和 Dear ImGui 界面之间共享输入，最简单的方法是采取“全有或全无”的策略，
通过组合键来切换目标。如果您认为游戏输入与导航输入之间的共享机制有待改进，请联系我们。


- 远程输入共享与鼠标模拟
- PS4/PS5 用户：考虑使用 DualShock 触摸板模拟鼠标光标，或将备用的模拟摇杆作为鼠标模拟的备选方案。
- 主机/平板/手机用户：考虑使用 Synergy 1.x 服务器（在您的 PC 上）+ 运行 examples/libs/synergy/uSynergy.c（在您的主机/平板/手机应用上）
以便共享您的电脑鼠标/键盘。
- 访问 https://github.com/ocornut/imgui/wiki/Useful-Extensions#remoting 查看其他远程解决方案。
- 在可读性较低或鼠标输入不便的电视/游戏机系统中，您可能需要设置 io.ConfigNavMoveSetMousePos 标志。
启用 io.ConfigNavMoveSetMousePos + ImGuiBackendFlags_HasSetMousePos 会指示 Dear ImGui 让鼠标光标随导航移动而移动。
启用后，NewFrame() 函数可能会修改 'io.MousePos' 并设置 'io.WantSetMousePos'，以通知您它希望移动鼠标光标。
当这种情况发生时，您的后端需要在下一帧移动操作系统或底层的鼠标光标。examples/ 目录中的一些后端已经实现了此功能。
（如果您设置了 NavEnableSetMousePos 标志，但没有正确响应 'io.WantSetMousePos'，Dear ImGui 将会出现异常行为，因为它会检测到您的鼠标在来回移动！）
（在您可能无法轻松控制鼠标光标的设置中，例如 uSynergy.c 没有公开移动远程鼠标光标的接口，您可能希望
设置一个布尔值，以忽略其他外部鼠标位置，直到外部源再次移动为止。）


程序员指南
================


必读事项
----------
- 记得查看精彩的 Wiki：https://github.com/ocornut/imgui/wiki
- 您的代码在应用程序循环的每一帧中创建 UI，如果您的代码不运行，UI 就会消失！
UI 可以是高度动态的，没有构造或销毁步骤，减少了多余的
减少您方的数据保留，减少状态重复，减少状态同步，减少错误。
- 调用并阅读 `ImGui::ShowDemoWindow()` 以获取演示大部分功能的示例代码。
或者访问 https://pthom.github.io/imgui_manual_online/manual/imgui_manual.html 查看交互式网页版。
- 本库旨在通过源码构建。请避免使用预编译的二进制文件和打包版本。请参阅 imconfig.h 以配置您的构建。
- Dear ImGui 是 IMGUI 范式（即时模式图形用户界面，由 Casey Muratori 提出）的一种实现。
您可以在 http://www.johno.se/book/imgui.html、http://mollyrocket.com/861 以及 Wiki 中的更多链接了解 IMGUI 的原理。
- Dear ImGui 是 IMGUI（即时模式图形用户界面）范式的一种“单次传递”光栅化实现，旨在易于使用且具备高性能。
在应用程序的每一帧中，您的 UI 代码仅会被调用一次。这与 Unity 等引擎的 IMGUI 实现形成了对比，
在后者的实现中，UI 代码会从单个入口点被多次调用（“多次传递”）。这两种方法各有优劣。
- 我们的坐标原点位于左上角。在轴对齐包围盒（AABB）中，Min 代表左上角，Max 代表右下角。
- 请确保你已启用断言（IM_ASSERT 默认重定向到 assert()，但也可以重定向到其他位置）。
如果触发了断言，请阅读该断言周围的消息和注释。
- 本代码库旨在实现高度优化：
- 典型的空闲帧不应调用 malloc/free。
- 我们尽可能依赖常数时间或 O(N) 算法。最大限度地减少搜索和扫描操作。
- 我们投入了大量精力，以确保在典型的“Debug”构建设置下也能拥有良好的性能。
这意味着我们倾向于避免过度依赖“零成本抽象”，因为它们在调试模式下并非真的零成本。
- 本代码库旨在同时兼具高度的主见性和高度的灵活性：
- 这段代码之所以有效，是因为它对需要解决和无需解决的问题做出了取舍。
- C++：这是一个务实的类 C 风格代码库：我们不使用花哨的 C++ 特性，不包含 C++ 标准库头文件，
且 ImGui:: 是一个命名空间。我们极少使用成员函数（即便偶尔使用了，我现在也大多感到后悔）。
这样做是为了提高兼容性、增强可维护性，并方便其他语言调用。
- C++：ImVec2/ImVec4 默认不提供数学运算符，因为预期你会使用自己的数学类型。
有关如何为此设置 imconfig.h 的详细信息，请参阅常见问题解答（FAQ）中的“如何使用我自己的数学类型代替 ImVec2/ImVec4？”。
我们可以选择使用 IMGUI_DEFINE_MATH_OPERATORS 来导出 ImVec2/ImVec4 的数学运算符，我们在内部也会使用这些运算符。
- C++：请注意 ImVector<> 操作的是简单原始数据（POD），不遵循构造/析构函数。
（因此请勿在您的代码中使用 ImVector，否则后果自负！）。
- 构建：我们不对主库使用或强制要求特定的构建系统。
这是为了确保它能在现实世界中运行，即兼容任何奇特的构建设置。
这也是因为为主库提供构建系统几乎没有价值。
编译问题几乎从不源自库本身，而是源自特定的后端。


如何更新到新版本的 DEAR IMGUI
----------------------------------------------
- 更新子模块或复制/覆盖所有文件。
- 关于 imconfig.h：
- 你可以修改你本地的 imconfig.h 副本，在这种情况下请不要覆盖它。
- 或者你可以通过本地分支来修改 imconfig.h，并合并/变基到最新版本。
- 或者你可以在构建系统中全局定义 '#define IMGUI_USER_CONFIG "my_config_file.h"'，以便
为你的 imconfig.h 文件指定一个自定义路径，从而无需修改默认文件。


- 覆盖除 imconfig.h 以外的所有源文件（如果你修改过自己的 imconfig.h 副本）。
- 或者维护你自己的分支，将修改后的 imconfig.h 作为最顶层的提交，以便你可以定期在 "master" 分支上进行变基（rebase）。
- 你也可以使用 '#define IMGUI_USER_CONFIG "my_config_file.h"' 将配置重定向到你自己的文件。
- 阅读“API 破坏性变更”（API BREAKING CHANGES）章节（见下文）。这里列出了偶尔出现的 API 破坏性变更。
如果某个函数/类型已被重命名或标记为废弃，请在它从公共 API 中永久移除之前，尝试在代码中修正其名称。
如果您遇到函数/符号缺失的问题，请在代码中搜索其名称，通常会有相关的注释说明。
请向 GitHub 页面报告任何问题！
- 若要查找旧版 API 的使用情况，您可以在配置文件中添加 '#define IMGUI_DISABLE_OBSOLETE_FUNCTIONS'。
- 尽量保持你所使用的 Dear ImGui 版本处于较新的状态！


开始将 DEAR IMGUI 集成到你的代码/引擎中
---------------------------------------------------------------
- 参阅 https://github.com/ocornut/imgui/wiki/Getting-Started。
- 运行并研究 imgui_demo.cpp 中的示例和演示，以熟悉该库。
- 在大多数情况下，你应该能够直接使用 backends/ 文件夹中提供的未经修改的后端文件。
- 将 Dear ImGui 源文件以及所选的后端源文件添加到你的项目中，或使用你偏好的构建系统进行管理。
建议将这些 .cpp 文件作为项目的一部分进行编译并静态链接，而不是将其作为共享库（DLL）。
- 稍后你可以自定义 imconfig.h 文件来调整某些编译时行为，例如将 Dear ImGui 的类型与你自己的数学类型集成。
- 使用 Dear ImGui 时，你的编程 IDE 就是你的好帮手：通过跳转查看变量、函数和类型的声明，可以找到相关的注释说明。
- Dear ImGui 永远不会触碰或了解你的 GPU 状态。唯一了解 GPU 的函数是你提供的渲染函数。
实际上，这意味着你可以在代码中的任何时间创建控件，而无需考虑应用程序处于“更新”还是“渲染”阶段。
所有的渲染信息都存储在命令列表中，你可以在调用 ImGui::Render() 后获取这些列表。
- 请参考 examples/ 文件夹中的后端和演示程序，了解如何设置代码。
- 如果您是在运行带有通用图形 API 的标准操作系统上，应该可以直接使用 examples/ 文件夹中未经修改的 imgui_impl_*** 文件。


一个简单的应用程序可能是什么样的
--------------------------------------


使用示例后端（即 backends/ 文件夹中的 imgui_impl_XXX.cpp 文件）。
examples/ 目录下的子文件夹包含了遵循此结构的示例应用程序。


// 应用程序初始化：创建 dear imgui 上下文，设置选项，加载字体
ImGui::CreateContext();
ImGuiIO& io = ImGui::GetIO();
// TODO: 设置可选的 io.ConfigFlags 值，例如使用 'io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard' 来启用键盘控制。
// TODO: 稍后填充 io 结构的可选字段。
// TODO: 如果不想使用默认字体，请加载 TTF/OTF 字体。


// 初始化辅助平台和渲染器后端（此处我们使用的是 imgui_impl_win32.cpp 和 imgui_impl_dx11.cpp）
ImGui_ImplWin32_Init(hwnd);
ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);


// 应用程序主循环
while (true)
{
// 向 dear imgui 传递输入，开始新帧
ImGui_ImplDX11_NewFrame();
ImGui_ImplWin32_NewFrame();
ImGui::NewFrame();


// 此处为任意应用程序代码
ImGui::Text("你好，世界！");


// 将 dear imgui 渲染至帧缓冲
ImGui::Render();
ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
g_pSwapChain->Present(1, 0);
}


// 关闭
ImGui_ImplDX11_Shutdown();
ImGui_ImplWin32_Shutdown();
ImGui::DestroyContext();


要决定是将鼠标/键盘输入分发给 Dear ImGui 还是应用程序的其他部分，
你应该读取 'io.WantCaptureMouse'、'io.WantCaptureKeyboard' 和 'io.WantTextInput' 标志！
请阅读 FAQ 中的条目“如何判断应该将鼠标/键盘输入发送给 Dear ImGui 还是我的应用程序？”以了解相关信息。


使用自定义后端 / 自定义引擎
------------------------------------


实现您的平台后端：
-> 请参阅 https://github.com/ocornut/imgui/blob/master/docs/BACKENDS.md 获取基础说明。
-> impl_impl_XXX.cpp 文件中的平台后端包含许多实现。


实现你的 RenderDrawData() 函数：
-> 参见 https://github.com/ocornut/imgui/blob/master/docs/BACKENDS.md
-> impl_impl_XXX.cpp 文件中的渲染器后端包含 ImGui_ImplXXXX_RenderDrawData() 函数的多种实现。


实现对 ImGuiBackendFlags_RendererHasTextures 的支持：
-> 参见 https://github.com/ocornut/imgui/blob/master/docs/BACKENDS.md
-> imgui_impl_XXX.cpp 文件中的渲染器后端包含了许多 ImGui_ImplXXXX_UpdateTexture() 函数的实现。


基础应用程序/后端骨架：


// 应用程序初始化：创建 Dear ImGui 上下文，设置选项，加载字体
ImGui::CreateContext();
ImGuiIO& io = ImGui::GetIO();
// TODO: 设置 io.ConfigXXX 的值，例如：
io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // 启用键盘控制


// TODO: 如果不想使用默认字体，请加载 TTF/OTF 字体。
io.Fonts->AddFontFromFileTTF("NotoSans.ttf");


// 应用程序主循环
while (true)
{
// 设置底层输入，例如在 Win32 上：调用 GetKeyboardState()，或者通过 Windows 消息处理器向这些字段写入数据等。
//（在 examples/ 示例程序中，这通常是在演示平台后端提供的 ImGui_ImplXXX_NewFrame() 函数内完成的）
io.DeltaTime = 1.0f/60.0f; // 设置自上一帧以来经过的时间（以秒为单位）
io.DisplaySize.x = 1920.0f; // 设置当前显示宽度
io.DisplaySize.y = 1280.0f; // 在此处设置当前显示高度
io.AddMousePosEvent(mouse_x, mouse_y); // 更新鼠标位置
io.AddMouseButtonEvent(0, mouse_b[0]); // 更新鼠标按键状态
io.AddMouseButtonEvent(1, mouse_b[1]); // 更新鼠标按键状态


// 调用 NewFrame()，在此之后你可以随时使用 ImGui::* 函数
//（因此，你应该尽可能在主循环的早期调用 NewFrame()，以便在任何地方都能使用 Dear ImGui）
ImGui::NewFrame();


// 此处编写大部分应用程序代码
ImGui::Text("你好，世界！");
MyGameUpdate(); // 可以使用任何 Dear ImGui 函数，例如 ImGui::Begin("我的窗口"); ImGui::Text("你好，世界！"); ImGui::End();
MyGameRender(); // 同样可以使用任何 Dear ImGui 函数！


// 结束 dear imgui 帧
//（你应该尽量晚地调用 EndFrame/Render，以便在自己的游戏渲染代码中使用 Dear ImGui）
ImGui::EndFrame(); // 该函数会被 Render() 自动调用，但也可以手动调用
ImGui::Render();


// 更新纹理
ImDrawData* draw_data = ImGui::GetDrawData();
for (ImTextureData* tex : *draw_data->Textures)
if (tex->Status != ImTextureStatus_OK)
MyImGuiBackend_UpdateTexture(tex);


// 渲染 dear imgui 内容，交换缓冲区
MyImGuiBackend_RenderDrawData(draw_data);
SwapBuffers();
}


// 关闭
ImGui::DestroyContext();



API 重大变更
====================


偶尔会引入破坏 API 兼容性的变更。我们尽量使这些破坏保持在较小范围内，并易于修复。
以下是仅针对 API 破坏性变更的更新日志。如果你正在使用列出的任何函数，请准备好修复相关代码。
如果你不确定某个旧符号或函数名，请尝试使用 IDE 的搜索/查找功能，在所有 imgui 文件中查找相关的注释或引用。
你可以阅读发布日志 https://github.com/ocornut/imgui/releases 以获取更多详情。


- 2026/01/08 (1.92.6) - 注释掉了在 1.90 版本（2023 年 9 月）中废弃的旧名称：'BeginChildFrame()' --> 使用带有 'ImGuiChildFlags_FrameStyle' 的 'BeginChild()'。'EndChildFrame()' --> 'EndChild()'。'ShowStackToolWindow()' --> 'ShowIDStackToolWindow()'。'IM_OFFSETOF()' --> 'offsetof()'。
- 2026/01/07 (1.92.6) - 弹出窗口：将 BeginPopupContextItem()、BeginPopupContextWindow()、BeginPopupContextVoid()、OpenPopupOnItemClick() 的编译时默认值从 `ImGuiPopupFlags popup_flags = 1` 修改为 `= 0`。默认值的实际含义在修改前后保持一致。
- 如有任何疑问，请参阅 GitHub 话题 #9157。
- 在此版本之前，这些函数在其函数签名中使用了 `ImGuiPopupFlags popup_flags = 1` 作为默认值。
显式传递字面量 0 代表 ImGuiPopupFlags_MouseButtonLeft。默认的字面量 1 代表 ImGuiPopupFlags_MouseButtonRight。
这一变化源于 2020/06/23 (1.77) 的一次改动，当时将函数签名从 `int mouse_button` 更改为 `ImGuiPopupFlags popup_flags`，并试图保留当时的旧版行为。
我们现在更改了这一行为，以清理一个非常古老的 API 缺陷，方便绑定库的使用，并移除最后一个且容易出错的非零默认值。
此外，我们也认为使用鼠标左键调用这些辅助函数的情况极其罕见！因为使用左键通常是通过另一个控件触发的，例如：Button() + OpenPopup()/BeginPopup() 调用。
- 之前：默认值 = 1 代表 ImGuiPopupFlags_MouseButtonRight。显式传递字面量 0 代表 ImGuiPopupFlags_MouseButtonLeft。
- 变更后：默认值 0 代表 ImGuiPopupFlags_MouseButtonRight。显式传递字面量 1 同样代表 ImGuiPopupFlags_MouseButtonRight（如果启用了旧版行为），否则将触发断言（如果禁用了旧版行为）。
- 简而言之：如果你不想使用鼠标右键触发弹出窗口，请务必使用命名的 ImGuiPopupFlags_MouseButtonXXXX 枚举值来显式指定。
回顾：
- BeginPopupContextItem("foo"); // 行为未改变（使用右键）
- BeginPopupContextItem("foo", ImGuiPopupFlags_MouseButtonLeft); // 行为未改变（使用左键）
- BeginPopupContextItem("foo", ImGuiPopupFlags_MouseButtonLeft | xxx); // 行为保持不变（使用左键 + 标志位）
- BeginPopupContextItem("foo", ImGuiPopupFlags_MouseButtonRight | xxx); // 行为保持不变（使用右键 + 标志位）
- BeginPopupContextItem("foo", 1); // 行为未改变（出于兼容性考虑，我们将 1 解释为 ImGuiPopupFlags_MouseButtonRight，如果禁用旧版行为则会触发断言）。
- BeginPopupContextItem("foo", 0); // !! 行为已更改 !! 原为左键，现在默认为右键！ --> 请使用 ImGuiPopupFlags_MouseButtonLeft。
- BeginPopupContextItem("foo", ImGuiPopupFlags_NoReopen); // !! 行为已更改 !! 原为左键 + 标志，现在默认为右键！ --> 请使用 ImGuiPopupFlags_MouseButtonLeft | xxx。
- 2025/12/23 (1.92.6) - 字体：AddFontDefault() 现在会自动在新的可缩放 AddFontDefaultVector() 和经典的像素级清晰 AddFontDefaultBitmap() 之间选择嵌入字体。
默认选择基于 (style.FontSizeBase * FontScaleMain * FontScaleDpi) 达到一个较小的阈值。建议根据您自己的逻辑调用其中之一。您可以调用 AddFontDefaultBitmap() 以确保旧版行为。
- 2025/12/23 (1.92.6) - 字体：移除了 1.92 中添加的 ImFontConfig::PixelSnapV，事实证明该项是不必要的（且文档有误）。缩放后的 GlyphOffset 始终会被取整。
- 2025/12/17 (1.92.6) - 重命名了辅助宏 IM_ARRAYSIZE() -> IM_COUNTOF()。目前保留了重定向/旧名称。
- 2025/12/11 (1.92.6) - 哈希：处理字符串标识符中用于重置种子的 "###" 运算符时，输出哈希中不再包含 "###" 字符本身。
- 变更前：GetID("Hello###World") == GetID("###World") != GetID("World");
- 变更后：GetID("Hello###World") == GetID("###World") == GetID("World");
- 此项特性便于使用 "###" 拼接和处理标识符，并将允许修复其他悬而未决的问题。
- 这将导致使用了 "###" 操作符的表格（Tables）和窗口（Windows）的哈希值（存储在 .ini 数据中）失效。(#713, #1698)
- 2025/11/24 (1.92.6) - 字体：修复了对 `ImFontConfig::FontDataOwnedByAtlas = false` 的处理，该问题曾导致错误地复制字体数据，从根本上违背了此标志的设计初衷并浪费了内存。
（琐事：自 2015 年 7 月以来一直未被发现，这可能是 Dear ImGui 历史上存在时间最长的 Bug，尽管它涉及的是一个很少使用的功能，详见 #9086）
然而，修复此 Bug 可能会暴露用户代码在使用 `FontDataOwnedByAtlas = false` 时存在的潜在问题。
- 在 1.92 版本之前，字体数据仅需在调用 atlas->AddFontXXX() 期间可用。
- 自 1.92 版本起，字体数据需要保持可用，直到调用 `atlas->RemoveFont()`，或者更常见的情况是直到所属上下文或字体图集关闭。
- 事实上，由于 `FontDataOwnedByAtlas = false` 的处理机制曾存在缺陷，反而完全绕过了这个问题。
- 2025/11/06 (1.92.5) - BeginChild：注释掉了一些在 1.90.0（2023 年 11 月）、1.90.9（2024 年 7 月）、1.91.1（2024 年 8 月）版本中已废弃的旧名称：
- ImGuiChildFlags_Border --> ImGuiChildFlags_Borders
- ImGuiWindowFlags_NavFlattened --> ImGuiChildFlags_NavFlattened（已移至 ImGuiChildFlags）。BeginChild(name, size, 0, ImGuiWindowFlags_NavFlattened) --> BeginChild(name, size, ImGuiChildFlags_NavFlattened, 0)
- ImGuiWindowFlags_AlwaysUseWindowPadding --> ImGuiChildFlags_AlwaysUseWindowPadding（已移至 ImGuiChildFlags）。BeginChild(name, size, 0, ImGuiWindowFlags_AlwaysUseWindowPadding) --> BeginChild(name, size, ImGuiChildFlags_AlwaysUseWindowPadding, 0)
- 2025/11/06 (1.92.5) - 按键：注释掉了在 1.89.0（2022年8月）中已废弃的旧名称：
- ImGuiKey_ModCtrl --> ImGuiMod_Ctrl
- ImGuiKey_ModShift --> ImGuiMod_Shift
- ImGuiKey_ModAlt --> ImGuiMod_Alt
- ImGuiKey_ModSuper --> ImGuiMod_Super
- 2025/11/06 (1.92.5) - IO：注释掉了在 1.89.8（2023 年 8 月）中已废弃的旧版 io.ClearInputCharacters()。现在只需调用 io.ClearInputKeys() 即可。
- 2025/11/06 (1.92.5) - 注释掉了在 1.89.7 中废弃的旧版 SetItemAllowOverlap()：该函数从未正常工作过。请改在控件_之前_使用 SetNextItemAllowOverlap()。
- 2025/10/14 (1.92.4) - TreeNode, Selectable, Clipper：注释掉了在 1.89.7（2023 年 7 月）和 1.89.9（2023 年 9 月）中废弃的旧名称；
- ImGuiTreeNodeFlags_AllowItemOverlap --> ImGuiTreeNodeFlags_AllowOverlap
- ImGuiSelectableFlags_AllowItemOverlap --> ImGuiSelectableFlags_AllowOverlap
- ImGuiListClipper::IncludeRangeByIndices() --> ImGuiListClipper::IncludeItemsByIndex()
- 2025/08/08 (1.92.2) - 后端：SDL_GPU3：将 ImTextureID 类型从 SDL_GPUTextureSamplerBinding* 更改为 SDL_GPUTexture*，这更符合直觉且更易于用户管理。如果您需要更改当前的采样器，可以访问 ImGui_ImplSDLGPU3_RenderState 结构体。(#8866, #8163, #7998, #7988)
- 2025/07/31 (1.92.2) - 选项卡：将 ImGuiTabBarFlags_FittingPolicyResizeDown 重命名为 ImGuiTabBarFlags_FittingPolicyShrink。保留了内联重定向枚举（即将废弃）。
- 2025/06/25 (1.92.0) - 布局：注释掉了在 1.89 版本（2022 年 8 月）中已废弃的旧版 ErrorCheckUsingSetCursorPosToExtendParentBoundaries() 回退机制，该机制曾允许在“没有控件”的情况下调用 SetCursorPos()/SetCursorScreenPos()
用于扩展父窗口/单元格边界。现已替换为断言/工具提示，如果之前使用了 IMGUI_DISABLE_OBSOLETE_FUNCTIONS，这些提示本就会出现。(#5548, #4510, #3355, #1760, #1490, #4152, #150)
- 使窗口内容尺寸达到 200x200 的错误方式：
Begin(...) + SetCursorScreenPos(GetCursorScreenPos() + ImVec2(200,200)) + End();
- 使窗口内容尺寸达到 200x200 的正确方式：
Begin(...) + SetCursorScreenPos(GetCursorScreenPos() + ImVec2(200,200)) + Dummy(ImVec2(0,0)) + End();
Begin(...) + Dummy(ImVec2(200,200)) + End();
- 简而言之：如果触发了断言，你可以添加一个 Dummy({0,0}) 调用来验证父级边界的扩展。
- 2025/06/11 (1.92.0) - 此版本包含自 2015 年以来最大规模的重大变更（Breaking Changes）！我已竭尽全力将其降至最低并减少干扰，但不可避免地仍会有部分用户受到影响。
为了帮助我们改进过渡流程（包括文档和注释），请将**任何**疑问、困惑、问题或反馈提交至：https://github.com/ocornut/imgui/issues/
作为减少 API 破坏性变更影响计划的一部分，若干与字体和文本系统及缩放相关的未完成变更/功能/重构，将在后续版本（1.92.1+）中陆续推出。
如果您是从旧版本进行更新，且预计会面临大规模或困难的更新，请考虑先更新到 1.91.9 版本以减少变更量。
- 阅读困难？请参阅“docs/Changelog.txt”获取排版更宽松、内容更完整的版本！
- 字体：**重要提示**：如果您的应用程序之前通过设置 `io.DisplayFramebufferScale`（例如设为 2.0f）+ 设置 `io.FontGlobalScale`（例如设为 1.0f/2.0f）+ 以缩放后的尺寸加载字体（例如尺寸 X * 2.0f）来解决 OSX/iOS Retina 屏幕特有的逻辑缩放与显示缩放问题：
这在旧系统中**无法**正确映射！因为字体将按请求的尺寸进行光栅化。
- 使用旧版后端（< 1.92）：不要设置 `io.FontGlobalScale = 1.0f/N` -> 而是设置 `ImFontCfg::RasterizerDensity = N`。这在以前就已经可以使用，但现在几乎是必须的。
- 使用新版后端（1.92+）：这一切都应该是自动的。`FramebufferScale` 会自动用于设置当前字体的 `RasterizerDensity`。在 'docking' 分支中，`FramebufferScale` 是由后端通过 `Platform_GetWindowFramebufferScale()` 句柄提供的每个视口（per-viewport）属性。
- 字体：**重要**关于字体大小：在 1.92 版本之前，字体只有单一尺寸。现在它们可以动态调整大小。
- PushFont() API 现在包含一个必填的大小参数。
- 1.92 版本之前：PushFont() 始终使用 AddFont() 调用中指定的字体“默认”大小。这相当于调用 PushFont(font, font->LegacySize)。
- 自 1.92 版本起：PushFont(font, 0.0f) 会保留当前的字体大小（这是一个共享值）。
- 若要使用旧行为：请在调用处使用 `ImGui::PushFont(font, font->LegacySize)`。
- 保留了内联单参数函数。即将废弃。
- 字体：关于字体合并的**重要提示**：
- 在多个合并字体中搜索字符（glyph）时：我们将搜索包含目标字符的第一个（FIRST）字体源。
由于用户不再需要提供字符范围（glyph ranges），原本你期望从次要/合并的图标字体中获取的字符，现在可能会错误地从主要字体中获取。
- 在多个合并字体中搜索字符时：我们现在会搜索包含目标字符的“第一个”字体源。从技术上讲，这与之前的行为有所不同！
- 例如：如果你正在合并字体，某些你期望从“字体源 2”加载的字符，可能在“字体源 1”中也存在。
在更新并使用新后端后，这些字符现在可能会从“字体源 1”中加载！
- 我们添加了 `ImFontConfig::GlyphExcludeRanges[]`，用于指定从给定字体源中排除的范围：
// 添加字体源 1，但忽略 ICON_MIN_FA..ICON_MAX_FA 范围
static ImWchar exclude_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
ImFontConfig cfg1;
cfg1.GlyphExcludeRanges = exclude_ranges;
io.Fonts->AddFontFromFileTTF("segoeui.ttf", 0.0f, &cfg1);
// 添加字体源 2，该源预期使用上述范围
ImFontConfig cfg2;
cfg2.MergeMode = true;
io.Fonts->AddFontFromFileTTF("FontAwesome4.ttf", 0.0f, &cfg2);
- 您可以使用 `Metrics/Debugger->Fonts->Font->Input Glyphs Overlap Detection Tool` 来查看多个字体源中可用的字形列表。这有助于了解哪个字体输入提供了哪个字形。
- 字体：关于线程安全的**重要提示**：
- 少数函数（如 font->CalcTextSizeA()）此前纯属侥幸（即偶然地）具备线程安全性，尽管我们从未提供过此类保证。由于现在可能会加载新的字形，这些函数已明确不再具备线程安全性。
- 字体：ImFont::FontSize 已被移除且不再具有实际意义。ImFont::LegacySize 是传递给 AddFont() 的尺寸。
- 字体：移除了对 PushFont(NULL) 的支持，该写法此前是“默认字体”的快捷方式。
- 字体：将 'io.FontGlobalScale' 重命名/移动至 'style.FontScaleMain'。
- 纹理：所有接受 'ImTextureID' 参数的 API 函数现在都改为接受 'ImTextureRef'。受影响的函数包括：ImGui::Image()、ImGui::ImageWithBg()、ImGui::ImageButton()、ImDrawList::AddImage()、ImDrawList::AddImageQuad()、ImDrawList::AddImageRounded()。
- 字体：废弃了 ImFontAtlas::GetTexDataAsRGBA32()、GetTexDataAsAlpha8()、Build()、SetTexID()、IsBuilt() 函数。后端处理纹理的新协议不再需要这些函数。目前保留了重定向函数（后续将彻底废弃）。
- 字体：自 v1.91.8 起，ImFontConfig::OversampleH/OversampleV 默认设为自动（== 0）。在决定是否提供更精细的策略表达方式之前，保持其为自动状态非常重要，否则在使用大字符时可能会浪费纹理空间。请注意，imgui_freetype 后端不使用也不需要过采样（oversampling）。
- 字体：现在无需指定字符范围（glyph ranges）。ImFontConfig::GlyphRanges[] 的值仅对旧版后端有用。所有 GetGlyphRangesXXXX() 函数现在都已标记为废弃：GetGlyphRangesDefault()、GetGlyphRangesGreek()、GetGlyphRangesKorean()、GetGlyphRangesJapanese()、GetGlyphRangesChineseSimplifiedCommon()、GetGlyphRangesChineseFull()、GetGlyphRangesCyrillic()、GetGlyphRangesThai()、GetGlyphRangesVietnamese()。
- 字体：移除了 ImFontAtlas::TexDesiredWidth 以强制执行纹理宽度。(#327)
- 字体：如果你自行创建并管理 ImFontAtlas 实例（而不是依赖 ImGuiContext 创建），则需要自行调用 ImFontAtlasUpdateNewFrame()。如果不调用，将触发断言。
- 字体：废弃了 ImGui::SetWindowFontScale()，该函数已不再实用。建议使用 'PushFont(NULL, style.FontSizeBase * factor)' 或操作其他缩放因子。
- 字体：废弃了 ImFont::Scale，该属性已不再实用。
- 字体：对 ImFontAtlas 和 ImFont 的内部机制进行了全面重构。虽然理论上绝大多数用户不会受到影响，但某些特定用例或扩展可能会受到波及。主要变更包括：
- ImDrawCmd::TextureId 已更改为 ImDrawCmd::TexRef。
- ImFontAtlas::TexID 已更改为 ImFontAtlas::TexRef。
- ImFontAtlas::ConfigData[] 已重命名为 ImFontAtlas::Sources[]
- ImFont::ConfigData[] 和 ConfigDataCount 已重命名为 Sources[] 和 SourceCount。
- 每个 ImFont 拥有若干个 ImFontBaked 实例，对应于活跃使用的尺寸。ImFont::GetFontBaked(size) 用于检索给定尺寸的实例。
- 从 ImFont 移动到 ImFontBaked 的字段：IndexAdvanceX[]、Glyphs[]、Ascent、Descent、FindGlyph()、FindGlyphNoFallback()、GetCharAdvance()。
- 从 ImFontAtlas 移动到 ImFontAtlas->Tex 的字段：ImFontAtlas::TexWidth => TexData->Width，ImFontAtlas::TexHeight => TexData->Height，ImFontAtlas::TexPixelsAlpha8/TexPixelsRGBA32 => TexData->GetPixels()。
- 控件代码可以使用 ImGui::GetFontBaked() 代替 ImGui::GetFont()，以获取当前字体在当前字号下的字体数据（你也可以使用 font->GetFontBaked(size) 来获取任何其他字号的数据）。
- 字体：（imgui_freetype 用户）：将 ImFontAtlas::FontBuilderFlags 重命名为 ImFontAtlas::FontLoaderFlags。将 ImFontConfig::FontBuilderFlags 重命名为 ImFontConfig::FontLoaderFlags。将 ImGuiFreeTypeBuilderFlags 重命名为 ImGuiFreeTypeLoaderFlags。
如果你使用的是运行时 imgui_freetype 选择，而非默认的 IMGUI_ENABLE_FREETYPE 编译时选项：将 ImFontBuilderIO 重命名/重构为 ImFontLoader。将 ImGuiFreeType::GetBuilderForFreeType() 重命名为 ImGuiFreeType::GetFontLoader()。
- 旧代码：io.Fonts->FontBuilderIO = ImGuiFreeType::GetBuilderForFreeType()
- 新增：io.Fonts->FontLoader = ImGuiFreeType::GetFontLoader()
- 新增：io.Fonts->SetFontLoader(ImGuiFreeType::GetFontLoader()) 用于在运行时动态更改 [自 1.92.1 版本起]
- 字体：（自定义矩形的用户请参阅 #8466）：将 AddCustomRectRegular() 重命名为 AddCustomRect()。新增 GetCustomRect() 以替代 GetCustomRectByIndex() + CalcCustomRectUV()。
- GetCustomRect() 的输出类型现在为 ImFontAtlasRect，其中包含 UV 坐标。对应关系为：X->x，Y->y，Width->w，Height->h。
- 旧代码：
const ImFontAtlasCustomRect* r = atlas->GetCustomRectByIndex(custom_rect_id);
ImVec2 uv0, uv1;
atlas->GetCustomRectUV(r, &uv0, &uv1);
ImGui::Image(atlas->TexRef, ImVec2(r->w, r->h), uv0, uv1);
- 新建；
ImFontAtlasRect r;
atlas->GetCustomRect(custom_rect_id, &r);
ImGui::Image(atlas->TexRef, ImVec2(r.w, r.h), r.uv0, r.uv1);
- 我们添加了一个重定向的 typedef，但并未尝试对字段名进行自动重定向，因为该 API 很少被使用且修复方法很简单。
- 废弃了 AddCustomRectFontGlyph()，因为该 API 对可伸缩字体没有意义。保留了使用字体“默认大小”（Sources[0]->LegacySize）的现有函数。添加了一个辅助函数 AddCustomRectFontGlyphForSize()，虽然它被立即标记为废弃，但可以方便旧代码的过渡。
- 建议优先使用自定义/程序化加载器来添加字体源（ImFontConfig）。
- DrawList：将 ImDrawList::PushTextureID()/PopTextureID() 重命名为 PushTexture()/PopTexture()。
- 后端（Backends）：移除了所有包含 ImGui_ImplXXXX_CreateFontsTexture()/ImGui_ImplXXXX_DestroyFontsTexture() 的后端中的这些函数。它们不再是必需的。
- 2025/05/23 (1.92.0) - 字体（Fonts）：将 ImFont::CalcWordWrapPositionA() 更改为 ImFont::CalcWordWrapPosition()
- 旧版：const char* ImFont::CalcWordWrapPositionA(float scale, const char* text, ....);
- 新增：const char* ImFont::CalcWordWrapPosition (float size, const char* text, ....);
前置参数 `float scale` 已更改为 `float size`。此更改是必要的，因为 `scale` 假定使用标准字体大小，而我们计划在未来的更新中消除这一概念。保留了内联重定向函数。
- 2025/05/15 (1.92.0) - TreeNode：为了清晰起见，将 ImGuiTreeNodeFlags_NavLeftJumpsBackHere 重命名为 ImGuiTreeNodeFlags_NavLeftJumpsToParent。保留了内联重定向枚举（即将废弃）。
- 2025/05/15 (1.92.0) - 注释掉了在 1.89.4 中已废弃的 PushAllowKeyboardFocus()/PopAllowKeyboardFocus()。请改用 PushItemFlag(ImGuiItemFlags_NoTabStop, !tab_stop)/PopItemFlag()。(#3092)
- 2025/05/15 (1.92.0) - 注释掉了 ImGuiListClipper::ForceDisplayRangeByIndices()，该函数在 1.89.6 版本中已废弃。请改用 ImGuiListClipper::IncludeItemsByIndex()。
- 2025/03/05 (1.91.9) - BeginMenu()：内部机制：重构了菜单窗口的命名混淆方式，使用 "###Menu_00" 等代替 "##Menu_00"，从而允许在其中存储菜单名称。除非直接通过混淆后的名称访问菜单窗口，否则这不会影响现有代码。
- 2025/04/16 (1.91.9) - 内部机制：RenderTextEllipsis() 函数移除了紧接在 'float ellipsis_max_x' 之前的 'float clip_max_x' 参数。对于绝大多数用户来说，这两个值是相同的。(#8387)
- 2025/02/27 (1.91.9) - Image()：从 Image() 函数中移除了 'tint_col' 和 'border_col' 参数。添加了 ImageWithBg() 作为替代方案。(#8131, #8238)
- 旧版：void Image (ImTextureID tex_id, ImVec2 image_size, ImVec2 uv0 = (0,0), ImVec2 uv1 = (1,1), ImVec4 tint_col = (1,1,1,1), ImVec4 border_col = (0,0,0,0));
- 新版：void Image (ImTextureID tex_id, ImVec2 image_size, ImVec2 uv0 = (0,0), ImVec2 uv1 = (1,1));
- 新版：void ImageWithBg(ImTextureID tex_id, ImVec2 image_size, ImVec2 uv0 = (0,0), ImVec2 uv1 = (1,1), ImVec4 bg_col = (0,0,0,0), ImVec4 tint_col = (1,1,1,1));
- 摘要：'border_col' 对布局有误导性的副作用，且缺少 'bg_col'，参数顺序也无法与 ImageButton() 保持一致。
- 新行为始终使用 ImGuiCol_Border 颜色以及 style.ImageBorderSize / ImGuiStyleVar_ImageBorderSize。
- 旧行为会根据边框颜色的 Alpha 值改变边框大小（从而影响布局），这导致了各种问题；此外，旧行为将边框大小固定为 1.0f 且不可调整。
- 保留了旧版签名（将被废弃），它模拟了旧行为，但当指定 border_col 时，会使用 Max(1.0f, style.ImageBorderSize)。
- 添加了 ImageWithBg() 函数，它同时具有“bg_col”（之前缺失）和“tint_col”。由于无法在保持与其他函数参数顺序一致的情况下向 Image() 添加“bg_col”，因此我们决定移除“tint_col”并引入 ImageWithBg()。
- 2025/02/25 (1.91.9) - 内部修改：字体：ImFontAtlas::ConfigData[] 已重命名为 ImFontAtlas::Sources[]。ImFont::ConfigData[]、ConfigDataCount 已重命名为 Sources[]、SourcesCount。
- 2025/02/06 (1.91.9) - 将 ImFontConfig::GlyphExtraSpacing.x 重命名为 ImFontConfig::GlyphExtraAdvanceX。
- 2025/01/22 (1.91.8) - 移除了 ImGuiColorEditFlags_AlphaPreview（将其值设为 0）：现在这已成为默认行为。
在 1.91.8 版本之前：预览中的 Alpha 默认是不透明的，除非使用了 ImGuiColorEditFlags_AlphaPreview。现在我们默认将预览显示为透明。你可以使用 ImGuiColorEditFlags_AlphaOpaque 来恢复旧的行为。
新的标志位（ImGuiColorEditFlags_AlphaOpaque、ImGuiColorEditFlags_AlphaNoBg 以及现有的 ImGuiColorEditFlags_AlphaPreviewHalf）可以更好地组合，并提供更精细的控制：
- 2025/01/14 (1.91.7) - 将 ImGuiTreeNodeFlags_SpanTextWidth 重命名为 ImGuiTreeNodeFlags_SpanLabelWidth，以保持与其他名称的一致性。保留了重定向枚举（后续将废弃）。(#6937)
- 2024/11/27 (1.91.6) - 将 CRC32 表从 CRC32-adler 更改为 CRC32c 多项式，以便与 SSE 4.2 指令的结果兼容。
因此，旧的 .ini 数据可能会部分丢失（特别是停靠布局和表格信息）。
由于部分用户通过构建和存储 .ini 数据来绕过停靠（docking）API 的限制，我们提供了一个名为 '#define IMGUI_USE_LEGACY_CRC32_ADLER' 的编译时选项。如果您无法承受旧版 .ini 数据失效的代价，可以使用该选项继续使用旧的 CRC32 表。
- 2024/11/06 (1.91.5) - 注释掉/废弃了 1.87 版本之前的 IO 系统（等同于此前使用 IMGUI_DISABLE_OBSOLETE_KEYIO 或 IMGUI_DISABLE_OBSOLETE_FUNCTIONS 的效果）。
- 移除了 io.KeyMap[] 和 io.KeysDown[]（于 2022 年 2 月废弃）。
- 移除了 io.NavInputs[] 和 ImGuiNavInput（于 2022 年 7 月废弃）。
- GetKeyIndex() 已移除（2022 年 3 月起废弃）。现在的间接寻址已不再必要。
- 不再支持 1.87 版本之前的后端：
- 后端需要调用 io.AddKeyEvent()、io.AddMouseEvent()，而不是直接写入 io.KeysDown[] 和 io.MouseDown[] 字段。
- 后端需要为手柄数值调用 io.AddKeyAnalogEvent()，而不是直接写入 io.NavInputs[] 字段。
- 更多参考资料：
- 阅读本章节中关于 1.87 和 1.88 的部分，或阅读 1.87 和 1.88 的更新日志（Changelog）。
- 阅读 https://github.com/ocornut/imgui/issues/4921
- 如果你在更新使用旧版后端特定键码（backend-specific key codes）的极旧代码库时遇到困难：建议先更新到 1.91.4 版本，然后 #define IMGUI_DISABLE_OBSOLETE_KEYIO，最后再更新到最新版本。
- 废弃了 ImGuiKey_COUNT（由于有效按键并非从 0 开始，该常量极易导致错误或产生误导）。建议改用 ImGuiKey_NamedKey_BEGIN/ImGuiKey_NamedKey_END？
- 字体：移除大部分字体函数中的 const 修饰符，以预备即将推出的字体功能改进。
- 2024/10/18 (1.91.4) - 将 ImGuiCol_NavHighlight 重命名为 ImGuiCol_NavCursor（为了与新公开及重构的功能保持一致）。保留了内联重定向枚举（后续将废弃）。
- 2024/10/14 (1.91.4) - 将 ImGuiConfigFlags_NavEnableSetMousePos 移动至独立的 io.ConfigNavMoveSetMousePos 布尔值中。
将 ImGuiConfigFlags_NavNoCaptureKeyboard 移至独立的 io.ConfigNavCaptureKeyboard 布尔值中（注意其值是反转的！）。
保留了旧名称（即将废弃）以及在首次运行时复制设置的代码。动态更改旧值将不再起作用。请切换到使用新值！
- 2024/10/10 (1.91.4) - ImTextureID 的 typedef 现在默认使用 ImU64 而非 void*。(#1641)
这消除了在 32 位架构上构建时，为存储描述符集或其他 64 位结构的后端重新定义它的需求。因此，它简化了各种构建脚本和辅助工具。
如果您在向接收 `ImTextureID` 值的函数（例如 `ImGui::Image()`）传递类型时，将其强制转换为 `void*` 而不是 `ImTextureID`，可能会遇到编译时问题。
若有疑问，通常最好进行中间层 intptr_t 强制转换，因为它允许在不产生警告的情况下转换任何指针/整数类型：
- 可能产生警告：ImGui::Image((void*)MyTextureData, ...);
- 可能产生警告：ImGui::Image((void*)(intptr_t)MyTextureData, ...);
- 不会产生警告：ImGui::Image((ImTextureID)(intptr_t)MyTextureData, ...);
- 请注意，如果你愿意，始终可以将 ImTextureID 定义为你自己的高级结构（带有专门的构造函数）。
- 2024/10/03 (1.91.3) - 拖动控件（drags）：当 v_min==v_max 且不等于 0.0f 时，将其视为有效的限制范围。由于历史原因，零仍然是一个特殊值，除非使用 ImGuiSliderFlags_ClampZeroRange。(#7968, #3361, #76)
- 拖动控件（drags）：扩展了 ImGuiSliderFlags_AlwaysClamp 的行为以包含 _ClampZeroRange。它将 v_min==v_max==0.0f 视为有效的限制范围（即不允许编辑）。
虽然可能性不大，但如果你希望仅在文本输入时进行限制，而希望 v_min==v_max==0.0f 表示不限制拖动，可以使用 _ClampOnInput 代替 _AlwaysClamp。(#7968, #3361, #76)
- 2024/09/10 (1.91.2) - 内部修改：现在使用多个具有相同 ID 的重叠 ButtonBehavior() 时，io.ConfigDebugHighlightIdConflicts=true 功能将发出警告。(#8030)
这是少数可以使用相同 ID 的合法情况。解决方法：(1) 使用带有多个 _MouseButton 标志的单个 ButtonBehavior() 调用，或 (2) 在调用前后加上 PushItemFlag(ImGuiItemFlags_AllowDuplicateId, true); ... PopItemFlag()。
- 2024/08/23 (1.91.1) - 为保持一致性，将 ImGuiChildFlags_Border 重命名为 ImGuiChildFlags_Borders。保留了内联重定向标志。
- 2024/08/22 (1.91.1) - 将部分函数从 ImGuiIO 结构体移动到了 ImGuiPlatformIO 结构体：
- io.GetClipboardTextFn -> platform_io.Platform_GetClipboardTextFn + 将 'void* user_data' 更改为 'ImGuiContext* ctx'。请从 platform_io.ClipboardUserData 中获取您的用户数据。
- io.SetClipboardTextFn -> platform_io.Platform_SetClipboardTextFn + 同上。
- io.PlatformOpenInShellFn -> platform_io.Platform_OpenInShellFn (#7660)
- io.PlatformSetImeDataFn -> platform_io.Platform_SetImeDataFn
- io.PlatformLocaleDecimalPoint -> platform_io.Platform_LocaleDecimalPoint (#7389, #6719, #2278)
- 请通过 GetPlatformIO() 而非 GetIO() 访问这些成员。
其中一些是最近才引入的，通常由核心库和后端自动设置，因此对于这些成员，我们破例不保留旧版的重定向符号。
- 注释掉了在 1.89 版本（约 2022 年 8 月）中废弃的旧版 ImageButton() 函数签名。提醒一下：
- 1.89 版本之前的旧版 ImageButton() 使用 ImTextureId 作为控件 ID（这会导致一些问题，例如在同一作用域内使用多个按钮、瞬态纹理 ID 值、ID 计算不透明等）
- 自 1.89 版本起的新版 ImageButton() 需要显式传入 'const char* str_id'
- 1.89 版本之前的旧版 ImageButton() 带有 'frame_padding' 覆盖参数。
- 自 1.89 版本起，新的 ImageButton() 始终使用 style.FramePadding，你可以通过 PushStyleVar()/PopStyleVar() 自由覆盖该参数。
- 2024/07/25 (1.91.0) - 废弃了 GetContentRegionMax()、GetWindowContentRegionMin() 和 GetWindowContentRegionMax()。（更多信息请参阅 GitHub 上的 #7838）
你永远不应该需要这些函数。你可以通过 GetCursorScreenPos() 和 GetContentRegionAvail() 以更简单的方式实现所有功能。
- 替代方案：GetWindowContentRegionMax().x - GetCursorPos().x
- 你可以使用：GetContentRegionAvail().x
- 而不是：GetWindowContentRegionMax().x + GetWindowPos().x
- 你可以使用：GetCursorScreenPos().x + GetContentRegionAvail().x // 当从窗口左边缘调用时
- 而不是：GetContentRegionMax()
- 你可以使用：GetContentRegionAvail() + GetCursorScreenPos() - GetWindowPos() // 本地坐标系下的右边缘
- 代替：GetWindowContentRegionMax().x - GetWindowContentRegionMin().x
- 你可以使用：GetContentRegionAvail() // 当从窗口左边缘调用时
- 2024/07/15 (1.91.0) - 将 ImGuiSelectableFlags_DontClosePopups 重命名为 ImGuiSelectableFlags_NoAutoClosePopups。(#1379, #1468, #2200, #4936, #5216, #7302, #7573)
（内部：同时将 ImGuiItemFlags_SelectableDontClosePopup 重命名为 ImGuiItemFlags_AutoClosePopups，并反转了行为逻辑）
- 2024/07/15 (1.91.0) - 废弃了 PushButtonRepeat()/PopButtonRepeat()，改为使用新的 PushItemFlag(ImGuiItemFlags_ButtonRepeat, ...)/PopItemFlag()。
- 2024/07/02 (1.91.0) - 注释掉了已废弃的 ImGuiModFlags（在 1.89 版本中已重命名为 ImGuiKeyChord）。(#4921, #456)
- 注释掉了已废弃的 ImGuiModFlags_XXX 数值（在 1.89 版本中已重命名为 ImGuiMod_XXX）。(#4921, #456)
- ImGuiModFlags_Ctrl -> ImGuiMod_Ctrl, ImGuiModFlags_Shift -> ImGuiMod_Shift 等。
- 2024/07/02 (1.91.0) - IO, IME：重命名了平台 IME 钩子，并添加了显式上下文以确保一致性和前瞻性。
- 旧：io.SetPlatformImeDataFn(ImGuiViewport* viewport, ImGuiPlatformImeData* data);
- 新：io.PlatformSetImeDataFn(ImGuiContext* ctx, ImGuiViewport* viewport, ImGuiPlatformImeData* data);
- 2024/06/21 (1.90.9) - BeginChild: 添加了 ImGuiChildFlags_NavFlattened 以替代窗口标志 ImGuiWindowFlags_NavFlattened：该功能无论如何都只对 BeginChild() 有意义。
- 旧代码：BeginChild("Name", size, 0, ImGuiWindowFlags_NavFlattened);
- 新代码：BeginChild("Name", size, ImGuiChildFlags_NavFlattened, 0);
- 2024/06/21 (1.90.9) - io: ClearInputKeys()（首次公开于 1.89.8）不会清除鼠标数据，新添加的 ClearInputMouse() 可以实现该功能。
- 2024/06/20 (1.90.9) - 将 ImGuiDragDropFlags_SourceAutoExpirePayload 重命名为 ImGuiDragDropFlags_PayloadAutoExpire。
- 2024/06/18 (1.90.9) - 样式：重命名 ImGuiCol_TabActive -> ImGuiCol_TabSelected，ImGuiCol_TabUnfocused -> ImGuiCol_TabDimmed，ImGuiCol_TabUnfocusedActive -> ImGuiCol_TabDimmedSelected。
- 2024/06/10 (1.90.9) - 移除了旧的嵌套结构：将 ImGuiStorage::ImGuiStoragePair 类型重命名为 ImGuiStoragePair（对多种语言更友好）。
- 2024/06/06 (1.90.8) - 重新排列了 ImGuiInputTextFlags 的数值。除非你使用的生成头文件中的数值与主库不匹配，否则这不应该导致破坏性变更。
- 2024/06/06 (1.90.8) - 移除了 'ImGuiButtonFlags_MouseButtonDefault_ = ImGuiButtonFlags_MouseButtonLeft'，该标志基本未被使用且具有误导性。
- 2024/05/27 (1.90.7) - 注释掉了在 1.88 版本（2022年5月）中标记为过时的符号：
- 旧：CaptureKeyboardFromApp(bool)
- 新：SetNextFrameWantCaptureKeyboard(bool)
- 旧名称：CaptureMouseFromApp(bool)
- 新名称：SetNextFrameWantCaptureMouse(bool)
- 2024/05/22 (1.90.7) - 输入（内部）：将 ImGuiKeyOwner_None 重命名为 ImGuiKeyOwner_NoOwner，以使用途更明确，并减少与默认值的混淆；它是一个非零值，不能作为默认值（从未公开，但考虑到可能有少数用户在使用感知所有者的输入功能，故予以披露）。
- 输入（内部）：重命名 ImGuiInputFlags_RouteGlobalLow -> ImGuiInputFlags_RouteGlobal，ImGuiInputFlags_RouteGlobal -> ImGuiInputFlags_RouteGlobalOverFocused，ImGuiInputFlags_RouteGlobalHigh -> ImGuiInputFlags_RouteGlobalHighest。
- 输入（内部）：Shortcut()、SetShortcutRouting()：交换了函数签名中最后两个参数的顺序：
- 旧版：Shortcut(ImGuiKeyChord key_chord, ImGuiID owner_id = 0, ImGuiInputFlags flags = 0);
- 新版：Shortcut(ImGuiKeyChord key_chord, ImGuiInputFlags flags = 0, ImGuiID owner_id = 0);
- 输入（内部）：IsKeyPressed()、IsKeyChordPressed()、IsMouseClicked() 的所有者感知（owner-aware）版本：交换了函数签名中最后两个参数的顺序。
- 旧版：IsKeyPressed(ImGuiKey key, ImGuiID owner_id, ImGuiInputFlags flags = 0);
- 新版：IsKeyPressed(ImGuiKey key, ImGuiInputFlags flags, ImGuiID owner_id = 0);
- 旧版：IsMouseClicked(ImGuiMouseButton button, ImGuiID owner_id, ImGuiInputFlags flags = 0);
- 新版：IsMouseClicked(ImGuiMouseButton button, ImGuiInputFlags flags, ImGuiID owner_id = 0);
出于各种原因，这些更改是有意义的。进行这些更改是因为要将其中一些 API 公开。
只有以往使用过包含额外参数的 imgui_internal.h 的用户会受到影响。在多个函数中增加了对有效标志的断言，以检测“部分”误用情况，但并非全部。
- 2024/05/16 (1.90.7) - 输入：在 macOS X 上，io.AddKeyEvent() 现在会自动交换 Cmd 和 Ctrl 键，因为这符合 macOS X 使用这些按键的自然习惯。
- 除非你为 macOS X 应用设置了自定义的快捷键交换逻辑，否则这应该不会对你产生实际影响。
- 移除了 ImGuiMod_Shortcut，该修饰键此前用于动态映射到 Ctrl 或 Cmd/Super。现在已无需专门指定跨平台惯用的快捷键。(#2343, #4084, #5923, #456)
- 2024/05/14 (1.90.7) - 后端：SDL_Renderer2 和 SDL_Renderer3 后端的 RenderDrawData() 函数现在需要传入 SDL_Renderer* 参数。
- 2024/04/18 (1.90.6) - TreeNode：修复了在使用空标签或隐藏标签后紧跟 SameLine() 调用时出现的布局不一致问题。(#7505, #282)
- 旧代码：TreeNode("##Hidden"); SameLine(); Text("Hello"); // <-- 这在实际上是不正确的！但在默认样式（即 ItemSpacing.x == FramePadding.x * 2）下看起来似乎没问题（否则看起来会不对齐）。
- 新写法：TreeNode("##Hidden"); SameLine(0, 0); Text("Hello"); // <-- 这对所有样式值都是正确的。
在修复之后，如果你之前一直在使用 TreeNode("")+SameLine();，那么现在你的 TreeNode 与后续项目之间会出现额外的间距。
你需要将 SameLine() 调用改为 SameLine(0,0) 以移除这些多余的间距。这似乎是更合理的修复方案，且不会降低一致性。
（注意：在使用这种惯用法时，你可能还会用到 ImGuiTreeNodeFlags_SpanAvailWidth）。
- 2024/03/18 (1.90.5) - 将 ImDrawList::AddEllipse()、AddEllipseFilled() 和 PathEllipticalArcTo() 中的 radius_x/radius_y 参数合并为单个 ImVec2 参数。破例说明：由于这些函数是在 1.90 版本中新增的，我们不会添加内联重定向函数。此转换非常简单，受影响的用户应该很少。(#2743, #7417)
- 2024/03/08 (1.90.5) - 输入：在设置了 IMGUI_DISABLE_OBSOLETE_FUNCTIONS 时，更正式地废弃了 GetKeyIndex()。自 1.87 版本以来，该函数已无必要且不执行任何操作（当配合使用 io.AddKeyEvent() 函数的 1.87+ 版本后端时，它返回的值与传入的值相同）。(#4921)
- IsKeyPressed(GetKeyIndex(ImGuiKey_XXX)) -> 请使用 IsKeyPressed(ImGuiKey_XXX)
- 2024/01/15 (1.90.2) - 注释掉了在 1.87 版本中标记为过时的 ImGuiIO::ImeWindowHandle，请改为写入 'void* ImGuiViewport::PlatformHandleRaw'。
- 2023/12/19 (1.90.1) - 注释掉了已废弃的 ImGuiKey_KeyPadEnter 到 ImGuiKey_KeypadEnter 的重定向。
- 2023/11/06 (1.90.1) - 移除了在 1.86 版本中标记为废弃的 CalcListClipping()。请优先使用支持返回非连续范围的 ImGuiListClipper。
- 2023/11/05 (1.90.1) - imgui_freetype: 注释掉了在 1.81 版本中废弃的 ImGuiFreeType::BuildFontAtlas()。请优先使用 #define IMGUI_ENABLE_FREETYPE，或参考注释掉的代码进行手动调用。
- 2023/11/05 (1.90.1) - 内部机制、列：注释掉了重定向至 ImGuiOldColumnsFlags_XXX 的旧版 ImGuiColumnsFlags_XXX 符号，这些符号自 1.80 版本起已在 imgui_internal.h 中废弃。
- 2023/11/09 (1.90.0) - 移除了 IM_OFFSETOF() 宏，改为使用 C++11 中提供的 offsetof()。保留了重定向定义（即将废弃）。
- 2023/11/07 (1.90.0) - 移除了 BeginChildFrame()/EndChildFrame()，改为使用带有 ImGuiChildFlags_FrameStyle 标志的 BeginChild()。保留了内联重定向函数（即将废弃）。
这些函数仅仅是 PushStyle/PopStyle 的辅助函数，移除它们的主要动力并非由于需要在 BeginChild() 中添加该功能，而是为了避免 BeginChildFrame() 的签名与 BeginChild() 的签名及功能发生冲突。
- 2023/11/02 (1.90.0) - BeginChild：将 'bool border = true' 参数升级为 'ImGuiChildFlags flags' 类型，并添加了等效的 ImGuiChildFlags_Border。与我们之前的“布尔转标志（bool-to-flags）”API 更新一样，ImGuiChildFlags_Border 的值保证永远等于 true，以确保平滑过渡，这意味着所有现有调用仍将有效。
- 旧版：BeginChild("Name", size, true)
- 新版：BeginChild("Name", size, ImGuiChildFlags_Border)
- 旧版：BeginChild("Name", size, false)
- 新版：BeginChild("Name", size) 或 BeginChild("Name", 0) 或 BeginChild("Name", size, ImGuiChildFlags_None)
**来自未来的修正：从 1.91.1 版本起，“ImGuiChildFlags_Border”已更名为“ImGuiChildFlags_Borders”**
- 2023/11/02 (1.90.0) - BeginChild: 添加了子窗口标志 ImGuiChildFlags_AlwaysUseWindowPadding，用以替代窗口标志 ImGuiWindowFlags_AlwaysUseWindowPadding：因为该功能本质上仅对 BeginChild() 有意义。
- 旧写法：BeginChild("Name", size, 0, ImGuiWindowFlags_AlwaysUseWindowPadding);
- 新写法：BeginChild("Name", size, ImGuiChildFlags_AlwaysUseWindowPadding, 0);
- 2023/09/27 (1.90.0) - io: 移除了 1.63 中引入的 io.MetricsActiveAllocations。其等同于 'g.DebugMemAllocCount - g.DebugMemFreeCount'（仍会在 Metrics 中显示，但最终用户不太可能访问）。
- 2023/09/26 (1.90.0) - 调试工具：将 ShowStackToolWindow()（“Stack Tool”）重命名为 ShowIDStackToolWindow()（“ID Stack Tool”），因为旧名称具有误导性。保留了内联重定向函数。(#4631)
- 2023/09/15 (1.90.0) - ListBox, Combo: 更改了旧版单行 ListBox()/Combo() API 中“名称获取器（name getter）”回调的签名。保留了内联重定向函数（即将废弃）。
- 旧版：bool Combo(const char* label, int* current_item, bool (*getter)(void* user_data, int idx, const char** out_text), ...)
- 新增：bool Combo(const char* label, int* current_item, const char* (*getter)(void* user_data, int idx), ...);
- 旧版：bool ListBox(const char* label, int* current_item, bool (*getting)(void* user_data, int idx, const char** out_text), ...);
- 新增：bool ListBox(const char* label, int* current_item, const char* (*getter)(void* user_data, int idx), ...);
- 2023/09/08 (1.90.0) - 注释掉了过时的重定向函数：
- GetWindowContentRegionWidth() -> 请使用 GetWindowContentRegionMax().x - GetWindowContentRegionMin().x。请注意，通常情况下使用 'GetContentRegionAvail().x' 会更有效。
- ImDrawCornerFlags_XXX -> 请使用 ImDrawFlags_RoundCornersXXX 标志。详情请参阅 1.82 更新日志，并在源码中搜索被注释掉的名称。
- 已注释掉对 AddRect()/AddRectFilled()/PathRect()/AddImageRounded() 中硬编码的 ~0 或 0x01..0x0F 圆角标志值的运行时支持 -> 请使用 ImDrawFlags_RoundCornersXXX 标志。详情请参阅 1.82 更新日志。
- 2023/08/25 (1.89.9) - clipper：将 IncludeRangeByIndices()（在 1.89.6 之前也称为 ForceDisplayRangeByIndices()）重命名为 IncludeItemsByIndex()。保留了内联重定向函数。抱歉！
- 2023/07/12 (1.89.8) - ImDrawData：CmdLists 现在为自有属性，从 ImDrawList** 更改为 ImVector<ImDrawList*>。大多数用户不会受到影响，但你不能再将其与 NULL 比较或手动重新赋值。请改用 AddDrawList()。(#6406, #4879, #1878)
- 2023/06/28 (1.89.7) - 重叠项：废弃了“SetItemAllowOverlap()”（在项目后调用），改为调用“SetNextItemAllowOverlap()”（在项目前调用）。自 1.89 (2022-11-15) 以来，“SetItemAllowOverlap()”一直无法且不能可靠地工作。
- 2023/06/28 (1.89.7) - 重叠项：将“ImGuiTreeNodeFlags_AllowItemOverlap”重命名为“ImGuiTreeNodeFlags_AllowOverlap”，将“ImGuiSelectableFlags_AllowItemOverlap”重命名为“ImGuiSelectableFlags_AllowOverlap”。保留了重定向枚举（即将废弃）。
- 2023/06/28 (1.89.7) - 重叠项：现在当查询一个使用了 AllowOverlap 模式且正被重叠的项目时，IsItemHovered() 默认返回 false。使用 ImGuiHoveredFlags_AllowWhenOverlappedByItem 可恢复到旧行为。
- 2023/06/28 (1.89.7) - 重叠项目：Selectable 和 TreeNode 在激活状态下不再允许重叠，因此重叠的小部件不会显示为悬停状态。虽然这修复了一个常见的细微视觉问题，但也意味着在非响应式元素（如 Text()）覆盖激活元素的情况下，如果你不使用 IsItemHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem)，那么调用 IsItemHovered() 可能会失败。(#6610)
- 2023/06/20 (1.89.7) - 将 io.HoverDelayShort/io.HoverDelayNormal 移至 style.HoverDelayShort/style.HoverDelayNormal。由于这些字段是在 1.89 版本中添加的，且预计大多数用户会保持其默认值，或仅在应用程序初始化期间调整一次，因此我们破例接受这一破坏性变更。
- 2023/05/30 (1.89.6) - 后端：将 "imgui_impl_sdlrenderer.cpp" 重命名为 "imgui_impl_sdlrenderer2.cpp"，将 "imgui_impl_sdlrenderer.h" 重命名为 "imgui_impl_sdlrenderer2.h"。这是为了预留给未来发布的 SDL3。
- 2023/05/22 (1.89.6) - 列表框：注释掉了已被标记为废弃超过两年的过时/重定向函数：
- ListBoxHeader() -> 使用 BeginListBox()（注意 ListBoxHeader() 曾存在两个变体。参考 imgui.h 中被注释掉的版本）
- ListBoxFooter() -> 使用 EndListBox()
- 2023/05/15 (1.89.6) - clipper：注释掉了已废弃的重定向构造函数 'ImGuiListClipper(int items_count, float items_height = -1.0f)'，该函数在 1.79 版本中已被标记为废弃。请使用默认构造函数 + clipper.Begin()。
- 2023/05/15 (1.89.6) - clipper：将 ImGuiListClipper::ForceDisplayRangeByIndices() 重命名为 ImGuiListClipper::IncludeRangeByIndices()。
- 2023/03/14 (1.89.4) - 注释掉了两年前标记为过时的重定向枚举/函数名称：
- ImGuiSliderFlags_ClampOnInput -> 使用 ImGuiSliderFlags_AlwaysClamp
- ImGuiInputTextFlags_AlwaysInsertMode -> 使用 ImGuiInputTextFlags_AlwaysOverwrite
- ImDrawList::AddBezierCurve() -> 使用 ImDrawList::AddBezierCubic()
- ImDrawList::PathBezierCurveTo() -> 请使用 ImDrawList::PathBezierCubicCurveTo()
- 2023/03/09 (1.89.4) - 将 PushAllowKeyboardFocus()/PopAllowKeyboardFocus() 重命名为 PushTabStop()/PopTabStop()。保留了内联重定向函数（即将废弃）。
- 2023/03/09 (1.89.4) - 工具提示：为了保持 API 的一致性，为 BeginTooltip() 添加了 'bool' 返回值。请仅在 BeginTooltip() 返回 true 时提交内容并调用 EndTooltip()。实际上，该函数“目前”总是返回 true，但后续的更改可能会改变这一点，最好尽早明确 API 规范。
- 2023/02/15 (1.89.4) - 将可选的“常规数学运算符”实现从 imgui_internal.h 移至 imgui.h。
尽管我们鼓励通过设置 IM_VEC2_CLASS_EXTRA 来使用您自己的数学类型和运算符，
但经常有人请求使用我们自带的。我们曾有一个可选的宏定义，
以前是在 imgui_internal.h 中实现的。现在它已在 imgui.h 中实现。(#6164)
- 正确做法：#define IMGUI_DEFINE_MATH_OPERATORS / #include "imgui.h" / #include "imgui_internal.h"
- 错误：#include "imgui.h" / #define IMGUI_DEFINE_MATH_OPERATORS / #include "imgui_internal.h"
- 2023/02/07 (1.89.3) - 后端：将 "imgui_impl_sdl.cpp" 重命名为 "imgui_impl_sdl2.cpp"，将 "imgui_impl_sdl.h" 重命名为 "imgui_impl_sdl2.h"。(＃6146) 这是为未来发布 SDL3 做的准备。
- 2022/10/26 (1.89) - 注释掉了 OpenPopupContextItem() 的重定向，该名称在 1.77 到 1.79 版本期间曾简短作为 OpenPopupOnItemClick() 的别名。
- 2022/10/12 (1.89) - 移除了对 DragInt()/SliderInt() 中无效 "%f"/"%0.f" 格式化字符串的运行时修补。此功能在 1.61 版本（2018 年 5 月）中已废弃。详情请参阅 1.61 更新日志。
- 2022/09/26 (1.89) - 重命名并将键盘修饰键枚举和标志合并为同一集合。保留了内联重定向枚举（即将废弃）。
- ImGuiKey_ModCtrl 和 ImGuiModFlags_Ctrl -> ImGuiMod_Ctrl
- ImGuiKey_ModShift 和 ImGuiModFlags_Shift -> ImGuiMod_Shift
- ImGuiKey_ModAlt 和 ImGuiModFlags_Alt -> ImGuiMod_Alt
- ImGuiKey_ModSuper 和 ImGuiModFlags_Super -> ImGuiMod_Super
ImGuiKey_ModXXX 是在 1.87 版本中引入的，主要由后端使用。
ImGuiModFlags_XXX 虽然在 imgui.h 中公开，但实际上并未被任何公共 API 使用，仅由第三方扩展使用。
破例在正式废弃计划前注释掉旧的 ImGuiKeyModFlags_XXX 名称，以减少混淆，且因为它们本来就不应该被使用。
- 2022/09/20 (1.89) - ImGuiKey 现在是一个强类型枚举（typed enum），这使得 ImGuiKey_XXX 符号可以在调试器中显示名称。
这将要求对使用旧版后端依赖索引的地方进行强制类型转换，例如：
- 使用 imgui_impl_glfw 时：IsKeyPressed(GLFW_KEY_A) -> IsKeyPressed((ImGuiKey)GLFW_KEY_A);
- 使用 imgui_impl_win32 时：IsKeyPressed('A') -> IsKeyPressed((ImGuiKey)'A')
- 等等。不过，如果你正在升级代码，现在大可以改用更好且与后端无关的 IsKeyPressed(ImGuiKey_A)！
- 2022/09/12 (1.89) - 移除了 'TreePush(const void* ptr = NULL)' 中古怪的遗留默认参数，现在必须显式传递指针值。NULL/nullptr 仍然可用，但需要进行转换，例如 TreePush((void*)nullptr);
- 2022/09/05 (1.89) - 注释掉了在 1.77 和 1.78 版本（2020年6月）中被标记为过时的重定向函数/枚举名称：
- DragScalar(), DragScalarN(), DragFloat(), DragFloat2(), DragFloat3(), DragFloat4(): 对于以 (..., const char* format, float power = 1.0f) 结尾的旧版签名 -> 如果 power != 1.0f，请改用 (..., format ImGuiSliderFlags_Logarithmic)。
- SliderScalar(), SliderScalarN(), SliderFloat(), SliderFloat2(), SliderFloat3(), SliderFloat4()：对于以 (..., const char* format, float power = 1.0f) 结尾的旧版签名 -> 如果 power != 1.0f，请使用 (..., format, ImGuiSliderFlags_Logarithmic)。
- BeginPopupContextWindow(const char*, ImGuiMouseButton, bool) -> 请使用 BeginPopupContextWindow(const char*, ImGuiPopupFlags)
- 2022/09/02 (1.89) - 废弃了通过 SetCursorPos()/SetCursorScreenPos() 来扩展父窗口/单元格边界的用法。
这涉及在未提交项目的情况下，将光标位置移动到当前边界之外的情形。
- 以前这样做会使窗口内容尺寸变为约 200x200：
Begin(...) + SetCursorScreenPos(GetCursorScreenPos() + ImVec2(200,200)) + End();
- 现在，请改为提交一个控件项：
Begin(...) + SetCursorScreenPos(GetCursorScreenPos() + ImVec2(200,200)) + Dummy(ImVec2(0,0)) + End();
- 替代方案：
Begin(...) + Dummy(ImVec2(200,200)) + End();
- 现在仅在提交控件项时才会扩展内容区域大小！
- 启用 '#define IMGUI_DISABLE_OBSOLETE_FUNCTIONS' 后，此项现在将被检测并触发断言。
- 在未定义 '#define IMGUI_DISABLE_OBSOLETE_FUNCTIONS' 的情况下，此问题将被静默修复，直到我们将其废弃。
- 2022/08/03 (1.89) - 修改了 ImageButton() 函数的签名。保留了重定向函数（后续将废弃）。
- 增加了 'const char* str_id' 参数 + 移除了 'int frame_padding = -1' 参数。
- 旧签名：bool ImageButton(ImTextureID tex_id, ImVec2 size, ImVec2 uv0 = ImVec2(0,0), ImVec2 uv1 = ImVec2(1,1), int frame_padding = -1, ImVec4 bg_col = ImVec4(0,0,0,0), ImVec4 tint_col = ImVec4(1,1,1,1));
- 曾使用 ImTextureID 的值来创建 ID。这与其他函数不一致，会导致 ID 冲突，并给使用瞬态 ImTextureID 值的引擎带来问题。
- 曾包含一个 FramePadding 覆盖参数，这与其他函数不一致，且使本就冗长的函数签名变得更长。
- 新签名：bool ImageButton(const char* str_id, ImTextureID tex_id, ImVec2 size, ImVec2 uv0 = ImVec2(0,0), ImVec2 uv1 = ImVec2(1,1), ImVec4 bg_col = ImVec4(0,0,0,0), ImVec4 tint_col = ImVec4(1,1,1,1));
- 需要一个显式的标识符。你仍然可以使用例如 PushID() 调用，然后传递一个空标识符。
- 始终使用 style.FramePadding 作为内边距，以保持与其他按钮的一致性。你可以使用 PushStyleVar() 来修改此项。
- 2022/07/08 (1.89) - 输入：移除了 io.NavInputs[] 和 ImGuiNavInput 枚举（继 1.87 版本的更改之后）。
- 1.87+ 版本的官方后端 -> 无此问题。
- 1.60 至 1.86 版本的官方后端 -> 将会构建并转换手柄输入，除非定义了 IMGUI_DISABLE_OBSOLETE_KEYIO。需要更新！
- 不向 io.NavInputs[] 写入数据的自定义后端 -> 无影响。
- 向 io.NavInputs[] 写入数据的自定义后端 -> 除非定义了 IMGUI_DISABLE_OBSOLETE_KEYIO，否则仍会构建并转换手柄输入。需要修复！
- 简而言之：后端应调用 io.AddKeyEvent()/io.AddKeyAnalogEvent() 并传入 ImGuiKey_GamepadXXX 值，而不是填充 io.NavInput[]。
- 2022/06/15 (1.88) - 为求准确，将 IMGUI_DISABLE_METRICS_WINDOW 重命名为 IMGUI_DISABLE_DEBUG_TOOLS。保留了对旧定义的支持（即将废弃）。
- 2022/05/03 (1.88) - 后端：osx：从后端 API 中移除了 ImGui_ImplOSX_HandleEvent()，改为由后端自动处理事件捕获。所有 ImGui_ImplOSX_HandleEvent() 调用都应移除，因为它们现在已不再需要。
- 2022/04/05 (1.88) - 输入：将 ImGuiKeyModFlags 重命名为 ImGuiModFlags。保留了内联重定向枚举（即将废弃）。这从未在公共 API 函数中使用过，但在技术上存在于 imgui.h 和 ImGuiIO 中。
- 2022/01/20 (1.87) - 输入：重写了手柄 IO。
- 后端写入 io.NavInputs[] -> 后端应调用 io.AddKeyEvent()/io.AddKeyAnalogEvent() 并传入 ImGuiKey_GamepadXXX 数值。
- 2022/01/19 (1.87) - 滑块（sliders）、拖动控件（drags）：移除了输入文本时对旧版算术运算符（+、+-、*、/）的支持。这不会破坏任何 API 或代码，但属于一项曾面向终端用户开放的功能（似乎无人使用）。
- 2022/01/17 (1.87) - 输入（inputs）：重构了鼠标 IO。
- 后端写入 io.MousePos -> 后端应调用 io.AddMousePosEvent()
- 后端写入 io.MouseDown[] -> 后端应调用 io.AddMouseButtonEvent()
- 后端写入 io.MouseWheel -> 后端应调用 io.AddMouseWheelEvent()
- 后端写入 io.MouseHoveredViewport -> 后端应调用 io.AddMouseViewportEvent() [仅限带多视口的 Docking 分支]
注意：对于所有 IO 新函数的调用，Dear ImGui 上下文必须已绑定/为当前上下文。
详情请阅读 https://github.com/ocornut/imgui/issues/4921。
- 2022/01/10 (1.87) - 输入：重构了键盘 IO。移除了 io.KeyMap[] 和 io.KeysDown[]，改为调用 io.AddKeyEvent() 和 ImGui::IsKeyDown()。移除了已不再需要的 GetKeyIndex()。所有 IsKeyXXX() 函数现在都接收 ImGuiKey 枚举值。在定义 IMGUI_DISABLE_OBSOLETE_KEYIO 之前，所有功能仍可正常使用。详情请阅读更新日志（Changelog）和发布说明（Release Notes）。
- IsKeyPressed(MY_NATIVE_KEY_XXX) -> 使用 IsKeyPressed(ImGuiKey_XXX)
- IsKeyPressed(GetKeyIndex(ImGuiKey_XXX)) -> 使用 IsKeyPressed(ImGuiKey_XXX)
- 后端写入 io.KeyMap[], io.KeysDown[] -> 后端应调用 io.AddKeyEvent()（如果你希望旧的用户代码仍能通过旧的键码运行，请同时调用 io.SetKeyEventNativeData()）。
- 后端写入 io.KeyCtrl, io.KeyShift.. -> 后端应调用 io.AddKeyEvent() 并传入 ImGuiMod_XXX 值。*如果你在 2021/01/10 到 2021/01/27 之间拉取了代码：我们曾使用过 io.AddKeyModsEvent() 函数，现在它已被使用 ImGuiMod_XXX 值的 io.AddKeyEvent() 取代。*
- 有一种情况无法向后兼容：如果你的自定义后端将 ImGuiKey 用作模拟原生索引（例如 "io.KeyMap[ImGuiKey_A] = ImGuiKey_A"），因为这些值现在大于旧有的 KeyDown[] 数组。这会导致断言失败。
- 输入：添加了 ImGuiKey_ModCtrl/ImGuiKey_ModShift/ImGuiKey_ModAlt/ImGuiKey_ModSuper 值，用于通过 io.AddKeyEvent() 提交键盘修饰键，而不是直接写入 io.KeyCtrl, io.KeyShift, io.KeyAlt, io.KeySuper。
- 2022/01/05 (1.87) - 输入：将 ImGuiKey_KeyPadEnter 重命名为 ImGuiKey_KeypadEnter 以与新符号保持一致。保留了重定向枚举。
- 2022/01/05 (1.87) - 移除了 io.ImeSetInputScreenPosFn()，代之以更灵活的 io.SetPlatformImeDataFn()。移除了 'void* io.ImeWindowHandle'，改为写入 'void* ImGuiViewport::PlatformHandleRaw'。
- 2022/01/01 (1.87) - 注释掉了在 1.69、1.70、1.71、1.72 版本（2019年3月至7月）中被标记为过时的重定向函数/枚举名称。
- ImGui::SetNextTreeNodeOpen() -> 请使用 ImGui::SetNextItemOpen()
- ImGui::GetContentRegionAvailWidth() -> 请使用 ImGui::GetContentRegionAvail().x
- ImGui::TreeAdvanceToLabelPos() -> 请使用 ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ImGui::GetTreeNodeToLabelSpacing());
- ImFontAtlas::CustomRect -> 请使用 ImFontAtlasCustomRect
- ImGuiColorEditFlags_RGB/HSV/HEX -> 请使用 ImGuiColorEditFlags_DisplayRGB/HSV/Hex
- 2021/12/20 (1.86) - 后端：移除了过时的 Marmalade 后端 (imgui_impl_marmalade.cpp) 及示例。请在 https://github.com/ocornut/imgui/wiki/Bindings 查找最后一个支持的版本。
- 2021/11/04 (1.86) - 移除了 CalcListClipping() 函数。请优先使用支持返回非连续范围的 ImGuiListClipper。如果您认为确实需要此函数，请提交 Issue。
- 2021/08/23 (1.85) - 移除了 GetWindowContentRegionWidth() 函数。保留了内联重定向辅助函数。可以使用 'GetWindowContentRegionMax().x - GetWindowContentRegionMin().x' 代替，但通常 'GetContentRegionAvail().x' 会更有用。
- 2021/07/26 (1.84) - 注释掉了在 1.67 和 1.69 版本（2019年3月）中被标记为过时的重定向函数/枚举名称：
- ImGui::GetOverlayDrawList() -> 请使用 ImGui::GetForegroundDrawList()
- ImFont::GlyphRangesBuilder -> 使用 ImFontGlyphRangesBuilder
- 2021/05/19 (1.83) - 后端：废弃了对 ImDrawCmd::TextureId 的直接访问，改为调用 ImDrawCmd::GetTexID()。
- 如果您使用的是源码树中的官方后端：无需进行任何操作。
- 如果您复制了旧的后端代码或使用自定义后端：请将对 draw_cmd->TextureId 的访问更改为 draw_cmd->GetTexID()。
- 2021/03/12 (1.82) - 升级了 ImDrawList::AddRect()、AddRectFilled()、PathRect()，改用 ImDrawFlags 代替 ImDrawCornersFlags。
- ImDrawCornerFlags_TopLeft -> 使用 ImDrawFlags_RoundCornersTopLeft
- ImDrawCornerFlags_BotRight -> 使用 ImDrawFlags_RoundCornersBottomRight
- ImDrawCornerFlags_None -> 使用 ImDrawFlags_RoundCornersNone 等。
标志（flags）现在的默认值已合理地设为 0 而非 0x0F，这与 API 中的所有其他标志保持一致。
重大变更：当圆角半径（rounding）> 0.0f 时，默认行为现在是“圆角化所有角”，而以前隐式默认为“不圆角化任何角”：
- rounding == 0.0f + flags == 0 --> 意味着无圆角 --> 保持不变（常见用法）
- rounding > 0.0f + flags != 0 --> 意味着有圆角 --> 保持不变（常见用法）
- rounding == 0.0f + flags != 0 --> 意为不圆角 --> 保持不变（不太可能的使用情况）
- rounding > 0.0f + flags == 0 --> 意为不圆角 --> 破坏性变更（不太可能的使用情况）：现在将对所有角进行圆角处理 --> 请使用 ImDrawFlags_RoundCornersNone 或设置 rounding == 0.0f。
这仅对硬编码使用 0 且 rounding > 0.0f 的情况有影响。使用命名的 ImDrawFlags_RoundCornersNone（新）或 ImDrawCornerFlags_None（旧）是没问题的。
旧的 ImDrawCornersFlags 使用了尴尬的默认值 ~0 或 0xF（低 4 位被置位）来表示“圆角化所有角”，我们有时曾鼓励将它们作为快捷方式使用。
旧版路径仍支持使用硬编码的 ~0 或 0x1 到 0xF 之间的任何值。在启用旧版路径的情况下，它们的行为保持一致（否则将触发断言）。
- 2021/03/11 (1.82) - 移除了在 1.66 版本（2018年9月）中标记为废弃的重定向函数/枚举名称：
- ImGui::SetScrollHere() -> 请使用 ImGui::SetScrollHereY()
- 2021/03/11 (1.82) - 明确了 ImDrawList::PathArcTo() 和 ImDrawList::PathArcToFast() 在半径 < 0.0f 时不会进行渲染。以前这在某种程度上能意外运行，但通常会导致逆时针路径并影响抗锯齿效果。
- 2021/03/10 (1.82) - 将 ImDrawList::AddPolyline() 和 PathStroke() 的 "bool closed" 参数升级为 "ImDrawFlags flags"。匹配的 ImDrawFlags_Closed 值保证在未来始终保持等于 1。
- 2021/02/22 (1.82) - (*在 1.84 中撤销*) win32+mingw：即使在 MinGW 下也默认重新启用 IME 函数。在 2016 年 7 月，问题 #738 导致我错误地禁用了 MinGW 的这些默认函数。MinGW 用户应当：链接 -limm32，或者在 imconfig 文件中设置 '#define IMGUI_DISABLE_WIN32_DEFAULT_IME_FUNCTIONS'。
- 2021/02/17 (1.82) - 将极少使用的 style.CircleSegmentMaxError（旧默认值 = 1.60f）重命名为 style.CircleTessellationMaxError（新默认值 = 0.30f），因为该值的含义发生了变化。
- 2021/02/03 (1.81) - 将 ListBoxHeader(const char* label, ImVec2 size) 重命名为 BeginListBox()。保留了内联重定向函数（即将废弃）。
- 移除了 ListBoxHeader(const char* label, int items_count, int height_in_items = -1)，改为指定尺寸。保留了内联重定向函数（即将废弃）。
- 将 ListBoxFooter() 重命名为 EndListBox()。保留了内联重定向函数（即将废弃）。
- 2021/01/26 (1.81) - 移除了 ImGuiFreeType::BuildFontAtlas()。保留了内联重定向函数。推荐使用 '#define IMGUI_ENABLE_FREETYPE'，但也提供运行时选择路径。共享的额外标志参数（极少使用）现在存储在 ImFontAtlas::FontBuilderFlags 中。
- 将 ImFontConfig::RasterizerFlags（由 FreeType 使用）重命名为 ImFontConfig::FontBuilderFlags。
- 将 ImGuiFreeType::XXX 标志重命名为 ImGuiFreeTypeBuilderFlags_XXX，以保持与其他 API 的一致性。
- 2020/10/12 (1.80) - 移除了在 1.63 版本（2018年8月）中标记为过时的重定向函数/枚举：
- ImGui::IsItemDeactivatedAfterChange() -> 请使用 ImGui::IsItemDeactivatedAfterEdit()。
- ImGuiCol_ModalWindowDarkening -> 请使用 ImGuiCol_ModalWindowDimBg
- ImGuiInputTextCallback -> 请使用 ImGuiTextEditCallback
- ImGuiInputTextCallbackData -> 使用 ImGuiTextEditCallbackData
- 2020/12/21 (1.80) - 将 ImDrawList::AddBezierCurve() 重命名为 AddBezierCubic()，并将 PathBezierCurveTo() 重命名为 PathBezierCubicCurveTo()。保留了内联重定向函数（后续将废弃）。
- 2020/12/04 (1.80) - 添加了 imgui_tables.cpp 文件！手动构建的项目文件需要添加这个新文件！
- 2020/11/18 (1.80) - 将未公开/内部的 ImGuiColumnsFlags_* 重命名为 ImGuiOldColumnFlags_*，以预备即将推出的 Tables API。
- 2020/11/03 (1.80) - 将 io.ConfigWindowsMemoryCompactTimer 重命名为 io.ConfigMemoryCompactTimer，因为该功能将应用于其他数据结构。
- 2020/10/14 (1.80) - 后端：将所有后端文件（imgui_impl_XXXX.cpp, imgui_impl_XXXX.h）从 examples/ 移动到 backends/ 目录下。
- 2020/10/12 (1.80) - 移除了在 1.60 版本（2018年4月）中被标记为废弃的重定向函数/枚举：
- io.RenderDrawListsFn 指针 -> 使用 ImGui::GetDrawData() 的返回值并调用后端的渲染函数
- ImGui::IsAnyWindowFocused() -> 使用 ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow)
- ImGui::IsAnyWindowHovered() -> 使用 ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow)
- ImGuiStyleVar_Count_ -> 使用 ImGuiStyleVar_COUNT
- ImGuiMouseCursor_Count_ -> 使用 ImGuiMouseCursor_COUNT
- 移除了在 1.61 版本（2018年5月）中被标记为过时的重定向函数名称：
- InputFloat (... int decimal_precision ...) -> 使用 InputFloat (... const char* format ...)，其中 format = "%.Xf"，X 为原先 decimal_precision 的值。
- 同样适用于带有 `int decimal_precision` 参数的 InputFloat2()/InputFloat3()/InputFloat4() 变体。
- 2020/10/05 (1.79) - 移除 ImGuiListClipper：重命名了构造函数参数，因为该参数与使用 ImGuiListClipper::Begin() 函数产生了歧义，并存在误导性的边缘情况（注：来自 imgui_club/ 的 imgui_memory_editor <0.40 版本使用了此旧版 clipper API。请根据需要更新您的副本）。
- 2020/09/25 (1.79) - 将 ImGuiSliderFlags_ClampOnInput 重命名为 ImGuiSliderFlags_AlwaysClamp。保留了重定向枚举（由于旧名称是最近才添加的，因此会较快废弃）。
- 2020/09/25 (1.79) - 将 style.TabMinWidthForUnselectedCloseButton 重命名为 style.TabMinWidthForCloseButton。
- 2020/09/21 (1.79) - 将 OpenPopupContextItem() 重新命名回 OpenPopupOnItemClick()，撤销了 1.77 版本中的更改。出于各种原因，此名称更易于理解。
- 2020/09/21 (1.79) - 移除了 OpenPopupOnItemClick() 的返回值（原先在条目上释放鼠标时返回 true），因为这与其他弹出窗口 API 不一致且容易产生误导。此外该返回值也是不必要的：你可以在 BeginPopup() 之后使用 IsWindowAppearing() 来获得类似的效果。
- 2020/09/17 (1.79) - 移除了 ImFont::DisplayOffset，取而代之的是 ImFontConfig::GlyphOffset。DisplayOffset 是在缩放后应用的，除了默认的 ProggyClean 字体需要它之外，并没有太大意义或用途。如果你以前在调用 AddFontDefault() 后缩放此值，现在这将自动完成。它还阻碍了更好的字体缩放，所以现在让我们弃用它！
- 2020/08/17 (1.78) - 废弃了 DragFloat(), DragFloat2(), DragFloat3(), DragFloat4(), DragFloatRange2(), DragScalar(), DragScalarN(), SliderFloat(), SliderFloat2(), SliderFloat3(), SliderFloat4(), SliderScalar(), SliderScalarN(), VSliderFloat() 和 VSliderScalar() 中末尾的 'float power=1.0f' 参数。
将“float power=1.0f”参数替换为基于整数的标志（flags），默认值为 0（与我们所有的标志一致）。
制定了一套向后兼容方案，因此大多数 C++ 代码库应该不会受到影响。简而言之，在调用这些函数时：
- 如果你省略了“power”参数（很可能如此！），则不受影响。
- 如果你将“power”参数设置为 1.0f（与之前的默认值相同）：1/ 编译器可能会发出浮点数转整数的警告；2/ 其他一切将正常工作；3/ 你可以将 1.0f 替换为 0 以消除警告，并在技术层面上保持正确。
- 如果你将 'power' 参数设置为 >1.0f（以启用非线性编辑）：1/ 你的编译器可能会对 float>int 转换发出警告，2/ 代码将在运行时触发断言，3/ 如果禁用了断言，代码不会崩溃并会启用 _Logarithmic 标志。4/ 你可以将 >1.0f 的值替换为 ImGuiSliderFlags_Logarithmic，以修复警告/断言，并获得与之前使用 power >1.0f 类似的效果。
详见 https://github.com/ocornut/imgui/issues/3361 以获取完整细节。
保留了内联重定向函数（即将废弃），但以下函数除外：DragFloatRange2()、VSliderFloat()、VSliderScalar()。对于这三个函数，直接移除了 'float power=1.0f' 版本，因为它们极少被使用。
对于共享代码，你可以在编译时使用 `#if IMGUI_VERSION_NUM >= 17704` 进行版本检查。
- 废弃了在 DragInt、DragFloat、DragScalar 中通过 v_min > v_max 来锁定编辑的用法（该功能在 1.73 版本引入，未曾进行演示或详细记录），未来将由更通用的 ReadOnly（只读）功能取代。在此期间，您可以使用内部标志 ImGuiSliderFlags_ReadOnly。
- 2020/06/23 (1.77) - 移除了 BeginPopupContextWindow(const char*, int mouse_button, bool also_over_items)，改为使用带有 ImGuiPopupFlags_NoOverItems 标志的 BeginPopupContextWindow(const char*, ImGuiPopupFlags flags)。
- 2020/06/15 (1.77) - 将 OpenPopupOnItemClick() 重命名为 OpenPopupContextItem()。保留了内联重定向函数（即将废弃）。[注：此更改在 1.79 版本中被撤销]
- 2020/06/15 (1.77) - 移除了 CalcItemRectClosestPoint() 入口点，该函数已于 2017 年 12 月废弃并加入断言检查。
- 2020/04/23 (1.77) - 移除了 ImFontAtlas::AddCustomRectRegular() 中不必要的 ID（第一个参数）。
- 2020/01/22 (1.75) - ImDrawList::AddCircle()/AddCircleFilled() 函数不再接受负半径。
- 2019/12/17 (1.75) - [在 1.76 版本中撤销了此更改] 通过在该限制之上添加断言，使 Columns() 限制为 64 列。虽然当前代码在技术上支持更多列，但未来的代码可能不支持，因此我们提前设置了此限制。
- 2019/12/13 (1.75) - [imgui_internal.h] 更改了 ImRect() 默认构造函数，将所有字段初始化为 0.0f，而不是 (FLT_MAX,FLT_MAX,-FLT_MAX,-FLT_MAX)。如果您曾使用 ImRect::Add() 通过添加多个点来创建边界框，则可能需要修正您的初始值。
- 2019/12/08 (1.75) - 移除了在 1.53 版本（2017年12月）中标记为过时的重定向函数/枚举：
- ShowTestWindow() -> 使用 ShowDemoWindow()
- IsRootWindowFocused() -> 使用 IsWindowFocused(ImGuiFocusedFlags_RootWindow)
- IsRootWindowOrAnyChildFocused() -> 使用 IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows)
- SetNextWindowContentWidth(w) -> 使用 SetNextWindowContentSize(ImVec2(w, 0.0f))
- GetItemsLineHeightWithSpacing() -> 使用 GetFrameHeightWithSpacing()
- ImGuiCol_ChildWindowBg -> 使用 ImGuiCol_ChildBg
- ImGuiStyleVar_ChildWindowRounding -> 使用 ImGuiStyleVar_ChildRounding
- ImGuiTreeNodeFlags_AllowOverlapMode -> 使用 ImGuiTreeNodeFlags_AllowItemOverlap
- IMGUI_DISABLE_TEST_WINDOWS -> 请使用 IMGUI_DISABLE_DEMO_WINDOWS
- 2019/12/08 (1.75) - 废弃了调用 ImDrawList::PrimReserve() 时传入负数计数的方法（该用法文档说明模糊且极少被使用）。取而代之的是，我们添加了一个明确的 PrimUnreserve() API。
- 2019/12/06 (1.75) - 删除了 IsMouseDragging(int button = 0) 的隐式默认参数，以保持与其他鼠标函数的一致性（其他函数均不带默认参数）。
- 2019/11/21 (1.74) - ImFontAtlas::AddCustomRectRegular() 现在要求 ID 大于 0x110000（原为 0x10000），以符合未来更新中对 Unicode 第 1-16 平面的支持。低于 0x110000 的 ID 现在会触发断言。
- 2019/11/19 (1.74) - 为保持一致性，将 IMGUI_DISABLE_FORMAT_STRING_FUNCTIONS 重命名为 IMGUI_DISABLE_DEFAULT_FORMAT_FUNCTIONS。
- 2019/11/19 (1.74) - 为保持一致性，将 IMGUI_DISABLE_MATH_FUNCTIONS 重命名为 IMGUI_DISABLE_DEFAULT_MATH_FUNCTIONS。
- 2019/10/22 (1.74) - 移除了在 1.52 版本（2017年10月）中标记为过时的重定向函数/枚举：
- Begin() [旧版 5 个参数的版本] -> 使用 Begin() [3 个参数]，如果需要，请使用 SetNextWindowSize() 或 SetNextWindowBgAlpha()
- IsRootWindowOrAnyChildHovered() -> 使用 IsWindowHovered(ImGuiHoveredFlags_RootAndChildWindows)
- AlignFirstTextHeightToWidgets() -> 使用 AlignTextToFramePadding()
- SetNextWindowPosCenter() -> 使用 SetNextWindowPos() 并将中心点（pivot）设置为 (0.5f, 0.5f)
- ImFont::Glyph -> 请使用 ImFontGlyph
- 2019/10/14 (1.74) - 输入：修复了键盘/鼠标“自动重复”（typematic）延迟/频率计算中的一个错误。该计算被按键、重复鼠标按钮以及 GetKeyPressedAmount() 函数所使用。
如果你之前为 io.KeyRepeatRate 使用了非默认值（之前的默认值为 0.250），你可以将其加上 io.KeyRepeatDelay 以补偿此修复带来的变化。
该函数之前的触发点为：0.0 以及 (delay+rate*N)，其中 (N>=1)。修复后的公式响应点为 (N>=0)。实际上，之前的错误使得 io.KeyRepeatRate 的表现就像是被设置成了 (io.KeyRepeatRate + io.KeyRepeatDelay)。
如果您从未修改过 `io.KeyRepeatRate` 也不曾使用过 `GetKeyPressedAmount()`，那么此项变更不会对您产生影响。
- 2019/07/15 (1.72) - 移除了极少使用的 `TreeAdvanceToLabelPos()`，该函数仅执行 `SetCursorPosX(GetCursorPosX() + GetTreeNodeToLabelSpacing())`。保留了重定向函数（即将废弃）。
- 2019/07/12 (1.72) - 将 `ImFontAtlas::CustomRect` 重命名为 `ImFontAtlasCustomRect`。保留了重定向类型定义（即将废弃）。
- 2019/06/14 (1.72) - 移除了在 1.51 版本（2017 年 6 月）中标记为废弃的重定向函数/枚举名称：`ImGuiCol_Column*`、`ImGuiSetCond_*`、`IsItemHoveredRect()`、`IsPosHoveringAnyWindow()`、`IsMouseHoveringAnyWindow()`、`IsMouseHoveringWindow()`、`IMGUI_ONCE_UPON_A_FRAME`。请在日志中搜索这些名称以获取详情和新名称，或查看它们在 1.71 版本之前的实现方式。
- 2019/06/07 (1.71) - 子窗口外部装饰（背景颜色、边框、滚动条）的渲染现在作为父窗口的一部分进行。
如果你在同一个父窗口中有重叠的子窗口，并且依赖它们的相对 Z 轴顺序（z-order）来映射到它们的提交顺序，这将影响你的渲染效果。
如果父窗口没有视觉输出，则禁用此优化，因为这似乎是导致创建重叠子窗口最常见的情况。
如果你受到影响，请联系我们。
- 2019/05/13 (1.71) - 将 SetNextTreeNodeOpen() 重命名为 SetNextItemOpen()。保留了内联重定向函数（将会废弃）。
- 2019/05/11 (1.71) - 将 io.AddInputCharacter(unsigned short c) 的签名更改为 io.AddInputCharacter(unsigned int c)。
- 2019/04/29 (1.70) - 改进了 ImDrawList 的粗线条（>1.0f）绘制，使其在高达 90 度的角度（例如矩形）下仍能保持正确的厚度。如果您有使用粗线条的自定义渲染，它们现在看起来会更厚。
- 2019/04/29 (1.70) - 移除了 GetContentRegionAvailWidth()，请改用 GetContentRegionAvail().x。保留了内联重定向函数（将会废弃）。
- 2019/03/04 (1.69) - 将 GetOverlayDrawList() 重命名为 GetForegroundDrawList()。保留了重定向函数（即将废弃）。
- 2019/02/26 (1.69) - 将 ImGuiColorEditFlags_RGB/ImGuiColorEditFlags_HSV/ImGuiColorEditFlags_HEX 重命名为 ImGuiColorEditFlags_DisplayRGB/ImGuiColorEditFlags_DisplayHSV/ImGuiColorEditFlags_DisplayHex。保留了重定向枚举（即将废弃）。
- 2019/02/14 (1.68) - 当 io.DisplayTime == 0.0f 时设为非法/触发断言（首帧除外）。如果由于某种原因你的步进时间计算得出了零值，请将其替换为一个极小的数值！
- 2019/02/01 (1.68) - 移除了 io.DisplayVisibleMin/DisplayVisibleMax（这些变量之前已被标记为废弃，并已从 viewport/docking 分支中移除）。
- 2019/01/06 (1.67) - 重命名了 io.InputCharacters[]，并将其标记为内部使用（这一直是其设计初衷）。请勿直接访问，请改用 AddInputCharacter()！
- 2019/01/06 (1.67) - 将 ImFontAtlas::GlyphRangesBuilder 重命名为 ImFontGlyphRangesBuilder。保留了重定向类型定义（即将废弃）。
- 2018/12/20 (1.67) - 规定调用 Begin("") 时使用空字符串为非法操作。此前这种做法在某种程度上勉强可行，但会产生各种不良副作用。
- 2018/12/10 (1.67) - 将 io.ConfigResizeWindowsFromEdges 重命名为 io.ConfigWindowsResizeFromEdges，因为我们正在对配置标志进行大规模调整。
- 2018/10/12 (1.66) - 将 misc/stl/imgui_stl.* 重命名为 misc/cpp/imgui_stdlib.*，以预留给其他 C++ 辅助文件。
- 2018/09/28 (1.66) - 将 SetScrollHere() 重命名为 SetScrollHereY()。保留了重定向函数（后续将废弃）。
- 2018/09/06 (1.65) - 将 stb_truetype.h 重命名为 imstb_truetype.h，stb_textedit.h 重命名为 imstb_textedit.h，并将 stb_rect_pack.h 重命名为 imstb_rectpack.h。
如果你之前在项目中方便地使用了 ImGui 附带的这些 STB 头文件，则需要更新你的包含路径（include paths）。
- 2018/09/05 (1.65) - 将 io.OptCursorBlink/io.ConfigCursorBlink 重命名为 io.ConfigInputTextCursorBlink。(#1427)
- 2018/08/31 (1.64) - 添加了 imgui_widgets.cpp 文件，将控件代码从 imgui.cpp 中提取并移至 imgui_widgets.cpp。对 imgui.cpp 中剩余的部分代码进行了重新排序。
没有任何函数发生改变。代码在语义上是 100% 相同的，但“每一个”函数都被移动了位置。
因此，对 imgui.cpp 的任何本地修改在更新时都可能会产生冲突。请阅读 docs/CHANGELOG.txt 获取建议。
- 2018/08/22 (1.63) - 将 IsItemDeactivatedAfterChange() 重命名为 IsItemDeactivatedAfterEdit()，以保持与新的 IsItemEdited() API 的一致性。保留了重定向函数（由于 IsItemDeactivatedAfterChange() 是最近才加入的，很快将被废弃）。
- 2018/08/21 (1.63) - 为了保持一致性，将 ImGuiTextEditCallback 重命名为 ImGuiInputTextCallback，将 ImGuiTextEditCallbackData 重命名为 ImGuiInputTextCallbackData。保留了重定向类型（将被废弃）。
- 2018/08/21 (1.63) - 移除了 ImGuiInputTextCallbackData::ReadOnly，因为它与 (ImGuiInputTextCallbackData::Flags & ImGuiInputTextFlags_ReadOnly) 重复。
- 2018/08/01 (1.63) - 移除了每个窗口单独设置的 ImGuiWindowFlags_ResizeFromAnySide Beta 标志，改为使用全局的 io.ConfigResizeWindowsFromEdges [1.67 版本更新中重命名为 ConfigWindowsResizeFromEdges] 来启用该功能。
- 2018/08/01 (1.63) - 为了保持一致性，将 io.OptCursorBlink 重命名为 io.ConfigCursorBlink [在 1.65 版本中改为 io.ConfigInputTextCursorBlink]，将 io.OptMacOSXBehaviors 重命名为 ConfigMacOSXBehaviors。
- 2018/07/22 (1.63) - 将 ImGui::GetTime() 的返回值从 float 更改为 double，以避免随时间推移产生的浮点精度误差累积。
- 2018/07/08 (1.63) - 样式：为了与其他功能保持一致，将 ImGuiCol_ModalWindowDarkening 重命名为 ImGuiCol_ModalWindowDimBg。保留了重定向枚举（即将废弃）。
- 2018/06/08 (1.62) - 示例：imgui_impl_XXX 文件已被拆分，以将平台（Win32、GLFW、SDL2 等）与渲染器（DX11、OpenGL、Vulkan 等）分开。
旧版后端仍可照常工作，但建议优先使用分离式后端，因为它们将更新以支持多视口（multi-viewports）。
在采用新后端时，请参考您所选 examples/ 文件夹中的 main.cpp 代码，以了解需要调用哪些函数。
特别需要注意的是，旧版后端在其 ImGui_ImplXXXX_NewFrame() 函数的末尾调用了 ImGui::NewFrame()。
- 2018/06/06 (1.62) - 将 GetGlyphRangesChinese() 重命名为 GetGlyphRangesChineseFull()，以区别于其他变体，并避免在非必要时使用全量字符集。
- 2018/06/06 (1.62) - TreeNodeEx()/TreeNodeBehavior()：ImGuiTreeNodeFlags_CollapsingHeader 辅助标志现在包含 ImGuiTreeNodeFlags_NoTreePushOnOpen 标志。详情请参阅更新日志。
- 2018/05/03 (1.61) - DragInt()：默认的编译时格式字符串已从 "%.0f" 更改为 "%d"，因为我们内部不再使用浮点数处理整数。
如果您在 DragInt() 中使用了自定义格式字符串，请确保将其更改为 %d 或与整数兼容的格式。
为了保持向后兼容性，DragInt() 代码目前会解析并修改格式字符串，将 %*f 替换为 %d，以便给用户留出时间升级代码。
如果您启用了 `IMGUI_DISABLE_OBSOLETE_FUNCTIONS`，代码将会触发断言！您可以在代码库中运行正则表达式搜索（例如 "DragInt.*%f"）来帮助查找这些位置。
- 2018/04/28 (1.61) - 废弃了带有可选 "int decimal_precision" 参数的 InputFloat() 函数，改为使用等效且更灵活的 "const char* format" 参数，
这与其他函数保持了一致。保留了重定向函数（后续将废弃）。
- 2018/04/09 (1.61) - 1.60 中添加的 IM_DELETE() 辅助函数现在不再清除输入的“指针”引用，这更符合预期并允许传递右值。
- 2018/03/20 (1.60) - 将 io.WantMoveMouse 重命名为 io.WantSetMousePos，以保持一致性并易于理解（该字段于 1.52 版本添加，核心库*未*使用，仅在合并 Nav 分支前被部分后端支持）。
- 2018/03/12 (1.60) - 移除了 ImGuiCol_CloseButton、ImGuiCol_CloseButtonActive、ImGuiCol_CloseButtonHovered，因为关闭叉号现在使用常规按钮颜色。
- 2018/03/08 (1.60) - 将 ImFont::DisplayOffset.y 的默认值从 +1 改为 0。修正了 Ascent/Descent 的舍入以匹配 TrueType 渲染器。如果你曾对 ImFont::DisplayOffset 进行过加减操作，请检查你的字体垂直对齐是否正确。
- 2018/03/03 (1.60) - 将 ImGuiStyleVar_Count_ 重命名为 ImGuiStyleVar_COUNT，将 ImGuiMouseCursor_Count_ 重命名为 ImGuiMouseCursor_COUNT，以与其他公共枚举保持一致。
- 2018/02/18 (1.60) - BeginDragDropSource()：暂时移除了可选的 mouse_button=0 参数，因为目前在许多情况下它并不真正实用。
- 2018/02/16 (1.60) - 废弃了 io.RenderDrawListsFn 回调，你可以在 ImGui::Render() 之后调用图形引擎的渲染函数。使用 ImGui::GetDrawData() 来获取要显示的 ImDrawData*。
- 2018/02/07 (1.60) - 重组了上下文处理逻辑使其更加明确，
- 你现在需要在应用程序开始时调用 ImGui::CreateContext()，并在结束时调用 ImGui::DestroyContext()。
- 移除了 Shutdown() 函数，因为 DestroyContext() 已具备此功能。
- 您可以向 CreateContext() 传递一个 ImFontAtlas* 指针，以便在多个上下文之间共享字体图集。否则，CreateContext() 将创建其自身的字体图集实例。
- 移除了 CreateContext() 中的分配器参数，现在这些参数通过 SetAllocatorFunctions() 进行设置，并由所有上下文共享。
- 移除了默认的全局上下文和字体图集实例，这些实例曾给 DLL 重新加载用户以及多上下文用户带来困扰。
- 2018/01/31 (1.60) - 将示例 TTF 文件从 extra_fonts/ 移动到了 misc/fonts/。如果您直接从 imgui 仓库加载文件，可能需要更新您的路径。
- 2018/01/11 (1.60) - 废弃了 IsAnyWindowHovered()，改为使用 IsWindowHovered(ImGuiHoveredFlags_AnyWindow)。保留了重定向函数（即将废弃）。
- 2018/01/11 (1.60) - 废弃了 IsAnyWindowFocused()，改为使用 IsWindowFocused(ImGuiFocusedFlags_AnyWindow)。保留了重定向函数（即将废弃）。
- 2018/01/03 (1.60) - 将 ImGuiSizeConstraintCallback 重命名为 ImGuiSizeCallback，将 ImGuiSizeConstraintCallbackData 重命名为 ImGuiSizeCallbackData。
- 2017/12/29 (1.60) - 移除了 CalcItemRectClosestPoint()，该函数很奇怪且除了示例代码外基本无人使用。如果你需要它，在本地自行实现也很容易。
- 2017/12/24 (1.53) - 将标志性的 ShowTestWindow() 函数重命名为 ShowDemoWindow()。保留了重定向函数（后续将废弃）。
- 2017/12/21 (1.53) - ImDrawList：为了保持一致性，并将 style.AntiAliasedShapes 重命名为 style.AntiAliasedFill，以此作为一种显式中断在运行时操作这些标志的代码的方式。你现在可以操作 ImDrawList::Flags。
- 2017/12/21 (1.53) - ImDrawList：移除了 ImDrawList::AddPolyline() 和 ImDrawList::AddConvexPolyFilled() 的最后一个参数 'bool anti_aliased = true'。如果需要在帧期间切换它们，请优先操作 ImDrawList::Flags。
- 2017/12/14 (1.53) - 在子窗口上使用 ImGuiWindowFlags_NoScrollWithMouse 标志会将鼠标滚轮事件转发至父窗口，除非同时设置了 ImGuiWindowFlags_NoInputs 或 ImGuiWindowFlags_NoScrollbar。
- 2017/12/13 (1.53) - 将 GetItemsLineHeightWithSpacing() 重命名为 GetFrameHeightWithSpacing()。保留了重定向函数（即将废弃）。
- 2017/12/13 (1.53) - 废弃了 IsRootWindowFocused()，改为使用 IsWindowFocused(ImGuiFocusedFlags_RootWindow)。保留了重定向函数（即将废弃）。
- 废弃了 IsRootWindowOrAnyChildFocused()，改为使用 IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows)。保留了重定向函数（即将废弃）。
- 2017/12/12 (1.53) - 将 ImGuiTreeNodeFlags_AllowOverlapMode 重命名为 ImGuiTreeNodeFlags_AllowItemOverlap。保留了重定向枚举（即将废弃）。
- 2017/12/10 (1.53) - 移除了 SetNextWindowContentWidth()，建议使用 SetNextWindowContentSize()。保留了重定向函数（即将废弃）。
- 2017/11/27 (1.53) - 将 ImGuiTextBuffer::append() 辅助函数重命名为 appendf()，将 appendv() 重命名为 appendfv()。如果你在代码中复制了“Log”演示代码，它使用了 appendv()，因此需要重命名。
- 2017/11/18 (1.53) - 样式、Begin：移除了 ImGuiWindowFlags_ShowBorders 窗口标志。边框现在完全在 ImGuiStyle 结构中设置（例如参见 style.FrameBorderSize, style.WindowBorderSize）。使用 ImGui::ShowStyleEditor() 来查看它们。
请注意，样式系统将持续演进（有望在 2018 年第一季度稳定下来），因此自定义样式可能会随着时间的推移而出现细微的损坏。建议您使用 StyleColorsClassic()、StyleColorsDark()、StyleColorsLight() 函数。
- 2017/11/18 (1.53) - 样式：移除了 ImGuiCol_ComboBg，转而让组合框使用 ImGuiCol_PopupBg 以保持一致性。
- 2017/11/18 (1.53) - 样式：将 ImGuiCol_ChildWindowBg 重命名为 ImGuiCol_ChildBg。
- 2017/11/18 (1.53) - 样式：将 style.ChildWindowRounding 重命名为 style.ChildRounding，将 ImGuiStyleVar_ChildWindowRounding 重命名为 ImGuiStyleVar_ChildRounding。
- 2017/11/02 (1.53) - 废弃了 IsRootWindowOrAnyChildHovered()，改为使用 IsWindowHovered(ImGuiHoveredFlags_RootAndChildWindows)；
- 2017/10/24 (1.52) - 为了保持一致性，将 IMGUI_DISABLE_WIN32_DEFAULT_CLIPBOARD_FUNCS/IMGUI_DISABLE_WIN32_DEFAULT_IME_FUNCS 重命名为 IMGUI_DISABLE_WIN32_DEFAULT_CLIPBOARD_FUNCTIONS/IMGUI_DISABLE_WIN32_DEFAULT_IME_FUNCTIONS。
- 2017/10/20 (1.52) - 更改了 IsWindowHovered() 默认参数的行为，如果另一个窗口中有项目处于激活状态（例如将项目从另一个窗口点击拖动到此窗口），则返回 false。如果需要，可以使用新引入的 IsWindowHovered() 标志来请求此特定行为。
- 2017/10/20 (1.52) - 将 IsItemHoveredRect()/IsMouseHoveringWindow() 标记为废弃，改为使用为 IsItemHovered() 和 IsWindowHovered() 新引入的标志。详情请参阅 https://github.com/ocornut/imgui/issues/1382。
删除了在 1.51 版本中引入的 IsItemRectHovered()/IsWindowRectHovered() 名称，因为它们仅仅是为了与我们现在废弃的这两个函数保持命名一致。
IsItemHoveredRect() --> IsItemHovered(ImGuiHoveredFlags_RectOnly)
IsMouseHoveringAnyWindow() --> IsWindowHovered(ImGuiHoveredFlags_AnyWindow)
IsMouseHoveringWindow() --> IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByPopup | ImGuiHoveredFlags_AllowWhenBlockedByActiveItem) [古怪的旧行为]
- 2017/10/17 (1.52) - 将旧版的 5 参数 Begin() 标记为废弃（目前仍可用）。请改用 SetNextWindowSize() + Begin()！
- 2017/10/11 (1.52) - 将 AlignFirstTextHeightToWidgets() 重命名为 AlignTextToFramePadding()。保留了内联重定向函数（后续将废弃）。
- 2017/09/26 (1.52) - 将 ImFont::Glyph 重命名为 ImFontGlyph。保留了重定向类型定义（后续将废弃）。
- 2017/09/25 (1.52) - 移除了 SetNextWindowPosCenter()，因为 SetNextWindowPos() 现在具有可选的轴心（pivot）信息，可以实现相同及更多的功能。保留了重定向函数（后续将废弃）。
- 2017/08/25 (1.52) - 当鼠标不可用或缺失时，io.MousePos 需要设置为 ImVec2(-FLT_MAX,-FLT_MAX)。以前 ImVec2(-1,-1) 就足够了，但现在我们支持负的鼠标坐标。在您的后端中，如果需要支持不可用的鼠标，请确保将 "io.MousePos = ImVec2(-1,-1)" 替换为 "io.MousePos = ImVec2(-FLT_MAX,-FLT_MAX)"。
- 2017/08/22 (1.51) - 将 IsItemHoveredRect() 重命名为 IsItemRectHovered()。保留了内联重定向函数（即将废弃）。 -> (1.52) 请使用 IsItemHovered(ImGuiHoveredFlags_RectOnly)！
- 为保持一致性，将 IsMouseHoveringAnyWindow() 重命名为 IsAnyWindowHovered()。保留了内联重定向函数（即将废弃）。
- 为保持一致性，将 IsMouseHoveringWindow() 重命名为 IsWindowRectHovered()。保留了内联重定向函数（即将废弃）。
- 2017/08/20 (1.51) - 为了保持一致性，将 GetStyleColName() 重命名为 GetStyleColorName()。
- 2017/08/20 (1.51) - 增加了 PushStyleColor(ImGuiCol idx, ImU32 col) 重载，如果你正在使用带有隐式转换的 ImColor()，这*可能*会导致“模糊调用”编译错误。显式转换为 ImU32 或 ImVec4 即可修复。
- 2017/08/15 (1.51) - 将奇怪的 IMGUI_ONCE_UPON_A_FRAME 辅助宏标记为废弃。建议使用更明确的 ImGuiOnceUponAFrame 类型。
- 2017/08/15 (1.51) - 修改了 BeginPopupContextWindow() 的参数顺序，从 (const char*,int buttons,bool also_over_items) 改为 (const char*,int buttons,bool also_over_items)。请注意，大多数调用完全依赖于默认参数。
- 2017/08/13 (1.51) - 将 ImGuiCol_Column 重命名为 ImGuiCol_Separator，ImGuiCol_ColumnHovered 重命名为 ImGuiCol_SeparatorHovered，ImGuiCol_ColumnActive 重命名为 ImGuiCol_SeparatorActive。保留了重定向枚举（即将废弃）。
- 2017/08/11 (1.51) - 将 ImGuiSetCond_Always 重命名为 ImGuiCond_Always，ImGuiSetCond_Once 重命名为 ImGuiCond_Once，ImGuiSetCond_FirstUseEver 重命名为 ImGuiCond_FirstUseEver，ImGuiSetCond_Appearing 重命名为 ImGuiCond_Appearing。保留了重定向枚举（即将废弃）。
- 2017/08/09 (1.51) - 移除了 ValueColor() 辅助函数，它们等同于调用 Text(label) + SameLine() + ColorButton()。
- 2017/08/08 (1.51) - 移除了 ColorEditMode() 和 ImGuiColorEditMode，取而代之的是 ImGuiColorEditFlags 以及各个 Color*() 函数的参数。SetColorEditOptions() 允许初始化默认值，但用户仍可以通过右键上下文菜单进行更改。
- 将 `ColorEdit4(const char* label, float col[4], bool show_alpha = true)` 的原型修改为 `ColorEdit4(const char* label, float col[4], ImGuiColorEditFlags flags = 0)`，其中传入 flags = 0x01 是一个安全的空操作（嘿，这可疑的向后兼容性！）。- 请查看并运行 Demo 窗口中“Color/Picker Widgets”下的内容，以了解各种新增选项。
- 将极少使用的 `ColorButton(ImVec4 col, bool small_height = false, bool outline_border = true)` 的原型修改为 `ColorButton(const char* desc_id, ImVec4 col, ImGuiColorEditFlags flags = 0, ImVec2 size = ImVec2(0, 0))`。
- 2017/07/20 (1.51) - 移除了 `IsPosHoveringAnyWindow(ImVec2)`，该函数部分功能已损坏且具有误导性。现在会触发断言（ASSERT）并引导用户使用 `io.WantCaptureMouse`。
- 2017/05/26 (1.50) - 移除了 `ImFontConfig::MergeGlyphCenterV`，取而代之的是功能更丰富的 `ImFontConfig::GlyphOffset`。
- 2017/05/01 (1.50) - 为了更清晰，将 ImDrawList::PathFill()（极少直接使用）重命名为 ImDrawList::PathFillConvex()。
- 2016/11/06 (1.50) - BeginChild(const char*) 现在会将堆栈 ID 应用于提供的标签，这与其他函数保持一致，也是其本应有的行为。除非您（极不可能地）从堆栈 ID 的不同位置多次向同一个子窗口追加内容，否则这不会对您产生影响。如果是这种情况，请使用 GetID() 生成一个 ID，并使用该 ID 代替传递给 BeginChild() 的字符串。
- 2016/10/15 (1.50) - 避免在 io.SetClipboardTextFn/io.GetClipboardTextFn 指针中使用 'void* user_data' 参数。我们改为向其传递 io.ClipboardUserData。
- 2016/09/25 (1.50) - style.WindowTitleAlign 现在是一个 ImVec2 类型（ImGuiAlign 枚举已被移除）。设置为 (0.5f, 0.5f) 表示水平和垂直居中，(0.0f, 0.0f) 表示左上角，依此类推。
- 2016/07/30 (1.50) - 当 x > 0.0f 时，SameLine(x) 现在相对于当前列/组（如果有的话）的左侧，而不总是相对于窗口左侧。这在某种程度上一直是设计初衷，希望造成的影响能降到最低。
- 2016/05/12 (1.49) - 标题栏（使用 ImGuiCol_TitleBg/ImGuiCol_TitleBgActive 颜色）不再渲染在窗口背景（ImGuiCol_WindowBg 颜色）之上。
如果你的 TitleBg/TitleBgActive 的 Alpha 值为 1.0f，或者你使用的是默认主题，则不会受到影响；否则，如果 Alpha 值小于 1.0f，你需要调整自定义主题，以适应标题栏背后不再绘制 WindowBg 背景这一变化。
给定旧颜色和旧的 WindowBg 颜色，此辅助函数将把旧的 TitleBg/TitleBgActive 颜色转换为具有相同视觉输出的新颜色：
ImVec4 ConvertTitleBgCol(const ImVec4& win_bg_col, const ImVec4& title_bg_col) { float new_a = 1.0f - ((1.0f - win_bg_col.w) * (1.0f - title_bg_col.w)), k = title_bg_col.w / new_a; return ImVec4((win_bg_col.x * win_bg_col.w + title_bg_col.x) * k, (win_bg_col.y * win_bg_col.w + title_bg_col.y) * k, (win_bg_col.z * win_bg_col.w + title_bg_col.z) * k, new_a); }
如果这让你感到困惑，可以从旧截图中提取标题栏的 RGB 值，并将其应用于 TitleBg/TitleBgActive。或者你也可以通过调整 TitleBg 的颜色来创建 TitleBgActive。
- 2016/05/07 (1.49) - 移除了容易混淆的 GetInternalState()、GetInternalStateSize()、SetInternalState() 函数集。现在使用 CreateContext()、DestroyContext()、GetCurrentContext()、SetCurrentContext()。
- 2016/05/02 (1.49) - 将 SetNextTreeNodeOpened() 重命名为 SetNextTreeNodeOpen()，未设重定向。
- 2016/05/01 (1.49) - 废弃了 CollapsingHeader(const char* label, const char* str_id = NULL, bool display_frame = true, bool default_open = false) 的旧签名，因为其额外参数设计不佳且极少使用。在新 API 中，你可以将 "default_open = true" 标志替换为 CollapsingHeader(label, ImGuiTreeNodeFlags_DefaultOpen)。
- 2016/04/26 (1.49) - 将 ImDrawList::PushClipRect(ImVec4 rect) 更改为 ImDrawList::PushClipRect(Imvec2 min, ImVec2 max, bool intersect_with_current_clip_rect=false)。请注意，更高级别的 ImGui::PushClipRect() 是首选，因为它会在逻辑/控件级别进行裁剪，而 ImDrawList::PushClipRect() 仅影响渲染器。
- 2016/04/03 (1.48) - 移除了冗余的 style.WindowFillAlphaDefault 设置。请将默认背景 Alpha 值合并到 style.Colors[ImGuiCol_WindowBg] 及所有其他背景颜色值中。（参考 GitHub issue #337）。
- 2016/04/03 (1.48) - 将 ImGuiCol_TooltipBg 重命名为 ImGuiCol_PopupBg，供弹出窗口/菜单和工具提示使用。弹出窗口/菜单此前使用的是 ImGuiCol_WindowBg。（参考 GitHub issue #337）
- 2016/03/21 (1.48) - 将 GetWindowFont() 重命名为 GetFont()，将 GetWindowFontSize() 重命名为 GetFontSize()。保留了内联重定向函数（即将废弃）。
- 2016/03/02 (1.48) - InputText() 的补全/历史/常驻回调：如果你手动修改文本缓冲区（而不使用 DeleteChars()/InsertChars() 辅助函数），则需要维护 BufTextLen 字段。添加了一个断言。
- 2016/01/23 (1.48) - 修复了不遵守传递给 PushItemWidth() 的精确宽度的问题，此前它会在该宽度基础上额外增加 FramePadding.x*2。如果你之前进行了手动的像素级精确对齐，这可能会对你产生影响。
- 2015/12/27 (1.48) - 修复了 ImDrawList::AddRect()，该函数此前渲染的矩形在每个轴上都大出 1 像素。
- 2015/12/04 (1.47) - 将 Color() 辅助函数重命名为 ValueColor() —— 原名称容易引起误解，且很少使用，未来可能会被废弃。
- 2015/08/29 (1.45) - 随着水平滚动条的加入，我们修复了处理光标位置时出现的各种不一致问题。
GetCursorPos()/SetCursorPos() 函数现在包含了滚动量。这应该不会影响大多数用户，但请注意，SetCursorPosX(100.0f) 会将你置于距离起始 x 位置 +100 的地方（其中可能包含滚动偏移），而不是距离窗口左侧 +100 的地方。
GetContentRegionMax()/GetWindowContentRegionMin()/GetWindowContentRegionMax() 函数现在也包含滚动量。通常这些函数用于不会发生滚动的情况，所以可能不是问题，但仍请留意！
- 2015/08/29 (1.45) - 将 style.ScrollbarWidth 重命名为 style.ScrollbarSize
- 2015/08/05 (1.44) - 将 imgui.cpp 拆分为额外文件：imgui_demo.cpp、imgui_draw.cpp 和 imgui_internal.h，你需要将这些文件添加到你的项目中。
- 2015/07/18 (1.44) - 修复了 ImDrawList::PathArcTo() 和 PathArcToFast() 中的角度问题（1.43 版本引入），该问题曾导致角度无故偏移了一个额外的 PI
- 2015/07/14 (1.43) - 添加了新的 ImFontAtlas::AddFont() API。对于旧的 AddFont***，将 ImFontAtlas::AddFont** 函数中的 'font_no' 参数移至 ImFontConfig 结构体中。
你需要使用双线性过滤来渲染带纹理的三角形，以便从文本的亚像素定位中获益。
- 2015/07/08 (1.43) - 将渲染数据切换为使用索引渲染。这节省了大量的 CPU/GPU 资源，并使我们能够以极低的成本实现抗锯齿。
这一必要的更改将破坏你现有的渲染函数！修复方法非常简单。对此深表歉意 :(
- 如果你使用的是示例中提供的 imgui_impl_XXX.cpp 的原始副本，你只需要更新你的副本即可，可以忽略其余内容。
- io.RenderDrawListsFn 处理函数的签名已更改！
旧版：ImGui_XXXX_RenderDrawLists(ImDrawList** const cmd_lists, int cmd_lists_count)
新版：ImGui_XXXX_RenderDrawLists(ImDrawData* draw_data).
参数对应关系：'cmd_lists' 变为 'draw_data->CmdLists'，'cmd_lists_count' 变为 'draw_data->CmdListsCount'
ImDrawList：“commands”更名为“CmdBuffer”，“vtx_buffer”更名为“VtxBuffer”，新增“IdxBuffer”。
ImDrawCmd：“vtx_count”更名为“ElemCount”，“clip_rect”更名为“ClipRect”，“user_callback”更名为“UserCallback”，“texture_id”更名为“TextureId”。
- 现在每个 ImDrawList 都同时包含一个顶点缓冲区（vertex buffer）和一个索引缓冲区（index buffer）。对于每个命令，请使用索引缓冲区中的索引渲染 ElemCount/3 个三角形。
- 如果你确实无法渲染索引原语，可以调用 draw_data->DeIndexAllBuffers() 方法对缓冲区进行去索引化。这样做速度较慢且浪费 CPU/GPU 资源。建议优先使用索引渲染！
- 如果你不确定如何升级，请参考 examples/ 文件夹中的代码或在 GitHub 上提问。请务必升级！
- 2015/07/10 (1.43) - 将 SameLine() 的参数从 int 改为 float。
- 2015/07/02 (1.42) - 将 SetScrollPosHere() 重命名为 SetScrollFromCursorPos()。保留了内联重定向函数（即将废弃）。
- 2015/07/02 (1.42) - 将 GetScrollPosY() 重命名为 GetScrollY()。为了减少与其他滚动函数的混淆，这是必要的，因为位置（例如光标位置）并不等同于滚动量。
- 2015/06/14 (1.41) - 将 ImageButton() 的默认 bg_col 参数从 (0,0,0,1)（黑色）改为 (0,0,0,0)（透明） - 当纹理具有透明度时会产生差异
- 2015/06/14 (1.41) - 将 Selectable() API 从 (label, selected, size) 改为 (label, selected, flags, size)。尺寸覆盖（Size override）应该很少被用到。抱歉！
- 2015/05/31 (1.40) - 为保持一致性，将 GetWindowCollapsed() 重命名为 IsWindowCollapsed()。保留了内联重定向函数（即将废弃）。
- 2015/05/31 (1.40) - 为保持一致性，将 IsRectClipped() 重命名为 IsRectVisible()。请注意返回值是相反的！保留了内联重定向函数（即将废弃）。
- 2015/05/27 (1.40) - 从 Button() 中移除了第三个参数 'repeat_if_held' —— 抱歉！该参数很少使用且不符合一致性。请使用 PushButtonRepeat(true) / PopButtonRepeat() 来为所需的按钮启用重复触发。
- 2015/05/11 (1.40) - 更改了 BeginPopup() API，现在接受字符串标识符而非布尔值。ImGui 需要管理弹窗的打开/关闭状态。调用 OpenPopup() 来实际设置弹窗的“打开”状态。如果弹窗已打开，BeginPopup() 将返回 true。
- 2015/05/03 (1.40) - 移除了 style.AutoFitPadding，改用 style.WindowPadding 更为合理（默认值本就相同）。
- 2015/04/13 (1.38) - 将 IsClipped() 重命名为 IsRectClipped()。保留内联重定向函数直至 1.50 版本。
- 2015/04/09 (1.38) - 将 ImDrawList::AddArc() 重命名为 ImDrawList::AddArcFast()，以确保与未来 API 的兼容性。
- 2015/04/03 (1.38) - 移除了 ImGuiCol_CheckHovered、ImGuiCol_CheckActive，替换为更通用的 ImGuiCol_FrameBgHovered、ImGuiCol_FrameBgActive。
- 2014/04/03 (1.38) - 移除了对 SliderFloat() 使用 -FLT_MAX..+FLT_MAX 作为范围的支持。请改用 DragFloat() 或 Inputfloat()。
- 2015/03/17 (1.36) - 将 GetItemBoxMin()/GetItemBoxMax()/IsMouseHoveringBox() 重命名为 GetItemRectMin()/GetItemRectMax()/IsMouseHoveringRect()。保留内联重定向函数直至 1.50 版本。
- 2015/03/15 (1.36) - 将 style.TreeNodeSpacing 重命名为 style.IndentSpacing，将 ImGuiStyleVar_TreeNodeSpacing 重命名为 ImGuiStyleVar_IndentSpacing
- 2015/03/13 (1.36) - 将 GetWindowIsFocused() 重命名为 IsWindowFocused()。保留内联重定向函数至 1.50 版本。
- 2015/03/08 (1.35) - 将 style.ScrollBarWidth 重命名为 style.ScrollbarWidth（修改大小写）
- 2015/02/27 (1.34) - 将 OpenNextNode(bool) 重命名为 SetNextTreeNodeOpened(bool, ImGuiSetCond)。保留内联重定向函数至 1.50 版本。
- 2015/02/27 (1.34) - 将 ImGuiSetCondition_*** 重命名为 ImGuiSetCond_***，且 _FirstUseThisSession 变为 _Once。
- 2015/02/11 (1.32) - 将文本输入回调 ImGuiTextEditCallback 的返回类型从 void 改为 int。保留供未来使用，目前请返回 0。
- 2015/02/10 (1.32) - 将 GetItemWidth() 重命名为 CalcItemWidth()，以明确其不断演变的行为
- 2015/02/08 (1.31) - 将 GetTextLineSpacing() 重命名为 GetTextLineHeightWithSpacing()
- 2015/02/01 (1.31) - 移除了 IO.MemReallocFn（未使用）
- 2015/01/19 (1.30) - 将 ImGuiStorage::GetIntPtr()/GetFloatPtr() 重命名为 GetIntRef()/GetIntRef()，因为 Ptr 与实际的指针存储函数冲突。
- 2015/01/11 (1.30) - 字体/图像 API 重大变更！现在支持加载 TTF 文件。允许使用多种字体。不再需要 PNG 加载器。
- 2015/01/11 (1.30) - 移除了 GetDefaultFontData()。使用 io.Fonts->GetTextureData*() API 来获取未压缩的像素。
- 旧方法：const void* png_data; unsigned int png_size; ImGui::GetDefaultFontData(NULL, NULL, &png_data, &png_size); [..上传纹理至 GPU..];
- 新方法：unsigned char* pixels; int width, height; io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height); [..上传纹理至 GPU..]; io.Fonts->SetTexID(YourTexIdentifier);
现在您可以更灵活地加载多个 TTF 字体，并根据内部需求管理纹理缓冲区。现在建议使用双线性插值对字体纹理进行采样。
- 2015/01/11 (1.30) - 在传递给渲染函数的 ImDrawCmd 中添加了纹理标识符（我们现在可以渲染图像了）。请确保调用 io.Fonts->SetTexID()
- 2015/01/11 (1.30) - 移除了 IO.PixelCenterOffset（不再需要，可在用户投影矩阵中处理）
- 2015/01/11 (1.30) - 移除了 ImGui::IsItemFocused()，改为使用支持所有控件的 ImGui::IsItemActive()
- 2014/12/10 (1.18) - 移除了 SetNewWindowDefaultPos()，改为使用新的通用 API SetNextWindowPos(pos, ImGuiSetCondition_FirstUseEver)
- 2014/11/28 (1.17) - 将 IO.Font*** 选项移至 IO.Font-> 结构内部（FontYOffset、FontTexUvForWhite、FontBaseScale、FontFallbackGlyph）
- 2014/11/26 (1.17) - 重构了 IMGUI_ONCE_UPON_A_FRAME 辅助宏的语法，以提高编译器兼容性
- 2014/11/07 (1.15) - 将 IsHovered() 重命名为 IsItemHovered()
- 2014/10/02 (1.14) - 将 IMGUI_INCLUDE_IMGUI_USER_CPP 重命名为 IMGUI_INCLUDE_IMGUI_USER_INL，并将 imgui_user.cpp 重命名为 imgui_user.inl（对 IDE 更友好）
- 2014/09/25 (1.13) - 移除了 IO.SetClipboardTextFn 中的 'text_end' 参数（为了简化，字符串现在始终以零结尾）
- 2014/09/24 (1.12) - 将 SetFontScale() 重命名为 SetWindowFontScale()
- 2014/09/24 (1.12) - 将 IM_MALLOC/IM_REALLOC/IM_FREE 预处理器定义移至 IO.MemAllocFn/IO.MemReallocFn/IO.MemFreeFn
- 2014/08/30 (1.09) - 移除了 IO.FontHeight（现在自动计算）
- 2014/08/30 (1.09) - 将 IMGUI_FONT_TEX_UV_FOR_WHITE 预处理器定义移至 IO.FontTexUvForWhite
- 2014/08/28 (1.09) - 在多项渲染修复后，更改了 IO.PixelCenterOffset 的行为


常见问题解答 (FAQ)
================================


在线阅读所有解答：
https://www.dearimgui.com/faq 或 https://github.com/ocornut/imgui/blob/master/docs/FAQ.md（相同链接）
在本地阅读所有解答（使用文本编辑器，或最好使用 Markdown 查看器）：
docs/FAQ.md
此处抄录了部分解答，以便于在代码中进行搜索。


问答：基础知识
===========


问：文档在哪里？
答：目前该库的文档较少，且要求使用者熟悉 C/C++。
- 运行 examples/ 目录下的示例程序并进行探索。
- 阅读入门指南 (https://github.com/ocornut/imgui/wiki/Getting-Started)。
- 参阅 imgui_demo.cpp 中的示例代码，特别是 ImGui::ShowDemoWindow() 函数。
- 示例涵盖了 Dear ImGui 的大部分功能，因此你可以通过阅读代码并查看其输出来学习。
- 参阅 imgui.cpp 顶部以及 imgui.h 中的文档和注释。
- 在该目录下提供了 20 多个使用 OpenGL/DirectX 等技术的独立示例应用程序：
examples/ 文件夹解释了如何将 Dear ImGui 集成到您自己的引擎/应用程序中。
- Wiki (https://github.com/ocornut/imgui/wiki) 包含许多资源和链接。
- 术语表 (https://github.com/ocornut/imgui/wiki/Glossary) 页面也可能很有用。
- 您的编程 IDE 是您的好帮手，通过查找类型或函数声明可以找到相关的注释说明
与其关联。


问：这个库叫什么名字？
问：Dear ImGui 与传统的 UI 工具包有什么区别？
问：我应该获取哪个版本？
>> 本库名为 "Dear ImGui"，请不要简称为 "ImGui" :)
>> 详情请参阅 https://www.dearimgui.com/faq。


问答：集成
================


问：如何开始使用？
答：请阅读 https://github.com/ocornut/imgui/wiki/Getting-Started。阅读上方的“程序员指南（PROGRAMMER GUIDE）”。阅读 examples/README.txt。


问：我该如何判断是将鼠标/键盘输入分发给 Dear ImGui 还是我的应用程序？
答：你应该读取 'io.WantCaptureMouse'、'io.WantCaptureKeyboard' 和 'io.WantTextInput' 标志位！
>> 请参阅 https://www.dearimgui.com/faq 获取详尽的解答。你务必要阅读此内容。


问：我该如何启用键盘或手柄控制？
问：我该如何在没有鼠标、键盘或屏幕的机器上使用它？（输入共享、远程显示）
问：我将 Dear ImGui 集成到了我的引擎中，但显示的不是文本而是小方块……
问：我将 Dear ImGui 集成到了我的引擎中，当我移动窗口时，一些元素会出现裁剪或消失的情况……
问：我将 Dear ImGui 集成到了我的引擎中，但有些元素显示在了预期的窗口边界之外……
>> 请参阅 https://www.dearimgui.com/faq


问与答：用法
----------


问：关于 ID 栈（ID Stack）系统……
- 为什么我的控件在点击时没有反应？
- 如何创建带有空标签的控件？
- 如何创建具有相同标签的多个控件？
- 如何创建具有相同标题的多个窗口？
问：我该如何显示图像？什么是 ImTextureID，它是如何工作的？
问：我该如何使用自定义的数学类型来替代 ImVec2？
问：我该如何与标准 C++ 类型（如 std::string 和 std::vector）进行交互？
问：我该如何显示自定义形状？（使用底层的 ImDrawList API）
>> 参见 https://www.dearimgui.com/faq


问答：字体、文本
================


问：我该如何在应用程序中处理 DPI？
问：我该如何加载默认以外的其他字体？
问：我该如何在应用程序中轻松使用图标？
问：我该如何加载多个字体？
问：我该如何显示和输入非拉丁字符，如中文、日文、韩文、西里尔文？
>> 请参阅 https://www.dearimgui.com/faq 和 https://github.com/ocornut/imgui/blob/master/docs/FONTS.md


常见问题解答：疑虑
=============


问：谁在应用 Dear ImGui？
问：可以用 Dear ImGui 开发复杂或专业的工具吗？
问：可以更换 Dear ImGui 的外观皮肤吗？
问：为什么要使用 C++（而不是 C）？
>> 请参阅 https://www.dearimgui.com/faq


问与答：社区
==============


问：我该如何提供帮助？
A：- 企业用户：如果您所在的单位正在使用 Dear ImGui，请联系 "omar AT dearimgui DOT com"！
我们可以共同探讨贵公司资助开发的各种方式，包括开具发票的技术支持、维护合同或赞助协议。
这是您能为 Dear ImGui 做的最有意义的事情之一。随着资金的增加，我们能够持续投入并扩大该项目的开发工作。
>>> 详见 https://github.com/ocornut/imgui/wiki/Funding
- 企业用户：您还可以购买 Dear ImGui 自动化/测试引擎的许可证。
- 如果您对 Dear ImGui 和 C++ 有丰富经验，请查看 GitHub issue 和 Wiki，看看您想如何提供帮助以及能提供哪些帮助！
- 通过开发博客文章、推文、截图或在某处提及等方式，公开您对 Dear ImGui 的使用情况。
您可以在展示帖（gallery threads）中发布截图或链接。视觉效果非常理想，因为它们能启发其他程序员。
即便没有视觉展示，公开你对 Dear ImGui 的使用也有助于提升该库的信誉，并帮助其他团队和程序员做出决策。
- 如果你遇到问题或需要对库进行底层修改，即使你不期望获得任何支持，分享你的问题（在 GitHub 上或私下分享）也是非常有用的。


*/


//-------------------------------------------------------------------------
// [SECTION] INCLUDES
//-------------------------------------------------------------------------