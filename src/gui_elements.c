#include <raygui.h>
#include "gui_elements.h"
#include "defs.h"
#include "draw.h"
#include "enums.h"
#include "raylib.h"
#include "structs.h"
#include <string.h>
#include <stdio.h>

extern App app;
extern Gui gui;

static Item     list_items[5];

static Textbox add_new_item_textbox(float y);
static Button add_new_button(float x, float y, float w, float h, char* filename, int btn_type);
static void textbox_interact(Textbox* textbox);
static void buttons_interact(Button* button, int i);
static void draw_text(char* text, int x, int y, int font_size);
static void update_textbox_position(Textbox* textbox, int i);
static void update_button_position(Button* button, int i, float d);

void gui_elements_logic()
{
    for (int i = 0; i < 5; i++)
    {
        textbox_interact(&list_items[i].textbox);
        update_textbox_position(&list_items[i].textbox, i);
        buttons_interact(&list_items[i].check_btn, i);
        buttons_interact(&list_items[i].cross_btn, i);
        buttons_interact(&list_items[i].edit_btn, i);
        update_button_position(&list_items[i].check_btn, i, 6.0f);
        update_button_position(&list_items[i].cross_btn, i, 4.0f);
        update_button_position(&list_items[i].edit_btn, i, 3.0f);
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

static void buttons_interact(Button* button, int i)
{
    if (CheckCollisionPointRec(GetMousePosition(),
                (Rectangle){button->position.x, button->position.y, button->dimensions.width, button->dimensions.height}))
    {
        button->is_hovered = true;
    } else
    {
        button->is_hovered = false;
    }
    if (button->is_hovered)
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
        list_items[i].textbox = add_new_item_textbox(app.S_H / 4.0f + i * (TEXTBOX_HEIGHT + app.S_H / 20.0f));
        list_items[i].check_btn = add_new_button(list_items[i].textbox.dimensions.width + app.S_W / 6.0f,
                app.S_H / 4.0f + i * (TEXTBOX_HEIGHT + app.S_H / 20.0f), 48.0f, 48.0f, "./icons/checked.png", CHECK);
        list_items[i].cross_btn = add_new_button(list_items[i].textbox.dimensions.width + app.S_W / 4.0f,
                app.S_H / 4.0f + i * (TEXTBOX_HEIGHT + app.S_H / 20.0f), 48.0f, 48.0f, "./icons/remove.png", CROSS);
        list_items[i].edit_btn = add_new_button(list_items[i].textbox.dimensions.width + app.S_W / 3.0f,
                app.S_H / 4.0f + i * (TEXTBOX_HEIGHT + app.S_H / 20.0f), 48.0f, 48.0f, "./icons/pencil.png", EDIT);
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
    textbox.color = GRAY;
    strncpy(textbox.buffer, "\0", sizeof(textbox.buffer));

    return textbox;
};

static Button add_new_button(float x, float y, float w, float h, char* filename, int btn_type)
{
    Button button;
    memset(&button, 0, sizeof(button));

    button.dimensions = (Rectangle){0.0f, 0.0f, w, h};
    button.texture = load_texture(filename);
    button.font_size = 28;
    button.is_pressed = false;
    button.is_hovered = false;
    button.btn_type = btn_type;
    button.position = (Vector2){x, y};

    return button;
}

static void update_textbox_position(Textbox* textbox, int i)
{
    textbox->position.x = (app.S_W / 4.0f - app.S_W / 6.0f);
    textbox->position.y = app.S_H / 3.5f + i * (TEXTBOX_HEIGHT + app.S_H / 20.0f);
    textbox->dimensions.width = app.S_W / 2.0f;
    textbox->dimensions.height = TEXTBOX_HEIGHT;
};

static void update_button_position(Button* button, int i, float d)
{
    button->position.x = list_items[i].textbox.dimensions.width + app.S_W / d;
    button->position.y = app.S_H / 3.5f + i * (TEXTBOX_HEIGHT + app.S_H / 20.0f);
};

void draw_main_page()
{
    for (int i = 0; i < 5; i++)
    {
        draw_text(list_items[i].textbox.buffer, list_items[i].textbox.position.x, list_items[i].textbox.position.y, list_items[i].textbox.font_size);

        DrawRectangleLines((int)list_items[i].textbox.position.x, (int)list_items[i].textbox.position.y,
                (int)list_items[i].textbox.dimensions.width, (int)list_items[i].textbox.dimensions.height, list_items[i].textbox.color);
    }
    for (int i = 0; i < 5; i++)
    {
        DrawTextureRec(list_items[i].check_btn.texture, list_items[i].check_btn.dimensions, list_items[i].check_btn.position, WHITE);
    }
    for (int i = 0; i < 5; i++)
    {
        DrawTextureRec(list_items[i].cross_btn.texture, list_items[i].cross_btn.dimensions, list_items[i].cross_btn.position, WHITE);
    }
    for (int i = 0; i < 5; i++)
    {
        DrawTextureRec(list_items[i].edit_btn.texture, list_items[i].edit_btn.dimensions, list_items[i].edit_btn.position, WHITE);
    }
};
