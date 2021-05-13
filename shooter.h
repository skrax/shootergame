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
  constexpr static f32 velocity = 1.f;
  constexpr static f32 gravity = 0.5f;
};

struct Player {
  constexpr static v2 size = {40, 60};
  constexpr static f32 boost = 3.5f;
  v2 velocity = {0.f, 0.f};
  v2 pos = {0.f, 0.f};
};

struct GameState {
  Player player;
};
