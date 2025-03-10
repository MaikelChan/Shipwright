#pragma once

#include "SohConsole.h"

struct GameAsset {
    uint32_t textureId;
    int width;
    int height;
};

namespace SohImGui {
    enum class Backend {
        DX11,
        SDL
    };

    enum class Dialogues {
        dConsole,
        dMenubar,
        dLoadSettings,
    };

    typedef struct {
        Backend backend;
        union {
            struct {
                void* window;
                void* device_context;
                void* device;
            } dx11;
            struct {
                void* window;
                void* context;
            } sdl;
        };
    } WindowImpl;

    typedef union {
        struct {
            void* handle;
            int msg;
            int wparam;
            int lparam;
        } win32;
        struct {
            void* event;
        } sdl;
    } EventImpl;

    extern WindowImpl impl;

    using WindowDrawFunc = void(*)(bool& enabled);

    typedef struct {
        bool enabled;
        WindowDrawFunc drawFunc;
    } CustomWindow;

    extern Console* console;
    void Init(WindowImpl window_impl);
    void Update(EventImpl event);
    void Draw(void);
    void ShowCursor(bool hide, Dialogues w);
    void BindCmd(const std::string& cmd, CommandEntry entry);
    void AddWindow(const std::string& category, const std::string& name, WindowDrawFunc drawFunc);
    void LoadResource(const std::string& name, const std::string& path);
    ImTextureID GetTextureByID(int id);
    ImTextureID GetTextureByName(const std::string& name);
}
