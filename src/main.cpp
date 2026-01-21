#include "http_client.hpp"
#include "utils/signal_handler.hpp"

#include <chrono>
#include <iostream>
#include <thread>

int main(int argc, char* argv[])
{
    http::HttpClient client;

    auto response = client.get("https://www.google.com/get", {{"Accept", "application/json"}});

    std::cout << "status: " << response.status << "\n";
    std::cout << "body:\n"
              << response.body << "\n";
    // utils::SignalHandler::setup();
    //
    // std::cout << "TelegramWeatherBot started\n";
    // while (utils::SignalHandler::is_running())
    // {
    //     std::this_thread::sleep_for(std::chrono::seconds(1));
    // }
    // std::cout << "TelegramWeatherBot stopped\n";

    return 0;
}
