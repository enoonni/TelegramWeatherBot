#include "utils/signal_handler.hpp"

#include <chrono>
#include <iostream>
#include <thread>

int main(int argc, char* argv[])
{
    utils::SignalHandler::setup();

    std::cout << "TelegramWeatherBot started\n";
    while (utils::SignalHandler::is_running())
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "TelegramWeatherBot stopped\n";

    return 0;
}
