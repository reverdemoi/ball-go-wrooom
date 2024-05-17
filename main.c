#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool init() {
  bool success = true;
  
  if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
    printf("Failed to initialize %s\n", SDL_GetError());
    success = false;
  } else {
    window = SDL_CreateWindow( "My moving ball", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

    if ( window == NULL ) {
      printf("Failed to create window, %s\n", SDL_GetError()); 
      success = false;
    } else {
      renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
      
      if ( renderer == NULL ) {
        printf("Failed to create renderer, %s\n", SDL_GetError());
        success = false;
      } else {
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
      }
    }
  }

  return success;
}

void closeApp() {
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);

  SDL_Quit();
}

int main(int argc, char *argv[]) {
  bool quit = false;

  SDL_Event e;

  SDL_Rect fillRect = {SCREEN_WIDTH / 2 - 5, SCREEN_HEIGHT / 2 - 5, 10, 10};
  if (!init()) {
    printf("Failed to initialize");
  } else {
    while (!quit) {

      while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
          quit = true;
        }

        if (e.type == SDL_KEYDOWN) {
          switch (e.key.keysym.sym) {
            case SDLK_UP:
              fillRect.y--;
              break;

            case SDLK_DOWN:
              fillRect.y++;
              break;

            case SDLK_LEFT:
              fillRect.x--;
              break;

            case SDLK_RIGHT:
              fillRect.x++;
              break;
          }
        }
      }

      SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
      SDL_RenderClear(renderer);

      SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
      SDL_RenderFillRect(renderer, &fillRect);

      SDL_RenderPresent(renderer);
    }
  }

  closeApp();

  return 0;
}