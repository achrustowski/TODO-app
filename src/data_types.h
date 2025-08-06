#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#include <stdbool.h>

typedef struct Item Item;

typedef enum
{
    WORK,
    HOME,
    HOBBY
} Category;

struct Item
{
    bool        is_completed;
    bool        in_progress;
    char        date_added[10];
    char        summary[60];
    Category    category;
    Item*       prev;
    Item*       next;
};

typedef struct
{
    char        label[20];
    bool        is_active;
} Button;

#endif
