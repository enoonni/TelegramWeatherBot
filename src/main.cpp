#include "config/config.hpp"
#include "database/database.hpp"
#include "telegram_bot/telegram_bot.hpp"
#include "utils/signal_handler.hpp"
#include "utils/stopwatch/stopwatch.hpp"
#include "weather_checker/weather_checker.hpp"

#include <chrono>
#include <iostream>
#include <memory>
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
    AppState app_state = AppState::ReadConfigPath;
    db::Database db;
    std::string config_path = "/etc/telegram-weather-bot/bot_config.json";
    config::Config bot_config(config_path);
    weatherchecker::WeatherChecker checker;
    std::unique_ptr<telegrambot::TelegramBot> bot;
    utils::stopwatch::Stopwatch stopwatch(std::chrono::hours(1));
    utils::stopwatch::Stopwatch stopwatch_telegram_poll(std::chrono::seconds(10));
    utils::SignalHandler::setup();

    while (utils::SignalHandler::is_running())
    {
        switch (app_state)
        {
        case AppState::ReadConfigPath:
            if (bot_config.load())
            {
                bot = std::make_unique<telegrambot::TelegramBot>(bot_config.GetToken());
                app_state = AppState::Initialize_db;
            }
            else
            {
                std::cerr << "Error: Config could not be loaded. Entering idle state...\n";

                while (utils::SignalHandler::is_running())
                {
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }
                return 0;
            }
            break;

        case AppState::Initialize_db:
            if (db.initialize())
            {
                app_state = AppState::Ready;
            }
            else
            {
                std::cerr << "Error: Database initialization failed. Entering idle state...\n";
                while (utils::SignalHandler::is_running())
                {
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }
                return 0;
            }
            break;

        case AppState::Ready:
            if (stopwatch_telegram_poll.expired())
            {
                bot->poll();
                stopwatch_telegram_poll.reset();
            }
            else if (stopwatch.expired())
            {
                checker.poll();
                auto current_weather = checker.get_weather();
                auto users = db.get_users();
                for (auto user : users)
                {
                    bot->sendMessage(current_weather, user);
                }
                stopwatch.reset();
            }
            else
            {
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }

            break;

        default:
            break;
        }
    }

    return 0;
}
