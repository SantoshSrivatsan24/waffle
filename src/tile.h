#pragma once

#include "helpers.h"

typedef struct color {

    CGFloat a;
    CGFloat r;
    CGFloat g;
    CGFloat b;
} color_t;

typedef struct tile {

    int tid;
    CGPoint origin;
    CGRect frame;
    CGMutablePathRef background;
    CGMutablePathRef border;

    // Tile properties
    color_t bg_color;
    color_t bd_color;
    int border_width;
    int outer_corner_radius;
    int inner_corner_radius;
} tile_t;

color_t get_color_from_hex (uint32_t color);
void *tile_create ();
void tile_init (tile_t *tile, int tid, CGSize tile_size, uint32_t bg_color, uint32_t bd_color, int border_width, int corner_radius);
void tile_render (CGContextRef context, tile_t *tile);