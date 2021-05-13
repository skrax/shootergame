#pragma once
#include <SDL.h>
#include <algorithm>
#include <memory>
#include <string>
#include <fstream>
#include <iostream>

#include "runtime.h"
#include "typedefs.h"

struct World {
  constexpr static f32 units = 1.f;
  constexpr static f32 gravity = 0.5f;
  constexpr static v2 tile_size = {32, 32};
};

struct TileMap {
  constexpr static v2 size = {40, 30};
};

struct Player {
  constexpr static v2 size = {32, 64};
  constexpr static f32 vertical_force = 7.5f;
  constexpr static f32 horizontal_force = 2.0f;
  v2 velocity = {0.f, 0.f};
  v2 pos = {20.f, 200.f};
  bool grounded = true;
};

struct GameState {
  Player player;
};
