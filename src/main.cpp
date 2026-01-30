#include "config/config.hpp"
#include "telegram_bot/telegram_bot.hpp"
#include "telegram_bot/telegram_client_api/telegram_client_api.hpp"
#include "utils/signal_handler.hpp"
#include "weather_checker/weather_checker.hpp"

#include <chrono>
#include <iostream>
#include <thread>

enum class App_State
{
    Initialize,
    Ready
};

int main(int argc, char* argv[])
{
    weatherchecker::WeatherChecker checker;
    checker.poll();
    std::string current_weather = checker.get_weather();
    std::cout << current_weather << "\n";
    // const std::string path = "bot_config.json";
    // config::Config bot_config(path);
    //
    // if (!bot_config.load())
    // {
    //     std::cout << "is not load\n";
    //     return 0;
    // }
    //
    // std::cout << "is load\n";
    // int timeout = 1000;
    // telegram_bot::TelegramBot bot(bot_config.GetToken());
    //
    // while (timeout--)
    // {
    //     bot.Poll();
    //     std::this_thread::sleep_for(std::chrono::seconds(1));
    // }
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
