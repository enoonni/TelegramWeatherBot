#pragma once

#include <atomic>

namespace utils
{
class SignalHandler
{
  public:
    static void setup();
    static bool is_running();

  private:
    static void handle(int signal);
    static std::atomic<bool> running_;
};
} // namespace utils
