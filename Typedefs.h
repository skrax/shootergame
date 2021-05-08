#pragma once
#include <cinttypes>
using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

struct Vector2 {
  u32 x, y;
};

using v2 = Vector2;

struct Color {
  u8 r, g, b, a = 0xff;
};

constexpr auto Black = Color{0, 0, 0};
constexpr auto White = Color{0xff, 0xff, 0xff};

constexpr v2 screen_size = {1280, 1042};
constexpr u32 fps = 60;
constexpr u32 refresh_rate = 1000 / fps;

struct GameState {
  u32 frame_start;
  bool quit;
  v2 player_pos;
};
