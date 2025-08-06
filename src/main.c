#include <stdbool.h>
#include <stdio.h>
#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

int main()
{
    int S_W = 900;
    int S_H = 600;

    bool show_main_screen = true;
    bool show_add_item_screen = false;

    char* buffer = calloc(1024, sizeof(char));
    strncpy(buffer, "", 1024);

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(S_W, S_H, "TODO App");

    Font font = LoadFont("./fonts/TerminessNerdFont-Bold.ttf");

    while (!WindowShouldClose())
    {
        if (IsWindowResized() && !IsWindowFullscreen())
        {
            S_W = GetScreenWidth();
            S_H = GetScreenHeight();
        }
        BeginDrawing();
        ClearBackground(BLACK);
        GuiSetFont(font);
        GuiSetStyle(DEFAULT, TEXT_SIZE, 18);
        if (show_main_screen)
        {
            if (GuiButton((Rectangle) {100.0f, 100.0f, 100.0f, 30.0f}, "New item") == true)
            {
                show_main_screen = false;
                show_add_item_screen = true;
            }
        }
        if (show_add_item_screen)
        {
            if (GuiTextInputBox((Rectangle){300.0f, 300.0f, 450.0f, 150.0f}, 0, "Enter item summary", "New item", buffer, 1024, false) == true)
            {
                show_add_item_screen = false;
                show_main_screen = true;
            }
        }
        EndDrawing();
    }
    
    CloseWindow();

    return 0;
}
