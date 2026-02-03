#include "stopwatch.hpp"
#include <chrono>

namespace utils::stopwatch
{

Stopwatch::Stopwatch(std::chrono::milliseconds duration) : duration_(duration), start_(std::chrono::steady_clock::now())
{
}
void Stopwatch::reset()
{
    this->start_ = std::chrono::steady_clock::now();
}
bool Stopwatch::expired() const
{
    return std::chrono::steady_clock::now() - this->start_ >= this->duration_;
}
std::chrono::milliseconds Stopwatch::remaining() const
{
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - this->start_);
    if (elapsed >= this->duration_)
        return std::chrono::milliseconds{0};

    return this->duration_ - elapsed;
}
std::chrono::milliseconds Stopwatch::duration() const
{
    return this->duration_;
}
} // namespace utils::stopwatch
