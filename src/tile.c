#include "tile.h"

color_t get_color_from_hex (uint32_t color) {

    color_t argb;
    argb.a = ((color >> 0x18) & 0xff) / 255.0f;
    argb.r = ((color >> 0x10) & 0xff) / 255.0f;
    argb.g = ((color >> 0x08) & 0xff) / 255.0f;
    argb.b = ((color >> 0x00) & 0xff) / 255.0f;
    return argb;
}

void tile_init (tile_t *tile, CGRect frame, uint32_t bg_color, uint32_t bd_color, int border_width, int corner_radius) {

    tile->frame = CGRectInset(frame, border_width / 2, border_width / 2);
    tile->background = CGPathCreateMutable();
    tile->border = CGPathCreateMutable();
    tile->bg_color = get_color_from_hex(bg_color);
    tile->bd_color = get_color_from_hex(bd_color);
    tile->border_width = border_width;
    tile->outer_corner_radius = corner_radius;
    tile->inner_corner_radius = corner_radius - border_width;

    CGPathAddRoundedRect(tile->background, NULL, tile->frame, tile->inner_corner_radius, tile->inner_corner_radius);
    CGPathAddRoundedRect(tile->border, NULL, tile->frame, tile->outer_corner_radius, tile->outer_corner_radius);    
}

void tile_render (window_t *window, tile_t *tile) {

    CGContextAddPath(window->context, tile->background);
    CGContextSetRGBFillColor(window->context, tile->bg_color.r, tile->bg_color.g, tile->bg_color.b, tile->bg_color.a);
    CGContextFillPath(window->context);

    CGContextAddPath(window->context, tile->border);
    CGContextSetRGBStrokeColor(window->context, tile->bd_color.r, tile->bd_color.g, tile->bd_color.b, tile->bd_color.a);
    CGContextSetLineWidth(window->context, tile->border_width);
    CGContextStrokePath(window->context);
}