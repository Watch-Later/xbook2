#include "xtk_button.h"
#include <stdlib.h>
#include <assert.h>

xtk_spirit_t *xtk_button_create()
{
    xtk_button_t *button = malloc(sizeof(xtk_button_t));
    if (!button)
        return NULL;
    button->state = XTK_BUTTON_IDLE;
    button->color_idle = UVIEW_WHITE;
    button->color_touch = UVIEW_RED;
    button->color_click = UVIEW_BLUE;
    
    xtk_spirit_t *spirit = &button->spirit;
    xtk_spirit_init(spirit, 0, 0, XTK_BUTTON_WIDTH_DEFAULT, XTK_BUTTON_HEIGHT_DEFAULT);
    xtk_spirit_set_type(spirit, XTK_SPIRIT_TYPE_BUTTON);
    
    spirit->style.border_color = UVIEW_GRAY;
    spirit->style.background_color = button->color_idle;
    spirit->style.color = UVIEW_BLACK;
    spirit->style.align = XTK_ALIGN_CENTER;
    return spirit;
}

xtk_spirit_t *xtk_button_create_with_label(const char *label)
{
    xtk_spirit_t *spirit = xtk_button_create();
    if (!spirit)
        return NULL;
    if (xtk_spirit_set_text(spirit, label) < 0) {
        xtk_spirit_destroy(spirit);
        return NULL;
    }
    return spirit;
}

void xtk_button_change_state(xtk_button_t *button, xtk_button_state_t state)
{
    if (button->state == state)
        return;
    xtk_spirit_t *spirit = &button->spirit;
    button->state = state;
    switch (state) {
    case XTK_BUTTON_IDLE:    
        spirit->style.background_color = button->color_idle;
        break;
    case XTK_BUTTON_TOUCH:    
        spirit->style.background_color = button->color_touch;
        break;
    case XTK_BUTTON_CLICK:    
        spirit->style.background_color = button->color_click;
        break;
    default:
        break;
    }
}