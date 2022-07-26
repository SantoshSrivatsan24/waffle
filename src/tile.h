#pragma once

#include "helpers.h"
#include "window.h"

typedef struct color
{
    CGFloat a;
    CGFloat r;
    CGFloat g;
    CGFloat b;
} color_t;

typedef struct tile 
{
    CGRect frame;
    CGMutablePathRef background;
    CGMutablePathRef border;
    color_t bg_color;
    color_t bd_color;
    int border_width;
    int outer_corner_radius;
    int inner_corner_radius;
} tile_t;

color_t get_color_from_hex (uint32_t color);
void tile_init (tile_t *tile, CGRect frame, uint32_t bg_color, uint32_t bd_color, int border_width, int corner_radius);
void tile_render (window_t *window, tile_t *tile);