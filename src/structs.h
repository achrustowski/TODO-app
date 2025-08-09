#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#include <stdbool.h>
#include "enums.h"
#include <raygui.h>

typedef struct Item Item;

typedef struct
{
    bool        show_main_screen;
    bool        show_new_item_screen;
    int         S_W;
    int         S_H;
    int         frame_counter;
} App;

struct Item
{
    bool        is_completed;
    bool        in_progress;
    char        date_added[10];
    char        summary[128];
    Category    category;
    Item*       prev;
    Item*       next;
};

typedef struct
{
    Rectangle   dimensions;
    bool        mouse_on_text;
    char        buffer[128];
    int         letter_count;
    int         font_size;
} Textbox;

typedef struct
{
    Rectangle   dimensions;
    char        label[20];
    bool        is_pressed;
    int         font_size;
} Button;

typedef struct
{
    int         font_size;
    Font        font;
} Gui;

#endif
