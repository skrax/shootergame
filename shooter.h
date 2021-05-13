#pragma once
#include <SDL.h>
#include <algorithm>
#include <memory>
#include <string>
#include <fstream>
#include <iostream>

#include "typedefs.h"

struct GameState {
  v2 player_pos = {0, 0};
  f32 player_velocity = 20.f;
};
