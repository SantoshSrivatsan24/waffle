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

int tile_manager_create_tile (tile_manager_t *tile_manager, CGSize tile_size, position_t position, uint32_t bg_color, uint32_t bd_color, int border_width, int corner_radius) {

    // Create a new tile
    tile_t *tile = tile_create ();

    // Initialize tile
    int tid = tile_manager->tile_count;
    tile_init (tile, tid, tile_size, position, bg_color, bd_color, border_width, corner_radius);

    // Increase capacity by 1
    tile_manager->tiles = (tile_t **) realloc (tile_manager->tiles, sizeof(tile_t *) * (tile_manager->tile_count + 1));
    tile_manager->tiles[tile_manager->tile_count] = tile;
    tile_manager->tile_count += 1;

    return tid;
}

void tile_manager_order_tiles (tile_manager_t *tile_manager, CGRect base) {

    // Go over each tile one by one. Adjust its frame based on its position
    tile_manager->tiles[0]->frame.origin.x = base.origin.x;
    tile_manager->tiles[0]->frame.origin.y = CGRectGetMaxY(base) - tile_manager->tiles[0]->frame.size.height;

    for (int i = 1; i < tile_manager->tile_count; i++) {

        enum position relative_position = tile_manager->tiles[i]->position.relative_position;
        int relative_tid = tile_manager->tiles[i]->position.relative_tid;

        tile_t *current_tile    = tile_manager->tiles[i];
        tile_t *relative_tile   = tile_manager->tiles[relative_tid];

        CGPoint origin;

        switch (relative_position) {
            case POSITION_LEFT:     origin.x = relative_tile->frame.origin.x - current_tile->frame.size.width;
                                    if (relative_tile->frame.size.height > current_tile->frame.size.height) {
                                        int height_difference = relative_tile->frame.size.height - current_tile->frame.size.height;
                                        origin.y = relative_tile->frame.origin.y + height_difference;
                                    } else {
                                        int height_difference = current_tile->frame.size.height - relative_tile->frame.size.height;
                                        origin.y = relative_tile->frame.origin.y - height_difference;
                                    }
                                    break;

            case POSITION_RIGHT:    origin.x = relative_tile->frame.origin.x + relative_tile->frame.size.width;
                                    if (relative_tile->frame.size.height > current_tile->frame.size.height) {
                                        int height_difference = relative_tile->frame.size.height - current_tile->frame.size.height;
                                        origin.y = relative_tile->frame.origin.y + height_difference;
                                    } else {
                                        int height_difference = current_tile->frame.size.height - relative_tile->frame.size.height;
                                        origin.y = relative_tile->frame.origin.y - height_difference;
                                    }
                                    break;

            case POSITION_BELOW:    origin.x = relative_tile->frame.origin.x;
                                    origin.y = relative_tile->frame.origin.y - current_tile->frame.size.height;
                                    break;

            case POSITION_ABOVE:    origin.x = relative_tile->frame.origin.x;
                                    origin.y = relative_tile->frame.origin.y + relative_tile->frame.size.height + current_tile->frame.size.height;
                                    break;
        }

        tile_manager->tiles[i]->frame.origin = origin;
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

void tile_manager_render_tiles (CGContextRef context, tile_manager_t *tile_manager) {

    for (int i = 0; i < tile_manager->tile_count; i++) {
        tile_render (context, tile_manager->tiles[i]);
    }
}






