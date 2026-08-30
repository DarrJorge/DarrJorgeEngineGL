# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project overview

DJEngine (`DarrJorgeEngine`) is a custom C++23 game engine. Current renderer backend is OpenGL (D3D12/Vulkan are
selectable via CMake but unimplemented — selecting them fails at compile time). Windowing works on Windows (GLFW or
native WinAPI), Linux and macOS (GLFW only).

## Working agreement (must follow)

- **Propose, then wait.** Before touching any file, present the proposed solution (what will change and why) and
  wait for explicit approval. Do not create, edit, or delete files until the user confirms — this applies to every
  change, not just large ones.
- **Fit the existing architecture.** Proposals must be the best solution given the architecture below (Window /
  Render / Scene / Event / Log layering) — extend it rather than bypass, duplicate, or work around it.
- **Architecture changes get a separate approval step.** If a task cannot be solved without changing the existing
  architecture, first present a plan of the architectural change on its own (what changes structurally and why) and
  get explicit approval for that plan specifically, before proposing or making the actual implementation.

## Build system

CMake (>=3.28.1) + Conan 2 (`CMakeDeps`/`CMakeToolchain` generators). The root `CMakeLists.txt` picks a Conan
profile from `automation/ConanProfiles/` based on host OS + build type (e.g. `macosDebug`, `windowsRelease`) before
adding the `Engine` subdirectory, which defines the actual targets.

All build actions go through `automation/automation.py` (invoked via `automation/build.sh`, which the root-level
`*.sh`/`*.bat` scripts wrap):

```bash
./generate_project_files.sh   # automation/build.sh generate Debug — CMake configure into build/
./build_debug.sh              # automation/build.sh generate Debug && build Debug
./build_release.sh            # automation/build.sh generate Release && build Release
./format_all_files.sh         # automation/build.sh clang_format — clang-format -i over Engine/ (*.cpp, *.h, *.hpp)
./clean.sh                    # automation/build.sh clean — removes build/
```

On macOS/Linux the generator is Ninja; on Windows it's Visual Studio. Binaries land in `build/bin/`.

CMake options (set at configure time, e.g. `-DENGINE_RENDERER_API=OpenGL`):
- `ENGINE_USE_GLFW` (Windows only; default ON) — GLFW vs native WinAPI window backend.
- `ENGINE_RENDERER_API` — `OpenGL` (default) | `D3D12` | `Vulkan`.

## Testing

No CTest integration — the test binary is a plain GTest executable built from `Engine/Tests/*.cpp`:

```bash
./build_debug.sh
build/bin/DarrJorgeEngineTestRunner                          # run all tests
build/bin/DarrJorgeEngineTestRunner --gtest_filter=EventTest.*   # run a subset
```

New test files must be added explicitly to the `add_executable(${PROJECT_NAME}TestRunner ...)` call in
`Engine/CMakeLists.txt`.

## Architecture

### Targets
`Engine/CMakeLists.txt` defines three targets sharing one source list (`ENGINE_SOURCES`, with WinAPI files appended
conditionally on `WIN32`):
- `DarrJorgeEngineLib` — static lib, all engine code, `Source/` as public include root.
- `DarrJorgeEngine` — the executable (`Source/main.cpp`), links the lib + Boost.
- `DarrJorgeEngineTestRunner` — GTest binary, links the lib + gtest.

New source files must be added to `ENGINE_SOURCES` by hand (no glob).

### Window layer (`Source/Window`)
`IWindow` is the per-window interface; `WindowManager` is an abstract owner of `WindowId -> IWindow` that tracks
lifecycle (`allWindowsClosed`, `cleanupClosedWindows`) and is subclassed per backend (`GLFW/GLFWWindowManager`,
`WinAPI/WinAPIWindowManager`). `WindowManagerFactory::Create()` picks the concrete manager via preprocessor checks on
`_WIN32`/`__linux__`/`__APPLE__` and `ENGINE_USE_GLFW` — this is the only place backend selection happens. Each
`IWindow` exposes an `Event<const InputEvent&>` that the owner (currently `Engine`) subscribes to for input.

### Render layer (`Source/Render`)
Two parallel abstractions, both backend-selected via the `ENGINE_RENDERER_API` compile define
(`ENGINE_RENDERER_OPENGL` etc.), OpenGL implementations live under `Source/Render/OpenGL` (`GL*` classes):
- `RHI/` — resource-creation side: `RenderDevice` creates `IShader`/`IVertexBuffer`/`IIndexBuffer`/`IVertexArray`.
- `Renderer/` — draw-call side: `RendererAPI` is the per-backend interface (`clear`, `setClearColor`, `drawIndexed`);
  `RenderCommand` is a static facade dispatching to a single `RendererAPI*` instance; `Renderer::render(scene, camera)`
  drives `beginFrame`/`endFrame` around scene submission.

### Scene layer (`Source/Scene`)
Not an ECS — plain OOP composition. `Entity` owns its `Component`s (`std::vector<std::unique_ptr<Component>>`);
`addComponent<T>`/`getComponent<T>`/`removeComponent<T>` use `dynamic_cast` for lookup, so `Component` needs `virtual
~Component()`. Concrete components live in `Scene/Components/` (`TransformComponent`, `MeshRendererComponent`).
`Scene` holds `std::vector<std::shared_ptr<Entity>>` and calls `update(deltaTime)` on its objects each frame.

### Event system (`Source/Event`)
`Event<Args...>` (`Event.h`) is a generic pub/sub type: `add(delegate)` / `add(obj, &Obj::method)` returns an
`EventHandle` for `remove`; `invoke(args...)` fans out to all subscribers. `InputEvent.h` builds on it for window
input: `InputEvent` wraps a `std::variant` of `MouseScrollEventData`/`MouseMoveEventData`/`WindowResizeEventData`/
`WindowCloseEventData`, consumed via `std::get_if` (see `Engine::onWindowEvent`).

### Logging (`Source/Log`)
`Log` is a singleton wrapping spdlog. Declare a category once per translation unit with
`DEFINE_LOG_CATEGORY_STATIC(Name)`, then log with `LOG(Name, Verbosity, "fmt {}", args...)` or `LOG_DEBUG(...)` (adds
source location). Verbosity below `c_minVerbosity` is compiled out via `if constexpr`.

### Frame loop
`Engine::run()` (`Core/Engine.cpp`) loops until `WindowManager::allWindowsClosed()`: computes `deltaTime`, calls
`Scene::update`, `Renderer::render(scene, camera)`, then `WindowManager::update()`.

### Utility (`Source/Core/Utility.h`)
`NonCopyable`/`NonMoveable` base classes and `PLATFORM_BREAK()` (compiler-specific trap/debugbreak) are shared
building blocks used across the codebase.

## Code style

`.clang-format` (Microsoft base, 4-space indent, Allman braces, 140-col limit, left-aligned pointers,
`AccessModifierOffset: -4`) is the source of truth — run `./format_all_files.sh` rather than hand-formatting. Class
member fields use an `m_` prefix, static members `s_`, constants `c_`.
