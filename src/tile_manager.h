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
void tile_manager_create_tile (tile_manager_t *tile_manager, CGSize tile_size, uint32_t bg_color, uint32_t bd_color, int border_width, int corner_radius);
void tile_manager_compute_positions (CGRect base, tile_manager_t *tile_manager);
void tile_manager_render_tiles (CGContextRef context, tile_manager_t *tile_manager);
