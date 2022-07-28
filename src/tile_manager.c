// Manage the layout of tiles on screen

#include "tile_manager.h"

static CGFloat get_tile_x (tile_t *tile);
static CGFloat get_tile_y (tile_t *tile);
static CGFloat get_tile_w (tile_t *tile);
static CGFloat get_tile_h (tile_t *tile);

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

int tile_manager_create_tile (tile_manager_t *tile_manager, CGSize tile_size, position_t position, uint32_t bg_color, uint32_t bd_color, int padding, int border_width, int corner_radius) {

    tile_t *tile = tile_create ();
    int tid = tile_manager->tile_count;
    tile_init (tile, tid, tile_size, position, bg_color, bd_color, padding, border_width, corner_radius);

    tile_manager->tiles = (tile_t **) realloc (tile_manager->tiles, sizeof(tile_t *) * (tile_manager->tile_count + 1));
    tile_manager->tiles[tile_manager->tile_count] = tile;
    tile_manager->tile_count += 1;

    return tid;
}

// Go over each tile one by one. Adjust its frame based on its position
void tile_manager_order_tiles (tile_manager_t *tile_manager, CGRect base) {

    // The first tile is positioned on the parent's top left corner
    tile_manager->tiles[0]->frame.origin.x = base.origin.x;
    tile_manager->tiles[0]->frame.origin.y = CGRectGetMaxY(base) - tile_manager->tiles[0]->frame.size.height;

    for (int i = 1; i < tile_manager->tile_count; i++) {

        tile_t *current_tile  = tile_manager->tiles[i];
        enum position relative_position = current_tile->position.relative_position;
        int relative_tid = current_tile->position.relative_tid;
        tile_t *relative_tile = tile_manager->tiles[relative_tid];
        CGPoint origin;

        switch (relative_position) {
            case POSITION_LEFT:     origin.x = get_tile_x (relative_tile) - get_tile_w (current_tile);
                                    origin.y = get_tile_y (relative_tile) - (get_tile_h (current_tile) - get_tile_h (relative_tile));
                                    break;

            case POSITION_RIGHT:    origin.x = get_tile_x (relative_tile) + get_tile_w (relative_tile);
                                    origin.y = get_tile_y (relative_tile) - (get_tile_h (current_tile) - get_tile_h (relative_tile));
                                    break;

            case POSITION_BELOW:    origin.x = get_tile_x (relative_tile);
                                    origin.y = get_tile_y (relative_tile) - get_tile_h (current_tile);
                                    break;

            case POSITION_ABOVE:    origin.x = get_tile_x (relative_tile);
                                    origin.y = get_tile_y (relative_tile) + get_tile_h (relative_tile);
                                    break;
        }
        tile_manager->tiles[i]->frame.origin = origin;
    }
}


void tile_manager_center_tiles (tile_manager_t *tile_manager, CGRect base) {

    CGFloat total_width = base.size.width;
    CGFloat occupied_width = 0.0f;

    for (int i = 0; i < tile_manager->tile_count; i++) {

        tile_t *tile = tile_manager->tiles[i];
        if (get_tile_y (tile) + get_tile_h (tile) == CGRectGetMaxY(base))
            occupied_width += get_tile_w (tile);
    }

    CGFloat shift_x = (total_width - occupied_width) / 2;

    for (int i = 0; i < tile_manager->tile_count; i++) {
        tile_manager->tiles[i]->frame.origin.x += shift_x;
    }
}

void tile_manager_render_tiles (CGContextRef context, tile_manager_t *tile_manager) {

    for (int i = 0; i < tile_manager->tile_count; i++) {
        tile_render (context, tile_manager->tiles[i]);
    }
}

static CGFloat get_tile_x (tile_t *tile) {
    return tile->frame.origin.x;
}

static CGFloat get_tile_y (tile_t *tile) {
    return tile->frame.origin.y;
}

static CGFloat get_tile_w (tile_t *tile) {
    return tile->frame.size.width;
}

static CGFloat get_tile_h (tile_t *tile) {
    return tile->frame.size.height;
}





