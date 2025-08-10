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
static Button add_new_button(float x, float y, float w, float h, char* filename);
static void textbox_interact(Textbox* textbox);
static void buttons_interact(Button* button);
static void draw_text(char* text, int x, int y, int font_size);
static void update_textbox_position(Textbox* textbox, int i);
static void update_button_position(Button* button, int i, float d);

void gui_elements_logic()
{
    for (int i = 0; i < 5; i++)
    {
        textbox_interact(&input_boxes[i]);
        update_textbox_position(&input_boxes[i], i);
    }
    for (int i = 0; i < 5; i++)
    {
        buttons_interact(&check_buttons[i]);
        update_button_position(&check_buttons[i], i, 6.0f);
    }
    for (int i = 0; i < 5; i++)
    {
        buttons_interact(&cross_buttons[i]);
        update_button_position(&cross_buttons[i], i, 4.0f);
    }
    for (int i = 0; i < 5; i++)
    {
        buttons_interact(&edit_buttons[i]);
        update_button_position(&edit_buttons[i], i, 3.0f);
    }
};

static void textbox_interact(Textbox* textbox)
{
    if (CheckCollisionPointRec(GetMousePosition(),
                (Rectangle){textbox->position.x, textbox->position.y, textbox->dimensions.width, textbox->dimensions.height}))
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
};

static void buttons_interact(Button* button)
{
    if (CheckCollisionPointRec(GetMousePosition(),
                (Rectangle){button->position.x, button->position.y, button->dimensions.width, button->dimensions.height}))
    {
        button->is_pressed = true;
    } else
    {
        button->is_pressed = false;
    }
    if (button->is_pressed)
    {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
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
        input_boxes[i] = add_new_item_textbox(app.S_H / 4.0f + i * (TEXTBOX_HEIGHT + app.S_H / 20.0f));
    }

    for (int i = 0; i < 5; i++)
    {
        check_buttons[i] = add_new_button(input_boxes[i].dimensions.width + app.S_W / 6.0f,
                app.S_H / 4.0f + i * (TEXTBOX_HEIGHT + app.S_H / 20.0f), 48.0f, 48.0f, "./icons/checked.png");
    }

    for (int i = 0; i < 5; i++)
    {
        cross_buttons[i] = add_new_button(input_boxes[i].dimensions.width + app.S_W / 4.0f,
                app.S_H / 4.0f + i * (TEXTBOX_HEIGHT + app.S_H / 20.0f), 48.0f, 48.0f, "./icons/remove.png");
    }

    for (int i = 0; i < 5; i++)
    {
        edit_buttons[i] = add_new_button(input_boxes[i].dimensions.width + app.S_W / 3.0f,
                app.S_H / 4.0f + i * (TEXTBOX_HEIGHT + app.S_H / 20.0f), 48.0f, 48.0f, "./icons/pencil.png");
    }
};

static Textbox add_new_item_textbox(float y)
{
    Textbox textbox;
    memset(&textbox, 0, sizeof(textbox));

    textbox.dimensions = (Rectangle){(app.S_W / 4.0f - app.S_W / 6.0f), y, app.S_W / 2.0f, TEXTBOX_HEIGHT};
    textbox.mouse_on_text = false;
    textbox.letter_count = 0;
    textbox.font_size = 28;
    strncpy(textbox.buffer, "\0", sizeof(textbox.buffer));

    return textbox;
};

static Button add_new_button(float x, float y, float w, float h, char* filename)
{
    Button button;
    memset(&button, 0, sizeof(button));

    button.dimensions = (Rectangle){0.0f, 0.0f, w, h};
    button.texture = load_texture(filename);
    button.font_size = 28;
    button.is_pressed = false;
    button.position = (Vector2){x, y};

    return button;
}

static void update_textbox_position(Textbox* textbox, int i)
{
    textbox->position.x = (app.S_W / 4.0f - app.S_W / 6.0f);
    textbox->position.y = app.S_H / 4.0f + i * (TEXTBOX_HEIGHT + app.S_H / 20.0f);
    textbox->dimensions.width = app.S_W / 2.0f;
    textbox->dimensions.height = TEXTBOX_HEIGHT;
};

static void update_button_position(Button* button, int i, float d)
{
    button->position.x = input_boxes[i].dimensions.width + app.S_W / d;
    button->position.y = app.S_H / 4.0f + i * (TEXTBOX_HEIGHT + app.S_H / 20.0f);
};

void draw_main_page()
{
    for (int i = 0; i < 5; i++)
    {
        //draw_textbox(input_boxes[i].dimensions, BLACK);
        draw_text(input_boxes[i].buffer, input_boxes[i].position.x, input_boxes[i].position.y, input_boxes[i].font_size);

        DrawRectangleLines((int)input_boxes[i].position.x, (int)input_boxes[i].position.y,
                (int)input_boxes[i].dimensions.width, (int)input_boxes[i].dimensions.height, input_boxes[i].mouse_on_text ? GREEN : RED);
    }
    for (int i = 0; i < 5; i++)
    {
        DrawTextureRec(check_buttons[i].texture, check_buttons[i].dimensions, check_buttons[i].position, WHITE);
    }
    for (int i = 0; i < 5; i++)
    {
        DrawTextureRec(cross_buttons[i].texture, cross_buttons[i].dimensions, cross_buttons[i].position, WHITE);
    }
    for (int i = 0; i < 5; i++)
    {
        DrawTextureRec(edit_buttons[i].texture, edit_buttons[i].dimensions, edit_buttons[i].position, WHITE);
    }
};
