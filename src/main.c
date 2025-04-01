#include <stdio.h>
#include <stdbool.h>
#include <SDL3/SDL.h>

// Window dimensions
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define APP_NAME "Border Detection"

// Function prototypes
bool initialize_sdl(SDL_Window** window, SDL_Renderer** renderer);
void cleanup(SDL_Window* window, SDL_Renderer* renderer);
void process_image(SDL_Surface* surface, SDL_Surface* result);
SDL_Surface* detect_edges(SDL_Surface* surface);

int main(int argc, char* argv[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Surface* image = NULL;
    SDL_Surface* processed_image = NULL;
    SDL_Texture* texture = NULL;
    bool quit = false;
    SDL_Event event;

    // Initialize SDL
    if (!initialize_sdl(&window, &renderer)) {
        return 1;
    }

    // Load an image if provided as command line argument
    if (argc > 1) {
        image = SDL_LoadBMP(argv[1]);
        if (!image) {
            fprintf(stderr, "Unable to load image: %s\n", SDL_GetError());
            cleanup(window, renderer);
            return 1;
        }

        // Process the image to detect borders
        processed_image = detect_edges(image);
        if (!processed_image) {
            fprintf(stderr, "Failed to process image\n");
            SDL_DestroySurface(image);
            cleanup(window, renderer);
            return 1;
        }

        // Create texture from the processed image
        texture = SDL_CreateTextureFromSurface(renderer, processed_image);
        if (!texture) {
            fprintf(stderr, "Unable to create texture: %s\n", SDL_GetError());
            SDL_DestroySurface(processed_image);
            SDL_DestroySurface(image);
            cleanup(window, renderer);
            return 1;
        }
    }

    // Main loop
    while (!quit) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            } else if (event.type == SDL_EVENT_KEY_DOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    quit = true;
                }
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Render the processed image if available
        if (texture) {
            SDL_FRect dest = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
            SDL_RenderTextureRotated(renderer, texture, NULL, &dest, 0, NULL, SDL_FLIP_NONE);
        }

        // Update screen
        SDL_RenderPresent(renderer);
    }

    // Cleanup
    if (texture) SDL_DestroyTexture(texture);
    if (processed_image) SDL_DestroySurface(processed_image);
    if (image) SDL_DestroySurface(image);
    cleanup(window, renderer);

    return 0;
}

bool initialize_sdl(SDL_Window** window, SDL_Renderer** renderer) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // Create window
    *window = SDL_CreateWindow(APP_NAME, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!*window) {
        fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return false;
    }

    // Create renderer
    *renderer = SDL_CreateRenderer(*window, NULL, SDL_RENDERER_ACCELERATED);
    if (!*renderer) {
        fprintf(stderr, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return false;
    }

    return true;
}

void cleanup(SDL_Window* window, SDL_Renderer* renderer) {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}