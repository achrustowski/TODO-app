#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <raylib.h>

typedef struct Item Item;

typedef enum
{
    WORK,
    HOME,
    HOBBY
} Category;

struct Item
{
    bool        is_completed;
    bool        in_progress;
    char        date_added[10];
    char        summary[60];
    Category    category;
    Item*       prev;
    Item*       next;
};

int main()
{
    int S_W = 900;
    int S_H = 600;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(S_W, S_H, "TODO App");

    Font font = LoadFont("/Users/work/Library/Fonts/TerminessNerdFont-Regular.ttf");

    char msg[20];

    strncpy(msg, "Hello", 20);

    while (!WindowShouldClose())
    {
        if (IsWindowResized() && !IsWindowFullscreen())
        {
            S_W = GetScreenWidth();
            S_H = GetScreenHeight();
        }
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTextEx(font, msg, (Vector2){100.0f, 100.f}, 20.0f, 1.0f, WHITE);
        EndDrawing();
    }
    
    CloseWindow();

    return 0;
}
