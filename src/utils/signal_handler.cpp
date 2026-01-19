#include "signal_handler.hpp"

#include <csignal>
#include <iostream>

namespace utils
{

std::atomic<bool> SignalHandler::running_{true};

void SignalHandler::handle(int signal)
{
    std::cout << "Signal received: " << signal << "\n";
    running_ = false;
}

void SignalHandler::setup()
{
    std::signal(SIGINT, SignalHandler::handle);
    std::signal(SIGTERM, SignalHandler::handle);
}

bool SignalHandler::is_running()
{
    return running_;
}

} // namespace utils
