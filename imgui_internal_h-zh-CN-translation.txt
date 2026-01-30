struct ImGuiContext
{
bool Initialized;
bool WithinFrameScope; // 由 NewFrame() 设置，由 EndFrame() 清除
bool WithinFrameScopeWithImplicitWindow; // 由 NewFrame() 设置，当隐式调试窗口被推入后由 EndFrame() 清除
bool TestEngineHookItems; // 将调用测试引擎钩子：ImGuiTestEngineHook_ItemAdd()、ImGuiTestEngineHook_ItemInfo()、ImGuiTestEngineHook_Log()
int FrameCount;
int FrameCountEnded;
int FrameCountRendered;
double Time;
char ContextName[16]; // 存储上下文名称（以便于调试多上下文设置）
ImGuiIO IO;
ImGuiPlatformIO PlatformIO;
ImGuiStyle Style;
ImVector<ImFontAtlas*> FontAtlases; // 上下文使用的字体图集列表（通常仅包含 g.IO.Fonts，即主字体图集）
ImFont* Font; // 当前绑定的字体。(== FontStack.back().Font)
ImFontBaked* FontBaked; // 当前绑定的字体及其当前绑定的尺寸。(== Font->GetFontBaked(FontSize))
float FontSize; // 当前绑定的字体尺寸 == 行高 (== FontSizeBase + 在 UpdateCurrentFontSize() 函数中应用的外部缩放)。
float FontSizeBase; // 缩放前的字体大小 == style.FontSizeBase == 指定时传递给 PushFont() 的值。
float FontBakedScale; // == FontBaked->Size / FontSize。相对于烘焙尺寸的缩放因子。现已很少使用，通常为 1.0f。
float FontRasterizerDensity; // 当前字体密度。供所有 GetFontBaked() 调用使用。
float CurrentDpiScale; // 当前窗口/视口的 DPI 缩放比例 == CurrentViewport->DpiScale
ImDrawListSharedData DrawListSharedData;
ImGuiID WithinEndChildID; // 在 EndChild() 中设置
void* TestEngine; // 测试引擎用户数据


// 输入
ImVector<ImGuiInputEvent> InputEventsQueue; // 将被逐个处理/写入 IO 结构的输入事件队列。
ImVector<ImGuiInputEvent> InputEventsTrail; // 在 NewFrame() 中处理过的历史输入事件。用于允许特定领域的应用程序访问例如鼠标/手写笔的轨迹。
ImGuiMouseSource InputEventsNextMouseSource;
ImU32 InputEventsNextEventId;


// Windows 状态
ImVector<ImGuiWindow*> Windows; // 窗口列表，按显示顺序排列（从后到前）
ImVector<ImGuiWindow*> WindowsFocusOrder; // 根窗口，按焦点顺序排序，从后到前。
ImVector<ImGuiWindow*> WindowsTempSortBuffer; // 在 EndFrame() 中使用的临时缓冲区，用于对窗口进行重新排序，以确保父窗口排在子窗口之前
ImVector<ImGuiWindowStackData> CurrentWindowStack;
ImGuiStorage WindowsById; // 将窗口的 ImGuiID 映射到 ImGuiWindow*
int WindowsActiveCount; // 每帧提交的唯一窗口数量
float WindowsBorderHoverPadding; // 可调整大小窗口周围的填充距离，在此范围内悬停即视为悬停在窗口上 == ImMax(style.TouchExtraPadding, style.WindowBorderHoverPadding)。这对多 DPI 环境不太友好。
ImGuiID DebugBreakInWindow; // 设置后将在 Begin() 调用时触发断点。
ImGuiWindow* CurrentWindow; // 当前正在绘制的窗口
ImGuiWindow* HoveredWindow; // 鼠标悬停的窗口。通常会接收鼠标输入。
ImGuiWindow* HoveredWindowUnderMovingWindow; // 忽略 MovingWindow 后的悬停窗口。仅在设置了 MovingWindow 时有效。
ImGuiWindow* HoveredWindowBeforeClear; // 鼠标悬停的窗口。即使设置了 _NoMouse 也会填充。目前对多上下文合成器（multi-context compositors）很有用。
ImGuiWindow* MovingWindow; // 追踪我们点击的窗口（为了保持焦点）。实际移动的窗口通常是 MovingWindow->RootWindow。
ImGuiWindow* WheelingWindow; // 追踪我们开始滚动鼠标滚轮时的窗口。在计时器到期或鼠标移动之前，通常会保持滚动同一个窗口，即使在滚动过程中鼠标最终悬停在了子窗口上。
ImVec2 WheelingWindowRefMousePos;
int WheelingWindowStartFrame; // 这可能会在 WheelingWindow != NULL 的前一帧被设置
int WheelingWindowScrolledFrame;
float WheelingWindowReleaseTimer;
ImVec2 WheelingWindowWheelRemainder;
ImVec2 WheelingAxisAvg;


// 物品/控件状态及跟踪信息
ImGuiID DebugDrawIdConflictsId; // 当我们检测到多个具有相同标识符的物品时设置
ImGuiID DebugHookIdInfoId; // 将从 GetID 函数中调用核心钩子：DebugHookIdInfo()，由 ID Stack Tool 使用 [紧邻 HoveredId/ActiveId 以避免引入额外的缓存行]
ImGuiID HoveredId; // 悬停的控件，在帧期间填充
ImGuiID HoveredIdPreviousFrame;
int HoveredIdPreviousFrameItemCount; // 统计使用与上一帧悬停 ID 相同 ID 的物品数量
float HoveredIdTimer; // 测量连续悬停时间
float HoveredIdNotActiveTimer; // 测量物品处于非激活状态时的连续悬停时间
bool HoveredIdAllowOverlap;
bool HoveredIdIsDisabled; // 至少有一个控件通过了矩形测试，但因禁用标志或弹窗抑制而被丢弃。即使 HoveredId == 0，此值也可能为 true。
bool ItemUnclipByLog; // 禁用 ItemAdd() 裁剪，本质上是 LogEnabled 的一个内存局部性友好副本
ImGuiID ActiveId; // 当前激活的控件
ImGuiID ActiveIdIsAlive; // 激活的控件在本帧已被处理（我们不能使用布尔值，因为 ActiveId 可能会在帧内发生变化）
float ActiveIdTimer;
bool ActiveIdIsJustActivated; // 在激活时设置，持续一帧
bool ActiveIdAllowOverlap; // 当前活跃控件允许另一个控件夺取活跃 ID（通常用于重叠控件，但并非总是如此）
bool ActiveIdNoClearOnFocusLoss; // 禁用当活跃 ID 窗口失去焦点时清除活跃 ID 的行为。
bool ActiveIdHasBeenPressedBefore; // 追踪活跃 ID 是否曾导致过点击（这是为了允许在“点击时触发”和“释放时触发”之间切换而无需点击两次）。由 range_select 分支使用。
bool ActiveIdHasBeenEditedBefore; // 与该控件关联的值在处于活跃状态期间是否被编辑过。
bool ActiveIdHasBeenEditedThisFrame;
bool ActiveIdFromShortcut;
ImS8 ActiveIdMouseButton;
ImGuiID ActiveIdDisabledId; // 当点击一个禁用的物品时，我们将 ActiveId 设置为 window->MoveId 以避免干扰控件代码。实际的物品 ID 存储在这里。
ImVec2 ActiveIdClickOffset; // 如果适用，存储相对于左上角的点击偏移量（目前仅由 ButtonBehavior 设置）
ImGuiInputSource ActiveIdSource; // 激活源：ImGuiInputSource_Mouse 或 ImGuiInputSource_Keyboard 或 ImGuiInputSource_Gamepad
ImGuiWindow* ActiveIdWindow;
ImGuiID ActiveIdPreviousFrame;
ImGuiDeactivatedItemData DeactivatedItemData;
ImGuiDataTypeStorage ActiveIdValueOnActivation; // 激活时初始值的备份。仅由特定控件设置：DragXXX 和 SliderXXX。
ImGuiID LastActiveId; // 存储上一个非零的 ActiveId，对动画很有用。
float LastActiveIdTimer; // 存储自激活开始以来最后一个非零的 ActiveId 计时器，对动画很有用。


// 按键/输入所有权 + 快捷键路由系统
// - 其核心理念是：我们不再直接“吞掉”给定的按键，而是将其链接到一个所有者（Owner）。
// - 随后，输入查询可以通过指定 ImGuiKeyOwner_Any (== 0)、ImGuiKeyOwner_NoOwner (== -1) 或自定义 ID 来读取输入。
// - 路由请求需针对给定的组合键（按键 + 修饰键）提前发起，并在 NewFrame() 中授予。
double LastKeyModsChangeTime; // 记录上一次按键修饰符发生变化的时间（在使用快捷键逻辑时影响重复延迟）
double LastKeyModsChangeFromNoneTime; // 记录上一次按键修饰符从无（0）变为有值的时间（在使用快捷键逻辑时影响重复延迟）
double LastKeyboardKeyPressTime; // 记录上一次键盘按键（忽略鼠标/手柄按键）被按下的时间
ImBitArrayForNamedKeys KeysMayBeCharInput; // 用于判断按键是否可能产生字符输入的查找表，参见 IsKeyChordPotentiallyCharInput()。sizeof() = 20 字节
ImGuiKeyOwnerData KeysOwnerData[ImGuiKey_NamedKey_COUNT];
ImGuiKeyRoutingTable KeysRoutingTable;
ImU32 ActiveIdUsingNavDirMask; // 当前激活的控件将读取这些导航移动请求（例如：可以激活一个按钮并从中移开）
bool ActiveIdUsingAllKeyboardKeys; // 当前激活的控件将读取所有键盘按键输入。（这是为了避免逐个获取 100 多个按键所有权的快捷方式，常用于拖拽操作）
ImGuiKeyChord DebugBreakInShortcutRouting; // 设置此项以在 SetShortcutRouting()/Shortcut() 调用时触发中断。
//ImU32 ActiveIdUsingNavInputMask; // [已废弃] 自 (IMGUI_VERSION_NUM >= 18804) 起：'g.ActiveIdUsingNavInputMask |= (1 << ImGuiNavInput_Cancel);' 变为 --> 'SetKeyOwner(ImGuiKey_Escape, g.ActiveId) 和/或 SetKeyOwner(ImGuiKey_NavGamepadCancel, g.ActiveId);'


// 下一个窗口/物品数据
ImGuiID CurrentFocusScopeId; // 当前添加项的值 == g.FocusScopeStack.back()。不要与 g.NavFocusScopeId 混淆。
ImGuiItemFlags CurrentItemFlags; // 当前添加项的值 == g.ItemFlagsStack.back()
ImGuiID DebugLocateId; // 用于 DebugLocateItemOnHover() 功能的存储：此变量由 ItemAdd() 读取，因此我们将其保留在热点/缓存位置
ImGuiNextItemData NextItemData; // 用于 SetNextItem** 函数的存储
ImGuiLastItemData LastItemData; // 用于最后提交物品的存储（由 ItemAdd 设置）
ImGuiNextWindowData NextWindowData; // 用于存储 SetNextWindow** 函数的数据
bool DebugShowGroupRects;
bool GcCompactAll; // 请求完整 GC


// 共享栈
ImGuiCol DebugFlashStyleColorIdx; // （保持靠近 ColorStack 以共享缓存行）
ImVector<ImGuiColorMod> ColorStack; // PushStyleColor()/PopStyleColor() 的栈 - 由 Begin() 继承
ImVector<ImGuiStyleMod> StyleVarStack; // PushStyleVar()/PopStyleVar() 的栈 - 由 Begin() 继承
ImVector<ImFontStackData> FontStack; // PushFont()/PopFont() 使用的栈 - 由 Begin() 继承
ImVector<ImGuiFocusScopeData> FocusScopeStack; // PushFocusScope()/PopFocusScope() 的栈 - 由 BeginChild() 继承，由 Begin() 压入
ImVector<ImGuiItemFlags> ItemFlagsStack; // PushItemFlag()/PopItemFlag() 使用的栈 - 由 Begin() 继承
ImVector<ImGuiGroupData> GroupStack; // BeginGroup()/EndGroup() 的栈 - 不由 Begin() 继承
ImVector<ImGuiPopupData> OpenPopupStack; // 哪些弹窗处于打开状态（持久性）
ImVector<ImGuiPopupData> BeginPopupStack; // 当前处于 BeginPopup() 的哪一层级（每帧重置）
ImVector<ImGuiTreeNodeStackData> TreeNodeStack; // TreeNode() 的堆栈


// 视口 (Viewports)
ImVector<ImGuiViewportP*> Viewports; // 激活的视口（在 'master' 分支中 Size==1）。每个视口持有各自的 ImDrawData 副本。


// 键盘/手柄导航
bool NavCursorVisible; // 导航焦点光标/矩形是否可见？我们在鼠标点击后将其隐藏，在导航移动后将其显示。
bool NavHighlightItemUnderNav; // 禁用鼠标悬停高亮。高亮导航焦点的物品，而不是鼠标悬停的物品。
//bool NavDisableHighlight; // 1.91.4 (2024/10/18) 之前 !g.NavCursorVisible 的旧名称。取值相反 (g.NavDisableHighlight == !g.NavCursorVisible)
//bool NavDisableMouseHover; // 1.91.1 (2024/10/18) 之前 g.NavHighlightItemUnderNav 的旧名称。当用户开始使用键盘/手柄时，我们会隐藏鼠标悬停高亮，直到再次触碰鼠标。
bool NavMousePosDirty; // 设置后，如果启用了 io.ConfigNavMoveSetMousePos（默认未启用），我们将更新鼠标位置
bool NavIdIsAlive; // 导航控件在本帧中可见 ~~ NavRectRel 有效
ImGuiID NavId; // 导航聚焦的物品
ImGuiWindow* NavWindow; // 导航聚焦的窗口。也可以被称为“FocusedWindow”
ImGuiID NavFocusScopeId; // 聚焦的焦点范围（例如，当落入同一范围的物品时，选择代码通常希望“清除其他物品”）
ImGuiNavLayer NavLayer; // 聚焦的层（主滚动层，或菜单/标题栏层）
ImGuiID NavActivateId; // ~~ (g.ActiveId == 0) && (IsKeyPressed(ImGuiKey_Space) || IsKeyDown(ImGuiKey_Enter) || IsKeyPressed(ImGuiKey_NavGamepadActivate)) ? NavId : 0，在调用 ActivateItemByID() 时也会设置
ImGuiID NavActivateDownId; // ~~ IsKeyDown(ImGuiKey_Space) || IsKeyDown(ImGuiKey_Enter) || IsKeyDown(ImGuiKey_NavGamepadActivate) ? NavId : 0
ImGuiID NavActivatePressedId; // ~~ IsKeyPressed(ImGuiKey_Space) || IsKeyPressed(ImGuiKey_Enter) || IsKeyPressed(ImGuiKey_NavGamepadActivate) ? NavId : 0 (不重复)
ImGuiActivateFlags NavActivateFlags;
ImVector<ImGuiFocusScopeData> NavFocusRoute; // NavId 的焦点范围栈的反向副本（应包含 NavFocusScopeId）。这本质上遵循 window->ParentWindowForFocusRoute 链。
ImGuiID NavHighlightActivatedId;
float NavHighlightActivatedTimer;
ImGuiID NavNextActivateId; // 由 ActivateItemByID() 设置，排队等待至下一帧。
ImGuiActivateFlags NavNextActivateFlags;
ImGuiInputSource NavInputSource; // 键盘或手柄模式？此处仅能为 ImGuiInputSource_Keyboard 或 ImGuiInputSource_Gamepad
ImGuiSelectionUserData NavLastValidSelectionUserData; // 上次传递给 SetNextItemSelectionUser() 的有效数据，或为 -1。针对当前窗口。当聚焦到没有选择数据的物品时不会重置。
ImS8 NavCursorHideFrames;
//ImGuiID NavActivateInputId; // 已在 1.89.4（2023 年 7 月）中移除。现在是 g.NavActivateId 的一部分，并设置 g.NavActivateFlags |= ImGuiActivateFlags_PreferInput。参见 commit c9a53aa74，issue #5606。


// 导航：初始化与移动请求
bool NavAnyRequest; // ~~ NavMoveRequest || NavInitRequest，用于在 ItemAdd() 中执行提前退出
bool NavInitRequest; // 针对新出现窗口的初始化请求，用于选择第一个项目
bool NavInitRequestFromMove;
ImGuiNavItemData NavInitResult; // 初始化请求结果（窗口的第一个项目，或调用了 SetItemDefaultFocus() 的项目）
bool NavMoveSubmitted; // 移动请求已提交，将在下一次 NewFrame() 时处理结果
bool NavMoveScoringItems; // 已提交移动请求，仍在对传入项目进行评分
bool NavMoveForwardToNextFrame;
ImGuiNavMoveFlags NavMoveFlags;
ImGuiScrollFlags NavMoveScrollFlags;
ImGuiKeyChord NavMoveKeyMods;
ImGuiDir NavMoveDir; // 移动请求的方向（左/右/上/下）
ImGuiDir NavMoveDirForDebug;
ImGuiDir NavMoveClipDir; // FIXME-NAV: 更好地描述此项用途。可能需要重命名？
ImRect NavScoringRect; // 用于评分的矩形，处于屏幕空间。基于 window->NavRectRel[]，并针对方向导航评分进行了修改。
ImRect NavScoringNoClipRect; // 某些导航操作（如 PageUp/PageDown）会强制指定一个区域，裁剪器将尝试始终保持该区域被提交。
int NavScoringDebugCount; // 用于调试的指标
int NavTabbingDir; // 通常为 -1 或 +1，在没有导航 ID 的情况下进行 Tab 切换时为 0。
int NavTabbingCounter; // 在为制表操作计数项目时 >0
ImGuiNavItemData NavMoveResultLocal; // NavWindow 中最佳的移动请求候选对象。
ImGuiNavItemData NavMoveResultLocalVisible; // NavWindow 中最理想的移动请求候选对象，且大部分可见（当使用 ImGuiNavMoveFlags_AlsoScoreVisibleSet 标志时）
ImGuiNavItemData NavMoveResultOther; // NavWindow 扁平化层级结构中最理想的移动请求候选对象（当使用 ImGuiWindowFlags_NavFlattened 标志时）
ImGuiNavItemData NavTabbingResultFirst; // NavWindow 及其扁平化层级结构中的第一个 Tab 键切换请求候选对象


// 导航：最后一次移动请求的记录
ImGuiID NavJustMovedFromFocusScopeId; // 刚刚离开的焦点范围 ID（成功执行 MoveRequest 的结果）。
ImGuiID NavJustMovedToId; // 刚刚导航到的 ID（成功执行 MoveRequest 的结果）。
ImGuiID NavJustMovedToFocusScopeId; // 刚刚导航到的焦点范围 ID（成功执行 MoveRequest 的结果）。
ImGuiKeyChord NavJustMovedToKeyMods;
bool NavJustMovedToIsTabbing; // ImGuiNavMoveFlags_IsTabbing 的副本。或许我们应该存储完整的标志位。
bool NavJustMovedToHasSelectionData; // 移动结果中 (ItemFlags & ImGuiItemFlags_HasSelectionUserData) 的副本。或许我们应该直接存储 ImGuiNavItemData。


// 导航：窗口操作（Ctrl+Tab 用于列表，或菜单按钮 + 按键或方向键进行移动/调整大小）
bool ConfigNavWindowingWithGamepad; // = true。允许通过按住 ImGuiKey_GamepadFaceLeft (== ImGuiKey_NavGamepadMenu) 来启用 Ctrl+Tab。若为 false，该按钮仍可用于切换菜单层。
ImGuiKeyChord ConfigNavWindowingKeyNext; // = ImGuiMod_Ctrl | ImGuiKey_Tab (在 OS X 上为 ImGuiMod_Super | ImGuiKey_Tab)。用于重新配置（参见 #4828）
ImGuiKeyChord ConfigNavWindowingKeyPrev; // = ImGuiMod_Ctrl | ImGuiMod_Shift | ImGuiKey_Tab (在 OS X 上为 ImGuiMod_Super | ImGuiMod_Shift | ImGuiKey_Tab)
ImGuiWindow* NavWindowingTarget; // 执行 Ctrl+Tab（或手柄菜单 + 聚焦上一个/下一个）时的目标窗口，该窗口会临时显示在最顶层！
ImGuiWindow* NavWindowingTargetAnim; // 记录上一个有效的 NavWindowingTarget，直到 DimBgRatio 和 NavWindowingHighlightAlpha 变为 0.0f，以便淡出效果能保持在该窗口上。
ImGuiWindow* NavWindowingListWindow; // 实际列出 Ctrl+Tab 内容的内部窗口
float NavWindowingTimer;
float NavWindowingHighlightAlpha;
ImGuiInputSource NavWindowingInputSource;
bool NavWindowingToggleLayer; // 在按住 Alt 或手柄菜单键时设置，可能会被其他操作清除，并在松开按键时处理。
ImGuiKey NavWindowingToggleKey; // 切换到菜单层时使用的键盘/手柄按键。
ImVec2 NavWindowingAccumDeltaPos;
ImVec2 NavWindowingAccumDeltaSize;


// 渲染
float DimBgRatio; // 0.0..1.0 调暗背景淡入时的动画比例（用于模态窗口和 Ctrl+Tab 列表）


// 拖放
bool DragDropActive;
bool DragDropWithinSource; // 当处于拖放源的 BeginDragDropXXX/EndDragDropXXX 块中时设置。
bool DragDropWithinTarget; // 当处于拖放目标的 BeginDragDropXXX/EndDragDropXXX 块中时设置。
ImGuiDragDropFlags DragDropSourceFlags;
int DragDropSourceFrameCount;
int DragDropMouseButton;
ImGuiPayload DragDropPayload;
ImRect DragDropTargetRect; // 存储当前目标候选者的矩形（当重叠时，我们优先选择较小的目标）
ImRect DragDropTargetClipRect; // 存储物品绘制时的裁剪矩形（ClipRect）
ImGuiID DragDropTargetId;
ImGuiID DragDropTargetFullViewport;
ImGuiDragDropFlags DragDropAcceptFlagsCurr;
ImGuiDragDropFlags DragDropAcceptFlagsPrev;
float DragDropAcceptIdCurrRectSurface; // 当前目标物品表面积（我们通过优先处理较小表面积来解决重叠目标的问题）
ImGuiID DragDropAcceptIdCurr; // 当前目标物品 ID（在接受掉落载荷时设置）
ImGuiID DragDropAcceptIdPrev; // 上一帧的目标物品 ID（我们需要存储此 ID 以允许重叠的拖放目标）
int DragDropAcceptFrameCount; // 目标最后一次表示愿意接受源的时间
ImGuiID DragDropHoldJustPressedId; // 当持有有效载荷并使 ButtonBehavior() 返回按下状态时设置
ImVector<unsigned char> DragDropPayloadBufHeap; // 我们不直接暴露 ImVector<>，ImGuiPayload 仅持有指针和大小
unsigned char DragDropPayloadBufLocal[16]; // 用于小负载的本地缓冲区


// Clipper
int ClipperTempDataStacked;
ImVector<ImGuiListClipperData> ClipperTempData;


// 表格
ImGuiTable* CurrentTable;
ImGuiID DebugBreakInTable; // 设置此项以在调用 BeginTable() 时中断。
int TablesTempDataStacked; // 临时表格数据堆叠大小（因为我们保留了之前的实例未销毁，所以通常不使用 TablesTempData.Size）
ImVector<ImGuiTableTempData> TablesTempData; // 临时表格数据（在实例间重用/共享的缓冲区，支持嵌套）
ImPool<ImGuiTable> Tables; // 持久表格数据
ImVector<float> TablesLastTimeActive; // 每个表格最后一次使用的时间戳（SOA 格式，用于高效垃圾回收）
ImVector<ImDrawChannel> DrawChannelsTempMergeBuffer;


// 选项卡栏 (Tab bars)
ImGuiTabBar* CurrentTabBar;
ImPool<ImGuiTabBar> TabBars;
ImVector<ImGuiPtrOrIndex> CurrentTabBarStack;
ImVector<ImGuiShrinkWidthItem> ShrinkWidthBuffer;


// 多选状态
ImGuiBoxSelectState BoxSelectState;
ImGuiMultiSelectTempData* CurrentMultiSelect;
int MultiSelectTempDataStacked; // 临时多选数据大小（因为我们保留了之前的实例未销毁，所以通常不使用 MultiSelectTempData.Size）
ImVector<ImGuiMultiSelectTempData> MultiSelectTempData;
ImPool<ImGuiMultiSelectState> MultiSelectStorage;


// 悬停延迟系统
ImGuiID HoverItemDelayId;
ImGuiID HoverItemDelayIdPreviousFrame;
float HoverItemDelayTimer; // 当前由 IsItemHovered() 使用
float HoverItemDelayClearTimer; // 当前由 IsItemHovered() 使用：g.TooltipHoverTimer 被清除前的缓冲时间。
ImGuiID HoverItemUnlockedStationaryId; // 鼠标曾在此物品上保持静止。仅在离开该物品后重置。
ImGuiID HoverWindowUnlockedStationaryId; // 鼠标曾在此窗口上停留。仅在离开窗口后重置。


// 鼠标状态
ImGuiMouseCursor MouseCursor;
float MouseStationaryTimer; // 鼠标停留时长（采用模糊启发式算法）
ImVec2 MouseLastValidPos;


// 组件状态
ImGuiInputTextState InputTextState;
ImGuiTextIndex InputTextLineIndex; // 临时存储
ImGuiInputTextDeactivatedState InputTextDeactivatedState;
ImFontBaked InputTextPasswordFontBackupBaked;
ImFontFlags InputTextPasswordFontBackupFlags;
ImGuiID TempInputId; // 在滑块等控件上使用 Ctrl+点击时的临时文本输入 ID
ImGuiDataTypeStorage DataTypeZeroValue; // 所有数据类型的 0 值
int BeginMenuDepth;
int BeginComboDepth;
ImGuiColorEditFlags ColorEditOptions; // 存储颜色编辑小部件的用户选项
ImGuiID ColorEditCurrentID; // 在最外层父级 ColorEdit4/ColorPicker4 内部时临时设置（因为它们会互相调用）。
ImGuiID ColorEditSavedID; // 我们正在为其保存/恢复 HS 的 ID
float ColorEditSavedHue; // 与 LastColor 关联的上一次色相备份，以便我们在有损的 RGB<>HSV 转换回合中恢复色相
float ColorEditSavedSat; // 与 LastColor 关联的上一次饱和度备份，以便我们在有损的 RGB<>HSV 转换回合中恢复饱和度
ImU32 ColorEditSavedColor; // Alpha 值设为 0 的 RGB 值。
ImVec4 ColorPickerRef; // 打开颜色选择器时的初始/参考颜色。
ImGuiComboPreviewData ComboPreviewData;
ImRect WindowResizeBorderExpectedRect; // 预期的边框矩形，如果移动则切换到相对编辑模式
bool WindowResizeRelativeMode;
short ScrollbarSeekMode; // 0: 滚动至点击位置，-1/+1: 上一页/下一页。
float ScrollbarClickDeltaToGrabCenter; // 当滚动至鼠标位置时：鼠标与抓取框中心之间的距离，在父空间中归一化。
float SliderGrabClickOffset;
float SliderCurrentAccum; // 使用导航控件时累积的滑块增量。
bool SliderCurrentAccumDirty; // 自上次尝试应用以来，累积的滑块增量（delta）是否发生了变化？
bool DragCurrentAccumDirty;
float DragCurrentAccum; // 拖动修改的累加器。始终保持高精度，不受最终用户精度设置的舍入影响
float DragSpeedDefaultRatio; // 如果 speed == 0.0f，则使用 (max-min) * DragSpeedDefaultRatio
float DisabledAlphaBackup; // 用于 BeginDisabled() 的 style.Alpha 备份
short DisabledStackSize;
short TooltipOverrideCount;
ImGuiWindow* TooltipPreviousWindow; // 当前帧内最后提交的工具提示窗口
ImVector<char> ClipboardHandlerData; // 如果未定义自定义剪贴板处理程序
ImVector<ImGuiID> MenusIdSubmittedThisFrame; // 在本帧中至少渲染过一次的菜单 ID 列表
ImGuiTypingSelectState TypingSelectState; // GetTypingSelectRequest() 的状态


// 平台支持
ImGuiPlatformImeData PlatformImeData; // 当前帧更新的数据。将在帧结束时应用。对于某些后端，必须设置 WantVisible=true 才能接收文本消息。
ImGuiPlatformImeData PlatformImeDataPrev; // 前一帧的数据。当数据发生变化时，我们会调用 platform_io.Platform_SetImeDataFn() 句柄。


// 扩展
// FIXME：我们可以提供一个 API，在 ImGuiContext 持有的数组中注册一个槽位吗？
ImVector<ImTextureData*> UserTextures; // 由用户或第三方扩展创建/管理的纹理列表。自动追加到 platform_io.Textures[] 中。


// 设置
bool SettingsLoaded;
float SettingsDirtyTimer; // 当时间归零时，将 .ini 设置保存到内存中
ImGuiTextBuffer SettingsIniData; // 内存中的 .ini 设置数据
ImVector<ImGuiSettingsHandler> SettingsHandlers; // .ini 设置处理器列表
ImChunkStream<ImGuiWindowSettings> SettingsWindows; // ImGuiWindow .ini 设置条目
ImChunkStream<ImGuiTableSettings> SettingsTables; // ImGuiTable .ini 设置条目
ImVector<ImGuiContextHook> Hooks; // 扩展钩子（例如测试引擎）
ImGuiID HookIdNext; // 下一个可用的 HookId


// 本地化
const char* LocalizationTable[ImGuiLocKey_COUNT];


// 捕获/日志记录
bool LogEnabled; // 当前正在捕获
bool LogLineFirstItem;
ImGuiLogFlags LogFlags; // 捕获标志/类型
ImGuiWindow* LogWindow;
ImFileHandle LogFile; // 如果 != NULL，则记录到标准输出/文件
ImGuiTextBuffer LogBuffer; // 记录到剪贴板时的累积缓冲区。这是一个指针，以便我们的 GImGui 静态构造函数不会调用堆分配器。
const char* LogNextPrefix; // 参见 LogSetNextTextDecoration() 中的注释：不拷贝底层数据，请谨慎使用！
const char* LogNextSuffix;
float LogLinePosY;
int LogDepthRef;
int LogDepthToExpand;
int LogDepthToExpandDefault; // 如果在 LogXXX 函数调用中未指定，则为 LogDepthMaxExpand 的默认/存储值。


// 错误处理
ImGuiErrorCallback ErrorCallback; // = NULL。最终可能会在公共 API 中公开。
void* ErrorCallbackUserData; // = NULL
ImVec2 ErrorTooltipLockedPos;
bool ErrorFirst;
int ErrorCountCurrentFrame; // [内部] 本帧提交的错误数量。
ImGuiErrorRecoveryState StackSizesInNewFrame; // [内部]
ImGuiErrorRecoveryState* StackSizesInBeginForCurrentWindow; // [内部]


// 调试工具
// (一些高频使用的数据交错排列在上方其他结构体中：DebugBreakXXX 字段、DebugHookIdInfo、DebugLocateId 等)
int DebugDrawIdConflictsCount; // 锁定的计数（按住 Ctrl 时保留）
ImGuiDebugLogFlags DebugLogFlags;
ImGuiTextBuffer DebugLogBuf;
ImGuiTextIndex DebugLogIndex;
int DebugLogSkippedErrors;
ImGuiDebugLogFlags DebugLogAutoDisableFlags;
ImU8 DebugLogAutoDisableFrames;
ImU8 DebugLocateFrames; // 用于 DebugLocateItemOnHover()。这与上方处于热点/缓存区域的 DebugLocateId 配合使用。
bool DebugBreakInLocateId; // 在 g.DebugLocateId 的 ItemAdd() 调用中触发调试断点。
ImGuiKeyChord DebugBreakKeyChord; // = ImGuiKey_Pause
ImS8 DebugBeginReturnValueCullDepth; // 在 0..9 之间循环，然后返回。
bool DebugItemPickerActive; // 物品选择器处于激活状态（通过 DebugStartItemPicker() 启动）
ImU8 DebugItemPickerMouseButton;
ImGuiID DebugItemPickerBreakId; // 当遇到此 ID 时将调用 IM_DEBUG_BREAK()
float DebugFlashStyleColorTime;
ImVec4 DebugFlashStyleColorBackup;
ImGuiMetricsConfig DebugMetricsConfig;
ImGuiDebugItemPathQuery DebugItemPathQuery;
ImGuiIDStackTool DebugIDStackTool;
ImGuiDebugAllocInfo DebugAllocInfo;
#if defined(IMGUI_DEBUG_HIGHLIGHT_ALL_ID_CONFLICTS) && !defined(IMGUI_DISABLE_DEBUG_TOOLS)
ImGuiStorage DebugDrawIdConflictsAliveCount;
ImGuiStorage DebugDrawIdConflictsHighlightSet;
#endif


// 杂项
float FramerateSecPerFrame[60]; // 计算过去 60 帧内用户的估算帧率。
int FramerateSecPerFrameIdx;
int FramerateSecPerFrameCount;
float FramerateSecPerFrameAccum;
int WantCaptureMouseNextFrame; // 通过 SetNextFrameWantCaptureMouse()/SetNextFrameWantCaptureKeyboard() 显式覆盖捕获状态。默认为 -1。
int WantCaptureKeyboardNextFrame; // "
int WantTextInputNextFrame; // 在 EndFrame() 中从 g.PlatformImeData.WantTextInput 复制。某些后端（如 SDL3）需要设置此项才能发出字符输入。
ImVector<char> TempBuffer; // 临时文本缓冲区
char TempKeychordName[64];


ImGuiContext(ImFontAtlas* shared_font_atlas);
~ImGuiContext();
};