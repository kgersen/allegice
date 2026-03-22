#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_opengl3.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_opengles2.h>
#include <emscripten.h>

static SDL_Window*   g_window  = nullptr;
static SDL_GLContext g_gl_ctx  = nullptr;

void main_loop() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        ImGui_ImplSDL3_ProcessEvent(&event);
    }

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    // Your ImGui windows here
    ImGui::Begin("Hello, browser!");
    ImGui::Text("ImGui + SDL3 + Emscripten");
    if (ImGui::Button("Click me"))
        SDL_Log("Button clicked!");
    ImGui::End();

    ImGui::Render();

    int w, h;
    SDL_GetWindowSize(g_window, &w, &h);
    glViewport(0, 0, w, h);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    SDL_GL_SwapWindow(g_window);
}

int main() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return -1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    g_window = SDL_CreateWindow("ImGui Web", 1280, 720,
                                SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!g_window) {
        SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
        return -1;
    }

    g_gl_ctx = SDL_GL_CreateContext(g_window);
    if (!g_gl_ctx) {
        SDL_Log("SDL_GL_CreateContext failed: %s", SDL_GetError());
        return -1;
    }

    SDL_GL_MakeCurrent(g_window, g_gl_ctx);
    SDL_GL_SetSwapInterval(1); // vsync

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

    ImGui_ImplSDL3_InitForOpenGL(g_window, g_gl_ctx);
    ImGui_ImplOpenGL3_Init("#version 300 es");

    emscripten_set_main_loop(main_loop, 0, true);

    // Cleanup — never reached in browser, but good practice
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
    SDL_GL_DestroyContext(g_gl_ctx);
    SDL_DestroyWindow(g_window);
    SDL_Quit();

    return 0;
}