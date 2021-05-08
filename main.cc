#define SDL_MAIN_HANDLED
#include "shooter.h"
SDL_Renderer* renderer;
SDL_Window* window;
GameState* game_state;

static void FillRect(SDL_Rect rect, Color color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_RenderFillRect(renderer, &rect);
}

static void Clear() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderFillRect(renderer, nullptr);
}
static void Flush() {
  SDL_RenderPresent(renderer);
}

static void DrawPlayer(v2 pos) {
  FillRect({(i32)pos.x, (i32)pos.y, 40, 60}, White);
}

static void HandleEvents() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT: {
        game_state->quit = true;
        break;
      }
      case SDL_KEYDOWN: {
        switch (event.key.keysym.sym) {
          case SDLK_UP: {
            --game_state->player_pos.y;
            break;
          }
          case SDLK_DOWN: {
            ++game_state->player_pos.y;
            break;
          }
          case SDLK_LEFT: {
            --game_state->player_pos.x;
            break;
          }
          case SDLK_RIGHT: {
            ++game_state->player_pos.x;
            break;
          }
        }
      }
    }
  }
}

static void WaitRemainingFrameTime() {
  const auto frame_time = SDL_GetTicks() - game_state->frame_start;
  SDL_Delay(std::max(frame_time, refresh_rate) - frame_time);
}

int main(int argc, char* argv[]) {
  SDL_SetMainReady();

  SDL_Init(SDL_INIT_VIDEO);
  window = SDL_CreateWindow("Shooter", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,  //
                            screen_size.x, screen_size.y, 0);
  renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);

  Clear();
  Flush();

  while (!game_state->quit) {
    game_state->frame_start = SDL_GetTicks();

    Clear();
    HandleEvents();

    DrawPlayer(game_state->player_pos);

    WaitRemainingFrameTime();
    Flush();
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
