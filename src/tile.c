#include "tile.h"

static color_t get_color_from_hex (uint32_t color) {

    color_t argb;
    argb.a = ((color >> 0x18) & 0xff) / 255.0f;
    argb.r = ((color >> 0x10) & 0xff) / 255.0f;
    argb.g = ((color >> 0x08) & 0xff) / 255.0f;
    argb.b = ((color >> 0x00) & 0xff) / 255.0f;
    return argb;
}

void *tile_create () {

    tile_t *tile = (tile_t *) malloc (sizeof(tile_t));
    memset (tile, 0, sizeof(tile_t));
    return tile;
}

void tile_init (tile_t *tile, int tid, CGSize tile_size, position_t position, uint32_t bg_color, uint32_t bd_color, int border_width, int corner_radius) {

    tile->tid = tid;
    // `tile->frame` is calculated by the tile_manager
    tile->frame.size = tile_size;
    tile->position = position;
    tile->background = CGPathCreateMutable();
    tile->border = CGPathCreateMutable();
    tile->bg_color = get_color_from_hex(bg_color);
    tile->bd_color = get_color_from_hex(bd_color);
    tile->border_width = border_width;
    tile->outer_corner_radius = corner_radius;
    tile->inner_corner_radius = corner_radius - border_width;
}

void tile_render (CGContextRef context, tile_t *tile) {

    printf("Tile origin (x, y): (%f, %f), size (w, h): (%f, %f)\n", tile->frame.origin.x, tile->frame.origin.y, tile->frame.size.width, tile->frame.size.height);

    CGPathAddRoundedRect(tile->background, NULL, tile->frame, tile->inner_corner_radius, tile->inner_corner_radius);
    CGContextAddPath(context, tile->background);
    CGContextSetRGBFillColor(context, tile->bg_color.r, tile->bg_color.g, tile->bg_color.b, tile->bg_color.a);
    CGContextFillPath(context);

    CGPathAddRoundedRect(tile->border, NULL, tile->frame, tile->outer_corner_radius, tile->outer_corner_radius);    
    CGContextAddPath(context, tile->border);
    CGContextSetRGBStrokeColor(context, tile->bd_color.r, tile->bd_color.g, tile->bd_color.b, tile->bd_color.a);
    CGContextSetLineWidth(context, tile->border_width);
    CGContextStrokePath(context);
}

