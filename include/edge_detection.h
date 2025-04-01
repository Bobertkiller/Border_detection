#ifndef EDGE_DETECTION_H
#define EDGE_DETECTION_H

#include <SDL3/SDL.h>

// Get pixel value from surface
Uint32 get_pixel(SDL_Surface* surface, int x, int y);

// Set pixel value on surface
void set_pixel(SDL_Surface* surface, int x, int y, Uint32 pixel);

// Convert RGB to grayscale
Uint8 rgb_to_grayscale(Uint8 r, Uint8 g, Uint8 b);

// Apply the Sobel operator for edge detection
SDL_Surface* detect_edges(SDL_Surface* surface);

#endif // EDGE_DETECTION_H