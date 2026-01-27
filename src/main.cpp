#include "config/config.hpp"
#include "telegram_bot/telegram_client_api/telegram_client_api.hpp"
#include "utils/signal_handler.hpp"

#include <chrono>
#include <iostream>
#include <thread>

int main(int argc, char* argv[])
{
    config::Config bot_config("bot_config.json");
    if (bot_config.load())
    {
        std::cout << "is load\n";
    }
    else
    {
        std::cout << "is not load\n";
        return 0;
    }

    telegram_bot::telegram_client_api::TelegramClientApi client;
    auto updates = client.Update(bot_config.GetToken());
    if (updates.size() < 1)
        std::cout << "empty";
    else
        std::cout << updates[0].message_id << "\n";
    //
    // std::cout << "status: " << response.status << "\n";
    // std::cout << "body:\n"
    //           << response.body << "\n";
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
