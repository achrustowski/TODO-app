#include <stdbool.h>
#include <raylib.h>
#include "gui_elements.h"
#include "init.h"
#include "structs.h"

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

App app;
Gui gui;

int main()
{
    memset(&app, 0, sizeof(App));
    app.S_W = 900;
    app.S_H = 600;

    SetTargetFPS(60);

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(app.S_W, app.S_H, "TODO App");

    init_gui();
    init_fonts();
    init_gui_style();
    initialize_gui_elements();

    while (!WindowShouldClose())
    {
        if (IsWindowResized() && !IsWindowFullscreen())
        {
            app.S_W = GetScreenWidth();
            app.S_H = GetScreenHeight();
        }
        gui_elements_logic();
        BeginDrawing();
        ClearBackground(BLACK);
        draw_main_page();
        EndDrawing();
    }
    
    CloseWindow();

    return 0;
}
