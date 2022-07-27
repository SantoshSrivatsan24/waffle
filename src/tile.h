#pragma once

#include "helpers.h"

enum position {

    POSITION_LEFT,
    POSITION_RIGHT,
    POSITION_ABOVE,
    POSITION_BELOW
};

typedef struct {

    enum position relative_position;
    int relative_tid;
} position_t;

typedef struct {

    CGFloat a;
    CGFloat r;
    CGFloat g;
    CGFloat b;
} color_t;

typedef struct {

    int tid;
    CGRect frame;
    position_t position;
    CGMutablePathRef background;
    CGMutablePathRef border;

    // Tile properties
    color_t bg_color;
    color_t bd_color;
    int border_width;
    int outer_corner_radius;
    int inner_corner_radius;
} tile_t;

void *tile_create ();
void tile_init (tile_t *tile, int tid, CGSize tile_size, position_t position, uint32_t bg_color, uint32_t bd_color, int border_width, int corner_radius);
void tile_render (CGContextRef context, tile_t *tile);