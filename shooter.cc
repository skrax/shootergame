#include "shooter.h"
#include "runtime.h"

#define EXPORT __declspec(dllexport)

Runtime* runtime;
std::unique_ptr<GameState> game_state;

static void FillRect(SDL_Rect rect, Color color) {
  SDL_SetRenderDrawColor(runtime->renderer, color.r, color.g, color.b, color.a);
  SDL_RenderFillRect(runtime->renderer, &rect);
}

static void DrawPlayer(v2 pos) {
  FillRect({(i32)pos.x, (i32)pos.y, 40, 60}, White);
}

static void HandleEvents() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT: {
        runtime->quit = true;
        break;
      }
      case SDL_KEYDOWN: {
        switch (event.key.keysym.sym) {
          case SDLK_UP: {
            game_state->player_velocity.y = -1.f;
            break;
          }
          case SDLK_DOWN: {
            game_state->player_velocity.y = 1.f;
            break;
          }
          case SDLK_LEFT: {
            game_state->player_velocity.x = -1.f;
            break;
          }
          case SDLK_RIGHT: {
            game_state->player_velocity.x = 1.f;
            break;
          }
          default: {
            break;
          }
        }
        break;
      }
      case SDL_KEYUP: {
        switch (event.key.keysym.sym) {
          case SDLK_UP: {
            if (game_state->player_velocity.y < 0.f) {
              game_state->player_velocity.y = 0.f;
            }
            break;
          }
          case SDLK_DOWN: {
            if (game_state->player_velocity.y > 0.f) {
              game_state->player_velocity.y = 0.f;
            }
            break;
          }
          case SDLK_LEFT: {
            if (game_state->player_velocity.x < 0.f) {
              game_state->player_velocity.x = 0.f;
            }
            break;
          }
          case SDLK_RIGHT: {
            if (game_state->player_velocity.x > 0.f) {
              game_state->player_velocity.x = 0.f;
            }
            break;
          }
          default: {
            break;
          }
        }
        break;
      }
    }
  }
  game_state->player_pos.x += game_state->player_velocity.x;
  game_state->player_pos.y += game_state->player_velocity.y;
}

extern "C" {
EXPORT void SetRuntime(Runtime* runtime_) {
  runtime = runtime_;
  game_state = std::make_unique<GameState>();
}
EXPORT void Update(void) {
  HandleEvents();
  DrawPlayer(game_state->player_pos);
}
}
