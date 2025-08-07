#include <raylib.h>
#include "init.h"
#include "structs.h"
#include "string.h"

extern Gui gui;

void init_fonts()
{
    gui.font = LoadFont("./fonts/TerminessNerdFont-Bold.ttf");
    gui.font_size = 18;
};

void init_gui()
{
    memset(&gui, 0, sizeof(Gui));
};
