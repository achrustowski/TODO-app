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

static Textbox  input_boxes[5];
static Button   check_buttons[5];
static Button   cross_buttons[5];
static Button   edit_buttons[5];

static Textbox add_new_item_textbox(float y);
static Button add_new_button(float x, float y, float w, char* label);
static void textbox_interact(Textbox* textbox);
static void draw_text(char* text, int x, int y, int font_size);

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

static void draw_text(char* text, int x, int y, int font_size)
{
    //draw actuall textbox buffer onto the screen, at this point x & y padding values are constants, can they be dynamic?
    DrawText(text, (int)x + 10, (int)y + 10, font_size, RAYWHITE);
};

void initialize_gui_elements()
{
    for (int i = 0; i < 5; i++)
    {
        input_boxes[i] = add_new_item_textbox(140 + (1 * i) * (TEXTBOX_HEIGHT + 20));
    }

    for (int i = 0; i < 5; i++)
    {
        check_buttons[i] = add_new_button(605, 140 + i * (TEXTBOX_HEIGHT + 20), 40, "•");
    }

    for (int i = 0; i < 5; i++)
    {
        cross_buttons[i] = add_new_button(655, 140 + i * (TEXTBOX_HEIGHT + 20), 40, "X");
    }

    for (int i = 0; i < 5; i++)
    {
        edit_buttons[i] = add_new_button(705, 140 + i * (TEXTBOX_HEIGHT + 20), 70, "Edit");
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

static Button add_new_button(float x, float y, float w, char* label)
{
    Button button;
    memset(&button, 0, sizeof(button));

    button.dimensions = (Rectangle){x, y, w, TEXTBOX_HEIGHT};
    strcat(button.label, label);
    button.font_size = 28;
    button.is_pressed = false;

    return button;
}

void draw_main_page()
{
    for (int i = 0; i < 5; i++)
    {
        draw_textbox(input_boxes[i].dimensions, BLACK);
        draw_text(input_boxes[i].buffer, input_boxes[i].dimensions.x, input_boxes[i].dimensions.y, input_boxes[i].font_size);

        DrawRectangleLines((int)input_boxes[i].dimensions.x, (int)input_boxes[i].dimensions.y,
                (int)input_boxes[i].dimensions.width, (int)input_boxes[i].dimensions.height, input_boxes[i].mouse_on_text ? GREEN : RED);
    }
    for (int i = 0; i < 5; i++)
    {
        draw_textbox(check_buttons[i].dimensions, BLACK);
        draw_text(check_buttons[i].label, check_buttons[i].dimensions.x, check_buttons[i].dimensions.y, check_buttons[i].font_size);

        DrawRectangleLines((int)check_buttons[i].dimensions.x, (int)check_buttons[i].dimensions.y,
                (int)check_buttons[i].dimensions.width, (int)check_buttons[i].dimensions.height, check_buttons[i].is_pressed ? GREEN : RED); 
    }
    for (int i = 0; i < 5; i++)
    {
        draw_textbox(cross_buttons[i].dimensions, BLACK);
        draw_text(cross_buttons[i].label, cross_buttons[i].dimensions.x, cross_buttons[i].dimensions.y, cross_buttons[i].font_size);

        DrawRectangleLines((int)cross_buttons[i].dimensions.x, (int)cross_buttons[i].dimensions.y,
                (int)cross_buttons[i].dimensions.width, (int)cross_buttons[i].dimensions.height, cross_buttons[i].is_pressed ? GREEN : RED); 
    }
    for (int i = 0; i < 5; i++)
    {
        draw_textbox(edit_buttons[i].dimensions, BLACK);
        draw_text(edit_buttons[i].label, edit_buttons[i].dimensions.x, edit_buttons[i].dimensions.y, edit_buttons[i].font_size);

        DrawRectangleLines((int)edit_buttons[i].dimensions.x, (int)edit_buttons[i].dimensions.y,
                (int)edit_buttons[i].dimensions.width, (int)edit_buttons[i].dimensions.height, edit_buttons[i].is_pressed ? GREEN : RED); 
    }
};
