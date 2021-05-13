#include "shooter.h"

#define EXPORT __declspec(dllexport)

Runtime* runtime;
std::unique_ptr<GameState> game_state;

static void DrawRect(SDL_Rect rect, Color color, bool fill) {
  SDL_SetRenderDrawColor(runtime->renderer, color.r, color.g, color.b, color.a);
  fill ? SDL_RenderFillRect(runtime->renderer, &rect)
       : SDL_RenderDrawRect(runtime->renderer, &rect);
}

static v2 ToScreenPosition(v2 position, v2 size) {
  return {position.x, Runtime::screen_size.y - position.y - size.y};
}

static void DrawPlayer() {
  const auto screen_position = ToScreenPosition(game_state->player.pos,  //
                                                game_state->player.size);
  DrawRect({(i32)screen_position.x, (i32)screen_position.y,  //
            (i32)game_state->player.size.x, (i32)game_state->player.size.y},
           White, true);
}

static void DrawTileMap() {
  for (int y = 0; y < (i32)TileMap::size.y; ++y) {
    for (int x = 0; x < (i32)TileMap::size.x; ++x) {
      const auto position = v2{x * World::tile_size.x, y * World::tile_size.y};
      const auto screen_position = ToScreenPosition(position, World::tile_size);
      DrawRect({(i32)screen_position.x, (i32)screen_position.y,  //
                (i32)World::tile_size.x, (i32)World::tile_size.y},
               Grey, false);
    }
  }
}

static void DrawBackground() {
  DrawRect({0, 0, (i32)Runtime::screen_size.x, (i32)Runtime::screen_size.y},
           Purple, true);
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
            if (player->grounded) {
              player->velocity.y = World::units * Player::vertical_force;
            }
            break;
          }
          case SDLK_SPACE: {
            if (player->grounded) {
              player->velocity.y = World::units * Player::vertical_force;
            }
            break;
          }
          case SDLK_LEFT: {
            player->velocity.x = -World::units * Player::horizontal_force;
            break;
          }
          case SDLK_RIGHT: {
            player->velocity.x = World::units * Player::horizontal_force;
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

  if (player->pos.y > 0.f) {
    player->velocity.y -= World::gravity * World::units;
    player->grounded = false;
  }

  // TODO: support multiple levels
  if (player->pos.y < 0.f) {
    player->velocity.y = 0.f;
    player->pos.y = 0.f;
  }
  if (player->pos.y == 0.f) {
    player->grounded = true;
  }

  player->pos.x += player->velocity.x;
  player->pos.y += player->velocity.y;
}

extern "C" {
EXPORT void SetRuntime(Runtime* runtime_) {
  runtime = runtime_;
  game_state = std::make_unique<GameState>();
}
EXPORT void Update(void) {
  HandleEvents();
  DrawBackground();
  DrawTileMap();
  // DrawPlayer();
}
}
