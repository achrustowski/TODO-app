#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#include <stdbool.h>
#include "enums.h"
#include <raygui.h>

typedef struct Textbox Textbox;
typedef struct Button Button;

typedef struct
{
    bool        show_main_screen;
    bool        show_new_item_screen;
    int         S_W;
    int         S_H;
    int         frame_counter;
} App;

struct Textbox
{
    Rectangle   dimensions;
    Vector2     position;
    Color       color;
    bool        mouse_on_text;
    char        buffer[128];
    int         letter_count;
    int         font_size;
};

struct Button
{
    Rectangle   dimensions;
    Texture2D   texture;
    Vector2     position;
    bool        is_pressed;
    bool        is_hovered;
    int         font_size;
    Button_Type btn_type;
};

typedef struct
{
    Textbox     textbox;
    Button      buttons[3];
} Item;

typedef struct
{
    int         font_size;
    Font        font;
} Gui;

#endif
