#include <iostream>
#include <vector>
#include "artGallery.hpp"
#include "graph.hpp"
#include <SDL2/SDL.h>

using std::vector;
using std::cout;

void defineGallery(vector<Edge> &edges);

int main(int argc, char* argv[]) {
  vector<Edge> edges;
  defineGallery(edges);
  Graph ag(edges);
  cout << ag;

  if (SDL_Init(SDL_INIT_VIDEO) == 0) {
      SDL_Window* window = NULL;
      SDL_Renderer* renderer = NULL;

      if (SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer) == 0) {
          SDL_bool done = SDL_FALSE;

          while (!done) {
              SDL_Event event;

              SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
              SDL_RenderClear(renderer);

              SDL_SetRenderDrawColor(renderer, 10, 155, 255, SDL_ALPHA_OPAQUE);
              SDL_RenderDrawLine(renderer, 100, 100, 200, 400);
              SDL_RenderDrawLine(renderer, 200, 400, 300, 200);
              SDL_RenderDrawLine(renderer, 400, 200, 500, 400);
              SDL_RenderDrawLine(renderer, 500, 400, 600, 100);
              SDL_RenderDrawLine(renderer, 300, 200, 400, 200);
              SDL_RenderDrawLine(renderer, 600, 100, 100, 100);
              SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
              SDL_RenderDrawLine(renderer, 300, 200, 100, 100);
              SDL_RenderDrawLine(renderer, 400, 200, 100, 100);
              SDL_RenderDrawLine(renderer, 600, 100, 400, 200);
              SDL_RenderPresent(renderer);

              while (SDL_PollEvent(&event)) {
                  if (event.type == SDL_QUIT) {
                      done = SDL_TRUE;
                  }
              }
          }
      }

      if (renderer) {
          SDL_DestroyRenderer(renderer);
      }
      if (window) {
          SDL_DestroyWindow(window);
      }
  }
  SDL_Quit();



  return 0;
}

void defineGallery(vector<Edge> &edges) {
  edges.push_back(
    Edge {
      Point {1, 1},
      Point {2, 4}
    }
  );
  edges.push_back(
    Edge {
      Point {2, 4},
      Point {3, 2}
    }
  );
  edges.push_back(
    Edge {
      Point {3, 2},
      Point {4, 2}
    }
  );
  edges.push_back(
    Edge {
      Point {4, 2},
      Point {5, 4}
    }
  );
  edges.push_back(
    Edge {
      Point {5, 4},
      Point {6, 1}
    }
  );
  edges.push_back(
    Edge {
      Point {6, 1},
      Point {1, 1}
    }
  );

  return;
}
