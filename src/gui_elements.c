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

static const int it_size = 5;
static const int btn_size = 4;

static Item list_items[it_size];

static Textbox add_new_item_textbox(float y);
static Button add_new_button(float x, float y, float w, float h, const char* filename, int btn_type);
static void textbox_interact(Textbox* textbox);
static void buttons_interact(Button buttons[]);
static void list_logic(void);
static void draw_text(char* text, int x, int y, int font_size, Color color);
static void update_textbox_position(Textbox* textbox, int i);
static void update_button_position(Button* button, int i, float d);

void gui_elements_logic()
{
    for (int i = 0; i < it_size; i++)
    {
        textbox_interact(&list_items[i].textbox);
        update_textbox_position(&list_items[i].textbox, i);
        update_button_position(&list_items[i].buttons[0], i, list_items[i].textbox.position.x + list_items[i].textbox.dimensions.width + (app.S_W / 24.0f));
        update_button_position(&list_items[i].buttons[1], i, list_items[i].textbox.position.x + list_items[i].textbox.dimensions.width + (app.S_W / 9.0f));
        update_button_position(&list_items[i].buttons[2], i, list_items[i].textbox.position.x + list_items[i].textbox.dimensions.width + (app.S_W / 5.5f));
        update_button_position(&list_items[i].buttons[3], i, list_items[i].textbox.position.x - (app.S_W / 12.0f));
        buttons_interact(list_items[i].buttons);
    }
    list_logic();
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
        //SetMouseCursor(MOUSE_CURSOR_IBEAM);
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
        //SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
};

static void buttons_interact(Button buttons[])
{
    for (int i = 0; i < btn_size; i++)
    {
        if (CheckCollisionPointRec(GetMousePosition(),
                    (Rectangle){buttons[i].position.x, buttons[i].position.y, buttons[i].dimensions.width, buttons[i].dimensions.height}))
        {
            buttons[i].is_hovered = true;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                switch (i)
                {
                    case CHECK:
                        buttons[CHECK].is_pressed = true;
                        buttons[CROSS].is_pressed = false;
                        buttons[EDIT].is_pressed = false;
                        buttons[CLEAN].is_pressed = false;
                        break;
                    case CROSS:
                        buttons[CHECK].is_pressed = false;
                        buttons[CROSS].is_pressed = true;
                        buttons[EDIT].is_pressed = false;
                        buttons[CLEAN].is_pressed = false;
                        break;
                    case EDIT:
                        buttons[CHECK].is_pressed = false;
                        buttons[CROSS].is_pressed = false;
                        buttons[EDIT].is_pressed = true;
                        buttons[CLEAN].is_pressed = false;
                        break;
                    case CLEAN:
                        buttons[CHECK].is_pressed = false;
                        buttons[CROSS].is_pressed = false;
                        buttons[EDIT].is_pressed = false;
                        buttons[CLEAN].is_pressed = true;
                        break;
                    default:
                        buttons[CHECK].is_pressed = false;
                        buttons[CROSS].is_pressed = false;
                        buttons[EDIT].is_pressed = false;
                        buttons[CLEAN].is_pressed = false;
                        break;
                }
            }
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            {
                buttons[CLEAN].is_pressed = false;
            }
        } else
        {
            buttons[i].is_hovered = false;
        }
    }
};

static void list_logic()
{
    for (int i = 0; i < it_size; i++)
    {
        if (list_items[i].buttons[CHECK].is_pressed)
        {
            list_items[i].textbox.color = GREEN;
            list_items[i].textbox.font_color = GREEN;
        }
        if (list_items[i].buttons[CROSS].is_pressed)
        {
            list_items[i].textbox.color = RED;
            list_items[i].textbox.font_color = RED;
        }
        if (list_items[i].buttons[EDIT].is_pressed)
        {
            list_items[i].textbox.color = BLUE;
            list_items[i].textbox.font_color = WHITE;
        }
        if (list_items[i].buttons[CLEAN].is_pressed)
        {
            list_items[i].textbox.color = GRAY;
            list_items[i].textbox.font_color = WHITE;
            list_items[i].textbox.letter_count = 0;
            memset(list_items[i].textbox.buffer, 0, sizeof(list_items[i].textbox.buffer));
        }
    }
};

static void draw_text(char* text, int x, int y, int font_size, Color color)
{
    //draw actuall textbox buffer onto the screen, at this point x & y padding values are constants, can they be dynamic?
    //DrawText(text, (int)x + 10, (int)y + 10, font_size, RAYWHITE);
    DrawTextEx(gui.font, text, (Vector2){(int)x + 10, (int)y + 10}, font_size, 1.0f, color);
};

void initialize_gui_elements()
{
    const char* file_names[btn_size];
    file_names[0] = "./icons/checked.png";
    file_names[1] = "./icons/remove.png";
    file_names[2] = "./icons/pencil.png";
    file_names[3] = "./icons/clean.png";

    for (int i = 0; i < it_size; i++)
    {
        list_items[i].textbox = add_new_item_textbox(app.S_H / 4.0f + i * (TEXTBOX_HEIGHT + app.S_H / 20.0f));
        for (int j = 0; j < btn_size; j++)
        {
            list_items[i].buttons[j] = add_new_button(0, 0, 48.0f, 48.0f, file_names[j], j);
        }
    }
};

static Textbox add_new_item_textbox(float y)
{
    Textbox textbox;
    memset(&textbox, 0, sizeof(textbox));

    textbox.dimensions = (Rectangle){(app.S_W / 3.0f - app.S_W / 6.0f), y, app.S_W / 2.0f, TEXTBOX_HEIGHT};
    textbox.mouse_on_text = false;
    textbox.letter_count = 0;
    textbox.font_size = 28;
    textbox.color = GRAY;
    textbox.font_color = WHITE;
    //strncpy(textbox.buffer, "\0", sizeof(textbox.buffer));

    return textbox;
};

static Button add_new_button(float x, float y, float w, float h, const char* filename, int btn_type)
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
    textbox->position.x = (app.S_W / 3.0f - app.S_W / 6.0f);
    textbox->position.y = app.S_H / 3.5f + i * (TEXTBOX_HEIGHT + app.S_H / 20.0f);
    textbox->dimensions.width = app.S_W / 2.0f;
    textbox->dimensions.height = TEXTBOX_HEIGHT;
};

static void update_button_position(Button* button, int j, float d)
{
    button->position.x = d;
    button->position.y = app.S_H / 3.5f + j * (TEXTBOX_HEIGHT + app.S_H / 20.0f);
};

void draw_main_page()
{
    for (int i = 0; i < it_size; i++)
    {
        draw_text(list_items[i].textbox.buffer, list_items[i].textbox.position.x,
                list_items[i].textbox.position.y, list_items[i].textbox.font_size, list_items[i].textbox.font_color);

        DrawRectangleLines((int)list_items[i].textbox.position.x, (int)list_items[i].textbox.position.y,
                (int)list_items[i].textbox.dimensions.width, (int)list_items[i].textbox.dimensions.height, list_items[i].textbox.color);
        for (int j = 0; j < btn_size; j++)
        {
            DrawTextureRec(list_items[i].buttons[j].texture, list_items[i].buttons[j].dimensions, list_items[i].buttons[j].position, WHITE);

        }
    }
    draw_text(app.title, app.S_W / 2.1, app.S_H / 10, 30, WHITE);
    DrawTextureRec(app.icon, (Rectangle){0.0f, 0.0f, 64.0f, 64.0f}, (Vector2){app.S_W / 2.3, app.S_H / 11.0f}, WHITE);
};
