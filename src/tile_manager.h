#pragma once

#include "helpers.h"
#include "tile.h"

// Keep track of all tiles that have been created
typedef struct tile_manager {

    tile_t **tiles;
    int tile_count;
} tile_manager_t;

void *tile_manager_create ();
void tile_manager_destroy (tile_manager_t *tile_manager);
int tile_manager_create_tile (tile_manager_t *tile_manager, CGSize tile_size, position_t position, uint32_t bg_color, uint32_t bd_color, int padding, int border_width, int corner_radius);
void tile_manager_order_tiles (tile_manager_t *tile_manager, CGRect base);
void tile_manager_center_tiles (tile_manager_t *tile_manager, CGRect base);
void tile_manager_render_tiles (CGContextRef context, tile_manager_t *tile_manager);
