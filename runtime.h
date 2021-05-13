#pragma once
#include <SDL.h>
#include <string>
#include "typedefs.h"

struct Runtime {
  static constexpr v2 screen_size = {1280, 1042};
  static constexpr u32 fps = 60;
  static constexpr u32 refresh_rate = 1000 / fps;

  u32 frame_start;
  bool quit = false;
  std::string app_path;

  SDL_Renderer* renderer;
  SDL_Window* window;
  std::string compilation_ts;
};

