// Manage the layout of tiles on screen

#include "tile_manager.h"
#include "stdio.h"

// static void tile_manager_compute_origin (window_t *window, tile_manager_t *tile_manager);

void *tile_manager_create () {

    tile_manager_t *tile_manager = (tile_manager_t *) malloc (sizeof(tile_manager_t));
    tile_manager->tiles = (tile_t **) malloc (sizeof(tile_t *));
    memset (tile_manager, 0, sizeof(tile_manager_t));
    return tile_manager;
}

void tile_manager_destroy (tile_manager_t *tile_manager) {

    free (tile_manager->tiles);
    free (tile_manager);
}

void tile_manager_create_tile (tile_manager_t *tile_manager, CGSize tile_size, uint32_t bg_color, uint32_t bd_color, int border_width, int corner_radius) {

    // Create a new tile
    tile_t *tile = tile_create ();

    // Initialize tile
    tile_init(tile, tile_manager->tile_count + 1, tile_size, bg_color, bd_color, border_width, corner_radius);

    // Increase capacity by 1
    tile_manager->tiles = (tile_t **) realloc (tile_manager->tiles, sizeof(tile_t *) * (tile_manager->tile_count + 1));
    tile_manager->tiles[tile_manager->tile_count] = tile;
    tile_manager->tile_count += 1;
}

void tile_manager_render_tiles (CGContextRef context, tile_manager_t *tile_manager) {

    for (int i = 0; i < tile_manager->tile_count; i++) {
        tile_render (context, tile_manager->tiles[i]);
    }
}

void tile_manager_compute_positions (CGRect base, tile_manager_t *tile_manager) {

    CGFloat total_width = base.size.width;
    CGFloat occupied_width = 0.0f;

    for (int i = 0; i < tile_manager->tile_count; i++) {
        occupied_width += tile_manager->tiles[i]->frame.size.width;
    }

    CGFloat gap_width = (total_width - occupied_width) / 2;
    CGFloat x = total_width - gap_width;
    CGFloat y;

    for (int i = tile_manager->tile_count - 1; i >= 0; i--) {
        x -= tile_manager->tiles[i]->frame.size.width;
        y = base.size.height - tile_manager->tiles[i]->frame.size.height;
        tile_manager->tiles[i]->frame.origin.x = x;
        tile_manager->tiles[i]->frame.origin.y = y;
    }
}




