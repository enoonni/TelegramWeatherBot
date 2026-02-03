#pragma once

#include <chrono>

namespace utils::stopwatch
{
class Stopwatch
{
  public:
    explicit Stopwatch(std::chrono::milliseconds duration);
    void reset();
    bool expired() const;
    std::chrono::milliseconds remaining() const;
    std::chrono::milliseconds duration() const;

  private:
    std::chrono::milliseconds duration_;
    std::chrono::steady_clock::time_point start_;
};

} // namespace utils::stopwatch
