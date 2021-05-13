#define SDL_MAIN_HANDLED
#include "shooter_main.h"
#include "runtime.h"

std::unique_ptr<Runtime> runtime;

using UpdateF = void (*)();
using SetRuntimeF = void (*)(Runtime*);

static std::string GetCompilationTS() {
  std::ifstream ts_f(runtime->app_path + "\\.ts_comp");
  std::string ts;
  std::getline(ts_f, ts);
  return ts;
}

static bool CheckCompilationTS() {
  const auto current = GetCompilationTS();
  if (runtime->compilation_ts != current) {
    runtime->compilation_ts = current;
    return false;
  }
  return true;
}

static void WaitRemainingFrameTime() {
  const auto frame_time = SDL_GetTicks() - runtime->frame_start;
  SDL_Delay(std::max(frame_time, runtime->refresh_rate) - frame_time);
}

static void Clear() {
  SDL_SetRenderDrawColor(runtime->renderer, 0, 0, 0, 0);
  SDL_RenderFillRect(runtime->renderer, nullptr);
}
static void Flush() {
  SDL_RenderPresent(runtime->renderer);
}

static void* LoadLib(void* handle_old = nullptr) {
  if (handle_old) {
    SDL_UnloadObject(handle_old);
  }
  auto lib_load_path = runtime->app_path + DllNameLoaded;
  auto lib_built_path = runtime->app_path + DllName;
  std::remove(lib_load_path.c_str());
  auto rename_err = std::rename(lib_built_path.c_str(), lib_load_path.c_str());
  std::cerr << rename_err << std::endl;
  assert(!rename_err);
  auto result = SDL_LoadObject(lib_load_path.c_str());
  assert(result);
  return result;
}

static std::pair<UpdateF, SetRuntimeF> LoadLibF(void* handle) {
  auto Update = (UpdateF)SDL_LoadFunction(handle, UpdateFName);
  auto SetRuntime = (SetRuntimeF)SDL_LoadFunction(handle, SetRuntimeFName);

  assert(SetRuntime);
  assert(Update);

  return std::make_pair(Update, SetRuntime);
}

int main(int argc, char* argv[]) {
  SDL_SetMainReady();

  runtime = std::make_unique<Runtime>();

  runtime->app_path = SDL_GetBasePath();
  runtime->compilation_ts = GetCompilationTS();

  auto ShooterLib = LoadLib();
  auto [Update, SetRuntime] = LoadLibF(ShooterLib);

  SDL_Init(SDL_INIT_VIDEO);
  runtime->window =
      SDL_CreateWindow(WindowName, SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED,  //
                       runtime->screen_size.x, runtime->screen_size.y, 0);
  runtime->renderer =
      SDL_CreateRenderer(runtime->window, 0, SDL_RENDERER_ACCELERATED);

  SetRuntime(runtime.get());

  Clear();
  Flush();

  while (!runtime->quit) {
    runtime->frame_start = SDL_GetTicks();

    if (!CheckCompilationTS()) {
      ShooterLib = LoadLib(ShooterLib);
      std::tie(Update, SetRuntime) = LoadLibF(ShooterLib);
      SetRuntime(runtime.get());
    }

    Clear();

    Update();

    WaitRemainingFrameTime();
    Flush();
  }

  SDL_UnloadObject(ShooterLib);
  SDL_DestroyRenderer(runtime->renderer);
  SDL_DestroyWindow(runtime->window);
  SDL_Quit();
  return 0;
}
