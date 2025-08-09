#include <raygui.h>
#include "gui_elements.h"
#include "defs.h"
#include "draw.h"
#include "raylib.h"
#include "structs.h"
#include <string.h>
#include <stdio.h>

extern App app;
extern Gui gui;

static Textbox input_boxes[4];

static Textbox add_new_item_textbox(float y);
static void textbox_interact(Textbox* textbox);
static void draw_text(Textbox* textbox);

void gui_elements_logic()
{
    for (int i = 0; i < 5; i++)
    {
        textbox_interact(&input_boxes[i]);
    }
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
    //draw actuall textbox buffer onto the screen, at this point x & y padding values are constants, can they be dynamic?
    DrawText(textbox->buffer, (int)textbox->dimensions.x + 5, (int)textbox->dimensions.y + 10, textbox->font_size, RAYWHITE);
};

void initialize_gui_elements()
{
    for (int i = 0; i < 5; i++)
    {
        input_boxes[i] = add_new_item_textbox(140 + (1 * i) * (TEXTBOX_HEIGHT + 20));
    }
};

static Textbox add_new_item_textbox(float y)
{
    Textbox textbox;
    memset(&textbox, 0, sizeof(textbox));

    textbox.dimensions = (Rectangle){app.S_W / 4.0f - 100, y, 425, TEXTBOX_HEIGHT};
    textbox.mouse_on_text = false;
    textbox.letter_count = 0;
    textbox.font_size = 28;
    strncpy(textbox.buffer, "\0", sizeof(textbox.buffer));

    return textbox;
};

void draw_main_page()
{
    for (int i = 0; i < 5; i++)
    {
        draw_textbox(input_boxes[i].dimensions, BLACK);
        draw_text(&input_boxes[i]);

        DrawRectangleLines((int)input_boxes[i].dimensions.x, (int)input_boxes[i].dimensions.y,
                (int)input_boxes[i].dimensions.width, (int)input_boxes[i].dimensions.height, input_boxes[i].mouse_on_text ? GREEN : RED);
    }
};
