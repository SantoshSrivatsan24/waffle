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

void tile_init (tile_t *tile, int tid, CGSize tile_size, position_t position, uint32_t bg_color, uint32_t bd_color, int padding, int border_width, int corner_radius) {

    tile->tid = tid;
    // `tile->frame.origin` is calculated by the tile_manager
    tile->frame.size = tile_size;
    tile->position = position;

    tile->background.path = CGPathCreateMutable();
    tile->background.color = get_color_from_hex (bg_color);
    tile->background.corner_radius = corner_radius - border_width;
    tile->background.padding = padding;

    tile->border.path = CGPathCreateMutable();
    tile->border.color = get_color_from_hex (bd_color);
    tile->border.corner_radius = corner_radius;
    tile->border.border_width = border_width;
}

void tile_render (CGContextRef context, tile_t *tile) {

    int padding = tile->background.padding + tile->border.border_width;
    tile->background.frame = CGRectInset (tile->frame, padding, padding);
    CGPathAddRoundedRect(tile->background.path, NULL, tile->background.frame, tile->background.corner_radius, tile->background.corner_radius);
    CGContextAddPath(context, tile->background.path);
    CGContextSetRGBFillColor(context, tile->background.color.r, tile->background.color.g, tile->background.color.b, tile->background.color.a);
    CGContextFillPath(context);

    tile->border.frame = tile->background.frame;
    CGPathAddRoundedRect(tile->border.path, NULL, tile->border.frame, tile->border.corner_radius, tile->border.corner_radius);    
    CGContextAddPath(context, tile->border.path);
    CGContextSetRGBStrokeColor(context, tile->border.color.r, tile->border.color.g, tile->border.color.b, tile->border.color.a);
    CGContextSetLineWidth(context, tile->border.border_width);
    CGContextStrokePath(context);
}


