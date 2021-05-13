#pragma once
#include <SDL.h>
#include <algorithm>
#include <memory>
#include <string>
#include <fstream>
#include <iostream>

#include "typedefs.h"

struct GameState {
  v2 player_pos = {0.f, 0.f};
  v2 player_velocity = {0.f, 0.f};
};
