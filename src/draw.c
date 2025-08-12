#include "draw.h"
#include "raylib.h"

void draw_textbox(Rectangle textbox, Color color)
{
    DrawRectangleRec(textbox, color);
};

Texture2D load_texture(const char *filename)
{
    Image image = LoadImage(filename);
    //ImageResizeNN(&image, image.width * scale, image.height * scale);
    Texture2D texture = LoadTextureFromImage(image);
    UnloadImage(image);

    return texture;
};
