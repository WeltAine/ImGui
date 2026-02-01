// dear imgui, v1.92.6 WIP
// (头文件)


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
// 演示程序的 Web 版本 .... https://pthom.github.io/imgui_manual_online/manual/imgui_manual.html (附带源码浏览器)


// 针对初次使用时遇到编译/链接/运行问题的用户：
// 如果在上述资源中找不到解决方案，请在 https://github.com/ocornut/imgui/discussions 中发帖。
// 除此之外的所有问题都应在“Issues”中提问！我们正在那里建立一个交叉引用的知识库。
// 自 1.92 版本起，我们鼓励将字体加载相关的问题也发布在“Issues”中。


// 库版本
//（整数编码为 XYYZZ，用于 #if 预处理器条件判断，例如 '#if IMGUI_VERSION_NUM >= 12345'）
#define IMGUI_VERSION "1.92.6 WIP"
#define IMGUI_VERSION_NUM 19259
#define IMGUI_HAS_TABLE // 已添加 BeginTable() - 始于 IMGUI_VERSION_NUM >= 18000
#define IMGUI_HAS_TEXTURES // 已添加 ImGuiBackendFlags_RendererHasTextures - 始于 IMGUI_VERSION_NUM >= 19198


/*


本文件索引：
// [SECTION] 头文件杂项
// [SECTION] 前向声明与基础类型
// [SECTION] 纹理标识符 (ImTextureID, ImTextureRef)
// [SECTION] Dear ImGui 终端用户 API 函数
// [SECTION] 标志与枚举 (Flags & Enumerations)
// [SECTION] 表格 API 标志与结构 (ImGuiTableFlags, ImGuiTableColumnFlags, ImGuiTableRowFlags, ImGuiTableBgTarget, ImGuiTableSortSpecs, ImGuiTableColumnSortSpecs)
// [SECTION] 辅助类：调试日志、内存分配宏、ImVector<>
// [SECTION] ImGuiStyle
// [SECTION] ImGuiIO
// [SECTION] 杂项数据结构 (ImGuiInputTextCallbackData, ImGuiSizeCallbackData, ImGuiPayload)
// [SECTION] 辅助类 (ImGuiOnceUponAFrame, ImGuiTextFilter, ImGuiTextBuffer, ImGuiStorage, ImGuiListClipper, 数学运算符, ImColor)
// [SECTION] 多选 API 标志与结构 (ImGuiMultiSelectFlags, ImGuiMultiSelectIO, ImGuiSelectionRequest, ImGuiSelectionBasicStorage, ImGuiSelectionExternalStorage)
// [SECTION] 绘制 API (ImDrawCallback, ImDrawCmd, ImDrawIdx, ImDrawVert, ImDrawChannel, ImDrawListSplitter, ImDrawFlags, ImDrawListFlags, ImDrawList, ImDrawData)
// [SECTION] 纹理 API (ImTextureFormat, ImTextureStatus, ImTextureRect, ImTextureData)
// [SECTION] 字体 API (ImFontConfig, ImFontGlyph, ImFontGlyphRangesBuilder, ImFontAtlasFlags, ImFontAtlas, ImFontBaked, ImFont)
// [SECTION] 视口 (ImGuiViewportFlags, ImGuiViewport)
// [SECTION] ImGuiPlatformIO + 其他平台相关接口 (ImGuiPlatformImeData)
// [SECTION] 已废弃的函数和类型


*/


#pragma once


// 包含编译时选项的配置文件
// (编辑 imconfig.h 或在构建系统中执行 '#define IMGUI_USER_CONFIG "myfilename.h"')
#ifdef IMGUI_USER_CONFIG
#include IMGUI_USER_CONFIG
#endif
#include "imconfig.h"


#ifndef IMGUI_DISABLE


//-----------------------------------------------------------------------------
// [SECTION] 标头杂项
//-----------------------------------------------------------------------------


// 包含文件
#include <float.h> // FLT_MIN, FLT_MAX
#include <stdarg.h> // va_list, va_start, va_end
#include <stddef.h> // ptrdiff_t, NULL
#include <string.h> // memset, memmove, memcpy, strlen, strchr, strcpy, strcmp


// 定义所有 API 符号声明的属性（例如 Windows 下的 DLL）
// IMGUI_API 用于核心 imgui 函数，IMGUI_IMPL_API 用于默认后端文件 (imgui_impl_xxx.h)
// 不建议通过共享库使用 dear imgui：我们不保证向后或向前的 ABI 兼容性 + 这是一个调用密集型库，函数调用开销会累积。
#ifndef IMGUI_API
#define IMGUI_API
#endif
#ifndef IMGUI_IMPL_API
#define IMGUI_IMPL_API IMGUI_API
#endif


// 辅助宏
//（注意：使用 NDEBUG 编译通常会将 assert() 剥离为空，这**不**被推荐，因为我们使用断言来提醒程序员的错误。）
#ifndef IM_ASSERT
#include <assert.h>
#define IM_ASSERT(_EXPR) assert(_EXPR) // 你可以通过编辑 imconfig.h 来覆盖默认的断言处理程序
#endif
#define IM_COUNTOF(_ARR) ((int)(sizeof(_ARR) / sizeof(*(_ARR)))) // 静态 C 风格数组的大小。切勿用于指针！
#define IM_UNUSED(_VAR) ((void)(_VAR)) // 用于消除“变量未使用的警告”。通常很有用，因为断言（asserts）可能会在最终构建中被移除。
#define IM_STRINGIFY_HELPER(_EXPR) #_EXPR
#define IM_STRINGIFY(_EXPR) IM_STRINGIFY_HELPER(_EXPR) // 预处理器惯用法，用于将整数或宏等内容字符串化。


// 检查编译后的 imgui 代码与调用者之间的版本和结构布局是否匹配。详见 DebugCheckVersionAndDataLayout() 上方的注释。
#define IMGUI_CHECKVERSION() ImGui::DebugCheckVersionAndDataLayout(IMGUI_VERSION, sizeof(ImGuiIO), sizeof(ImGuiStyle), sizeof(ImVec2), sizeof(ImVec4), sizeof(ImDrawVert), sizeof(ImDrawIdx))


// 辅助宏 - IM_FMTARGS, IM_FMTLIST：为我们的格式化函数应用 printf 风格的警告检查。
// （MSVC 通过 SAL 注解提供等效机制，但它要求宏位于不同的
// 位置。例如：#include <sal.h> + void myprintf(_Printf_format_string_ const char* format, ...)，
// 且仅在进行代码分析（Code Analysis）时有效，而非普通编译时）。
// （参见 https://github.com/ocornut/imgui/issues/8871 获取在 MSVC 代码分析中启用此功能的补丁）
#if !defined(IMGUI_USE_STB_SPRINTF) && defined(__MINGW32__) && !defined(__clang__)
#define IM_FMTARGS(FMT) __attribute__((format(gnu_printf, FMT, FMT+1)))
#define IM_FMTLIST(FMT) __attribute__((format(gnu_printf, FMT, 0)))
#elif !defined(IMGUI_USE_STB_SPRINTF) && (defined(__clang__) || defined(__GNUC__))
#define IM_FMTARGS(FMT) __attribute__((format(printf, FMT, FMT+1)))
#define IM_FMTLIST(FMT) __attribute__((format(printf, FMT, 0)))
#else
#define IM_FMTARGS(FMT)
#define IM_FMTLIST(FMT)
#endif


// 在函数头/尾中禁用一些 MSVC 最激进的调试运行时检查（用于某些简单/低级函数）
#if defined(_MSC_VER) && !defined(__clang__) && !defined(__INTEL_COMPILER) && !defined(IMGUI_DEBUG_PARANOID)
#define IM_MSVC_RUNTIME_CHECKS_OFF __pragma(runtime_checks("",off)) __pragma(check_stack(off)) __pragma(strict_gs_check(push,off))
#define IM_MSVC_RUNTIME_CHECKS_RESTORE __pragma(runtime_checks("",restore)) __pragma(check_stack()) __pragma(strict_gs_check(pop))
#else
#define IM_MSVC_RUNTIME_CHECKS_OFF
#define IM_MSVC_RUNTIME_CHECKS_RESTORE
#endif


// 警告
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable: 26495) // [静态分析器] 变量 'XXX' 未初始化。请始终初始化成员变量 (type.6)。
#endif
#if defined(__clang__)
#pragma clang diagnostic push
#if __has_warning("-Wunknown-warning-option")
#pragma clang diagnostic ignored "-Wunknown-warning-option" // 警告：未知的警告组 'xxx'
#endif
#pragma clang diagnostic ignored "-Wunknown-pragmas" // 警告：未知的警告组 'xxx'
#pragma clang diagnostic ignored "-Wold-style-cast" // 警告：使用了旧式转换（C 风格强制转换）
#pragma clang diagnostic ignored "-Wfloat-equal" // 警告：使用 == 或 != 比较浮点数是不安全的
#pragma clang diagnostic ignored "-Wzero-as-null-pointer-constant" // 警告：将零用作空指针常量
#pragma clang diagnostic ignored "-Wreserved-identifier" // 警告：标识符 '_Xxx' 被保留，因为它以 '_' 后紧跟大写字母开头
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage" // 警告：'xxx' 是用于缓冲区访问的不安全指针
#pragma clang diagnostic ignored "-Wnontrivial-memaccess" // 警告：'memset' 调用中的第一个参数是指向非平凡可复制类型的指针
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpragmas" // 警告：'#pragma GCC diagnostic' 类型后出现未知选项
#pragma GCC diagnostic ignored "-Wfloat-equal" // 警告：使用 '==' 或 '!=' 比较浮点数是不安全的
#pragma GCC diagnostic ignored "-Wclass-memaccess" // [__GNUC__ >= 8] 警告：'memset/memcpy' 正在清除/写入类型为 'xxxx' 的非平凡复制赋值对象；请改用赋值或值初始化
#endif


//-----------------------------------------------------------------------------
// [SECTION] 前向声明与基础类型
//-----------------------------------------------------------------------------


// 标量数据类型
typedef unsigned int ImGuiID;// 控件使用的唯一 ID（通常是对一组字符串栈进行哈希处理的结果）
typedef signed char ImS8; // 8 位有符号整数
typedef unsigned char ImU8; // 8 位无符号整数
typedef signed short ImS16; // 16 位有符号整数
typedef unsigned short ImU16; // 16 位无符号整数
typedef signed int ImS32; // 32 位有符号整数 == int
typedef unsigned int ImU32; // 32 位无符号整数（常用于存储打包后的颜色）
typedef signed long long ImS64; // 64 位有符号整数
typedef unsigned long long ImU64; // 64 位无符号整数


// 前向声明：ImDrawList, ImFontAtlas 层
struct ImDrawChannel; // 用于乱序输出绘制命令的临时存储，由 ImDrawListSplitter 和 ImDrawList::ChannelsSplit() 使用
struct ImDrawCmd; // 父级 ImDrawList 中的单个绘制命令（通常对应 1 个 GPU 绘制调用，除非它是回调函数）
struct ImDrawData; // 渲染当前帧所需的所有绘制命令列表 + 用于投影矩阵的位置/尺寸坐标。
struct ImDrawList; // 单个绘制命令列表（通常每个窗口一个，从概念上讲，你可以将其视为一个动态的“网格”构建器）
struct ImDrawListSharedData; // 多个绘制列表之间共享的数据（通常由父级 ImGui 上下文拥有，但你也可以自行创建一个）
struct ImDrawListSplitter; // 辅助类，用于将绘制列表拆分为不同的层，这些层可以不按顺序进行绘制，最后再合并。
struct ImDrawVert; // 单个顶点（位置 + UV + 颜色 = 默认 20 字节。可通过 IMGUI_OVERRIDE_DRAWVERT_STRUCT_LAYOUT 覆盖布局）
struct ImFont; // 父级 ImFontAtlas 中单个字体的运行时数据
struct ImFontAtlas; // 多个字体的运行时数据，可将多个字体烘焙到单个纹理中，包含 TTF/OTF 字体加载器
struct ImFontAtlasBuilder; // 用于构建 ImFontAtlas 的不透明存储结构
struct ImFontAtlasRect; // 使用自定义矩形时 ImFontAtlas::GetCustomRect() 的输出结果
struct ImFontBaked; // 特定尺寸下 ImFont 的烘焙数据
struct ImFontConfig; // 添加字体或合并字体时的配置数据
struct ImFontGlyph; // 单个字体字形（码点 + 在 ImFontAtlas 中的坐标 + 偏移量）
struct ImFontGlyphRangesBuilder; // 从文本/字符串数据构建字形范围的辅助类
struct ImFontLoader; // 字体加载后端（如 stb_truetype、FreeType 等）的不透明接口。
struct ImTextureData; // Dear ImGui 所使用的纹理的规格和像素存储。
struct ImTextureRect; // 纹理内矩形区域的坐标。
struct ImColor; // 用于创建颜色的辅助函数，可转换为 u32 或 float4（*已废弃* 请避免使用）


// 前向声明：ImGui 层
struct ImGuiContext; // Dear ImGui 上下文（不透明结构，除非包含 imgui_internal.h）
struct ImGuiIO; // 应用程序与 ImGui 之间的主要配置和 I/O（另请参阅：ImGuiPlatformIO）
struct ImGuiInputTextCallbackData; // 使用自定义 ImGuiInputTextCallback 时 InputText() 的共享状态（罕见/高级用法）
struct ImGuiKeyData; // 用于 ImGuiIO 以及 IsKeyDown()、IsKeyPressed() 等函数的数据存储。
struct ImGuiListClipper; // 用于手动裁剪大列表项目的辅助结构体
struct ImGuiMultiSelectIO; // 用于与 BeginMultiSelect()/EndMultiSelect() 模块交互的结构体
struct ImGuiOnceUponAFrame; // 用于确保每帧代码块运行次数不超过一次的辅助结构体
struct ImGuiPayload; // 用于拖放操作的用户数据负载
struct ImGuiPlatformIO; // 平台/渲染器后端与 ImGui 之间的接口（例如剪贴板、IME 钩子）。它是 ImGuiIO 的扩展。在 docking 分支中，它被扩展以支持多视口。
struct ImGuiPlatformImeData; // 用于 io.PlatformSetImeDataFn() 函数的平台 IME 数据。
struct ImGuiSelectionBasicStorage; // 可选的辅助结构，用于存储多选状态并应用多选请求。
struct ImGuiSelectionExternalStorage; // 可选的辅助结构，用于将多选请求应用于现有的可随机访问的存储。
struct ImGuiSelectionRequest; // 选择请求（存储于 ImGuiMultiSelectIO 中）
struct ImGuiSizeCallbackData; // 使用 SetNextWindowSizeConstraints() 时的回调数据（罕见/高级用法）
struct ImGuiStorage; // 键->值存储辅助类（按键排序的容器）
struct ImGuiStoragePair; // 键->值存储辅助类（键值对）
struct ImGuiStyle; // 用于样式/颜色的运行时数据
struct ImGuiTableSortSpecs; // 表格的排序规格（通常处理单列的排序规格，有时也处理多列）
struct ImGuiTableColumnSortSpecs; // 表格中单列的排序规格
struct ImGuiTextBuffer; // 用于持有并追加文本内容的辅助类（类似于 string builder）
struct ImGuiTextFilter; // 用于解析和应用文本过滤器的辅助结构体（例如 "aaaaa[,bbbbb][,ccccc]"）
struct ImGuiViewport; // 平台窗口（在 'master' 分支中始终只有一个），未来可能代表平台显示器


// 枚举
// - 我们不常使用强类型枚举（strongly typed enums），因为它们会增加限制（无法在私有代码中扩展、无法在位域中存储类型、迭代时需要额外的类型转换）
// - 提示：利用编程 IDE 的导航功能点击下方“中间列”的名称，即可找到对应的标志（flags）或枚举（enum）列表！
// - 在 Visual Studio 中：Ctrl+逗号（“编辑.转到全部”）可以追踪注释中的符号，而 Ctrl+F12（“编辑.转到实现”）则不行。
// - 在安装了 Visual Assist 的 Visual Studio 中：Alt+G（“VAssistX.GoToImplementation”）也可以追踪注释中的符号。
// - 在 VS Code、CLion 等编辑器中：按住 Ctrl 并单击可以追踪注释中的符号。
enum ImGuiDir : int; // -> enum ImGuiDir // 枚举：基本方向（左、右、上、下）
enum ImGuiKey : int; // -> enum ImGuiKey // 枚举：按键标识符（ImGuiKey_XXX 或 ImGuiMod_XXX 值）
enum ImGuiMouseSource : int; // -> enum ImGuiMouseSource // 枚举：鼠标输入源标识符（鼠标、触摸屏、手写笔）
enum ImGuiSortDirection : ImU8; // -> enum ImGuiSortDirection // 枚举：排序方向（升序或降序）
typedef int ImGuiCol; // -> enum ImGuiCol_ // 枚举：用于样式的颜色标识符
typedef int ImGuiCond; // -> enum ImGuiCond_ // 枚举：许多 Set*() 函数的触发条件
typedef int ImGuiDataType; // -> enum ImGuiDataType_ // 枚举：主要数据类型
typedef int ImGuiMouseButton; // -> enum ImGuiMouseButton_ // 枚举：鼠标按键标识符 (0=左键, 1=右键, 2=中键)
typedef int ImGuiMouseCursor; // -> enum ImGuiMouseCursor_ // 枚举：鼠标光标形状
typedef int ImGuiStyleVar; // -> enum ImGuiStyleVar_ // 枚举：样式变量标识符
typedef int ImGuiTableBgTarget; // -> enum ImGuiTableBgTarget_ // 枚举：TableSetBgColor() 的颜色目标


// 标志位（声明为 int 以允许作为标志使用且无额外开销，同时避免污染文件顶部）
// - 提示：利用编程 IDE 的导航功能点击下方“中间列”的名称，即可找到对应的标志（flags）或枚举（enum）列表！
// - 在 Visual Studio 中：Ctrl+逗号（“编辑.转到全部”）可以追踪注释中的符号，而 Ctrl+F12（“编辑.转到实现”）则不行。
// - 在安装了 Visual Assist 的 Visual Studio 中：Alt+G（“VAssistX.GoToImplementation”）也可以追踪注释中的符号。
// - 在 VS Code、CLion 等编辑器中：按住 Ctrl 并单击可以追踪注释中的符号。
typedef int ImDrawFlags; // -> enum ImDrawFlags_ // 标志：用于 ImDrawList 函数
typedef int ImDrawListFlags; // -> enum ImDrawListFlags_ // 标志：用于 ImDrawList 实例
typedef int ImDrawTextFlags; // -> enum ImDrawTextFlags_ // 内部使用，请勿使用！
typedef int ImFontFlags; // -> enum ImFontFlags_ // 标志：用于 ImFont
typedef int ImFontAtlasFlags; // -> enum ImFontAtlasFlags_ // 标志：用于 ImFontAtlas
typedef int ImGuiBackendFlags; // -> enum ImGuiBackendFlags_ // 标志：用于 io.BackendFlags
typedef int ImGuiButtonFlags; // -> enum ImGuiButtonFlags_ // 标志：用于 InvisibleButton()
typedef int ImGuiChildFlags; // -> enum ImGuiChildFlags_ // 标志：用于 BeginChild()
typedef int ImGuiColorEditFlags; // -> enum ImGuiColorEditFlags_ // 标志：用于 ColorEdit4()、ColorPicker4() 等
typedef int ImGuiConfigFlags; // -> enum ImGuiConfigFlags_ // 标志：用于 io.ConfigFlags
typedef int ImGuiComboFlags; // -> enum ImGuiComboFlags_ // 标志：用于 BeginCombo()
typedef int ImGuiDragDropFlags; // -> enum ImGuiDragDropFlags_ // 标志：用于 BeginDragDropSource()、AcceptDragDropPayload()
typedef int ImGuiFocusedFlags; // -> enum ImGuiFocusedFlags_ // 标志：用于 IsWindowFocused()
typedef int ImGuiHoveredFlags; // -> enum ImGuiHoveredFlags_ // 标志：用于 IsItemHovered()、IsWindowHovered() 等
typedef int ImGuiInputFlags; // -> enum ImGuiInputFlags_ // 标志：用于 Shortcut()、SetNextItemShortcut()
typedef int ImGuiInputTextFlags; // -> enum ImGuiInputTextFlags_ // 标志：用于 InputText()、InputTextMultiline()
typedef int ImGuiItemFlags; // -> enum ImGuiItemFlags_ // 标志：用于 PushItemFlag()，由所有项目共享
typedef int ImGuiKeyChord; // -> ImGuiKey | ImGuiMod_XXX // 标志：用于 IsKeyChordPressed()、Shortcut() 等。一个 ImGuiKey 可选地与一个或多个 ImGuiMod_XXX 值进行按位或运算。
typedef int ImGuiListClipperFlags; // -> enum ImGuiListClipperFlags_// 标志：用于 ImGuiListClipper
typedef int ImGuiPopupFlags; // -> enum ImGuiPopupFlags_ // 标志：用于 OpenPopup*()、BeginPopupContext*()、IsPopupOpen()
typedef int ImGuiMultiSelectFlags; // -> enum ImGuiMultiSelectFlags_// 标志：用于 BeginMultiSelect()
typedef int ImGuiSelectableFlags; // -> enum ImGuiSelectableFlags_ // 标志：用于 Selectable()
typedef int ImGuiSliderFlags; // -> enum ImGuiSliderFlags_ // 标志：用于 DragFloat(), DragInt(), SliderFloat(), SliderInt() 等
typedef int ImGuiTabBarFlags; // -> enum ImGuiTabBarFlags_ // 标志：用于 BeginTabBar()
typedef int ImGuiTabItemFlags; // -> enum ImGuiTabItemFlags_ // 标志：用于 BeginTabItem()
typedef int ImGuiTableFlags; // -> enum ImGuiTableFlags_ // 标志：用于 BeginTable()
typedef int ImGuiTableColumnFlags; // -> enum ImGuiTableColumnFlags_// 标志：用于 TableSetupColumn()
typedef int ImGuiTableRowFlags; // -> enum ImGuiTableRowFlags_ // 标志：用于 TableNextRow()
typedef int ImGuiTreeNodeFlags; // -> enum ImGuiTreeNodeFlags_ // 标志：用于 TreeNode()、TreeNodeEx()、CollapsingHeader()
typedef int ImGuiViewportFlags; // -> enum ImGuiViewportFlags_ // 标志：用于 ImGuiViewport
typedef int ImGuiWindowFlags; // -> enum ImGuiWindowFlags_ // 标志：用于 Begin()、BeginChild()


// 字符类型
//（我们在 API 中通常使用 UTF-8 编码的字符串。这是专门用于存储键盘输入和显示的解码后字符）
typedef unsigned int ImWchar32; // 单个解码后的 U32 字符/码点。在字符串中使用时，我们会将其编码为多字节 UTF-8。
typedef unsigned short ImWchar16; // 单个解码后的 U16 字符/码点。在字符串中使用时，我们会将其编码为多字节 UTF-8。
#ifdef IMGUI_USE_WCHAR32 // ImWchar [可配置类型：在 imconfig.h 中通过 '#define IMGUI_USE_WCHAR32' 进行覆盖，以支持 Unicode 第 1-16 平面]
typedef ImWchar32 ImWchar;
#else
typedef ImWchar16 ImWchar;
#endif


// 使用 BeginMultiSelect() 时的多选项目索引或标识符
// - 用于 SetNextItemSelectionUserData() 以及 ImGuiMultiSelectIO 结构体内部。
// - 大多数用户可能会使用此变量来存储项的索引（INDEX），但它也可以用于存储指针（POINTER）或 ID。详情请参阅 ImGuiMultiSelectIO 附近的注释。
typedef ImS64 ImGuiSelectionUserData;


// 回调和函数类型
typedef int (*ImGuiInputTextCallback)(ImGuiInputTextCallbackData* data); // ImGui::InputText() 的回调函数
typedef void (*ImGuiSizeCallback)(ImGuiSizeCallbackData* data); // 用于 ImGui::SetNextWindowSizeConstraints() 的回调函数
typedef void* (*ImGuiMemAllocFunc)(size_t sz, void* user_data); // 用于 ImGui::SetAllocatorFunctions() 的函数签名
typedef void (*ImGuiMemFreeFunc)(void* ptr, void* user_data); // 用于 ImGui::SetAllocatorFunctions() 的函数签名


// ImVec2: 用于存储位置、大小等的二维向量。[编译时可配置类型]
// - 这是 API 中频繁使用的类型。可以考虑使用 IM_VEC2_CLASS_EXTRA 来创建与你首选类型之间的隐式转换。
// - 在包含此文件之前（或在 imconfig.h 中）添加 '#define IMGUI_DEFINE_MATH_OPERATORS'，即可使用为 ImVec2 和 ImVec4 提供的便利数学运算符。
IM_MSVC_RUNTIME_CHECKS_OFF
struct ImVec2
{
    float x, y;
    constexpr ImVec2() : x(0.0f), y(0.0f) {}
    constexpr ImVec2(float _x, float _y) : x(_x), y(_y) {}
    float& operator[] (size_t idx) { IM_ASSERT(idx == 0 || idx == 1); return ((float*)(void*)(char*)this)[idx]; } // 我们极少使用这个 [] 运算符，因此断言带来的开销是可以接受的。
    float operator[] (size_t idx) const { IM_ASSERT(idx == 0 || idx == 1); return ((const float*)(const void*)(const char*)this)[idx]; }
#ifdef IM_VEC2_CLASS_EXTRA
    IM_VEC2_CLASS_EXTRA // 在 imconfig.h 中定义额外的构造函数和隐式转换运算符，以便在你的数学类型和 ImVec2 之间进行来回转换。
#endif
};


// ImVec4：用于存储裁剪矩形、颜色等的 4D 向量。[编译时可配置类型]
struct ImVec4
{
    float x, y, z, w;
    constexpr ImVec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
    constexpr ImVec4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
#ifdef IM_VEC4_CLASS_EXTRA
    IM_VEC4_CLASS_EXTRA // 在 imconfig.h 中定义额外的构造函数和隐式转换运算符，以便在你的数学类型和 ImVec4 之间进行相互转换。
#endif
};
IM_MSVC_RUNTIME_CHECKS_RESTORE


//-----------------------------------------------------------------------------
// [SECTION] 纹理标识符 (ImTextureID, ImTextureRef)
//-----------------------------------------------------------------------------


// ImTextureID = 后端特定的底层标识符，用于表示上传到 GPU/图形系统中的纹理。
// [编译时可配置类型]
// - 当渲染后端创建纹理时，它会将原生标识符存储到 ImTextureID 值中。
// （例如：DX11 后端将其用于存储 `ID3D11ShaderResourceView*`；OpenGL 后端将其用于存储 `GLuint`；）
// 由 SDLGPU 后端用于存储 `SDL_GPUTextureSamplerBinding*` 等。
// - 用户可以通过传递此值，将自己的纹理提交给例如 ImGui::Image() 的函数。
// - 在渲染循环期间，渲染器后端获取 ImTextureID，该 ID 存储在
// ImTextureRef 中，而 ImTextureRef 则存储在 ImDrawCmd 中。
// - 编译时类型配置：
// - 若要使用 64 位以外的值：请在 imconfig.h 文件中添加 '#define ImTextureID MyTextureType*'。
// - 这可以是你想要的任何内容！详情请阅读 FAQ 中关于纹理（textures）的条目。
// - 你可以决定存储一个包含纹理、采样器、着色器等各种信息的更高级别结构体
// 如果你愿意，可以添加构造函数。你需要实现 ==/!= 运算符。
// 历史记录：
// - 在 v1.91.4 (2024/10/08) 中：ImTextureID 的默认类型从 'void*' 更改为 'ImU64'。这使得需要在 32 位架构上构建的后端能够支持 64 位数据。如果遇到类型转换警告，请使用中间类型 intptr_t 进行转换并阅读常见问题解答（FAQ）。
// - 在 v1.92.0 (2025/06/11) 中：添加了 ImTextureRef，它可以携带 ImTextureID 或指向内部纹理图集（texture atlas）的指针。所有面向用户的接受 ImTextureID 的函数都已更改为接受 ImTextureRef
#ifndef ImTextureID
typedef ImU64 ImTextureID; // 默认：存储最多 64 位（任何指针或整数）。大多数后端都支持这种方式。
#endif


// 如果你的后端需要将 0 作为有效的 ImTextureID，请定义此项。
#ifndef ImTextureID_Invalid
#define ImTextureID_Invalid ((ImTextureID)0)
#endif


// ImTextureRef = 纹理的高级标识符。存储一个 ImTextureID _或_ 一个 ImTextureData*。
// 即使在纹理上传到 GPU/图形系统之前，该标识符也是有效的。
// 这是传递给 `ImGui::Image()`、`ImDrawList::AddImage()` 等函数的参数。
// 这是存储在绘制命令（`ImDrawCmd`）中的内容，用于在渲染期间识别纹理。
// - 当纹理是由用户代码创建时（例如自定义图像），我们直接存储底层的 ImTextureID。
// 因此，在显示您自己的纹理时，您可能只需要在自己的一侧管理 ImTextureID 值。
// - 当纹理是由后端创建时，我们存储一个 ImTextureData*，它成为一个间接引用
// 用于在纹理上传完成后，在渲染期间提取 ImTextureID 值。
// - 若要从 ImTextureData 创建 ImTextureRef，可以使用 ImTextureData::GetTexRef()。
// 我们特意没有为此提供 ImTextureRef 构造函数：我们不认为这
// 对最终用户会经常有用，而且它可能会被许多旧代码错误地调用。
// - 如果你想在使用自定义矩形时绑定当前的图集，可以使用 io.Fonts->TexRef。
// - 针对 C 语言（没有构造函数）等语言的绑定生成器，应当提供一个辅助函数，例如：
// inline ImTextureRef ImTextureRefFromID(ImTextureID tex_id) { ImTextureRef tex_ref = { ._TexData = NULL, .TexID = tex_id }; return tex_ref; }
// 在 1.92 版本中，我们将大多数使用 ImTextureID 的绘图函数更改为使用 ImTextureRef。
// 我们特意不提供从 ImTextureRef 到 ImTextureID 的隐式转换操作符，因为在渲染前将 ImTextureRef 转换为 ImTextureID 在技术上是有损的。
IM_MSVC_RUNTIME_CHECKS_OFF
struct ImTextureRef
{
    ImTextureRef() { _TexData = NULL; _TexID = ImTextureID_Invalid; }
    ImTextureRef(ImTextureID tex_id) { _TexData = NULL; _TexID = tex_id; }
#if !defined(IMGUI_DISABLE_OBSOLETE_FUNCTIONS) && !defined(ImTextureID)
    ImTextureRef(void* tex_id) { _TexData = NULL; _TexID = (ImTextureID)(size_t)tex_id; } // 用于将指针转换为 ImTextureID 的旧版后端
#endif


    inline ImTextureID GetTexID() const; // == (_TexData ? _TexData->TexID : _TexID) // 在文件下方实现。


    // 成员（两者必居其一，绝不会同时设置！）
    ImTextureData* _TexData; // 纹理数据，通常由 ImFontAtlas 所有。在纹理上传后的渲染循环期间，将转换为 ImTextureID。
    ImTextureID _TexID; // 或 底层后端纹理标识符（如果已上传或由用户/应用创建）。通常提供给 ImGui::Image() 等调用。
};
IM_MSVC_RUNTIME_CHECKS_RESTORE


//-----------------------------------------------------------------------------
// [SECTION] Dear ImGui 终端用户 API 函数
// （注意，由于 ImGui:: 是一个命名空间，您可以在自己独立的文件中添加额外的 ImGui:: 函数。请不要修改 imgui 的源文件！）
//-----------------------------------------------------------------------------


namespace ImGui
{
    // 上下文创建与访问
    // - 默认情况下，每个上下文（Context）都会创建自己的 ImFontAtlas。你可以自行实例化一个并将其传递给 CreateContext()，以便在多个上下文之间共享字体图集。
    // - DLL 用户：堆和全局变量不能跨越 DLL 边界共享！你需要为你调用的每个静态库/DLL 边界调用 SetCurrentContext() + SetAllocatorFunctions()。
    // 详情请阅读 imgui.cpp 中的 "Context and Memory Allocators" 章节。
    IMGUI_API ImGuiContext* CreateContext(ImFontAtlas* shared_font_atlas = NULL);
    IMGUI_API void DestroyContext(ImGuiContext* ctx = NULL); // NULL = 销毁当前上下文
    IMGUI_API ImGuiContext* GetCurrentContext();
    IMGUI_API void SetCurrentContext(ImGuiContext* ctx);


    // 主程序 (Main)
    IMGUI_API ImGuiIO& GetIO(); // 访问 ImGuiIO 结构体（鼠标/键盘/手柄输入、时间、各种配置选项/标志）
    IMGUI_API ImGuiPlatformIO& GetPlatformIO(); // 访问 ImGuiPlatformIO 结构体（主要是连接平台/渲染器以及操作系统剪贴板、输入法等的钩子/函数）
    IMGUI_API ImGuiStyle& GetStyle(); // 访问 Style 结构体（颜色、尺寸）。在帧中间修改样式时，请务必使用 PushStyleColor()、PushStyleVar()！
    IMGUI_API void NewFrame(); // 开始一个新的 Dear ImGui 帧，从此刻起直到调用 Render()/EndFrame() 为止，你可以提交任何命令。
    IMGUI_API void EndFrame(); // 结束 Dear ImGui 帧。由 Render() 自动调用。如果你不需要渲染数据（跳过渲染），可以在不调用 Render() 的情况下调用 EndFrame()... 但你已经浪费了 CPU 资源！如果你不需要渲染，最好根本不要创建任何窗口，也不要调用 NewFrame()！
    IMGUI_API void Render(); // 结束 Dear ImGui 帧，完成绘制数据。随后你可以调用 GetDrawData()。
    IMGUI_API ImDrawData* GetDrawData(); // 在 Render() 之后到下一次调用 NewFrame() 之前有效。在你的渲染器后端调用 ImGui_ImplXXXX_RenderDrawData() 函数进行渲染。


    // 演示、调试、信息
    IMGUI_API void ShowDemoWindow(bool* p_open = NULL); // 创建演示窗口。展示 ImGui 的大部分功能。调用此函数以了解该库！尝试在你的应用程序中始终保留它！
    IMGUI_API void ShowMetricsWindow(bool* p_open = NULL); // 创建指标/调试器（Metrics/Debugger）窗口。显示 Dear ImGui 内部信息：窗口、绘制命令、各种内部状态等。
    IMGUI_API void ShowDebugLogWindow(bool* p_open = NULL); // 创建调试日志（Debug Log）窗口。显示 Dear ImGui 重要事件的简化日志。
    IMGUI_API void ShowIDStackToolWindow(bool* p_open = NULL); // 创建堆栈工具（Stack Tool）窗口。用鼠标悬停在项目上，以查询其唯一 ID 来源的信息。
    IMGUI_API void ShowAboutWindow(bool* p_open = NULL); // 创建关于（About）窗口。显示 Dear ImGui 版本、致谢以及构建/系统信息。
    IMGUI_API void ShowStyleEditor(ImGuiStyle* ref = NULL); // 添加样式编辑器组件（非窗口）。你可以传入一个 ImGuiStyle 结构体引用，用于对比、重置和保存（否则将使用默认样式）。
    IMGUI_API bool ShowStyleSelector(const char* label); // 添加样式选择器组件（非窗口），本质上是一个列出默认样式的组合框。
    IMGUI_API void ShowFontSelector(const char* label); // 添加字体选择器组件（非窗口），本质上是一个列出已加载字体的组合框。
    IMGUI_API void ShowUserGuide(); // 添加基础帮助/信息组件（非窗口）：介绍最终用户如何操作 ImGui（鼠标/键盘控制）。
    IMGUI_API const char* GetVersion(); // 获取编译后的版本字符串，例如 "1.80 WIP"（本质上是编译版 imgui.cpp 中 IMGUI_VERSION 的值）


    // 样式（Styles）
    IMGUI_API void StyleColorsDark(ImGuiStyle* dst = NULL); // 新版推荐样式（默认）
    IMGUI_API void StyleColorsLight(ImGuiStyle* dst = NULL); // 建议配合边框和自定义加粗字体使用
    IMGUI_API void StyleColorsClassic(ImGuiStyle* dst = NULL); // 经典 ImGui 风格


    // 窗口 (Windows)
    // - Begin() = 将窗口推入栈中并开始向其追加内容。End() = 从栈中弹出窗口。
    // - 传入 'bool* p_open != NULL' 会在窗口右上角显示一个关闭控件，
    // 点击该按钮会将布尔值设置为 false。
    // - 您可以在同一帧内多次调用 Begin()/End() 组合，从而多次向同一个窗口追加内容。
    // 某些信息（如 'flags' 或 'p_open'）仅在第一次调用 Begin() 时生效。
    // - Begin() 返回 false 表示窗口处于折叠状态或被完全裁剪，因此您可以提前退出并省略提交内容的操作。
    // 任何内容到窗口中。无论返回值如何，请务必为每个 Begin() 调用匹配一个 End() 调用！
    // [重要提示：由于历史原因，Begin/End 和 BeginChild/EndChild 与所有其他函数（如
    // BeginMenu/EndMenu、BeginPopup/EndPopup 等）不一致。在其他函数中，只有当对应的
    // BeginXXX 函数返回 true 时才应调用 EndXXX。Begin 和 BeginChild 是仅有的例外。这将在未来的更新中修复。]
    // - 请注意，窗口栈的底部始终包含一个名为 "Debug" 的窗口。
    IMGUI_API bool Begin(const char* name, bool* p_open = NULL, ImGuiWindowFlags flags = 0);
    IMGUI_API void End();


    // 子窗口
    // - 使用子窗口（child windows）在宿主窗口内开启一个独立且自包含的滚动/剪裁区域。子窗口可以嵌套其自身的子窗口。
    // - 在 1.90 版本（2023 年 11 月）之前，“ImGuiChildFlags child_flags = 0”参数原为“bool border = false”。
    // 此 API 与旧代码向后兼容，因为我们保证 ImGuiChildFlags_Borders == true。
    // 请考虑更新您的旧代码：
    // BeginChild("Name", size, false) -> Begin("Name", size, 0); 或 Begin("Name", size, ImGuiChildFlags_None);
    // BeginChild("Name", size, true) -> Begin("Name", size, ImGuiChildFlags_Borders);
    // - 手动调整尺寸（每个轴可以使用不同的设置，例如 ImVec2(0.0f, 400.0f)）：
    // == 0.0f：该轴使用父窗口的剩余尺寸。
    // > 0.0f：该轴使用指定的大小。
    // < 0.0f：相对于可用内容边界的指定距离进行右对齐/底部对齐。
    // - 指定 ImGuiChildFlags_AutoResizeX 或 ImGuiChildFlags_AutoResizeY 会使尺寸根据子内容自动调整。
    // 同时结合使用 ImGuiChildFlags_AutoResizeX 和 ImGuiChildFlags_AutoResizeY 会使滚动区域失去意义，因此不建议这样做。
    // - BeginChild() 返回 false 表示窗口已折叠或被完全裁剪，因此您可以提前退出并省略向窗口提交
    // 任何内容。无论返回值如何，请务必为每个 BeginChild() 调用匹配一个 EndChild() 调用。
    // [重要提示：由于历史原因，Begin/End 和 BeginChild/EndChild 与所有其他函数（如
    // BeginMenu/EndMenu、BeginPopup/EndPopup 等）不一致，在其他函数中，仅当对应的 BeginXXX 返回 true 时才应调用 EndXXX。
    // BeginXXX 函数返回了 true。Begin 和 BeginChild 是仅有的例外。这将在未来的更新中修复。]
    IMGUI_API bool BeginChild(const char* str_id, const ImVec2& size = ImVec2(0, 0), ImGuiChildFlags child_flags = 0, ImGuiWindowFlags window_flags = 0);
    IMGUI_API bool BeginChild(ImGuiID id, const ImVec2& size = ImVec2(0, 0), ImGuiChildFlags child_flags = 0, ImGuiWindowFlags window_flags = 0);
    IMGUI_API void EndChild();


    // Windows 工具函数
    // - “当前窗口 (current window)” = 在 Begin()/End() 块中我们正在向其添加内容的窗口。“下一窗口 (next window)” = 我们即将调用 Begin() 进入的下一个窗口。
    IMGUI_API bool IsWindowAppearing();
    IMGUI_API bool IsWindowCollapsed();
    IMGUI_API bool IsWindowFocused(ImGuiFocusedFlags flags = 0); // 当前窗口是否获得焦点？或者是其根窗口/子窗口，取决于标志位。具体选项请参阅 flags。
    IMGUI_API bool IsWindowHovered(ImGuiHoveredFlags flags = 0); // 当前窗口是否被悬停且可悬停（例如未被弹出窗口/模态窗口遮挡）？具体选项请参阅 ImGuiHoveredFlags_。重要提示：如果您试图检查鼠标应该分发给 Dear ImGui 还是您的底层应用程序，请不要使用此函数！请使用布尔值 'io.WantCaptureMouse'！详情请参阅常见问题解答（FAQ）条目 "How can I tell whether to dispatch mouse/keyboard to Dear ImGui or my application?"。
    IMGUI_API ImDrawList* GetWindowDrawList(); // 获取与当前窗口关联的绘制列表，用于添加您自己的绘制图元
    IMGUI_API ImVec2 GetWindowPos(); // 获取当前窗口在屏幕空间中的位置（您极少需要使用此函数。请考虑始终改用 GetCursorScreenPos() 和 GetContentRegionAvail()）
    IMGUI_API ImVec2 GetWindowSize(); // 获取当前窗口大小（你极少需要用到此函数。请考虑始终优先使用 GetCursorScreenPos() 和 GetContentRegionAvail()）
    IMGUI_API float GetWindowWidth(); // 获取当前窗口宽度（你极少需要用到此函数）。是 GetWindowSize().x 的简写。
    IMGUI_API float GetWindowHeight(); // 获取当前窗口高度（你极少需要用到此函数）。是 GetWindowSize().y 的简写。


    // 窗口操作
    // - 优先使用 SetNextXXX 函数（在 Begin 之前调用），而非 SetXXX 函数（在 Begin 之后调用）。
    IMGUI_API void SetNextWindowPos(const ImVec2& pos, ImGuiCond cond = 0, const ImVec2& pivot = ImVec2(0, 0)); // 设置下一个窗口的位置。在 Begin() 之前调用。使用 pivot=(0.5f,0.5f) 可使窗口以给定点为中心对齐等。
    IMGUI_API void SetNextWindowSize(const ImVec2& size, ImGuiCond cond = 0); // 设置下一个窗口的大小。将轴设为 0.0f 可强制在该轴上自动适应内容。在 Begin() 之前调用。
    IMGUI_API void SetNextWindowSizeConstraints(const ImVec2& size_min, const ImVec2& size_max, ImGuiSizeCallback custom_callback = NULL, void* custom_callback_data = NULL); // 设置下一个窗口的大小限制。如果不希望限制，请使用 0.0f 或 FLT_MAX。若要保留当前大小（其本身也是一种约束），请将同一轴的最小值和最大值都设为 -1。使用回调函数可应用复杂的程序化约束。
    IMGUI_API void SetNextWindowContentSize(const ImVec2& size); // 设置下次窗口的内容区域大小（即：可滚动客户区，用于强制设定滚动条范围）。不包括窗口装饰（标题栏、菜单栏等）及 WindowPadding。将某一轴设为 0.0f 可保持自动计算。在 Begin() 之前调用。
    IMGUI_API void SetNextWindowCollapsed(bool collapsed, ImGuiCond cond = 0); // 设置下次窗口的折叠状态。在 Begin() 之前调用。
    IMGUI_API void SetNextWindowFocus(); // 设置下次窗口为聚焦/最上层状态。在 Begin() 之前调用。
    IMGUI_API void SetNextWindowScroll(const ImVec2& scroll); // 设置下次窗口的滚动数值（使用 < 0.0f 的值表示不影响该轴）。
    IMGUI_API void SetNextWindowBgAlpha(float alpha); // 设置下一个窗口背景颜色的透明度。这是轻松覆盖 ImGuiCol_WindowBg/ChildBg/PopupBg 透明度分量的辅助函数。你也可以使用 ImGuiWindowFlags_NoBackground。
    IMGUI_API void SetWindowPos(const ImVec2& pos, ImGuiCond cond = 0); // （不推荐）设置当前窗口位置 - 在 Begin()/End() 之间调用。建议优先使用 SetNextWindowPos()，因为此函数可能会导致画面撕裂和副作用。
    IMGUI_API void SetWindowSize(const ImVec2& size, ImGuiCond cond = 0); // （不推荐）设置当前窗口大小 - 在 Begin()/End() 之间调用。设置为 ImVec2(0, 0) 可强制自动适应。建议优先使用 SetNextWindowSize()，因为此函数可能会导致画面撕裂和轻微副作用。
    IMGUI_API void SetWindowCollapsed(bool collapsed, ImGuiCond cond = 0); // （不推荐）设置当前窗口的折叠状态。建议优先使用 SetNextWindowCollapsed()。
    IMGUI_API void SetWindowFocus(); // （不建议使用）将当前窗口设置为聚焦/最上层。建议优先使用 SetNextWindowFocus()。
    IMGUI_API void SetWindowPos(const char* name, const ImVec2& pos, ImGuiCond cond = 0); // 设置指定名称窗口的位置。
    IMGUI_API void SetWindowSize(const char* name, const ImVec2& size, ImGuiCond cond = 0); // 设置指定名称窗口的大小。将轴设为 0.0f 可在该轴上强制执行自动适应。
    IMGUI_API void SetWindowCollapsed(const char* name, bool collapsed, ImGuiCond cond = 0); // 设置指定名称窗口的折叠状态。
    IMGUI_API void SetWindowFocus(const char* name); // 将指定名称的窗口设置为聚焦/置顶状态。传入 NULL 则取消聚焦。


    // 窗口滚动
    // - 任何对滚动条（Scroll）的更改都将在下一帧开始时，即第一次调用 Begin() 时生效。
    // - 您也可以在调用 Begin() 之前使用 SetNextWindowScroll() 来避免这种延迟，这是除了使用 SetScrollX()/SetScrollY() 之外的另一种选择。
    IMGUI_API float GetScrollX(); // 获取滚动量 [0 .. GetScrollMaxX()]
    IMGUI_API float GetScrollY(); // 获取滚动量 [0 .. GetScrollMaxY()]
    IMGUI_API void SetScrollX(float scroll_x); // 设置滚动量 [0 .. GetScrollMaxX()]
    IMGUI_API void SetScrollY(float scroll_y); // 设置滚动量 [0 .. GetScrollMaxY()]
    IMGUI_API float GetScrollMaxX(); // 获取最大滚动量 ~~ 内容宽度 - 窗口宽度 - 装饰宽度
    IMGUI_API float GetScrollMaxY(); // 获取最大滚动量 ~~ 内容高度 - 窗口高度 - 装饰高度
    IMGUI_API void SetScrollHereX(float center_x_ratio = 0.5f); // 调整滚动量以使当前光标位置可见。center_x_ratio=0.0：左侧，0.5：居中，1.0：右侧。若用于使“默认/当前项目”可见，请考虑改用 SetItemDefaultFocus()。
    IMGUI_API void SetScrollHereY(float center_y_ratio = 0.5f); // 调整滚动量以使当前光标位置可见。center_y_ratio=0.0：顶部，0.5：居中，1.0：底部。若用于使“默认/当前项目”可见，请考虑改用 SetItemDefaultFocus()。
    IMGUI_API void SetScrollFromPosX(float local_x, float center_x_ratio = 0.5f); // 调整滚动量以使给定位置可见。通常使用 GetCursorStartPos() + 偏移量来计算有效位置。
    IMGUI_API void SetScrollFromPosY(float local_y, float center_y_ratio = 0.5f); // 调整滚动量以使给定位置可见。通常使用 GetCursorStartPos() + 偏移量来计算有效位置。


    // 参数栈 (字体)
    // - PushFont(font, 0.0f) // 更改字体并保持当前大小
    // - PushFont(NULL, 20.0f) // 保持当前字体并更改当前字号
    // - PushFont(font, 20.0f) // 更改字体并将字号设置为 20.0f
    // - PushFont(font, style.FontSizeBase * 2.0f) // 更改字体并将字号设置为当前字号的两倍
    // - PushFont(font, font->LegacySize) // 更改字体并将字号设置为传递给 AddFontXXX() 函数的大小。与 1.92 版本之前的行为一致。
    // *重要提示* 在 1.92 版本之前，字体只有单一尺寸。现在它们可以动态调整。
    // - 在 1.92 版本中，我们移除了单参数版本的 PushFont()，因为这似乎是提供无错过渡最简单的方法。
    // - 1.92 之前的 PushFont(font) = 1.92 之后的 PushFont(font, font->LegacySize) // 使用传递给 AddFontXXX() 函数的默认字体尺寸。
    // *重要提示* 全局缩放因子会应用在提供的尺寸之上。
    // - 全局缩放因子包括：'style.FontScaleMain'、'style.FontScaleDpi' 等。
    // - 如果你想对“当前”字体大小应用缩放因子：
    // - 正确做法：PushFont(NULL, style.FontSizeBase) // 使用当前未缩放的大小 == 不执行任何操作
    // - 正确做法：PushFont(NULL, style.FontSizeBase * 2.0f) // 使用当前未缩放大小的 2 倍 == 使文本变大两倍
    // - 错误写法：PushFont(NULL, GetFontSize()) // 错误！使用了已经应用过全局缩放因子的尺寸 == 全局缩放因子将被应用两次！
    // - 错误写法：PushFont(NULL, GetFontSize() * 2.0f) // 错误！使用了已经应用过全局缩放因子的尺寸 == 全局缩放因子将被应用两次！
    IMGUI_API void PushFont(ImFont* font, float font_size_base_unscaled); // 使用 NULL 作为保留当前字体的快捷方式。使用 0.0f 以保留当前尺寸。
    IMGUI_API void PopFont();
    IMGUI_API ImFont* GetFont(); // 获取当前字体
    IMGUI_API float GetFontSize(); // 获取当前缩放后的字体大小（即像素高度）。该值已应用全局缩放因子。*重要提示* 请勿将此值传递给 PushFont()！若要获取应用全局缩放因子之前的值，请使用 ImGui::GetStyle().FontSizeBase。
    IMGUI_API ImFontBaked* GetFontBaked(); // 获取当前大小下绑定的当前字体 // 等同于 GetFont()->GetFontBaked(GetFontSize())


    // 参数栈（共享）
    IMGUI_API void PushStyleColor(ImGuiCol idx, ImU32 col); // 修改样式颜色。如果在 NewFrame() 之后修改样式，请务必使用此函数。
    IMGUI_API void PushStyleColor(ImGuiCol idx, const ImVec4& col);
    IMGUI_API void PopStyleColor(int count = 1);
    IMGUI_API void PushStyleVar(ImGuiStyleVar idx, float val); // 修改样式浮点变量。如果在 NewFrame() 之后修改样式，请务必使用此函数！
    IMGUI_API void PushStyleVar(ImGuiStyleVar idx, const ImVec2& val); // 修改 ImVec2 类型的样式变量。
    IMGUI_API void PushStyleVarX(ImGuiStyleVar idx, float val_x); // 修改 ImVec2 类型样式变量的 X 分量。
    IMGUI_API void PushStyleVarY(ImGuiStyleVar idx, float val_y); // 修改 ImVec2 类型样式变量的 Y 分量。
    IMGUI_API void PopStyleVar(int count = 1);
    IMGUI_API void PushItemFlag(ImGuiItemFlags option, bool enabled); // 修改指定的共享项标志，例如 PushItemFlag(ImGuiItemFlags_NoTabStop, true)
    IMGUI_API void PopItemFlag();


    // 参数栈（当前窗口）
    IMGUI_API void PushItemWidth(float item_width); // 设置通用大型“控件+标签”组件的宽度。>0.0f：以像素为单位的宽度；<0.0f：向窗口右侧对齐 xx 像素（因此 -FLT_MIN 始终将宽度对齐到右侧）。
    IMGUI_API void PopItemWidth();
    IMGUI_API void SetNextItemWidth(float item_width); // 设置“下一个”通用大型“控件+标签”组件的宽度。>0.0f：以像素为单位的宽度；<0.0f：对齐到窗口右侧 xx 像素处（因此 -FLT_MIN 始终将宽度对齐到右侧）
    IMGUI_API float CalcItemWidth(); // 根据已推入的设置和当前光标位置计算出的控件宽度。与大多数“Item”函数不同，这不一定是上一个控件的宽度。
    IMGUI_API void PushTextWrapPos(float wrap_local_pos_x = 0.0f); // 为 Text*() 命令推入自动换行位置。< 0.0f：不换行；0.0f：换行至窗口（或列）末尾；> 0.0f：在窗口本地空间的“wrap_pos_x”位置换行
    IMGUI_API void PopTextWrapPos();


    // 样式读取访问
    // - 使用 ShowStyleEditor() 函数可以交互式地查看/编辑颜色。
    IMGUI_API ImVec2 GetFontTexUvWhitePixel(); // 获取白色像素的 UV 坐标，适用于通过 ImDrawList API 绘制自定义图形
    IMGUI_API ImU32 GetColorU32(ImGuiCol idx, float alpha_mul = 1.0f); // 获取指定的样式颜色，并应用样式透明度（Alpha）及可选的额外透明度系数，打包为适用于 ImDrawList 的 32 位数值
    IMGUI_API ImU32 GetColorU32(const ImVec4& col); // 获取指定的颜色并应用样式透明度，打包为适用于 ImDrawList 的 32 位数值
    IMGUI_API ImU32 GetColorU32(ImU32 col, float alpha_mul = 1.0f); // 获取指定的颜色并应用样式透明度，打包为适用于 ImDrawList 的 32 位数值
    IMGUI_API const ImVec4& GetStyleColorVec4(ImGuiCol idx); // 获取存储在 ImGuiStyle 结构中的样式颜色。用于传回 PushStyleColor()，否则请使用 GetColorU32() 来获取已融合样式透明度的颜色。


    // 布局光标定位
    // - 我们所说的“光标（cursor）”是指当前的输出位置。
    // - 典型的控件行为是在当前光标位置输出自身，然后将光标向下移动一行。
    // - 您可以在控件之间调用 SameLine() 来撤销上一次换行，并在前一个控件的右侧进行输出。
    // - 仅使用 GetCursorScreenPos() 和 GetContentRegionAvail() 就能完成 99% 的需求。
    // - 注意！目前我们在窗口局部坐标和绝对坐标之间存在不一致性，我们计划在未来的 API 中予以修复：
    // - 绝对坐标：GetCursorScreenPos()、SetCursorScreenPos() 以及所有 ImDrawList:: 函数。 -> 这是推荐的后续开发方式。
    // - 窗口局部坐标：SameLine(offset)、GetCursorPos()、SetCursorPos()、GetCursorStartPos()、PushTextWrapPos()
    // - 窗口局部坐标：GetContentRegionMax(), GetWindowContentRegionMin(), GetWindowContentRegionMax() --> 全部已废弃。你不需要它们。
    // - GetCursorScreenPos() = GetCursorPos() + GetWindowPos()。GetWindowPos() 几乎只在将窗口局部坐标转换为绝对坐标时才有用。尽量不要使用它。
    IMGUI_API ImVec2 GetCursorScreenPos(); // 光标位置，绝对坐标。这是你最好的朋友（优先使用此函数而非 GetCursorPos()，在配合 ImDrawList API 工作时也更有用）。
    IMGUI_API void SetCursorScreenPos(const ImVec2& pos); // 光标位置，绝对坐标。这是你最好的朋友。
    IMGUI_API ImVec2 GetContentRegionAvail(); // 从当前位置起可用的空间。这是你最好的朋友。
    IMGUI_API ImVec2 GetCursorPos(); // [窗口局部] 窗口局部坐标系下的光标位置。这不是你最好的朋友。
    IMGUI_API float GetCursorPosX(); // [窗口局部] 同上
    IMGUI_API float GetCursorPosY(); // [窗口局部] 同上
    IMGUI_API void SetCursorPos(const ImVec2& local_pos); // [窗口局部坐标]
    IMGUI_API void SetCursorPosX(float local_x); // [窗口局部坐标]
    IMGUI_API void SetCursorPosY(float local_y); // [窗口局部坐标]
    IMGUI_API ImVec2 GetCursorStartPos(); // [窗口局部坐标] 初始光标位置，使用窗口局部坐标。在 Begin() 之后调用 GetCursorScreenPos() 可获取绝对坐标版本。


    // 其他布局函数
    IMGUI_API void Separator(); // 分隔线，通常为水平方向。在菜单栏或水平布局模式下，它会变为垂直分隔线。
    IMGUI_API void SameLine(float offset_from_start_x = 0.0f, float spacing = -1.0f); // 在控件或组之间调用以进行水平布局。X 坐标以窗口坐标给出。
    IMGUI_API void NewLine(); // 撤销 SameLine() 的效果，或在水平布局上下文中强制换行。
    IMGUI_API void Spacing(); // 添加垂直间距。
    IMGUI_API void Dummy(const ImVec2& size); // 添加一个给定尺寸的占位项。与 InvisibleButton() 不同，Dummy() 不会响应鼠标点击，也无法被导航选中。
    IMGUI_API void Indent(float indent_w = 0.0f); // 将内容位置向右移动 indent_w 距离；如果 indent_w <= 0，则移动 style.IndentSpacing 距离。
    IMGUI_API void Unindent(float indent_w = 0.0f); // 将内容位置向左移回 indent_w 距离；如果 indent_w <= 0，则移回 style.IndentSpacing 距离。
    IMGUI_API void BeginGroup(); // 锁定水平起始位置
    IMGUI_API void EndGroup(); // 解锁水平起始位置 + 将整个组的包围盒捕获为一个“项目”（因此你可以对整个组使用 IsItemHovered() 或 SameLine() 等布局原语）
    IMGUI_API void AlignTextToFramePadding(); // 将后续文本的基线与 FramePadding.y 垂直对齐，使其能与常规带框项目对齐（如果你在带框项目之前的同一行有文本，请调用此函数）
    IMGUI_API float GetTextLineHeight(); // 约等于 FontSize
    IMGUI_API float GetTextLineHeightWithSpacing(); // ~ FontSize + style.ItemSpacing.y（相邻两行文本之间的像素距离）
    IMGUI_API float GetFrameHeight(); // ~ FontSize + style.FramePadding.y * 2
    IMGUI_API float GetFrameHeightWithSpacing(); // ~ FontSize + style.FramePadding.y * 2 + style.ItemSpacing.y（相邻两个带框架控件之间的像素距离）


    // ID 栈/作用域
    // 请阅读 FAQ（docs/FAQ.md 或 http://dearimgui.com/faq）以了解更多关于 Dear ImGui 如何处理 ID 的详细信息。
    // - 理解 ID 栈系统可以回答并解决以下问题：
    // - “问：为什么我的控件在点击时没有反应？”
    // - “问：如何创建带有空标签的控件？”
    // - “问：如何让多个控件拥有相同的标签？”
    // - 简短回答：ID 是整个 ID 栈的哈希值。如果你在循环中创建控件，你通常
    // 需要推入一个唯一标识符（例如对象指针、循环索引）来唯一地区分它们。
    // - 你也可以在控件标签中使用 “Label##foobar” 语法来将它们彼此区分开。
    // - 在此头文件中，我们使用 "label"/"name" 术语来表示一个既会被显示又会被用作 ID 的字符串，
    // 而 "str_id" 则表示一个仅用作 ID 且通常不显示的字符串。
    IMGUI_API void PushID(const char* str_id); // 将字符串压入 ID 栈（将对字符串进行哈希处理）。
    IMGUI_API void PushID(const char* str_id_begin, const char* str_id_end); // 将字符串压入 ID 栈（将对字符串进行哈希处理）。
    IMGUI_API void PushID(const void* ptr_id); // 将指针压入 ID 栈（将对指针进行哈希）。
    IMGUI_API void PushID(int int_id); // 将整数压入 ID 栈（将对整数进行哈希）。
    IMGUI_API void PopID(); // 从 ID 栈中弹出。
    IMGUI_API ImGuiID GetID(const char* str_id); // 计算唯一 ID（整个 ID 栈的哈希 + 给定参数）。例如，当你想要自行查询 ImGuiStorage 时使用。
    IMGUI_API ImGuiID GetID(const char* str_id_begin, const char* str_id_end);
    IMGUI_API ImGuiID GetID(const void* ptr_id);
    IMGUI_API ImGuiID GetID(int int_id);


    // 控件：文本
    IMGUI_API void TextUnformatted(const char* text, const char* text_end = NULL); // 原始文本，不进行格式化。大致相当于 Text("%s", text)，但：A) 如果指定了 'text_end'，则不需要以空字符结尾的字符串；B) 速度更快，不进行内存复制，没有缓冲区大小限制，推荐用于长文本块。
    IMGUI_API void Text(const char* fmt, ...) IM_FMTARGS(1); // 格式化文本
    IMGUI_API void TextV(const char* fmt, va_list args) IM_FMTLIST(1);
    IMGUI_API void TextColored(const ImVec4& col, const char* fmt, ...) IM_FMTARGS(2); // PushStyleColor(ImGuiCol_Text, col); Text(fmt, ...); PopStyleColor(); 的快捷方式
    IMGUI_API void TextColoredV(const ImVec4& col, const char* fmt, va_list args) IM_FMTLIST(2);
    IMGUI_API void TextDisabled(const char* fmt, ...) IM_FMTARGS(1); // PushStyleColor(ImGuiCol_Text, style.Colors[ImGuiCol_TextDisabled]); Text(fmt, ...); PopStyleColor(); 的快捷方式。
    IMGUI_API void TextDisabledV(const char* fmt, va_list args) IM_FMTLIST(1);
    IMGUI_API void TextWrapped(const char* fmt, ...) IM_FMTARGS(1); // PushTextWrapPos(0.0f); Text(fmt, ...); PopTextWrapPos(); 的快捷方式。请注意，如果没有其他控件来扩展窗口宽度，这在自动调整大小的窗口上将不起作用，您可能需要使用 SetNextWindowSize() 设置一个尺寸。
    IMGUI_API void TextWrappedV(const char* fmt, va_list args) IM_FMTLIST(1);
    IMGUI_API void LabelText(const char* label, const char* fmt, ...) IM_FMTARGS(2); // 显示文本+标签，其对齐方式与“数值+标签”型控件一致
    IMGUI_API void LabelTextV(const char* label, const char* fmt, va_list args) IM_FMTLIST(2);
    IMGUI_API void BulletText(const char* fmt, ...) IM_FMTARGS(1); // Bullet()+Text() 的快捷方式
    IMGUI_API void BulletTextV(const char* fmt, va_list args) IM_FMTLIST(1);
    IMGUI_API void SeparatorText(const char* label); // 目前效果为：带有水平线的格式化文本


    // 控件：主要 (Main)
    // - 大多数控件在值改变或被点击/选中时返回 true
    // - 您还可以使用众多的 IsItemXXX 函数（例如 IsItemActive、IsItemHovered 等）来查询控件状态。
    IMGUI_API bool Button(const char* label, const ImVec2& size = ImVec2(0, 0)); // 按钮
    IMGUI_API bool SmallButton(const char* label); // 紧凑型按钮（FramePadding.y == 0），便于嵌入文本中
    IMGUI_API bool InvisibleButton(const char* str_id, const ImVec2& size, ImGuiButtonFlags flags = 0); // 灵活的不可见按钮，不具备视觉外观，常用于配合公共 API（如 IsItemActive、IsItemHovered 等）构建自定义交互行为
    IMGUI_API bool ArrowButton(const char* str_id, ImGuiDir dir); // 带有箭头形状的正方形按钮
    IMGUI_API bool Checkbox(const char* label, bool* v);
    IMGUI_API bool CheckboxFlags(const char* label, int* flags, int flags_value);
    IMGUI_API bool CheckboxFlags(const char* label, unsigned int* flags, unsigned int flags_value);
    IMGUI_API bool RadioButton(const char* label, bool active); // 用法示例：if (RadioButton("one", my_value==1)) { my_value = 1; }
    IMGUI_API bool RadioButton(const char* label, int* v, int v_button); // 当值为整数时，用于处理上述模式的快捷方式
    IMGUI_API void ProgressBar(float fraction, const ImVec2& size_arg = ImVec2(-FLT_MIN, 0), const char* overlay = NULL);
    IMGUI_API void Bullet(); // 绘制一个小圆圈并保持光标在同一行。光标的 x 轴位置将前进 GetTreeNodeToLabelSpacing() 的距离，该距离与 TreeNode() 使用的距离相同
    IMGUI_API bool TextLink(const char* label); // 超链接文本按钮，点击时返回 true
    IMGUI_API bool TextLinkOpenURL(const char* label, const char* url = NULL); // 超链接文本按钮，点击时自动打开文件/URL


    // 控件：图像
    // - 在此处阅读关于 ImTextureID/ImTextureRef 的内容：https://github.com/ocornut/imgui/wiki/Image-Loading-and-Displaying-Examples
    // - 'uv0' 和 'uv1' 是纹理坐标。请通过上方相同的链接了解相关信息。
    // - Image() 在每一侧添加 style.ImageBorderSize 边距，ImageButton() 在每一侧添加 style.FramePadding 边距。
    // - ImageButton() 基于常规 Button() 的颜色绘制背景，如果指定了内部背景，则还可以选择绘制内部背景。
    // - 在 1.91.9 版本（2025 年 3 月）之前，Image() 有一个过时的版本包含 'tint_col' 参数，该参数现在由 ImageWithBg() 函数支持。
    IMGUI_API void Image(ImTextureRef tex_ref, const ImVec2& image_size, const ImVec2& uv0 = ImVec2(0, 0), const ImVec2& uv1 = ImVec2(1, 1));
    IMGUI_API void ImageWithBg(ImTextureRef tex_ref, const ImVec2& image_size, const ImVec2& uv0 = ImVec2(0, 0), const ImVec2& uv1 = ImVec2(1, 1), const ImVec4& bg_col = ImVec4(0, 0, 0, 0), const ImVec4& tint_col = ImVec4(1, 1, 1, 1));
    IMGUI_API bool ImageButton(const char* str_id, ImTextureRef tex_ref, const ImVec2& image_size, const ImVec2& uv0 = ImVec2(0, 0), const ImVec2& uv1 = ImVec2(1, 1), const ImVec4& bg_col = ImVec4(0, 0, 0, 0), const ImVec4& tint_col = ImVec4(1, 1, 1, 1));


    // 控件：组合框（下拉列表）
    // - BeginCombo()/EndCombo() API 允许你通过创建例如 Selectable() 控件的方式，按需灵活管理内容和选择状态。
    // - 旧的 Combo() API 是基于 BeginCombo()/EndCombo() 的辅助函数，为了方便起见予以保留。这与 ListBox 的创建方式类似。
    IMGUI_API bool BeginCombo(const char* label, const char* preview_value, ImGuiComboFlags flags = 0);
    IMGUI_API void EndCombo(); // 仅在 BeginCombo() 返回 true 时才调用 EndCombo()！
    IMGUI_API bool Combo(const char* label, int* current_item, const char* const items[], int items_count, int popup_max_height_in_items = -1);
    IMGUI_API bool Combo(const char* label, int* current_item, const char* items_separated_by_zeros, int popup_max_height_in_items = -1); // 在字符串内用 \0 分隔各个选项，并以 \0\0 结束列表。例如："One\0Two\0Three\0"
    IMGUI_API bool Combo(const char* label, int* current_item, const char* (*getter)(void* user_data, int idx), void* user_data, int items_count, int popup_max_height_in_items = -1);


    // 控件：拖动滑块 (Drag Sliders)
    // - 在任何拖拽框（drag box）上按 Ctrl+左键 即可将其转换为输入框。默认情况下，手动输入的值不会被限制，可能会超出范围。使用 ImGuiSliderFlags_AlwaysClamp 可以始终强制限制范围。
    // - 对于所有函数的 Float2/Float3/Float4/Int2/Int3/Int4 版本，请注意函数参数中的 'float v[X]' 与 'float* v' 是等价的，
    // 数组语法仅用于说明预期可访问的元素数量。你可以传递连续集合中第一个元素的地址，例如 &myvector.x
    // - 调整格式化字符串（format string）可以为数值添加前缀、后缀，或调整编辑与显示的精度。例如："%.3f" -> 1.234；"%5.2f secs" -> 01.23 secs；"Biscuit: %.0f" -> Biscuit: 1；等等。
    // - 格式化字符串可以设置为 NULL 或使用默认格式（"%f" 或 "%d"）。
    // - 速度是基于鼠标移动的每个像素计算的（v_speed=0.2f：鼠标需要移动 5 个像素才能使数值增加 1）。对于键盘/手柄导航，最小速度为 Max(v_speed, 给定精度下的最小步长)。
    // - 使用 v_min < v_max 将编辑限制在给定范围内。请注意，如果未使用 ImGuiSliderFlags_AlwaysClamp，Ctrl+左键点击的手动输入可能会覆盖这些限制。
    // - 使用 v_max = FLT_MAX / INT_MAX 等可以避免上限限制，同理使用 v_min = -FLT_MAX / INT_MIN 可以避免下限限制。
    // - 我们在 DragXXX() 和 SliderXXX() 函数中使用相同的标志集，因为它们的功能相同，这样更便于互相替换。
    // - 遗留问题：在 1.78 版本之前，DragXXX() 函数签名的最后一个参数是 `float power=1.0f`，而不是 `ImGuiSliderFlags flags=0`。
    // 如果你在将 float 转换为 ImGuiSliderFlags 时收到警告，请阅读 https://github.com/ocornut/imgui/issues/3361
    IMGUI_API bool DragFloat(const char* label, float* v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", ImGuiSliderFlags flags = 0); // 如果 v_min >= v_max，则不设限制
    IMGUI_API bool DragFloat2(const char* label, float v[2], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
    IMGUI_API bool DragFloat3(const char* label, float v[3], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
    IMGUI_API bool DragFloat4(const char* label, float v[4], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
    IMGUI_API bool DragFloatRange2(const char* label, float* v_current_min, float* v_current_max, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", const char* format_max = NULL, ImGuiSliderFlags flags = 0);
    IMGUI_API bool DragInt(const char* label, int* v, float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d", ImGuiSliderFlags flags = 0); // 如果 v_min >= v_max，则不设限制
    IMGUI_API bool DragInt2(const char* label, int v[2], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d", ImGuiSliderFlags flags = 0);
    IMGUI_API bool DragInt3(const char* label, int v[3], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d", ImGuiSliderFlags flags = 0);
    IMGUI_API bool DragInt4(const char* label, int v[4], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d", ImGuiSliderFlags flags = 0);
    IMGUI_API bool DragIntRange2(const char* label, int* v_current_min, int* v_current_max, float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d", const char* format_max = NULL, ImGuiSliderFlags flags = 0);
    IMGUI_API bool DragScalar(const char* label, ImGuiDataType data_type, void* p_data, float v_speed = 1.0f, const void* p_min = NULL, const void* p_max = NULL, const char* format = NULL, ImGuiSliderFlags flags = 0);
    IMGUI_API bool DragScalarN(const char* label, ImGuiDataType data_type, void* p_data, int components, float v_speed = 1.0f, const void* p_min = NULL, const void* p_max = NULL, const char* format = NULL, ImGuiSliderFlags flags = 0);


    // 控件：普通滑块 (Regular Sliders)
    // - 在任何滑块上按 Ctrl+左键 即可将其转换为输入框。默认情况下，手动输入的值不会被限制，可能会超出范围。使用 ImGuiSliderFlags_AlwaysClamp 可以始终强制限制范围。
    // - 调整格式化字符串可以为数值添加前缀、后缀，或调整编辑和显示的精度。例如："%.3f" -> 1.234；"%5.2f secs" -> 01.23 secs；"Biscuit: %.0f" -> Biscuit: 1 等。
    // - 格式化字符串也可以设置为 NULL 或使用默认格式（"%f" 或 "%d"）。
    // - 遗留问题：在 1.78 版本之前，SliderXXX() 函数签名的最后一个参数是 `float power=1.0f`，而不是 `ImGuiSliderFlags flags=0`。
    // 如果你在将 float 转换为 ImGuiSliderFlags 时收到警告，请阅读 https://github.com/ocornut/imgui/issues/3361
    IMGUI_API bool SliderFloat(const char* label, float* v, float v_min, float v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0); // 调整 format 参数以在滑块内标签或单位显示中为数值添加前缀或后缀。
    IMGUI_API bool SliderFloat2(const char* label, float v[2], float v_min, float v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
    IMGUI_API bool SliderFloat3(const char* label, float v[3], float v_min, float v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
    IMGUI_API bool SliderFloat4(const char* label, float v[4], float v_min, float v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
    IMGUI_API bool SliderAngle(const char* label, float* v_rad, float v_degrees_min = -360.0f, float v_degrees_max = +360.0f, const char* format = "%.0f deg", ImGuiSliderFlags flags = 0);
    IMGUI_API bool SliderInt(const char* label, int* v, int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0);
    IMGUI_API bool SliderInt2(const char* label, int v[2], int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0);
    IMGUI_API bool SliderInt3(const char* label, int v[3], int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0);
    IMGUI_API bool SliderInt4(const char* label, int v[4], int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0);
    IMGUI_API bool SliderScalar(const char* label, ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max, const char* format = NULL, ImGuiSliderFlags flags = 0);
    IMGUI_API bool SliderScalarN(const char* label, ImGuiDataType data_type, void* p_data, int components, const void* p_min, const void* p_max, const char* format = NULL, ImGuiSliderFlags flags = 0);
    IMGUI_API bool VSliderFloat(const char* label, const ImVec2& size, float* v, float v_min, float v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
    IMGUI_API bool VSliderInt(const char* label, const ImVec2& size, int* v, int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0);
    IMGUI_API bool VSliderScalar(const char* label, const ImVec2& size, ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max, const char* format = NULL, ImGuiSliderFlags flags = 0);


    // 控件：键盘输入
    // - 如果你想在 InputText() 中使用 std::string 或任何自定义动态字符串类型，请使用 misc/cpp/imgui_stdlib.h/.cpp 中的包装器！
    // - 大多数 ImGuiInputTextFlags 标志仅对 InputText() 有用，而不适用于 InputFloatX、InputIntX、InputDouble 等。
    IMGUI_API bool InputText(const char* label, char* buf, size_t buf_size, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL);
    IMGUI_API bool InputTextMultiline(const char* label, char* buf, size_t buf_size, const ImVec2& size = ImVec2(0, 0), ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL);
    IMGUI_API bool InputTextWithHint(const char* label, const char* hint, char* buf, size_t buf_size, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL);
    IMGUI_API bool InputFloat(const char* label, float* v, float step = 0.0f, float step_fast = 0.0f, const char* format = "%.3f", ImGuiInputTextFlags flags = 0);
    IMGUI_API bool InputFloat2(const char* label, float v[2], const char* format = "%.3f", ImGuiInputTextFlags flags = 0);
    IMGUI_API bool InputFloat3(const char* label, float v[3], const char* format = "%.3f", ImGuiInputTextFlags flags = 0);
    IMGUI_API bool InputFloat4(const char* label, float v[4], const char* format = "%.3f", ImGuiInputTextFlags flags = 0);
    IMGUI_API bool InputInt(const char* label, int* v, int step = 1, int step_fast = 100, ImGuiInputTextFlags flags = 0);
    IMGUI_API bool InputInt2(const char* label, int v[2], ImGuiInputTextFlags flags = 0);
    IMGUI_API bool InputInt3(const char* label, int v[3], ImGuiInputTextFlags flags = 0);
    IMGUI_API bool InputInt4(const char* label, int v[4], ImGuiInputTextFlags flags = 0);
    IMGUI_API bool InputDouble(const char* label, double* v, double step = 0.0, double step_fast = 0.0, const char* format = "%.6f", ImGuiInputTextFlags flags = 0);
    IMGUI_API bool InputScalar(const char* label, ImGuiDataType data_type, void* p_data, const void* p_step = NULL, const void* p_step_fast = NULL, const char* format = NULL, ImGuiInputTextFlags flags = 0);
    IMGUI_API bool InputScalarN(const char* label, ImGuiDataType data_type, void* p_data, int components, const void* p_step = NULL, const void* p_step_fast = NULL, const char* format = NULL, ImGuiInputTextFlags flags = 0);


    // 控件：颜色编辑器/拾色器（提示：ColorEdit* 函数带有一个小色块，左键点击可打开拾色器，右键点击可打开选项菜单。）
    // - 注意在 C++ 中，函数参数中的 'float v[X]' 与 'float* v' 是等价的，数组语法仅用于说明预期可访问的元素数量。
    // - 你可以传递连续结构体中第一个 float 元素的地址，例如 &myvector.x
    IMGUI_API bool ColorEdit3(const char* label, float col[3], ImGuiColorEditFlags flags = 0);
    IMGUI_API bool ColorEdit4(const char* label, float col[4], ImGuiColorEditFlags flags = 0);
    IMGUI_API bool ColorPicker3(const char* label, float col[3], ImGuiColorEditFlags flags = 0);
    IMGUI_API bool ColorPicker4(const char* label, float col[4], ImGuiColorEditFlags flags = 0, const float* ref_col = NULL);
    IMGUI_API bool ColorButton(const char* desc_id, const ImVec4& col, ImGuiColorEditFlags flags = 0, const ImVec2& size = ImVec2(0, 0)); // 显示一个颜色方块/按钮，悬停查看详情，点击时返回 true。
    IMGUI_API void SetColorEditOptions(ImGuiColorEditFlags flags); // 初始化当前选项（通常在应用程序启动时），用于选择默认格式、选择器类型等。除非在调用时传入 _NoOptions 标志，否则用户可以更改许多设置。


    // 控件：树 (Trees)
    // - 当节点处于打开状态时，TreeNode 函数返回 true，在这种情况下，您在完成显示树节点内容后还需要调用 TreePop()。
    IMGUI_API bool TreeNode(const char* label);
    IMGUI_API bool TreeNode(const char* str_id, const char* fmt, ...) IM_FMTARGS(2); // 辅助变体，用于轻松地将 ID 与显示的字符串分离。请阅读常见问题解答（FAQ）了解为什么要使用 ID 以及如何使用。若要将任意文本与 TreeNode() 对齐在同一层级，可以使用 Bullet()。
    IMGUI_API bool TreeNode(const void* ptr_id, const char* fmt, ...) IM_FMTARGS(2); // 同上
    IMGUI_API bool TreeNodeV(const char* str_id, const char* fmt, va_list args) IM_FMTLIST(2);
    IMGUI_API bool TreeNodeV(const void* ptr_id, const char* fmt, va_list args) IM_FMTLIST(2);
    IMGUI_API bool TreeNodeEx(const char* label, ImGuiTreeNodeFlags flags = 0);
    IMGUI_API bool TreeNodeEx(const char* str_id, ImGuiTreeNodeFlags flags, const char* fmt, ...) IM_FMTARGS(3);
    IMGUI_API bool TreeNodeEx(const void* ptr_id, ImGuiTreeNodeFlags flags, const char* fmt, ...) IM_FMTARGS(3);
    IMGUI_API bool TreeNodeExV(const char* str_id, ImGuiTreeNodeFlags flags, const char* fmt, va_list args) IM_FMTLIST(3);
    IMGUI_API bool TreeNodeExV(const void* ptr_id, ImGuiTreeNodeFlags flags, const char* fmt, va_list args) IM_FMTLIST(3);
    IMGUI_API void TreePush(const char* str_id); // ~ Indent()+PushID()。当 TreeNode() 返回 true 时会自动调用，但如果需要，你也可以自行调用 TreePush/TreePop。
    IMGUI_API void TreePush(const void* ptr_id); // 同上
    IMGUI_API void TreePop(); // ~ Unindent()+PopID()
    IMGUI_API float GetTreeNodeToLabelSpacing(); // 使用 TreeNode*() 或 Bullet() 时标签前的水平距离 == 普通无边框 TreeNode 的 (g.FontSize + style.FramePadding.x*2)
    IMGUI_API bool CollapsingHeader(const char* label, ImGuiTreeNodeFlags flags = 0); // 如果返回 'true' 则折叠页眉处于打开状态。不产生缩进也不推入 ID 栈。用户无需调用 TreePop()。
    IMGUI_API bool CollapsingHeader(const char* label, bool* p_visible, ImGuiTreeNodeFlags flags = 0); // 当 'p_visible != NULL' 时：如果 '*p_visible==true'，在页眉右上角显示一个额外的关闭小按钮，点击后会将该布尔值设为 false；如果 '*p_visible==false'，则不显示该页眉。
    IMGUI_API void SetNextItemOpen(bool is_open, ImGuiCond cond = 0); // 设置下一个 TreeNode/CollapsingHeader 的打开状态。
    IMGUI_API void SetNextItemStorageID(ImGuiID storage_id); // 设置用于打开/关闭状态存储的 ID（默认为与项目 ID 相同）。


    // 控件：可选项 (Selectables)
    // - 可选项在悬停时会高亮显示，并在被选中时显示另一种颜色。
    // - 相邻的可选项会扩展其高亮边界，以便在它们之间不留间隙。这样可以使一系列被选中的可选项看起来是连续的。
    IMGUI_API bool Selectable(const char* label, bool selected = false, ImGuiSelectableFlags flags = 0, const ImVec2& size = ImVec2(0, 0)); // "bool selected" 携带选中状态（只读）。当 Selectable() 被点击时返回 true，以便您修改选中状态。size.x==0.0：使用剩余宽度，size.x>0.0：指定宽度。size.y==0.0：使用标签高度，size.y>0.0：指定高度。
    IMGUI_API bool Selectable(const char* label, bool* p_selected, ImGuiSelectableFlags flags = 0, const ImVec2& size = ImVec2(0, 0)); // "bool* p_selected" 指向选中状态（读写），作为一个便捷的辅助函数。


    // 适用于 Selectable()、Checkbox()、TreeNode() 函数的多选系统 [BETA]
    // - 这使得标准的多选/范围选择习惯用法（Ctrl+鼠标/键盘、Shift+鼠标/键盘等）得以实现，同时也允许使用裁剪器（clipper）。
    // - ImGuiSelectionUserData 通常用于存储当前视图中的项目索引（但也可以存储其他内容）。
    // - 请阅读 ImGuiMultiSelectIO 附近的注释以获取说明/详情，并查看“Demo->Widgets->Selection State & Multi-Select”以获取演示。
    // - TreeNode() 在技术上是支持的，但……正确使用它会更复杂。你需要对树进行某种线性/随机访问，
    // 这适用于已经实现了过滤器和裁剪器的进阶树结构设置。我们将致力于简化当前的演示。
    // - 'selection_size' 和 'items_count' 参数是可选的，仅用于少数功能。如果计算这些参数的开销较大，您可以忽略它们。
    IMGUI_API ImGuiMultiSelectIO* BeginMultiSelect(ImGuiMultiSelectFlags flags, int selection_size = -1, int items_count = -1);
    IMGUI_API ImGuiMultiSelectIO* EndMultiSelect();
    IMGUI_API void SetNextItemSelectionUserData(ImGuiSelectionUserData selection_user_data);
    IMGUI_API bool IsItemToggledSelection(); // 上一个条目的选择状态是否发生了切换？如果你需要在调用 EndMultiSelect() _之前_ 获取每个条目的信息，该函数会很有用。我们仅返回切换_事件_，以便正确处理裁剪（clipping）。


    // 控件：列表框 (List Boxes)
    // - 这本质上是一个简单的包装器，通过使用带有 ImGuiChildFlags_FrameStyle 标志的 BeginChild/EndChild 来实现样式变化并显示标签。
    // - 如果你不需要标签，通常可以直接使用带有 ImGuiChildFlags_FrameStyle 标志的 BeginChild() 来达到同样的效果。
    // - 你可以按需提交内容并管理选择状态，例如通过创建 Selectable() 或任何其他项目。
    // - 简化版/旧版的 ListBox() API 是基于 BeginListBox()/EndListBox() 的辅助函数，为了方便起见予以保留。这与 Combo 的创建方式类似。
    // - 选择框体宽度：size.x > 0.0f：自定义 / size.x < 0.0f 或 -FLT_MIN：右对齐 / size.x = 0.0f（默认）：使用当前 ItemWidth
    // - 选择框体高度：size.y > 0.0f：自定义 / size.y < 0.0f 或 -FLT_MIN：底部对齐 / size.y = 0.0f（默认）：可容纳约 7 个项目的任意默认高度
    IMGUI_API bool BeginListBox(const char* label, const ImVec2& size = ImVec2(0, 0)); // 打开一个带框的滚动区域
    IMGUI_API void EndListBox(); // 仅在 BeginListBox() 返回 true 时调用 EndListBox()！
    IMGUI_API bool ListBox(const char* label, int* current_item, const char* const items[], int items_count, int height_in_items = -1);
    IMGUI_API bool ListBox(const char* label, int* current_item, const char* (*getter)(void* user_data, int idx), void* user_data, int items_count, int height_in_items = -1);


    // 控件：数据绘图
    // - 考虑使用 ImPlot (https://github.com/epezent/implot)，它的功能要强大得多！
    IMGUI_API void PlotLines(const char* label, const float* values, int values_count, int values_offset = 0, const char* overlay_text = NULL, float scale_min = FLT_MAX, float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0, 0), int stride = sizeof(float));
    IMGUI_API void PlotLines(const char* label, float(*values_getter)(void* data, int idx), void* data, int values_count, int values_offset = 0, const char* overlay_text = NULL, float scale_min = FLT_MAX, float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0, 0));
    IMGUI_API void PlotHistogram(const char* label, const float* values, int values_count, int values_offset = 0, const char* overlay_text = NULL, float scale_min = FLT_MAX, float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0, 0), int stride = sizeof(float));
    IMGUI_API void PlotHistogram(const char* label, float (*values_getter)(void* data, int idx), void* data, int values_count, int values_offset = 0, const char* overlay_text = NULL, float scale_min = FLT_MAX, float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0, 0));


    // 控件：Value() 辅助函数。
    // - 这些仅仅是使用格式化字符串调用 Text() 的快捷方式。以 "name: value" 格式输出单个值（提示：可以在代码中自由声明更多此类函数来处理自定义类型。你可以向 ImGui 命名空间添加函数）
    IMGUI_API void Value(const char* prefix, bool b);
    IMGUI_API void Value(const char* prefix, int v);
    IMGUI_API void Value(const char* prefix, unsigned int v);
    IMGUI_API void Value(const char* prefix, float v, const char* float_format = NULL);


    // 控件：菜单
    // - 在带有 ImGuiWindowFlags_MenuBar 标志的窗口上使用 BeginMenuBar()，以向其菜单栏添加内容。
    // - 使用 BeginMainMenuBar() 在屏幕顶部创建一个菜单栏并向其添加内容。
    // - 使用 BeginMenu() 创建一个菜单。你可以使用相同的标识符多次调用 BeginMenu()，以向其中追加更多项目。
    // - 请注意，MenuItem() 的键盘快捷键仅作为提示显示，目前 Dear ImGui *不会处理* 这些快捷键。
    IMGUI_API bool BeginMenuBar(); // 追加到当前窗口的菜单栏（需要在父窗口设置 ImGuiWindowFlags_MenuBar 标志）。
    IMGUI_API void EndMenuBar(); // 仅在 BeginMenuBar() 返回 true 时调用 EndMenuBar()！
    IMGUI_API bool BeginMainMenuBar(); // 创建并追加到一个全屏菜单栏。
    IMGUI_API void EndMainMenuBar(); // 仅在 BeginMainMenuBar() 返回 true 时调用 EndMainMenuBar()！
    IMGUI_API bool BeginMenu(const char* label, bool enabled = true); // 创建一个子菜单项。只有当此函数返回 true 时才调用 EndMenu()！
    IMGUI_API void EndMenu(); // 只有当 BeginMenu() 返回 true 时才调用 EndMenu()！
    IMGUI_API bool MenuItem(const char* label, const char* shortcut = NULL, bool selected = false, bool enabled = true); // 当被激活时返回 true。
    IMGUI_API bool MenuItem(const char* label, const char* shortcut, bool* p_selected, bool enabled = true); // 当被激活时返回 true + 如果 p_selected != NULL 则切换 (*p_selected) 的状态


    // 工具提示 (Tooltips)
    // - 工具提示是跟随鼠标的窗口。它们不会夺取焦点。
    // - 工具提示窗口可以包含任何类型的项目。
    // - SetTooltip() 基本上是 'if (BeginTooltip()) { Text(...); EndTooltip(); }' 这一惯用写法的快捷方式（细微的区别在于它会丢弃之前提交的任何工具提示）
    IMGUI_API bool BeginTooltip(); // 开始/追加一个工具提示窗口。
    IMGUI_API void EndTooltip(); // 仅在 BeginTooltip()/BeginItemTooltip() 返回 true 时调用 EndTooltip()！
    IMGUI_API void SetTooltip(const char* fmt, ...) IM_FMTARGS(1); // 设置纯文本工具提示。通常在 ImGui::IsItemHovered() 检查后使用。会覆盖之前所有对 SetTooltip() 的调用。
    IMGUI_API void SetTooltipV(const char* fmt, va_list args) IM_FMTLIST(1);


    // 工具提示：用于在悬停项目时显示工具提示的辅助函数
    // - BeginItemTooltip() 是 'if (IsItemHovered(ImGuiHoveredFlags_ForTooltip) && BeginTooltip())' 这一惯用法的简写。
    // - SetItemTooltip() 是 'if (IsItemHovered(ImGuiHoveredFlags_ForTooltip)) { SetTooltip(...); }' 这一惯用法的简写。
    // - 其中 'ImGuiHoveredFlags_ForTooltip' 本身是根据当前输入类型使用 'style.HoverFlagsForTooltipMouse' 或 'style.HoverFlagsForTooltipNav' 的简写。对于鼠标，它默认为 'ImGuiHoveredFlags_Stationary | ImGuiHoveredFlags_DelayShort'。
    IMGUI_API bool BeginItemTooltip(); // 如果前一个项目被悬停，则开始/追加一个工具提示窗口。
    IMGUI_API void SetItemTooltip(const char* fmt, ...) IM_FMTARGS(1); // 如果前一个项目被悬停，则设置一个纯文本工具提示。会覆盖之前对 SetTooltip() 的任何调用。
    IMGUI_API void SetItemTooltipV(const char* fmt, va_list args) IM_FMTLIST(1);


    // 弹出窗口、模态窗口
    // - 它们会阻挡其后方的正常鼠标悬停检测（以及大多数鼠标交互）。
    // - 如果不是模态的：可以通过点击外部任意位置或按下 ESCAPE 键来关闭。
    // - 它们的可见性状态（~bool）由内部持有，而不是像我们习惯的常规 Begin*() 调用那样由程序员持有。
    // - 以上三个属性是相关的：我们需要在库中保留弹窗的可见性状态，因为弹窗可能随时被关闭。
    // - 在调用 IsItemHovered() 或 IsWindowHovered() 时，你可以通过使用 ImGuiHoveredFlags_AllowWhenBlockedByPopup 来绕过因弹出窗口阻挡而产生的悬停限制。
    // - 重要提示：弹出窗口的标识符（ID）是相对于当前 ID 栈的，因此 OpenPopup 和 BeginPopup 通常需要在栈的同一层级调用。
    // 这有时会导致令人困惑的错误。未来可能会对此进行重构。
    // - BeginPopup()：查询弹出窗口状态，如果处于打开状态则开始向该窗口追加内容。如果返回值为 true，之后必须调用 EndPopup()。ImGuiWindowFlags 会被转发至该窗口。
    // - BeginPopupModal(): 拦截窗口后的所有交互，用户无法直接关闭，添加背景变暗效果，带有标题栏。
    IMGUI_API bool BeginPopup(const char* str_id, ImGuiWindowFlags flags = 0); // 如果弹窗处于打开状态则返回 true，此时您可以开始向其输出内容。
    IMGUI_API bool BeginPopupModal(const char* name, bool* p_open = NULL, ImGuiWindowFlags flags = 0); // 如果模态弹窗处于打开状态则返回 true，此时您可以开始向其输出内容。
    IMGUI_API void EndPopup(); // 仅在 BeginPopupXXX() 返回 true 时才调用 EndPopup()！


    // 弹出窗口：打开/关闭函数
    // - OpenPopup()：将弹出窗口状态设置为打开。可以使用 ImGuiPopupFlags 设置打开选项。
    // - 如果不是模态窗口：可以通过点击窗口外的任意位置或按 ESC 键来关闭。
    // - CloseCurrentPopup()：在 BeginPopup()/EndPopup() 作用域内使用，用于手动关闭。
    // - 当 Selectable()/MenuItem() 被激活时，默认会调用 CloseCurrentPopup()（待办：需要增加一些选项）。
    // - 使用 ImGuiPopupFlags_NoOpenOverExistingPopup 可以避免在同级已存在弹窗时再次打开。这等同于在调用 OpenPopup() 之前先测试 !IsAnyPopupOpen()。
    // - 在 BeginPopup() 之后使用 IsWindowAppearing() 可以判断窗口是否刚刚打开。
    IMGUI_API void OpenPopup(const char* str_id, ImGuiPopupFlags popup_flags = 0); // 调用此函数将弹窗标记为打开状态（请勿每帧调用！）。
    IMGUI_API void OpenPopup(ImGuiID id, ImGuiPopupFlags popup_flags = 0); // id 重载版本，便于从嵌套栈中调用
    IMGUI_API void OpenPopupOnItemClick(const char* str_id = NULL, ImGuiPopupFlags popup_flags = 0); // 辅助函数，用于在点击上一个项目时打开弹出窗口。默认为 ImGuiPopupFlags_MouseButtonRight == 1。（注意：实际上是在鼠标“释放”事件时触发，以保持与弹出窗口行为的一致性）
    IMGUI_API void CloseCurrentPopup(); // 手动关闭我们已经 Begin 进去的弹出窗口。


    // 弹出窗口：Open+Begin 组合辅助函数，用于创建上下文菜单。
    // - 辅助函数，用于执行 OpenPopup+BeginPopup，其中打开操作由悬停在项目上并右键单击等行为触发。
    // - 重要提示：请注意 BeginPopupContextXXX 接收的是 ImGuiPopupFlags，这与 OpenPopup() 相同，但与 BeginPopup() 不同。为了保持完全一致，我们未来可能会在 BeginPopupContextXXX 函数中加入 ImGuiWindowFlags。
    // - 重要提示：如果你在 1.92.6 版本之前曾对 BeginPopupContextXXX() 辅助函数使用过鼠标左键：
    // - 在此版本之前，OpenPopupOnItemClick()、BeginPopupContextItem()、BeginPopupContextWindow()、BeginPopupContextVoid() 在其函数签名中默认带有 'ImGuiPopupFlags popup_flags = 1'。
    // - 变更前：显式传递字面量 0 代表 ImGuiPopupFlags_MouseButtonLeft。默认值 1 代表 ImGuiPopupFlags_MouseButtonRight。
    // - 变更后：默认值 0 代表 ImGuiPopupFlags_MouseButtonRight。显式传递字面量 1 同样代表 ImGuiPopupFlags_MouseButtonRight（如果启用了旧版行为），否则将触发断言（如果禁用了旧版行为）。
    // - 简而言之：如果你不想在弹窗中使用鼠标右键，请务必使用命名的 ImGuiPopupFlags_MouseButtonXXXX 枚举值显式指定。
    // - 详见 imgui.cpp 中 2026/01/07 (1.92.6) 的“API BREAKING CHANGES”条目或 GitHub 话题 #9157。
    IMGUI_API bool BeginPopupContextItem(const char* str_id = NULL, ImGuiPopupFlags popup_flags = 0); // 当点击上一个项目时打开并开始弹出窗口。使用 str_id==NULL 将弹出窗口关联到上一个项目。如果你想在 Text() 等非交互式项目上使用它，你需要在此传入一个显式的 ID。请阅读 .cpp 文件中的注释！
    IMGUI_API bool BeginPopupContextWindow(const char* str_id = NULL, ImGuiPopupFlags popup_flags = 0);// 当点击当前窗口时打开并开始弹出窗口。
    IMGUI_API bool BeginPopupContextVoid(const char* str_id = NULL, ImGuiPopupFlags popup_flags = 0); // 当在空白处（没有窗口的地方）点击时打开并开始弹出窗口。


    // 弹出窗口：查询函数
    // - IsPopupOpen()：如果在弹出窗口栈的当前 BeginPopup() 层级下该弹出窗口已打开，则返回 true。
    // - 带有 ImGuiPopupFlags_AnyPopupId 的 IsPopupOpen()：如果在弹出窗口栈的当前 BeginPopup() 层级下有任何弹出窗口已打开，则返回 true。
    // - 带有 ImGuiPopupFlags_AnyPopupId + ImGuiPopupFlags_AnyPopupLevel 的 IsPopupOpen()：如果任何弹出窗口已打开，则返回 true。
    IMGUI_API bool IsPopupOpen(const char* str_id, ImGuiPopupFlags flags = 0); // 如果弹出窗口已打开，则返回 true。


    // 表格 (Tables)
    // - 功能齐全，用于替代旧版的列 (Columns) API。
    // - 示例代码请参考 Demo->Tables。通用注释请参考 imgui_tables.cpp 顶部。
    // - 可用标志的说明请参考 ImGuiTableFlags_ 和 ImGuiTableColumnFlags_ 枚举。
    // 典型的调用流程如下：
    // - 1. 调用 BeginTable()，如果返回 false 则提前退出。
    // - 2. （可选）调用 TableSetupColumn() 来提交列名、标志或默认设置。
    // - 3. （可选）调用 TableSetupScrollFreeze() 来请求冻结特定列或行的滚动。
    // - 4. （可选）调用 TableHeadersRow() 来提交标题行。名称将从 TableSetupColumn() 的数据中提取。
    // - 5. 填充内容：
    // - 在大多数情况下，你可以使用 TableNextRow() + TableSetColumnIndex(N) 来开始向某一列添加内容。
    // - 如果你将表格作为某种网格使用，即每一列都包含相同类型的内容，
    // 你可能更倾向于使用 TableNextColumn()，而不是 TableNextRow() + TableSetColumnIndex()。
    // TableNextColumn() 会在需要时自动换行到下一行。
    // - 重要提示：与旧的 Columns() API 相比，我们需要为第一列也调用 TableNextColumn()！
    // - 可能的调用流程总结：
    // - TableNextRow() -> TableSetColumnIndex(0) -> Text("Hello 0") -> TableSetColumnIndex(1) -> Text("Hello 1") // 正常
    // - TableNextRow() -> TableNextColumn() -> Text("Hello 0") -> TableNextColumn() -> Text("Hello 1") // 正常
    // - TableNextColumn() -> Text("Hello 0") -> TableNextColumn() -> Text("Hello 1") // 正常：TableNextColumn() 会自动跳转到下一行！
    // - TableNextRow() -> Text("Hello 0") // 错误！缺少 TableSetColumnIndex() 或 TableNextColumn()！文本将不会显示！
    // - 5. 调用 EndTable()
    IMGUI_API bool BeginTable(const char* str_id, int columns, ImGuiTableFlags flags = 0, const ImVec2& outer_size = ImVec2(0.0f, 0.0f), float inner_width = 0.0f);
    IMGUI_API void EndTable(); // 仅在 BeginTable() 返回 true 时调用 EndTable()！
    IMGUI_API void TableNextRow(ImGuiTableRowFlags row_flags = 0, float min_row_height = 0.0f); // 追加到新行的第一个单元格。'min_row_height' 包含最小的上下内边距，即 CellPadding.y * 2.0f。
    IMGUI_API bool TableNextColumn(); // 移动到下一列（如果当前在最后一列，则移动到下一行的第一列）。当该列可见时返回 true。
    IMGUI_API bool TableSetColumnIndex(int column_n); // 移动到指定列。当该列可见时返回 true。


    // 表格：表头与列声明
    // - 使用 TableSetupColumn() 来指定标签、调整大小策略、默认宽度/权重、ID 以及其他各种标志等。
    // - 使用 TableHeadersRow() 创建标题行，并为每一列自动提交一个 TableHeader()。
    // 标题是执行以下操作所必需的：重排、排序以及打开上下文菜单。
    // 也可以使用 ImGuiTableFlags_ContextMenuInBody 标志使上下文菜单在列主体中可用。
    // - 您可以使用 TableNextRow() + TableHeader() 调用来手动提交标题，但这仅在以下情况下有用：
    // 一些高级用法（例如：在表头行添加自定义小部件）。
    // - 使用 TableSetupScrollFreeze() 锁定列/行，使其在滚动时保持可见。
    IMGUI_API void TableSetupColumn(const char* label, ImGuiTableColumnFlags flags = 0, float init_width_or_weight = 0.0f, ImGuiID user_id = 0);
    IMGUI_API void TableSetupScrollFreeze(int cols, int rows); // 锁定列/行，使其在滚动时保持可见。
    IMGUI_API void TableHeader(const char* label); // 手动提交一个表头单元格（很少使用）
    IMGUI_API void TableHeadersRow(); // 根据 TableSetupColumn() 提供的数据提交一个包含表头单元格的行 + 提交上下文菜单
    IMGUI_API void TableAngledHeadersRow(); // 为每个带有 ImGuiTableColumnFlags_AngledHeader 标志的列提交一个倾斜表头行。必须是第一行。


    // 表格：排序及其他杂项函数
    // - 排序：调用 TableGetSortSpecs() 以获取表格最新的排序规格。不进行排序时返回 NULL。
    // 当 'sort_specs->SpecsDirty == true' 时，你应该对数据进行排序。当排序规则发生变化时，该值将为 true。
    // 自上次调用以来已更改，或者是第一次调用。请确保在排序后设置 'SpecsDirty = false'，
    // 否则你可能会在每一帧都浪费地对数据进行排序！
    // - 函数参数 'int column_n' 将默认值 -1 视为与传递当前列索引相同。
    IMGUI_API ImGuiTableSortSpecs* TableGetSortSpecs(); // 获取表格最新的排序规格（如果不排序则为 NULL）。生命周期：请勿跨帧持有此指针，或在后续调用 BeginTable() 后继续持有。
    IMGUI_API int TableGetColumnCount(); // 返回列数（传递给 BeginTable 的值）
    IMGUI_API int TableGetColumnIndex(); // 返回当前列索引。
    IMGUI_API int TableGetRowIndex(); // 返回当前行索引（包含表头行）
    IMGUI_API const char* TableGetColumnName(int column_n = -1); // 如果列没有通过 TableSetupColumn() 声明名称，则返回 ""。传入 -1 以使用当前列。
    IMGUI_API ImGuiTableColumnFlags TableGetColumnFlags(int column_n = -1); // 返回列标志，以便查询其 Enabled/Visible/Sorted/Hovered 等状态标志。传入 -1 以使用当前列。
    IMGUI_API void TableSetColumnEnabled(int column_n, bool v);// 更改用户可访问的列启用/禁用状态。设置为 false 可隐藏该列。用户可以通过上下文菜单自行更改此状态（右键单击表头，或在带有 ImGuiTableFlags_ContextMenuInBody 标志的列主体中右键单击）
    IMGUI_API int TableGetHoveredColumn(); // 返回悬停的列索引。如果未悬停在表格上则返回 -1。如果悬停在可见列右侧的未使用空间，则返回 columns_count。也可以使用 (TableGetColumnFlags() & ImGuiTableColumnFlags_IsHovered) 代替。
    IMGUI_API void TableSetBgColor(ImGuiTableBgTarget target, ImU32 color, int column_n = -1); // 更改单元格、行或列的颜色。详见 ImGuiTableBgTarget_ 标志。


    // 旧版列 API（建议优先使用 Tables！）
    // - 您也可以使用 SameLine(pos_x) 来模拟简化的列。
    IMGUI_API void Columns(int count = 1, const char* id = NULL, bool borders = true);
    IMGUI_API void NextColumn(); // 下一列，默认跳转至当前行或当前行结束后的下一行
    IMGUI_API int GetColumnIndex(); // 获取当前列索引
    IMGUI_API float GetColumnWidth(int column_index = -1); // 获取列宽（以像素为单位）。传入 -1 则使用当前列
    IMGUI_API void SetColumnWidth(int column_index, float width); // 设置列宽（以像素为单位）。传入 -1 则使用当前列
    IMGUI_API float GetColumnOffset(int column_index = -1); // 获取列线的位置（以像素为单位，从内容区域左侧算起）。传入 -1 使用当前列，否则范围为 0..GetColumnsCount()（含）。第 0 列通常为 0.0f
    IMGUI_API void SetColumnOffset(int column_index, float offset_x); // 设置列线的位置（以像素为单位，从内容区域左侧算起）。传入 -1 则使用当前列
    IMGUI_API int GetColumnsCount();


    // 标签栏，标签 (Tab Bars, Tabs)
    // - 注意：标签页由停靠系统（在 'docking' 分支中）自动创建。使用这些函数可以手动创建标签栏/标签页。
    IMGUI_API bool BeginTabBar(const char* str_id, ImGuiTabBarFlags flags = 0); // 创建并附加到标签栏
    IMGUI_API void EndTabBar(); // 仅在 BeginTabBar() 返回 true 时调用 EndTabBar()！
    IMGUI_API bool BeginTabItem(const char* label, bool* p_open = NULL, ImGuiTabItemFlags flags = 0); // 创建一个选项卡（Tab）。如果该选项卡被选中则返回 true。
    IMGUI_API void EndTabItem(); // 仅在 BeginTabItem() 返回 true 时才调用 EndTabItem()！
    IMGUI_API bool TabItemButton(const char* label, ImGuiTabItemFlags flags = 0); // 创建一个行为类似于按钮的选项卡。点击时返回 true。无法在选项卡栏中被选中。
    IMGUI_API void SetTabItemClosed(const char* tab_or_docked_window_label); // 提前通知选项卡栏（TabBar）或停靠（Docking）系统某个选项卡/窗口已关闭（有助于减少可重排序选项卡栏上的视觉闪烁）。对于选项卡栏：在 BeginTabBar() 之后且在提交选项卡之前调用。否则请传入窗口名称调用。


    // 日志/捕获
    // - 界面中的所有文本输出都可以捕获到 tty、文件或剪贴板。默认情况下，树节点在记录日志期间会自动展开。
    IMGUI_API void LogToTTY(int auto_open_depth = -1); // 开始记录日志到 tty (stdout)
    IMGUI_API void LogToFile(int auto_open_depth = -1, const char* filename = NULL); // 开始记录日志到文件
    IMGUI_API void LogToClipboard(int auto_open_depth = -1); // 开始记录到系统剪贴板
    IMGUI_API void LogFinish(); // 停止记录（关闭文件等）
    IMGUI_API void LogButtons(); // 用于显示记录到 tty/文件/剪贴板按钮的辅助函数
    IMGUI_API void LogText(const char* fmt, ...) IM_FMTARGS(1); // 直接将文本数据传递给日志（不显示）
    IMGUI_API void LogTextV(const char* fmt, va_list args) IM_FMTLIST(1);


    // 拖放
    // - 在源项目上，调用 BeginDragDropSource()，如果其返回值为 true，则还需调用 SetDragDropPayload() + EndDragDropSource()。
    // - 在目标候选对象上，调用 BeginDragDropTarget()，如果其返回值为 true，则还需调用 AcceptDragDropPayload() + EndDragDropTarget()。
    // - 如果你停止调用 BeginDragDropSource()，有效载荷（payload）会被保留，但它将不再有预览工具提示（目前我们会显示一个后备的 "..." 工具提示，参见 #1725）
    // - 一个项目可以同时作为拖动源（drag source）和放置目标（drop target）。
    IMGUI_API bool BeginDragDropSource(ImGuiDragDropFlags flags = 0); // 在提交可能被拖动的项目后调用。当此函数返回 true 时，你可以调用 SetDragDropPayload() + EndDragDropSource()
    IMGUI_API bool SetDragDropPayload(const char* type, const void* data, size_t sz, ImGuiCond cond = 0); // type 是用户定义的字符串，最大长度为 32 个字符。以 '_' 开头的字符串保留给 dear imgui 内部类型使用。数据会被 imgui 复制并持有。当有效载荷被接受时返回 true。
    IMGUI_API void EndDragDropSource(); // 仅在 BeginDragDropSource() 返回 true 时调用 EndDragDropSource()！
    IMGUI_API bool BeginDragDropTarget(); // 在提交可能接收载荷的项后调用。如果返回 true，则可以调用 AcceptDragDropPayload() + EndDragDropTarget()
    IMGUI_API const ImGuiPayload* AcceptDragDropPayload(const char* type, ImGuiDragDropFlags flags = 0); // 接受给定类型的内容。如果设置了 ImGuiDragDropFlags_AcceptBeforeDelivery，您可以在松开鼠标按钮之前预览载荷内容。
    IMGUI_API void EndDragDropTarget(); // 仅在 BeginDragDropTarget() 返回 true 时调用 EndDragDropTarget()！
    IMGUI_API const ImGuiPayload* GetDragDropPayload(); // 从任何地方直接查看当前有效载荷。当拖放结束或处于非活动状态时返回 NULL。使用 ImGuiPayload::IsDataType() 来测试有效载荷类型。


    // 禁用 [测试版 API]
    // - 禁用所有用户交互并使项目视觉效果变暗（在当前颜色上应用 style.DisabledAlpha）
    // - 这些可以嵌套，但不能用于启用已经禁用的部分（栈中只要有一个 BeginDisabled(true) 就足以保持所有内容处于禁用状态）
    // - 工具提示窗口会自动排除在禁用状态之外。请注意，除非使用 ImGuiHoveredFlags_AllowWhenDisabled，否则 IsItemHovered() 默认对禁用项返回 false。
    // - BeginDisabled(false)/EndDisabled() 基本上不执行任何操作，提供它是为了方便布尔表达式的使用（作为一种微优化：如果你有成千上万对 BeginDisabled(false)/EndDisabled()，你可能需要重构代码以避免这些调用）
    IMGUI_API void BeginDisabled(bool disabled = true);
    IMGUI_API void EndDisabled();


    // 裁剪
    // - 鼠标悬停受 ImGui::PushClipRect() 调用的影响，这与直接调用 ImDrawList::PushClipRect() 不同，后者仅影响渲染。
    IMGUI_API void PushClipRect(const ImVec2& clip_rect_min, const ImVec2& clip_rect_max, bool intersect_with_current_clip_rect);
    IMGUI_API void PopClipRect();


    // 焦点、激活
    IMGUI_API void SetItemDefaultFocus(); // 将上一个项目设置为新出现窗口的默认焦点项目。
    IMGUI_API void SetKeyboardFocusHere(int offset = 0); // 将键盘焦点设置在下一个控件上。使用正数“offset”来访问多组件控件的子组件。使用 -1 来访问上一个控件。


    // 键盘/手柄导航
    IMGUI_API void SetNavCursorVisible(bool visible); // 修改键盘/手柄光标的可见性。默认情况下：使用方向键时显示，使用鼠标点击时隐藏。


    // 重叠模式
    IMGUI_API void SetNextItemAllowOverlap(); // 允许下一个项目被后续项目重叠。适用于不可见按钮、可选择项（Selectable）、树节点（TreeNode）覆盖了后续项目可能需要添加的区域。请注意，Selectable() 和 TreeNode() 都有实现此功能的专用标志。


    // 项目/控件实用工具及查询函数
    // - 大多数函数都是针对上一个已提交的控件（Item）。
    // - 请参阅演示窗口（Demo Window）中的“Widgets->Querying Status”，以获取大多数此类函数的交互式可视化演示。
    IMGUI_API bool IsItemHovered(ImGuiHoveredFlags flags = 0); // 上一个控件是否被悬停？（且可用，即未被弹窗等遮挡）。更多选项请参阅 ImGuiHoveredFlags。
    IMGUI_API bool IsItemActive(); // 上一个控件是否处于激活状态？（例如按钮正被按住、文本框正在编辑。在控件上按住鼠标键时，此函数将持续返回 true。不具备交互能力的控件将始终返回 false）
    IMGUI_API bool IsItemFocused(); // 上一个控件是否处于键盘/手柄导航的焦点状态？
    IMGUI_API bool IsItemClicked(ImGuiMouseButton mouse_button = 0); // 上一个控件是否被悬停且被鼠标点击？(**) == IsMouseClicked(mouse_button) && IsItemHovered()。注意：(**) 这并不等同于 Button() 等控件的行为。请阅读函数定义中的注释。
    IMGUI_API bool IsItemVisible(); // 上一个控件是否可见？（控件可能因裁剪/滚动而处于视线之外）
    IMGUI_API bool IsItemEdited(); // 上一个控件是否在本帧修改了其底层数值？或者被按下了？这通常与许多小部件返回的 "bool" 值相同。
    IMGUI_API bool IsItemActivated(); // 上一个控件是否刚刚变为激活状态（该控件此前处于非激活状态）。
    IMGUI_API bool IsItemDeactivated(); // 上一个控件是否刚刚变为非激活状态（该控件此前处于激活状态）。适用于需要连续编辑的控件的撤销/重做模式。
    IMGUI_API bool IsItemDeactivatedAfterEdit(); // 上一个控件是否刚刚变为非激活状态，且在其处于激活状态时改变了数值？（例如滑块/拖拽框被移动了）。适用于需要连续编辑的控件的撤销/重做模式。请注意，可能会出现误报（某些控件如 Combo()/ListBox()/Selectable() 即使在点击已选中的项目时也会返回 true）。
    IMGUI_API bool IsItemToggledOpen(); // 上一个控件的展开状态是否刚刚被切换？由 TreeNode() 设置。
    IMGUI_API bool IsAnyItemHovered(); // 是否有任意项处于悬停状态？
    IMGUI_API bool IsAnyItemActive(); // 是否有任意项处于激活状态？
    IMGUI_API bool IsAnyItemFocused(); // 是否有任意项处于聚焦状态？
    IMGUI_API ImGuiID GetItemID(); // 获取最后一项的 ID（~~ 通常与此前的 ImGui::GetID(label) 相同）
    IMGUI_API ImVec2 GetItemRectMin(); // 获取上一个控件的左上角边界矩形坐标（屏幕空间）
    IMGUI_API ImVec2 GetItemRectMax(); // 获取上一个控件的右下角边界矩形坐标（屏幕空间）
    IMGUI_API ImVec2 GetItemRectSize(); // 获取上一个控件的大小
    IMGUI_API ImGuiItemFlags GetItemFlags(); // 获取上一个控件的通用标志


    // 视口
    // - 目前代表由托管 Dear ImGui 窗口的应用程序所创建的平台窗口。
    // - 在启用了多视口的“docking”分支中，我们将这一概念扩展为拥有多个活动视口。
    // - 未来我们将进一步扩展这一概念，使其也能代表平台显示器，并支持“无主平台窗口”的操作模式。
    IMGUI_API ImGuiViewport* GetMainViewport(); // 返回主/默认视口。该值永远不会为 NULL。


    // 背景/前景绘制列表 (Background/Foreground Draw Lists)
    IMGUI_API ImDrawList* GetBackgroundDrawList(); // 此绘制列表将最先被渲染。适用于在 Dear ImGui 内容背后快速绘制形状或文本。
    IMGUI_API ImDrawList* GetForegroundDrawList(); // 此绘制列表将最后被渲染。适用于在 Dear ImGui 内容之上快速绘制形状或文本。


    // 杂项工具函数
    IMGUI_API bool IsRectVisible(const ImVec2& size); // 测试矩形（给定大小，从光标位置开始）是否可见 / 未被裁剪。
    IMGUI_API bool IsRectVisible(const ImVec2& rect_min, const ImVec2& rect_max); // 测试矩形（屏幕空间）是否可见 / 未被裁剪。用于在用户侧进行粗略裁剪。
    IMGUI_API double GetTime(); // 获取全局 imgui 时间。每帧随 io.DeltaTime 递增。
    IMGUI_API int GetFrameCount(); // 获取全局 imgui 帧计数。每一帧增加 1。
    IMGUI_API ImDrawListSharedData* GetDrawListSharedData(); // 在创建自定义 ImDrawList 实例时可能会用到此函数。
    IMGUI_API const char* GetStyleColorName(ImGuiCol idx); // 获取枚举值对应的字符串（用于显示、保存等）。
    IMGUI_API void SetStateStorage(ImGuiStorage* storage); // 用自定义存储替换当前窗口存储（如果你想自行操作它，通常是清除其中的子部分）
    IMGUI_API ImGuiStorage* GetStateStorage();


    // 文本工具 (Text Utilities)
    IMGUI_API ImVec2 CalcTextSize(const char* text, const char* text_end = NULL, bool hide_text_after_double_hash = false, float wrap_width = -1.0f);


    // 颜色工具 (Color Utilities)
    IMGUI_API ImVec4 ColorConvertU32ToFloat4(ImU32 in);
    IMGUI_API ImU32 ColorConvertFloat4ToU32(const ImVec4& in);
    IMGUI_API void ColorConvertRGBtoHSV(float r, float g, float b, float& out_h, float& out_s, float& out_v);
    IMGUI_API void ColorConvertHSVtoRGB(float h, float s, float v, float& out_r, float& out_g, float& out_b);


    // 输入实用程序：原始键盘/鼠标/手柄访问
    // - 考虑使用 Shortcut() 函数而不是 IsKeyPressed()/IsKeyChordPressed()！Shortcut() 更易于使用且功能更全（可以进行焦点路由检查）。
    // - ImGuiKey 枚举包含所有可能的键盘、鼠标和手柄输入（例如 ImGuiKey_A、ImGuiKey_MouseLeft、ImGuiKey_GamepadDpadUp...）。
    // - （遗留问题：在 v1.87 (2022-02) 之前，我们使用小于 512 的 ImGuiKey 值来承载由各后端定义的原生/用户索引。这在 1.87 (2022-02) 中被废弃，并在 1.91.5 (2024-11) 中被完全移除。参见 https://github.com/ocornut/imgui/issues/4921）
    IMGUI_API bool IsKeyDown(ImGuiKey key); // 按键是否正被按住。
    IMGUI_API bool IsKeyPressed(ImGuiKey key, bool repeat = true); // 按键是否被按下（状态从未按下变为按下）？重复频率使用 io.KeyRepeatDelay / KeyRepeatRate。
    IMGUI_API bool IsKeyReleased(ImGuiKey key); // 按键是否被释放（状态从按下变为未按下）？
    IMGUI_API bool IsKeyChordPressed(ImGuiKeyChord key_chord); // 组合键（修饰键 + 按键）是否被按下，例如你可以传入 'ImGuiMod_Ctrl | ImGuiKey_S' 作为组合键。此函数不进行任何路由或焦点检查，请考虑改用 Shortcut() 函数。
    IMGUI_API int GetKeyPressedAmount(ImGuiKey key, float repeat_delay, float rate); // 使用提供的重复延迟/频率。返回一个计数值，通常为 0 或 1，但如果 RepeatRate 足够小且 DeltaTime > RepeatRate，则可能大于 1。
    IMGUI_API const char* GetKeyName(ImGuiKey key); // [调试] 返回按键的英文名称。这些名称仅用于调试目的，不应持久化保存或进行比较。
    IMGUI_API void SetNextFrameWantCaptureKeyboard(bool want_capture_keyboard); // 在下一帧覆盖 io.WantCaptureKeyboard 标志（该标志由您的应用程序处理，通常为 true 时指示应用忽略输入）。例如：当您的控件被悬停时强制捕获键盘。这相当于在下一次 NewFrame() 调用后设置 "io.WantCaptureKeyboard = want_capture_keyboard"。


    // 输入工具：快捷键测试与路由
    // - 典型用法例如：'if (ImGui::Shortcut(ImGuiMod_Ctrl | ImGuiKey_S)) { ... }'。
    // - 标志位：默认路由使用 ImGuiInputFlags_RouteFocused，但请参阅 ImGuiInputFlags_ 中的 ImGuiInputFlags_RouteGlobal 及其他选项！
    // - 标志位：使用 ImGuiInputFlags_Repeat 以支持重复触发。
    // - ImGuiKeyChord = 一个 ImGuiKey + 可选的 ImGuiMod_Alt/ImGuiMod_Ctrl/ImGuiMod_Shift/ImGuiMod_Super。
    // ImGuiKey_C // 可被接受 ImGuiKey 或 ImGuiKeyChord 参数的函数接收
    // ImGuiMod_Ctrl | ImGuiKey_C // 可被接受 ImGuiKeyChord 参数的函数接收
    // 只有 ImGuiMod_XXX 值可以合法地与 ImGuiKey 组合。你不能将两个 ImGuiKey 值组合。
    // - 核心理念是多个调用者可能对同一个快捷键注册兴趣，但只有一个所有者能获取它。
    // 父窗口 -> 调用 Shortcut(Ctrl+S) // 当父窗口获得焦点时，父窗口接收该快捷键。
    // 子窗口 1 -> 调用 Shortcut(Ctrl+S) // 当子窗口 1 获得焦点时，子窗口 1 接收该快捷键（子窗口 1 会覆盖父窗口的快捷键）
    // 子窗口2 -> 无调用 // 当子窗口2获得焦点时，父窗口接收该快捷键。
    // 整个系统的运行与顺序无关，因此即使子窗口1在父窗口之前进行调用，结果也是一致的。
    // 这是一个重要的特性，因为它有助于处理外部代码或大型代码库。
    // - 为了理解其中的区别：
    // - IsKeyChordPressed() 会比较修饰键并调用 IsKeyPressed()
    // -> 该函数没有副作用。
    // - Shortcut() 提交一个路由，路由被解析后，如果当前可以进行路由，它将调用 IsKeyChordPressed()
    // -> 该函数具有（预期的）副作用，因为它可以防止其他调用获取该路由。
    // - 在“Metrics/Debugger->Inputs”中可视化已注册的路由。
    IMGUI_API bool Shortcut(ImGuiKeyChord key_chord, ImGuiInputFlags flags = 0);
    IMGUI_API void SetNextItemShortcut(ImGuiKeyChord key_chord, ImGuiInputFlags flags = 0);


    // 输入实用工具：按键/输入所有权 [BETA]
    // - 一个常见的用例是允许您的控件禁用标准的输入行为，
    // 例如 Tab 或 Alt 键的处理、鼠标滚轮滚动等。
    // 例如：Button(...); SetItemKeyOwner(ImGuiKey_MouseWheelY); 可以使悬停/激活按钮时禁用滚轮滚动。
    // - 提示：ImGuiKey 枚举包含对鼠标按钮和手柄的访问，因此按键所有权（key ownership）也可以应用于它们。
    // - 许多相关功能仍位于 imgui_internal.h 中。例如，大多数 IsKeyXXX()/IsMouseXXX() 函数都有一个支持所有者 ID（owner-id-aware）的版本。
    IMGUI_API void SetItemKeyOwner(ImGuiKey key); // 如果最后一个项目处于悬停或激活状态，则将其设为按键所有者。等同于 'if (IsItemHovered() || IsItemActive()) { SetKeyOwner(key, GetItemID());'。


    // 输入工具：鼠标
    // - 若要引用鼠标按键，您可以在代码中使用命名的枚举，例如 ImGuiMouseButton_Left，ImGuiMouseButton_Right。
    // - 您也可以使用普通的整数：永久保证 0=左键，1=右键，2=中键。
    // - 只有当鼠标移动距离初始点击位置一定距离后，才会报告拖拽操作（参见 'lock_threshold' 和 'io.MouseDraggingThreshold'）
    IMGUI_API bool IsMouseDown(ImGuiMouseButton button); // 鼠标按键是否正被按住？
    IMGUI_API bool IsMouseClicked(ImGuiMouseButton button, bool repeat = false); // 鼠标按键是否被点击？（状态从“未按下”变为“按下”）。等同于 GetMouseClickedCount() == 1。
    IMGUI_API bool IsMouseReleased(ImGuiMouseButton button); // 鼠标按键是否被释放？（状态从“按下”变为“未按下”）
    IMGUI_API bool IsMouseDoubleClicked(ImGuiMouseButton button); // 鼠标按键是否被双击？等同于 GetMouseClickedCount() == 2。（注意，双击时 IsMouseClicked() 也会返回 true）
    IMGUI_API bool IsMouseReleasedWithDelay(ImGuiMouseButton button, float delay); // 延迟鼠标释放（请谨慎使用！）。通常与 'delay >= io.MouseDoubleClickTime' 以及 'io.MouseClickedLastCount==1' 测试结合使用。这是一种极少使用的 UI 惯用法，但某些应用程序会用到：例如 MS 资源管理器中单击图标进行重命名。
    IMGUI_API int GetMouseClickedCount(ImGuiMouseButton button); // 返回点击发生时连续鼠标点击的次数（否则返回 0）。
    IMGUI_API bool IsMouseHoveringRect(const ImVec2& r_min, const ImVec2& r_max, bool clip = true);// 鼠标是否悬停在给定的矩形区域内（屏幕空间）。受当前裁剪设置限制，但忽略焦点/窗口排序/弹出窗口阻挡等其他因素。
    IMGUI_API bool IsMousePosValid(const ImVec2* mouse_pos = NULL); // 按照惯例，我们使用 (-FLT_MAX, -FLT_MAX) 来表示鼠标不可用
    IMGUI_API bool IsAnyMouseDown(); // [即将废弃] 是否有任意鼠标按键被按下？此函数原为后端设计，但建议由后端自行维护按键掩码，因为即将推出的输入队列系统将使此函数失效。
    IMGUI_API ImVec2 GetMousePos(); // 用户提供的 ImGui::GetIO().MousePos 的快捷方式，旨在与其他调用保持一致
    IMGUI_API ImVec2 GetMousePosOnOpeningCurrentPopup(); // 获取打开当前 BeginPopup() 所指向的弹出窗口时的鼠标位置（辅助函数，避免用户自行记录该值）
    IMGUI_API bool IsMouseDragging(ImGuiMouseButton button, float lock_threshold = -1.0f); // 鼠标是否正在拖拽？（如果 lock_threshold < 0.0f，则使用 io.MouseDraggingThreshold）
    IMGUI_API ImVec2 GetMouseDragDelta(ImGuiMouseButton button = 0, float lock_threshold = -1.0f); // 返回鼠标按键按下期间或刚释放时，相对于初始点击位置的位移增量。在鼠标移动距离至少超过一次阈值之前，该值会被锁定并返回 0.0f（如果 lock_threshold < 0.0f，则使用 io.MouseDraggingThreshold）
    IMGUI_API void ResetMouseDragDelta(ImGuiMouseButton button = 0); // 重置鼠标拖拽位移增量
    IMGUI_API ImGuiMouseCursor GetMouseCursor(); // 获取期望的鼠标光标形状。注意：该值在 ImGui::NewFrame() 中重置，并在帧期间更新。在 Render() 之前有效。如果你通过设置 io.MouseDrawCursor 使用软件渲染，ImGui 将为你渲染这些光标
    IMGUI_API void SetMouseCursor(ImGuiMouseCursor cursor_type); // 设置期望的鼠标光标形状
    IMGUI_API void SetNextFrameWantCaptureMouse(bool want_capture_mouse); // 在下一帧覆盖 io.WantCaptureMouse 标志（该标志留给您的应用程序处理，通常为 true 时指示您的应用忽略输入）。这相当于在下一次调用 NewFrame() 后设置 "io.WantCaptureMouse = want_capture_mouse;"。


    // 剪贴板工具 (Clipboard Utilities)
    // - 另请参阅 LogToClipboard() 函数，以将 GUI 内容捕获到剪贴板，或轻松地将文本数据输出到剪贴板。
    IMGUI_API const char* GetClipboardText();
    IMGUI_API void SetClipboardText(const char* text);


    // 设置/.Ini 实用程序
    // - 如果 io.IniFilename != NULL（默认为 "imgui.ini"），则会自动调用磁盘函数。
    // - 将 io.IniFilename 设置为 NULL 以进行手动加载/保存。关于手动处理 .ini 保存的方法，请阅读 io.WantSaveIniSettings 的说明。
    // - 重要提示：默认值 "imgui.ini" 是相对于当前工作目录的！大多数应用程序会希望将其锁定为绝对路径（例如，与可执行文件相同的路径）。
    IMGUI_API void LoadIniSettingsFromDisk(const char* ini_filename); // 在 CreateContext() 之后、第一次调用 NewFrame() 之前调用。NewFrame() 会自动调用 LoadIniSettingsFromDisk(io.IniFilename)。
    IMGUI_API void LoadIniSettingsFromMemory(const char* ini_data, size_t ini_size = 0); // 在 CreateContext() 之后、第一次调用 NewFrame() 之前调用，用于从你自己的数据源提供 .ini 数据。
    IMGUI_API void SaveIniSettingsToDisk(const char* ini_filename); // 如果 io.IniFilename 不为空，在任何需要反映到 .ini 文件的修改发生几秒后（以及调用 DestroyContext 时），此函数会被自动调用。
    IMGUI_API const char* SaveIniSettingsToMemory(size_t* out_ini_size = NULL); // 返回一个以零结尾的字符串，其中包含 .ini 数据，你可以通过自己的方式进行保存。当 io.WantSaveIniSettings 被置位时调用，然后通过你自己的方式保存数据并清除 io.WantSaveIniSettings。


    // 调试实用程序
    // - 你主要的调试伙伴是 ShowMetricsWindow() 函数。
    // - 交互式工具均可通过 'Dear ImGui Demo->Tools' 菜单访问。
    // - 阅读 https://github.com/ocornut/imgui/wiki/Debug-Tools 以获取所有可用调试工具的说明。
    IMGUI_API void DebugTextEncoding(const char* text);
    IMGUI_API void DebugFlashStyleColor(ImGuiCol idx);
    IMGUI_API void DebugStartItemPicker();
    IMGUI_API bool DebugCheckVersionAndDataLayout(const char* version_str, size_t sz_io, size_t sz_style, size_t sz_vec2, size_t sz_vec4, size_t sz_drawvert, size_t sz_drawidx); // 此函数由 IMGUI_CHECKVERSION() 宏调用。
#ifndef IMGUI_DISABLE_DEBUG_TOOLS
    IMGUI_API void DebugLog(const char* fmt, ...) IM_FMTARGS(1); // 请通过 IMGUI_DEBUG_LOG() 调用，以便在调用方代码中实现最大程度的剥离！
    IMGUI_API void DebugLogV(const char* fmt, va_list args) IM_FMTLIST(1);
#endif


    // 内存分配器
    // - 这些函数不依赖于当前上下文。
    // - DLL 用户：堆和全局变量不跨越 DLL 边界共享！你需要为调用的每个静态/DLL 边界调用 SetCurrentContext() + SetAllocatorFunctions()。
    // 详情请阅读 imgui.cpp 中的 "Context and Memory Allocators" 章节。
    IMGUI_API void SetAllocatorFunctions(ImGuiMemAllocFunc alloc_func, ImGuiMemFreeFunc free_func, void* user_data = NULL);
    IMGUI_API void GetAllocatorFunctions(ImGuiMemAllocFunc* p_alloc_func, ImGuiMemFreeFunc* p_free_func, void** p_user_data);
    IMGUI_API void* MemAlloc(size_t size);
    IMGUI_API void MemFree(void* ptr);


} // namespace ImGui


//-----------------------------------------------------------------------------
// [SECTION] 标志与枚举 (Flags & Enumerations)
//-----------------------------------------------------------------------------


// ImGui::Begin() 的标志
// (这些是针对单个窗口的标志。在 ImGuiIO 中还有共享标志：io.ConfigWindowsResizeFromEdges 和 io.ConfigWindowsMoveFromTitleBarOnly)
enum ImGuiWindowFlags_
{
    ImGuiWindowFlags_None = 0,
    ImGuiWindowFlags_NoTitleBar = 1 << 0, // 禁用标题栏
    ImGuiWindowFlags_NoResize = 1 << 1, // 禁用用户通过右下角手柄调整大小
    ImGuiWindowFlags_NoMove = 1 << 2, // 禁用用户移动窗口
    ImGuiWindowFlags_NoScrollbar = 1 << 3, // 禁用滚动条（窗口仍可通过鼠标或程序进行滚动）
    ImGuiWindowFlags_NoScrollWithMouse = 1 << 4, // 禁用用户使用鼠标滚轮进行垂直滚动。在子窗口中，除非同时设置了 NoScrollbar，否则鼠标滚轮事件将传递给父窗口。
    ImGuiWindowFlags_NoCollapse = 1 << 5, // 禁用用户通过双击折叠窗口。也指代窗口菜单按钮（例如在停靠节点内）。
    ImGuiWindowFlags_AlwaysAutoResize = 1 << 6, // 每帧都根据内容自动调整窗口大小
    ImGuiWindowFlags_NoBackground = 1 << 7, // 禁用绘制背景颜色（WindowBg 等）和外部边框。类似于使用 SetNextWindowBgAlpha(0.0f)。
    ImGuiWindowFlags_NoSavedSettings = 1 << 8, // 永不从 .ini 文件中加载/保存设置
    ImGuiWindowFlags_NoMouseInputs = 1 << 9, // 禁用鼠标捕获，悬停测试将直接穿透。
    ImGuiWindowFlags_MenuBar = 1 << 10, // 具有菜单栏
    ImGuiWindowFlags_HorizontalScrollbar = 1 << 11, // 允许显示水平滚动条（默认关闭）。你可以在调用 Begin() 之前使用 SetNextWindowContentSize(ImVec2(width,0.0f)); 来指定宽度。请参阅 imgui_demo 中“Horizontal Scrolling”部分的代码。
    ImGuiWindowFlags_NoFocusOnAppearing = 1 << 12, // 当窗口从隐藏状态转为可见状态时，禁用自动获取焦点
    ImGuiWindowFlags_NoBringToFrontOnFocus = 1 << 13, // 当窗口获取焦点时（例如点击窗口或通过程序赋予焦点），禁用将其置于前台的操作
    ImGuiWindowFlags_AlwaysVerticalScrollbar = 1 << 14, // 始终显示垂直滚动条（即使内容高度 ContentSize.y < 窗口高度 Size.y）
    ImGuiWindowFlags_AlwaysHorizontalScrollbar = 1 << 15, // 始终显示水平滚动条（即使内容宽度 ContentSize.x < 窗口宽度 Size.x）
    ImGuiWindowFlags_NoNavInputs = 1 << 16, // 窗口内不接收键盘/手柄导航输入
    ImGuiWindowFlags_NoNavFocus = 1 << 17, // 键盘/手柄导航时不聚焦此窗口（例如：Ctrl+Tab 切换时会跳过此窗口）
    ImGuiWindowFlags_UnsavedDocument = 1 << 18, // 在标题旁显示一个圆点。在选项卡/停靠上下文中使用时，点击 X 会选中该选项卡且不假设关闭（将等待用户停止提交该选项卡）。否则，按下 X 时会假设关闭，因此如果你继续提交，该选项卡可能会重新出现在选项卡栏末尾。
    ImGuiWindowFlags_NoNav = ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus,
    ImGuiWindowFlags_NoDecoration = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse,
    ImGuiWindowFlags_NoInputs = ImGuiWindowFlags_NoMouseInputs | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus,


    // [内部]
    ImGuiWindowFlags_ChildWindow = 1 << 24, // 请勿使用！由 BeginChild() 内部使用
    ImGuiWindowFlags_Tooltip = 1 << 25, // 请勿使用！由 BeginTooltip() 内部使用
    ImGuiWindowFlags_Popup = 1 << 26, // 请勿使用！由 BeginPopup() 内部使用
    ImGuiWindowFlags_Modal = 1 << 27, // 请勿使用！由 BeginPopupModal() 内部使用
    ImGuiWindowFlags_ChildMenu = 1 << 28, // 请勿使用！由 BeginMenu() 内部使用


    // 已废弃的名称
#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
//ImGuiWindowFlags_NavFlattened = 1 << 29, // 在 1.90.9 中已废弃：已移动至 ImGuiChildFlags。BeginChild(name, size, 0, ImGuiWindowFlags_NavFlattened) --> BeginChild(name, size, ImGuiChildFlags_NavFlattened, 0)
//ImGuiWindowFlags_AlwaysUseWindowPadding = 1 << 30, // 在 1.90.0 中已废弃：已移动至 ImGuiChildFlags。BeginChild(name, size, 0, ImGuiWindowFlags_AlwaysUseWindowPadding) --> BeginChild(name, size, ImGuiChildFlags_AlwaysUseWindowPadding, 0)
#endif
};


// ImGui::BeginChild() 的标志位
// (遗留问题：第 0 位必须始终对应 ImGuiChildFlags_Borders，以便与使用 'bool border = false' 的旧 API 保持向后兼容。)
// 关于使用 AutoResizeX/AutoResizeY 标志：
// - 可与 SetNextWindowSizeConstraints() 结合使用，为每个轴设置最小/最大尺寸（参见 "Demo->Child->Auto-resize with Constraints"）。
// - 仅当子窗口处于可见边界内或刚刚出现时，才会对给定轴进行尺寸测量。
// - 这使得 BeginChild() 在超出边界（例如滚动时）可以返回 false，这样效率更高。但在被裁剪（clipped）期间，它不会更新其自动调整的尺寸。
// 虽然并不完美，但这是一种更好的默认行为，因为持续的性能提升比偶尔出现的“再次可见后重新调整大小”的闪烁更有价值。
// - 您也可以使用 ImGuiChildFlags_AlwaysAutoResize 来强制更新，即使子窗口不在视图中。
// 但请务必理解，这样做将导致 BeginChild() 永远不会返回 false，从而禁用粗略裁剪（coarse clipping）带来的性能优势。
enum ImGuiChildFlags_
{
    ImGuiChildFlags_None = 0,
    ImGuiChildFlags_Borders = 1 << 0, // 显示外边框并启用 WindowPadding。（重要：由于历史原因，此值始终 == 1 == true）
    ImGuiChildFlags_AlwaysUseWindowPadding = 1 << 1, // 即使不绘制边框也使用 style.WindowPadding 进行填充（默认情况下，无边框子窗口不进行填充，因为这样更合理）
    ImGuiChildFlags_ResizeX = 1 << 2, // 允许从右侧边界（布局方向）调整大小。启用 .ini 保存（除非在窗口标志中传递了 ImGuiWindowFlags_NoSavedSettings）
    ImGuiChildFlags_ResizeY = 1 << 3, // 允许从底边调整大小（布局方向）。
    ImGuiChildFlags_AutoResizeX = 1 << 4, // 启用自动调整宽度。请阅读上文“重要：尺寸测量”详情。
    ImGuiChildFlags_AutoResizeY = 1 << 5, // 启用自动调整高度。请阅读上文“重要：尺寸测量”详情。
    ImGuiChildFlags_AlwaysAutoResize = 1 << 6, // 与 AutoResizeX/AutoResizeY 结合使用。即使子窗口隐藏时也始终测量尺寸，始终返回 true，始终禁用裁剪优化！不推荐使用。
    ImGuiChildFlags_FrameStyle = 1 << 7, // 将子窗口样式设置为框架项目：使用 FrameBg、FrameRounding、FrameBorderSize、FramePadding，而非 ChildBg、ChildRounding、ChildBorderSize、WindowPadding。
    ImGuiChildFlags_NavFlattened = 1 << 8, // [测试版] 共享焦点范围，允许键盘/手柄导航跨越父级边界进入此子窗口，或在兄弟子窗口之间切换。


    // 已废弃的名称
#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
//ImGuiChildFlags_Border = ImGuiChildFlags_Borders, // 在 1.91.1 版本（2024 年 8 月）中为保持一致性而重命名。
#endif
};


// ImGui::PushItemFlag() 的标志
// （这些标志由所有提交的项共享）
enum ImGuiItemFlags_
{
    ImGuiItemFlags_None = 0, // (默认)
    ImGuiItemFlags_NoTabStop = 1 << 0, // false // 禁用键盘 Tab 键切换。这是 ImGuiItemFlags_NoNav 的“轻量”版本。
    ImGuiItemFlags_NoNav = 1 << 1, // false // 禁用任何形式的聚焦（键盘/手柄方向导航以及 SetKeyboardFocusHere() 调用）。
    ImGuiItemFlags_NoNavDefaultFocus = 1 << 2, // false // 禁止该项目成为默认焦点的候选对象（例如用于标题栏项目）。
    ImGuiItemFlags_ButtonRepeat = 1 << 3, // false // 任何类似按钮的行为都将启用重复模式（基于 io.KeyRepeatDelay 和 io.KeyRepeatRate 的值）。注意，你也可以在任何按钮后调用 IsItemActive() 来判断它是否正被按住。
    ImGuiItemFlags_AutoClosePopups = 1 << 4, // true // MenuItem()/Selectable() 会自动关闭其父级弹出窗口。
    ImGuiItemFlags_AllowDuplicateId = 1 << 5, // false // 允许提交与本帧已提交项目具有相同标识符的项目，且在设置了 io.ConfigDebugHighlightIdConflicts 时不会触发警告工具提示。
    ImGuiItemFlags_Disabled = 1 << 6, // false // [内部] 禁用交互。不影响视觉效果。这由 BeginDisabled()/EndDisabled() 使用，在此提供仅供通过 GetItemFlags() 读取。
};


// ImGui::InputText() 的标志
//（这些是针对单个项目的标志。在 ImGuiIO 中还有共享标志：io.ConfigInputTextCursorBlink 和 io.ConfigInputTextEnterKeepActive）
enum ImGuiInputTextFlags_
{
    // 基础过滤器（另请参阅 ImGuiInputTextFlags_CallbackCharFilter）
    ImGuiInputTextFlags_None = 0,
    ImGuiInputTextFlags_CharsDecimal = 1 << 0, // 允许输入 0123456789.+-*/
    ImGuiInputTextFlags_CharsHexadecimal = 1 << 1, // 允许输入 0123456789ABCDEFabcdef
    ImGuiInputTextFlags_CharsScientific = 1 << 2, // 允许输入 0123456789.+-*/eE（科学计数法输入）
    ImGuiInputTextFlags_CharsUppercase = 1 << 3, // 将 a..z 转换为 A..Z
    ImGuiInputTextFlags_CharsNoBlank = 1 << 4, // 过滤空格和制表符


    // 输入
    ImGuiInputTextFlags_AllowTabInput = 1 << 5, // 按下 TAB 键向文本框输入一个 '\t' 字符
    ImGuiInputTextFlags_EnterReturnsTrue = 1 << 6, // 按下回车键时返回 'true'（而非每次修改值时都返回）。请考虑改用 IsItemDeactivatedAfterEdit()！
    ImGuiInputTextFlags_EscapeClearsAll = 1 << 7, // 如果内容不为空，按下 Escape 键将清除内容，否则取消激活（与 Escape 键默认的还原行为相反）
    ImGuiInputTextFlags_CtrlEnterForNewLine = 1 << 8, // 在多行模式下，按 Enter 键确认，按 Ctrl+Enter 键换行（默认情况相反：按 Ctrl+Enter 确认，按 Enter 换行）。


    // 其他选项
    ImGuiInputTextFlags_ReadOnly = 1 << 9, // 只读模式
    ImGuiInputTextFlags_Password = 1 << 10, // 密码模式，所有字符显示为“*”，并禁用复制功能
    ImGuiInputTextFlags_AlwaysOverwrite = 1 << 11, // 覆盖模式
    ImGuiInputTextFlags_AutoSelectAll = 1 << 12, // 首次获得鼠标焦点时选中全部文本
    ImGuiInputTextFlags_ParseEmptyRefVal = 1 << 13, // 仅用于 InputFloat()、InputInt()、InputScalar() 等：将空字符串解析为零值。
    ImGuiInputTextFlags_DisplayEmptyRefVal = 1 << 14, // 仅用于 InputFloat()、InputInt()、InputScalar() 等：当值为零时不显示。通常与 ImGuiInputTextFlags_ParseEmptyRefVal 配合使用。
    ImGuiInputTextFlags_NoHorizontalScroll = 1 << 15, // 禁用水平滚动跟随光标
    ImGuiInputTextFlags_NoUndoRedo = 1 << 16, // 禁用撤销/重做。请注意，输入文本在激活状态下拥有文本数据，如果你想提供自定义的撤销/重做栈，通常需要调用如 ClearActiveID() 等函数。


    // 省略显示 / 对齐
    ImGuiInputTextFlags_ElideLeft = 1 << 17, // 当文本超出宽度时，省略左侧以确保右侧可见。适用于路径/文件名。仅限单行！


    // 回调功能
    ImGuiInputTextFlags_CallbackCompletion = 1 << 18, // 按下 TAB 键时回调（用于处理补全）
    ImGuiInputTextFlags_CallbackHistory = 1 << 19, // 按下上/下方向键时回调（用于处理历史记录）
    ImGuiInputTextFlags_CallbackAlways = 1 << 20, // 每次迭代时回调。用户代码可以查询光标位置、修改文本缓冲区。
    ImGuiInputTextFlags_CallbackCharFilter = 1 << 21, // 字符输入时的回调，用于替换或丢弃字符。修改 'EventChar' 以替换或丢弃，或在回调中返回 1 以丢弃。
    ImGuiInputTextFlags_CallbackResize = 1 << 22, // 缓冲区容量变更请求时的回调（超出 'buf_size' 参数值），允许字符串增长。当字符串需要调整大小时通知（适用于持有大小缓存的字符串类型）。你将在回调中获得一个新的 BufSize 且必须遵守它。（参见 misc/cpp/imgui_stdlib.h 获取使用示例）
    ImGuiInputTextFlags_CallbackEdit = 1 << 23, // 任何编辑操作时的回调。注意 InputText() 在编辑时已经会返回 true + 你始终可以使用 IsItemEdited()。该回调在焦点处于激活状态时操作底层缓冲区非常有用。


    // 多行自动换行 [BETA]
    // - 尚未经过充分测试。请将任何不正确的光标移动、选择行为等错误报告至 https://github.com/ocornut/imgui/issues/3237。
    // - 换行样式尚不理想。长单词/长段落（例如宽度超过总可用宽度的单词）的换行效果可能尤其不佳。
    // - 换行宽度需要始终考虑到垂直滚动条出现的可能性。
    // - 它的运行速度比常规文本框慢得多。
    // 在我 2019 年的台式机上的大致成本估算：对于 100 KB 的文本缓冲区：约 +0.3 毫秒（优化版）/ 约 +1.0 毫秒（调试版）。
    // CPU 成本大致与文本长度成正比，因此 10 KB 的缓冲区成本应该低十倍左右。
    ImGuiInputTextFlags_WordWrap = 1 << 24, // InputTextMultiline()：对过长的行进行自动换行。


    // 已废弃名称
    //ImGuiInputTextFlags_AlwaysInsertMode = ImGuiInputTextFlags_AlwaysOverwrite // [在 1.82 版本中重命名] 原名称与行为不符
};


// ImGui::TreeNodeEx(), ImGui::CollapsingHeader*() 的标志位
enum ImGuiTreeNodeFlags_
{
    ImGuiTreeNodeFlags_None = 0,
    ImGuiTreeNodeFlags_Selected = 1 << 0, // 绘制为选中状态
    ImGuiTreeNodeFlags_Framed = 1 << 1, // 绘制带有背景的框架（例如用于 CollapsingHeader）
    ImGuiTreeNodeFlags_AllowOverlap = 1 << 2, // 命中测试允许后续控件与本控件重叠
    ImGuiTreeNodeFlags_NoTreePushOnOpen = 1 << 3, // 打开时不执行 TreePush()（例如用于 CollapsingHeader） = 无额外缩进且不入栈 ID
    ImGuiTreeNodeFlags_NoAutoOpenOnLog = 1 << 4, // 当日志记录（Logging）处于活动状态时，不要自动且临时地打开节点（默认情况下，日志记录会自动打开树节点）
    ImGuiTreeNodeFlags_DefaultOpen = 1 << 5, // 默认节点为打开状态
    ImGuiTreeNodeFlags_OpenOnDoubleClick = 1 << 6, // 双击而非单击时打开（多选模式下的默认行为，除非显式设置了任何 _OpenOnXXX 行为）。两种行为可以结合使用。
    ImGuiTreeNodeFlags_OpenOnArrow = 1 << 7, // 点击箭头部分时打开（多选模式下的默认行为，除非显式设置了任何 _OpenOnXXX 行为）。两种行为可以结合使用。
    ImGuiTreeNodeFlags_Leaf = 1 << 8, // 无折叠，无箭头（作为叶节点的便利选项）。
    ImGuiTreeNodeFlags_Bullet = 1 << 9, // 显示圆点而非箭头。重要提示：如果不设置 _Leaf 标志，节点仍然可以被标记为打开/关闭状态！
    ImGuiTreeNodeFlags_FramePadding = 1 << 10, // 使用 FramePadding（即使是非框架文本节点），使文本基线与常规控件高度垂直对齐。相当于在节点前调用 AlignTextToFramePadding()。
    ImGuiTreeNodeFlags_SpanAvailWidth = 1 << 11, // 将点击区域延伸至最右侧边缘，即使没有框架。这并非默认行为，以便在不使用 AllowOverlap 模式的情况下在同一行添加其他项目。
    ImGuiTreeNodeFlags_SpanFullWidth = 1 << 12, // 将点击区域扩展至最左侧和最右侧边缘（覆盖缩进区域）。
    ImGuiTreeNodeFlags_SpanLabelWidth = 1 << 13, // 窄点击区域 + 窄悬停高亮，仅覆盖标签文本。
    ImGuiTreeNodeFlags_SpanAllColumns = 1 << 14, // 框架将跨越其容器表格的所有列（标签仍将保持在当前列中）
    ImGuiTreeNodeFlags_LabelSpanAllColumns = 1 << 15, // 标签将跨越其容器表格的所有列
    //ImGuiTreeNodeFlags_NoScrollOnOpen = 1 << 16, // 修订：待办：如果节点刚刚打开且内容不可见，则在 TreePop() 时禁用自动滚动
    ImGuiTreeNodeFlags_NavLeftJumpsToParent = 1 << 17, // 导航：左方向键返回父节点。当存在未处理的左向导航请求时，在 TreePop() 中处理。
    ImGuiTreeNodeFlags_CollapsingHeader = ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_NoAutoOpenOnLog,


    // [实验性] 绘制连接 TreeNode 层级的线条。在 GitHub issue #2920 中讨论。
    // 默认值取自 style.TreeLinesFlags。可以在 TreeNode 调用中进行覆盖。
    ImGuiTreeNodeFlags_DrawLinesNone = 1 << 18, // 不绘制线条
    ImGuiTreeNodeFlags_DrawLinesFull = 1 << 19, // 绘制到子节点的水平线。垂直线向下延伸至 TreePop() 位置：覆盖全部内容。速度较快（适用于大型树结构）。
    ImGuiTreeNodeFlags_DrawLinesToNodes = 1 << 20, // 绘制到子节点的水平线。垂直线向下延伸至最底部的子节点。速度较慢（适用于大型树结构）。


#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    ImGuiTreeNodeFlags_NavLeftJumpsBackHere = ImGuiTreeNodeFlags_NavLeftJumpsToParent, // 在 1.92.0 版本中重命名
    ImGuiTreeNodeFlags_SpanTextWidth = ImGuiTreeNodeFlags_SpanLabelWidth, // 在 1.90.7 版本中重命名
    //ImGuiTreeNodeFlags_AllowItemOverlap = ImGuiTreeNodeFlags_AllowOverlap, // 在 1.89.7 版本中重命名
#endif
};


// OpenPopup*()、BeginPopupContext*()、IsPopupOpen() 函数的标志。
// - 重要提示：如果您在 1.92.6 版本之前曾将鼠标左键用于 BeginPopupContextXXX() 辅助函数：请阅读 imgui.cpp 中 2026/01/07 (1.92.6) 的“API 重大变更”条目或 GitHub 话题 #9157。
// - 目前在这些函数中无法组合/或运算多个按钮（我们以后可能会允许这样做）。
enum ImGuiPopupFlags_
{
    ImGuiPopupFlags_None = 0,
    ImGuiPopupFlags_MouseButtonLeft = 1 << 2, // 用于 BeginPopupContext*()：在鼠标左键释放时打开。仅允许选择一个按键！
    ImGuiPopupFlags_MouseButtonRight = 2 << 2, // 用于 BeginPopupContext*()：在鼠标右键释放时打开。仅允许选择一个按键！（默认）
    ImGuiPopupFlags_MouseButtonMiddle = 3 << 2, // 用于 BeginPopupContext*()：在鼠标中键释放时打开。仅允许选择一个按键！
    ImGuiPopupFlags_NoReopen = 1 << 5, // 用于 OpenPopup*()、BeginPopupContext*()：如果弹窗已打开，则不再重新打开（不会重新定位，不会重新初始化导航）
    //ImGuiPopupFlags_NoReopenAlwaysNavInit = 1 << 6, // 用于 OpenPopup*()、BeginPopupContext*()：即使不重新打开，也聚焦并初始化导航。
    ImGuiPopupFlags_NoOpenOverExistingPopup = 1 << 7, // 用于 OpenPopup*()、BeginPopupContext*()：如果弹窗栈的同一层级已经有一个弹窗，则不打开
    ImGuiPopupFlags_NoOpenOverItems = 1 << 8, // 用于 BeginPopupContextWindow()：悬停在项目上时不返回 true，仅在悬停在空白区域时返回
    ImGuiPopupFlags_AnyPopupId = 1 << 10, // 用于 IsPopupOpen()：忽略 ImGuiID 参数，测试是否有任意弹窗打开。
    ImGuiPopupFlags_AnyPopupLevel = 1 << 11, // 用于 IsPopupOpen()：在弹窗栈的任意层级进行搜索/测试（默认仅测试当前层级）。
    ImGuiPopupFlags_AnyPopup = ImGuiPopupFlags_AnyPopupId | ImGuiPopupFlags_AnyPopupLevel,
    ImGuiPopupFlags_MouseButtonShift_ = 2, // [内部使用]
    ImGuiPopupFlags_MouseButtonMask_ = 0x0C, // [内部]
    ImGuiPopupFlags_InvalidMask_ = 0x03, // [内部] 保留旧有的第 0-1 位，用于检测是否错误地向函数传递了 1 或 2。
};


// ImGui::Selectable() 的标志
enum ImGuiSelectableFlags_
{
    ImGuiSelectableFlags_None = 0,
    ImGuiSelectableFlags_NoAutoClosePopups = 1 << 0, // 点击此项不会关闭父级弹出窗口（覆盖 ImGuiItemFlags_AutoClosePopups）
    ImGuiSelectableFlags_SpanAllColumns = 1 << 1, // 框架将跨越其容器表格的所有列（文本仍将保持在当前列中）
    ImGuiSelectableFlags_AllowDoubleClick = 1 << 2, // 在双击时也生成点击事件
    ImGuiSelectableFlags_Disabled = 1 << 3, // 不可选择，显示灰色文本
    ImGuiSelectableFlags_AllowOverlap = 1 << 4, // (开发中) 命中测试允许后续控件与此控件重叠
    ImGuiSelectableFlags_Highlight = 1 << 5, // 使项目显示为悬停状态
    ImGuiSelectableFlags_SelectOnNav = 1 << 6, // 导航移入时自动选择（除非按住 Ctrl）。在 BeginMultiSelect() 块中会自动启用。


#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    ImGuiSelectableFlags_DontClosePopups = ImGuiSelectableFlags_NoAutoClosePopups, // 在 1.91.0 版本中重命名
    //ImGuiSelectableFlags_AllowItemOverlap = ImGuiSelectableFlags_AllowOverlap, // 在 1.89.7 版本中重命名
#endif
};


// ImGui::BeginCombo() 的标志位
enum ImGuiComboFlags_
{
    ImGuiComboFlags_None = 0,
    ImGuiComboFlags_PopupAlignLeft = 1 << 0, // 默认将弹出窗口向左对齐
    ImGuiComboFlags_HeightSmall = 1 << 1, // 最大可见约 4 个项目。提示：如果你希望组合框弹出窗口具有特定尺寸，可以在调用 BeginCombo() 之前使用 SetNextWindowSizeConstraints()
    ImGuiComboFlags_HeightRegular = 1 << 2, // 最大显示约 8 个项目（默认）
    ImGuiComboFlags_HeightLarge = 1 << 3, // 最大显示约 20 个项目
    ImGuiComboFlags_HeightLargest = 1 << 4, // 尽可能多地显示符合条件的项目
    ImGuiComboFlags_NoArrowButton = 1 << 5, // 在预览框上显示，不带方形箭头按钮
    ImGuiComboFlags_NoPreview = 1 << 6, // 仅显示方形箭头按钮
    ImGuiComboFlags_WidthFitPreview = 1 << 7, // 宽度根据预览内容动态计算
    ImGuiComboFlags_HeightMask_ = ImGuiComboFlags_HeightSmall | ImGuiComboFlags_HeightRegular | ImGuiComboFlags_HeightLarge | ImGuiComboFlags_HeightLargest,
};


// ImGui::BeginTabBar() 的标志位
enum ImGuiTabBarFlags_
{
    ImGuiTabBarFlags_None = 0,
    ImGuiTabBarFlags_Reorderable = 1 << 0, // 允许手动拖动标签页以重新排序 + 新标签页将添加在列表末尾
    ImGuiTabBarFlags_AutoSelectNewTabs = 1 << 1, // 当新标签页出现时自动选择它们
    ImGuiTabBarFlags_TabListPopupButton = 1 << 2, // 禁用打开标签列表弹出窗口的按钮
    ImGuiTabBarFlags_NoCloseWithMiddleMouseButton = 1 << 3, // 禁用通过鼠标中键关闭标签（即提交时 p_open != NULL 的标签）的行为。您可以在用户端通过 if (IsItemHovered() && IsMouseClicked(2)) *p_open = false 手动处理此行为。
    ImGuiTabBarFlags_NoTabListScrollingButtons = 1 << 4, // 禁用滚动按钮（当适应策略为 ImGuiTabBarFlags_FittingPolicyScroll 时生效）
    ImGuiTabBarFlags_NoTooltip = 1 << 5, // 禁用悬停在标签上时的工具提示
    ImGuiTabBarFlags_DrawSelectedOverline = 1 << 6, // 在选中的选项卡上方绘制选中状态的横线标记


    // 适配/调整大小策略
    ImGuiTabBarFlags_FittingPolicyMixed = 1 << 7, // 当选项卡空间不足时先缩小，直到宽度达到 style.TabMinWidthShrink，然后启用滚动按钮。
    ImGuiTabBarFlags_FittingPolicyShrink = 1 << 8, // 当选项卡空间不足时缩小选项卡宽度
    ImGuiTabBarFlags_FittingPolicyScroll = 1 << 9, // 当标签页超出显示范围时启用滚动按钮
    ImGuiTabBarFlags_FittingPolicyMask_ = ImGuiTabBarFlags_FittingPolicyMixed | ImGuiTabBarFlags_FittingPolicyShrink | ImGuiTabBarFlags_FittingPolicyScroll,
    ImGuiTabBarFlags_FittingPolicyDefault_ = ImGuiTabBarFlags_FittingPolicyMixed,


#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    ImGuiTabBarFlags_FittingPolicyResizeDown = ImGuiTabBarFlags_FittingPolicyShrink, // 在 1.92.2 版本中重命名
#endif
};


// ImGui::BeginTabItem() 的标志
enum ImGuiTabItemFlags_
{
    ImGuiTabItemFlags_None = 0,
    ImGuiTabItemFlags_UnsavedDocument = 1 << 0, // 在标题旁显示一个圆点 + 设置 ImGuiTabItemFlags_NoAssumedClosure。
    ImGuiTabItemFlags_SetSelected = 1 << 1, // 触发标志，用于在调用 BeginTabItem() 时通过程序使该选项卡处于选中状态。
    ImGuiTabItemFlags_NoCloseWithMiddleMouseButton = 1 << 2, // 禁用通过鼠标中键关闭选项卡（即那些以 p_open != NULL 提交的选项卡）的行为。您可以在用户端通过 if (IsItemHovered() && IsMouseClicked(2)) *p_open = false 手动处理此行为。
    ImGuiTabItemFlags_NoPushId = 1 << 3, // 不在 BeginTabItem()/EndTabItem() 中调用 PushID()/PopID()
    ImGuiTabItemFlags_NoTooltip = 1 << 4, // 禁用该选项卡的工具提示
    ImGuiTabItemFlags_NoReorder = 1 << 5, // 禁止重新排序该选项卡，或禁止其他选项卡跨越该选项卡
    ImGuiTabItemFlags_Leading = 1 << 6, // 强制将选项卡置于选项卡栏左侧（位于选项卡列表弹出按钮之后）
    ImGuiTabItemFlags_Trailing = 1 << 7, // 强制将选项卡置于选项卡栏右侧（位于滚动按钮之前）
    ImGuiTabItemFlags_NoAssumedClosure = 1 << 8, // 尝试关闭时选项卡将被选中 + 不会立即假定关闭（将等待用户停止提交该选项卡）。否则，按下 X 时即假定关闭，因此如果你继续提交，该选项卡可能会重新出现在选项卡栏末尾。
};


// ImGui::IsWindowFocused() 的标志
enum ImGuiFocusedFlags_
{
    ImGuiFocusedFlags_None = 0,
    ImGuiFocusedFlags_ChildWindows = 1 << 0, // 如果该窗口的任何子窗口获得焦点，则返回 true
    ImGuiFocusedFlags_RootWindow = 1 << 1, // 从根窗口（当前层级中最顶层的父窗口）开始测试
    ImGuiFocusedFlags_AnyWindow = 1 << 2, // 如果任何窗口获得焦点，则返回 true。重要提示：如果你试图据此判断如何分发底层输入，请勿使用此标志！请改用 'io.WantCaptureMouse'！请阅读 FAQ！
    ImGuiFocusedFlags_NoPopupHierarchy = 1 << 3, // 不考虑弹出窗口层级（不将弹出窗口的触发者视为弹出窗口的父级）（与 _ChildWindows 或 _RootWindow 配合使用时）
    //ImGuiFocusedFlags_DockHierarchy = 1 << 4, // 考虑停靠层级（将停靠空间宿主视为停靠窗口的父级）（与 _ChildWindows 或 _RootWindow 配合使用时）
    ImGuiFocusedFlags_RootAndChildWindows = ImGuiFocusedFlags_RootWindow | ImGuiFocusedFlags_ChildWindows,
};


// ImGui::IsItemHovered(), ImGui::IsWindowHovered() 的标志位
// 注意：如果你想检查鼠标输入应该分发给 Dear ImGui 还是你的应用程序，请改用 'io.WantCaptureMouse'！请阅读 FAQ！
// 注意：带有 ImGuiWindowFlags_NoInputs 标志的窗口会被 IsWindowHovered() 调用忽略。
enum ImGuiHoveredFlags_
{
    ImGuiHoveredFlags_None = 0, // 如果直接位于项目/窗口上方，且未被其他窗口遮挡，也未被其下方阻塞输入的活动弹出窗口或模态窗口遮挡，则返回 true。
    ImGuiHoveredFlags_ChildWindows = 1 << 0, // 仅用于 IsWindowHovered()：如果该窗口的任何子窗口被悬停，则返回 true
    ImGuiHoveredFlags_RootWindow = 1 << 1, // 仅用于 IsWindowHovered()：从根窗口（当前层级中最顶层的父窗口）开始测试
    ImGuiHoveredFlags_AnyWindow = 1 << 2, // 仅用于 IsWindowHovered()：如果任何窗口被悬停则返回 true
    ImGuiHoveredFlags_NoPopupHierarchy = 1 << 3, // 仅用于 IsWindowHovered()：不考虑弹出窗口层级（不将弹出窗口的触发者视为弹出窗口的父级）（与 _ChildWindows 或 _RootWindow 配合使用时）
    //ImGuiHoveredFlags_DockHierarchy = 1 << 4, // 仅用于 IsWindowHovered()：考虑停靠层级（将停靠空间宿主视为停靠窗口的父级）（与 _ChildWindows 或 _RootWindow 配合使用时）
    ImGuiHoveredFlags_AllowWhenBlockedByPopup = 1 << 5, // 即使弹窗通常会阻碍对此项目/窗口的访问，也返回 true
    //ImGuiHoveredFlags_AllowWhenBlockedByModal = 1 << 6, // 即使模态弹窗通常会阻碍对此项目/窗口的访问，也返回 true。修订-待办：目前尚不可用。
    ImGuiHoveredFlags_AllowWhenBlockedByActiveItem = 1 << 7, // 即使有活动项目（Active Item）阻碍对此项目/窗口的访问，也返回 true。适用于拖放模式。
    ImGuiHoveredFlags_AllowWhenOverlappedByItem = 1 << 8, // 仅限 IsItemHovered()：即使该项目使用了 AllowOverlap 模式且被另一个可悬停项目重叠，也返回 true。
    ImGuiHoveredFlags_AllowWhenOverlappedByWindow = 1 << 9, // 仅限 IsItemHovered()：即使位置被另一个窗口遮挡或重叠，也返回 true。
    ImGuiHoveredFlags_AllowWhenDisabled = 1 << 10, // 仅限 IsItemHovered()：即使项目处于禁用状态也返回 true
    ImGuiHoveredFlags_NoNavOverride = 1 << 11, // 仅限 IsItemHovered()：激活时禁用键盘/手柄导航状态，始终查询鼠标
    ImGuiHoveredFlags_AllowWhenOverlapped = ImGuiHoveredFlags_AllowWhenOverlappedByItem | ImGuiHoveredFlags_AllowWhenOverlappedByWindow,
    ImGuiHoveredFlags_RectOnly = ImGuiHoveredFlags_AllowWhenBlockedByPopup | ImGuiHoveredFlags_AllowWhenBlockedByActiveItem | ImGuiHoveredFlags_AllowWhenOverlapped,
    ImGuiHoveredFlags_RootAndChildWindows = ImGuiHoveredFlags_RootWindow | ImGuiHoveredFlags_ChildWindows,


    // 工具提示模式
    // - 通常用于 IsItemHovered() + SetTooltip() 序列。
    // - 这是一个快捷方式，用于从 'style.HoverFlagsForTooltipMouse' 或 'style.HoverFlagsForTooltipNav' 中获取标志，您可以在其中重新配置所需的行为。
    // 例如：'HoverFlagsForTooltipMouse' 默认值为 'ImGuiHoveredFlags_Stationary | ImGuiHoveredFlags_DelayShort | ImGuiHoveredFlags_AllowWhenDisabled'。
    // - 对于需要提供工具提示的频繁操作或悬停项，您可能希望使用 ImGuiHoveredFlags_ForTooltip（静止 + 延迟），以免工具提示显示过于频繁。
    // - 对于主要目的是被悬停的项、示能性（affordance）较低的项，或在一致性较低的应用中，建议不设延迟或使用较短的延迟。
    ImGuiHoveredFlags_ForTooltip = 1 << 12, // 使用 IsItemHovered() + SetTooltip() 序列时的标准标志快捷方式。


    // (高级) 鼠标悬停延迟。
    // - 通常你可以使用 ImGuiHoveredFlags_ForTooltip 来使用应用程序标准化的标志。
    // - 如果你需要特定的覆盖设置，请使用这些。
    ImGuiHoveredFlags_Stationary = 1 << 13, // 要求鼠标在 style.HoverStationaryDelay（约 0.15 秒）内保持静止状态“至少一次”。在此之后，可以在同一项目/窗口上移动。使用静止测试往往可以减少对长时间延迟的需求。
    ImGuiHoveredFlags_DelayNone = 1 << 14, // 仅限 IsItemHovered()：立即返回 true（默认值）。由于这是默认设置，通常可以忽略此项。
    ImGuiHoveredFlags_DelayShort = 1 << 15, // 仅限 IsItemHovered()：在 style.HoverDelayShort 耗尽（约 0.15 秒）后返回 true（在项目间共享）+ 要求鼠标在 style.HoverStationaryDelay 内保持静止（每个项目一次）。
    ImGuiHoveredFlags_DelayNormal = 1 << 16, // 仅限 IsItemHovered()：在 style.HoverDelayNormal 耗尽（约 0.40 秒）后返回 true（在项目间共享）+ 要求鼠标在 style.HoverStationaryDelay 内保持静止（每个项目一次）。
    ImGuiHoveredFlags_NoSharedDelay = 1 << 17, // 仅用于 IsItemHovered()：禁用共享延迟系统。在该系统下，从一个项目移动到下一个项目时会短时间保留前一个计时器（这是具有长延迟工具提示的标准行为）
};


// 用于 ImGui::BeginDragDropSource(), ImGui::AcceptDragDropPayload() 的标志
enum ImGuiDragDropFlags_
{
    ImGuiDragDropFlags_None = 0,
    // BeginDragDropSource() 标志
    ImGuiDragDropFlags_SourceNoPreviewTooltip = 1 << 0, // 禁用预览工具提示。默认情况下，成功调用 BeginDragDropSource 会打开一个工具提示，以便你可以显示源内容的预览或描述。此标志会禁用该行为。
    ImGuiDragDropFlags_SourceNoDisableHover = 1 << 1, // 默认情况下，拖动时我们会清除数据，使 IsItemHovered() 返回 false，以避免后续用户代码提交工具提示。此标志会禁用该行为，以便你仍可以对源项目调用 IsItemHovered()。
    ImGuiDragDropFlags_SourceNoHoldToOpenOthers = 1 << 2, // 禁用以下行为：在拖动源项目时，通过悬停在树节点或折叠标题上来将其打开。
    ImGuiDragDropFlags_SourceAllowNullID = 1 << 3, // 允许没有唯一标识符的项目（如 Text()、Image()）通过基于其窗口相对位置生成临时标识符来作为拖动源。这在 dear imgui 生态系统中极其罕见，因此我们将其显式化。
    ImGuiDragDropFlags_SourceExtern = 1 << 4, // 外部源（来自 dear imgui 外部），不会尝试读取当前项目/窗口信息。将始终返回 true。同时只能激活一个外部源。
    ImGuiDragDropFlags_PayloadAutoExpire = 1 << 5, // 如果源停止提交，则自动使有效载荷过期（否则有效载荷在拖动过程中会一直持久存在）
    ImGuiDragDropFlags_PayloadNoCrossContext = 1 << 6, // 提示指定有效载荷不得复制到当前 dear imgui 上下文之外。
    ImGuiDragDropFlags_PayloadNoCrossProcess = 1 << 7, // 提示指定有效负载不得复制到当前进程之外。
    // AcceptDragDropPayload() 标志
    ImGuiDragDropFlags_AcceptBeforeDelivery = 1 << 10, // AcceptDragDropPayload() 即使在鼠标按键释放前也会返回 true。随后你可以调用 IsDelivery() 来测试有效负载是否需要交付。
    ImGuiDragDropFlags_AcceptNoDrawDefaultRect = 1 << 11, // 悬停在目标上时不要绘制默认的高亮矩形。
    ImGuiDragDropFlags_AcceptNoPreviewTooltip = 1 << 12, // 请求在 BeginDragDropTarget 端隐藏来自 BeginDragDropSource 的预览工具提示。
    ImGuiDragDropFlags_AcceptDrawAsHovered = 1 << 13, // 接收物品时将渲染为悬停状态。适用于例如用作放置目标的 Button()。
    ImGuiDragDropFlags_AcceptPeekOnly = ImGuiDragDropFlags_AcceptBeforeDelivery | ImGuiDragDropFlags_AcceptNoDrawDefaultRect, // 用于在实际交付前提前预览并检查有效载荷。


#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    ImGuiDragDropFlags_SourceAutoExpirePayload = ImGuiDragDropFlags_PayloadAutoExpire, // 在 1.90.9 版本中重命名
#endif
};


// 标准拖放载荷类型。你可以使用短字符串定义自己的载荷类型。以 '_' 开头的类型由 Dear ImGui 定义。
#define IMGUI_PAYLOAD_TYPE_COLOR_3F "_COL3F" // float[3]: 颜色的标准类型，不含 alpha 通道。用户代码可以使用此类型。
#define IMGUI_PAYLOAD_TYPE_COLOR_4F "_COL4F" // float[4]: 颜色的标准类型。用户代码可以使用此类型。


// 基本数据类型
enum ImGuiDataType_
{
    ImGuiDataType_S8, // 有符号字符型 / 字符型（在使用合理的编译器时）
    ImGuiDataType_U8, // 无符号字符型
    ImGuiDataType_S16, // 有符号短整型 (short)
    ImGuiDataType_U16, // 无符号短整型 (unsigned short)
    ImGuiDataType_S32, // 整型 (int)
    ImGuiDataType_U32, // 无符号整型 (unsigned int)
    ImGuiDataType_S64, // long long / __int64
    ImGuiDataType_U64, // unsigned long long / unsigned __int64
    ImGuiDataType_Float, // float
    ImGuiDataType_Double, // double
    ImGuiDataType_Bool, // 布尔型（为方便用户提供，标量控件不支持此类型）
    ImGuiDataType_String, // 字符串型（为方便用户提供，标量控件不支持此类型）
    ImGuiDataType_COUNT
};


// 基本方向
enum ImGuiDir : int
{
    ImGuiDir_None = -1,
    ImGuiDir_Left = 0,
    ImGuiDir_Right = 1,
    ImGuiDir_Up = 2,
    ImGuiDir_Down = 3,
    ImGuiDir_COUNT
};


// 排序方向
enum ImGuiSortDirection : ImU8
{
    ImGuiSortDirection_None = 0,
    ImGuiSortDirection_Ascending = 1, // 升序 = 0->9, A->Z 等。
    ImGuiSortDirection_Descending = 2 // 降序 = 9->0, Z->A 等。
};


// 按键标识符（ImGuiKey_XXX 或 ImGuiMod_XXX 值）：可以代表键盘、鼠标和手柄的值。
// 所有命名的按键值均 >= 512。0 到 511 的按键值目前处于未使用状态，它们曾是旧版本的原生/不透明键值（版本 < 1.87）。
// 对旧版按键的支持已在 1.91.5 版本中完全移除。
// 阅读关于 1.87+ 版本过渡的详细信息：https://github.com/ocornut/imgui/issues/4921
// 请注意，“按键”（Keys）是指物理按键，与输入“字符”（Characters）并非同一概念，后者通过 io.AddInputCharacter() 提交。
// 键盘按键枚举值是根据标准美式键盘上的按键命名的，在其他类型的键盘上，报告的按键可能与键帽上的标注不符。
enum ImGuiKey : int
{
    // 键盘
    ImGuiKey_None = 0,
    ImGuiKey_NamedKey_BEGIN = 512, // 第一个有效的键值（除 0 以外）


    ImGuiKey_Tab = 512, // == ImGuiKey_NamedKey_BEGIN
    ImGuiKey_LeftArrow,
    ImGuiKey_RightArrow,
    ImGuiKey_UpArrow,
    ImGuiKey_DownArrow,
    ImGuiKey_PageUp,
    ImGuiKey_PageDown,
    ImGuiKey_Home,
    ImGuiKey_End,
    ImGuiKey_Insert,
    ImGuiKey_Delete,
    ImGuiKey_Backspace,
    ImGuiKey_Space,
    ImGuiKey_Enter,
    ImGuiKey_Escape,
    ImGuiKey_LeftCtrl, ImGuiKey_LeftShift, ImGuiKey_LeftAlt, ImGuiKey_LeftSuper, // 另请参阅下方的 ImGuiMod_Ctrl, ImGuiMod_Shift, ImGuiMod_Alt, ImGuiMod_Super！
    ImGuiKey_RightCtrl, ImGuiKey_RightShift, ImGuiKey_RightAlt, ImGuiKey_RightSuper,
    ImGuiKey_Menu,
    ImGuiKey_0, ImGuiKey_1, ImGuiKey_2, ImGuiKey_3, ImGuiKey_4, ImGuiKey_5, ImGuiKey_6, ImGuiKey_7, ImGuiKey_8, ImGuiKey_9,
    ImGuiKey_A, ImGuiKey_B, ImGuiKey_C, ImGuiKey_D, ImGuiKey_E, ImGuiKey_F, ImGuiKey_G, ImGuiKey_H, ImGuiKey_I, ImGuiKey_J,
    ImGuiKey_K, ImGuiKey_L, ImGuiKey_M, ImGuiKey_N, ImGuiKey_O, ImGuiKey_P, ImGuiKey_Q, ImGuiKey_R, ImGuiKey_S, ImGuiKey_T,
    ImGuiKey_U, ImGuiKey_V, ImGuiKey_W, ImGuiKey_X, ImGuiKey_Y, ImGuiKey_Z,
    ImGuiKey_F1, ImGuiKey_F2, ImGuiKey_F3, ImGuiKey_F4, ImGuiKey_F5, ImGuiKey_F6,
    ImGuiKey_F7, ImGuiKey_F8, ImGuiKey_F9, ImGuiKey_F10, ImGuiKey_F11, ImGuiKey_F12,
    ImGuiKey_F13, ImGuiKey_F14, ImGuiKey_F15, ImGuiKey_F16, ImGuiKey_F17, ImGuiKey_F18,
    ImGuiKey_F19, ImGuiKey_F20, ImGuiKey_F21, ImGuiKey_F22, ImGuiKey_F23, ImGuiKey_F24,
    ImGuiKey_Apostrophe, // '
    ImGuiKey_Comma, // ,
    ImGuiKey_Minus, // -
    ImGuiKey_Period, // .
    ImGuiKey_Slash, // /
    ImGuiKey_Semicolon, // ;
    ImGuiKey_Equal, // =
    ImGuiKey_LeftBracket, // [
    ImGuiKey_Backslash, // \ (此文本用于防止反斜杠引起的多行注释)
    ImGuiKey_RightBracket, // ]
    ImGuiKey_GraveAccent, // `
    ImGuiKey_CapsLock,
    ImGuiKey_ScrollLock,
    ImGuiKey_NumLock,
    ImGuiKey_PrintScreen,
    ImGuiKey_Pause,
    ImGuiKey_Keypad0, ImGuiKey_Keypad1, ImGuiKey_Keypad2, ImGuiKey_Keypad3, ImGuiKey_Keypad4,
    ImGuiKey_Keypad5, ImGuiKey_Keypad6, ImGuiKey_Keypad7, ImGuiKey_Keypad8, ImGuiKey_Keypad9,
    ImGuiKey_KeypadDecimal,
    ImGuiKey_KeypadDivide,
    ImGuiKey_KeypadMultiply,
    ImGuiKey_KeypadSubtract,
    ImGuiKey_KeypadAdd,
    ImGuiKey_KeypadEnter,
    ImGuiKey_KeypadEqual,
    ImGuiKey_AppBack, // 某些键盘/鼠标上可用。通常被称为“浏览器后退”
    ImGuiKey_AppForward,
    ImGuiKey_Oem102, // 非美式反斜杠。


    // 手柄
    // (模拟值为 0.0f 至 1.0f)
    // (请在 http://dearimgui.com/controls_sheets 下载控制器映射的 PNG/PSD 文件)
    // // Xbox | Switch | PLAYSTA. | -> 动作
    ImGuiKey_GamepadStart, // 菜单 | + | 选项 |
    ImGuiKey_GamepadBack, // 视图 | - | 分享 |
    ImGuiKey_GamepadFaceLeft, // X | Y | 正方形 | 点按：切换菜单。按住：窗口模式（聚焦/移动/调整窗口大小）
    ImGuiKey_GamepadFaceRight, // B | A | 圆圈 | 取消 / 关闭 / 退出
    ImGuiKey_GamepadFaceUp, // Y | X | 三角键 | 文本输入 / 屏幕键盘
    ImGuiKey_GamepadFaceDown, // A | B | 叉键 | 激活 / 打开 / 切换 / 调整
    ImGuiKey_GamepadDpadLeft, // 方向键左 | " | " | 移动 / 调整 / 调整窗口大小（在窗口模式下）
    ImGuiKey_GamepadDpadRight, // 方向键右 | " | " | 移动 / 调整 / 调整窗口大小（在窗口模式下）
    ImGuiKey_GamepadDpadUp, // 方向键上 | " | " | 移动 / 调整 / 缩放窗口（在窗口模式下）
    ImGuiKey_GamepadDpadDown, // 方向键下 | " | " | 移动 / 调整 / 缩放窗口（在窗口模式下）
    ImGuiKey_GamepadL1, // 左肩键 | L | L1 | 慢速调整 / 聚焦上一个（在窗口模式下）
    ImGuiKey_GamepadR1, // 右肩键 | R | R1 | 快速调整 / 聚焦下一个（在窗口模式下）
    ImGuiKey_GamepadL2, // 左扳机键 | ZL | L2 | [模拟量]
    ImGuiKey_GamepadR2, // 右扳机键 | ZR | R2 | [模拟量]
    ImGuiKey_GamepadL3, // 左摇杆键 | L3 | L3 |
    ImGuiKey_GamepadR3, // 右摇杆键 | R3 | R3 |
    ImGuiKey_GamepadLStickLeft, // | | | [模拟信号] 移动窗口（在窗口管理模式下）
    ImGuiKey_GamepadLStickRight, // | | | [模拟信号] 移动窗口（在窗口管理模式下）
    ImGuiKey_GamepadLStickUp, // | | | [模拟信号] 移动窗口（在窗口管理模式下）
    ImGuiKey_GamepadLStickDown, // | | | [模拟信号] 移动窗口（在窗口管理模式下）
    ImGuiKey_GamepadRStickLeft, // | | | [模拟信号]
    ImGuiKey_GamepadRStickRight, // | | | [模拟信号]
    ImGuiKey_GamepadRStickUp, // | | | [模拟信号]
    ImGuiKey_GamepadRStickDown, // | | | [模拟信号]


    // 别名：鼠标按钮（通过 AddMouseButtonEvent() 调用自动提交）
    // - 这是对写入 io.MouseDown[]、io.MouseWheel 中数据的镜像，其格式允许通过标准按键 API 进行访问。
    ImGuiKey_MouseLeft, ImGuiKey_MouseRight, ImGuiKey_MouseMiddle, ImGuiKey_MouseX1, ImGuiKey_MouseX2, ImGuiKey_MouseWheelX, ImGuiKey_MouseWheelY,


    // [内部] 预留用于存储修饰键状态
    ImGuiKey_ReservedForModCtrl, ImGuiKey_ReservedForModShift, ImGuiKey_ReservedForModAlt, ImGuiKey_ReservedForModSuper,


    // [内部] 如果你需要遍历所有按键（例如用于输入映射器），可以使用 ImGuiKey_NamedKey_BEGIN..ImGuiKey_NamedKey_END。
    ImGuiKey_NamedKey_END,
    ImGuiKey_NamedKey_COUNT = ImGuiKey_NamedKey_END - ImGuiKey_NamedKey_BEGIN,


    // 键盘修饰键（由后端通过 AddKeyEvent() 调用显式提交）
    // - 任何接受 ImGuiKeyChord 参数的函数都可以将这些修饰键与常规键进行按位或运算，例如 Shortcut(ImGuiMod_Ctrl | ImGuiKey_S)。
    // - 为了方便起见，这些键会被写回 io.KeyCtrl、io.KeyShift、io.KeyAlt、io.KeySuper，
    // 但也可以通过标准的按键 API 进行访问，例如 IsKeyPressed()、IsKeyReleased()、查询持续时间等。
    // - 轮询每个按键的代码（例如用于检测按键以进行输入映射的界面）可能希望忽略这些
    // 并且更倾向于使用真实的按键（例如使用 ImGuiKey_LeftCtrl、ImGuiKey_RightCtrl 而不是 ImGuiMod_Ctrl）。
    // - 从理论上讲，键盘修饰键的值应该大致等同于对应的左/右键的逻辑或（OR）运算结果。
    // 在实践中：情况很复杂；修饰键通常来自不同的源。键盘布局、输入法（IME）、粘滞键以及
    // 后端往往会产生干扰并破坏这种等效性。更安全的决定是将这种歧义性传递给最终用户……
    // - 在 macOS 上，我们在调用 io.AddKeyEvent() 时交换 Cmd(Super) 和 Ctrl 键。
    ImGuiMod_None = 0,
    ImGuiMod_Ctrl = 1 << 12, // Ctrl (非 macOS), Cmd (macOS)
    ImGuiMod_Shift = 1 << 13, // Shift
    ImGuiMod_Alt = 1 << 14, // Option/Menu
    ImGuiMod_Super = 1 << 15, // Windows/Super (非 macOS), Ctrl (macOS)
    ImGuiMod_Mask_ = 0xF000, // 4 位掩码


#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    ImGuiKey_COUNT = ImGuiKey_NamedKey_END, // 在 1.91.5 版本中弃用，因为该常量具有误导性（因为命名键不再从 0 开始）
    ImGuiMod_Shortcut = ImGuiMod_Ctrl, // 在 1.90.7 版本中移除，现在您可以直接使用 ImGuiMod_Ctrl
    //ImGuiKey_ModCtrl = ImGuiMod_Ctrl, ImGuiKey_ModShift = ImGuiMod_Shift, ImGuiKey_ModAlt = ImGuiMod_Alt, ImGuiKey_ModSuper = ImGuiMod_Super, // 在 1.89 版本中重命名
    //ImGuiKey_KeyPadEnter = ImGuiKey_KeypadEnter, // 在 1.87 版本中重命名
#endif
};


// 用于 Shortcut()、SetNextItemShortcut() 的标志，
// （以及即将推出的 IsKeyPressed()、IsMouseClicked()、Shortcut()、SetKeyOwner()、SetItemKeyOwner() 的扩展版本，目前仍在 imgui_internal.h 中）
// 不要与 ImGuiInputTextFlags 混淆！（后者用于 ImGui::InputText() 函数）
enum ImGuiInputFlags_
{
    ImGuiInputFlags_None = 0,
    ImGuiInputFlags_Repeat = 1 << 0, // 启用重复。在连续重复时返回 true。旧版 IsKeyPressed() 的默认行为。非旧版 IsMouseClicked() 的默认行为。必须等于 1。


    // 用于 Shortcut()、SetNextItemShortcut() 的标志
    // - 路由策略：RouteGlobal+OverActive >> RouteActive 或 RouteFocused（如果所有者是活动项）>> RouteGlobal+OverFocused >> RouteFocused（如果在聚焦窗口栈中）>> RouteGlobal。
    // - 默认策略为 RouteFocused。在所有可用策略中只能选择 1 种。
    ImGuiInputFlags_RouteActive = 1 << 10, // 仅路由至活动项（Active item）。
    ImGuiInputFlags_RouteFocused = 1 << 11, // 路由至聚焦栈中的窗口（默认）。处于最深层的聚焦窗口接收输入。活动项的输入优先级高于最深层的聚焦窗口。
    ImGuiInputFlags_RouteGlobal = 1 << 12, // 全局路由（除非有聚焦窗口或活动项注册了该路由）。
    ImGuiInputFlags_RouteAlways = 1 << 13, // 不注册路由，直接轮询按键。
    // - 路由选项
    ImGuiInputFlags_RouteOverFocused = 1 << 14, // 选项：全局路由：优先级高于聚焦路由（除非聚焦路由中有活动项）。
    ImGuiInputFlags_RouteOverActive = 1 << 15, // 选项：全局路由：优先级高于活动项。你通常不需要使用此项：它会干扰所有活动项，例如 InputText 注册的 Ctrl+A 将被此项覆盖。可能无法完全生效，因为用户/内部代码通常假设在活动状态下始终可以访问按键。
    ImGuiInputFlags_RouteUnlessBgFocused = 1 << 16, // 选项：全局路由：如果底层背景/空白区域处于聚焦状态（即没有 Dear ImGui 窗口处于聚焦状态），则不应用此路由。适用于覆盖层（overlay）应用程序。
    ImGuiInputFlags_RouteFromRootWindow = 1 << 17, // 选项：从根窗口而非当前窗口的角度评估路由。


    // SetNextItemShortcut() 的标志
    ImGuiInputFlags_Tooltip = 1 << 18, // 悬停在项目上时自动显示工具提示 [测试版] 尚不确定正确的 API 设计（加入/退出机制）
};


// 存储在 io.ConfigFlags 中的配置标志。由用户/应用程序设置。
enum ImGuiConfigFlags_
{
    ImGuiConfigFlags_None = 0,
    ImGuiConfigFlags_NavEnableKeyboard = 1 << 0, // 主键盘导航启用标志。启用完整的 Tab 键切换 + 方向键 + 空格/回车键激活功能。
    ImGuiConfigFlags_NavEnableGamepad = 1 << 1, // 主手柄导航启用标志。后端还需设置 ImGuiBackendFlags_HasGamepad。
    ImGuiConfigFlags_NoMouse = 1 << 4, // 指示 Dear ImGui 禁用鼠标输入和交互。
    ImGuiConfigFlags_NoMouseCursorChange = 1 << 5, // 指示后端不要更改鼠标光标的形状和可见性。如果后端的游标更改干扰了你自己的设置，且你不想使用 SetMouseCursor() 来更改鼠标光标，请使用此标志。你可能需要通过自行读取 GetMouseCursor() 来响应来自 ImGui 的请求。
    ImGuiConfigFlags_NoKeyboard = 1 << 6, // 指示 Dear ImGui 禁用键盘输入和交互。这是通过忽略键盘事件并清除现有状态来实现的。


    // 用户存储（允许你的后端/引擎与可能在多个项目之间共享的代码进行通信。这些标志不被 Dear ImGui 核心库使用）
    ImGuiConfigFlags_IsSRGB = 1 << 20, // 应用程序支持 SRGB。
    ImGuiConfigFlags_IsTouchScreen = 1 << 21, // 应用程序正在使用触摸屏而非鼠标。


#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    ImGuiConfigFlags_NavEnableSetMousePos = 1 << 2, // [在 1.91.4 中移动/重命名] -> 请使用 bool io.ConfigNavMoveSetMousePos
    ImGuiConfigFlags_NavNoCaptureKeyboard = 1 << 3, // [在 1.91.4 中移动/重命名] -> 请使用 bool io.ConfigNavCaptureKeyboard
#endif
};


// 存储在 io.BackendFlags 中的后端能力标志。由 imgui_impl_xxx 或自定义后端设置。
enum ImGuiBackendFlags_
{
    ImGuiBackendFlags_None = 0,
    ImGuiBackendFlags_HasGamepad = 1 << 0, // 后端平台支持手柄且当前已连接一个手柄。
    ImGuiBackendFlags_HasMouseCursors = 1 << 1, // 后端平台支持根据 GetMouseCursor() 的返回值来更改操作系统光标形状。
    ImGuiBackendFlags_HasSetMousePos = 1 << 2, // 后端平台支持 io.WantSetMousePos 请求以重新定位操作系统鼠标位置（仅在设置了 io.ConfigNavMoveSetMousePos 时使用）。
    ImGuiBackendFlags_RendererHasVtxOffset = 1 << 3, // 后端渲染器支持 ImDrawCmd::VtxOffset。这使得在仍使用 16 位索引的情况下能够输出大型网格（64K+ 顶点）。
    ImGuiBackendFlags_RendererHasTextures = 1 << 4, // 后端渲染器支持 ImTextureData 请求以创建/更新/销毁纹理。这启用了增量纹理更新和纹理重新加载。有关如何升级自定义后端的说明，请参阅 https://github.com/ocornut/imgui/blob/master/docs/BACKENDS.md。
};


// PushStyleColor() / PopStyleColor() 的枚举
enum ImGuiCol_
{
    ImGuiCol_Text,
    ImGuiCol_TextDisabled,
    ImGuiCol_WindowBg, // 普通窗口的背景
    ImGuiCol_ChildBg, // 子窗口的背景
    ImGuiCol_PopupBg, // 弹窗、菜单、工具提示窗口的背景
    ImGuiCol_Border,
    ImGuiCol_BorderShadow,
    ImGuiCol_FrameBg, // 复选框、单选按钮、图表、滑块、文本输入的背景
    ImGuiCol_FrameBgHovered,
    ImGuiCol_FrameBgActive,
    ImGuiCol_TitleBg, // 标题栏
    ImGuiCol_TitleBgActive, // 聚焦时的标题栏
    ImGuiCol_TitleBgCollapsed, // 折叠时的标题栏
    ImGuiCol_MenuBarBg,
    ImGuiCol_ScrollbarBg,
    ImGuiCol_ScrollbarGrab,
    ImGuiCol_ScrollbarGrabHovered,
    ImGuiCol_ScrollbarGrabActive,
    ImGuiCol_CheckMark, // 复选框（Checkbox）的勾选标记和单选按钮（RadioButton）的圆点
    ImGuiCol_SliderGrab,
    ImGuiCol_SliderGrabActive,
    ImGuiCol_Button,
    ImGuiCol_ButtonHovered,
    ImGuiCol_ButtonActive,
    ImGuiCol_Header, // Header* 颜色用于 CollapsingHeader、TreeNode、Selectable、MenuItem
    ImGuiCol_HeaderHovered,
    ImGuiCol_HeaderActive,
    ImGuiCol_Separator,
    ImGuiCol_SeparatorHovered,
    ImGuiCol_SeparatorActive,
    ImGuiCol_ResizeGrip, // 窗口右下角和左下角的调整大小手柄。
    ImGuiCol_ResizeGripHovered,
    ImGuiCol_ResizeGripActive,
    ImGuiCol_InputTextCursor, // InputText 光标/插入符
    ImGuiCol_TabHovered, // 标签页背景（悬停时）
    ImGuiCol_Tab, // 标签页背景（当标签栏获得焦点且该标签未被选中时）
    ImGuiCol_TabSelected, // 标签页背景（当标签栏获得焦点且该标签被选中时）
    ImGuiCol_TabSelectedOverline, // 选项卡水平上划线，当选项卡栏获得焦点且选项卡被选中时
    ImGuiCol_TabDimmed, // 选项卡背景，当选项卡栏失去焦点且选项卡未选中时
    ImGuiCol_TabDimmedSelected, // 选项卡背景，当选项卡栏失去焦点且选项卡被选中时
    ImGuiCol_TabDimmedSelectedOverline,// ..水平上划线，当选项卡栏失去焦点且选项卡被选中时
    ImGuiCol_PlotLines,
    ImGuiCol_PlotLinesHovered,
    ImGuiCol_PlotHistogram,
    ImGuiCol_PlotHistogramHovered,
    ImGuiCol_TableHeaderBg, // 表格标题背景
    ImGuiCol_TableBorderStrong, // 表格外部和标题边框（此处建议使用 Alpha=1.0）
    ImGuiCol_TableBorderLight, // 表格内部边框（此处建议使用 Alpha=1.0）
    ImGuiCol_TableRowBg, // 表格行背景（偶数行）
    ImGuiCol_TableRowBgAlt, // 表格行背景（奇数行）
    ImGuiCol_TextLink, // 超链接颜色
    ImGuiCol_TextSelectedBg, // InputText 中选中文本的背景色
    ImGuiCol_TreeLines, // 使用 ImGuiTreeNodeFlags_DrawLines 时的树节点层级轮廓线
    ImGuiCol_DragDropTarget, // 放置目标的高亮矩形边框
    ImGuiCol_DragDropTargetBg, // 放置目标的高亮矩形背景
    ImGuiCol_UnsavedMarker, // 未保存文档标记（显示在窗口标题和标签页）
    ImGuiCol_NavCursor, // 键盘/手柄导航光标/矩形可见时的颜色
    ImGuiCol_NavWindowingHighlight, // 使用 Ctrl+Tab 时的导航窗口高亮
    ImGuiCol_NavWindowingDimBg, // 当 Ctrl+Tab 窗口列表激活时，调暗/着色其背后的整个屏幕背景
    ImGuiCol_ModalWindowDimBg, // 当模态窗口激活时，调暗/着色其背后的整个屏幕背景
    ImGuiCol_COUNT,


#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    ImGuiCol_TabActive = ImGuiCol_TabSelected, // [在 1.90.9 版本中重命名]
    ImGuiCol_TabUnfocused = ImGuiCol_TabDimmed, // [在 1.90.9 版本中重命名]
    ImGuiCol_TabUnfocusedActive = ImGuiCol_TabDimmedSelected, // [在 1.90.9 版本中重命名]
    ImGuiCol_NavHighlight = ImGuiCol_NavCursor, // [在 1.91.4 版本中重命名]
#endif
};


// 用于 PushStyleVar() / PopStyleVar() 的枚举，用于临时修改 ImGuiStyle 结构。
// - 该枚举仅引用 ImGuiStyle 中适合在 UI 代码内进行入栈/出栈（push/pop）操作的字段。
// 在初始化期间或帧与帧之间，可以随意直接修改 ImGuiStyle。
// - 提示：利用编程 IDE 的导航功能点击下方“第二列”中的名称，即可找到实际的成员及其说明。
// - 在 Visual Studio 中：Ctrl+逗号（“Edit.GoToAll”）可以追踪注释内的符号，而 Ctrl+F12（“Edit.GoToImplementation”）则不行。
// - 在安装了 Visual Assist 的 Visual Studio 中：Alt+G（“VAssistX.GoToImplementation”）也可以追踪注释内的符号。
// - 在 VS Code、CLion 等编辑器中：Ctrl+左键单击可以追踪注释内的符号。
// - 当更改此枚举时，你需要相应地更新关联的内部表 GStyleVarInfo[]。这是我们将枚举值与成员偏移量/类型进行链接的地方。
enum ImGuiStyleVar_
{
    // 枚举名称 -------------------------- // ImGuiStyle 结构体中的成员 (说明请参见 ImGuiStyle)
    ImGuiStyleVar_Alpha, // float Alpha
    ImGuiStyleVar_DisabledAlpha, // float 禁用状态下的透明度 (DisabledAlpha)
    ImGuiStyleVar_WindowPadding, // ImVec2 窗口内边距 (WindowPadding)
    ImGuiStyleVar_WindowRounding, // float 窗口圆角半径 (WindowRounding)
    ImGuiStyleVar_WindowBorderSize, // float 窗口边框尺寸 (WindowBorderSize)
    ImGuiStyleVar_WindowMinSize, // ImVec2 WindowMinSize
    ImGuiStyleVar_WindowTitleAlign, // ImVec2 WindowTitleAlign
    ImGuiStyleVar_ChildRounding, // float ChildRounding
    ImGuiStyleVar_ChildBorderSize, // float ChildBorderSize
    ImGuiStyleVar_PopupRounding, // float PopupRounding
    ImGuiStyleVar_PopupBorderSize, // float PopupBorderSize
    ImGuiStyleVar_FramePadding, // ImVec2 FramePadding
    ImGuiStyleVar_FrameRounding, // float FrameRounding
    ImGuiStyleVar_FrameBorderSize, // float 框架边框大小 (FrameBorderSize)
    ImGuiStyleVar_ItemSpacing, // ImVec2 项目间距 (ItemSpacing)
    ImGuiStyleVar_ItemInnerSpacing, // ImVec2 项目内部间距 (ItemInnerSpacing)
    ImGuiStyleVar_IndentSpacing, // float 缩进间距 (IndentSpacing)
    ImGuiStyleVar_CellPadding, // ImVec2 单元格内边距 (CellPadding)
    ImGuiStyleVar_ScrollbarSize, // float 滚动条大小 (ScrollbarSize)
    ImGuiStyleVar_ScrollbarRounding, // float 滚动条圆角 (ScrollbarRounding)
    ImGuiStyleVar_ScrollbarPadding, // float 滚动条内边距 (ScrollbarPadding)
    ImGuiStyleVar_GrabMinSize, // float GrabMinSize（抓取器最小尺寸）
    ImGuiStyleVar_GrabRounding, // float GrabRounding（抓取器圆角）
    ImGuiStyleVar_ImageRounding, // float ImageRounding（图像圆角）
    ImGuiStyleVar_ImageBorderSize, // float ImageBorderSize（图像边框尺寸）
    ImGuiStyleVar_TabRounding, // float TabRounding（标签圆角）
    ImGuiStyleVar_TabBorderSize, // float TabBorderSize（标签边框大小）
    ImGuiStyleVar_TabMinWidthBase, // float TabMinWidthBase（标签最小宽度基准）
    ImGuiStyleVar_TabMinWidthShrink, // float TabMinWidthShrink（标签收缩时的最小宽度）
    ImGuiStyleVar_TabBarBorderSize, // float TabBarBorderSize
    ImGuiStyleVar_TabBarOverlineSize, // float TabBarOverlineSize
    ImGuiStyleVar_TableAngledHeadersAngle, // float TableAngledHeadersAngle
    ImGuiStyleVar_TableAngledHeadersTextAlign,// ImVec2 TableAngledHeadersTextAlign
    ImGuiStyleVar_TreeLinesSize, // float TreeLinesSize
    ImGuiStyleVar_TreeLinesRounding, // float TreeLinesRounding
    ImGuiStyleVar_ButtonTextAlign, // ImVec2 ButtonTextAlign
    ImGuiStyleVar_SelectableTextAlign, // ImVec2 SelectableTextAlign
    ImGuiStyleVar_SeparatorTextBorderSize, // float 分隔符文本边框粗细 (SeparatorTextBorderSize)
    ImGuiStyleVar_SeparatorTextAlign, // ImVec2 分隔符文本对齐方式 (SeparatorTextAlign)
    ImGuiStyleVar_SeparatorTextPadding, // ImVec2 分隔符文本内边距 (SeparatorTextPadding)
    ImGuiStyleVar_COUNT
};


// InvisibleButton() 的标志位 [在 imgui_internal.h 中有扩展]
enum ImGuiButtonFlags_
{
    ImGuiButtonFlags_None = 0,
    ImGuiButtonFlags_MouseButtonLeft = 1 << 0, // 对鼠标左键做出反应（默认）
    ImGuiButtonFlags_MouseButtonRight = 1 << 1, // 响应鼠标右键
    ImGuiButtonFlags_MouseButtonMiddle = 1 << 2, // 响应鼠标中键
    ImGuiButtonFlags_MouseButtonMask_ = ImGuiButtonFlags_MouseButtonLeft | ImGuiButtonFlags_MouseButtonRight | ImGuiButtonFlags_MouseButtonMiddle, // [内部使用]
    ImGuiButtonFlags_EnableNav = 1 << 3, // InvisibleButton()：不禁用导航/制表位（Tabbing）。否则默认禁用。
};


// ColorEdit3() / ColorEdit4() / ColorPicker3() / ColorPicker4() / ColorButton() 的标志位
enum ImGuiColorEditFlags_
{
    ImGuiColorEditFlags_None = 0,
    ImGuiColorEditFlags_NoAlpha = 1 << 1, // ColorEdit, ColorPicker, ColorButton: 忽略 Alpha 分量（仅从输入指针读取 3 个分量）。
    ImGuiColorEditFlags_NoPicker = 1 << 2, // // ColorEdit：点击颜色方块时禁用拾色器。
    ImGuiColorEditFlags_NoOptions = 1 << 3, // // ColorEdit：右键点击输入框/小预览图时禁用切换选项菜单。
    ImGuiColorEditFlags_NoSmallPreview = 1 << 4, // // ColorEdit, ColorPicker：禁用输入框旁的颜色方块预览。（例如：仅显示输入框）
    ImGuiColorEditFlags_NoInputs = 1 << 5, // // ColorEdit, ColorPicker：禁用输入滑块/文本组件（例如：仅显示小预览颜色方块）。
    ImGuiColorEditFlags_NoTooltip = 1 << 6, // // ColorEdit, ColorPicker, ColorButton: 悬停在预览图上时禁用工具提示。
    ImGuiColorEditFlags_NoLabel = 1 << 7, // // ColorEdit, ColorPicker: 禁用内联文本标签的显示（标签仍会传递给工具提示和选择器）。
    ImGuiColorEditFlags_NoSidePreview = 1 << 8, // // ColorPicker: 禁用选择器右侧较大的颜色预览，改用小的正方形颜色预览。
    ImGuiColorEditFlags_NoDragDrop = 1 << 9, // // ColorEdit: 禁用拖放目标。ColorButton: 禁用拖放源。
    ImGuiColorEditFlags_NoBorder = 1 << 10, // // ColorButton：禁用边框（默认强制显示）
    ImGuiColorEditFlags_NoColorMarkers = 1 << 11, // // ColorEdit：禁用 R/G/B/A 颜色标记的渲染。也可以通过将 style.ColorMarkerSize 设置为 0 来全局禁用。


    // Alpha 预览
    // - 在 1.91.8 (2025/01/21) 版本之前：预览中的 Alpha 通道默认是不透明的，使用的是旧名称 ImGuiColorEditFlags_AlphaPreview。
    // - 我们现在默认将预览显示为透明。你可以使用 ImGuiColorEditFlags_AlphaOpaque 来恢复旧的行为。
    // - 新的标志位可以更好地组合，并允许更精细的控制。
    ImGuiColorEditFlags_AlphaOpaque = 1 << 12, // // ColorEdit, ColorPicker, ColorButton: 在预览中禁用 Alpha。与 _NoAlpha 不同，在调用 ColorEdit4()/ColorPicker4() 时仍可对其进行编辑。对于 ColorButton()，其效果与 _NoAlpha 相同。
    ImGuiColorEditFlags_AlphaNoBg = 1 << 13, // // ColorEdit, ColorPicker, ColorButton: 禁用在透明色后面渲染棋盘格背景。
    ImGuiColorEditFlags_AlphaPreviewHalf = 1 << 14, // ColorEdit, ColorPicker, ColorButton：显示一半不透明、一半透明的预览。


    // 用户选项（右键单击控件可更改其中部分选项）。
    ImGuiColorEditFlags_AlphaBar = 1 << 18, // ColorEdit, ColorPicker：在拾取器中显示垂直 Alpha 条/渐变。
    ImGuiColorEditFlags_HDR = 1 << 19, // (开发中) ColorEdit：目前仅在 RGBA 编辑中禁用 0.0f..1.0f 的限制（注意：你可能也需要使用 ImGuiColorEditFlags_Float 标志）。
    ImGuiColorEditFlags_DisplayRGB = 1 << 20, // [显示] // ColorEdit：在 RGB/HSV/Hex 中覆盖“显示类型”。ColorPicker：使用 RGB/HSV/Hex 中的一个或多个组合进行选择。
    ImGuiColorEditFlags_DisplayHSV = 1 << 21, // [显示] // "
    ImGuiColorEditFlags_DisplayHex = 1 << 22, // [显示] // "
    ImGuiColorEditFlags_Uint8 = 1 << 23, // [数据类型] // ColorEdit, ColorPicker, ColorButton：“显示值”格式化为 0..255。
    ImGuiColorEditFlags_Float = 1 << 24, // [数据类型] // ColorEdit, ColorPicker, ColorButton：将显示值格式化为 0.0f..1.0f 的浮点数，而非 0..255 的整数。数值不会经过整数转换。
    ImGuiColorEditFlags_PickerHueBar = 1 << 25, // [选择器] // ColorPicker：色相使用条状，饱和度/明度使用矩形。
    ImGuiColorEditFlags_PickerHueWheel = 1 << 26, // [选择器] // ColorPicker：色相使用轮状，饱和度/明度使用三角形。
    ImGuiColorEditFlags_InputRGB = 1 << 27, // [输入] // ColorEdit, ColorPicker：输入和输出数据采用 RGB 格式。
    ImGuiColorEditFlags_InputHSV = 1 << 28, // [输入] // ColorEdit, ColorPicker：以 HSV 格式输入和输出数据。


    // 默认选项。你可以使用 SetColorEditOptions() 设置应用程序默认值。其意图是，你可能不希望在
    // 大多数调用中覆盖它们。让用户通过选项菜单选择，和/或在启动期间调用一次 SetColorEditOptions()。
    ImGuiColorEditFlags_DefaultOptions_ = ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_PickerHueBar,


    // [内部] 掩码
    ImGuiColorEditFlags_AlphaMask_ = ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_AlphaOpaque | ImGuiColorEditFlags_AlphaNoBg | ImGuiColorEditFlags_AlphaPreviewHalf,
    ImGuiColorEditFlags_DisplayMask_ = ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_DisplayHSV | ImGuiColorEditFlags_DisplayHex,
    ImGuiColorEditFlags_DataTypeMask_ = ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_Float,
    ImGuiColorEditFlags_PickerMask_ = ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_PickerHueBar,
    ImGuiColorEditFlags_InputMask_ = ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_InputHSV,


    // 已废弃的名称
#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    ImGuiColorEditFlags_AlphaPreview = 0, // 在 1.91.8 版本中移除。现在这是默认行为。除非设置了 ImGuiColorEditFlags_AlphaNoBg，否则将显示棋盘格背景。
#endif
    //ImGuiColorEditFlags_RGB = ImGuiColorEditFlags_DisplayRGB, ImGuiColorEditFlags_HSV = ImGuiColorEditFlags_DisplayHSV, ImGuiColorEditFlags_HEX = ImGuiColorEditFlags_DisplayHex // [在 1.69 版本中重命名]
};


// DragFloat()、DragInt()、SliderFloat()、SliderInt() 等函数的标志。
// 我们为 DragXXX() 和 SliderXXX() 系列函数使用相同的标志集，因为它们的功能相同，这样更便于互相替换。
//（这些是针对单个项目的标志。还有一个共享的行为标志：ImGuiIO: io.ConfigDragClickToInputText）
enum ImGuiSliderFlags_
{
    ImGuiSliderFlags_None = 0,
    ImGuiSliderFlags_Logarithmic = 1 << 5, // 使控件变为对数显示（否则为线性）。如果使用的格式化字符串小数位数较少，请考虑配合使用 ImGuiSliderFlags_NoRoundToFormat。
    ImGuiSliderFlags_NoRoundToFormat = 1 << 6, // 禁用将底层数值四舍五入以匹配显示格式字符串的精度（例如 %.3f 的值会被舍入到小数点后 3 位）。
    ImGuiSliderFlags_NoInput = 1 << 7, // 禁用通过 Ctrl+左键单击或 Enter 键直接在控件中输入文本的功能。
    ImGuiSliderFlags_WrapAround = 1 << 8, // 启用从最大值到最小值以及从最小值到最大值的循环回绕。目前仅由 DragXXX() 系列函数支持。
    ImGuiSliderFlags_ClampOnInput = 1 << 9, // 当通过 Ctrl+左键单击手动输入时，将数值限制在最小/最大范围内。默认情况下，Ctrl+左键单击允许超出范围。
    ImGuiSliderFlags_ClampZeroRange = 1 << 10, // 即使 min==max==0.0f 也会进行限制。否则由于历史原因，DragXXX 系列函数在这些数值下不会生效。当你的限制范围是动态变化时，通常都需要使用此标志。
    ImGuiSliderFlags_NoSpeedTweaks = 1 << 11, // 禁用键盘修饰键对微调速度的影响。如果你想根据自己的逻辑自定义微调速度，此标志非常有用。
    ImGuiSliderFlags_ColorMarkers = 1 << 12, // DragScalarN(), SliderScalarN()：在每个分量上绘制 R/G/B/A 颜色标记。
    ImGuiSliderFlags_AlwaysClamp = ImGuiSliderFlags_ClampOnInput | ImGuiSliderFlags_ClampZeroRange,
    ImGuiSliderFlags_InvalidMask_ = 0x7000000F, // [内部] 我们将这些位视为可能来自旧版 API（2020-08 已废弃）的“float power”参数，这些参数可能被错误地强制转换为此枚举，并在需要时触发断言。
};


// 标识鼠标按键。
// 这些值保证是稳定的，我们经常直接使用 0/1。提供命名枚举是为了方便起见。
enum ImGuiMouseButton_
{
    ImGuiMouseButton_Left = 0,
    ImGuiMouseButton_Right = 1,
    ImGuiMouseButton_Middle = 2,
    ImGuiMouseButton_COUNT = 5
};


// GetMouseCursor() 的枚举
// 用户代码可以通过调用 SetMouseCursor() 请求后端显示特定光标，这就是为什么这里有一些标记为未使用的光标
enum ImGuiMouseCursor_
{
    ImGuiMouseCursor_None = -1,
    ImGuiMouseCursor_Arrow = 0,
    ImGuiMouseCursor_TextInput, // 当悬停在 InputText 等控件上时
    ImGuiMouseCursor_ResizeAll, // （Dear ImGui 函数暂未使用）
    ImGuiMouseCursor_ResizeNS, // 当悬停在水平边框上时
    ImGuiMouseCursor_ResizeEW, // 当悬停在垂直边界或列上时
    ImGuiMouseCursor_ResizeNESW, // 当悬停在窗口左下角时
    ImGuiMouseCursor_ResizeNWSE, // 当悬停在窗口右下角时
    ImGuiMouseCursor_Hand, // （Dear ImGui 函数未使用。可用于超链接等）
    ImGuiMouseCursor_Wait, // 当等待某项操作处理或加载时。
    ImGuiMouseCursor_Progress, // 当等待某项操作处理或加载，但应用程序仍可交互时。
    ImGuiMouseCursor_NotAllowed, // 当悬停在禁止交互的内容上时。通常是一个带斜杠的圆圈。
    ImGuiMouseCursor_COUNT
};


// AddMouseSourceEvent() 的枚举，用于表示鼠标输入数据的实际来源。
// 从历史上看，我们随处都在使用“Mouse（鼠标）”这一术语来表示指针数据，例如 MousePos、IsMousePressed()、io.AddMousePosEvent()。
// 但这些“鼠标”数据可能来自不同的来源，应用程序有时了解这些来源会很有用。
// 你可以使用 io.AddMouseSourceEvent() 来提交指针类型的更改。
enum ImGuiMouseSource : int
{
    ImGuiMouseSource_Mouse = 0, // 输入来自真实的鼠标。
    ImGuiMouseSource_TouchScreen, // 输入来自触摸屏（在首次按下前没有悬停状态，首次按下的瞄准精度较低，可能支持双轴滚轮）。
    ImGuiMouseSource_Pen, // 输入来自压力/磁性笔（通常与高采样率结合使用）。
    ImGuiMouseSource_COUNT
};


// 用于 ImGui::SetNextWindow***()、SetWindow***()、SetNextItem***() 函数的枚举
// 表示一个条件。
// 重要提示：请将其视为普通枚举！切勿使用二进制运算符组合多个数值！上述所有函数都会将 0 视为 ImGuiCond_Always 的快捷方式。
enum ImGuiCond_
{
    ImGuiCond_None = 0, // 无条件（始终设置变量），等同于 _Always
    ImGuiCond_Always = 1 << 0, // 无条件（始终设置变量），等同于 _None
    ImGuiCond_Once = 1 << 1, // 在每次运行时会话中仅设置一次变量（只有第一次调用会生效）
    ImGuiCond_FirstUseEver = 1 << 2, // 如果对象/窗口没有持久保存的数据（.ini 文件中无条目），则设置该变量
    ImGuiCond_Appearing = 1 << 3, // 如果对象/窗口在隐藏/非活动状态后重新出现（或首次出现），则设置该变量
};


//-----------------------------------------------------------------------------
// [SECTION] 表格 API 标志与结构 (ImGuiTableFlags, ImGuiTableColumnFlags, ImGuiTableRowFlags, ImGuiTableBgTarget, ImGuiTableSortSpecs, ImGuiTableColumnSortSpecs)
//-----------------------------------------------------------------------------


// ImGui::BeginTable() 的标志
// - 重要提示！尺寸调整策略具有复杂且微妙的副作用，其影响远超你的预期。
// 请仔细阅读注释/示例，并结合实时演示进行实验，以熟悉这些策略。
// - 默认（DEFAULT）尺寸调整策略如下：
// - 如果开启了 ScrollX，或者宿主窗口带有 ImGuiWindowFlags_AlwaysAutoResize 标志，则默认为 ImGuiTableFlags_SizingFixedFit。
// - 如果 ScrollX 关闭，则默认为 ImGuiTableFlags_SizingStretchSame。
// - 当 ScrollX 关闭时：
// - 表格默认为 ImGuiTableFlags_SizingStretchSame -> 所有列默认为具有相同权重的 ImGuiTableColumnFlags_WidthStretch。
// - 允许的列尺寸策略：Stretch（默认）、Fixed/Auto。
// - 固定列（如果有）通常会获得其请求的宽度（除非表格无法容纳所有固定列）。
// - 拉伸列（Stretch Columns）将根据各自的权重分享剩余宽度。
// - 混合使用固定/拉伸列是可行的，但会对调整大小的行为产生各种副作用。
// 混合尺寸策略的典型用法是：任意数量的前置固定列，后跟一到两个后置拉伸列。
// （这是因为列的可见顺序对它们在手动调整大小时的反应有着微妙但必要的影响）。
// - 当 ScrollX 开启时：
// - 表格默认使用 ImGuiTableFlags_SizingFixedFit -> 所有列默认使用 ImGuiTableColumnFlags_WidthFixed
// - 允许的列尺寸策略：主要为 Fixed/Auto。
// - 固定列可以根据需要放大。如果需要，表格将显示水平滚动条。
// - 当使用自动调整大小（不可调整大小）的固定列时，查询内容宽度以进行项目右对齐（例如使用 SetNextItemWidth(-FLT_MIN)）是没有意义的，这会产生反馈循环。
// - 如果开启了 ScrollX，使用拉伸（Stretch）列通常是没有意义的，除非你在 BeginTable() 中为 'inner_width' 指定了一个值。
// - 如果你为 'inner_width' 指定了一个值，那么滚动空间实际上就是已知的，拉伸列或固定/拉伸混合列将再次变得有意义。
// - 详情请阅读 imgui_tables.cpp 顶部的文档。
enum ImGuiTableFlags_
{
    // 功能特性
    ImGuiTableFlags_None = 0,
    ImGuiTableFlags_Resizable = 1 << 0, // 允许调整列宽。
    ImGuiTableFlags_Reorderable = 1 << 1, // 允许在表头行中重新排列列顺序（需要调用 TableSetupColumn() + TableHeadersRow() 来显示表头）
    ImGuiTableFlags_Hideable = 1 << 2, // 允许在上下文菜单中隐藏/禁用列。
    ImGuiTableFlags_Sortable = 1 << 3, // 启用排序。调用 TableGetSortSpecs() 以获取排序规格。另请参阅 ImGuiTableFlags_SortMulti 和 ImGuiTableFlags_SortTristate。
    ImGuiTableFlags_NoSavedSettings = 1 << 4, // 禁用在 .ini 文件中持久化保存列的顺序、宽度、可见性和排序设置。
    ImGuiTableFlags_ContextMenuInBody = 1 << 5, // 在列主体/内容上右键点击将显示表格上下文菜单。默认情况下，该菜单仅在 TableHeadersRow() 中可用。
    // 装饰 (Decorations)
    ImGuiTableFlags_RowBg = 1 << 6, // 使用 ImGuiCol_TableRowBg 或 ImGuiCol_TableRowBgAlt 设置每一行的背景颜色（相当于手动对每一行调用带有 ImGuiTableBgFlags_RowBg0 的 TableSetBgColor）
    ImGuiTableFlags_BordersInnerH = 1 << 7, // 在行与行之间绘制水平边框。
    ImGuiTableFlags_BordersOuterH = 1 << 8, // 在顶部和底部绘制水平边框。
    ImGuiTableFlags_BordersInnerV = 1 << 9, // 在列与列之间绘制垂直边框。
    ImGuiTableFlags_BordersOuterV = 1 << 10, // 在左侧和右侧绘制垂直边框。
    ImGuiTableFlags_BordersH = ImGuiTableFlags_BordersInnerH | ImGuiTableFlags_BordersOuterH, // 绘制水平边框。
    ImGuiTableFlags_BordersV = ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_BordersOuterV, // 绘制垂直边框。
    ImGuiTableFlags_BordersInner = ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_BordersInnerH, // 绘制内部边框。
    ImGuiTableFlags_BordersOuter = ImGuiTableFlags_BordersOuterV | ImGuiTableFlags_BordersOuterH, // 绘制外部边框。
    ImGuiTableFlags_Borders = ImGuiTableFlags_BordersInner | ImGuiTableFlags_BordersOuter, // 绘制所有边框。
    ImGuiTableFlags_NoBordersInBody = 1 << 11, // [ALPHA] 禁用表格主体（Body）中的垂直边框（表头 Headers 中仍会显示边框）。-> 可能会移至 style
    ImGuiTableFlags_NoBordersInBodyUntilResize = 1 << 12, // [ALPHA] 在悬停调整大小前，禁用表格主体中的垂直边框（表头中仍会显示边框）。-> 可能会移至 style
    // 尺寸策略（默认值请参阅上文）
    ImGuiTableFlags_SizingFixedFit = 1 << 13, // 列默认设置为 _WidthFixed 或 _WidthAuto（取决于是否可调整尺寸），以匹配内容宽度。
    ImGuiTableFlags_SizingFixedSame = 2 << 13, // 列默认设置为 _WidthFixed 或 _WidthAuto（取决于是否可调整尺寸），以匹配所有列中的最大内容宽度。隐式启用 ImGuiTableFlags_NoKeepColumnsVisible。
    ImGuiTableFlags_SizingStretchProp = 3 << 13, // 列默认设置为 _WidthStretch，默认权重与每列的内容宽度成比例。
    ImGuiTableFlags_SizingStretchSame = 4 << 13, // 列默认设置为 _WidthStretch，默认权重全部相等，除非被 TableSetupColumn() 覆盖。
    // 尺寸调整额外选项
    ImGuiTableFlags_NoHostExtendX = 1 << 16, // 使外部宽度自动适应列宽，覆盖 outer_size.x 的值。仅在禁用 ScrollX/ScrollY 且未使用 Stretch 列时可用。
    ImGuiTableFlags_NoHostExtendY = 1 << 17, // 使外部高度精确停止在 outer_size.y（防止表格自动延伸超过限制）。仅在禁用 ScrollX/ScrollY 时可用。超出限制的数据将被裁剪且不可见。
    ImGuiTableFlags_NoKeepColumnsVisible = 1 << 18, // 当 ScrollX 关闭且表格变得过小时，禁用“保持列始终最小可见”的特性。如果列是可调整大小的，则不建议使用此选项。
    ImGuiTableFlags_PreciseWidths = 1 << 19, // 禁用将剩余宽度分配给伸展列（在宽度为 100 且有 3 列的表格上进行宽度分配：不带此标志时为 33, 33, 34；带此标志时为 33, 33, 33）。当列数较多时，调整大小的操作可能会显得不够平滑。
    // 裁剪 (Clipping)
    ImGuiTableFlags_NoClip = 1 << 20, // 禁用每个独立列的裁剪矩形（减少绘制命令数量，内容将能够溢出到其他列）。通常与 TableSetupScrollFreeze() 不兼容。
    // 填充 (Padding)
    ImGuiTableFlags_PadOuterX = 1 << 21, // 如果开启了 BordersOuterV，则默认为此项。启用最外侧填充。如果有表头，通常建议开启。
    ImGuiTableFlags_NoPadOuterX = 1 << 22, // 如果关闭了 BordersOuterV，则默认为此项。禁用最外侧填充。
    ImGuiTableFlags_NoPadInnerX = 1 << 23, // 禁用列之间的内部填充（如果开启了 BordersOuterV 则为双倍内部填充，如果关闭了 BordersOuterV 则为单倍内部填充）。
    // 滚动
    ImGuiTableFlags_ScrollX = 1 << 24, // 启用水平滚动。需要通过 BeginTable() 的 'outer_size' 参数指定容器尺寸。这会改变默认的尺寸调整策略。由于这会创建一个子窗口，在使用 ScrollX 时，目前通常建议同时启用 ScrollY。
    ImGuiTableFlags_ScrollY = 1 << 25, // 启用垂直滚动。需要通过 BeginTable() 的 'outer_size' 参数指定容器尺寸。
    // 排序
    ImGuiTableFlags_SortMulti = 1 << 26, // 点击表头时按住 Shift 键可对多列进行排序。TableGetSortSpecs() 可能会返回 (SpecsCount > 1) 的规格。
    ImGuiTableFlags_SortTristate = 1 << 27, // 允许不排序，禁用默认排序。TableGetSortSpecs() 可能会返回 (SpecsCount == 0) 的规格。
    // 杂项
    ImGuiTableFlags_HighlightHoveredColumn = 1 << 28, // 悬停时高亮列标题（未来可能会演变为更完整的高亮效果）


    // [内部] 组合与掩码
    ImGuiTableFlags_SizingMask_ = ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_SizingFixedSame | ImGuiTableFlags_SizingStretchProp | ImGuiTableFlags_SizingStretchSame,
};


// 用于 ImGui::TableSetupColumn() 的标志
enum ImGuiTableColumnFlags_
{
    // 输入配置标志
    ImGuiTableColumnFlags_None = 0,
    ImGuiTableColumnFlags_Disabled = 1 << 0, // 强制禁用标志：隐藏列，且不会显示在右键菜单中（不同于调用 TableSetColumnEnabled()，后者操作的是用户可访问的状态）
    ImGuiTableColumnFlags_DefaultHide = 1 << 1, // 默认作为隐藏/禁用列。
    ImGuiTableColumnFlags_DefaultSort = 1 << 2, // 默认作为排序列。
    ImGuiTableColumnFlags_WidthStretch = 1 << 3, // 列将拉伸。在禁用水平滚动时优先使用（如果表格尺寸策略为 _SizingStretchSame 或 _SizingStretchProp，则为默认值）。
    ImGuiTableColumnFlags_WidthFixed = 1 << 4, // 列不会拉伸。在启用水平滚动时优先使用（如果表格尺寸策略为 _SizingFixedFit 且表格可调整大小，则为默认值）。
    ImGuiTableColumnFlags_NoResize = 1 << 5, // 禁用手动调整大小。
    ImGuiTableColumnFlags_NoReorder = 1 << 6, // 禁用手动重新排序此列，这也会防止其他列跨越此列。
    ImGuiTableColumnFlags_NoHide = 1 << 7, // 禁用隐藏/关闭此列的功能。
    ImGuiTableColumnFlags_NoClip = 1 << 8, // 禁用此列的裁剪（所有 NoClip 列将在同一个绘制命令中渲染）。
    ImGuiTableColumnFlags_NoSort = 1 << 9, // 禁用此字段的排序功能（即使表格设置了 ImGuiTableFlags_Sortable）。
    ImGuiTableColumnFlags_NoSortAscending = 1 << 10, // 禁用升序排序功能。
    ImGuiTableColumnFlags_NoSortDescending = 1 << 11, // 禁用降序排序功能。
    ImGuiTableColumnFlags_NoHeaderLabel = 1 << 12, // TableHeadersRow() 将为此列提交一个空标签。适用于某些窄列。名称仍会出现在右键菜单或倾斜表头中。您可以在调用 TableHeadersRow() 后立即调用 TableSetColumnIndex() 来向此单元格追加内容。
    ImGuiTableColumnFlags_NoHeaderWidth = 1 << 13, // 禁用表头文本宽度对自动列宽的影响。
    ImGuiTableColumnFlags_PreferSortAscending = 1 << 14, // 首次对此列进行排序时，将初始排序方向设为升序（默认）。
    ImGuiTableColumnFlags_PreferSortDescending = 1 << 15, // 首次对该列进行排序时，初始排序方向优先设为降序。
    ImGuiTableColumnFlags_IndentEnable = 1 << 16, // 进入单元格时使用当前的缩进值（第 0 列的默认设置）。
    ImGuiTableColumnFlags_IndentDisable = 1 << 17, // 进入单元格时忽略当前的缩进值（第 0 列之后的默认设置）。单元格*内部*的缩进更改仍会被生效。
    ImGuiTableColumnFlags_AngledHeader = 1 << 18, // TableHeadersRow() 将为此列提交一个倾斜的表头行。注意这会增加一个额外的行。


    // 输出状态标志，可通过 TableGetColumnFlags() 进行只读访问
    ImGuiTableColumnFlags_IsEnabled = 1 << 24, // 状态：已启用 == 未被用户/API 隐藏（在 _DefaultHide 和 _NoHide 标志中被称为“隐藏”）。
    ImGuiTableColumnFlags_IsVisible = 1 << 25, // 状态：可见 == 已启用且未被滚动剪裁。
    ImGuiTableColumnFlags_IsSorted = 1 << 26, // 状态：当前是排序规范（sort specs）的一部分
    ImGuiTableColumnFlags_IsHovered = 1 << 27, // 状态：鼠标正在其上方悬停


    // [内部] 组合与掩码
    ImGuiTableColumnFlags_WidthMask_ = ImGuiTableColumnFlags_WidthStretch | ImGuiTableColumnFlags_WidthFixed,
    ImGuiTableColumnFlags_IndentMask_ = ImGuiTableColumnFlags_IndentEnable | ImGuiTableColumnFlags_IndentDisable,
    ImGuiTableColumnFlags_StatusMask_ = ImGuiTableColumnFlags_IsEnabled | ImGuiTableColumnFlags_IsVisible | ImGuiTableColumnFlags_IsSorted | ImGuiTableColumnFlags_IsHovered,
    ImGuiTableColumnFlags_NoDirectResize_ = 1 << 30, // [内部] 禁止用户直接调整此列的大小（但可能会通过其左侧边缘间接调整大小）
};


// ImGui::TableNextRow() 的标志
enum ImGuiTableRowFlags_
{
    ImGuiTableRowFlags_None = 0,
    ImGuiTableRowFlags_Headers = 1 << 0, // 标识标题行（设置默认背景颜色 + 其内容宽度在计算自动列宽时会有不同的处理方式）
};


// 用于 ImGui::TableSetBgColor() 的枚举
// 背景颜色分 3 层渲染：
// - 第 0 层：如果设置了 RowBg0 颜色则使用它绘制，否则如果设置了 ColumnBg0 则使用它绘制。
// - 第 1 层：如果设置了 RowBg1 颜色则使用它绘制，否则如果设置了 ColumnBg1 则使用它绘制。
// - 第 2 层：如果设置了 CellBg 颜色则使用它绘制。
// 设置两个行/列层的目的是让您决定背景颜色的更改应该是覆盖现有颜色还是与其混合。
// 在表格中使用 ImGuiTableFlags_RowBg 时，每一行都会根据奇偶行自动设置 RowBg0 颜色。
// 如果你设置了 RowBg0 目标的颜色，你的颜色将覆盖现有的 RowBg0 颜色。
// 如果你设置了 RowBg1 或 ColumnBg1 目标的颜色，你的颜色将混合在 RowBg0 颜色之上。
enum ImGuiTableBgTarget_
{
    ImGuiTableBgTarget_None = 0,
    ImGuiTableBgTarget_RowBg0 = 1, // 设置行背景颜色 0（通常用于背景，在使用 ImGuiTableFlags_RowBg 时会自动设置）
    ImGuiTableBgTarget_RowBg1 = 2, // 设置行背景颜色 1（通常用于选择标记）
    ImGuiTableBgTarget_CellBg = 3, // 设置单元格背景颜色（最顶层颜色）
};


// 表格的排序规范（通常处理单列的排序规范，有时也处理多列）
// 通过调用 TableGetSortSpecs() 获取。
// 当 'SpecsDirty == true' 时，你可以对数据进行排序。当排序规范自上次调用以来发生变化，或者是第一次调用时，该值将为 true。
// 请务必在排序后将 'SpecsDirty' 设置为 false，否则你可能会在每一帧都浪费地对数据进行排序！
struct ImGuiTableSortSpecs
{
    const ImGuiTableColumnSortSpecs* Specs; // 指向排序规范数组的指针。
    int SpecsCount; // 排序规范的数量。通常为 1。当启用 ImGuiTableFlags_SortMulti 时可能大于 1。当启用 ImGuiTableFlags_SortTristate 时可能等于 0。
    bool SpecsDirty; // 当排序规范自上次以来发生变化时设置为 true！请据此重新排序，然后清除该标志。


    ImGuiTableSortSpecs() { memset(this, 0, sizeof(*this)); }
};


// 表格单列的排序规范（大小 == 12 字节）
struct ImGuiTableColumnSortSpecs
{
    ImGuiID ColumnUserID; // 列的用户 ID（如果在 TableSetupColumn() 调用中指定了的话）
    ImS16 ColumnIndex; // 列的索引
    ImS16 SortOrder; // 在父级 ImGuiTableSortSpecs 中的索引（始终从 0 开始按顺序存储，仅按单一标准排序的表格此处始终为 0）
    ImGuiSortDirection SortDirection; // ImGuiSortDirection_Ascending（升序）或 ImGuiSortDirection_Descending（降序）


    ImGuiTableColumnSortSpecs() { memset(this, 0, sizeof(*this)); }
};


//-----------------------------------------------------------------------------
// [SECTION] 辅助工具：调试日志、内存分配宏、ImVector<>
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// 调试日志记录，输出至 ShowDebugLogWindow()、tty 等。
//-----------------------------------------------------------------------------


#ifndef IMGUI_DISABLE_DEBUG_TOOLS
#define IMGUI_DEBUG_LOG(...) ImGui::DebugLog(__VA_ARGS__)
#else
#define IMGUI_DEBUG_LOG(...) ((void)0)
#endif


//-----------------------------------------------------------------------------
// IM_MALLOC(), IM_FREE(), IM_NEW(), IM_PLACEMENT_NEW(), IM_DELETE()
// 我们通过 placement "new(ptr) Type()" 语法在自行分配的内存上调用 C++ 构造函数。
// 定义一个带有自定义参数的自定义 placement new()，可以让我们绕过对 <new> 的包含，因为在某些平台上，当用户禁用异常时，包含 <new> 会报错。
//-----------------------------------------------------------------------------


struct ImNewWrapper {};
inline void* operator new(size_t, ImNewWrapper, void* ptr) { return ptr; }
inline void operator delete(void*, ImNewWrapper, void*) {} // 仅为了能使用对称的 new() 而定义
#define IM_ALLOC(_SIZE) ImGui::MemAlloc(_SIZE)
#define IM_FREE(_PTR) ImGui::MemFree(_PTR)
#define IM_PLACEMENT_NEW(_PTR) new(ImNewWrapper(), _PTR)
#define IM_NEW(_TYPE) new(ImNewWrapper(), ImGui::MemAlloc(sizeof(_TYPE))) _TYPE
template<typename T> void IM_DELETE(T* p) { if (p) { p->~T(); ImGui::MemFree(p); } }


//-----------------------------------------------------------------------------
// ImVector<>
// 轻量级的类 std::vector<>-like 类，旨在避免引入依赖（此外，某些启用了调试模式的 STL 实现速度慢得离谱，我们绕过它以确保代码在调试模式下也能快速运行）。
//-----------------------------------------------------------------------------
// - 通常情况下，你完全不需要关心或使用它。但我们需要在 imgui.h 中提供它，因为我们的一些公共结构体依赖于它。
// - 我们在这里使用了类 std 的命名规范，这在本代码库中有些不同寻常。
// - 重要提示：clear() 会释放内存，而 resize(0) 则保留已分配的缓冲区。我们经常使用 resize(0) 来有意地在帧之间循环利用已分配的缓冲区，从而分摊开销。
// - 重要提示：我们的实现不会调用 C++ 构造函数/析构函数，我们将所有内容都视为原始数据！这是有意为之的，但请务必格外留意这一点。
// 请勿在您自己的代码中将此类用作 std::vector 的替代品！Dear ImGui 使用的许多结构体都可以通过 zero-memset（零初始化）安全地进行初始化。
//-----------------------------------------------------------------------------


IM_MSVC_RUNTIME_CHECKS_OFF
template<typename T>
struct ImVector
{
    int Size;
    int Capacity;
    T* Data;


    // 提供标准类型定义，但我们内部并不使用它们。
    typedef T value_type;
    typedef value_type* iterator;
    typedef const value_type* const_iterator;


    // 构造函数、析构函数
    inline ImVector() { Size = Capacity = 0; Data = NULL; }
    inline ImVector(const ImVector<T>& src) { Size = Capacity = 0; Data = NULL; operator=(src); }
    inline ImVector<T>& operator=(const ImVector<T>& src) { clear(); resize(src.Size); if (Data && src.Data) memcpy(Data, src.Data, (size_t)Size * sizeof(T)); return *this; }
    inline ~ImVector() { if (Data) IM_FREE(Data); } // 重要：不会析构任何内容


    inline void clear() { if (Data) { Size = Capacity = 0; IM_FREE(Data); Data = NULL; } } // 重要：不会析构任何内容
    inline void clear_delete() { for (int n = 0; n < Size; n++) IM_DELETE(Data[n]); clear(); } // 重要：绝不会自动调用！必须显式调用。
    inline void clear_destruct() { for (int n = 0; n < Size; n++) Data[n].~T(); clear(); } // 重要：绝不会自动调用！必须显式调用。


    inline bool empty() const { return Size == 0; }
    inline int size() const { return Size; }
    inline int size_in_bytes() const { return Size * (int)sizeof(T); }
    inline int max_size() const { return 0x7FFFFFFF / (int)sizeof(T); }
    inline int capacity() const { return Capacity; }
    inline T& operator[](int i) { IM_ASSERT(i >= 0 && i < Size); return Data[i]; }
    inline const T& operator[](int i) const { IM_ASSERT(i >= 0 && i < Size); return Data[i]; }


    inline T* begin() { return Data; }
    inline const T* begin() const { return Data; }
    inline T* end() { return Data + Size; }
    inline const T* end() const { return Data + Size; }
    inline T& front() { IM_ASSERT(Size > 0); return Data[0]; }
    inline const T& front() const { IM_ASSERT(Size > 0); return Data[0]; }
    inline T& back() { IM_ASSERT(Size > 0); return Data[Size - 1]; }
    inline const T& back() const { IM_ASSERT(Size > 0); return Data[Size - 1]; }
    inline void swap(ImVector<T>& rhs) { int rhs_size = rhs.Size; rhs.Size = Size; Size = rhs_size; int rhs_cap = rhs.Capacity; rhs.Capacity = Capacity; Capacity = rhs_cap; T* rhs_data = rhs.Data; rhs.Data = Data; Data = rhs_data; }


    inline int _grow_capacity(int sz) const { int new_capacity = Capacity ? (Capacity + Capacity / 2) : 8; return new_capacity > sz ? new_capacity : sz; }
    inline void resize(int new_size) { if (new_size > Capacity) reserve(_grow_capacity(new_size)); Size = new_size; }
    inline void resize(int new_size, const T& v) { if (new_size > Capacity) reserve(_grow_capacity(new_size)); if (new_size > Size) for (int n = Size; n < new_size; n++) memcpy(&Data[n], &v, sizeof(v)); Size = new_size; }
    inline void shrink(int new_size) { IM_ASSERT(new_size <= Size); Size = new_size; } // 将 vector 调整为更小的尺寸，保证不会引起重新分配
    inline void reserve(int new_capacity) { if (new_capacity <= Capacity) return; T* new_data = (T*)IM_ALLOC((size_t)new_capacity * sizeof(T)); if (Data) { memcpy(new_data, Data, (size_t)Size * sizeof(T)); IM_FREE(Data); } Data = new_data; Capacity = new_capacity; }
    inline void reserve_discard(int new_capacity) { if (new_capacity <= Capacity) return; if (Data) IM_FREE(Data); Data = (T*)IM_ALLOC((size_t)new_capacity * sizeof(T)); Capacity = new_capacity; }


    // 注意：调用 push_back/push_front/insert 时，禁止传入指向 ImVector 数据本身的引用！例如：禁止使用 v.push_back(v[10])。
    inline void push_back(const T& v) { if (Size == Capacity) reserve(_grow_capacity(Size + 1)); memcpy(&Data[Size], &v, sizeof(v)); Size++; }
    inline void pop_back() { IM_ASSERT(Size > 0); Size--; }
    inline void push_front(const T& v) { if (Size == 0) push_back(v); else insert(Data, v); }
    inline T* erase(const T* it) { IM_ASSERT(it >= Data && it < Data + Size); const ptrdiff_t off = it - Data; memmove(Data + off, Data + off + 1, ((size_t)Size - (size_t)off - 1) * sizeof(T)); Size--; return Data + off; }
    inline T* erase(const T* it, const T* it_last) { IM_ASSERT(it >= Data && it < Data + Size && it_last >= it && it_last <= Data + Size); const ptrdiff_t count = it_last - it; const ptrdiff_t off = it - Data; memmove(Data + off, Data + off + count, ((size_t)Size - (size_t)off - (size_t)count) * sizeof(T)); Size -= (int)count; return Data + off; }
    inline T* erase_unsorted(const T* it) { IM_ASSERT(it >= Data && it < Data + Size); const ptrdiff_t off = it - Data; if (it < Data + Size - 1) memcpy(Data + off, Data + Size - 1, sizeof(T)); Size--; return Data + off; }
    inline T* insert(const T* it, const T& v) { IM_ASSERT(it >= Data && it <= Data + Size); const ptrdiff_t off = it - Data; if (Size == Capacity) reserve(_grow_capacity(Size + 1)); if (off < (int)Size) memmove(Data + off + 1, Data + off, ((size_t)Size - (size_t)off) * sizeof(T)); memcpy(&Data[off], &v, sizeof(v)); Size++; return Data + off; }
    inline bool contains(const T& v) const { const T* data = Data; const T* data_end = Data + Size; while (data < data_end) if (*data++ == v) return true; return false; }
    inline T* find(const T& v) { T* data = Data; const T* data_end = Data + Size; while (data < data_end) if (*data == v) break; else ++data; return data; }
    inline const T* find(const T& v) const { const T* data = Data; const T* data_end = Data + Size; while (data < data_end) if (*data == v) break; else ++data; return data; }
    inline int find_index(const T& v) const { const T* data_end = Data + Size; const T* it = find(v); if (it == data_end) return -1; const ptrdiff_t off = it - Data; return (int)off; }
    inline bool find_erase(const T& v) { const T* it = find(v); if (it < Data + Size) { erase(it); return true; } return false; }
    inline bool find_erase_unsorted(const T& v) { const T* it = find(v); if (it < Data + Size) { erase_unsorted(it); return true; } return false; }
    inline int index_from_ptr(const T* it) const { IM_ASSERT(it >= Data && it < Data + Size); const ptrdiff_t off = it - Data; return (int)off; }
};
IM_MSVC_RUNTIME_CHECKS_RESTORE


//-----------------------------------------------------------------------------
// [SECTION] ImGuiStyle
//-----------------------------------------------------------------------------
// 您可以在初始化期间以及调用 NewFrame() 之前修改 ImGui::GetStyle() 主实例。
// 在帧执行期间，使用 ImGui::PushStyleVar(ImGuiStyleVar_XXXX)/PopStyleVar() 来修改主要的样式值，
// 使用 ImGui::PushStyleColor(ImGuiCol_XXX)/PopStyleColor() 来修改颜色。
//-----------------------------------------------------------------------------


struct ImGuiStyle
{
    // 字体缩放
    // - 简述：ImGui::GetFontSize() == FontSizeBase * (FontScaleMain * FontScaleDpi * 其他缩放因子)
    float FontSizeBase; // 应用外部全局因子之前的当前基础字体大小。使用 PushFont(NULL, size) 进行修改。使用 ImGui::GetFontSize() 获取缩放后的值。
    float FontScaleMain; // 主要全局缩放因子。可由应用程序设置一次，或开放给最终用户。
    float FontScaleDpi; // 来自视口/显示器内容缩放的额外全局缩放因子。在 docking 分支中：当启用 io.ConfigDpiScaleFonts 时，此值在更改显示器 DPI 时会自动覆盖。


    float Alpha; // 全局透明度，应用于 Dear ImGui 中的所有内容。
    float DisabledAlpha; // 由 BeginDisabled() 应用的额外透明度乘数。在当前 Alpha 值的基础上进行乘法运算。
    ImVec2 WindowPadding; // 窗口内的填充。
    float WindowRounding; // 窗口圆角的半径。设置为 0.0f 以获得矩形窗口。较大的值往往会导致各种伪影，不建议使用。
    float WindowBorderSize; // 窗口边框的厚度。通常设置为 0.0f 或 1.0f。（其他数值未经过充分测试，且会消耗更多 CPU/GPU 资源）。
    float WindowBorderHoverPadding; // 调整窗口大小时，边框内外侧的点击测试范围。同时也用于扩展悬停窗口的判定。通常该值应明显大于 WindowBorderSize，以便于用户触及边框。
    ImVec2 WindowMinSize; // 窗口的最小尺寸。这是一个全局设置。如果你想限制单个窗口的大小，请使用 SetNextWindowSizeConstraints()。
    ImVec2 WindowTitleAlign; // 标题栏文本的对齐方式。默认为 (0.0f, 0.5f)，即左对齐且垂直居中。
    ImGuiDir WindowMenuButtonPosition; // 标题栏中折叠/停靠按钮的位置（None/Left/Right）。默认为 ImGuiDir_Left。
    float ChildRounding; // 子窗口圆角半径。设置为 0.0f 以使用矩形窗口。
    float ChildBorderSize; // 子窗口边框厚度。通常设置为 0.0f 或 1.0f。（其他数值未经过充分测试，且会消耗更多 CPU/GPU 资源）。
    float PopupRounding; // 弹出窗口的圆角半径。（注意：提示框窗口使用的是 WindowRounding）
    float PopupBorderSize; // 弹出窗口/工具提示窗口周围边框的厚度。通常设置为 0.0f 或 1.0f。（其他数值未经过充分测试，且会消耗更多 CPU/GPU 资源）。
    ImVec2 FramePadding; // 框架矩形内的内边距（被大多数控件使用）。
    float FrameRounding; // 框架圆角的半径。设置为 0.0f 以获得矩形框架（被大多数控件使用）。
    float FrameBorderSize; // 框架周围边框的厚度。通常设置为 0.0f 或 1.0f。（其他数值未经过充分测试，且会消耗更多 CPU/GPU 资源）。
    ImVec2 ItemSpacing; // 控件/行之间的水平和垂直间距。
    ImVec2 ItemInnerSpacing; // 复合控件内部元素（例如滑块与其标签）之间的水平和垂直间距。
    ImVec2 CellPadding; // 表格单元格内的内边距。Cellpadding.x 在整个表格中是锁定的。CellPadding.y 可以在不同行之间更改。
    ImVec2 TouchExtraPadding; // 为触摸系统扩大响应边界框，以应对触摸位置不够精确的情况。遗憾的是，我们不对控件进行排序，因此重叠时的优先级始终赋予第一个控件。所以请不要将其增加得太大！
    float IndentSpacing; // 进入树节点等操作时的水平缩进。通常等于 (FontSize + FramePadding.x*2)。
    float ColumnsMinSpacing; // 两列之间的最小水平间距。建议大于 (FramePadding.x + 1)。
    float ScrollbarSize; // 垂直滚动条的宽度，水平滚动条的高度。
    float ScrollbarRounding; // 滚动条滑块圆角的半径。
    float ScrollbarPadding; // 滚动条滑块在其轨道内的内边距（两个轴向相同）。
    float GrabMinSize; // 滑块/滚动条抓取框的最小宽度/高度。
    float GrabRounding; // 抓取框圆角半径。设置为 0.0f 以使用矩形滑块。
    float LogSliderDeadzone; // 跨越零点的对数滑块在零点附近的死区大小（以像素为单位）。
    float ImageRounding; // Image() 调用的圆角半径。
    float ImageBorderSize; // Image() 调用周围的边框厚度。
    float TabRounding; // 选项卡上角的圆角半径。设置为 0.0f 以使用矩形选项卡。
    float TabBorderSize; // 选项卡周围的边框厚度。
    float TabMinWidthBase; // 标签页最小宽度，用于使标签页宽于其内容。TabBar 按钮不受此影响。
    float TabMinWidthShrink; // 缩减后的标签页最小宽度，在使用 ImGuiTabBarFlags_FittingPolicyMixed 策略时生效。
    float TabCloseButtonMinWidthSelected; // -1：始终可见。0.0f：悬停时可见。>0.0f：达到最小宽度且悬停时可见。
    float TabCloseButtonMinWidthUnselected; // -1：始终可见。0.0f：悬停时可见。>0.0f：达到最小宽度且悬停时可见。FLT_MAX：未选中时从不显示关闭按钮。
    float TabBarBorderSize; // 选项卡栏分隔线的厚度，该线采用活动选项卡的颜色以表示焦点。
    float TabBarOverlineSize; // 选项卡栏上划线的厚度，用于突出显示选中的选项卡。
    float TableAngledHeadersAngle; // 倾斜表头的角度（支持的范围为 -50.0f 度至 +50.0f 度）。
    ImVec2 TableAngledHeadersTextAlign; // 单元格内倾斜表头的对齐方式
    ImGuiTreeNodeFlags TreeLinesFlags; // 绘制连接 TreeNode 层级线条的默认方式。可选 ImGuiTreeNodeFlags_DrawLinesNone、ImGuiTreeNodeFlags_DrawLinesFull 或 ImGuiTreeNodeFlags_DrawLinesToNodes。
    float TreeLinesSize; // 使用 ImGuiTreeNodeFlags_DrawLines 时轮廓线的厚度。
    float TreeLinesRounding; // 连接子节点与垂直线的线条圆角半径。
    float DragDropTargetRounding; // 拖放目标框的圆角半径。
    float DragDropTargetBorderSize; // 拖放目标边框的厚度。
    float DragDropTargetPadding; // 拖放目标相对于实际项目尺寸的扩展大小。
    float ColorMarkerSize; // ColorEdit4() 以及使用 ImGuiSliderFlags_ColorMarkers 标志时的拖动条/滑块中 R/G/B/A 颜色标记的大小。
    ImGuiDir ColorButtonPosition; // ColorEdit4 控件中颜色按钮的位置（左侧/右侧）。默认为 ImGuiDir_Right。
    ImVec2 ButtonTextAlign; // 当按钮大于文本时，按钮文本的对齐方式。默认为 (0.5f, 0.5f)（居中）。
    ImVec2 SelectableTextAlign; // 可选项目（Selectable）文本的对齐方式。默认为 (0.0f, 0.0f)（左上对齐）。如果你想在同一行放置多个项目，通常保持左对齐很重要。
    float SeparatorTextBorderSize; // SeparatorText() 中边框的厚度
    ImVec2 SeparatorTextAlign; // 分隔线内文本的对齐方式。默认为 (0.0f, 0.5f)（左对齐，垂直居中）。
    ImVec2 SeparatorTextPadding; // 文本距离分隔线两端的水平偏移量 + 另一轴向的间距。通常取较小值。建议 .y 等于 FramePadding.y。
    ImVec2 DisplayWindowPadding; // 应用于常规窗口：当窗口移动到屏幕边缘附近时，强制保持可见的预留量。
    ImVec2 DisplaySafeAreaPadding; // 应用于所有窗口、菜单、弹出窗口、工具提示：避免显示内容的预留量。如果您无法看到屏幕边缘（例如在未配置缩放的电视上），请调整此项。
    float MouseCursorScale; // 软件渲染鼠标光标的缩放比例（当启用 io.MouseDrawCursor 时）。我们在此比例之上应用每台显示器的 DPI 缩放。未来可能会移除此项。
    bool AntiAliasedLines; // 启用线条/边框的抗锯齿。如果 CPU/GPU 资源非常紧张，请禁用。在帧开始时锁定（复制到 ImDrawList）。
    bool AntiAliasedLinesUseTex; // 在可能的情况下，启用基于纹理的线条/边框抗锯齿。需要后端使用双线性过滤（而非点过滤/最近邻过滤）进行渲染。在帧开始时锁定（复制到 ImDrawList）。
    bool AntiAliasedFill; // 启用填充形状（圆角矩形、圆形等）边缘的抗锯齿。如果 CPU/GPU 资源非常紧张，请禁用。在帧开始时锁定（复制到 ImDrawList）。
    float CurveTessellationTol; // 在使用 PathBezierCurveTo() 且未指定分段数时的细分容差。减小此值可获得高度细分的曲线（质量更高，多边形更多），增大此值则降低质量。
    float CircleTessellationMaxError; // 在使用 AddCircle()/AddCircleFilled() 或绘制未指定分段数的圆角矩形时允许的最大误差（以像素为单位）。减小此值可提高质量，但会增加几何图形数量。


    // 颜色
    ImVec4 Colors[ImGuiCol_COUNT];


    // 行为
    //（如果特定行为需要，可以在帧中途修改这些字段，这与 ImGuiIO 中的配置字段等不同）
    float HoverStationaryDelay; // IsItemHovered(ImGuiHoveredFlags_Stationary) 的延迟。判定鼠标为静止状态所需的时间。
    float HoverDelayShort; // IsItemHovered(ImGuiHoveredFlags_DelayShort) 的延迟。通常与 HoverStationaryDelay 配合使用。
    float HoverDelayNormal; // IsItemHovered(ImGuiHoveredFlags_DelayNormal) 的延迟。同上。
    ImGuiHoveredFlags HoverFlagsForTooltipMouse; // 使用鼠标时，调用 IsItemHovered(ImGuiHoveredFlags_ForTooltip) 或 BeginItemTooltip()/SetItemTooltip() 的默认标志。
    ImGuiHoveredFlags HoverFlagsForTooltipNav; // 使用键盘/手柄时，调用 IsItemHovered(ImGuiHoveredFlags_ForTooltip) 或 BeginItemTooltip()/SetItemTooltip() 的默认标志。


    // [内部]
    float _MainScale; // FIXME-WIP：参考缩放比例，由 ScaleAllSizes() 应用。
    float _NextFrameFontSizeBase; // 修复：在完成剩余工作之前的临时权宜之计。


    // 函数
    IMGUI_API ImGuiStyle();
    IMGUI_API void ScaleAllSizes(float scale_factor); // 缩放所有间距/填充/厚度值。不缩放字体。


    // 已废弃名称
#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
// TabMinWidthForCloseButton = TabCloseButtonMinWidthUnselected // 在 1.91.9 版本中重命名。
#endif
};


//-----------------------------------------------------------------------------
// [SECTION] ImGuiIO
//-----------------------------------------------------------------------------
// 使用此结构体向 Dear ImGui 传递大多数设置和输入/输出数据。
// 通过 ImGui::GetIO() 进行访问。常规用法请参阅 .cpp 文件中的“程序员指南（Programmer guide）”章节。
// 通常预期：
// - 初始化：后端和用户代码向 ImGuiIO 写入数据。
// - 主循环：后端写入 ImGuiIO，用户代码和 imgui 代码读取 ImGuiIO。
//-----------------------------------------------------------------------------
// 另请参阅 ImGui::GetPlatformIO() 和 ImGuiPlatformIO 结构体以获取 OS/平台相关功能：剪贴板、输入法（IME）等。
//-----------------------------------------------------------------------------


// [内部] IsKeyDown()、IsKeyPressed() 等函数使用的存储空间。
// 如果在 1.87 版本之前你使用了 io.KeysDownDuration[]（该成员曾被标记为内部使用），现在你应该使用 GetKeyData(key)->DownDuration，而**不是** io.KeysData[key]->DownDuration。
struct ImGuiKeyData
{
    bool Down; // 如果按键被按下则为 True
    float DownDuration; // 按键被按下的持续时间（<0.0f: 未按下, 0.0f: 刚刚按下, >0.0f: 已按下的时间）
    float DownDurationPrev; // 上一帧按键被按下的持续时间
    float AnalogValue; // 0.0f..1.0f，用于游戏手柄数值
};


struct ImGuiIO
{
    //------------------------------------------------------------------
    // 配置 // 默认值
    //------------------------------------------------------------------


    ImGuiConfigFlags ConfigFlags; // = 0 // 详见 ImGuiConfigFlags_ 枚举。由用户/应用程序设置。键盘/游戏手柄导航选项等。
    ImGuiBackendFlags BackendFlags; // = 0 // 详见 ImGuiBackendFlags_ 枚举。由后端（imgui_impl_xxx 文件或自定义后端）设置，用于传达后端支持的功能特性。
    ImVec2 DisplaySize; // <未设置> // 主显示区域大小，以像素为单位（== GetMainViewport()->Size）。可能每帧都会改变。
    ImVec2 DisplayFramebufferScale; // = (1, 1) // 主显示密度。用于视网膜（Retina）显示屏等窗口坐标与帧缓冲坐标不同的情况。这会影响字体密度，并最终传递给 ImDrawData::FramebufferScale。
    float DeltaTime; // = 1.0f/60.0f // 自上一帧以来经过的时间，以秒为单位。可能每帧都会改变。
    float IniSavingRate; // = 5.0f // 将位置/大小保存到 .ini 文件的最小间隔时间，单位为秒。
    const char* IniFilename; // = "imgui.ini" // .ini 文件的路径（重要：默认的 "imgui.ini" 是相对于当前工作目录的！）。设置为 NULL 可禁用自动加载/保存 .ini 文件，或者用于手动调用 LoadIniSettingsXXX() / SaveIniSettingsXXX() 函数。
    const char* LogFilename; // = "imgui_log.txt" // .log 文件的路径（当未指定文件时，作为 ImGui::LogToFile 的默认参数）。
    void* UserData; // = NULL // 存储您自定义的数据。


    // 字体系统
    ImFontAtlas* Fonts; // <auto> // 字体图集：加载、光栅化并将一个或多个字体打包到单个纹理中。
    ImFont* FontDefault; // = NULL // 在 NewFrame() 中使用的字体。设置为 NULL 则使用 Fonts->Fonts[0]。
    bool FontAllowUserScaling; // = false // 允许用户通过 Ctrl+滚轮 缩放单个窗口的文本。


    // 键盘/手柄导航选项
    bool ConfigNavSwapGamepadButtons; // = false // 交换“激活”与“取消”（A<>B）按钮，以匹配典型的“任天堂/日系风格”手柄布局。
    bool ConfigNavMoveSetMousePos; // = false // 方向或 Tab 键导航时会传送鼠标光标。在移动虚拟鼠标较为困难的电视/主机系统上可能很有用。将更新 io.MousePos 并设置 io.WantSetMousePos=true。
    bool ConfigNavCaptureKeyboard; // = true // 当 io.NavActive 启用时，设置 io.WantCaptureKeyboard。
    bool ConfigNavEscapeClearFocusItem; // = true // 按下 Escape 键可以清除焦点项目 + 导航 ID/高亮。如果希望始终保持高亮，请设置为 false。
    bool ConfigNavEscapeClearFocusWindow;// = false // 按下 Escape 键也可以清除焦点窗口（是 io.ConfigNavEscapeClearFocusItem 的超集）。
    bool ConfigNavCursorVisibleAuto; // = true // 使用方向导航键会使光标可见。鼠标点击则隐藏光标。
    bool ConfigNavCursorVisibleAlways; // = false // 导航光标始终可见。


    // 杂项选项
    //（您可以在“Demo->Configuration”中查看并交互所有选项）
    bool MouseDrawCursor; // = false // 请求 ImGui 为您绘制鼠标光标（如果您所在的平台没有鼠标光标）。由于后端实现频繁使用此变量，因此无法轻易将其重命名为“io.ConfigXXX”。
    bool ConfigMacOSXBehaviors; // = defined(__APPLE__) // 交换 Cmd<>Ctrl 键 + OS X 风格的文本编辑光标移动（使用 Alt 代替 Ctrl）、快捷键使用 Cmd/Super 代替 Ctrl、行/文本首尾跳转使用 Cmd+方向键代替 Home/End、双击按词选择而非选择全文、列表多选使用 Cmd/Super 代替 Ctrl。
    bool ConfigInputTrickleEventQueue; // = true // 启用输入队列滴流：在同一帧内提交的某些类型事件（例如按钮按下 + 释放）将分散到多个帧中，从而改善低帧率下的交互体验。
    bool ConfigInputTextCursorBlink; // = true // 启用光标闪烁（可选，因为某些用户认为这会分散注意力）。
    bool ConfigInputTextEnterKeepActive; // = false // [测试版] 按下回车键将保持项目激活状态并选中内容（仅限单行）。
    bool ConfigDragClickToInputText; // = false // [测试版] 允许通过简单的鼠标点击并释放（不移动）将 DragXXX 控件转换为文本输入。在没有键盘的设备上不建议开启。
    bool ConfigWindowsResizeFromEdges; // = true // 允许通过窗口边缘和左下角调整窗口大小。这需要 ImGuiBackendFlags_HasMouseCursors 以获得更好的鼠标光标反馈。（以前这是一个针对单个窗口的 ImGuiWindowFlags_ResizeFromAnySide 标志）
    bool ConfigWindowsMoveFromTitleBarOnly; // = false // 启用后仅允许通过点击标题栏来移动窗口。不适用于没有标题栏的窗口。
    bool ConfigWindowsCopyContentsWithCtrlC; // = false // [实验性] Ctrl+C 将当前焦点窗口的内容复制到剪贴板。实验性原因：(1) 嵌套的 Begin/End 对存在已知问题 (2) 文本输出质量参差不齐 (3) 文本输出是按提交顺序而非空间顺序排列的。
    bool ConfigScrollbarScrollByPage; // = true // 启用后，点击滚动条滑块以外的区域将逐页滚动。禁用时，点击将直接滚动至点击位置。启用时，Shift+点击可滚动至点击位置。
    float ConfigMemoryCompactTimer; // = 60.0f // 释放未使用的临时窗口/表格内存缓冲区的计时器（以秒为单位）。设置为 -1.0f 可禁用。


    // 输入行为 (Inputs Behaviors)
    //（其他变量，即那些预期在 UI 代码中进行调整的变量，已在 ImGuiStyle 中公开）
    float MouseDoubleClickTime; // = 0.30f // 双击判定时间，以秒为单位。
    float MouseDoubleClickMaxDist; // = 6.0f // 判定为双击的距离阈值，单位为像素。
    float MouseDragThreshold; // = 6.0f // 判定为拖拽行为前的距离阈值。
    float KeyRepeatDelay; // = 0.275f // 按住按键/按钮时，开始重复触发前的延迟时间，单位为秒（适用于处于重复模式的按钮等）。
    float KeyRepeatRate; // = 0.050f // 按住按键/按钮时，重复触发的频率，单位为秒。


    //------------------------------------------------------------------
    // 调试选项
    //------------------------------------------------------------------


    // 用于配置错误处理以及我们如何处理可恢复错误的选项 [实验性]
    // - 提供错误恢复是为了便于：
    // - 在编程错误（原生代码或脚本语言——后者往往有助于在运行时迭代代码）后进行恢复。
    // - 在运行异常处理程序或任何可能在检测到错误后跳过代码的错误处理流程后进行恢复。
    // - 错误恢复既不完美也不保证成功！这是一项旨在简化开发的功能。
    // - 你不应该在应用程序的正常运行过程中依赖它。
    // - 支持错误恢复的函数使用的是 IM_ASSERT_USER_ERROR() 而非 IM_ASSERT()。
    // - 按照设计，我们不允许错误恢复过程完全静默。必须勾选以下三个选项之一！
    // - 请务必确保在程序员席位上直接调用 imgui API 时，至少启用了断言（Asserts）或工具提示（Tooltips）！
    // 否则，这将严重阻碍你发现并纠正错误的能力！
    // 详见 https://github.com/ocornut/imgui/wiki/Error-Handling。
    // - 程序员席位：保留断言（默认），或禁用断言并保留错误工具提示（新功能，体验良好！）
    // - 非程序员席位：可以禁用断言，但要确保错误能够重新显现（工具提示、可见的日志条目、使用回调等）
    // - 错误/异常后的恢复：使用 ErrorRecoveryStoreState() 记录堆栈大小，禁用断言，设置日志回调（例如触发高级断点），使用 ErrorRecoveryTryToRecoverState() 进行恢复，最后还原设置。
    bool ConfigErrorRecovery; // = true // 启用错误恢复支持。如果禁用恢复，某些错误将无法被检测到并导致直接崩溃。
    bool ConfigErrorRecoveryEnableAssert; // = true // 启用可恢复错误时的断言。默认情况下，当从失败的 IM_ASSERT_USER_ERROR() 返回时调用 IM_ASSERT()。
    bool ConfigErrorRecoveryEnableDebugLog; // = true // 启用可恢复错误时的调试日志输出。
    bool ConfigErrorRecoveryEnableTooltip; // = true // 启用可恢复错误时的工具提示。该工具提示包含一种在断言被禁用时重新启用它们的方法。


    // 选项用于启用各种调试工具，这些工具会显示调用 IM_DEBUG_BREAK() 宏的按钮。
    // - 无论此项是否启用，项目拾取器（Item Picker）工具都将可用，以最大限度地提高其可发现性。
    // - 需要连接调试器，否则 IM_DEBUG_BREAK() 选项会导致应用程序崩溃。
    // 例如：在 Win32 上设置 io.ConfigDebugIsDebuggerPresent = ::IsDebuggerPresent()，或者参考 imgui_test_engine/imgui_te_utils.cpp 中的 ImOsIsDebuggerPresent() 以获取 Unix 兼容版本。
    bool ConfigDebugIsDebuggerPresent; // = false // 启用各种调用 IM_DEBUG_BREAK() 的工具。


    // 用于检测提交具有冲突/重复 ID 的控件的代码工具
    // - 代码应在循环中使用 PushID()/PopID()，或在相同标签的标识符后添加 "##xx"。
    // - 空标签（例如 Button("")）的 ID 与父级控件/节点相同。请改用 Button("##xx")！
    // - 详见常见问题解答 https://github.com/ocornut/imgui/blob/master/docs/FAQ.md#q-about-the-id-stack-system
    bool ConfigDebugHighlightIdConflicts;// = true // 当多个项目具有冲突的标识符（ID）时，高亮显示并弹出错误消息。
    bool ConfigDebugHighlightIdConflictsShowItemPicker;//=true // 在上述弹出窗口中显示“项目选择器（Item Picker）”按钮。


    // 用于测试 Begin/End 和 BeginChild/EndChild 行为正确性的工具。
    // - 目前 Begin()/End() 和 BeginChild()/EndChild() 必须始终成对调用，无论 BeginXXX() 的返回值为何。
    // - 这与其他 BeginXXX 函数不一致，给许多用户带来了困扰。
    // - 我们计划最终更新该 API。在此期间，我们提供了一些工具来方便检查用户代码的行为。
    bool ConfigDebugBeginReturnValueOnce;// = false // 首次调用 Begin()/BeginChild() 将返回 false。如果你不想遗漏窗口，则需要在应用程序启动时设置此项。
    bool ConfigDebugBeginReturnValueLoop;// = false // 部分 Begin()/BeginChild() 调用将返回 false。将循环遍历窗口深度并重复。建议用法：在主循环中添加 "io.ConfigDebugBeginReturnValue = io.KeyShift"，然后偶尔按下 SHIFT 键。运行期间窗口应当会出现闪烁。


    // 可选选项，用于禁用对 io.AddFocusEvent(false) 的处理。
    // - 当失去焦点导致输入数据被清除时，此选项可方便与调试器进行交互。
    // - 后端在失去焦点时可能还有其他副作用，因此这会减少副作用，但不一定能完全消除它们。
    bool ConfigDebugIgnoreFocusLoss; // = false // 忽略 io.AddFocusEvent(false)，从而在输入处理中不调用 io.ClearInputKeys()/io.ClearInputMouse()。


    // 审核 .ini 数据的选项
    bool ConfigDebugIniSettings; // = false // 保存 .ini 数据时附带额外注释（对停靠功能特别有用，但会降低保存速度）


    //------------------------------------------------------------------
    // 平台标识符
    //（imgui_impl_xxxx 后端文件会为你设置这些内容）
    //------------------------------------------------------------------


    // 如今这些内容通常存储在 ImGuiPlatformIO 中，但出于兼容性原因，我们仍将它们保留在这里。
    // 可选：平台/渲染器后端名称（仅供参考！将显示在“关于”窗口中）+ 供后端/包装器存储自定义数据的用户数据。
    const char* BackendPlatformName; // = NULL
    const char* BackendRendererName; // = NULL
    void* BackendPlatformUserData; // = NULL // 平台后端的自定义用户数据
    void* BackendRendererUserData; // = NULL // 渲染器后端的自定义用户数据
    void* BackendLanguageUserData; // = NULL // 非 C++ 编程语言后端的自定义用户数据


    //------------------------------------------------------------------
    // 输入 - 请在调用 NewFrame() 之前调用
    //------------------------------------------------------------------


    // 输入函数
    IMGUI_API void AddKeyEvent(ImGuiKey key, bool down); // 排队一个新的按键按下/释放事件。按键应当是“已转换”的（通常 ImGuiKey_A 对应终端用户用于输入字符 'A' 的物理按键）
    IMGUI_API void AddKeyAnalogEvent(ImGuiKey key, bool down, float v); // 为模拟量值（例如 ImGuiKey_Gamepad_ 系列值）排队一个新的按键按下/释放事件。死区（Dead-zones）应由后端处理。
    IMGUI_API void AddMousePosEvent(float x, float y); // 排队一个鼠标位置更新。使用 -FLT_MAX, -FLT_MAX 表示无鼠标（例如应用程序未聚焦且未被悬停）
    IMGUI_API void AddMouseButtonEvent(int button, bool down); // 将鼠标按键状态更改加入队列
    IMGUI_API void AddMouseWheelEvent(float wheel_x, float wheel_y); // 将鼠标滚轮更新加入队列。wheel_y<0: 向下滚动, wheel_y>0: 向上滚动, wheel_x<0: 向右滚动, wheel_x>0: 向左滚动。
    IMGUI_API void AddMouseSourceEvent(ImGuiMouseSource source); // 将鼠标来源更改（鼠标/触摸屏/笔）加入队列
    IMGUI_API void AddFocusEvent(bool focused); // 将应用程序获得/失去焦点的事件加入队列（通常基于操作系统/平台对窗口的聚焦状态）
    IMGUI_API void AddInputCharacter(unsigned int c); // 将一个新的字符输入排入队列
    IMGUI_API void AddInputCharacterUTF16(ImWchar16 c); // 将一个来自 UTF-16 字符的新字符输入排入队列，该字符可以是代理对（surrogate）
    IMGUI_API void AddInputCharactersUTF8(const char* str); // 将来自 UTF-8 字符串的新字符输入排入队列


    IMGUI_API void SetKeyEventNativeData(ImGuiKey key, int native_keycode, int native_scancode, int native_legacy_index = -1); // [可选] 为版本 <1.87 的旧版 IsKeyXXX() 函数指定原生索引，并指定原生键码（keycode）和扫描码（scancode）。
    IMGUI_API void SetAppAcceptingEvents(bool accepting_events); // 设置接受键盘/鼠标/文本事件的总标志（默认为 true）。如果你的原生对话框中断了应用程序循环/刷新，并且你希望在应用冻结时禁用事件排队，则此功能非常有用。
    IMGUI_API void ClearEventsQueue(); // 清除所有传入事件。
    IMGUI_API void ClearInputKeys(); // 清除当前键盘/手柄状态 + 当前帧文本输入缓冲区。相当于释放所有按键/按钮。
    IMGUI_API void ClearInputMouse(); // 清除当前鼠标状态。


    //------------------------------------------------------------------
    // 输出 - 由 NewFrame() 或 EndFrame()/Render() 更新
    // （当通过读取 io.WantCaptureMouse, io.WantCaptureKeyboard 标志来分发输入时，
    // 通常在调用 NewFrame() 之前使用它们的状态会更简单且更准确。详见 FAQ！）
    //------------------------------------------------------------------


    bool WantCaptureMouse; // 当 Dear ImGui 将使用鼠标输入时置为 true，在这种情况下请勿将输入分发给您的主游戏/应用程序（无论哪种情况，始终将鼠标输入传递给 imgui）。（例如：未点击的鼠标正悬停在 imgui 窗口上、控件处于激活状态、鼠标在 imgui 窗口上点击等）。
    bool WantCaptureKeyboard; // 当 Dear ImGui 将使用键盘输入时设为 true，在这种情况下请勿将输入分发给您的主游戏/应用程序（无论哪种情况，始终都要将键盘输入传递给 imgui）。（例如：InputText 处于活动状态，或某个 imgui 窗口处于聚焦状态且启用了导航等）。
    bool WantTextInput; // 移动端/主机端：当设为 true 时，您可以显示屏幕键盘。当 Dear ImGui 需要文本键盘输入时（例如当 InputText 控件处于活动状态时），会设置此项。
    bool WantSetMousePos; // MousePos 已被更改，后端应在下一帧重新定位鼠标。极少使用！仅在启用 io.ConfigNavMoveSetMousePos 时设置。
    bool WantSaveIniSettings; // 当启用手动 .ini 加载/保存（io.IniFilename == NULL）时，此项将被设置以通知您的应用程序可以调用 SaveIniSettingsToMemory() 并自行保存。重要提示：保存后请自行清除 io.WantSaveIniSettings！
    bool NavActive; // 当前允许键盘/手柄导航（将处理 ImGuiKey_NavXXX 事件） = 某个窗口处于聚焦状态且未使用 ImGuiWindowFlags_NoNavInputs 标志。
    bool NavVisible; // 键盘/手柄导航高亮显示可见且允许（将处理 ImGuiKey_NavXXX 事件）。
    float Framerate; // 应用程序帧率的估算值（基于 io.DeltaTime 的 60 帧滚动平均值），单位为帧/秒。仅为方便起见提供。运行缓慢的应用程序可能不希望使用移动平均值，或者可能希望偶尔重置底层缓冲区。
    int MetricsRenderVertices; // 上一次调用 Render() 期间输出的顶点数
    int MetricsRenderIndices; // 上一次调用 Render() 期间输出的索引数 = 三角形数量 * 3
    int MetricsRenderWindows; // 可见窗口的数量
    int MetricsActiveWindows; // 活动窗口的数量
    ImVec2 MouseDelta; // 鼠标增量。请注意，如果当前或前一个位置无效 (-FLT_MAX, -FLT_MAX)，则此值为零，因此消失/重新出现的鼠标不会产生巨大的增量。


    //------------------------------------------------------------------
    // [内部] Dear ImGui 将维护这些字段。不保证向前兼容性！
    //------------------------------------------------------------------


    ImGuiContext* Ctx; // 父级 UI 上下文（需要由父级显式设置）。


    // 主要输入状态
    // （此区块以前由后端写入，自 1.87 版本起，最好不要直接写入这些字段，请改为调用上方的 AddXXX 函数）
    //（读取这些变量是安全的，因为它们极不可能发生变动）
    ImVec2 MousePos; // 鼠标位置，以像素为单位。如果鼠标不可用（在另一个屏幕上等），则设置为 ImVec2(-FLT_MAX, -FLT_MAX)
    bool MouseDown[5]; // 鼠标按钮：0=左键，1=右键，2=中键 + 其他 (ImGuiMouseButton_COUNT == 5)。Dear ImGui 主要使用左右键。其他按钮允许我们跟踪鼠标是否正被您的应用程序使用，并通过 IsMouse** API 方便用户调用。
    float MouseWheel; // 鼠标垂直滚轮：1 个单位大约滚动 5 行文本。>0 向上滚动，<0 向下滚动。按住 Shift 键可将垂直滚动转为水平滚动。
    float MouseWheelH; // 鼠标水平滚轮。>0 向左滚动，<0 向右滚动。大多数用户的鼠标没有水平滚轮，并非所有后端都会填充此项。
    ImGuiMouseSource MouseSource; // 鼠标实际输入外设（鼠标/触摸屏/手写笔）。
    bool KeyCtrl; // 键盘修饰键按下：Ctrl (非 macOS)，Cmd (macOS)
    bool KeyShift; // 键盘修饰键按下：Shift
    bool KeyAlt; // 键盘修饰键按下状态：Alt
    bool KeySuper; // 键盘修饰键按下状态：Windows/Super (非 macOS), Ctrl (macOS)


    // 根据上述数据和 IO 函数调用维护的其他状态
    ImGuiKeyChord KeyMods; // 按键修饰键标志（包含 ImGuiMod_Ctrl/ImGuiMod_Shift/ImGuiMod_Alt/ImGuiMod_Super 中的任意标志，与 io.KeyCtrl/KeyShift/KeyAlt/KeySuper 相同，但合并为标志位）。只读，由 NewFrame() 更新。
    ImGuiKeyData KeysData[ImGuiKey_NamedKey_COUNT];// 所有已知按键的状态。必须使用 'key - ImGuiKey_NamedKey_BEGIN' 作为索引。请使用 IsKeyXXX() 函数进行访问。
    bool WantCaptureMouseUnlessPopupClose; // WantCaptureMouse 的替代方案：当点击空白区域预期会关闭弹出窗口时，(WantCaptureMouse == true && WantCaptureMouseUnlessPopupClose == false)。
    ImVec2 MousePosPrev; // 上一次鼠标位置（注意，如果任一位置无效，MouseDelta 不一定等于 MousePos - MousePosPrev）
    ImVec2 MouseClickedPos[5]; // 点击时的位置
    double MouseClickedTime[5]; // 上次点击的时间（用于计算双击）
    bool MouseClicked[5]; // 鼠标按键状态从“未按下”变为“按下”（等同于 MouseClickedCount[x] != 0）
    bool MouseDoubleClicked[5]; // 鼠标按键是否被双击？（等同于 MouseClickedCount[x] == 2）
    ImU16 MouseClickedCount[5]; // 当状态从“未按下”变为“按下”时：== 0 (未点击), == 1 (等同于 MouseClicked[]), == 2 (双击), == 3 (三击) 等。
    ImU16 MouseClickedLastCount[5]; // 连续点击次数。在鼠标松开后保持有效。在下一次点击完成后重置。
    bool MouseReleased[5]; // 鼠标按键状态从“按下”变为“未按下”。
    double MouseReleasedTime[5]; // 上次松开的时间（很少使用！但在尝试区分单击与双击时，用于处理延迟单击非常有用）。
    bool MouseDownOwned[5]; // 追踪按键是否在 Dear ImGui 窗口内点击，或在被弹窗阻挡的空白区域点击。如果点击起始于 ImGui 边界之外，我们不会向应用程序请求鼠标捕获。
    bool MouseDownOwnedUnlessPopupClose[5]; // 追踪鼠标按键是否在 Dear ImGui 窗口内点击。
    bool MouseWheelRequestAxisSwap; // 在非 Mac 系统上，按住 Shift 键会请求将垂直滚轮（WheelY）转换为水平滚轮（WheelX）事件。在 Mac 系统上，这已由系统强制执行。
    bool MouseCtrlLeftAsRightClick; // (OSX) 当当前的点击是 Ctrl+左键点击并产生了一个模拟右键点击时，设为 true。
    float MouseDownDuration[5]; // 鼠标按键按下的持续时间（0.0f 表示刚刚点击）
    float MouseDownDurationPrev[5]; // 鼠标按键上次持续按下的时间
    float MouseDragMaxDistanceSqr[5]; // 鼠标从点击点移动的最大距离的平方（用于移动阈值）
    float PenPressure; // 触摸/笔压（0.0f 到 1.0f，仅当 MouseDown[0] == true 时应 >0.0f）。目前 Dear ImGui 尚未使用的辅助存储。
    bool AppFocusLost; // 仅通过 AddFocusEvent() 修改
    bool AppAcceptingEvents; // 仅通过 SetAppAcceptingEvents() 修改
    ImWchar16 InputQueueSurrogate; // 用于 AddInputCharacterUTF16()
    ImVector<ImWchar> InputQueueCharacters; // 输入字符队列（由平台后端获取）。使用 AddInputCharacter() 辅助函数填充。


    // 旧版遗留：在 1.87 版本之前，我们要求后端在初始化期间填充 io.KeyMap[]（imgui 到原生键码的映射），并在每一帧填充 io.KeysDown[]（原生索引）。
    // 这目前仍作为一项遗留功能被临时支持。然而，现在更推荐的方案是由后端调用 io.AddKeyEvent()。
    // 旧版 (<1.87): ImGui::IsKeyPressed(ImGui::GetIO().KeyMap[ImGuiKey_Space]) --> 新版 (1.87+) ImGui::IsKeyPressed(ImGuiKey_Space)
    // 旧版 (<1.87): ImGui::IsKeyPressed(MYPLATFORM_KEY_SPACE) --> 新版 (1.87+) ImGui::IsKeyPressed(ImGuiKey_Space)
    // 详情请参阅 https://github.com/ocornut/imgui/issues/4921。
    //int KeyMap[ImGuiKey_COUNT]; // [旧版] 输入：KeysDown[512] 条目数组的索引映射，代表您的“原生”键盘状态。前 512 个现在已不再使用，应保持为零。旧版后端将使用始终大于 512 的 ImGuiKey_ 索引写入 KeyMap[]。
    //bool KeysDown[ImGuiKey_COUNT]; // [旧版] 输入：已按下的键盘按键（理想情况下保留您的引擎访问键盘按键的“原生”顺序，以便您可以使用自己的按键定义/枚举）。此数组以前的大小为 [512]。现在改为 ImGuiKey_COUNT，以允许旧版的 io.KeysDown[GetKeyIndex(...)] 在不溢出的情况下工作。
    //float NavInputs[ImGuiNavInput_COUNT]; // [旧版] 自 1.88 起，NavInputs[] 已被移除。1.60 到 1.86 版本的后端将无法编译。请通过 io.AddKeyEvent() 和 ImGuiKey_GamepadXXX 枚举提供手柄输入。
    //void* ImeWindowHandle; // [在 1.87 中废弃] 请改为设置 ImGuiViewport::PlatformHandleRaw。将其设置为您的 HWND 以获取自动 IME 光标定位。


#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    float FontGlobalScale; // 在 1.92 版本（2025 年 6 月）中，io.FontGlobalScale 已移至 style.FontScaleMain


    // 遗留问题：在 1.91.1 版本之前，剪贴板函数存储在 ImGuiIO 中，而非 ImGuiPlatformIO。
    // 由于这将影响所有使用自定义引擎/后端的开发者，我们提供了适当的旧版重定向（后续将废弃）。
    const char* (*GetClipboardTextFn)(void* user_data);
    void (*SetClipboardTextFn)(void* user_data, const char* text);
    void* ClipboardUserData;


    //void ClearInputCharacters() { InputQueueCharacters.resize(0); } // [在 1.89.8 版本中已废弃] 清除当前帧的文本输入缓冲区。现在已包含在 ClearInputKeys() 中。移除此函数是因为其含义模糊/具有误导性，且在存在更高级别输入队列的情况下，使用它通常是不正确的。
#endif


    IMGUI_API ImGuiIO();
};


//-----------------------------------------------------------------------------
// [SECTION] 杂项数据结构 (ImGuiInputTextCallbackData, ImGuiSizeCallbackData, ImGuiPayload)
//-----------------------------------------------------------------------------


// InputText() 的共享状态，当使用 ImGuiInputTextFlags_Callback* 标志时，作为参数传递给您的回调函数。
// 回调函数默认应返回 0。
// 回调函数（请参考 ImGuiInputTextFlags_ 声明中的标志名称及注释以获取更多详情）
// - ImGuiInputTextFlags_CallbackEdit：缓冲区编辑时的回调。注意，InputText() 在编辑时已经会返回 true，且你始终可以使用 IsItemEdited()。该回调在焦点处于激活状态时操作底层缓冲区非常有用。
// - ImGuiInputTextFlags_CallbackAlways：每次迭代时的回调
// - ImGuiInputTextFlags_CallbackCompletion：按下 TAB 键时的回调
// - ImGuiInputTextFlags_CallbackHistory: 按下上/下方向键时的回调
// - ImGuiInputTextFlags_CallbackCharFilter: 字符输入时的回调，用于替换或丢弃字符。修改 'EventChar' 以替换或丢弃，或在回调中返回 1 以丢弃。
// - ImGuiInputTextFlags_CallbackResize: 缓冲区容量变更请求（超过 'buf_size' 参数值）时的回调，允许字符串增长。
struct ImGuiInputTextCallbackData
{
    ImGuiContext* Ctx; // 父级 UI 上下文
    ImGuiInputTextFlags EventFlag; // 属于 ImGuiInputTextFlags_Callback* 之一 // 只读
    ImGuiInputTextFlags Flags; // 用户传递给 InputText() 的参数 // 只读
    void* UserData; // 用户传递给 InputText() 的数据 // 只读
    ImGuiID ID; // 控件 ID // 只读


    // 不同回调事件的参数
    // - 在 Resize（调整大小）回调期间，Buf 将与您的输入缓冲区相同。
    // - 然而，在 Completion（补全）/ History（历史）/ Always（总是）回调期间，Buf 始终指向我们自己的内部数据（它与您的缓冲区不同）！对其进行的更改将在回调结束后不久反映到您的缓冲区中。
    // - 若要在回调中修改文本缓冲区，建议优先使用 InsertChars() / DeleteChars() 函数。如有必要，InsertChars() 会自动处理并调用调整大小（resize）的回调。
    // - 如果你确定你的编辑操作不会改变底层缓冲区的分配大小，可以直接修改 'Buf[]' 的内容。你需要相应地更新 'BufTextLen'（需满足 0 <= BufTextLen < BufSize），并将 'BufDirty' 设置为 true，以便 InputText 更新其内部状态。
    ImGuiKey EventKey; // 按下的按键 (Up/Down/TAB) // 只读 // [Completion,History]
    ImWchar EventChar; // 输入的字符 // 读写 // [CharFilter] 可替换为另一个字符，或设为 0 以丢弃。返回 1 等同于设置 EventChar=0；
    bool EventActivated; // 输入框刚刚被激活 // 只读 // [始终有效]
    bool BufDirty; // 如果修改了 Buf/BufTextLen，请设置此项！ // 写入 // [补全, 历史记录, 始终有效]
    char* Buf; // 文本缓冲区 // 读写 // [调整大小] 可以更换指针 / [补全, 历史记录, 始终有效] 仅写入指向的数据，不要更换实际指针！
    int BufTextLen; // 文本长度（字节数） // 读写 // [调整大小, 补全, 历史记录, 始终有效] 不包括 0 终止符。在 C 语言中：== strlen(some_text)，在 C++ 语言中：string.length()
    int BufSize; // 缓冲区大小（字节）= 容量+1 // 只读 // [Resize,Completion,History,Always] 包含零终止符存储空间。在 C 语言中：== ARRAYSIZE(my_char_array)，在 C++ 语言中：string.capacity()+1
    int CursorPos; // // 读写 // [Completion,History,Always]
    int SelectionStart; // // 读写 // [Completion,History,Always] 无选中内容时 == SelectionEnd
    int SelectionEnd; // // 读写 // [Completion,History,Always]


    // 文本操作辅助函数。
    // 使用这些函数可以受益于 CallbackResize 行为。调用这些函数会重置选择状态。
    IMGUI_API ImGuiInputTextCallbackData();
    IMGUI_API void DeleteChars(int pos, int bytes_count);
    IMGUI_API void InsertChars(int pos, const char* text, const char* text_end = NULL);
    void SelectAll() { SelectionStart = 0; CursorPos = SelectionEnd = BufTextLen; }
    void SetSelection(int s, int e) { IM_ASSERT(s >= 0 && s <= BufTextLen); IM_ASSERT(e >= 0 && e <= BufTextLen); SelectionStart = s; CursorPos = SelectionEnd = e; }
    void ClearSelection() { SelectionStart = SelectionEnd = BufTextLen; }
    bool HasSelection() const { return SelectionStart != SelectionEnd; }
};


// 调整大小的回调数据，用于应用自定义约束。通过 SetNextWindowSizeConstraints() 启用。回调将在下一次 Begin() 期间调用。
// 注意：对于每个轴上的基本最小/最大尺寸约束，您不需要使用回调！SetNextWindowSizeConstraints() 的参数已经足够了。
struct ImGuiSizeCallbackData
{
    void* UserData; // 只读。用户传递给 SetNextWindowSizeConstraints() 的数据。通常在此处存储整数或浮点数（需要使用 reinterpret_cast<>）。
    ImVec2 Pos; // 只读。窗口位置，供参考。
    ImVec2 CurrentSize; // 只读。当前窗口大小。
    ImVec2 DesiredSize; // 读写。基于用户鼠标位置的期望大小。通过写入此字段来限制调整大小。
};


// 拖放操作的数据负载：AcceptDragDropPayload(), GetDragDropPayload()
struct ImGuiPayload
{
    // 成员变量
    void* Data; // 数据（由 dear imgui 复制并持有）
    int DataSize; // 数据大小


    // [内部]
    ImGuiID SourceId; // 源项目 ID
    ImGuiID SourceParentId; // 源父级 ID（如果可用）
    int DataFrameCount; // 数据时间戳
    char DataType[32 + 1]; // 数据类型标签（用户提供的短字符串，最多 32 个字符）
    bool Preview; // 当 AcceptDragDropPayload() 被调用且鼠标一直悬停在目标项目上时设置（注：用于处理重叠的拖放目标）
    bool Delivery; // 当 AcceptDragDropPayload() 被调用且鼠标按键在目标项目上释放时设置。


    ImGuiPayload() { Clear(); }
    void Clear() { SourceId = SourceParentId = 0; Data = NULL; DataSize = 0; memset(DataType, 0, sizeof(DataType)); DataFrameCount = -1; Preview = Delivery = false; }
    bool IsDataType(const char* type) const { return DataFrameCount != -1 && strcmp(type, DataType) == 0; }
    bool IsPreview() const { return Preview; }
    bool IsDelivery() const { return Delivery; }
};


//-----------------------------------------------------------------------------
// [章节] 辅助类 (ImGuiOnceUponAFrame, ImGuiTextFilter, ImGuiTextBuffer, ImGuiStorage, ImGuiListClipper, 数学运算符, ImColor)
//-----------------------------------------------------------------------------


// 辅助：Unicode 定义
#define IM_UNICODE_CODEPOINT_INVALID 0xFFFD // 无效的 Unicode 码点（标准值）。
#ifdef IMGUI_USE_WCHAR32
#define IM_UNICODE_CODEPOINT_MAX 0x10FFFF // 此版本支持的最大 Unicode 码点。
#else
#define IM_UNICODE_CODEPOINT_MAX 0xFFFF // 此版本支持的最大 Unicode 码点。
#endif


// 辅助说明：每帧最多执行一次代码块。如果你想在每帧运行多次的深层嵌套代码中快速创建 UI，这会非常方便。
// 用法：static ImGuiOnceUponAFrame oaf; if (oaf) ImGui::Text("这行代码每帧只会被调用一次");
struct ImGuiOnceUponAFrame
{
    ImGuiOnceUponAFrame() { RefFrame = -1; }
    mutable int RefFrame;
    operator bool() const { int current_frame = ImGui::GetFrameCount(); if (RefFrame == current_frame) return false; RefFrame = current_frame; return true; }
};


// 辅助工具：解析并应用文本过滤器。格式为 "aaaaa[,bbbb][,ccccc]"
struct ImGuiTextFilter
{
    IMGUI_API ImGuiTextFilter(const char* default_filter = "");
    IMGUI_API bool Draw(const char* label = "Filter (inc,-exc)", float width = 0.0f); // 调用 InputText+Build 的辅助函数
    IMGUI_API bool PassFilter(const char* text, const char* text_end = NULL) const;
    IMGUI_API void Build();
    void Clear() { InputBuf[0] = 0; Build(); }
    bool IsActive() const { return !Filters.empty(); }


    // [内部]
    struct ImGuiTextRange
    {
        const char* b;
        const char* e;


        ImGuiTextRange() { b = e = NULL; }
        ImGuiTextRange(const char* _b, const char* _e) { b = _b; e = _e; }
        bool empty() const { return b == e; }
        IMGUI_API void split(char separator, ImVector<ImGuiTextRange>* out) const;
    };
    char InputBuf[256];
    ImVector<ImGuiTextRange>Filters;
    int CountGrep;
};


// 辅助类：用于日志记录/文本累积的可扩容文本缓冲区
// (该类也可被称为 'ImGuiTextBuilder' / 'ImGuiStringBuilder')
struct ImGuiTextBuffer
{
    ImVector<char> Buf;
    IMGUI_API static char EmptyString[1];


    ImGuiTextBuffer() {}
    inline char operator[](int i) const { IM_ASSERT(Buf.Data != NULL); return Buf.Data[i]; }
    const char* begin() const { return Buf.Data ? &Buf.front() : EmptyString; }
    const char* end() const { return Buf.Data ? &Buf.back() : EmptyString; } // Buf 以零终止，因此 end() 将指向零终止符
    int size() const { return Buf.Size ? Buf.Size - 1 : 0; }
    bool empty() const { return Buf.Size <= 1; }
    void clear() { Buf.clear(); }
    void resize(int size) { if (Buf.Size > size) Buf.Data[size] = 0; Buf.resize(size ? size + 1 : 0, 0); } // 类似于 ImVector 的 resize(0)：清空字符串但不释放缓冲区。
    void reserve(int capacity) { Buf.reserve(capacity); }
    const char* c_str() const { return Buf.Data ? Buf.Data : EmptyString; }
    IMGUI_API void append(const char* str, const char* str_end = NULL);
    IMGUI_API void appendf(const char* fmt, ...) IM_FMTARGS(2);
    IMGUI_API void appendfv(const char* fmt, va_list args) IM_FMTLIST(2);
};


// [内部] ImGuiStorage 的 键+值 对
struct ImGuiStoragePair
{
    ImGuiID key;
    union { int val_i; float val_f; void* val_p; };
    ImGuiStoragePair(ImGuiID _key, int _val) { key = _key; val_i = _val; }
    ImGuiStoragePair(ImGuiID _key, float _val) { key = _key; val_f = _val; }
    ImGuiStoragePair(ImGuiID _key, void* _val) { key = _key; val_p = _val; }
};


// 辅助类：键->值 存储 (Key->Value storage)
// 通常你不需要担心这个，因为每个窗口内部都持有一个存储实例。
// 我们使用它来存储诸如树节点的折叠状态（整数 0/1）等信息。
// 该功能针对高效查找（在连续缓冲区中进行二分查找）和低频插入（通常与用户交互相关，即每帧最多一次）进行了优化。
// 您可以将其用作临时值的自定义用户存储。在以下情况下，您可以声明自己的存储，例如：
// - 您想要操作界面中特定子树的展开/折叠状态（树节点使用 Int 0/1 来存储其状态）。
// - 您想要轻松存储自定义调试数据，而无需在代码中添加或修改结构（这可能效率不高，但很方便）。
// 类型信息不会被存储，因此您需要自行确保 Key 不会与不同类型发生冲突。
struct ImGuiStorage
{
    // [内部]
    ImVector<ImGuiStoragePair> Data;


    // - Get***() 函数用于查找键值对，绝不会进行添加或分配。键值对已排序，因此查询复杂度为 O(log N)。
    // - Set***() 函数用于查找键值对，如果缺失则按需插入。
    // - 有序插入的代价较高，但只需支付一次。在典型的帧中，不应需要插入任何新的键值对。
    void Clear() { Data.clear(); }
    IMGUI_API int GetInt(ImGuiID key, int default_val = 0) const;
    IMGUI_API void SetInt(ImGuiID key, int val);
    IMGUI_API bool GetBool(ImGuiID key, bool default_val = false) const;
    IMGUI_API void SetBool(ImGuiID key, bool val);
    IMGUI_API float GetFloat(ImGuiID key, float default_val = 0.0f) const;
    IMGUI_API void SetFloat(ImGuiID key, float val);
    IMGUI_API void* GetVoidPtr(ImGuiID key) const; // 默认值为 NULL
    IMGUI_API void SetVoidPtr(ImGuiID key, void* val);


    // - Get***Ref() 函数用于查找键值对，如果不存在则按需插入，并返回指针。如果你打算进行“获取+设置”操作，这会非常有用。
    // - 引用仅在向存储中添加新值之前有效。调用 Set***() 函数或 Get***Ref() 函数会使之前的指针失效。
    // - 一个典型的使用场景是方便快速开发（例如，在无法修改现有结构体的实时“编辑并继续”会话期间添加存储）。
    // float* pvar = ImGui::GetFloatRef(key); ImGui::SliderFloat("var", pvar, 0, 100.0f); some_var += *pvar;
    IMGUI_API int* GetIntRef(ImGuiID key, int default_val = 0);
    IMGUI_API bool* GetBoolRef(ImGuiID key, bool default_val = false);
    IMGUI_API float* GetFloatRef(ImGuiID key, float default_val = 0.0f);
    IMGUI_API void** GetVoidPtrRef(ImGuiID key, void* default_val = NULL);


    进阶用法：为了更快速地完整重建存储（而非增量重建），您可以添加所有内容后进行一次性排序。
        IMGUI_API void BuildSortByKey();
    已废弃：如果您确定存储的仅为整数（例如打开 / 关闭所有树节点），可在您自己的存储上使用。
        IMGUI_API void SetAllInt(int val);


#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    //typedef ::ImGuiStoragePair ImGuiStoragePair; // 1.90.8: 将类型移至结构体外
#endif
};


// ImGuiListClipper 的标志（目前尚未在函数调用中完全公开：未来的重构可能会将其添加到 ImGuiListClipper::Begin 的等效函数中）
enum ImGuiListClipperFlags_
{
    ImGuiListClipperFlags_None = 0,
    ImGuiListClipperFlags_NoSetTableRowCounters = 1 << 0, // [内部] 禁用修改表格行计数器。避免假设 1 个 clipper 项目等于 1 个表格行。
};


// 辅助类：手动裁剪大量列表项。
// 如果你有大量等间距的项目，并且可以对列表进行随机访问，你可以进行粗略的
// 基于可见性的裁剪，仅提交处于视图内的项目。
// 裁剪器计算可见项目的范围，并移动光标以补偿我们跳过的不可见项目。
//（Dear ImGui 已经会根据项目的边界进行裁剪，但：它通常需要先对项目进行布局才能做到这一点，而且通常
// 获取/提交你自己的数据会产生额外的开销。使用 ImGuiListClipper 进行粗略裁剪可以让你轻松地
// 即使处理包含数万个项目的列表也能轻松扩展，不会出现问题）
// 用法：
// ImGuiListClipper clipper;
// clipper.Begin(1000); // 我们有 1000 个等间距的元素。
// while (clipper.Step())
// for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
// ImGui::Text("line number %d", i);
// 通常发生的情况是：
// - Clipper 允许您处理第一个元素（DisplayStart = 0, DisplayEnd = 1），无论其是否可见。
// - 用户代码提交该元素。
// - 分割器（Clipper）可以测量第一个元素的高度。
// - 分割器根据当前的裁剪矩形计算实际需要显示的元素范围，并将光标置于第一个可见元素之前。
// - 用户代码提交可见元素。
// - 分割器还处理与键盘/手柄导航、换行等相关的各种细节。
struct ImGuiListClipper
{
    ImGuiContext* Ctx; // 父级 UI 上下文
    int DisplayStart; // 要显示的第一个项目，每次调用 Step() 时更新
    int DisplayEnd; // 要显示的项目结束索引（不包含）
    int ItemsCount; // [内部] 项目数量
    float ItemsHeight; // [内部] 项目高度，在第一步和项目提交后可计算得出
    double StartPosY; // [内部] 执行 Begin() 时或表格冻结行全部处理后的光标位置
    double StartSeekOffsetY; // [内部] 用于处理表格中的冻结行以及超大窗口中初始精度的损失
    void* TempData; // [内部] 内部数据
    ImGuiListClipperFlags Flags; // [内部] 标志，目前尚未完全公开。


    // items_count: 如果你不知道有多少个项目，请使用 INT_MAX（在这种情况下，光标在最后一步不会前进，如果需要，你可以手动调用 SeekCursorForItem()）
    // items_height: 使用 -1.0f 以在第一步自动计算。否则请传入项目之间的距离，通常为 GetTextLineHeightWithSpacing() 或 GetFrameHeightWithSpacing()。
    IMGUI_API ImGuiListClipper();
    IMGUI_API ~ImGuiListClipper();
    IMGUI_API void Begin(int items_count, float items_height = -1.0f);
    IMGUI_API void End(); // 在 Step() 最后一次返回 false 时会自动调用。
    IMGUI_API bool Step(); // 循环调用直到返回 false。届时 DisplayStart/DisplayEnd 字段将被设置，您可以处理/绘制这些项目。


    // 如果您需要确保某段范围内的项目无论是否可见都不被裁剪，请在第一次调用 Step() *之前* 调用 IncludeItemByIndex() 或 IncludeItemsByIndex()。
    // （由于某些项目的对齐或填充原因，显示范围的两端可能会多包含一个额外的项目）。
    inline void IncludeItemByIndex(int item_index) { IncludeItemsByIndex(item_index, item_index + 1); }
    IMGUI_API void IncludeItemsByIndex(int item_begin, int item_end); // item_end 是开区间，例如使用 (42, 42+1) 可确保第 42 项永远不会被裁剪。


    // 将光标移向指定项目。这在步进（stepping）过程中会被自动调用。
    // - 调用此函数的唯一原因是：如果你预先不知道项目总数，可以使用 ImGuiListClipper::Begin(INT_MAX)。
    // - 在这种情况下，当所有步骤完成后，你需要调用 SeekCursorForItem(item_count)。
    IMGUI_API void SeekCursorForItem(int item_index);


#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    //inline void IncludeRangeByIndices(int item_begin, int item_end) { IncludeItemsByIndex(item_begin, item_end); } // [在 1.89.9 版本中重命名]
    //inline void ForceDisplayRangeByIndices(int item_begin, int item_end) { IncludeItemsByIndex(item_begin, item_end); } // [在 1.89.6 版本中重命名]
    //inline ImGuiListClipper(int items_count, float items_height = -1.0f) { memset(this, 0, sizeof(*this)); ItemsCount = -1; Begin(items_count, items_height); } // [在 1.79 版本中移除]
#endif
};


// 辅助类：ImVec2/ImVec4 运算符
// - 重要的是，我们默认保持这些功能禁用，以免它们泄露到用户空间。
// - 这是为了允许用户在 ImVec2/ImVec4 与其自定义类型之间启用隐式转换运算符（通过在 imconfig.h 中使用 IM_VEC2_CLASS_EXTRA）
// - 在包含此文件之前（或在 imconfig.h 中）添加 '#define IMGUI_DEFINE_MATH_OPERATORS'，即可使用为 ImVec2 和 ImVec4 提供的便利数学运算符。
// - 我们特意提供了 ImVec2*float 但没有提供 float*ImVec2：这种情况足够少见，且我们希望减少用户可能出错的范围。
#ifdef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS_IMPLEMENTED
IM_MSVC_RUNTIME_CHECKS_OFF
// ImVec2 运算符
inline ImVec2 operator*(const ImVec2& lhs, const float rhs) { return ImVec2(lhs.x * rhs, lhs.y * rhs); }
inline ImVec2 operator/(const ImVec2& lhs, const float rhs) { return ImVec2(lhs.x / rhs, lhs.y / rhs); }
inline ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y); }
inline ImVec2 operator-(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x - rhs.x, lhs.y - rhs.y); }
inline ImVec2 operator*(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x * rhs.x, lhs.y * rhs.y); }
inline ImVec2 operator/(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x / rhs.x, lhs.y / rhs.y); }
inline ImVec2 operator-(const ImVec2& lhs) { return ImVec2(-lhs.x, -lhs.y); }
inline ImVec2& operator*=(ImVec2& lhs, const float rhs) { lhs.x *= rhs; lhs.y *= rhs; return lhs; }
inline ImVec2& operator/=(ImVec2& lhs, const float rhs) { lhs.x /= rhs; lhs.y /= rhs; return lhs; }
inline ImVec2& operator+=(ImVec2& lhs, const ImVec2& rhs) { lhs.x += rhs.x; lhs.y += rhs.y; return lhs; }
inline ImVec2& operator-=(ImVec2& lhs, const ImVec2& rhs) { lhs.x -= rhs.x; lhs.y -= rhs.y; return lhs; }
inline ImVec2& operator*=(ImVec2& lhs, const ImVec2& rhs) { lhs.x *= rhs.x; lhs.y *= rhs.y; return lhs; }
inline ImVec2& operator/=(ImVec2& lhs, const ImVec2& rhs) { lhs.x /= rhs.x; lhs.y /= rhs.y; return lhs; }
inline bool operator==(const ImVec2& lhs, const ImVec2& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; }
inline bool operator!=(const ImVec2& lhs, const ImVec2& rhs) { return lhs.x != rhs.x || lhs.y != rhs.y; }
// ImVec4 运算符
inline ImVec4 operator*(const ImVec4& lhs, const float rhs) { return ImVec4(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs); }
inline ImVec4 operator/(const ImVec4& lhs, const float rhs) { return ImVec4(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs, lhs.w / rhs); }
inline ImVec4 operator+(const ImVec4& lhs, const ImVec4& rhs) { return ImVec4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w); }
inline ImVec4 operator-(const ImVec4& lhs, const ImVec4& rhs) { return ImVec4(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w); }
inline ImVec4 operator*(const ImVec4& lhs, const ImVec4& rhs) { return ImVec4(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w); }
inline ImVec4 operator/(const ImVec4& lhs, const ImVec4& rhs) { return ImVec4(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z, lhs.w / rhs.w); }
inline ImVec4 operator-(const ImVec4& lhs) { return ImVec4(-lhs.x, -lhs.y, -lhs.z, -lhs.w); }
inline bool operator==(const ImVec4& lhs, const ImVec4& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w; }
inline bool operator!=(const ImVec4& lhs, const ImVec4& rhs) { return lhs.x != rhs.x || lhs.y != rhs.y || lhs.z != rhs.z || lhs.w != rhs.w; }
IM_MSVC_RUNTIME_CHECKS_RESTORE
#endif


// 用于生成 32 位编码颜色的辅助宏
// - 用户可以通过在 imconfig 文件中 #define 这 5 个 _SHIFT/_MASK 宏来声明自己的格式。
// - 除默认设置外的任何设置都需要自定义后端支持。唯一支持非默认设置的标准后端是 DirectX9。
#ifndef IM_COL32_R_SHIFT
#ifdef IMGUI_USE_BGRA_PACKED_COLOR
#define IM_COL32_R_SHIFT 16
#define IM_COL32_G_SHIFT 8
#define IM_COL32_B_SHIFT 0
#define IM_COL32_A_SHIFT 24
#define IM_COL32_A_MASK 0xFF000000
#else
#define IM_COL32_R_SHIFT 0
#define IM_COL32_G_SHIFT 8
#define IM_COL32_B_SHIFT 16
#define IM_COL32_A_SHIFT 24
#define IM_COL32_A_MASK 0xFF000000
#endif
#endif
#define IM_COL32(R,G,B,A) (((ImU32)(A)<<IM_COL32_A_SHIFT) | ((ImU32)(B)<<IM_COL32_B_SHIFT) | ((ImU32)(G)<<IM_COL32_G_SHIFT) | ((ImU32)(R)<<IM_COL32_R_SHIFT))
#define IM_COL32_WHITE IM_COL32(255,255,255,255) // 不透明白色 = 0xFFFFFFFF
#define IM_COL32_BLACK IM_COL32(0,0,0,255) // 不透明黑色
#define IM_COL32_BLACK_TRANS IM_COL32(0,0,0,0) // 透明黑色 = 0x00000000


// 辅助类：ImColor() 可将颜色隐式转换为 ImU32（4x1 字节打包）或 ImVec4（4x1 浮点数）
如果您希望获得确定的编译时 ImU32 常量以用于 ImDrawList API，请优先使用 IM_COL32() 宏。
// **避免存储 ImColor！请存储 u32 或 ImVec4。这并非一个功能齐全的颜色类。未来可能会废弃。**
// **没有任何 ImGui API 直接使用 ImColor，但您可以将其作为一种便利手段，以 ImU32 或 ImVec4 格式传递颜色。如果需要，请显式转换为 ImU32 或 ImVec4。**
struct ImColor
{
    ImVec4 Value;


    constexpr ImColor() {}
    constexpr ImColor(float r, float g, float b, float a = 1.0f) : Value(r, g, b, a) {}
    constexpr ImColor(const ImVec4& col) : Value(col) {}
    constexpr ImColor(int r, int g, int b, int a = 255) : Value((float)r* (1.0f / 255.0f), (float)g* (1.0f / 255.0f), (float)b* (1.0f / 255.0f), (float)a* (1.0f / 255.0f)) {}
    constexpr ImColor(ImU32 rgba) : Value((float)((rgba >> IM_COL32_R_SHIFT) & 0xFF)* (1.0f / 255.0f), (float)((rgba >> IM_COL32_G_SHIFT) & 0xFF)* (1.0f / 255.0f), (float)((rgba >> IM_COL32_B_SHIFT) & 0xFF)* (1.0f / 255.0f), (float)((rgba >> IM_COL32_A_SHIFT) & 0xFF)* (1.0f / 255.0f)) {}
    inline operator ImU32() const { return ImGui::ColorConvertFloat4ToU32(Value); }
    inline operator ImVec4() const { return Value; }


    // 待修复-已废弃：可能需要废弃或清理这些辅助函数。
    inline void SetHSV(float h, float s, float v, float a = 1.0f) { ImGui::ColorConvertHSVtoRGB(h, s, v, Value.x, Value.y, Value.z); Value.w = a; }
    static ImColor HSV(float h, float s, float v, float a = 1.0f) { float r, g, b; ImGui::ColorConvertHSVtoRGB(h, s, v, r, g, b); return ImColor(r, g, b, a); }
};


//-----------------------------------------------------------------------------
// [部分] 多选 API 标志和结构 (ImGuiMultiSelectFlags, ImGuiSelectionRequestType, ImGuiSelectionRequest, ImGuiMultiSelectIO, ImGuiSelectionBasicStorage)
//-----------------------------------------------------------------------------


// 多选系统
// 文档地址：https://github.com/ocornut/imgui/wiki/Multi-Select
// - 请参考“Demo->Widgets->Selection State & Multi-Select”查看相关演示。
// - 该系统实现了标准的多选交互习惯（Ctrl+鼠标/键盘、Shift+鼠标/键盘等）
// 支持裁剪器（跳过不可见项目）、框选以及许多其他细节。
// - 支持 Selectable()、Checkbox()，但自定义控件也可以使用它。
// - TreeNode() 在技术上是支持的，但……正确使用它比较复杂：你需要对树进行某种线性/随机访问，
// 这适用于同时也实现了过滤器和裁剪器的进阶树结构设置。我们将致力于简化并演示这一功能。
// - 秉承 Dear ImGui 的设计精神，你的代码拥有实际的选择数据。
// 这种设计旨在允许你在应用程序中使用各种类型的选择存储方式，例如 set/map/hash。
// 关于 ImGuiSelectionBasicStorage：
// - 这是一个可选的辅助结构，用于存储选择状态并应用选择请求。
// - 它被我们的示例程序所使用，并作为一种便捷方式提供，以便快速实现多选功能。
// 用法：
// - 使用 SetNextItemSelectionUserData() 标识提交的项目，通常使用当前数据集中的索引。
// - 使用持久的对象标识符来存储和维护实际的选择数据。
// - 使用流程：
// 开始 - (1) 调用 BeginMultiSelect() 并获取 ImGuiMultiSelectIO* 结果。
// - (2) 通过更新您的选择数据来响应请求列表（SetAll/SetRange 请求）。代码与第 6 步相同。
// - (3) [如果使用 clipper] 您需要确保 RangeSrcItem 始终被提交。计算其索引并传递给 clipper.IncludeItemByIndex()。如果将索引存储在 ImGuiSelectionUserData 中，只需调用 clipper.IncludeItemByIndex(ms_io->RangeSrcItem) 即可。
// 循环 - (4) 通过调用 SetNextItemSelectionUserData() + Selectable()/TreeNode() 来提交您的项目。
// 结束 - (5) 调用 EndMultiSelect() 并获取 ImGuiMultiSelectIO* 结果。
// - (6) 通过更新您的选择数据来响应请求列表（SetAll/SetRange 请求）。代码与第 2 步相同。
// 如果您提交了所有项目（未使用 clipper），第 2 步和第 3 步是可选的，将由每个项目自行处理。始终执行这些步骤也是可以的。
// 关于 ImGuiSelectionUserData：
// - 它可以存储通过 SetNextItemSelectionUserData() 提交的应用程序定义标识符（例如索引或指针）。
// - 作为回报，我们将它们存储在 ImGuiMultiSelectIO 的 RangeSrcItem/RangeFirstItem/RangeLastItem 以及其他字段中。
// - 大多数应用程序会存储一个对象索引（INDEX），因此选择了这个名称和类型。存储索引是很自然的，因为
// SetRange 请求将为您提供两个端点，您需要在这两个端点之间进行迭代/插值，以更新您的选择。
// - 然而，在 ImGuiSelectionUserData 中存储指针或其他标识符是完全可行的。
// 我们的系统从不假设您通过索引来标识项目，也从不尝试在两个值之间进行插值。
// - 如果您启用了 ImGuiMultiSelectFlags_NoRangeSelect，那么可以保证您永远不需要进行插值。
// 在两个 ImGuiSelectionUserData 之间，这可能是一种以较少代码量使用部分功能的便捷方式。
// - 由于大多数用户会希望存储索引，为了方便并减少混淆，我们使用 ImS64 而不是 void*，
// 在语法上更易于向下转型。你可以随意使用 reinterpret_cast 并在其中存储指针。


// BeginMultiSelect() 的标志位
enum ImGuiMultiSelectFlags_
{
    ImGuiMultiSelectFlags_None = 0,
    ImGuiMultiSelectFlags_SingleSelect = 1 << 0, // 禁用选择多个项目。如果需要，这允许单选代码共享相同的代码/逻辑。不过，它本质上禁用了 BeginMultiSelect() 的主要目的！
    ImGuiMultiSelectFlags_NoSelectAll = 1 << 1, // 禁用 Ctrl+A 全选快捷键。
    ImGuiMultiSelectFlags_NoRangeSelect = 1 << 2, // 禁用 Shift+选择的鼠标/键盘支持（适用于无序的 2D 选择）。配合 BoxSelect 使用时，还能确保连续的 SetRange 请求不会被合并为一个。这使得在处理 SetRange 请求时无需进行插值处理。
    ImGuiMultiSelectFlags_NoAutoSelect = 1 << 3, // 禁用导航时自动选择项目（例如，适用于在复选框列表中支持范围选择）。
    ImGuiMultiSelectFlags_NoAutoClear = 1 << 4, // 禁用在导航或选择另一个项目时清除原有选择（通常与 ImGuiMultiSelectFlags_NoAutoSelect 配合使用。例如，适用于在复选框列表中支持范围选择）。
    ImGuiMultiSelectFlags_NoAutoClearOnReselect = 1 << 5, // 禁用在点击或选择已选项目时清除选择。
    ImGuiMultiSelectFlags_BoxSelect1d = 1 << 6, // 启用针对等宽且 X 轴位置相同的项（例如全行 Selectable()）的框选。为了能瞄准空白区域，框选功能在项的碰撞箱之间留有少量间距时效果更好。
    ImGuiMultiSelectFlags_BoxSelect2d = 1 << 7, // 启用支持不同宽度或不同 X 轴位置的项（例如不同宽度的标签，或 2D 布局/网格）的框选。此模式较慢：它会改变裁剪逻辑，使得水平移动也能更新通常被裁剪掉的项的选中状态。
    ImGuiMultiSelectFlags_BoxSelectNoScroll = 1 << 8, // 在范围边缘进行框选时禁用滚动。
    ImGuiMultiSelectFlags_ClearOnEscape = 1 << 9, // 当范围处于焦点状态时，按下 Escape 键清除选中项。
    ImGuiMultiSelectFlags_ClearOnClickVoid = 1 << 10, // 点击作用域内的空白区域时清除选择。
    ImGuiMultiSelectFlags_ScopeWindow = 1 << 11, // _BoxSelect（框选）和 _ClearOnClickVoid 的作用域为整个窗口（默认）。如果 BeginMultiSelect() 覆盖了整个窗口，或在同一窗口中仅使用一次时使用此项。
    ImGuiMultiSelectFlags_ScopeRect = 1 << 12, // _BoxSelect（框选）和 _ClearOnClickVoid 的作用域为包含 BeginMultiSelect()/EndMultiSelect() 的矩形区域。如果在同一窗口中多次调用 BeginMultiSelect() 时使用此项。
    ImGuiMultiSelectFlags_SelectOnClick = 1 << 13, // 点击未选中项时，在鼠标按下时应用选择。（默认）
    ImGuiMultiSelectFlags_SelectOnClickRelease = 1 << 14, // 点击未选中项时，在鼠标释放时应用选择。允许在不改变选择状态的情况下拖动未选中项。
    //ImGuiMultiSelectFlags_RangeSelect2d = 1 << 15, // Shift+选择使用 2D 几何布局而非线性序列，因此可以使用 Shift+上/下键在网格中进行垂直选择。类似于框选（BoxSelect）的行为。
    ImGuiMultiSelectFlags_NavWrapX = 1 << 16, // [临时] 启用 X 轴的导航环绕。提供此功能是为了方便，因为我们目前还没有针对此功能的通用导航 API 设计。当更通用的功能发布时，我们可能会废弃此标志以支持新标志。
    ImGuiMultiSelectFlags_NoSelectOnRightClick = 1 << 17, // 禁用默认的右键单击处理。默认处理会在鼠标按下时选择项目，是为上下文菜单设计的。
};


// 由 BeginMultiSelect()/EndMultiSelect() 返回的主要 IO 结构体。
// 这主要包含一个选择请求列表。
// - 使用 "Demo->Tools->Debug Log->Selection" 来查看实时发生的请求。
// - 某些字段仅在列表是动态且允许删除时才有用（在示例中展示了如何正确处理删除后的焦点/状态）
// - 下方：谁读取/写入各个字段？'r'=读取，'w'=写入，'ms'=多选代码，'app'=应用程序/用户代码。
struct ImGuiMultiSelectIO
{
    //------------------------------------------// BeginMultiSelect / EndMultiSelect
    ImVector<ImGuiSelectionRequest> Requests; // ms:w, app:r / ms:w app:r // 需要应用到您的选择数据中的请求。
    ImGuiSelectionUserData RangeSrcItem; // ms:w app:r / // （如果使用裁剪器）开始：源项目（通常是第一个选定项目）绝不能被裁剪：请使用 clipper.IncludeItemByIndex() 以确保其被提交。
    ImGuiSelectionUserData NavIdItem; // ms:w, app:r / // （如果使用删除功能）NavId 最后已知的 SetNextItemSelectionUserData() 值（如果是已提交项目的一部分）。
    bool NavIdSelected; // ms:w, app:r / app:r // （如果使用删除功能）NavId 最后已知的选择状态（如果是已提交项目的一部分）。
    bool RangeSrcReset; // app:w / ms:r // （如果使用删除功能）在 EndMultiSelect() 之前设置，用于重置 ResetSrcItem（例如在删除了所选项的情况下）。
    int ItemsCount; // ms:w, app:r / app:r // 传给 BeginMultiSelect() 的 'int items_count' 参数会被复制到此处以提供便利，从而简化对 ApplyRequests 处理函数的调用。内部并未使用。
};


// 选择请求类型
enum ImGuiSelectionRequestType
{
    ImGuiSelectionRequestType_None = 0,
    ImGuiSelectionRequestType_SetAll, // 请求应用程序清除选择（若 Selected==false）或全选所有项目（若 Selected==true）。我们无法设置 RangeFirstItem/RangeLastItem，因为其内容完全由用户决定（不一定是一个索引）
    ImGuiSelectionRequestType_SetRange, // 请求应用程序根据 Selected 的值选择/取消选择 [RangeFirstItem..RangeLastItem] 范围内的项目（闭区间）。仅 EndMultiSelect() 会发出此请求，应用程序代码可以在 BeginMultiSelect() 之后读取，且其值始终为 false。
};


// 选择请求项
struct ImGuiSelectionRequest
{
    //------------------------------------------// BeginMultiSelect / EndMultiSelect
    ImGuiSelectionRequestType Type; // ms:w, app:r / ms:w, app:r // 请求类型。你最常会收到 1 个 Clear（清除）+ 1 个单项范围的 SetRange（设置范围）。
    bool Selected; // ms:w, app:r / ms:w, app:r // SetAll/SetRange 请求的参数（true = 选择，false = 取消选择）
    ImS8 RangeDirection; // / ms:w app:r // SetRange 请求的参数：当 RangeFirstItem 在 RangeLastItem 之前时为 +1，否则为 -1。如果你想在反向 Shift+点击时保持选择顺序，这会很有用。
    ImGuiSelectionUserData RangeFirstItem; // / ms:w, app:r // SetRange 请求的参数（从上到下进行 Shift 选择时，通常等于 RangeSrcItem）。
    ImGuiSelectionUserData RangeLastItem; // / ms:w, app:r // SetRange 请求的参数（从下到上进行 Shift 选择时，通常等于 RangeSrcItem）。包含此项！
};


// 可选的辅助工具，用于存储多选状态并应用多选请求。
// - 用于我们的示例程序，并作为一种便利方式提供，以便轻松实现基础的多选功能。
// - 使用 'void* it = NULL; ImGuiID id; while (selection.GetNextSelectedItem(&it, &id)) { ... }' 来遍历选中项。
// - 或者，如果对象数量不多，你也可以对每个可能的对象检查 'if (Contains(id)) { ... }'。
// - 使用此功能并非强制。这仅是一个辅助工具，而非必需的 API。
// 要存储多选状态，在您的应用程序中您可以：
// - 使用此辅助工具以提供便利。我们使用简单的键值对存储 ImGuiStorage 来替代 std::set<ImGuiID>。
// - 使用您自己的外部存储：例如 std::set<MyObjectId>、std::vector<MyObjectId>、区间树、侵入式存储的选择状态等。
// 在 ImGuiSelectionBasicStorage 中，我们：
// - 在多选 API 中始终使用索引（通过 SetNextItemSelectionUserData() 传递，在 ImGuiMultiSelectIO 中检索）
// - 使用 AdapterIndexToStorageId() 间接层来抽象如何从索引派生持久化选择数据。
// - 使用经过深度优化的逻辑，以支持对超大型选择集进行查询和插入。
// - 不保留选择顺序。
// 根据您偏好的项目存储方式以及选择状态存储方式，可以有多种组合方案。
// 大型应用最终可能希望摆脱这一间接层，并实现自己的逻辑。
// 有关使用此辅助程序的详细信息和伪代码，请参阅 https://github.com/ocornut/imgui/wiki/Multi-Select。
struct ImGuiSelectionBasicStorage
{
    // 成员
    int Size; // // 已选项目的数量，由该辅助结构维护。
    bool PreserveOrder; // = false // GetNextSelectedItem() 将返回有序的选择结果（目前通过对选择内容进行两次额外排序实现。尚有改进空间）
    void* UserData; // = NULL // 供适配器函数使用的用户数据 // 例如：selection.UserData = (void*)my_items;
    ImGuiID(*AdapterIndexToStorageId)(ImGuiSelectionBasicStorage* self, int idx); // 例如：selection.AdapterIndexToStorageId = [](ImGuiSelectionBasicStorage* self, int idx) { return ((MyItems**)self->UserData)[idx]->ID; };
    int _SelectionOrder;// [内部] 递增计数器，用于存储选择顺序
    ImGuiStorage _Storage; // [内部] 选择集。可以将其视为类似于 std::set<ImGuiID> 的结构。建议不要直接访问：请使用 GetNextSelectedItem() 进行迭代。


    // 方法
    IMGUI_API ImGuiSelectionBasicStorage();
    IMGUI_API void ApplyRequests(ImGuiMultiSelectIO* ms_io); // 应用来自 BeginMultiSelect() 和 EndMultiSelect() 函数的选择请求。它使用传递给 BeginMultiSelect() 的 'items_count' 参数。
    IMGUI_API bool Contains(ImGuiID id) const; // 查询某个项目 ID 是否在选择集中。
    IMGUI_API void Clear(); // 清除选择
    IMGUI_API void Swap(ImGuiSelectionBasicStorage& r); // 交换两个选择集
    IMGUI_API void SetItemSelected(ImGuiID id, bool selected); // 从选择集中添加/移除一项（通常由 ApplyRequests() 函数执行）
    IMGUI_API bool GetNextSelectedItem(void** opaque_it, ImGuiID* out_id); // 遍历选择集，用法：'void* it = NULL; ImGuiID id; while (selection.GetNextSelectedItem(&it, &id)) { ... }'
    inline ImGuiID GetStorageIdFromIndex(int idx) { return AdapterIndexToStorageId(this, idx); } // 根据提供的适配器将索引转换为项目 ID。
};


// 可选的辅助函数，用于将多选请求应用于现有的随机访问存储。
// 如果你想在布尔数组或存储自身选择状态的项目上快速连接多选 API，这将非常方便。
struct ImGuiSelectionExternalStorage
{
    // 成员
    void* UserData; // 供适配器函数使用的用户数据 // 例如 selection.UserData = (void*)my_items;
    void (*AdapterSetItemSelected)(ImGuiSelectionExternalStorage* self, int idx, bool selected); // 例如 AdapterSetItemSelected = [](ImGuiSelectionExternalStorage* self, int idx, bool selected) { ((MyItems**)self->UserData)[idx]->Selected = selected; }


    // 方法
    IMGUI_API ImGuiSelectionExternalStorage();
    IMGUI_API void ApplyRequests(ImGuiMultiSelectIO* ms_io); // 通过调用 AdapterSetItemSelected() 来应用选择请求
};


//-----------------------------------------------------------------------------
// [SECTION] 绘图 API (ImDrawCmd, ImDrawIdx, ImDrawVert, ImDrawChannel, ImDrawListSplitter, ImDrawListFlags, ImDrawList, ImDrawData)
// 保存一系列绘图命令。用户需为 ImDrawData 提供一个渲染器，而 ImDrawData 本质上包含了一个 ImDrawList 数组。
//-----------------------------------------------------------------------------


// 用于烘焙抗锯齿纹理的最大线宽。在构建图集时使用 ImFontAtlasFlags_NoBakedLines 可禁用烘焙。
#ifndef IM_DRAWLIST_TEX_LINES_WIDTH_MAX
#define IM_DRAWLIST_TEX_LINES_WIDTH_MAX (32)
#endif


// ImDrawIdx：顶点索引。[编译时可配置类型]
// - 若要使用 16 位索引并支持大型网格：后端需要设置 'io.BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset' 并处理 ImDrawCmd::VtxOffset（推荐做法）。
// - 若要使用 32 位索引：请在您的 imconfig.h 文件中通过 '#define ImDrawIdx unsigned int' 进行重写。
#ifndef ImDrawIdx
typedef unsigned short ImDrawIdx; // 默认：16 位（为了与渲染器后端保持最大兼容性）
#endif


// ImDrawCallback：用于高级用途的绘制回调 [可配置类型：可在 imconfig.h 中重写]
// 注意：通常情况下，你并不需要使用绘制回调来创建自定义控件或自定义 UI 渲染，
// 你可以直接操作绘制列表（draw list）来实现！绘制回调通常用于以下场景：
// A) 更改 GPU 渲染状态，
// B) 在 UI 元素内部渲染复杂的 3D 场景，且无需中间纹理/渲染目标等。
// 渲染函数预期的行为是 'if (cmd.UserCallback != NULL) { cmd.UserCallback(parent_list, cmd); } else { RenderTriangles() }'
// 如果你想覆盖 ImDrawCallback 的签名，只需使用例如 '#define ImDrawCallback MyDrawCallback'（在 imconfig.h 中）并相应地更新渲染后端。
#ifndef ImDrawCallback
typedef void (*ImDrawCallback)(const ImDrawList* parent_list, const ImDrawCmd* cmd);
#endif


// 特殊的绘制回调值，用于请求渲染后端重置图形/渲染状态。
// 渲染后端需要处理这个特殊值，否则在尝试调用该地址处的函数时会发生崩溃。
// 这很有用，例如，如果您提交了已知会改变渲染状态的回调，并希望恢复该状态。
// 渲染状态默认不会被重置，因为有许多非常有用的方式可以改变渲染状态（例如，在调用 Image 之前更改着色器/混合设置）。
#define ImDrawCallback_ResetRenderState (ImDrawCallback)(-8)


// 通常情况下，1 条命令 = 1 次 GPU 绘制调用（除非该命令是一个回调）
// - VtxOffset: 当 'io.BackendFlags & ImGuiBackendFlags_RendererHasVtxOffset' 启用时，
// 这些字段允许我们在保持 16 位索引的同时，渲染超过 64K 个顶点的网格。
// 为 1.71 以前版本制作的后端通常会忽略 VtxOffset 字段。
// - ClipRect/TexRef/VtxOffset 字段必须是连续的，因为我们会对它们进行 memcmp() 操作（这一点已通过断言确认）。
struct ImDrawCmd
{
    ImVec4 ClipRect; // 4*4 // 裁剪矩形 (x1, y1, x2, y2)。减去 ImDrawData->DisplayPos 可获得“视口”坐标系下的裁剪矩形。
    ImTextureRef TexRef; // 16 // 引用字体/纹理图集（后端调用 ImTextureData::SetTexID() 的位置）或用户提供的纹理 ID（例如通过 ImGui::Image() 调用）。两者最终都会产生一个 ImTextureID 值。
    unsigned int VtxOffset; // 4 // 顶点缓冲区中的起始偏移量。若未开启 ImGuiBackendFlags_RendererHasVtxOffset，则始终为 0；否则可能大于 0，以支持使用 16 位索引且超过 64K 顶点的网格。
    unsigned int IdxOffset; // 4 // 索引缓冲区中的起始偏移量。
    unsigned int ElemCount; // 4 // 要渲染为三角形的索引数量（3 的倍数）。顶点存储在调用方 ImDrawList 的 vtx_buffer[] 数组中，索引存储在 idx_buffer[] 中。
    ImDrawCallback UserCallback; // 4-8 // 如果不为 NULL，则调用该函数而不是渲染顶点。clip_rect 和 texture_id 仍会正常设置。
    void* UserCallbackData; // 4-8 // 回调用户数据（当 UserCallback != NULL 时）。如果调用 AddCallback() 时 size == 0，则这是 AddCallback() 参数的副本。如果调用 AddCallback() 时 size > 0，则这指向存储数据的缓冲区。
    int UserCallbackDataSize; // 4 // 使用存储时的回调用户数据大小，否则为 0。
    int UserCallbackDataOffset;// 4 // [内部] 使用存储时的回调用户数据偏移量，否则为 -1。


    ImDrawCmd() { memset(this, 0, sizeof(*this)); } // 同时确保填充字段被清零


    // 自 1.83 版本起：返回与此绘制调用关联的 ImTextureID。警告：不要假设这始终与 'TextureId' 相同（我们将为即将推出的功能更改此函数）
    // 自 1.92 版本起：移除了 ImDrawCmd::TextureId 字段，必须使用 getter 函数！
    inline ImTextureID GetTexID() const; // == (TexRef._TexData ? TexRef._TexData->TexID : TexRef._TexID)
};


// 顶点布局
#ifndef IMGUI_OVERRIDE_DRAWVERT_STRUCT_LAYOUT
struct ImDrawVert
{
    ImVec2 pos;
    ImVec2 uv;
    ImU32 col;
};
#else
// 你可以通过在 imconfig.h 中定义 IMGUI_OVERRIDE_DRAWVERT_STRUCT_LAYOUT 来覆盖顶点格式布局
// 代码期望的布局为 ImVec2 pos (8 字节), ImVec2 uv (8 字节), ImU32 col (4 字节)，但你可以根据需要重新排序或添加其他字段，以简化与引擎的集成。
// 必须在宏内描述该类型（你可以声明结构体或使用 typedef）。这是因为在你想设置类型时，ImVec2/ImU32 可能尚未声明。
// 注意：IMGUI 不会清理该结构体，也不会调用构造函数，因此任何自定义字段都将是未初始化的。如果你添加了额外字段（例如“Z”坐标），你需要在渲染期间清理它们或忽略它们。
IMGUI_OVERRIDE_DRAWVERT_STRUCT_LAYOUT;
#endif


// [内部] 供 ImDrawList 使用
struct ImDrawCmdHeader
{
    ImVec4 ClipRect;
    ImTextureRef TexRef;
    unsigned int VtxOffset;
};


// [内部使用] 供 ImDrawListSplitter 使用
struct ImDrawChannel
{
    ImVector<ImDrawCmd> _CmdBuffer;
    ImVector<ImDrawIdx> _IdxBuffer;
};


// 分离/合并（Split/Merge）函数用于将绘制列表拆分为不同的层，从而可以实现乱序绘制。
// 此功能被列（Columns）和表格（Tables）API 使用，以便将每个列的项目合并到同一个绘制调用中。
struct ImDrawListSplitter
{
    int _Current; // 当前通道索引 (0)
    int _Count; // 活跃通道数量 (1+)
    ImVector<ImDrawChannel> _Channels; // 绘制通道（不会缩减容量，因此 _Count 可能小于 Channels.Size）


    inline ImDrawListSplitter() { memset(this, 0, sizeof(*this)); }
    inline ~ImDrawListSplitter() { ClearFreeMemory(); }
    inline void Clear() { _Current = 0; _Count = 1; } // 不清除 Channels[]，以便在下一帧重用我们的分配
    IMGUI_API void ClearFreeMemory();
    IMGUI_API void Split(ImDrawList* draw_list, int count);
    IMGUI_API void Merge(ImDrawList* draw_list);
    IMGUI_API void SetCurrentChannel(ImDrawList* draw_list, int channel_idx);
};


// ImDrawList 函数的标志位
//（遗留问题：第 0 位必须始终对应 ImDrawFlags_Closed，以便与使用布尔值的旧版 API 向后兼容。第 1..3 位必须保持未使用状态）
enum ImDrawFlags_
{
    ImDrawFlags_None = 0,
    ImDrawFlags_Closed = 1 << 0, // PathStroke(), AddPolyline(): 指定形状应当闭合（重要：由于历史原因，此值始终等于 1）
    ImDrawFlags_RoundCornersTopLeft = 1 << 4, // AddRect(), AddRectFilled(), PathRect(): 仅启用左上角圆角（当 rounding > 0.0f 时，默认所有角均为圆角）。原为 0x01。
    ImDrawFlags_RoundCornersTopRight = 1 << 5, // AddRect(), AddRectFilled(), PathRect(): 仅对右上角启用圆角（当 rounding > 0.0f 时，默认对所有角生效）。原为 0x02。
    ImDrawFlags_RoundCornersBottomLeft = 1 << 6, // AddRect(), AddRectFilled(), PathRect(): 仅对左下角启用圆角（当 rounding > 0.0f 时，默认对所有角生效）。原为 0x04。
    ImDrawFlags_RoundCornersBottomRight = 1 << 7, // AddRect(), AddRectFilled(), PathRect(): 仅对右下角启用圆角（当 rounding > 0.0f 时，默认对所有角生效）。原为 0x08。
    ImDrawFlags_RoundCornersNone = 1 << 8, // AddRect(), AddRectFilled(), PathRect(): 禁用所有角的圆角（当 rounding > 0.0f 时）。这不为零，也不是隐式标志！
    ImDrawFlags_RoundCornersTop = ImDrawFlags_RoundCornersTopLeft | ImDrawFlags_RoundCornersTopRight,
    ImDrawFlags_RoundCornersBottom = ImDrawFlags_RoundCornersBottomLeft | ImDrawFlags_RoundCornersBottomRight,
    ImDrawFlags_RoundCornersLeft = ImDrawFlags_RoundCornersBottomLeft | ImDrawFlags_RoundCornersTopLeft,
    ImDrawFlags_RoundCornersRight = ImDrawFlags_RoundCornersBottomRight | ImDrawFlags_RoundCornersTopRight,
    ImDrawFlags_RoundCornersAll = ImDrawFlags_RoundCornersTopLeft | ImDrawFlags_RoundCornersTopRight | ImDrawFlags_RoundCornersBottomLeft | ImDrawFlags_RoundCornersBottomRight,
    ImDrawFlags_RoundCornersDefault_ = ImDrawFlags_RoundCornersAll, // 如果未指定任何 _RoundCornersXX 标志，则默认为全圆角（ALL）。
    ImDrawFlags_RoundCornersMask_ = ImDrawFlags_RoundCornersAll | ImDrawFlags_RoundCornersNone,
};


// ImDrawList 实例的标志。这些标志通常由 ImGui:: 函数根据 ImGuiIO 设置自动设定，一般不直接进行操作。
// 不过，在调用 ImDrawList:: 各个函数之间临时修改标志位是可行的。
enum ImDrawListFlags_
{
    ImDrawListFlags_None = 0,
    ImDrawListFlags_AntiAliasedLines = 1 << 0, // 启用线条/边框抗锯齿（对于 1.0f 宽或足够细以使用纹理绘制的线条，三角形数量变为 2 倍，否则为 3 倍）
    ImDrawListFlags_AntiAliasedLinesUseTex = 1 << 1, // 在可能的情况下，启用基于纹理的抗锯齿线条/边框。需要后端以双线性过滤（而非点过滤/最近邻过滤）进行渲染。
    ImDrawListFlags_AntiAliasedFill = 1 << 2, // 在填充形状（圆角矩形、圆形）周围启用抗锯齿边缘。
    ImDrawListFlags_AllowVtxOffset = 1 << 3, // 可以发出 'VtxOffset > 0' 以允许大型网格。当启用 'ImGuiBackendFlags_RendererHasVtxOffset' 时设置。
};


// 绘制命令列表
// 这是 ImGui:: 函数填充的底层多边形列表。在帧结束时，
// 所有的命令列表都会被传递给您的 ImGuiIO::RenderDrawListFn 函数进行渲染。
// 每个 Dear ImGui 窗口都包含其自身的 ImDrawList。您可以使用 ImGui::GetWindowDrawList() 来
// 访问当前窗口的绘制列表并绘制自定义原语。
// 你可以将常规的 ImGui:: 调用与向当前绘制列表（draw list）添加图元的操作交替进行。
// 在单视口模式下，左上角等于 GetMainViewport()->Pos（通常为 0,0），右下角等于 GetMainViewport()->Pos+Size（通常为 io.DisplaySize）。
// 你可以完全自由地对数据应用任何你想要的变换矩阵（取决于变换的用途，你可能也需要将其应用于裁剪矩形 ClipRect！）。
// 重要提示：图元总是被直接添加到列表中而不会被剔除（剔除是由 ImGui:: 函数在更高层级完成的），如果你大量使用此 API，请考虑对绘制对象进行粗略剔除。
struct ImDrawList
{
    // 这是你需要进行渲染的内容
    ImVector<ImDrawCmd> CmdBuffer; // 绘制命令。通常 1 条命令对应 1 次 GPU 绘制调用，除非该命令是回调函数。
    ImVector<ImDrawIdx> IdxBuffer; // 索引缓冲区。每条命令消耗 ImDrawCmd::ElemCount 个索引。
    ImVector<ImDrawVert> VtxBuffer; // 顶点缓冲区。
    ImDrawListFlags Flags; // 标志位，你可以通过修改这些标志来调整每个图元的抗锯齿设置。


    // [内部使用，在构建列表时使用]
    unsigned int _VtxCurrentIdx; // [内部] 通常等于 VtxBuffer.Size，除非顶点数超过 64K，在这种情况下它会被重置为 0。
    ImDrawListSharedData* _Data; // 指向共享绘制数据的指针（可以使用 ImGui::GetDrawListSharedData() 获取当前 ImGui 上下文中的数据）
    ImDrawVert* _VtxWritePtr; // [内部] 每次添加命令后在 VtxBuffer.Data 中的指向位置（为了避免过度使用 ImVector<> 运算符）
    ImDrawIdx* _IdxWritePtr; // [内部] 每次添加命令后在 IdxBuffer.Data 中的指向位置（为了避免过度使用 ImVector<> 运算符）
    ImVector<ImVec2> _Path; // [内部] 当前正在构建的路径
    ImDrawCmdHeader _CmdHeader; // [内部] 当前命令的模板。字段应与 CmdBuffer.back() 保持一致。
    ImDrawListSplitter _Splitter; // [内部] 用于通道 API（注意：建议优先使用您自己持久化的 ImDrawListSplitter 实例！）
    ImVector<ImVec4> _ClipRectStack; // [内部]
    ImVector<ImTextureRef> _TextureStack; // [内部]
    ImVector<ImU8> _CallbacksDataBuf; // [内部]
    float _FringeScale; // [内部] 抗锯齿边缘按此值缩放，这有助于在缩放顶点缓冲区内容时保持清晰度
    const char* _OwnerName; // 指向所属窗口名称的指针，用于调试


    // 如果你想创建 ImDrawList 实例，请向其传递 ImGui::GetDrawListSharedData()。
    //（高级用法：你可以创建并使用自己的 ImDrawListSharedData，以便在不使用 ImGui 的情况下使用 ImDrawList，但这涉及的操作较多）
    IMGUI_API ImDrawList(ImDrawListSharedData* shared_data);
    IMGUI_API ~ImDrawList();


    IMGUI_API void PushClipRect(const ImVec2& clip_rect_min, const ImVec2& clip_rect_max, bool intersect_with_current_clip_rect = false); // 渲染层级的裁剪（Scissoring）。这会传递给您的渲染函数，但不会用于 CPU 端的粗略裁剪。建议优先使用更高级别的 ImGui::PushClipRect() 以影响逻辑（命中测试和控件剔除）。
    IMGUI_API void PushClipRectFullScreen();
    IMGUI_API void PopClipRect();
    IMGUI_API void PushTexture(ImTextureRef tex_ref);
    IMGUI_API void PopTexture();
    inline ImVec2 GetClipRectMin() const { const ImVec4& cr = _ClipRectStack.back(); return ImVec2(cr.x, cr.y); }
    inline ImVec2 GetClipRectMax() const { const ImVec4& cr = _ClipRectStack.back(); return ImVec2(cr.z, cr.w); }


    // 图元 (Primitives)
    // - 填充形状必须始终使用顺时针绕序。抗锯齿边缘依赖于此。逆时针形状将产生“向内”的抗锯齿效果。
    // - 对于矩形图元，“p_min” 和 “p_max” 分别代表左上角和右下角。
    // - 对于圆形图元，使用 “num_segments == 0” 来自动计算细分数（推荐做法）。
    // 在旧版本中（直到 Dear ImGui 1.77 为止），AddCircle 函数的 num_segments 默认值为 12。
    // 在未来的版本中，我们将使用纹理来提供更廉价且更高质量的圆。
    // 如果你需要确保特定的边数，请使用 AddNgon() 和 AddNgonFilled() 函数。
    IMGUI_API void AddLine(const ImVec2& p1, const ImVec2& p2, ImU32 col, float thickness = 1.0f);
    IMGUI_API void AddRect(const ImVec2& p_min, const ImVec2& p_max, ImU32 col, float rounding = 0.0f, ImDrawFlags flags = 0, float thickness = 1.0f); // a: 左上角, b: 右下角 (== 左上角 + 尺寸)
    IMGUI_API void AddRectFilled(const ImVec2& p_min, const ImVec2& p_max, ImU32 col, float rounding = 0.0f, ImDrawFlags flags = 0); // a: 左上角, b: 右下角 (== 左上角 + 尺寸)
    IMGUI_API void AddRectFilledMultiColor(const ImVec2& p_min, const ImVec2& p_max, ImU32 col_upr_left, ImU32 col_upr_right, ImU32 col_bot_right, ImU32 col_bot_left);
    IMGUI_API void AddQuad(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, ImU32 col, float thickness = 1.0f);
    IMGUI_API void AddQuadFilled(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, ImU32 col);
    IMGUI_API void AddTriangle(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, ImU32 col, float thickness = 1.0f);
    IMGUI_API void AddTriangleFilled(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, ImU32 col);
    IMGUI_API void AddCircle(const ImVec2& center, float radius, ImU32 col, int num_segments = 0, float thickness = 1.0f);
    IMGUI_API void AddCircleFilled(const ImVec2& center, float radius, ImU32 col, int num_segments = 0);
    IMGUI_API void AddNgon(const ImVec2& center, float radius, ImU32 col, int num_segments, float thickness = 1.0f);
    IMGUI_API void AddNgonFilled(const ImVec2& center, float radius, ImU32 col, int num_segments);
    IMGUI_API void AddEllipse(const ImVec2& center, const ImVec2& radius, ImU32 col, float rot = 0.0f, int num_segments = 0, float thickness = 1.0f);
    IMGUI_API void AddEllipseFilled(const ImVec2& center, const ImVec2& radius, ImU32 col, float rot = 0.0f, int num_segments = 0);
    IMGUI_API void AddText(const ImVec2& pos, ImU32 col, const char* text_begin, const char* text_end = NULL);
    IMGUI_API void AddText(ImFont* font, float font_size, const ImVec2& pos, ImU32 col, const char* text_begin, const char* text_end = NULL, float wrap_width = 0.0f, const ImVec4* cpu_fine_clip_rect = NULL);
    IMGUI_API void AddBezierCubic(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, ImU32 col, float thickness, int num_segments = 0); // 三次贝塞尔曲线（4 个控制点）
    IMGUI_API void AddBezierQuadratic(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, ImU32 col, float thickness, int num_segments = 0); // 二次贝塞尔曲线（3 个控制点）


    // 通用多边形
    // - 填充函数仅支持简单多边形（无自交，无孔洞）。
    // - 凹多边形填充比凸多边形填充开销更大：其复杂度为 O(N^2)。该功能仅为方便用户而提供，主库并未使用。
    IMGUI_API void AddPolyline(const ImVec2* points, int num_points, ImU32 col, ImDrawFlags flags, float thickness);
    IMGUI_API void AddConvexPolyFilled(const ImVec2* points, int num_points, ImU32 col);
    IMGUI_API void AddConcavePolyFilled(const ImVec2* points, int num_points, ImU32 col);


    // 图像原语
    // - 请阅读常见问题解答（FAQ）以了解 ImTextureID/ImTextureRef 的含义。
    // - "p_min" 和 "p_max" 代表矩形的左上角和右下角。
    // - "uv_min" 和 "uv_max" 代表用于这些角落的归一化纹理坐标。使用 (0,0)->(1,1) 的纹理坐标通常会显示整个纹理。
    IMGUI_API void AddImage(ImTextureRef tex_ref, const ImVec2& p_min, const ImVec2& p_max, const ImVec2& uv_min = ImVec2(0, 0), const ImVec2& uv_max = ImVec2(1, 1), ImU32 col = IM_COL32_WHITE);
    IMGUI_API void AddImageQuad(ImTextureRef tex_ref, const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, const ImVec2& uv1 = ImVec2(0, 0), const ImVec2& uv2 = ImVec2(1, 0), const ImVec2& uv3 = ImVec2(1, 1), const ImVec2& uv4 = ImVec2(0, 1), ImU32 col = IM_COL32_WHITE);
    IMGUI_API void AddImageRounded(ImTextureRef tex_ref, const ImVec2& p_min, const ImVec2& p_max, const ImVec2& uv_min, const ImVec2& uv_max, ImU32 col, float rounding, ImDrawFlags flags = 0);


    // 有状态的路径 API：先添加点，然后以 PathFillConvex() 或 PathStroke() 结束
    // - 重要提示：填充图形必须始终使用顺时针绕序！抗锯齿边缘依赖于此。逆时针图形将产生“向内”的抗锯齿效果。
    // 例如：'PathArcTo(center, radius, PI * -0.5f, PI)' 是正确的，而 'PathArcTo(center, radius, PI, PI * -0.5f)' 在接下来的 PathFillConvex() 调用中将无法获得正确的抗锯齿效果。
    inline void PathClear() { _Path.Size = 0; }
    inline void PathLineTo(const ImVec2& pos) { _Path.push_back(pos); }
    inline void PathLineToMergeDuplicate(const ImVec2& pos) { if (_Path.Size == 0 || memcmp(&_Path.Data[_Path.Size - 1], &pos, 8) != 0) _Path.push_back(pos); }
    inline void PathFillConvex(ImU32 col) { AddConvexPolyFilled(_Path.Data, _Path.Size, col); _Path.Size = 0; }
    inline void PathFillConcave(ImU32 col) { AddConcavePolyFilled(_Path.Data, _Path.Size, col); _Path.Size = 0; }
    inline void PathStroke(ImU32 col, ImDrawFlags flags = 0, float thickness = 1.0f) { AddPolyline(_Path.Data, _Path.Size, col, flags, thickness); _Path.Size = 0; }
    IMGUI_API void PathArcTo(const ImVec2& center, float radius, float a_min, float a_max, int num_segments = 0);
    IMGUI_API void PathArcToFast(const ImVec2& center, float radius, int a_min_of_12, int a_max_of_12); // 为 12 分段圆使用预计算的角度
    IMGUI_API void PathEllipticalArcTo(const ImVec2& center, const ImVec2& radius, float rot, float a_min, float a_max, int num_segments = 0); // 椭圆
    IMGUI_API void PathBezierCubicCurveTo(const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, int num_segments = 0); // 三次贝塞尔曲线（4 个控制点）
    IMGUI_API void PathBezierQuadraticCurveTo(const ImVec2& p2, const ImVec2& p3, int num_segments = 0); // 二次贝塞尔曲线（3 个控制点）
    IMGUI_API void PathRect(const ImVec2& rect_min, const ImVec2& rect_max, float rounding = 0.0f, ImDrawFlags flags = 0);


    // 进阶：绘制回调
    // - 可用于修改渲染状态（更改采样器、混合模式、当前着色器）。也可用于发出自定义渲染命令（虽然难以正确实现，但确实可行）。
    // - 使用特殊的 ImDrawCallback_ResetRenderState 回调来指示后端将其渲染状态重置为默认值。
    // - 您的渲染循环必须检查 ImDrawCmd 中的 'UserCallback'，如果存在则调用该函数而非渲染三角形。所有标准后端都遵循此规则。
    // - 对于某些后端，回调函数可以通过 platform_io.Renderer_RenderState 指向的 ImGui_ImplXXXX_RenderState 结构体，访问后端暴露的特定渲染状态。
    // - 重要提示：请注意使用 size==0（复制参数本身）和 size>0（将指针指向的数据复制到缓冲区）之间不同的间接层级。
    // - 如果 userdata_size == 0：我们将原样复制/存储 'userdata' 参数。在渲染期间，它将以未修改的状态存在于 ImDrawCmd::UserCallbackData 中。
    // - 如果 userdata_size > 0，我们将拷贝并存储由 'userdata' 指向的 'userdata_size' 字节数据。这些数据存储在绘制列表（drawlist）内部的缓冲区中。ImDrawCmd::UserCallbackData 将指向该缓冲区内部，因此你需要从中检索数据。如果你预期使用动态大小的数据，你的回调函数可能需要使用 ImDrawCmd::UserCallbackDataSize。
    // - 对 userdata_size > 0 的支持是在 2024 年 10 月的 v1.91.4 版本中加入的。在此之前的代码始终只允许拷贝/存储一个简单的 void* 指针。
    IMGUI_API void AddCallback(ImDrawCallback callback, void* userdata, size_t userdata_size = 0);


    // 进阶：杂项
    IMGUI_API void AddDrawCmd(); // 如果你需要强制创建一个新的绘制调用（以允许依赖渲染/混合），这会很有用。否则，图元将尽可能地合并到同一个绘制调用中。
    IMGUI_API ImDrawList* CloneOutput() const; // 创建 CmdBuffer/IdxBuffer/VtxBuffer 的克隆。对于多线程渲染，请考虑改用来自 https://github.com/ocornut/imgui_club 的 imgui_threaded_rendering。


    // 进阶：通道 (Channels)
    // - 用于将渲染拆分为图层。通过切换通道，可以进行乱序渲染（例如，在提交背景图元之前先提交前景图元）。
    // - 用于减少绘制调用（例如，如果在多个裁剪矩形之间来回切换，建议先附加到不同的通道，最后再进行合并）
    // - 这个 API 本就不该出现在 ImDrawList 中！
    // 建议使用您自己持久化的 ImDrawListSplitter 实例，因为它们可以嵌套使用。
    // 使用 ImDrawList::ChannelsXXXX 时，您无法在已有的拆分之上再进行嵌套拆分。
    inline void ChannelsSplit(int count) { _Splitter.Split(this, count); }
    inline void ChannelsMerge() { _Splitter.Merge(this); }
    inline void ChannelsSetCurrent(int n) { _Splitter.SetCurrentChannel(this, n); }


    // 高级：图元分配 (Primitives allocations)
    // - 我们渲染三角形（三个顶点）
    // - 所有图元都需要事先通过 PrimReserve() 进行预留。
    IMGUI_API void PrimReserve(int idx_count, int vtx_count);
    IMGUI_API void PrimUnreserve(int idx_count, int vtx_count);
    IMGUI_API void PrimRect(const ImVec2& a, const ImVec2& b, ImU32 col); // 轴对齐矩形（由两个三角形组成）
    IMGUI_API void PrimRectUV(const ImVec2& a, const ImVec2& b, const ImVec2& uv_a, const ImVec2& uv_b, ImU32 col);
    IMGUI_API void PrimQuadUV(const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImVec2& d, const ImVec2& uv_a, const ImVec2& uv_b, const ImVec2& uv_c, const ImVec2& uv_d, ImU32 col);
    inline void PrimWriteVtx(const ImVec2& pos, const ImVec2& uv, ImU32 col) { _VtxWritePtr->pos = pos; _VtxWritePtr->uv = uv; _VtxWritePtr->col = col; _VtxWritePtr++; _VtxCurrentIdx++; }
    inline void PrimWriteIdx(ImDrawIdx idx) { *_IdxWritePtr = idx; _IdxWritePtr++; }
    inline void PrimVtx(const ImVec2& pos, const ImVec2& uv, ImU32 col) { PrimWriteIdx((ImDrawIdx)_VtxCurrentIdx); PrimWriteVtx(pos, uv, col); } // 写入带有唯一索引的顶点


    // 已废弃的名称
#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    inline void PushTextureID(ImTextureRef tex_ref) { PushTexture(tex_ref); } // 在 1.92.0 版本中重命名
    inline void PopTextureID() { PopTexture(); } // 在 1.92.0 版本中重命名
#endif
    //inline void AddEllipse(const ImVec2& center, float radius_x, float radius_y, ImU32 col, float rot = 0.0f, int num_segments = 0, float thickness = 1.0f) { AddEllipse(center, ImVec2(radius_x, radius_y), col, rot, num_segments, thickness); } // 在 1.90.5 版本中已废弃 (2024 年 3 月)
    //inline void AddEllipseFilled(const ImVec2& center, float radius_x, float radius_y, ImU32 col, float rot = 0.0f, int num_segments = 0) { AddEllipseFilled(center, ImVec2(radius_x, radius_y), col, rot, num_segments); } // 在 1.90.5 版本中已废弃 (2024 年 3 月)
    //inline void PathEllipticalArcTo(const ImVec2& center, float radius_x, float radius_y, float rot, float a_min, float a_max, int num_segments = 0) { PathEllipticalArcTo(center, ImVec2(radius_x, radius_y), rot, a_min, a_max, num_segments); } // 已于 1.90.5 版本废弃 (2024 年 3 月)
    //inline void AddBezierCurve(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, ImU32 col, float thickness, int num_segments = 0) { AddBezierCubic(p1, p2, p3, p4, col, thickness, num_segments); } // 已在 1.80 版本（2021 年 1 月）中弃用
    //inline void PathBezierCurveTo(const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, int num_segments = 0) { PathBezierCubicCurveTo(p2, p3, p4, num_segments); } // 已在 1.80 版本（2021 年 1 月）中弃用


    // [内部辅助函数]
    IMGUI_API void _SetDrawListSharedData(ImDrawListSharedData* data);
    IMGUI_API void _ResetForNewFrame();
    IMGUI_API void _ClearFreeMemory();
    IMGUI_API void _PopUnusedDrawCmd();
    IMGUI_API void _TryMergeDrawCmds();
    IMGUI_API void _OnChangedClipRect();
    IMGUI_API void _OnChangedTexture();
    IMGUI_API void _OnChangedVtxOffset();
    IMGUI_API void _SetTexture(ImTextureRef tex_ref);
    IMGUI_API int _CalcCircleAutoSegmentCount(float radius) const;
    IMGUI_API void _PathArcToFastEx(const ImVec2& center, float radius, int a_min_sample, int a_max_sample, int a_step);
    IMGUI_API void _PathArcToN(const ImVec2& center, float radius, float a_min, float a_max, int num_segments);
};


// 渲染 Dear ImGui 帧所需的所有绘制数据
// （注：此处的样式和命名规范略有不统一，目前为了向后兼容性而保留它们，
// 因为这是库中暴露的最古老的结构之一！基本上，ImDrawList == CmdList）
struct ImDrawData
{
    bool Valid; // 仅在调用 Render() 之后且在调用下一次 NewFrame() 之前有效。
    int CmdListsCount; // == CmdLists.Size。（已废弃：因历史原因存在）。要渲染的 ImDrawList* 数量。
    int TotalIdxCount; // 为了方便起见，所有 ImDrawList 的 IdxBuffer.Size 之和
    int TotalVtxCount; // 为了方便起见，所有 ImDrawList 的 VtxBuffer.Size 之和
    ImVector<ImDrawList*> CmdLists; // 待渲染的 ImDrawList* 数组。这些 ImDrawList 由 ImGuiContext 持有，此处仅为指向它们的指针。
    ImVec2 DisplayPos; // 待渲染视口的左上角位置（== 待使用的正交投影矩阵的左上角）（对于主视口 == GetMainViewport()->Pos，在大多数单视口应用程序中 == (0.0)）
    ImVec2 DisplaySize; // 待渲染视口的尺寸（对于主视口等于 GetMainViewport()->Size，在大多数单视口应用中等于 io.DisplaySize）
    ImVec2 FramebufferScale; // DisplaySize 每个单位对应的像素数量。从 viewport->FramebufferScale 复制而来（对于主视口等于 io.DisplayFramebufferScale）。在普通显示器上通常为 (1,1)，在配备 Retina 显示屏的 OSX 上为 (2,2)。
    ImGuiViewport* OwnerViewport; // 携带该 ImDrawData 实例的视口，可能对渲染器有用（通常没用）。
    ImVector<ImTextureData*>* Textures; // 待更新的纹理列表。大多数情况下该列表由所有 ImDrawData 共享，仅包含 1 个纹理且不需要任何更新。这几乎总是指向 ImGui::GetPlatformIO().Textures[]。如果你想手动更新纹理，可以将其覆盖或设置为 NULL。


    // 函数
    ImDrawData() { Clear(); }
    IMGUI_API void Clear();
    IMGUI_API void AddDrawList(ImDrawList* draw_list); // 将外部绘制列表添加到现有 ImDrawData 的辅助函数。
    IMGUI_API void DeIndexAllBuffers(); // 辅助函数，用于将所有缓冲区从索引格式转换为非索引格式，以防你无法渲染索引数据。注意：此操作速度较慢，且极有可能浪费资源。请始终优先使用索引渲染！
    IMGUI_API void ScaleClipRects(const ImVec2& fb_scale); // 辅助函数，用于缩放每个 ImDrawCmd 的 ClipRect 字段。如果你的最终输出缓冲区缩放比例与 Dear ImGui 预期的不同，或者你的窗口分辨率与帧缓冲区分辨率存在差异，请使用此函数。
};


//-----------------------------------------------------------------------------
// [SECTION] 纹理 API (ImTextureFormat, ImTextureStatus, ImTextureRect, ImTextureData)
//-----------------------------------------------------------------------------
// 原则上，用户/应用程序代码唯一需要关心的底层数据类型是 'ImTextureRef' 和 'ImTextureID'。
// 它们在本头文件的上方定义。请阅读其说明以了解 ImTextureRef 和 ImTextureID 之间的区别。
对于所有其他 ImTextureXXXX 类型：只有核心库和渲染器后端需要了解并关注它们。
//-----------------------------------------------------------------------------


#undef Status // X11 头文件泄露了此定义。


我们有意仅支持有限数量的纹理格式，以减轻 CPU 端代码和扩展的负担。
大多数标准后端仅支持 RGBA32，但我们为低资源 / 嵌入式系统提供了一个单通道选项。
enum ImTextureFormat
{
    ImTextureFormat_RGBA32, // 每像素 4 个分量，每个分量为无符号 8 位。总大小 = 纹理宽度 * 纹理高度 * 4
    ImTextureFormat_Alpha8, // 每像素 1 个分量，每个分量为无符号 8 位。总大小 = 纹理宽度 * 纹理高度
};


// 用于与渲染器后端通信的纹理状态。
enum ImTextureStatus
{
    ImTextureStatus_OK,
    ImTextureStatus_Destroyed, // 后端已销毁该纹理。
    ImTextureStatus_WantCreate, // 请求后端创建该纹理。完成后请将状态设为 OK。
    ImTextureStatus_WantUpdates, // 请求后端更新特定的像素块（写入从未被使用过的纹理部分）。完成后请将状态设为 OK。
    ImTextureStatus_WantDestroy, // 请求后端销毁该纹理。完成后请将状态设为 Destroyed。
};


// 纹理内矩形区域的坐标。
// 当纹理处于 ImTextureStatus_WantUpdates 状态时，我们会提供一个需要复制到图形系统的独立矩形列表。
// 你可以使用 ImTextureData::Updates[] 列表，或者使用 ImTextureData::UpdateBox 来指定单个边界框。
struct ImTextureRect
{
    unsigned short x, y; // 待更新矩形的左上角坐标
    unsigned short w, h; // 待更新矩形的尺寸（以像素为单位）
};


// Dear ImGui 所使用的纹理规格和像素存储。
// 这仅对 (1) 核心库和 (2) 后端有用。终端用户/应用程序无需关心此内容。
// 渲染器后端将创建此内容的 GPU 端版本。
// 为什么我们要存储两个标识符：TexID 和 BackendUserData？
// - ImTextureID TexID = 存储在 ImDrawCmd 中的底层标识符。ImDrawCmd 可以引用非后端创建的纹理，且这些纹理可能没有对应的 ImTextureData。
// - void* BackendUserData = 用于后端自身簿记的高层不透明存储。某些后端仅使用 TexID 即可满足需求，不需要同时使用两者。
// 在下表中：谁负责读/写各个字段？'r'=读，'w'=写，'core'=主库，'backend'=渲染器后端
struct ImTextureData
{
    //------------------------------------------ 核心 / 后端 ---------------------------------------
    int UniqueID; // w - // [调试] 顺序索引，用于在调试/打印时识别纹理。在每个图集中是唯一的。
    ImTextureStatus Status; // rw rw // ImTextureStatus_OK/_WantCreate/_WantUpdates/_WantDestroy。请务必使用 SetStatus() 进行修改！
    void* BackendUserData; // - rw // 后端使用的便捷存储。某些后端可能仅使用 TexID 就足够了。
    ImTextureID TexID; // r w // 后端特定的纹理标识符。请务必使用 SetTexID() 进行修改！该标识符将存储在 ImDrawCmd::GetTexID() 中，并传递给后端的 RenderDrawData 函数。
    ImTextureFormat Format; // w r // ImTextureFormat_RGBA32 (默认) 或 ImTextureFormat_Alpha8
    int Width; // w r // 纹理宽度
    int Height; // w r // 纹理高度
    int BytesPerPixel; // w r // 4 或 1
    unsigned char* Pixels; // w r // 指向持有 'Width*Height' 个像素和 'Width*Height*BytesPerPixels' 字节数据的缓冲区的指针。
    ImTextureRect UsedRect; // w r // 包含所有已完成和排队中的 Updates[] 的包围盒。
    ImTextureRect UpdateRect; // w r // 包含所有排队中的 Updates[] 的包围盒。
    ImVector<ImTextureRect> Updates; // w r // 单个更新操作的数组。
    int UnusedFrames; // w r // 为了方便某些后端处理 Status==WantDestroy：这是纹理未被使用的连续帧数。当 Status==WantDestroy 时，该值始终 >0。
    unsigned short RefCount; // w r // 使用此纹理的上下文数量。在后端关闭期间使用。
    bool UseColors; // w r // 告知纹理数据是否已知使用了彩色（而不仅仅是白色 + Alpha）。
    bool WantDestroyNextFrame; // rw - // [内部] 已排队准备在下一帧设置 ImTextureStatus_WantDestroy。在当前帧中可能仍在使用。


    // 函数
    ImTextureData() { memset(this, 0, sizeof(*this)); Status = ImTextureStatus_Destroyed; TexID = ImTextureID_Invalid; }
    ~ImTextureData() { DestroyPixels(); }
    IMGUI_API void Create(ImTextureFormat format, int w, int h);
    IMGUI_API void DestroyPixels();
    void* GetPixels() { IM_ASSERT(Pixels != NULL); return Pixels; }
    void* GetPixelsAt(int x, int y) { IM_ASSERT(Pixels != NULL); return Pixels + (x + y * Width) * BytesPerPixel; }
    int GetSizeInBytes() const { return Width * Height * BytesPerPixel; }
    int GetPitch() const { return Width * BytesPerPixel; }
    ImTextureRef GetTexRef() { ImTextureRef tex_ref; tex_ref._TexData = this; tex_ref._TexID = ImTextureID_Invalid; return tex_ref; }
    ImTextureID GetTexID() const { return TexID; }


    // 由渲染器后端调用
    // - 在响应纹理请求后调用 SetTexID() 和 SetStatus()。切勿直接修改 TexID 和 Status！
    // - 后端可能会决定销毁一个我们并未请求销毁的纹理，这是允许的（例如释放资源），但我们会立即将该纹理重新设为 _WantCreate 模式。
    void SetTexID(ImTextureID tex_id) { TexID = tex_id; }
    void SetStatus(ImTextureStatus status) { Status = status; if (status == ImTextureStatus_Destroyed && !WantDestroyNextFrame && Pixels != nullptr) Status = ImTextureStatus_WantCreate; }
};


//-----------------------------------------------------------------------------
// [SECTION] 字体 API (ImFontConfig, ImFontGlyph, ImFontAtlasFlags, ImFontAtlas, ImFontGlyphRangesBuilder, ImFont)
//-----------------------------------------------------------------------------


// 字体输入/源（未来我们可能会将其重命名为 ImFontSource）
struct ImFontConfig
{
    // 数据源
    char Name[40]; // <auto> // 名称（严格来说是为了方便调试，因此缓冲区大小有限）
    void* FontData; // // TTF/OTF 数据
    int FontDataSize; // // TTF/OTF 数据大小
    bool FontDataOwnedByAtlas; // true // TTF/OTF 数据所有权由所有者 ImFontAtlas 接管（将自行删除内存）。自 1.92 版本起，该数据需要在 Atlas 的整个生命周期内持续存在。


    // 选项
    bool MergeMode; // false // 合并到前一个 ImFont 中，这样你可以将多个输入字体组合成一个 ImFont（例如：ASCII 字体 + 图标 + 日语字形）。在合并不同高度的字体时，你可能需要使用 GlyphOffset.y。
    bool PixelSnapH; // false // 将每个字形的 AdvanceX 对齐到像素边界。这会阻止小数级别的字体大小正常工作！例如，当你将一个非像素对齐的字体与默认字体合并时，这很有用。如果启用此项，你可以将 OversampleH/V 设置为 1。
    ImS8 OversampleH; // 0 (2) // 以更高质量进行光栅化，以实现亚像素定位。0 == 自动 == 根据大小设为 1 或 2。注意 2 和 3 之间的区别微乎其微。对于大字形，你可以将其降低到 1 以节省内存。详情请阅读 https://github.com/nothings/stb/blob/master/tests/oversample/README.md。
    ImS8 OversampleV; // 0 (1) // 以更高质量进行光栅化以实现亚像素定位。0 == 自动 == 1。这其实没什么用，因为我们不在 Y 轴上使用亚像素位置。
    ImWchar EllipsisChar; // 0 // 显式指定省略号字符的 Unicode 码点。当字体合并时，将使用第一个指定的省略号。
    float SizePixels; // // 光栅化器的输出像素大小（大致对应于生成的字体高度）。
    const ImWchar* GlyphRanges; // NULL // *旧版遗留* 数组数据在字体存续期间必须保持有效。指向用户提供的 Unicode 范围列表的指针（每个范围 2 个值，包含边界值，列表以零终止）。
    const ImWchar* GlyphExcludeRanges; // NULL // 指向用户提供的 Unicode 范围列表的指针（每个范围 2 个值，包含边界值，以 0 结尾）。这与 GlyphRanges[] 非常相似，但旨在合并具有重叠字符的字体时，从特定字体源中排除某些范围。请使用“输入字符重叠检测工具 (Input Glyphs Overlap Detection Tool)”来查找重叠范围。
    //ImVec2 GlyphExtraSpacing; // 0, 0 // （已移除，因其似乎已过时。如果您正在使用此功能，请报告）。渲染时字符之间的额外间距（以像素为单位）：本质上是增加到 glyph->AdvanceX。目前仅支持 X 轴。
    ImVec2 GlyphOffset; // 0, 0 // 偏移此字体输入的所有字符（以像素为单位）。此值为默认大小下的绝对值，其他大小将按比例缩放此值。
    float GlyphMinAdvanceX; // 0 // 字符的最小 AdvanceX，设置最小值以对齐字体图标，同时设置最小值/最大值以强制使用等宽字体。此值为默认大小下的绝对值，其他大小将按比例缩放此值。
    float GlyphMaxAdvanceX; // FLT_MAX // 字符的最大水平间距 (AdvanceX)
    float GlyphExtraAdvanceX; // 0 // 字符之间的额外间距（以像素为单位）。如果您正在使用此项，请联系我们。 // FIXME-NEWATLAS: 故意未缩放
    ImU32 FontNo; // 0 // TTF/OTF 文件中的字体索引
    unsigned int FontLoaderFlags; // 0 // 自定义字体构建器的设置。这取决于构建器的具体实现。如果不确定，请保持为零。
    //unsigned int FontBuilderFlags; // -- // [在 1.92 版本中重命名] 请使用 FontLoaderFlags。
    float RasterizerMultiply; // 1.0f // 线性地加亮（>1.0f）或变暗（<1.0f）字体输出。加亮小字体可能是提高其可读性的一个不错方案。这是一个比较笨的功能，我们将来可能会将其移除。
    float RasterizerDensity; // 1.0f // [遗留参数：仅在不支持 ImGuiBackendFlags_RendererHasTextures 时有意义] 光栅化的 DPI 缩放倍数。不改变其他字体度量：这使得在缩放显示时可以轻松地在（例如）100% 和 400% 字体之间切换，或处理 Retina 屏幕。重要提示：如果你更改此项，通常需要按此值的倒数相应地增加/减少字体缩放（font scale），否则显示质量可能会下降。
    float ExtraSizeScale; // 1.0f // 在 SizePixels 之上的额外光栅化缩放。


    // [内部]
    ImFontFlags Flags; // 字体标志（暂请勿使用，将在即将发布的 1.92.X 更新中公开）
    ImFont* DstFont; // 目标字体（由于我们正在合并字体，多个 ImFontConfig 可能会指向同一个字体）
    const ImFontLoader* FontLoader; // 此源的自定义字体后端（默认源是存储在 ImFontAtlas 中的那个）
    void* FontLoaderData; // 字体加载器不透明存储（按字体配置）


#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    bool PixelSnapV; // true // [1.91.6 已废弃] 将缩放后的 GlyphOffset.y 对齐到像素边界。
#endif
    IMGUI_API ImFontConfig();
};


// 保存单个字形的渲染数据。
//（注意：某些语言解析器可能无法转换位域成员，在这种情况下，可以考虑存储为单个 u32，或者我们可以对此进行重构）
struct ImFontGlyph
{
    unsigned int Colored : 1; // 标志位，指示字形带有颜色，通常应忽略着色（使其在小端序上无需移位即可使用，因为此标志常用于循环中）
    unsigned int Visible : 1; // 标记字形是否没有可见像素（例如空格）。允许在渲染时提前退出。
    unsigned int SourceIdx : 4; // 在父字体中的源索引
    unsigned int Codepoint : 26; // 0x0000..0x10FFFF
    float AdvanceX; // 推进光标/布局位置的水平距离。
    float X0, Y0, X1, Y1; // 字形边角。相对于当前光标/布局位置的偏移量。
    float U0, V0, U1, V1; // 当前 ImFontAtlas->TexRef 值的纹理坐标。相当于使用 PackId 调用 GetCustomRect() 的缓存结果。
    int PackId; // [内部] ImFontAtlasRectId 值（待修复：冷数据，是否可以移至别处？）


    ImFontGlyph() { memset(this, 0, sizeof(*this)); PackId = -1; }
};


// 用于从文本/字符串数据构建字形范围（glyph ranges）的辅助类。将应用程序的字符串/字符输入其中，然后调用 BuildRanges()。
// 这本质上是一个紧凑打包的 64k 布尔值向量 = 8KB 存储空间。
struct ImFontGlyphRangesBuilder
{
    ImVector<ImU32> UsedChars; // 为每个 Unicode 码点存储 1 位（0=未使用，1=已使用）


    ImFontGlyphRangesBuilder() { Clear(); }
    inline void Clear() { int size_in_bytes = (IM_UNICODE_CODEPOINT_MAX + 1) / 8; UsedChars.resize(size_in_bytes / (int)sizeof(ImU32)); memset(UsedChars.Data, 0, (size_t)size_in_bytes); }
    inline bool GetBit(size_t n) const { int off = (int)(n >> 5); ImU32 mask = 1u << (n & 31); return (UsedChars[off] & mask) != 0; } // 获取数组中的第 n 位
    inline void SetBit(size_t n) { int off = (int)(n >> 5); ImU32 mask = 1u << (n & 31); UsedChars[off] |= mask; } // 设置数组中的第 n 位
    inline void AddChar(ImWchar c) { SetBit(c); } // 添加字符
    IMGUI_API void AddText(const char* text, const char* text_end = NULL); // 添加字符串（UTF-8 字符串中的每个字符都将被添加）
    IMGUI_API void AddRanges(const ImWchar* ranges); // 添加范围，例如 builder.AddRanges(ImFontAtlas::GetGlyphRangesDefault()) 以强制添加所有 ASCII/Latin+Ext 字符
    IMGUI_API void BuildRanges(ImVector<ImWchar>* out_ranges); // 输出新范围
};


// 指向图集中矩形的模糊标识符。无效时为 -1。
// 矩形可能会移动且 UV 可能会失效，请使用 GetCustomRect() 来重新获取。
typedef int ImFontAtlasRectId;
#define ImFontAtlasRectId_Invalid -1


// 使用自定义矩形时 ImFontAtlas::GetCustomRect() 的输出。
// 这些值不应被缓存或存储，因为它们仅对当前 atlas->TexRef 的值有效
//（理论上这派生自 ImTextureRect，但出于某些原因我们使用了独立的结构体）
struct ImFontAtlasRect
{
    unsigned short x, y; // 位置（在当前纹理中）
    unsigned short w, h; // 尺寸
    ImVec2 uv0, uv1; // UV 坐标（在当前纹理中）


    ImFontAtlasRect() { memset(this, 0, sizeof(*this)); }
};


// ImFontAtlas 构建标志
enum ImFontAtlasFlags_
{
    ImFontAtlasFlags_None = 0,
    ImFontAtlasFlags_NoPowerOfTwoHeight = 1 << 0, // 不要将高度向上取整为 2 的幂
    ImFontAtlasFlags_NoMouseCursors = 1 << 1, // 不要将软件鼠标光标构建到图集中（节省少量纹理内存）
    ImFontAtlasFlags_NoBakedLines = 1 << 2, // 不要将粗线纹理构建到图集中（节省少量纹理内存，允许支持点/最近邻过滤）。AntiAliasedLinesUseTex 功能会使用它们，否则将使用多边形进行渲染（对 CPU/GPU 消耗更高）。
};


// 将多个 TTF/OTF 字体加载并光栅化到同一张纹理中。字体图集（Font Atlas）将构建一张包含以下内容的单一纹理：
// - 一个或多个字体。
// - 渲染 Dear ImGui 所需形状时用到的自定义图形数据。
// - 用于软件光标渲染的鼠标光标形状（除非在字体图集中设置了 'Flags |= ImFontAtlasFlags_NoMouseCursors'）。
// - 如果你不调用任何 AddFont*** 函数，程序将自动为你加载代码中嵌入的默认字体。
// 渲染后端负责将纹理上传到你的图形 API：
// - ImGui_ImplXXXX_RenderDrawData() 函数通常会遍历 platform_io->Textures[]，以创建/更新/销毁每个 ImTextureData 实例。
// - 随后后端会设置 ImTextureData 的 TexID 和 BackendUserData。
// - 纹理 ID 会在渲染期间传回给您以识别纹理。有关更多详细信息，请阅读关于 ImTextureID/ImTextureRef 的常见问题解答（FAQ）条目。
// 旧版路径：
// - 调用 Build() + GetTexDataAsAlpha8() 或 GetTexDataAsRGBA32() 来构建并获取像素数据。
// - 调用 SetTexID(my_tex_id); 并以适合您图形 API 的格式传递指向纹理的指针/标识符。
// 常见陷阱：
// - 如果你向 AddFont*** 函数传递了 'glyph_ranges' 数组，请务必确保该数组在
// 图集构建完成（即调用 GetTexData*** 或 Build() 时）之前一直有效。我们仅拷贝指针，而不拷贝数据。
// - 重要提示：默认情况下，AddFontFromMemoryTTF() 会接管数据的所有权。尽管我们不会对其进行写操作，但我们会在销毁时释放该指针。
// 你可以将 font_cfg->FontDataOwnedByAtlas 设置为 false 以保留数据的所有权，这样它就不会被释放。
// - 尽管许多函数带有“TTF”后缀，但同样支持 OTF 数据。
// - 这是一个旧的 API，由于这些及其他各种原因，目前使用起来比较别扭！我们将在未来解决这些问题！
struct ImFontAtlas
{
    IMGUI_API ImFontAtlas();
    IMGUI_API ~ImFontAtlas();
    IMGUI_API ImFont* AddFont(const ImFontConfig* font_cfg);
    IMGUI_API ImFont* AddFontDefault(const ImFontConfig* font_cfg = NULL); // 在 AddFontDefaultVector() 和 AddFontDefaultBitmap() 之间进行选择。
    IMGUI_API ImFont* AddFontDefaultVector(const ImFontConfig* font_cfg = NULL); // 内置的可缩放字体。推荐在任何较大字号下使用。
    IMGUI_API ImFont* AddFontDefaultBitmap(const ImFontConfig* font_cfg = NULL); // 内置的经典像素级清晰字体。推荐在 13px 大小且不缩放的情况下使用。
    IMGUI_API ImFont* AddFontFromFileTTF(const char* filename, float size_pixels = 0.0f, const ImFontConfig* font_cfg = NULL, const ImWchar* glyph_ranges = NULL);
    IMGUI_API ImFont* AddFontFromMemoryTTF(void* font_data, int font_data_size, float size_pixels = 0.0f, const ImFontConfig* font_cfg = NULL, const ImWchar* glyph_ranges = NULL); // 注意：'ttf_data' 的所有权将转移给 ImFontAtlas！它将在图集（atlas）销毁后被删除。将 font_cfg->FontDataOwnedByAtlas 设置为 false 可保留数据所有权，这样它就不会被释放。
    IMGUI_API ImFont* AddFontFromMemoryCompressedTTF(const void* compressed_font_data, int compressed_font_data_size, float size_pixels = 0.0f, const ImFontConfig* font_cfg = NULL, const ImWchar* glyph_ranges = NULL); // 'compressed_font_data' 仍由调用者所有。请使用 binary_to_compressed_c.cpp 进行压缩。
    IMGUI_API ImFont* AddFontFromMemoryCompressedBase85TTF(const char* compressed_font_data_base85, float size_pixels = 0.0f, const ImFontConfig* font_cfg = NULL, const ImWchar* glyph_ranges = NULL); // 'compressed_font_data_base85' 仍由调用者所有。请使用带有 -base85 参数的 binary_to_compressed_c.cpp 进行压缩。
    IMGUI_API void RemoveFont(ImFont* font);


    IMGUI_API void Clear(); // 清除所有内容（输入字体、输出字形/纹理）。
    IMGUI_API void CompactCache(); // 压缩缓存的字形和纹理。
    IMGUI_API void SetFontLoader(const ImFontLoader* font_loader); // 在运行时更改字体加载器。


    // 由于我们正在向新的字体系统过渡，预计这些功能很快就会被废弃：
    IMGUI_API void ClearInputData(); // [已废弃] 清除输入数据（所有 ImFontConfig 结构，包括尺寸、TTF 数据、字符范围等） = 所有用于构建纹理和字体的数据。
    IMGUI_API void ClearFonts(); // [已废弃] 清除输入+输出字体数据（等同于 ClearInputData() + 字符存储、UV 坐标）。
    IMGUI_API void ClearTexData(); // [已废弃] 清除纹理数据的 CPU 端副本。在纹理复制到显存后，此操作可节省内存。


#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    // 构建图集 + 获取像素数据的旧版路径。
    // - 用户负责将像素复制到显存中（例如，使用您的引擎创建一个纹理）。然后使用 SetTexID() 存储您的纹理句柄。
    // - 步幅（Pitch）始终等于 宽度 * 每像素字节数 (1 或 4)
    // - 提供以 RGBA32 格式构建是为了方便和兼容性，但请注意，除非你手动操作或将颜色数据复制到
    // 纹理中（例如使用 AddCustomRect*** API 时），否则输出的 RGB 像素将始终为白色（约浪费 75% 的内存/带宽）。
    // - 从 1.92 版本开始，对于支持 ImGuiBackendFlags_RendererHasTextures 的后端：
    // - 不再需要调用 Build()、GetTexDataAsAlpha8()、GetTexDataAsRGBA32()。
    // - 在后端中：在完成纹理创建后，将对 ImFontAtlas::SetTexID() 的调用替换为对 ImTextureData::SetTexID() 的调用。
    IMGUI_API bool Build(); // 构建像素数据。GetTexData*** 函数会自动为你调用此函数。
    IMGUI_API void GetTexDataAsAlpha8(unsigned char** out_pixels, int* out_width, int* out_height, int* out_bytes_per_pixel = NULL); // 每像素 1 字节
    IMGUI_API void GetTexDataAsRGBA32(unsigned char** out_pixels, int* out_width, int* out_height, int* out_bytes_per_pixel = NULL); // 每像素 4 字节
    void SetTexID(ImTextureID id) { IM_ASSERT(TexRef._TexID == ImTextureID_Invalid); TexRef._TexData->TexID = id; } // 由旧版后端调用。可能在纹理创建之前调用。
    void SetTexID(ImTextureRef id) { IM_ASSERT(TexRef._TexID == ImTextureID_Invalid && id._TexData == NULL); TexRef._TexData->TexID = id._TexID; } // 由旧版后端调用。
    bool IsBuilt() const { return Fonts.Size > 0 && TexIsBuilt; } // 略有歧义：用于检测用户是否未构建纹理，但实际上我们应该检查 TexID != 0，除非这取决于具体的后端实现。
#endif


    //-------------------------------------------
    // 字符范围（Glyph Ranges）
    //-------------------------------------------


    // 自 1.92 版本起：仅当您的后端不支持 ImGuiBackendFlags_RendererHasTextures 时，指定字符范围（glyph ranges）才是有效/必要的！
    IMGUI_API const ImWchar* GetGlyphRangesDefault(); // 基础拉丁语，扩展拉丁语
#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    // 用于获取常用 Unicode 范围列表的辅助函数（每个范围包含 2 个值，值为闭区间，列表以零终止）
    // 注意：请确保您的字符串是 UTF-8 编码，而不是本地代码页编码。
    // 详情请参阅 https://github.com/ocornut/imgui/blob/master/docs/FONTS.md/#about-utf-8-encoding。
    // 注意：可以考虑使用 ImFontGlyphRangesBuilder 从文本数据中构建字符范围。
    IMGUI_API const ImWchar* GetGlyphRangesGreek(); // 默认字符 + 希腊语和科普特语
    IMGUI_API const ImWchar* GetGlyphRangesKorean(); // 默认字符 + 韩文字符
    IMGUI_API const ImWchar* GetGlyphRangesJapanese(); // 默认字符 + 平假名、片假名、半角字符、精选的 2999 个常用汉字
    IMGUI_API const ImWchar* GetGlyphRangesChineseFull(); // 默认字符 + 半角字符 + 日语平假名/片假名 + 约 21000 个 CJK 统一汉字全集
    IMGUI_API const ImWchar* GetGlyphRangesChineseSimplifiedCommon();// 默认字符 + 半角字符 + 日语平假名/片假名 + 2500 个常用简体中文字符集
    IMGUI_API const ImWchar* GetGlyphRangesCyrillic(); // 默认字符 + 约 400 个西里尔字母
    IMGUI_API const ImWchar* GetGlyphRangesThai(); // 默认字符 + 泰文字符
    IMGUI_API const ImWchar* GetGlyphRangesVietnamese(); // 默认字符 + 越南语字符
#endif


    //-------------------------------------------
    // [ALPHA] 自定义矩形/字形 API
    //-------------------------------------------


    // 注册并获取自定义矩形
    // - 您可以出于自己的目的，请求将任意矩形打包进图集中。
    // - 自 1.92.0 版本起，打包操作会在函数调用时立即完成（此前打包是在 Build 调用期间进行的）。
    // - 您可以在调用 AddCustomRect() 函数后立即将像素渲染到纹理中。
    // - 非常重要：
    // - 在调用 ImGui 或 ImFontAtlas 函数时，纹理可能随时被创建或调整大小。
    // - 这将导致矩形数据（如 UV 坐标）失效。请始终使用来自 GetCustomRect() 的最新值。
    // - UV 坐标与当前的纹理标识符（即 'atlas->TexRef'）相关联。TexRef 和 UV 坐标通常会同时发生变化。
    // - 如果你在自定义矩形中渲染彩色输出：请设置 'atlas->TexPixelsUseColors = true'，因为这可以帮助某些后端决定首选的纹理格式。
    // - 查阅 docs/FONTS.md 以获取有关使用彩色图标的更多详情。
    // - 注意：此 API 可能会进一步重构，以便更好地支持诸如多显示器、不同的 DPI 设置等功能。
    // - (1.92 版本之前的名称) ------------> (1.92 版本的名称)
    // - GetCustomRectByIndex() --> 使用 GetCustomRect()
    // - CalcCustomRectUV() --> 请使用 GetCustomRect() 并读取 uv0, uv1 字段。
    // - AddCustomRectRegular() --> 已重命名为 AddCustomRect()
    // - AddCustomRectFontGlyph() --> 建议在 ImFontConfig 中使用自定义的 ImFontLoader
    // - ImFontAtlasCustomRect --> 已重命名为 ImFontAtlasRect
    IMGUI_API ImFontAtlasRectId AddCustomRect(int width, int height, ImFontAtlasRect* out_r = NULL);// 注册一个矩形。出错时返回 -1 (ImFontAtlasRectId_Invalid)。
    IMGUI_API void RemoveCustomRect(ImFontAtlasRectId id); // 注销一个矩形。现有的像素将保留在纹理中，直到重新调整大小或进行垃圾回收。
    IMGUI_API bool GetCustomRect(ImFontAtlasRectId id, ImFontAtlasRect* out_r) const; // 获取当前纹理的矩形坐标。立即生效，切勿存储此结果（见上文说明）！


    //-------------------------------------------
    // 成员变量
    //-------------------------------------------


    // 输入
    ImFontAtlasFlags Flags; // 构建标志（详见 ImFontAtlasFlags_）
    ImTextureFormat TexDesiredFormat; // 期望的纹理格式（默认为 ImTextureFormat_RGBA32，但可以更改为 ImTextureFormat_Alpha8）。
    int TexGlyphPadding; // FIXME：应更名为 "TexPackPadding"。纹理中字形之间的间距（像素）。默认为 1。如果您的渲染方法不依赖双线性过滤，可以将其设置为 0（同时需要设置 AntiAliasedLinesUseTex = false）。
    int TexMinWidth; // 期望的纹理最小宽度。必须是 2 的幂。默认为 512。
    int TexMinHeight; // 期望的纹理最小高度。必须是 2 的幂。默认为 128。
    int TexMaxWidth; // 期望的纹理最大宽度。必须是 2 的幂。默认为 8192。
    int TexMaxHeight; // 期望的纹理最大高度。必须是 2 的幂。默认为 8192。
    void* UserData; // 存储您自定义的图集相关用户数据（例如，当您有多个字体图集时）。


    // 输出
    // - 由于纹理是动态创建/调整大小的，当前的纹理标识符可能会在帧内的 *任何时间* 发生变化。
    // - 这不应对您产生影响，因为您始终可以使用最新的值。但请注意，任何预计算的 UV 坐标仅对当前的 TexRef 有效。
#ifdef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    ImTextureRef TexRef; // 最新的纹理标识符 == TexData->GetTexRef()。
#else
    union { ImTextureRef TexRef; ImTextureRef TexID; }; // 最新的纹理标识符 == TexData->GetTexRef()。 // 在 1.92.0 版本中将 TexID 重命名为 TexRef。
#endif
    ImTextureData* TexData; // 最新纹理。


    // [内部]
    ImVector<ImTextureData*> TexList; // 纹理列表（通常 TexList.Size == 1）。TexData 始终等于 TexList.back()。请勿直接使用，请改用 GetDrawData().Textures[] 或 GetPlatformIO().Textures[]！
    bool Locked; // 如果不支持纹理更新（TexUpdates），则在 ImGui::NewFrame()..EndFrame() 作用域内被标记为锁定。任何修改图集的尝试都将触发断言。
    bool RendererHasTextures;// 来自支持上下文的 (BackendFlags & ImGuiBackendFlags_RendererHasTextures) 副本。
    bool TexIsBuilt; // 当纹理构建完成并与当前字体输入匹配时设置。主要用于旧版的 IsBuilt() 调用。
    bool TexPixelsUseColors; // 告知纹理数据是否已知使用了颜色（而不仅仅是 Alpha 通道），以帮助后端选择格式或转换过程。
    ImVec2 TexUvScale; // = (1.0f/TexData->TexWidth, 1.0f/TexData->TexHeight)。可能会随着新纹理的创建而改变。
    ImVec2 TexUvWhitePixel; // 白色像素的纹理坐标。随着新纹理的创建可能会发生变化。
    ImVector<ImFont*> Fonts; // 持有所有由 AddFont* 返回的字体。Fonts[0] 是调用 ImGui::NewFrame() 时的默认字体，使用 ImGui::PushFont()/PopFont() 来更改当前字体。
    ImVector<ImFontConfig> Sources; // 源/配置数据
    ImVec4 TexUvLines[IM_DRAWLIST_TEX_LINES_WIDTH_MAX + 1]; // 预烘焙抗锯齿线条的 UV 坐标
    int TexNextUniqueID; // 下一个要存储在 TexData->UniqueID 中的值
    int FontNextUniqueID; // 下一个要存储在 ImFont->FontID 中的值
    ImVector<ImDrawListSharedData*> DrawListSharedDatas; // 此图集的用户列表。通常每个 Dear ImGui 上下文对应一个。
    ImFontAtlasBuilder* Builder; // 数据的非公开接口，不需要公开，且在重新构建时可能会被丢弃。
    const ImFontLoader* FontLoader; // 字体加载器不透明接口（当定义了 IMGUI_ENABLE_FREETYPE 时默认使用 FreeType，否则默认使用 stb_truetype）。可在运行时使用 SetFontLoader() 进行更改。
    const char* FontLoaderName; // 字体加载器名称（用于显示，例如在“关于”框中） == FontLoader->Name
    void* FontLoaderData; // 字体后端不透明存储
    unsigned int FontLoaderFlags; // 字体加载器的共享标志（适用于所有字体）。这取决于具体的构建实现（例如：在 ImFontConfig 中也提供了针对单个字体的覆盖选项）。
    int RefCount; // 使用此图集的上下文数量
    ImGuiContext* OwnerContext; // 拥有该图集的上下文将负责其更新和销毁。


    // [已废弃]
#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
// 遗留功能：你可以请求将矩形映射为字体字符（给定字体 + Unicode 码点），以便渲染自定义彩色图标并将其作为普通字符使用。--> 建议改用自定义 ImFontLoader。
    ImFontAtlasRect TempRect; // 用于旧版的 GetCustomRectByIndex() API
    inline ImFontAtlasRectId AddCustomRectRegular(int w, int h) { return AddCustomRect(w, h); } // 在 1.92.0 版本中重命名
    inline const ImFontAtlasRect* GetCustomRectByIndex(ImFontAtlasRectId id) { return GetCustomRect(id, &TempRect) ? &TempRect : NULL; } // 在 1.92.0 版本中已废弃
    inline void CalcCustomRectUV(const ImFontAtlasRect* r, ImVec2* out_uv_min, ImVec2* out_uv_max) const { *out_uv_min = r->uv0; *out_uv_max = r->uv1; } // 在 1.92.0 版本中已废弃
    IMGUI_API ImFontAtlasRectId AddCustomRectFontGlyph(ImFont* font, ImWchar codepoint, int w, int h, float advance_x, const ImVec2& offset = ImVec2(0, 0)); // 在 1.92.0 版本中已废弃：请在 ImFontConfig 中使用自定义 ImFontLoader
    IMGUI_API ImFontAtlasRectId AddCustomRectFontGlyphForSize(ImFont* font, float font_size, ImWchar codepoint, int w, int h, float advance_x, const ImVec2& offset = ImVec2(0, 0)); // 在 1.92.0 版本中新增并废弃
#endif
    //unsigned int FontBuilderFlags; // 在 1.92.0 版本中已废弃：已重命名为 FontLoaderFlags。
    //int TexDesiredWidth; // 在 1.92.0 版本中已废弃：在调用 Build() 之前强制设定纹理宽度。必须是 2 的幂。如果字形较多且您的图形 API 存在纹理尺寸限制，您可能需要增加纹理宽度以减小高度。
    //typedef ImFontAtlasRect ImFontAtlasCustomRect; // 在 1.92.0 版本中已废弃
    //typedef ImFontAtlasCustomRect CustomRect; // 在 1.72+ 版本中已废弃
    //typedef ImFontGlyphRangesBuilder GlyphRangesBuilder; // 在 1.67+ 版本中已废弃
};


// 给定尺寸的字体运行时数据
// 重要提示：指向 ImFontBaked 的指针仅在当前帧有效。
struct ImFontBaked
{
    // [内部] 成员：热数据约 20/24 字节（用于 CalcTextSize）
    ImVector<float> IndexAdvanceX; // 12-16 // 输出 // 稀疏。以可直接索引的方式存储 Glyphs->AdvanceX（对仅需此信息的 CalcTextSize 函数缓存友好，该函数通常是大规模 UI 的性能瓶颈）。
    float FallbackAdvanceX; // 4 // 输出 // FindGlyph(FallbackChar)->AdvanceX
    float Size; // 4 // 输入 // 字符/行的高度，在加载时设置（加载后不再改变）
    float RasterizerDensity; // 4 // 输入 // 烘焙时的光栅化密度


    // [内部] 成员：热数据 ~28/36 字节（用于 RenderText 循环）
    ImVector<ImU16> IndexLookup; // 12-16 // 输出 // 稀疏矩阵。按 Unicode 码点索引字符。
    ImVector<ImFontGlyph> Glyphs; // 12-16 // 输出 // 所有字符。
    int FallbackGlyphIndex; // 4 // 输出 // FontFallbackChar 的索引


    // [内部] 成员：冷数据
    float Ascent, Descent; // 4+4 // 输出 // Ascent：从顶部到底部的距离，例如字符 'A' [0..FontSize]（未缩放）
    unsigned int MetricsTotalSurface : 26;// 3 // 输出 // 总表面积（像素），用于评估字体光栅化/纹理开销（非精确值，我们估算了字符间填充的开销）
    unsigned int WantDestroy : 1; // 0 // // 已排队等待销毁
    unsigned int LoadNoFallback : 1; // 0 // // 在低级调用中禁用加载备用方案（fallback）。
    unsigned int LoadNoRenderOnLayout : 1;// 0 // // 启用两步模式，使 CalcTextSize() 调用仅加载 AdvanceX 而不渲染/打包字形。仅当你确定该字形不太可能被实际渲染时才有优势，否则会更慢，因为我们会在第一次 CalcTextSize 时进行一次查询，在第一次 Draw 时又进行一次查询。
    int LastUsedFrame; // 4 // // 记录该项最后一次被绑定的帧
    ImGuiID BakedId; // 4 // // 此烘焙存储的唯一 ID
    ImFont* OwnerFont; // 4-8 // in // 父级字体
    void* FontLoaderDatas; // 4-8 // // 字体加载器不透明存储（每个烘焙字体 * 源）：由 imgui 分配的单个连续缓冲区，传递给加载器。


    // 函数
    IMGUI_API ImFontBaked();
    IMGUI_API void ClearOutputData();
    IMGUI_API ImFontGlyph* FindGlyph(ImWchar c); // 如果请求的字形不存在，则返回 U+FFFD 字形。
    IMGUI_API ImFontGlyph* FindGlyphNoFallback(ImWchar c); // 如果字形不存在，则返回 NULL。
    IMGUI_API float GetCharAdvance(ImWchar c);
    IMGUI_API bool IsGlyphLoaded(ImWchar c);
};


// 字体标志
//（在未来的版本中，随着我们重新设计字体加载 API，这部分将变得更加重要并提供更完善的文档。目前请将其视为内部/高级用途）
enum ImFontFlags_
{
    ImFontFlags_None = 0,
    ImFontFlags_NoLoadError = 1 << 1, // 当调用 AddFontXXX() 且文件/数据缺失时，禁用抛出错误或断言。调用代码应自行检查 AddFontXXX() 的返回值。
    ImFontFlags_NoLoadGlyphs = 1 << 2, // [内部] 禁用加载新字形。
    ImFontFlags_LockBakedSizes = 1 << 3, // [内部] 禁用加载新的烘焙尺寸，禁用对当前尺寸的垃圾回收。例如，当你想要将字体锁定为单一尺寸时使用。重要提示：如果你使用此项来预加载特定尺寸，请考虑 Retina 显示屏上可能使用多种字体密度的可能性。
};


// 字体运行时数据与渲染
// - 如果你没有手动加载字体，ImFontAtlas 会自动为你加载一个默认的嵌入字体。
// - 自 1.92.0 版本起，字体可以以任何尺寸进行渲染！因此，字体不再具有单一的特定尺寸。
// - 使用 'font->GetFontBaked(size)' 来获取对应给定尺寸的 ImFontBaked*。
// - 如果你使用了 g.Font + g.FontSize（这在 ImGui 层很常见），你可以使用 g.FontBaked 作为快捷方式，因为 g.FontBaked == g.Font->GetFontBaked(g.FontSize)。
struct ImFont
{
    // [内部] 成员：热数据 ~12-20 字节
    ImFontBaked* LastBaked; // 4-8 // 缓存最后绑定的烘焙数据。切勿直接使用。请使用 GetFontBaked()。
    ImFontAtlas* OwnerAtlas; // 4-8 // 我们被加载到的所属图集。
    ImFontFlags Flags; // 4 // 字体标志。
    float CurrentRasterizerDensity; // 当前光栅化密度。这是字体的一个可变状态。


    // [内部] 成员：冷数据 ~24-52 字节
    // 从概念上讲，Sources[] 是用于合并创建此字体的字体源列表。
    ImGuiID FontId; // 字体的唯一标识符
    float LegacySize; // 4 // 输入 // 传递给 AddFont() 的字体大小。用于调用 PushFont() 并期望使用该大小的旧代码。（使用 ImGui::GetFontBaked() 获取当前绑定大小下烘焙的字体）。
    ImVector<ImFontConfig*> Sources; // 16 // 输入 // 源列表。指向 OwnerAtlas->Sources[] 内部的指针
    ImWchar EllipsisChar; // 2-4 // 输出 // 用于渲染省略号（'...'）的字符。
    ImWchar FallbackChar; // 2-4 // 输出 // 未找到字形时使用的字符（U+FFFD, '?'）
    ImU8 Used8kPagesMap[(IM_UNICODE_CODEPOINT_MAX + 1) / 8192 / 8]; // 如果 ImWchar=ImWchar16 则为 1 字节，如果 ImWchar==ImWchar32 则为 16 字节。为每个包含至少一个活动字形的 4K 码位块存储 1 位。这主要用于方便遍历所有已使用的码位。
    bool EllipsisAutoBake; // 1 // // 标记何时需要生成 "..." 字形。
    ImGuiStorage RemapPairs; // 16 // // 使用 AddRemapChar() 时的重映射对，否则为空。
#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    float Scale; // 4 // 输入 // 旧版基础字体缩放（~1.0f），会与通过 SetWindowFontScale() 调整的每个窗口字体缩放相乘
#endif


    // 方法
    IMGUI_API ImFont();
    IMGUI_API ~ImFont();
    IMGUI_API bool IsGlyphInFont(ImWchar c);
    bool IsLoaded() const { return OwnerAtlas != NULL; }
    const char* GetDebugName() const { return Sources.Size ? Sources[0]->Name : "<unknown>"; } // 填充 ImFontConfig::Name。


    // [内部使用] 请勿使用！
    // 'max_width' 在达到一定宽度后停止渲染（可以转换为 2D 尺寸）。使用 FLT_MAX 禁用。
    // 'wrap_width' 启用跨多行的自动换行，以适应给定宽度。使用 0.0f 禁用。
    IMGUI_API ImFontBaked* GetFontBaked(float font_size, float density = -1.0f); // 获取或创建给定尺寸的烘焙数据
    IMGUI_API ImVec2 CalcTextSizeA(float size, float max_width, float wrap_width, const char* text_begin, const char* text_end = NULL, const char** out_remaining = NULL);
    IMGUI_API const char* CalcWordWrapPosition(float size, const char* text, const char* text_end, float wrap_width);
    IMGUI_API void RenderChar(ImDrawList* draw_list, float size, const ImVec2& pos, ImU32 col, ImWchar c, const ImVec4* cpu_fine_clip = NULL);
    IMGUI_API void RenderText(ImDrawList* draw_list, float size, const ImVec2& pos, ImU32 col, const ImVec4& clip_rect, const char* text_begin, const char* text_end, float wrap_width = 0.0f, ImDrawTextFlags flags = 0);
#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    inline const char* CalcWordWrapPositionA(float scale, const char* text, const char* text_end, float wrap_width) { return CalcWordWrapPosition(LegacySize * scale, text, text_end, wrap_width); }
#endif


    // [内部使用] 请勿使用！
    IMGUI_API void ClearOutputData();
    IMGUI_API void AddRemapChar(ImWchar from_codepoint, ImWchar to_codepoint); // 使 'from_codepoint' 字符指向 'to_codepoint' 字形。
    IMGUI_API bool IsGlyphRangeUnused(unsigned int c_begin, unsigned int c_last);
};


// 提供此项是为了保持一致性（但我们实际上并未使用它）
inline ImTextureID ImTextureRef::GetTexID() const
{
    IM_ASSERT(!(_TexData != NULL && _TexID != ImTextureID_Invalid));
    return _TexData ? _TexData->TexID : _TexID;
}


// 使用间接引用以避免在调用 SetTexID() 后修改 ImDrawCmd（但这也可以是另一种替代方案）
inline ImTextureID ImDrawCmd::GetTexID() const
{
    // 如果你遇到此断言：一个支持 ImGuiBackendFlags_RendererHasTextures (1.92) 的渲染器后端
    // 必须遍历并处理存储在 ImDrawData::Textures[] 中的 ImTextureData 请求。
    ImTextureID tex_id = TexRef._TexData ? TexRef._TexData->TexID : TexRef._TexID; // 等同于上方的 TexRef.GetTexID()。
    if (TexRef._TexData != NULL)
        IM_ASSERT(tex_id != ImTextureID_Invalid && "ImDrawCmd 引用了尚未上传至图形系统的 ImTextureData。后端在处理 ImTextureStatus_WantCreate 请求后必须调用 ImTextureData::SetTexID()！");
    return tex_id;
}


//-----------------------------------------------------------------------------
// [SECTION] 视口 (Viewports)
//-----------------------------------------------------------------------------


// 存储在 ImGuiViewport::Flags 中的标志，用于向平台后端提供指示。
enum ImGuiViewportFlags_
{
    ImGuiViewportFlags_None = 0,
    ImGuiViewportFlags_IsPlatformWindow = 1 << 0, // 代表一个平台窗口
    ImGuiViewportFlags_IsPlatformMonitor = 1 << 1, // 代表一个平台显示器（暂未使用）
    ImGuiViewportFlags_OwnedByApp = 1 << 2, // 平台窗口：由应用程序（而非 Dear ImGui 后端）创建/管理
};


// - 目前代表由应用程序创建的、用于承载 Dear ImGui 窗口的平台窗口。
// - 在启用了多视口的“docking”分支中，我们将这一概念扩展为拥有多个活动视口。
// - 未来我们将进一步扩展这一概念，使其也能代表平台显示器（Platform Monitor），并支持“无主平台窗口”的操作模式。
// - 关于主区域 (Main Area) 与工作区域 (Work Area)：
// - 主区域 = 整个视口 (viewport)。
// - 工作区域 = 整个视口减去主菜单栏（针对平台窗口）或任务栏（针对平台显示器）所占用的部分。
// - 窗口通常会尝试保持在其宿主视口的工作区域内。
struct ImGuiViewport
{
    ImGuiID ID; // 视口的唯一标识符
    ImGuiViewportFlags Flags; // 详见 ImGuiViewportFlags_
    ImVec2 Pos; // 主区域：视口的位置（Dear ImGui 坐标与操作系统桌面/原生坐标一致）
    ImVec2 Size; // 主区域：视口的大小。
    ImVec2 FramebufferScale; // 视口针对 Retina 显示屏的密度（在 Windows 上始终为 1,1，在 macOS/iOS 上可能为 2,2 等）。这会影响字体光栅化密度。
    ImVec2 WorkPos; // 工作区域：视口位置减去任务栏、菜单栏、状态栏后的位置（>= Pos）。
    ImVec2 WorkSize; // 工作区域：视口大小减去任务栏、菜单栏、状态栏后的大小（<= Size）。


    // 平台/后端相关数据
    void* PlatformHandle; // 用于持有高级别平台窗口句柄的 void* 指针（例如 HWND, GLFWWindow*, SDL_Window*）
    void* PlatformHandleRaw; // 用于持有低级别平台原生窗口句柄的 void* 指针（在 Win32 下通常为 HWND，其他平台通常不使用）


    ImGuiViewport() { memset(this, 0, sizeof(*this)); }


    // 辅助函数
    ImVec2 GetCenter() const { return ImVec2(Pos.x + Size.x * 0.5f, Pos.y + Size.y * 0.5f); }
    ImVec2 GetWorkCenter() const { return ImVec2(WorkPos.x + WorkSize.x * 0.5f, WorkPos.y + WorkSize.y * 0.5f); }
};


//-----------------------------------------------------------------------------
// [SECTION] 平台相关接口
//-----------------------------------------------------------------------------


// 通过 ImGui::GetPlatformIO() 访问
struct ImGuiPlatformIO
{
    IMGUI_API ImGuiPlatformIO();


    //------------------------------------------------------------------
    // 输入 - 与操作系统和平台后端交互（最常用的部分）
    //------------------------------------------------------------------


    // 可选：访问操作系统剪贴板
    //（在 Windows 上默认使用原生 Win32 剪贴板，否则使用私有剪贴板。在其他架构上可重写以访问操作系统剪贴板）
    const char* (*Platform_GetClipboardTextFn)(ImGuiContext* ctx); // 失败时应返回 NULL（例如剪贴板数据不是文本）。
    void (*Platform_SetClipboardTextFn)(ImGuiContext* ctx, const char* text);
    void* Platform_ClipboardUserData;


    // 可选：在操作系统外壳（OS Shell）中打开链接/文件夹/文件
    // （在 Windows 上默认使用 ShellExecuteW()，在 Linux/Mac 上默认使用 system()。失败时应返回 false，但某些平台可能始终返回 true）
    bool (*Platform_OpenInShellFn)(ImGuiContext* ctx, const char* path);
    void* Platform_OpenInShellUserData;


    // 可选：通知操作系统的输入法生成器（IME）光标在屏幕上的位置，以便定位文本输入框（例如在 Windows 上使用日文/中文输入法时）
    //（在 Windows 上默认使用原生的 imm32 API）
    void (*Platform_SetImeDataFn)(ImGuiContext* ctx, ImGuiViewport* viewport, ImGuiPlatformImeData* data);
    void* Platform_ImeUserData;
    //void (*SetPlatformImeDataFn)(ImGuiViewport* viewport, ImGuiPlatformImeData* data); // [在 1.91.1 版本中重命名为 platform_io.PlatformSetImeDataFn]


    // 可选：平台区域设置（Locale）
    // [实验性] 配置小数点，例如 '.' 或 ','，对某些语言（如德语）很有用，通常从 *localeconv()->decimal_point 获取
    ImWchar Platform_LocaleDecimalPoint; // '.'


    //------------------------------------------------------------------
    // 输入 - 与渲染器后端（Renderer Backend）的接口
    //------------------------------------------------------------------


    // 可选：渲染器支持的最大纹理尺寸（用于调整纹理大小）。如果未知则为 0。
    int Renderer_TextureMaxWidth;
    int Renderer_TextureMaxHeight;


    // 由某些后端在调用 ImGui_ImplXXXX_RenderDrawData() 期间写入，指向后端特定的 ImGui_ImplXXXX_RenderState* 结构。
    void* Renderer_RenderState;


    //------------------------------------------------------------------
    // 输出
    //------------------------------------------------------------------


    // 纹理列表（该列表通过调用 ImGui::EndFrame 或 ImGui::Render 进行更新）
    // 每个后端的 ImGui_ImplXXXX_RenderDrawData() 函数通常通过指向此处的 ImDrawData::Textures 来访问它。该数组在此处可用，主要是因为后端需要在关闭时销毁纹理。
    ImVector<ImTextureData*> Textures; // Dear ImGui 使用的纹理列表（通常为 1 个）+ 外部纹理列表的内容会自动追加到此处。


    //------------------------------------------------------------------
    // 函数
    //------------------------------------------------------------------


    IMGUI_API void ClearPlatformHandlers(); // 清除所有 Platform_XXX 字段。通常在平台后端关闭时调用。
    IMGUI_API void ClearRendererHandlers(); // 清除所有 Renderer_XXX 字段。通常在渲染器后端关闭时调用。
};


// （可选）通过 platform_io.Platform_SetImeDataFn() 函数支持 IME（输入法编辑器）。处理程序在 EndFrame() 期间被调用。
struct ImGuiPlatformImeData
{
    bool WantVisible; // 控件请求显示输入法（IME）。
    bool WantTextInput; // 控件请求文本输入，但不一定需要显示输入法。此值会自动设置为 io.WantTextInput 的即将生效值。
    ImVec2 InputPos; // 输入光标位置（用于输入法）。
    float InputLineHeight; // 行高（用于输入法）。
    ImGuiID ViewportId; // 平台窗口/视口的 ID。


    ImGuiPlatformImeData() { memset(this, 0, sizeof(*this)); }
};


//-----------------------------------------------------------------------------
// [SECTION] 已废弃的函数和类型
//（将被移除！详情请参阅 imgui.cpp 中的“API 破坏性变更”章节）
// 请保持您的 dear imgui 版本为最新！偶尔在 imconfig.h 中设置 '#define IMGUI_DISABLE_OBSOLETE_FUNCTIONS' 以保持领先。
//-----------------------------------------------------------------------------


#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
namespace ImGui
{
    // 已在 1.92.0 版本中废弃（自 2025 年 6 月起）
    inline void PushFont(ImFont* font) { PushFont(font, font ? font->LegacySize : 0.0f); }
    IMGUI_API void SetWindowFontScale(float scale); // 设置当前窗口的字体缩放系数。推荐使用 PushFont(NULL, style.FontSizeBase * factor) 或使用 style.FontScaleMain 来缩放所有窗口。
    // 已于 1.91.9 版本弃用（2025年2月）
    IMGUI_API void Image(ImTextureRef tex_ref, const ImVec2& image_size, const ImVec2& uv0, const ImVec2& uv1, const ImVec4& tint_col, const ImVec4& border_col); // <-- 'border_col' 已被移除，取而代之的是 ImGuiCol_ImageBorder。如果您使用了 'tint_col'，请改用 ImageWithBg()。
    // 已在 1.91.0 版本中弃用（自 2024 年 7 月起）
    inline void PushButtonRepeat(bool repeat) { PushItemFlag(ImGuiItemFlags_ButtonRepeat, repeat); }
    inline void PopButtonRepeat() { PopItemFlag(); }
    inline void PushTabStop(bool tab_stop) { PushItemFlag(ImGuiItemFlags_NoTabStop, !tab_stop); }
    inline void PopTabStop() { PopItemFlag(); }
    IMGUI_API ImVec2 GetContentRegionMax(); // 内容区域最大边界（例如包含滚动条的窗口边界，或当前列边界）。你永远不应该需要这个。请始终使用 GetCursorScreenPos() 和 GetContentRegionAvail()！
    IMGUI_API ImVec2 GetWindowContentRegionMin(); // 窗口内容区域的最小边界（大致为 (0,0)-Scroll），采用窗口局部坐标。你永远不应该需要这个。请始终使用 GetCursorScreenPos() 和 GetContentRegionAvail()！
    IMGUI_API ImVec2 GetWindowContentRegionMax(); // 窗口内容区域的最大边界（大致为 (0,0)+Size-Scroll），使用窗口局部坐标。你永远不应该需要这个函数。请始终使用 GetCursorScreenPos() 和 GetContentRegionAvail()！
    // 已在 1.90.0 版本中废弃（2023 年 9 月）
    IMGUI_API bool Combo(const char* label, int* current_item, bool (*old_callback)(void* user_data, int idx, const char** out_text), void* user_data, int items_count, int popup_max_height_in_items = -1);
    IMGUI_API bool ListBox(const char* label, int* current_item, bool (*old_callback)(void* user_data, int idx, const char** out_text), void* user_data, int items_count, int height_in_items = -1);


    // 一些旧的废弃名称及其替代方案（已注释掉，以免在 IDE 中报错）
    // 已在 1.90.0 版本中废弃（2023 年 9 月起）
    //inline bool BeginChild(const char* str_id, const ImVec2& size_arg, bool borders, ImGuiWindowFlags window_flags) { return BeginChild(str_id, size_arg, borders ? ImGuiChildFlags_Borders : ImGuiChildFlags_None, window_flags); } // 不必要，因为 true == ImGuiChildFlags_Borders
    //inline bool BeginChild(ImGuiID id, const ImVec2& size_arg, bool borders, ImGuiWindowFlags window_flags) { return BeginChild(id, size_arg, borders ? ImGuiChildFlags_Borders : ImGuiChildFlags_None, window_flags); } // 不必要，因为 true == ImGuiChildFlags_Borders
    //inline bool BeginChildFrame(ImGuiID id, const ImVec2& size, ImGuiWindowFlags flags = 0) { return BeginChild(id, size, ImGuiChildFlags_FrameStyle, flags); }
    //inline void EndChildFrame() { EndChild(); }
    //inline void ShowStackToolWindow(bool* p_open = NULL) { ShowIDStackToolWindow(p_open); }
    // 已于 1.89.7 版本弃用（2023年6月）
    //IMGUI_API void SetItemAllowOverlap(); // 请在控件_之前_使用 SetNextItemAllowOverlap()。
    //-- 在 1.89.4 版本中已废弃（2023年3月）
    //static inline void PushAllowKeyboardFocus(bool tab_stop) { PushItemFlag(ImGuiItemFlags_NoTabStop, !tab_stop); }
    //static inline void PopAllowKeyboardFocus() { PopItemFlag(); }
    //-- 已于 1.89 版本弃用（2022年8月）
    //IMGUI_API bool ImageButton(ImTextureID user_texture_id, const ImVec2& size, const ImVec2& uv0 = ImVec2(0, 0), const ImVec2& uv1 = ImVec2(1, 1), int frame_padding = -1, const ImVec4& bg_col = ImVec4(0, 0, 0, 0), const ImVec4& tint_col = ImVec4(1, 1, 1, 1)); // --> 请使用新的 ImageButton() 函数签名（需显式指定项目 ID 和常规 FramePadding）。如果你想获取此版本的副本，请参考 1.91 版本的代码。
    //-- 已于 1.88 版本弃用（2022年5月）
    //static inline void CaptureKeyboardFromApp(bool want_capture_keyboard = true) { SetNextFrameWantCaptureKeyboard(want_capture_keyboard); } // 已重命名，因为原名称具有误导性，且移除了默认值。
    //static inline void CaptureMouseFromApp(bool want_capture_mouse = true) { SetNextFrameWantCaptureMouse(want_capture_mouse); } // 已重命名，因为原名称具有误导性 + 移除了默认值。
    //-- 在 1.87 版本中废弃（自 2022 年 2 月起，2024 年 4 月正式废弃）
    //IMGUI_API ImGuiKey GetKeyIndex(ImGuiKey key); { IM_ASSERT(key >= ImGuiKey_NamedKey_BEGIN && key < ImGuiKey_NamedKey_END); const ImGuiKeyData* key_data = GetKeyData(key); return (ImGuiKey)(key_data - g.IO.KeysData); } // 将 ImGuiKey_* 值映射为旧版原生键索引。等同于 io.KeyMap[key]。当使用 1.87+ 版本且通过 io.AddKeyEvent() 实现的后端时，对任何 ImGuiKey_XXXX 值调用 GetKeyIndex() 都将返回相同的值！
    //static inline ImGuiKey GetKeyIndex(ImGuiKey key) { IM_ASSERT(key >= ImGuiKey_NamedKey_BEGIN && key < ImGuiKey_NamedKey_END); return key; }
    //-- 已于 1.86 版本弃用（2021年11月）
    //IMGUI_API void CalcListClipping(int items_count, float items_height, int* out_items_display_start, int* out_items_display_end); // 代码已移除，最后版本见 1.90。用于计算等高大列表的可见项范围。建议改用 ImGuiListClipper。
    //-- 已于 1.85 版本弃用（2021年8月）
    //static inline float GetWindowContentRegionWidth() { return GetWindowContentRegionMax().x - GetWindowContentRegionMin().x; }
    //-- 已于 1.81 版本弃用（2021年2月起）
    //static inline bool ListBoxHeader(const char* label, const ImVec2& size = ImVec2(0, 0)) { return BeginListBox(label, size); }
    //static inline bool ListBoxHeader(const char* label, int items_count, int height_in_items = -1) { float height = GetTextLineHeightWithSpacing() * ((height_in_items < 0 ? ImMin(items_count, 7) : height_in_items) + 0.25f) + GetStyle().FramePadding.y * 2.0f; return BeginListBox(label, ImVec2(0.0f, height)); } // 用于根据 items_count 和 height_in_items 计算尺寸的辅助函数
    //static inline void ListBoxFooter() { EndListBox(); }
    //-- 已于 1.79 版本弃用（2020年8月）
    //static inline void OpenPopupContextItem(const char* str_id = NULL, ImGuiMouseButton mb = 1) { OpenPopupOnItemClick(str_id, mb); } // 移除了布尔返回值。请在 BeginPopup() 中改用 IsWindowAppearing()。在 1.77 版本中更名，在 1.79 版本中又改回原名。抱歉！
    //-- 已于 1.78 版本弃用（2020 年 6 月）：旧的拖动/滑块函数，这些函数使用 'float power > 1.0f' 参数而非 ImGuiSliderFlags_Logarithmic。详情请参阅 github.com/ocornut/imgui/issues/3361。
    //IMGUI_API bool DragScalar(const char* label, ImGuiDataType data_type, void* p_data, float v_speed, const void* p_min, const void* p_max, const char* format, float power = 1.0f) // 已于 1.78 版本弃用（2020 年 6 月）
    //IMGUI_API bool DragScalarN(const char* label, ImGuiDataType data_type, void* p_data, int components, float v_speed, const void* p_min, const void* p_max, const char* format, float power = 1.0f); // 已于 1.78 版本弃用（2020 年 6 月）
    //IMGUI_API bool SliderScalar(const char* label, ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max, const char* format, float power = 1.0f); // 已于 1.78 版本弃用（2020 年 6 月）
    //IMGUI_API bool SliderScalarN(const char* label, ImGuiDataType data_type, void* p_data, int components, const void* p_min, const void* p_max, const char* format, float power = 1.0f); // 已于 1.78 版本弃用（2020 年 6 月）
    //static inline bool DragFloat(const char* label, float* v, float v_speed, float v_min, float v_max, const char* format, float power = 1.0f) { return DragScalar(label, ImGuiDataType_Float, v, v_speed, &v_min, &v_max, format, power); } // 已于 1.78 版本弃用（2020 年 6 月）
    //static inline bool DragFloat2(const char* label, float v[2], float v_speed, float v_min, float v_max, const char* format, float power = 1.0f) { return DragScalarN(label, ImGuiDataType_Float, v, 2, v_speed, &v_min, &v_max, format, power); } // 已在 1.78 版本中弃用（2020 年 6 月）
    //static inline bool DragFloat3(const char* label, float v[3], float v_speed, float v_min, float v_max, const char* format, float power = 1.0f) { return DragScalarN(label, ImGuiDataType_Float, v, 3, v_speed, &v_min, &v_max, format, power); } // 已在 1.78 版本中弃用（2020 年 6 月）
    //static inline bool DragFloat4(const char* label, float v[4], float v_speed, float v_min, float v_max, const char* format, float power = 1.0f) { return DragScalarN(label, ImGuiDataType_Float, v, 4, v_speed, &v_min, &v_max, format, power); } // 已在 1.78 版本中弃用（2020 年 6 月）
    //static inline bool SliderFloat(const char* label, float* v, float v_min, float v_max, const char* format, float power = 1.0f) { return SliderScalar(label, ImGuiDataType_Float, v, &v_min, &v_max, format, power); } // 已在 1.78 版本中弃用（2020 年 6 月）
    //static inline bool SliderFloat2(const char* label, float v[2], float v_min, float v_max, const char* format, float power = 1.0f) { return SliderScalarN(label, ImGuiDataType_Float, v, 2, &v_min, &v_max, format, power); } // 已在 1.78 版本中弃用（2020 年 6 月）
    //static inline bool SliderFloat3(const char* label, float v[3], float v_min, float v_max, const char* format, float power = 1.0f) { return SliderScalarN(label, ImGuiDataType_Float, v, 3, &v_min, &v_max, format, power); } // 已在 1.78 版本中弃用（2020 年 6 月）
    //static inline bool SliderFloat4(const char* label, float v[4], float v_min, float v_max, const char* format, float power = 1.0f) { return SliderScalarN(label, ImGuiDataType_Float, v, 4, &v_min, &v_max, format, power); } // 已在 1.78 版本中弃用（2020 年 6 月）
    //-- 已在 1.77 及更早版本中弃用
    //static inline bool BeginPopupContextWindow(const char* str_id, ImGuiMouseButton mb, bool over_items) { return BeginPopupContextWindow(str_id, mb | (over_items ? 0 : ImGuiPopupFlags_NoOpenOverItems)); } // 已于 1.77 版本弃用（2020 年 6 月）
    //static inline void TreeAdvanceToLabelPos() { SetCursorPosX(GetCursorPosX() + GetTreeNodeToLabelSpacing()); } // 已于 1.72 版本弃用（2019 年 7 月）
    //static inline void SetNextTreeNodeOpen(bool open, ImGuiCond cond = 0) { SetNextItemOpen(open, cond); } // 已于 1.71 版本弃用（2019 年 6 月）
    //static inline float GetContentRegionAvailWidth() { return GetContentRegionAvail().x; } // 已于 1.70 版本弃用（2019 年 5 月）
    //static inline ImDrawList* GetOverlayDrawList() { return GetForegroundDrawList(); } // 已在 1.69 版本中弃用（2019 年 3 月）
    //static inline void SetScrollHere(float ratio = 0.5f) { SetScrollHereY(ratio); } // 已在 1.66 版本中弃用（2018 年 11 月）
    //static inline bool IsItemDeactivatedAfterChange() { return IsItemDeactivatedAfterEdit(); } // 已于 1.63 版本弃用（2018 年 8 月）
    //-- 已于 1.60 及更早版本弃用
    //static inline bool IsAnyWindowFocused() { return IsWindowFocused(ImGuiFocusedFlags_AnyWindow); } // 已于 1.60 版本弃用（2018 年 4 月）
    //static inline bool IsAnyWindowHovered() { return IsWindowHovered(ImGuiHoveredFlags_AnyWindow); } // 已于 1.60 版本弃用（2017 年 12 月至 2018 年 4 月期间）
    //static inline void ShowTestWindow() { return ShowDemoWindow(); } // 已在 1.53 版本中弃用（2017 年 10 月至 12 月期间）
    //static inline bool IsRootWindowFocused() { return IsWindowFocused(ImGuiFocusedFlags_RootWindow); } // 已在 1.53 版本中弃用（2017 年 10 月至 12 月期间）
    //static inline bool IsRootWindowOrAnyChildFocused() { return IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows); } // 已在 1.53 版本中弃用（2017 年 10 月至 12 月期间）
    //static inline void SetNextWindowContentWidth(float w) { SetNextWindowContentSize(ImVec2(w, 0.0f)); } // 已在 1.53 版本中弃用（2017 年 10 月至 12 月期间）
    //static inline float GetItemsLineHeightWithSpacing() { return GetFrameHeightWithSpacing(); } // 在 1.53 版本中已废弃（2017 年 10 月至 12 月期间）
    //IMGUI_API bool Begin(char* name, bool* p_open, ImVec2 size_first_use, float bg_alpha = -1.0f, ImGuiWindowFlags flags=0); // 在 1.52 版本中已废弃（2017 年 8 月至 10 月期间）：等同于使用 SetNextWindowSize(size, ImGuiCond_FirstUseEver) 和 SetNextWindowBgAlpha()。
    //static inline bool IsRootWindowOrAnyChildHovered() { return IsWindowHovered(ImGuiHoveredFlags_RootAndChildWindows); } // 在 1.52 版本中已废弃（2017 年 8 月至 10 月期间）
    //static inline void AlignFirstTextHeightToWidgets() { AlignTextToFramePadding(); } // 在 1.52 版本中已废弃（2017 年 8 月至 10 月期间）
    //static inline void SetNextWindowPosCenter(ImGuiCond c=0) { SetNextWindowPos(GetMainViewport()->GetCenter(), c, ImVec2(0.5f,0.5f)); } // 已在 1.52 版本中废弃（2017 年 8 月至 2017 年 10 月期间）
    //static inline bool IsItemHoveredRect() { return IsItemHovered(ImGuiHoveredFlags_RectOnly); } // 已在 1.51 版本中废弃（2017 年 6 月至 2017 年 8 月期间）
    //static inline bool IsPosHoveringAnyWindow(const ImVec2&) { IM_ASSERT(0); return false; } // 已在 1.51 版本中废弃（2017 年 6 月至 2017 年 8 月期间）：该函数具有误导性且部分功能损坏。你可能应该改用 io.WantCaptureMouse 标志。
    //static inline bool IsMouseHoveringAnyWindow() { return IsWindowHovered(ImGuiHoveredFlags_AnyWindow); } // 已在 1.51 版本中废弃（2017 年 6 月至 2017 年 8 月期间）
    //static inline bool IsMouseHoveringWindow() { return IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByPopup | ImGuiHoveredFlags_AllowWhenBlockedByActiveItem); } // 在 1.51 版本中已废弃（2017 年 6 月至 2017 年 8 月期间）
    //-- 在 1.50 及更早版本中已废弃
    //static inline bool CollapsingHeader(char* label, const char* str_id, bool framed = true, bool default_open = false) { return CollapsingHeader(label, (default_open ? (1 << 5) : 0)); } // 在 1.49 版本中已废弃
    //static inline ImFont*GetWindowFont() { return GetFont(); } // 在 1.48 版本中已废弃
    //static inline float GetWindowFontSize() { return GetFontSize(); } // 在 1.48 版本中已废弃
    //static inline void SetScrollPosHere() { SetScrollHere(); } // 在 1.42 版本中已废弃
}


//-- 在 1.92.0 版本中已废弃：ImFontAtlasCustomRect 更名为 ImTextureRect
// - ImFontAtlasCustomRect::X,Y --> ImTextureRect::x,y
// - ImFontAtlasCustomRect::Width,Height --> ImTextureRect::w,h
// - ImFontAtlasCustomRect::GlyphColored --> 如果你需要写入此项，可以在调用 AddCustomRectFontGlyph() 后改为写入 'font->Glyphs.back()->Colored'
// 我们可以将 ImTextureRect 设为联合体以使用旧名称，但 1) 这会引起混淆 2) 修复很简单 3) ImFontAtlasCustomRect 一直是一个相当冷门的 API。
typedef ImFontAtlasRect ImFontAtlasCustomRect;
/*struct ImFontAtlasCustomRect
{
unsigned short X, Y; // 输出 // 在图集（Atlas）中的打包位置
unsigned short Width, Height; // 输入 // [内部] 矩形的目标尺寸
unsigned int GlyphID:31; // 输入 // [内部] 仅用于自定义字体字形 (ID < 0x110000)
unsigned int GlyphColored:1; // 输入 // [内部] 仅用于自定义字体字形：字形带有颜色，移除着色 (tinting)。
float GlyphAdvanceX; // 输入 // [内部] 仅用于自定义字体字形：字形 X 轴步进 (xadvance)
ImVec2 GlyphOffset; // 输入 // [内部] 仅用于自定义字体字形：字形显示偏移
ImFont* Font; // 输入 // [内部] 仅用于自定义字体字形：目标字体
ImFontAtlasCustomRect() { X = Y = 0xFFFF; Width = Height = 0; GlyphID = 0; GlyphColored = 0; GlyphAdvanceX = 0.0f; GlyphOffset = ImVec2(0, 0); Font = NULL; }
bool IsPacked() const { return X != 0xFFFF; }
};*/


//-- 在 1.82 版本中已废弃（自 2021 年 3 月起）：AddRect()、AddRectFilled()、AddImageRounded()、PathRect() 的标志位
//typedef ImDrawFlags ImDrawCornerFlags;
//enum ImDrawCornerFlags_
//{
// ImDrawCornerFlags_None = ImDrawFlags_RoundCornersNone, // 在 1.82 版本之前为 0，现在等于 ImDrawFlags_RoundCornersNone，其值不为 0 且不再是隐式的
// ImDrawCornerFlags_TopLeft = ImDrawFlags_RoundCornersTopLeft, // 在 1.82 版本之前为 0x01 (1 << 0)。顺序与 ImDrawFlags_NoRoundCorner* 标志匹配（我们在内部利用了这一点）。
// ImDrawCornerFlags_TopRight = ImDrawFlags_RoundCornersTopRight, // 在 1.82 版本之前为 == 0x02 (1 << 1)。
// ImDrawCornerFlags_BotLeft = ImDrawFlags_RoundCornersBottomLeft, // 在 1.82 版本之前为 == 0x04 (1 << 2)。
// ImDrawCornerFlags_BotRight = ImDrawFlags_RoundCornersBottomRight, // 在 1.82 版本之前为 == 0x08 (1 << 3)。
// ImDrawCornerFlags_All = ImDrawFlags_RoundCornersAll, // 在 1.82 版本之前为 == 0x0F
// ImDrawCornerFlags_Top = ImDrawCornerFlags_TopLeft | ImDrawCornerFlags_TopRight,
// ImDrawCornerFlags_Bot = ImDrawCornerFlags_BotLeft | ImDrawCornerFlags_BotRight,
// ImDrawCornerFlags_Left = ImDrawCornerFlags_TopLeft | ImDrawCornerFlags_BotLeft,
// ImDrawCornerFlags_Right = ImDrawCornerFlags_TopRight | ImDrawCornerFlags_BotRight,
//};


// 将 ImGuiKey_ModXXX 和 ImGuiModFlags_XXX 重命名并合并为 ImGuiMod_XXX（自 2022 年 9 月起）
// 在 1.88 版本中将 ImGuiKeyModFlags 重命名为 ImGuiModFlags（自 2022 年 4 月起）。破例在正式废弃计划前将其注释掉，以减少混淆，且因为它们最初本就不该被直接使用。
//typedef ImGuiKeyChord ImGuiModFlags; // == int。我们通常使用 ImGuiKeyChord 来表示“一个 ImGuiKey 与任意数量的 ImGuiMod_XXX 值进行按位或运算的结果”，因此你可以在其中存储修饰键。
//enum ImGuiModFlags_ { ImGuiModFlags_None = 0, ImGuiModFlags_Ctrl = ImGuiMod_Ctrl, ImGuiModFlags_Shift = ImGuiMod_Shift, ImGuiModFlags_Alt = ImGuiMod_Alt, ImGuiModFlags_Super = ImGuiMod_Super };
//typedef ImGuiKeyChord ImGuiKeyModFlags; // == int
//enum ImGuiKeyModFlags_ { ImGuiKeyModFlags_None = 0, ImGuiKeyModFlags_Ctrl = ImGuiMod_Ctrl, ImGuiKeyModFlags_Shift = ImGuiMod_Shift, ImGuiKeyModFlags_Alt = ImGuiMod_Alt, ImGuiKeyModFlags_Super = ImGuiMod_Super };


//#define IM_OFFSETOF(_TYPE,_MEMBER) offsetof(_TYPE, _MEMBER) // 在 1.90 版本中已废弃（现使用 C++11 标准版本）


#endif // #ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS


#define IM_ARRAYSIZE IM_COUNTOF // 在 1.92.6 版本中重命名：IM_ARRAYSIZE -> IM_COUNTOF


// 在 1.88 版本（2022 年 6 月）中，IMGUI_DISABLE_METRICS_WINDOW 已重命名为 IMGUI_DISABLE_DEBUG_TOOLS
#ifdef IMGUI_DISABLE_METRICS_WINDOW
#error IMGUI_DISABLE_METRICS_WINDOW 已重命名为 IMGUI_DISABLE_DEBUG_TOOLS，请使用新名称。
#endif


//-----------------------------------------------------------------------------


#if defined(__clang__)
#pragma clang diagnostic pop
#elif defined(__GNUC__)
#pragma GCC diagnostic pop
#endif


#ifdef _MSC_VER
#pragma warning (pop)
#endif


// 在 imgui.h 的末尾包含 imgui_user.h
// 对于某些用户来说，仅显式包含原版 imgui.h 并自动包含额外内容可能会很方便。
#ifdef IMGUI_INCLUDE_IMGUI_USER_H
#ifdef IMGUI_USER_H_FILENAME
#include IMGUI_USER_H_FILENAME
#else
#include "imgui_user.h"
#endif
#endif


#endif // #ifndef IMGUI_DISABLE
