#include "shooter.h"

#define EXPORT __declspec(dllexport)

Runtime* runtime;
std::unique_ptr<GameState> game_state;

static void FillRect(SDL_Rect rect, Color color) {
  SDL_SetRenderDrawColor(runtime->renderer, color.r, color.g, color.b, color.a);
  SDL_RenderFillRect(runtime->renderer, &rect);
}

static void DrawPlayer() {
  FillRect({(i32)game_state->player.pos.x,
            (i32)Runtime::screen_size.y - (i32)game_state->player.size.y -
                (i32)game_state->player.pos.y,
            (i32)game_state->player.size.x, (i32)game_state->player.size.y},
           White);
}

static void HandleEvents() {
  SDL_Event event;
  auto player = &game_state->player;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT: {
        runtime->quit = true;
        break;
      }
      case SDL_KEYDOWN: {
        switch (event.key.keysym.sym) {
          case SDLK_UP: {
            if (player->velocity.y == 0.f)
              player->velocity.y = World::velocity * Player::boost;
            break;
          }
          case SDLK_LEFT: {
            player->velocity.x = -World::velocity;
            break;
          }
          case SDLK_RIGHT: {
            player->velocity.x = World::velocity;
            break;
          }
          case SDLK_SPACE: {
            if (player->velocity.y == 0.f)
              player->velocity.y = World::velocity * Player::boost;
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
            if (player->velocity.y < 0.f) {
              player->velocity.y = 0.f;
            }
            break;
          }
          case SDLK_LEFT: {
            if (player->velocity.x < 0.f) {
              player->velocity.x = 0.f;
            }
            break;
          }
          case SDLK_RIGHT: {
            if (player->velocity.x > 0.f) {
              player->velocity.x = 0.f;
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

  player->pos.x += player->velocity.x;
  player->pos.y += player->velocity.y;

  if (player->velocity.y > 0.f) {
    player->velocity.y -= World::gravity;
  }
}

static void PrintPlayerState() {
  auto player = &game_state->player;
  std::cout << "Position: " << player->pos.x << ", " << player->pos.y << '\n';

  std::cout << "Velocity: " << player->velocity.x << ", " << player->velocity.y
            << '\n';

  std::cout << std::endl;
}

extern "C" {
EXPORT void SetRuntime(Runtime* runtime_) {
  runtime = runtime_;
  game_state = std::make_unique<GameState>();
}
EXPORT void Update(void) {
  HandleEvents();
  PrintPlayerState();
  DrawPlayer();
}
}
