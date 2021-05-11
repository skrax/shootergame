#include <iostream>

extern "C" {
__declspec(dllexport) void Update(void) {
  std::cout << "Hello from Shooter!" << std::endl;
}
}
