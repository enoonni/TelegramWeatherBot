#include "config/config.hpp"
#include "database/database.hpp"
#include "telegram_bot/telegram_bot.hpp"
#include "telegram_bot/telegram_client_api/telegram_client_api.hpp"
#include "utils/signal_handler.hpp"
#include "weather_checker/weather_checker.hpp"

#include <chrono>
#include <iostream>
#include <locale>
#include <thread>

enum class AppState
{
    ReadConfigPath,
    Initialize_db,
    Initialize,
    Ready
};

int main(int argc, char* argv[])
{
    utils::SignalHandler signal_handler;
    AppState app_state = AppState::Initialize;
    db::Database db;
    std::string db_path = "telegram.db";
    std::string config_path = "bot_config.json";
    config::Config bot_config(config_path);
    weatherchecker::WeatherChecker checker;

    while (signal_handler.is_running())
    {
        switch (app_state)
        {
        case AppState::ReadConfigPath:
            if (bot_config.load())
            {
                app_state = AppState::Initialize_db;
            }
            else
            {
                while (signal_handler.is_running())
                {
                }
                return 0;
            }
            break;

        case AppState::Initialize_db:
            if (db.initialize(db_path))
            {
                app_state = AppState::Ready;
            }
            else
            {
                while (signal_handler.is_running())
                {
                    checker.poll();
                }
                return 0;
            }
            break;

        case AppState::Ready:
            break;

        default:
            break;
        }
    }

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
