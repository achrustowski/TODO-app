#include <raygui.h>
#include "gui_elements.h"
#include "draw.h"
#include "raylib.h"
#include "structs.h"
#include <string.h>
#include <stdio.h>

extern App app;
extern Gui gui;

static Textbox new_item_textbox;

static void set_gui_defaults(void);
static void add_new_item_textbox(void);
static void textbox_interact(Textbox* textbox);
static void draw_text(Textbox* textbox);

void gui_elements_logic()
{
    textbox_interact(&new_item_textbox);
};

static void textbox_interact(Textbox* textbox)
{
    if (CheckCollisionPointRec(GetMousePosition(), textbox->dimensions))
    {
        textbox->mouse_on_text = true;
    } else
    {
        textbox->mouse_on_text = false;
    }
    if (textbox->mouse_on_text)
    {
        SetMouseCursor(MOUSE_CURSOR_IBEAM);
        int key = GetCharPressed();

        while (key > 0)
        {
            if ((key >= 32) && (key <= 125) && (textbox->letter_count < 128))
            {
                textbox->buffer[textbox->letter_count] = (char)key;
                textbox->buffer[textbox->letter_count + 1] = '\0';
                textbox->letter_count++;
            }
            key = GetCharPressed();
        }
        if (IsKeyDown(KEY_BACKSPACE))
        {
            textbox->letter_count--;
            if (textbox->letter_count < 0)
            {
                textbox->letter_count = 0;
            }
            textbox->buffer[textbox->letter_count] = '\0';
            WaitTime(0.09);
        }

    } else
    {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

    if (textbox->mouse_on_text)
    {
        app.frame_counter++;
    } else
    {
        app.frame_counter = 0;
    }
};

static void draw_text(Textbox* textbox)
{
    DrawText(textbox->buffer, (int)textbox->dimensions.x + 5, (int)textbox->dimensions.y + 5, textbox->font_size, MAROON);
};

void initialize_gui_elements()
{
    set_gui_defaults();
    add_new_item_textbox();
};

static void set_gui_defaults()
{
    GuiSetFont(gui.font);
    GuiSetStyle(DEFAULT, TEXT_SIZE, gui.font_size);
};

static void add_new_item_textbox()
{
    memset(&new_item_textbox, 0, sizeof(new_item_textbox));

    new_item_textbox.dimensions = (Rectangle){app.S_W / 2.0f - 100, 180, 225, 50};
    new_item_textbox.mouse_on_text = false;
    new_item_textbox.letter_count = 0;
    new_item_textbox.font_size = 36;
    strncpy(new_item_textbox.buffer, "\0", sizeof(new_item_textbox.buffer));
};

void draw_main_page()
{
    draw_textbox(new_item_textbox.dimensions, LIGHTGRAY);
    draw_text(&new_item_textbox);
    if (new_item_textbox.mouse_on_text)
    {
        DrawRectangleLines((int)new_item_textbox.dimensions.x, (int)new_item_textbox.dimensions.y,
                (int)new_item_textbox.dimensions.width, (int)new_item_textbox.dimensions.height, GREEN);
    } else
    {
        DrawRectangleLines((int)new_item_textbox.dimensions.x, (int)new_item_textbox.dimensions.y,
                (int)new_item_textbox.dimensions.width, (int)new_item_textbox.dimensions.height, RED);
    }
};
